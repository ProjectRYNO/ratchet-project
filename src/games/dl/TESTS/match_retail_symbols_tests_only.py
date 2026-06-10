import collections
import re
import struct
from bisect import bisect_left
from pathlib import Path


TESTS = Path(__file__).resolve().parent
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
    if opcode in (2, 3):
        return word & 0xFC000000
    if opcode in (1, 4, 5, 6, 7, 20, 21, 22, 23):
        return word & 0xFFFF0000
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


def parse_symbols(path):
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


def find_unique_aligned(haystack, needle):
    occurrences = []
    position = haystack.find(needle)
    while position != -1 and len(occurrences) < 2:
        if position % 4 == 0:
            occurrences.append(position)
        position = haystack.find(needle, position + 4)
    return occurrences[0] if len(occurrences) == 1 else None


def body_at(elf, sections, section, addr, size):
    offset = sections[section]["offset"] + addr - sections[section]["addr"]
    return elf[offset : offset + size]


def validate_at(proto_elf, retail_elf, proto_sections, retail_sections, symbol, retail_addr):
    section = symbol["section"]
    size = symbol["size"]
    if size <= 0 or retail_addr + size > retail_sections[section]["addr"] + retail_sections[section]["size"]:
        return None

    proto_body = body_at(proto_elf, proto_sections, section, symbol["proto_addr"], size)
    retail_body = body_at(retail_elf, retail_sections, section, retail_addr, size)
    if proto_body == retail_body:
        return "exact_at"
    if normalize_bytes(proto_body) == normalize_bytes(retail_body):
        return "norm_at"
    return None


def main():
    proto_elf, proto_sections = parse_elf(TESTS / "proto_elf.elf")
    retail_elf, retail_sections = parse_elf(TESTS / "retail_elf.elf")
    retail_normalized = {
        section: normalize_bytes(retail_sections[section]["data"])
        for section in SECTIONS
    }

    symbols = parse_symbols(TESTS / "proto_symbols.txt")
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
    low_confidence = []

    # Pass 1: direct unique body search, including small functions when unique.
    for symbol in [s for s in symbols if s["section"]]:
        section = symbol["section"]
        size = symbol["size"]
        if size < 4 or size % 4:
            continue

        signature = body_at(
            proto_elf, proto_sections, section, symbol["proto_addr"], size
        )
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

    # Pass 2: fill symbols inside two matched anchors when the whole proto gap and
    # retail gap have the same size. This catches tiny/duplicate functions without
    # guessing across inserted or removed code.
    for section in SECTIONS:
        section_symbols = sorted(
            [s for s in symbols if s["section"] == section],
            key=lambda s: (s["proto_addr"], s["index"]),
        )
        anchor_symbols = [
            s for s in section_symbols if s["index"] in matched
        ]

        anchors = [
            (
                proto_sections[section]["addr"],
                retail_sections[section]["addr"],
                -1,
            )
        ]
        anchors.extend(
            (s["proto_addr"], matched[s["index"]], s["index"])
            for s in anchor_symbols
        )
        anchors.append(
            (
                proto_sections[section]["addr"] + proto_sections[section]["size"],
                retail_sections[section]["addr"] + retail_sections[section]["size"],
                -1,
            )
        )
        anchors = sorted(set(anchors))

        proto_addrs = [s["proto_addr"] for s in section_symbols]
        for left, right in zip(anchors, anchors[1:]):
            left_proto, left_retail, _ = left
            right_proto, right_retail, _ = right
            if right_proto <= left_proto:
                continue
            if right_retail - left_retail != right_proto - left_proto:
                continue

            start = bisect_left(proto_addrs, left_proto)
            end = bisect_left(proto_addrs, right_proto)
            for symbol in section_symbols[start:end]:
                if symbol["index"] in matched:
                    continue
                retail_addr = left_retail + symbol["proto_addr"] - left_proto
                validation = validate_at(
                    proto_elf,
                    retail_elf,
                    proto_sections,
                    retail_sections,
                    symbol,
                    retail_addr,
                )
                if validation:
                    matched[symbol["index"]] = retail_addr
                    methods[symbol["index"]] = f"gap_equal_{validation}"
                else:
                    low_confidence.append((symbol, retail_addr, "gap_equal"))

    # Pass 3: section translation for the remaining leading/trailing symbols only
    # when the translated body validates at the expected address.
    section_deltas = {
        section: retail_sections[section]["addr"] - proto_sections[section]["addr"]
        for section in SECTIONS
    }
    for symbol in [s for s in symbols if s["section"] and s["index"] not in matched]:
        retail_addr = symbol["proto_addr"] + section_deltas[symbol["section"]]
        validation = validate_at(
            proto_elf,
            retail_elf,
            proto_sections,
            retail_sections,
            symbol,
            retail_addr,
        )
        if validation:
            matched[symbol["index"]] = retail_addr
            methods[symbol["index"]] = f"section_delta_{validation}"

    output = [
        "// Generated using only files in TESTS: proto_elf.elf, proto_symbols.txt, and retail_elf.elf.",
        "// Methods: exact/norm = unique body search; gap_equal* = placed between two matched anchors with equal byte distance; section_delta* = validated section-start translation.",
        "// gap_equal without a validation suffix is order-derived only; keep those separate if you need only body-proven matches.",
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

    out_path = TESTS / "retail_symbols.txt"
    out_path.write_text("\n".join(output) + "\n")

    unmatched = [
        "// Proto symbols not placed by the TESTS-only matcher.",
        "// section:none usually means the proto symbol is outside core.text/.text/net.text.",
    ]
    for symbol in symbols:
        if symbol["index"] in matched:
            continue
        unmatched.append(
            f"{symbol['name']} = 0x{symbol['proto_addr']:08x};  // "
            f"type:func section:{symbol['section']}"
        )
    unmatched_path = TESTS / "retail_symbols_unmatched.txt"
    unmatched_path.write_text("\n".join(unmatched) + "\n")

    low_confidence_output = [
        "// Candidate placements rejected from retail_symbols.txt because they did not body-validate.",
        "// These are useful leads only, not accepted matches.",
    ]
    for symbol, retail_addr, method in low_confidence:
        low_confidence_output.append(
            f"{symbol['name']} = 0x{retail_addr:08x};  // "
            f"type:func proto:0x{symbol['proto_addr']:08x} "
            f"section:{symbol['section']} rejected_match:{method}"
        )
    low_confidence_path = TESTS / "retail_symbols_low_confidence.txt"
    low_confidence_path.write_text("\n".join(low_confidence_output) + "\n")

    gap_report = [
        "// Unmatched proto symbols grouped by nearest matched anchors.",
        "// If proto_gap_size and retail_gap_size differ, that region likely has inserted/removed/changed retail code.",
        "// If they are equal but symbols remain here, the bodies were too ambiguous or did not validate cleanly.",
    ]
    for section in SECTIONS:
        section_symbols = sorted(
            [s for s in symbols if s["section"] == section],
            key=lambda s: (s["proto_addr"], s["index"]),
        )
        current = []
        left_anchor = None
        for symbol in section_symbols:
            if symbol["index"] in matched:
                if current:
                    first = current[0]
                    last = current[-1]
                    right_anchor = symbol
                    if left_anchor:
                        left_proto = left_anchor["proto_addr"]
                        left_retail = matched[left_anchor["index"]]
                        left_name = left_anchor["name"]
                    else:
                        left_proto = proto_sections[section]["addr"]
                        left_retail = retail_sections[section]["addr"]
                        left_name = "<section_start>"

                    right_proto = right_anchor["proto_addr"]
                    right_retail = matched[right_anchor["index"]]
                    right_name = right_anchor["name"]
                    proto_gap_size = right_proto - left_proto
                    retail_gap_size = right_retail - left_retail

                    gap_report.append("")
                    gap_report.append(
                        f"[{section}] count:{len(current)} "
                        f"proto:0x{first['proto_addr']:08x}-0x{last['proto_addr']:08x} "
                        f"between:{left_name}@0x{left_proto:08x}->"
                        f"{right_name}@0x{right_proto:08x}"
                    )
                    gap_report.append(
                        f"  retail anchors:0x{left_retail:08x}->0x{right_retail:08x} "
                        f"proto_gap_size:0x{proto_gap_size:x} "
                        f"retail_gap_size:0x{retail_gap_size:x} "
                        f"delta:0x{retail_gap_size - proto_gap_size:x}"
                    )
                    for item in current:
                        expected = left_retail + item["proto_addr"] - left_proto
                        gap_report.append(
                            f"  {item['name']} = 0x{item['proto_addr']:08x}; "
                            f"expected_if_equal_gap:0x{expected:08x}"
                        )
                    current = []
                left_anchor = symbol
            else:
                current.append(symbol)

        if current:
            first = current[0]
            last = current[-1]
            if left_anchor:
                left_proto = left_anchor["proto_addr"]
                left_retail = matched[left_anchor["index"]]
                left_name = left_anchor["name"]
            else:
                left_proto = proto_sections[section]["addr"]
                left_retail = retail_sections[section]["addr"]
                left_name = "<section_start>"
            right_proto = proto_sections[section]["addr"] + proto_sections[section]["size"]
            right_retail = retail_sections[section]["addr"] + retail_sections[section]["size"]
            proto_gap_size = right_proto - left_proto
            retail_gap_size = right_retail - left_retail
            gap_report.append("")
            gap_report.append(
                f"[{section}] count:{len(current)} "
                f"proto:0x{first['proto_addr']:08x}-0x{last['proto_addr']:08x} "
                f"between:{left_name}@0x{left_proto:08x}-><section_end>@0x{right_proto:08x}"
            )
            gap_report.append(
                f"  retail anchors:0x{left_retail:08x}->0x{right_retail:08x} "
                f"proto_gap_size:0x{proto_gap_size:x} "
                f"retail_gap_size:0x{retail_gap_size:x} "
                f"delta:0x{retail_gap_size - proto_gap_size:x}"
            )
            for item in current:
                expected = left_retail + item["proto_addr"] - left_proto
                gap_report.append(
                    f"  {item['name']} = 0x{item['proto_addr']:08x}; "
                    f"expected_if_equal_gap:0x{expected:08x}"
                )

    no_section = [s for s in symbols if s["section"] is None and s["index"] not in matched]
    if no_section:
        gap_report.append("")
        gap_report.append(f"[no matched executable section] count:{len(no_section)}")
        for symbol in no_section:
            gap_report.append(f"  {symbol['name']} = 0x{symbol['proto_addr']:08x};")

    gap_report_path = TESTS / "retail_symbols_unmatched_gaps.txt"
    gap_report_path.write_text("\n".join(gap_report) + "\n")

    print(f"wrote {len(output) - 3} matches to {out_path}")
    print(f"wrote {len(unmatched) - 2} unmatched symbols to {unmatched_path}")
    print(f"wrote {len(low_confidence)} low-confidence candidates to {low_confidence_path}")
    print(f"wrote unmatched gap report to {gap_report_path}")
    print(collections.Counter(methods.values()))
    print(f"unmatched_or_ambiguous {len(symbols) - len(matched)}")


if __name__ == "__main__":
    main()
