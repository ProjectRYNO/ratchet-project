#!/usr/bin/env python3
import re
import sys
from pathlib import Path


SEGMENT_RE = re.compile(r"^\s*-\s+name:\s+(.+?)\s*(?:#.*)?$")
KEY_RE = re.compile(r"^\s*(start|vram|subsegments):\s*(.*?)\s*(?:#.*)?$")
SUBSEG_RE = re.compile(r"^\s*-\s*\[\s*(0x[0-9A-Fa-f]+|\d+)\s*,\s*[^,\]]+\s*,\s*([^,\]]+)\s*\]")


def parse_split_addr(path, segment_name, subsegment_name):
    current = None
    in_subsegments = False

    for raw_line in path.read_text().splitlines():
        segment = SEGMENT_RE.match(raw_line)
        if segment:
            current = {"name": segment.group(1).strip(), "start": None, "vram": None}
            in_subsegments = False
            continue

        if current is None:
            continue

        key = KEY_RE.match(raw_line)
        if key:
            key_name, value = key.groups()
            if key_name == "subsegments":
                in_subsegments = current["name"] == segment_name
            elif current["name"] == segment_name:
                current[key_name] = int(value, 0)
            continue

        if not in_subsegments:
            continue

        subsegment = SUBSEG_RE.match(raw_line)
        if not subsegment:
            continue

        offset_text, name = subsegment.groups()
        if name.strip().strip("'\"") != subsegment_name:
            continue

        if current["start"] is None or current["vram"] is None:
            raise ValueError(f"segment {segment_name!r} is missing start or vram")

        return current["vram"] + (int(offset_text, 0) - current["start"])

    raise ValueError(f"could not find {segment_name!r} subsegment {subsegment_name!r}")


def main():
    if len(sys.argv) != 4:
        print(f"usage: {Path(sys.argv[0]).name} YAML SEGMENT SUBSEGMENT", file=sys.stderr)
        return 2

    addr = parse_split_addr(Path(sys.argv[1]), sys.argv[2], sys.argv[3])
    print(f"0x{addr:08x}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
