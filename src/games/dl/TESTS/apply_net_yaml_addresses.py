from __future__ import annotations

import csv
import posixpath
import re
from collections import defaultdict, deque
from pathlib import Path


NET_TEXT_VRAM = 0x01E9A000
NET_TEXT_START = 0x44E000
ADDR_TO_SEGMENT_OFFSET_DELTA = NET_TEXT_VRAM - NET_TEXT_START
HERE = Path(__file__).resolve().parent
YAML_PATH = HERE / "net yaml.txt"
TSV_PATH = HERE / "net_function_sources.tsv"
REPORT_PATH = HERE / "net_yaml_address_report.txt"


SUBSEGMENT_RE = re.compile(
    r"^(?P<prefix>\s*-\s*\[)0x(?P<addr>[0-9A-Fa-f]*)(?P<rest>,\s*(?P<type>[^,\]]+),\s*(?P<path>[^\]]+)\]\s*)$"
)


def yaml_paths(lines: list[str]) -> list[str]:
    paths: list[str] = []
    for line in lines:
        match = SUBSEGMENT_RE.match(line)
        if match:
            paths.append(match.group("path").strip())
    return paths


def source_to_candidates(source: str, yaml_by_base: dict[str, list[str]]) -> list[str]:
    source = source.replace("\\", "/")
    source = source.replace("/../", "/")
    root = ""

    root_filter = ""
    if source.startswith("/public/work/210/"):
        rel = source.removeprefix("/public/work/210/")
        root = "medius/"
        root_filter = "medius/"
    elif source.startswith("/home/abrunstetter/public/HEAD/SVO3/client/core/"):
        rel = source.removeprefix("/home/abrunstetter/public/HEAD/SVO3/client/core/")
        root = "svo3/"
        root_filter = "svo3/"
    else:
        rel = source

    rel_no_ext = re.sub(r"\.(c|cpp|s|h)$", "", rel, flags=re.IGNORECASE)
    rel_no_ext = posixpath.normpath(rel_no_ext)
    candidates = [root + rel_no_ext] if root else []

    base = posixpath.basename(rel_no_ext)
    if base in yaml_by_base:
        candidates.extend(
            path for path in yaml_by_base[base] if not root_filter or path.startswith(root_filter)
        )

    seen: set[str] = set()
    unique: list[str] = []
    for candidate in candidates:
        if candidate not in seen:
            seen.add(candidate)
            unique.append(candidate)
    return unique


def main() -> None:
    lines = YAML_PATH.read_text().splitlines()
    paths = yaml_paths(lines)
    path_set = set(paths)
    yaml_by_base: dict[str, list[str]] = defaultdict(list)
    for path in paths:
        yaml_by_base[posixpath.basename(path)].append(path)

    first_by_path: dict[str, list[tuple[int, str, str]]] = defaultdict(list)
    unmatched_sources: set[str] = set()

    tsv_lines = TSV_PATH.read_text().splitlines()
    if tsv_lines and tsv_lines[0].startswith("# "):
        tsv_lines[0] = tsv_lines[0][2:]
    reader = csv.DictReader(tsv_lines, delimiter="\t")
    for row in reader:
        source = row["file"].strip()
        if not source:
            continue
        retail_addr = int(row["retail_addr"], 16)
        function = row["function"]
        candidates = [candidate for candidate in source_to_candidates(source, yaml_by_base) if candidate in path_set]
        if not candidates:
            unmatched_sources.add(source)
            continue
        for candidate in candidates:
            first_by_path[candidate].append((retail_addr, function, source))

    queues: dict[str, deque[tuple[int, str, str]]] = {}
    for path, entries in first_by_path.items():
        entries.sort(key=lambda item: item[0])
        queues[path] = deque(entries)

    replacements = 0
    kept = 0
    missing_paths: list[str] = []
    report_rows: list[str] = [
        "path\tfile_offset\tretail_addr\tfunction\tsource",
    ]
    out_lines: list[str] = []

    for line in lines:
        match = SUBSEGMENT_RE.match(line)
        if not match:
            out_lines.append(line)
            continue

        path = match.group("path").strip()
        if path in queues and queues[path]:
            retail_addr, function, source = queues[path].popleft()
            file_offset = retail_addr - ADDR_TO_SEGMENT_OFFSET_DELTA
            out_lines.append(f"{match.group('prefix')}0x{file_offset:x}{match.group('rest')}")
            replacements += 1
            report_rows.append(f"{path}\t0x{file_offset:x}\t0x{retail_addr:08x}\t{function}\t{source}")
        else:
            out_lines.append(line)
            if match.group("addr"):
                kept += 1
            else:
                missing_paths.append(path)

    YAML_PATH.write_text("\n".join(out_lines) + "\n")

    report_rows.append("")
    report_rows.append(f"updated_subsegments\t{replacements}")
    report_rows.append(f"kept_existing_addresses\t{kept}")
    report_rows.append(f"unfilled_subsegments\t{len(missing_paths)}")
    report_rows.append(f"unmatched_sources\t{len(unmatched_sources)}")
    if unmatched_sources:
        report_rows.append("")
        report_rows.append("unmatched_source_examples")
        for source in sorted(unmatched_sources)[:80]:
            report_rows.append(source)
    REPORT_PATH.write_text("\n".join(report_rows) + "\n")

    print(f"updated_subsegments: {replacements}")
    print(f"unfilled_subsegments: {len(missing_paths)}")
    print(f"report: {REPORT_PATH}")


if __name__ == "__main__":
    main()
