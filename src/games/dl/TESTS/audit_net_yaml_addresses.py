from __future__ import annotations

import csv
import re
from pathlib import Path

from apply_net_yaml_addresses import (
    ADDR_TO_SEGMENT_OFFSET_DELTA,
    SUBSEGMENT_RE,
    TSV_PATH,
    YAML_PATH,
    source_to_candidates,
    yaml_paths,
)


REPORT_PATH = Path(__file__).resolve().parent / "net_yaml_top_address_audit.txt"


def read_tsv() -> list[dict[str, str]]:
    tsv_lines = TSV_PATH.read_text().splitlines()
    if tsv_lines and tsv_lines[0].startswith("# "):
        tsv_lines[0] = tsv_lines[0][2:]
    return list(csv.DictReader(tsv_lines, delimiter="\t"))


def main() -> None:
    lines = YAML_PATH.read_text().splitlines()
    paths = yaml_paths(lines)
    yaml_by_base: dict[str, list[str]] = {}
    for path in paths:
        yaml_by_base.setdefault(path.rsplit("/", 1)[-1], []).append(path)
    path_set = set(paths)

    functions: list[dict[str, object]] = []
    for row in read_tsv():
        source = row["file"].strip()
        if not source:
            continue
        retail_addr = int(row["retail_addr"], 16)
        candidates = [p for p in source_to_candidates(source, yaml_by_base) if p in path_set]
        functions.append(
            {
                "retail_addr": retail_addr,
                "offset": retail_addr - ADDR_TO_SEGMENT_OFFSET_DELTA,
                "function": row["function"],
                "source": source,
                "paths": candidates,
            }
        )
    functions.sort(key=lambda item: int(item["offset"]))

    subsegments: list[dict[str, object]] = []
    for lineno, line in enumerate(lines, 1):
        match = SUBSEGMENT_RE.match(line)
        if not match or not match.group("addr"):
            continue
        subsegments.append(
            {
                "line": lineno,
                "offset": int(match.group("addr"), 16),
                "type": match.group("type").strip(),
                "path": match.group("path").strip(),
            }
        )
    subsegments.sort(key=lambda item: int(item["offset"]))

    issues: list[str] = []
    report: list[str] = [
        "line\toffset\tpath\tfunction\tretail_addr\tsource\tstatus",
    ]

    for index, seg in enumerate(subsegments):
        start = int(seg["offset"])
        end = int(subsegments[index + 1]["offset"]) if index + 1 < len(subsegments) else 0x4E5330
        path = str(seg["path"])
        mapped_in_range = [
            f for f in functions if start <= int(f["offset"]) < end and path in f["paths"]
        ]
        if not mapped_in_range:
            issues.append(f"line {seg['line']}: no mapped function in range for {path} at 0x{start:x}")
            report.append(f"{seg['line']}\t0x{start:x}\t{path}\t\t\t\tmissing_mapped_function")
            continue

        first = mapped_in_range[0]
        if int(first["offset"]) != start:
            issues.append(
                f"line {seg['line']}: {path} starts at 0x{start:x}, "
                f"but first mapped function is {first['function']} at 0x{int(first['offset']):x}"
            )
            status = "not_top"
        else:
            status = "ok"

        # Also catch accidental cross-root/basename claims where the function at the exact
        # boundary maps to multiple unrelated YAML paths.
        exact_boundary = [f for f in functions if int(f["offset"]) == start and path in f["paths"]]
        if len(exact_boundary) != 1:
            issues.append(
                f"line {seg['line']}: {path} has {len(exact_boundary)} exact boundary matches at 0x{start:x}"
            )
            status = "ambiguous_boundary"

        report.append(
            f"{seg['line']}\t0x{start:x}\t{path}\t{first['function']}\t"
            f"0x{int(first['retail_addr']):08x}\t{first['source']}\t{status}"
        )

    offsets = [int(seg["offset"]) for seg in subsegments]
    ordering_issues = [
        (i, offsets[i - 1], offsets[i]) for i in range(1, len(offsets)) if offsets[i] < offsets[i - 1]
    ]
    for i, prev_addr, addr in ordering_issues:
        issues.append(f"order issue around sorted index {i}: 0x{prev_addr:x} > 0x{addr:x}")

    report.append("")
    report.append(f"filled_subsegments\t{len(subsegments)}")
    report.append(f"top_address_issues\t{len(issues)}")
    if issues:
        report.append("")
        report.append("issues")
        report.extend(issues)

    REPORT_PATH.write_text("\n".join(report) + "\n")
    print(f"filled_subsegments: {len(subsegments)}")
    print(f"top_address_issues: {len(issues)}")
    print(f"report: {REPORT_PATH}")
    if issues:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
