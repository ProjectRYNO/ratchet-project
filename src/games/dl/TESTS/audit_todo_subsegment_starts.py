import collections
import re
from pathlib import Path


TESTS = Path(__file__).resolve().parent
BASE_ADDR = 0x100080


def normalize_source_path(path):
    path = path.replace("\\", "/")
    path = re.sub(r"^[A-Za-z]:/rcb/code/stable/", "", path, flags=re.IGNORECASE)
    path = re.sub(r"\.(cpp|c|s)$", "", path, flags=re.IGNORECASE)
    return path


def load_prototype_paths():
    text = (TESTS / "PROTOTYPE FUNCTIONS.txt").read_text(errors="replace")
    blocks = re.split(r"(?=^@function\s+[0-9a-fA-F]+)", text, flags=re.MULTILINE)
    by_proto_addr = {}
    for block in blocks:
        header = re.match(r"@function\s+([0-9a-fA-F]+)", block)
        if not header:
            continue
        path_match = re.search(r"/\*\s*([^*]*X:\\rcb\\code\\stable\\[^*]+?)\s*\*/", block)
        if not path_match:
            continue
        by_proto_addr[int(header.group(1), 16)] = normalize_source_path(path_match.group(1).strip())
    return by_proto_addr


def load_proto_symbols_by_name():
    by_name = collections.defaultdict(list)
    for line in (TESTS / "proto_symbols.txt").read_text().splitlines():
        match = re.match(r"(.+?)\s*=\s*0x([0-9a-fA-F]+);.*type:func", line)
        if match:
            by_name[match.group(1)].append(int(match.group(2), 16))
    return by_name


def load_retail_symbols():
    pattern = re.compile(r"(.+?)\s*=\s*0x([0-9a-fA-F]+);\s*//\s*type:func\s+(.*)$")
    entries = []
    for line in (TESTS / "retail_symbols.txt").read_text().splitlines():
        match = pattern.match(line)
        if not match:
            continue
        extra = match.group(3)
        proto_match = re.search(r"proto:0x([0-9a-fA-F]+)", extra)
        section_match = re.search(r"section:([^ ]+)", extra)
        method_match = re.search(r"match:(\S+)", extra)
        entries.append(
            {
                "name": match.group(1),
                "retail_addr": int(match.group(2), 16),
                "offset": int(match.group(2), 16) - BASE_ADDR,
                "proto_addr": int(proto_match.group(1), 16) if proto_match else None,
                "section": section_match.group(1) if section_match else None,
                "method": method_match.group(1) if method_match else "unknown",
            }
        )
    return entries


def load_todo_entries():
    entry_re = re.compile(
        r"^(?P<prefix>\s*-\s*\[)0x(?P<offset>[0-9a-fA-F]*),\s*"
        r"(?P<kind>[^,\]]+),\s*(?P<path>[^\]]+)(?P<suffix>\].*)$"
    )
    entries = []
    for line_number, line in enumerate((TESTS / "TODO_retail_subsegments.txt").read_text().splitlines(), 1):
        match = entry_re.match(line)
        if not match:
            continue
        raw_offset = match.group("offset")
        entries.append(
            {
                "line": line_number,
                "offset": int(raw_offset, 16) if raw_offset else None,
                "kind": match.group("kind").strip(),
                "path": match.group("path").strip(),
                "normalized_path": normalize_source_path(match.group("path").strip()),
                "text": line,
            }
        )
    return entries


def main():
    proto_paths = load_prototype_paths()
    proto_symbols_by_name = load_proto_symbols_by_name()
    retail_symbols = load_retail_symbols()
    todo_entries = load_todo_entries()
    existing_offset_by_path = {
        entry["normalized_path"]: entry["offset"]
        for entry in todo_entries
        if entry["offset"] is not None
    }

    functions_by_source = collections.defaultdict(list)
    for symbol in retail_symbols:
        source_path = proto_paths.get(symbol["proto_addr"])
        if not source_path and symbol["proto_addr"] is None:
            proto_candidates = proto_symbols_by_name.get(symbol["name"], [])
            source_candidates = {
                proto_paths[proto_addr]
                for proto_addr in proto_candidates
                if proto_addr in proto_paths
            }
            if len(source_candidates) == 1:
                source_path = next(iter(source_candidates))
        if source_path:
            existing_offset = existing_offset_by_path.get(source_path)
            if (
                symbol["proto_addr"] is None
                and existing_offset is not None
                and abs(symbol["offset"] - existing_offset) > 0x400
            ):
                continue
            functions_by_source[source_path].append(symbol)

    for functions in functions_by_source.values():
        functions.sort(key=lambda symbol: symbol["offset"])

    known_entries = [entry for entry in todo_entries if entry["offset"] is not None]
    known_entries.sort(key=lambda entry: (entry["offset"], entry["line"]))

    report = [
        "TODO Subsegment Start Sanity Audit",
        "",
        "Rules:",
        "- Known functions for a source path must not start before that file's TODO subsegment offset.",
        "- Known functions should fall before the next known TODO subsegment offset.",
        "- TODO offsets should be monotonic in file order within the list.",
        "- A first known function later than the TODO offset is acceptable; file starts can include non-path-marked code, padding, or asm.",
        "",
    ]

    issues = []
    checked = 0
    exact_first_function_starts = 0
    starts_before_first_function = 0

    # Check file-list ordering as written.
    previous = None
    for entry in todo_entries:
        if entry["offset"] is None:
            continue
        if previous and entry["offset"] < previous["offset"]:
            issues.append(
                (
                    "todo_order_backtrack",
                    entry,
                    f"previous line {previous['line']} offset=0x{previous['offset']:x}",
                )
            )
        previous = entry

    for index, entry in enumerate(known_entries):
        functions = functions_by_source.get(entry["normalized_path"], [])
        if not functions:
            continue
        checked += 1
        next_offset = known_entries[index + 1]["offset"] if index + 1 < len(known_entries) else None
        first = functions[0]
        last = functions[-1]

        if first["offset"] == entry["offset"]:
            exact_first_function_starts += 1
        elif first["offset"] > entry["offset"]:
            starts_before_first_function += 1
        else:
            issues.append(
                (
                    "function_before_subsegment_start",
                    entry,
                    f"first={first['name']} function_offset=0x{first['offset']:x}",
                )
            )

        if next_offset is not None:
            spills = [function for function in functions if function["offset"] >= next_offset]
            if spills:
                sample = spills[0]
                issues.append(
                    (
                        "function_spills_past_next_subsegment",
                        entry,
                        f"next_offset=0x{next_offset:x} first_spill={sample['name']}@0x{sample['offset']:x}",
                    )
                )

        # Suspiciously large prelude before first known function. Not an error, but worth surfacing.
        prelude = first["offset"] - entry["offset"]
        if prelude > 0x200:
            issues.append(
                (
                    "large_gap_before_first_known_function",
                    entry,
                    f"gap=0x{prelude:x} first={first['name']}@0x{first['offset']:x}",
                )
            )

        if next_offset is not None and last["offset"] >= next_offset:
            pass

    report.append(f"todo_entries: {len(todo_entries)}")
    report.append(f"todo_entries_with_offsets: {len(known_entries)}")
    report.append(f"source_paths_with_known_retail_functions: {len(functions_by_source)}")
    report.append(f"offset_entries_checked_against_functions: {checked}")
    report.append(f"starts_equal_first_known_function: {exact_first_function_starts}")
    report.append(f"starts_before_first_known_function: {starts_before_first_function}")
    report.append(f"issues_or_review_items: {len(issues)}")
    report.append("")
    report.append("Issues / Review Items")
    for kind, entry, detail in issues:
        functions = functions_by_source.get(entry["normalized_path"], [])
        first_detail = ""
        if functions:
            first = functions[0]
            first_detail = (
                f" first_known={first['name']}@0x{first['offset']:x}"
                f" method={first['method']}"
            )
        report.append(
            f"{kind}: line {entry['line']} {entry['path']} "
            f"todo_offset=0x{entry['offset']:x} {detail}{first_detail}"
        )

    report.append("")
    report.append("Checked Entries")
    for entry in known_entries:
        functions = functions_by_source.get(entry["normalized_path"], [])
        if not functions:
            continue
        first = functions[0]
        next_entry = next((candidate for candidate in known_entries if candidate["offset"] > entry["offset"]), None)
        next_text = f" next=0x{next_entry['offset']:x}" if next_entry else ""
        report.append(
            f"line {entry['line']} {entry['path']} start=0x{entry['offset']:x}"
            f" first_known={first['name']}@0x{first['offset']:x}"
            f" gap=0x{first['offset'] - entry['offset']:x}"
            f" funcs={len(functions)}{next_text}"
        )

    out_path = TESTS / "TODO_retail_subsegments_start_audit.txt"
    out_path.write_text("\n".join(report) + "\n")
    print("\n".join(report[:15]))
    print(f"wrote {out_path}")


if __name__ == "__main__":
    main()
