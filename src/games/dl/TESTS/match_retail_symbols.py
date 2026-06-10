import collections
import re
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
TESTS = ROOT / "TESTS"
SECTIONS = ["core.text", ".text", "net.text"]


def parse_elf(path):
    data = path.read_bytes()
    if data[:4] != b"\x7fELF":
        raise SystemExit(f"not an ELF: {path}")

    shoff = struct.unpack_from("<I", data, 32)[0]
    shentsize = struct.unpack_from("<H", data, 46)[0]
    shnum = struct.unpack_from("<H", data, 48)[0]
    shstrndx = struct.unpack_from("<H", data, 50)[0]

    raw_sections = [
        struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize)
        for i in range(shnum)
    ]
    shstr = raw_sections[shstrndx]
    names = data[shstr[4] : shstr[4] + shstr[5]]

    sections = {}
    for values in raw_sections:
        name_offset, section_type, flags, addr, offset, size, *_ = values
        name_end = names.find(b"\0", name_offset)
        name = names[name_offset:name_end].decode("ascii", "replace")
        sections[name] = {
            "addr": addr,
            "offset": offset,
            "size": size,
            "flags": flags,
            "data": data[offset : offset + size] if section_type != 8 else b"",
        }

    return data, sections


def section_for(sections, addr):
    for section in SECTIONS:
        info = sections[section]
        if info["addr"] <= addr < info["addr"] + info["size"]:
            return section
    return None


def normalize_word(word):
    opcode = (word >> 26) & 0x3F

    # j / jal
    if opcode in (2, 3):
        return word & 0xFC000000

    # Common PC-relative branches, including COP branches.
    if opcode in (1, 4, 5, 6, 7, 20, 21, 22, 23):
        return word & 0xFFFF0000

    # Immediate/load/store forms often encode addresses or stack/member offsets.
    if opcode in (
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        32,
        33,
        34,
        35,
        36,
        37,
        38,
        39,
        40,
        41,
        42,
        43,
        46,
        47,
        49,
        50,
        51,
        54,
        55,
        57,
        58,
        59,
        62,
        63,
    ):
        return word & 0xFFFF0000

    return word


def normalize_bytes(blob):
    size = len(blob) // 4 * 4
    out = bytearray(size)
    for offset in range(0, size, 4):
        word = struct.unpack_from("<I", blob, offset)[0]
        struct.pack_into("<I", out, offset, normalize_word(word))
    return bytes(out)


def parse_symbol_file(path):
    symbols = []
    for index, line in enumerate(path.read_text().splitlines()):
        match = re.match(r"(.+?)\s*=\s*0x([0-9a-fA-F]+);.*type:func", line)
        if match:
            symbols.append(
                {
                    "index": index,
                    "name": match.group(1),
                    "proto_addr": int(match.group(2), 16),
                }
            )
    return symbols


def load_retail_config_names():
    by_name = collections.defaultdict(list)
    for relative_path in (
        "config/symbols_core.text.txt",
        "config/symbols_text.txt",
        "config/symbols_net.text.txt",
    ):
        path = ROOT / relative_path
        if not path.exists():
            continue
        for line in path.read_text().splitlines():
            match = re.match(r"(.+?)\s*=\s*0x([0-9a-fA-F]+);.*type:func", line)
            if match:
                by_name[match.group(1)].append(int(match.group(2), 16))
    return by_name


def find_unique_aligned(haystack, needle):
    occurrences = []
    position = haystack.find(needle)
    while position != -1 and len(occurrences) < 2:
        if position % 4 == 0:
            occurrences.append(position)
        position = haystack.find(needle, position + 4)
    return occurrences[0] if len(occurrences) == 1 else None


def main():
    proto_elf, proto_sections = parse_elf(TESTS / "proto_elf.elf")
    retail_elf, retail_sections = parse_elf(TESTS / "retail_elf.elf")
    retail_normalized = {
        section: normalize_bytes(retail_sections[section]["data"])
        for section in SECTIONS
    }

    symbols = parse_symbol_file(TESTS / "proto_symbols.txt")
    for symbol in symbols:
        symbol["section"] = section_for(proto_sections, symbol["proto_addr"])

    for section in SECTIONS:
        section_symbols = [s for s in symbols if s["section"] == section]
        addrs = sorted({s["proto_addr"] for s in section_symbols})
        for symbol in section_symbols:
            end = next(
                (addr for addr in addrs if addr > symbol["proto_addr"]),
                proto_sections[section]["addr"] + proto_sections[section]["size"],
            )
            symbol["size"] = end - symbol["proto_addr"]

    matched = {}
    methods = {}

    for symbol in [s for s in symbols if s["section"]]:
        section = symbol["section"]
        size = symbol["size"]
        if size < 16 or size % 4:
            continue

        proto_offset = (
            proto_sections[section]["offset"]
            + symbol["proto_addr"]
            - proto_sections[section]["addr"]
        )
        signature = proto_elf[proto_offset : proto_offset + size]

        exact_offset = find_unique_aligned(retail_sections[section]["data"], signature)
        if exact_offset is not None:
            matched[symbol["index"]] = retail_sections[section]["addr"] + exact_offset
            methods[symbol["index"]] = "exact"
            continue

        normalized_offset = find_unique_aligned(
            retail_normalized[section], normalize_bytes(signature)
        )
        if normalized_offset is not None:
            matched[symbol["index"]] = (
                retail_sections[section]["addr"] + normalized_offset
            )
            methods[symbol["index"]] = "norm"

    retail_config_names = load_retail_config_names()

    for symbol in [s for s in symbols if s["section"] and s["index"] not in matched]:
        section = symbol["section"]
        candidates = [
            addr
            for addr in retail_config_names.get(symbol["name"], [])
            if section_for(retail_sections, addr) == section
        ]
        if len(candidates) != 1:
            continue

        size = symbol["size"]
        retail_addr = candidates[0]
        if (
            size < 16
            or retail_addr + size
            > retail_sections[section]["addr"] + retail_sections[section]["size"]
        ):
            continue

        proto_offset = (
            proto_sections[section]["offset"]
            + symbol["proto_addr"]
            - proto_sections[section]["addr"]
        )
        retail_offset = (
            retail_sections[section]["offset"]
            + retail_addr
            - retail_sections[section]["addr"]
        )
        proto_body = proto_elf[proto_offset : proto_offset + size]
        retail_body = retail_elf[retail_offset : retail_offset + size]

        if proto_body == retail_body:
            matched[symbol["index"]] = retail_addr
            methods[symbol["index"]] = "config_exact"
        elif normalize_bytes(proto_body) == normalize_bytes(retail_body):
            matched[symbol["index"]] = retail_addr
            methods[symbol["index"]] = "config_norm"

    output = [
        "// Generated by matching TESTS/proto_elf.elf + TESTS/proto_symbols.txt against TESTS/retail_elf.elf.",
        "// Match methods: exact = unique identical body; norm = unique normalized MIPS body; config_* = retail config name anchor with body validation.",
        "// Only validated matches are listed; unmatched/ambiguous proto symbols are omitted.",
    ]

    for symbol in sorted(
        (s for s in symbols if s["index"] in matched),
        key=lambda s: (matched[s["index"]], s["index"]),
    ):
        output.append(
            f"{symbol['name']} = 0x{matched[symbol['index']]:08x};  // "
            f"type:func proto:0x{symbol['proto_addr']:08x} "
            f"section:{symbol['section']} match:{methods[symbol['index']]}"
        )

    output_path = TESTS / "retail_symbols.txt"
    output_path.write_text("\n".join(output) + "\n")

    print(f"wrote {len(output) - 3} matches to {output_path}")
    print(collections.Counter(methods.values()))
    print(f"unmatched_or_ambiguous {len(symbols) - len(matched)}")


if __name__ == "__main__":
    main()
