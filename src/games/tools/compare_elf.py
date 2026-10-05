#!/usr/bin/env python3
"""Compare the bytes a PS2 loader will place in memory, not ELF file offsets."""
import argparse
import struct
from pathlib import Path


def read_elf(path):
    data = Path(path).read_bytes()
    if data[:6] != b"\x7fELF\x01\x01":
        raise ValueError(f"{path}: expected little-endian ELF32")
    h = struct.unpack_from("<16sHHIIIIIHHHHHH", data)
    segments = []
    for i in range(h[10]):
        p = struct.unpack_from("<8I", data, h[5] + i * h[9])
        if p[0] == 1:
            segments.append((p[2], data[p[1]:p[1]+p[4]] + bytes(p[5]-p[4])))
    sections = [struct.unpack_from("<10I", data, h[6]+i*h[11]) for i in range(h[12])]
    st = sections[h[13]]
    names = data[st[4]:st[4]+st[5]]
    sections = [(names[s[0]:].split(b"\0")[0].decode(), s) for s in sections]
    return h[4], segments, sections


def runtime_layout(path):
    data = Path(path).read_bytes()
    h = struct.unpack_from("<16sHHIIIIIHHHHHH", data)
    header = (h[0][4:9], h[1], h[2], h[3], h[4], h[7])
    loads = []
    for i in range(h[10]):
        p = struct.unpack_from("<8I", data, h[5] + i * h[9])
        if p[0] == 1:
            # File offsets and debug/section tables may differ. These fields
            # determine what the loader actually puts in memory.
            loads.append(p[2:])
    return header, loads


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("original")
    ap.add_argument("rebuilt")
    args = ap.parse_args()
    entry, segments, sections = read_elf(args.original)
    new_entry, new_segments, _ = read_elf(args.rebuilt)
    print(f"Entry: original=0x{entry:08X}, rebuilt=0x{new_entry:08X}")
    failed = runtime_layout(args.original) != runtime_layout(args.rebuilt)
    print("Runtime headers: " + ("DIFFER" if failed else "match"))
    for addr, data in segments:
        rebuilt = bytearray(len(data))
        covered = bytearray(len(data))
        for a, b in new_segments:
            lo, hi = max(addr, a), min(addr+len(data), a+len(b))
            if lo < hi:
                rebuilt[lo-addr:hi-addr] = b[lo-a:hi-a]
                covered[lo-addr:hi-addr] = b"\1" * (hi-lo)
        differences = [i for i, (x, y) in enumerate(zip(data, rebuilt)) if x != y or not covered[i]]
        print(f"LOAD 0x{addr:08X}: {len(differences):,} differing/missing bytes of {len(data):,}")
        failed |= bool(differences)
        for name, s in sections:
            if not s[2] & 2 or not addr <= s[3] < addr+len(data):
                continue
            ds = [addr+i for i in differences if s[3] <= addr+i < s[3]+s[5]]
            print(f"  {name:16} {len(ds):7,} differences" + (f"; first 0x{ds[0]:08X}" if ds else ""))
        for i in differences[:8]:
            print(f"    0x{addr+i:08X}: {data[i:i+16].hex()} -> {rebuilt[i:i+16].hex()}")
    return int(failed)


if __name__ == "__main__":
    raise SystemExit(main())
