#!/usr/bin/env python3
"""Extract loadable ELF bytes at the ROM offsets declared by a splat config.

objcopy -O binary uses load addresses. Deadlocked's network code lives near
32 MiB in RAM, but the split config packs it immediately after the main image.
"""
import argparse
import struct
from pathlib import Path

import yaml


def extract(elf, config):
    if elf[:6] != b"\x7fELF\x01\x01":
        raise ValueError("expected a little-endian ELF32")
    h = struct.unpack_from("<16sHHIIIIIHHHHHH", elf)
    loads = []
    for i in range(h[10]):
        p = struct.unpack_from("<8I", elf, h[5] + i * h[9])
        if p[0] == 1:
            if p[4] > p[5] or p[1] + p[4] > len(elf):
                raise ValueError("invalid or truncated ELF load segment")
            loads.append(p)
    segments = config["segments"]
    result = bytearray(segments[-1][0])
    for segment, following in zip(segments, segments[1:]):
        if segment["type"] == "pad":
            continue
        start = segment["start"]
        end = following["start"] if isinstance(following, dict) else following[0]
        address = segment["vram"]
        if not any(p[2] <= address < p[2] + p[5] for p in loads):
            raise ValueError(f"{segment['name']}: VRAM is outside ELF load segments")
        for p in loads:
            lo, hi = max(address, p[2]), min(address + end - start, p[2] + p[4])
            if lo < hi:
                result[start + lo - address:start + hi - address] = elf[p[1] + lo - p[2]:p[1] + hi - p[2]]
    return result


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("elf", type=Path)
    ap.add_argument("config", type=Path)
    ap.add_argument("output", type=Path)
    args = ap.parse_args()
    result = extract(args.elf.read_bytes(), yaml.safe_load(args.config.read_text()))
    args.output.write_bytes(result)
    print(f"Extracted {len(result):#x} bytes to {args.output}")


if __name__ == "__main__":
    main()
