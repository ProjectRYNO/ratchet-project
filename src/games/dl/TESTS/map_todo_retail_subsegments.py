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
        proto_addr = int(header.group(1), 16)
        source_path = normalize_source_path(path_match.group(1).strip())
        by_proto_addr[proto_addr] = source_path
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
                "proto_addr": int(proto_match.group(1), 16) if proto_match else None,
                "section": section_match.group(1) if section_match else None,
                "method": method_match.group(1) if method_match else "unknown",
            }
        )
    return entries


def build_subsegment_map():
    proto_paths = load_prototype_paths()
    proto_symbols_by_name = load_proto_symbols_by_name()
    retail_symbols = load_retail_symbols()
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
        if not source_path:
            continue
        functions_by_source[source_path].append(symbol)

    mapping = {}
    for source_path, symbols in functions_by_source.items():
        first = min(symbols, key=lambda symbol: symbol["retail_addr"])
        mapping[source_path] = {
            "offset": first["retail_addr"] - BASE_ADDR,
            "retail_addr": first["retail_addr"],
            "first_name": first["name"],
            "proto_addr": first["proto_addr"],
            "count": len(symbols),
            "method": first["method"],
        }
    return mapping


def nearest_existing_offset_by_path(todo_entries):
    existing = {}
    for entry in todo_entries:
        if entry["offset"] is not None:
            existing[entry["normalized_path"]] = entry["offset"]
    return existing


def main():
    mapping = build_subsegment_map()
    todo_path = TESTS / "TODO_retail_subsegments.txt"
    lines = todo_path.read_text().splitlines()
    entry_re = re.compile(
        r"^(?P<prefix>\s*-\s*\[)0x(?P<offset>[0-9a-fA-F]*),\s*"
        r"(?P<kind>[^,\]]+),\s*(?P<path>[^\]]+)(?P<suffix>\].*)$"
    )

    existing_offsets = nearest_existing_offset_by_path(
        [
            {
                "offset": int(match.group("offset"), 16) if match.group("offset") else None,
                "normalized_path": normalize_source_path(match.group("path").strip()),
            }
            for line in lines
            if (match := entry_re.match(line))
        ]
    )

    mapped_lines = []
    report = [
        "TODO Retail Subsegment Mapping Report",
        "",
    ]
    filled = 0
    already_correct = 0
    existing_mismatch = []
    missing = []

    for line_number, line in enumerate(lines, 1):
        match = entry_re.match(line)
        if not match:
            mapped_lines.append(line)
            continue

        source_path = match.group("path").strip()
        normalized_path = normalize_source_path(source_path)
        info = mapping.get(normalized_path)

        if not info:
            missing.append((line_number, source_path))
            mapped_lines.append(line)
            continue

        # Manual symbols can be name-associated to a source path, but without a
        # proto address they are weaker evidence. If an existing TODO offset is
        # already present and far away, keep the existing boundary.
        existing_for_path = existing_offsets.get(normalized_path)
        if (
            info["proto_addr"] is None
            and existing_for_path is not None
            and abs(info["offset"] - existing_for_path) > 0x400
        ):
            mapped_lines.append(line)
            continue

        expected_offset = info["offset"]
        existing_offset = match.group("offset")
        replacement = (
            f"{match.group('prefix')}0x{expected_offset:x}, "
            f"{match.group('kind').strip()}, {source_path}{match.group('suffix')}"
        )

        if existing_offset:
            if int(existing_offset, 16) == expected_offset:
                already_correct += 1
            else:
                existing_mismatch.append(
                    (line_number, source_path, int(existing_offset, 16), expected_offset, info)
                )
            mapped_lines.append(line)
        else:
            filled += 1
            mapped_lines.append(replacement)

    mapped_path = TESTS / "TODO_retail_subsegments_mapped.txt"
    mapped_path.write_text("\n".join(mapped_lines) + "\n")
    todo_path.write_text("\n".join(mapped_lines) + "\n")

    report.append(f"known_source_paths_from_prototype_and_retail: {len(mapping)}")
    report.append(f"blank_offsets_filled_in_mapped_copy: {filled}")
    report.append(f"existing_offsets_already_correct: {already_correct}")
    report.append(f"existing_offsets_mismatched: {len(existing_mismatch)}")
    report.append(f"todo_entries_without_mapping: {len(missing)}")

    report.append("")
    report.append("Filled Entries")
    for line, mapped in zip(lines, mapped_lines):
        if line != mapped:
            report.append(mapped.strip())

    report.append("")
    report.append("Existing Offset Mismatches")
    for line_number, source_path, existing, expected, info in existing_mismatch:
        proto_text = (
            f"0x{info['proto_addr']:08x}" if info["proto_addr"] is not None else "none"
        )
        report.append(
            f"line {line_number}: {source_path} existing=0x{existing:x} "
            f"mapped=0x{expected:x} first={info['first_name']} "
            f"retail=0x{info['retail_addr']:08x} proto={proto_text}"
        )

    report.append("")
    report.append("TODO Entries Without Mapping")
    for line_number, source_path in missing:
        report.append(f"line {line_number}: {source_path}")

    report_path = TESTS / "TODO_retail_subsegments_mapping_report.txt"
    report_path.write_text("\n".join(report) + "\n")

    print(f"wrote mapped TODO copy to {mapped_path}")
    print(f"updated TODO in place at {todo_path}")
    print(f"wrote report to {report_path}")
    print(f"filled {filled}, already_correct {already_correct}, mismatches {len(existing_mismatch)}, missing {len(missing)}")


if __name__ == "__main__":
    main()
