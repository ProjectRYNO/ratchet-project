#!/usr/bin/env python3
"""Verify compiled replacements and unchanged loaded bytes outside their slots."""
import argparse
import struct
import sys
from pathlib import Path
import yaml

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools"))
from compare_elf import read_elf, runtime_layout


def symbols(path):
    data = Path(path).read_bytes()
    h = struct.unpack_from("<16sHHIIIIIHHHHHH", data)
    sections = [struct.unpack_from("<10I", data, h[6] + i*h[11]) for i in range(h[12])]
    result = {}
    for section in sections:
        if section[1] != 2:
            continue
        strings = sections[section[6]]
        names = data[strings[4]:strings[4]+strings[5]]
        for offset in range(section[4], section[4]+section[5], section[9]):
            name, value, size, info, other, index = struct.unpack_from("<IIIBBH", data, offset)
            result[names[name:].split(b"\0")[0].decode()] = (value, size, info, index)
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("original")
    parser.add_argument("rebuilt")
    parser.add_argument("boot_object")
    args = parser.parse_args()
    if runtime_layout(args.original) != runtime_layout(args.rebuilt):
        raise SystemExit("FAIL: runtime ELF headers changed")
    linked = symbols(args.rebuilt)
    manifest = yaml.safe_load((Path(__file__).resolve().parents[1] / 'config/decompiled_functions.yaml').read_text())
    all_slots = [slot for bounds in manifest['objects'].values() for slot in bounds.get('slots', [])]
    slots = [slot for slot in all_slots if slot['start'] in manifest['functions'].values()]
    object_root = Path(args.boot_object).parents[1]
    for name, expected in manifest['functions'].items():
        slot = next(s for s in slots if s['start'] == expected)
        obj = symbols(object_root / (slot['object'] + '.o'))
        for label, table in (("object", obj), ("ELF", linked)):
            address, size, info, section = table[name]
            if info & 15 != 2 or section in (0, 0xFFF1) or not size:
                raise SystemExit(f"FAIL: {label} {name} is not a real compiled function")
            if name + '.NON_MATCHING' in table:
                raise SystemExit(f"FAIL: original assembly {name} remains in {label}")
        address, size, _, _ = linked[name]
        if address != expected or address + size > slot['end']:
            raise SystemExit(f"FAIL: {name} moved or exceeds its original slot")
        print(f'{name}: address=0x{address:08X}, size=0x{size:X}, compiled object verified')
    _, old_segments, _ = read_elf(args.original)
    _, new_segments, _ = read_elf(args.rebuilt)
    count = 0
    for (address, original), (_, rebuilt) in zip(old_segments, new_segments):
        changed = [address+i for i, (a, b) in enumerate(zip(original, rebuilt)) if a != b]
        unexpected = [a for a in changed if not any(s['start'] <= a < s['end'] for s in slots)]
        if unexpected:
            raise SystemExit(f"FAIL: {len(unexpected)} unexpected differences; first at 0x{unexpected[0]:08X}")
        count += len(changed)
    print(f"PASS: {count} changed bytes, all within registered compiled function slots; every other loaded byte and runtime header matches")


if __name__ == "__main__":
    main()
