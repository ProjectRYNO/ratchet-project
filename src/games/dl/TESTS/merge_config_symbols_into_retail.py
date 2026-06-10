import collections
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
TESTS = ROOT / "TESTS"
CONFIG_SYMBOLS = [
    ROOT / "config" / "symbols_core.text.txt",
    ROOT / "config" / "symbols_text.txt",
    ROOT / "config" / "symbols_net.text.txt",
]


def parse_config_symbol_line(line):
    match = re.match(r"(.+?)\s*=\s*0x([0-9a-fA-F]+);\s*//\s*type:func(.*)$", line)
    if not match:
        return None
    return {
        "name": match.group(1).strip(),
        "addr": int(match.group(2), 16),
        "extra": match.group(3).strip(),
        "line": line,
    }


def parse_retail_symbol_line(line):
    match = re.match(r"(.+?)\s*=\s*0x([0-9a-fA-F]+);\s*//\s*type:func(.*)$", line)
    if not match:
        return None
    return {
        "name": match.group(1).strip(),
        "addr": int(match.group(2), 16),
        "extra": match.group(3).strip().replace("\\", "/"),
        "line": line,
    }


def main():
    retail_path = TESTS / "retail_symbols.txt"
    retail_lines = retail_path.read_text().splitlines()
    retail_entries = [
        entry for line in retail_lines if (entry := parse_retail_symbol_line(line))
    ]
    retail_by_addr = collections.defaultdict(list)
    retail_by_name_addr = collections.defaultdict(list)
    for entry in retail_entries:
        retail_by_addr[entry["addr"]].append(entry)
        retail_by_name_addr[(entry["name"], entry["addr"])].append(entry)

    section_by_source = {
        "config/symbols_core.text.txt": "core.text",
        "config/symbols_text.txt": ".text",
        "config/symbols_net.text.txt": "net.text",
    }
    config_entries = []
    for path in CONFIG_SYMBOLS:
        for line in path.read_text().splitlines():
            entry = parse_config_symbol_line(line)
            if entry:
                entry["source"] = str(path.relative_to(ROOT)).replace("\\", "/")
                entry["section"] = section_by_source[entry["source"]]
                config_entries.append(entry)

    missing = []
    already_present = []
    addr_conflicts = []
    for entry in config_entries:
        if retail_by_name_addr.get((entry["name"], entry["addr"])):
            already_present.append(entry)
        elif retail_by_addr.get(entry["addr"]):
            addr_conflicts.append((entry, retail_by_addr[entry["addr"]]))
        else:
            missing.append(entry)

    merged_entries = list(retail_entries)
    for entry in missing:
        merged_entries.append(
            {
                "name": entry["name"],
                "addr": entry["addr"],
                "extra": f"section:{entry['section']} match:config_manual source:{entry['source']}",
                "line": "",
            }
        )

    merged_entries.sort(key=lambda entry: (entry["addr"], entry["name"]))
    header = [
        "// Generated/merged retail symbols.",
        "// match:config_manual entries come directly from config/symbols_core.text.txt and were not proto-body matched.",
    ]
    merged_lines = header + [
        f"{entry['name']} = 0x{entry['addr']:08x};  // type:func {entry['extra']}".rstrip()
        for entry in merged_entries
    ]
    retail_path.write_text("\n".join(merged_lines) + "\n")

    report = [
        "Config Symbol Merge Report",
        "",
        f"config_entries: {len(config_entries)}",
        f"already_present_exact_name_addr: {len(already_present)}",
        f"missing_added_to_retail_symbols: {len(missing)}",
        f"address_conflicts_not_added: {len(addr_conflicts)}",
        "",
        "Missing Added",
    ]
    for entry in missing:
        report.append(f"{entry['name']} = 0x{entry['addr']:08x}; // {entry['source']}")

    report.append("")
    report.append("Address Conflicts Not Added")
    for entry, conflicts in addr_conflicts:
        conflict_text = ", ".join(f"{c['name']}@0x{c['addr']:08x}" for c in conflicts)
        report.append(
            f"{entry['name']} = 0x{entry['addr']:08x}; // {entry['source']} conflicts with {conflict_text}"
        )

    report_path = TESTS / "retail_symbols_config_merge_report.txt"
    report_path.write_text("\n".join(report) + "\n")

    print(f"config_entries {len(config_entries)}")
    print(f"already_present {len(already_present)}")
    print(f"missing_added {len(missing)}")
    print(f"address_conflicts_not_added {len(addr_conflicts)}")
    print(f"wrote {retail_path}")
    print(f"wrote {report_path}")


if __name__ == "__main__":
    main()
