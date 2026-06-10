import collections
import re
import struct
from pathlib import Path


TESTS = Path(__file__).resolve().parent
SECTIONS = ["core.text", ".text", "net.text"]


def parse_elf(path):
    data = path.read_bytes()
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


def body_at(elf, sections, section, addr, size):
    offset = sections[section]["offset"] + addr - sections[section]["addr"]
    return elf[offset : offset + size]


def parse_proto_symbols(path, proto_sections):
    symbols = []
    by_addr = collections.defaultdict(list)
    for index, line in enumerate(path.read_text().splitlines()):
        match = re.match(r"(.+?)\s*=\s*0x([0-9a-fA-F]+);.*type:func", line)
        if not match:
            continue
        addr = int(match.group(2), 16)
        section = section_for(proto_sections, addr)
        symbol = {
            "index": index,
            "name": match.group(1),
            "proto_addr": addr,
            "section": section,
        }
        symbols.append(symbol)
        by_addr[addr].append(symbol)

    for section in SECTIONS:
        section_symbols = [s for s in symbols if s["section"] == section]
        addrs = sorted({s["proto_addr"] for s in section_symbols})
        for symbol in section_symbols:
            end = next(
                (addr for addr in addrs if addr > symbol["proto_addr"]),
                proto_sections[section]["addr"] + proto_sections[section]["size"],
            )
            symbol["size"] = end - symbol["proto_addr"]
    return symbols


def parse_retail_symbols(path):
    entries = []
    pattern = re.compile(r"(.+?)\s*=\s*0x([0-9a-fA-F]+);\s*//\s*type:func\s+(.*)$")
    for line_number, line in enumerate(path.read_text().splitlines(), 1):
        match = pattern.match(line)
        if not match:
            continue
        extra = match.group(3)
        proto_match = re.search(r"proto:0x([0-9a-fA-F]+)", extra)
        section_match = re.search(r"section:([^ ]+)", extra)
        method_match = re.search(r"match:(\S+)", extra)
        entries.append(
            {
                "line": line_number,
                "name": match.group(1),
                "retail_addr": int(match.group(2), 16),
                "proto_addr": int(proto_match.group(1), 16) if proto_match else None,
                "section": section_match.group(1) if section_match else None,
                "method": method_match.group(1) if method_match else "unknown",
                "text": line,
            }
        )
    return entries


def main():
    proto_elf, proto_sections = parse_elf(TESTS / "proto_elf.elf")
    retail_elf, retail_sections = parse_elf(TESTS / "retail_elf.elf")
    proto_symbols = parse_proto_symbols(TESTS / "proto_symbols.txt", proto_sections)
    proto_by_key = {(s["name"], s["proto_addr"]): s for s in proto_symbols}
    entries = parse_retail_symbols(TESTS / "retail_symbols.txt")

    issues = []
    method_counts = collections.Counter(e["method"] for e in entries)
    validation_counts = collections.Counter()

    by_retail = collections.defaultdict(list)
    by_proto = collections.defaultdict(list)
    for entry in entries:
        by_retail[(entry["section"], entry["retail_addr"])].append(entry)
        if entry["proto_addr"] is not None:
            by_proto[(entry["name"], entry["proto_addr"])].append(entry)

        if entry["method"] == "config_manual":
            validation_counts["config_manual_unverified"] += 1
            continue
        if entry["section"] not in SECTIONS:
            issues.append(("bad_section", entry, "unknown section"))
            continue
        if section_for(retail_sections, entry["retail_addr"]) != entry["section"]:
            issues.append(("retail_out_of_section", entry, "retail address outside section"))
            continue
        symbol = proto_by_key.get((entry["name"], entry["proto_addr"]))
        if not symbol:
            issues.append(("missing_proto_source", entry, "not found in proto_symbols.txt"))
            continue
        if symbol["section"] != entry["section"]:
            issues.append(("proto_section_mismatch", entry, f"proto section is {symbol['section']}"))
            continue

        size = symbol.get("size", 0)
        if size <= 0 or entry["retail_addr"] + size > retail_sections[entry["section"]]["addr"] + retail_sections[entry["section"]]["size"]:
            issues.append(("body_out_of_bounds", entry, f"size 0x{size:x}"))
            continue

        proto_body = body_at(proto_elf, proto_sections, entry["section"], entry["proto_addr"], size)
        retail_body = body_at(retail_elf, retail_sections, entry["section"], entry["retail_addr"], size)
        if proto_body == retail_body:
            validation_counts["exact_body_at_addr"] += 1
        elif normalize_bytes(proto_body) == normalize_bytes(retail_body):
            validation_counts["normalized_body_at_addr"] += 1
        else:
            validation_counts["not_body_validated"] += 1
            issues.append(("body_mismatch", entry, f"size 0x{size:x}"))

    duplicate_retail = {
        key: vals for key, vals in by_retail.items() if len(vals) > 1
    }
    duplicate_proto = {
        key: vals for key, vals in by_proto.items() if len(vals) > 1
    }

    order_issues = []
    for section in SECTIONS:
        section_entries = sorted(
            [e for e in entries if e["section"] == section and e["proto_addr"] is not None],
            key=lambda e: (e["proto_addr"], e["line"]),
        )
        previous = None
        for entry in section_entries:
            if previous and entry["retail_addr"] < previous["retail_addr"]:
                order_issues.append((previous, entry))
            previous = entry

    report = [
        "Retail Symbol Accuracy Audit",
        "",
        f"entries: {len(entries)}",
        f"method_counts: {dict(method_counts)}",
        f"body_validation_counts: {dict(validation_counts)}",
        f"issues: {len(issues)}",
        f"duplicate_retail_addresses: {len(duplicate_retail)}",
        f"duplicate_proto_entries: {len(duplicate_proto)}",
        f"proto_order_retail_backtracks: {len(order_issues)}",
        "",
        "Issue Samples",
    ]
    for kind, entry, detail in issues[:200]:
        report.append(
            f"{kind}: line {entry['line']} {entry['name']} "
            f"retail=0x{entry['retail_addr']:08x} proto=0x{entry['proto_addr']:08x} "
            f"method={entry['method']} {detail}"
        )

    report.append("")
    report.append("Duplicate Retail Address Samples")
    for (section, addr), vals in list(duplicate_retail.items())[:100]:
        names = ", ".join(f"{v['name']}@proto:0x{v['proto_addr']:08x}" for v in vals)
        report.append(f"{section} 0x{addr:08x}: {names}")

    report.append("")
    report.append("Proto Order / Retail Backtrack Samples")
    for previous, entry in order_issues[:100]:
        report.append(
            f"{entry['section']}: {previous['name']} proto=0x{previous['proto_addr']:08x} "
            f"retail=0x{previous['retail_addr']:08x} -> {entry['name']} "
            f"proto=0x{entry['proto_addr']:08x} retail=0x{entry['retail_addr']:08x}"
        )

    (TESTS / "retail_symbols_accuracy_audit.txt").write_text("\n".join(report) + "\n")
    print("\n".join(report[:12]))


if __name__ == "__main__":
    main()
