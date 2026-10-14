#!/usr/bin/env python3
"""Require exact compiled DL Medius memory slots and unchanged module bytes."""
import argparse
from pathlib import Path
import sys

from check_main_elf import symbols
sys.path.insert(0, str(Path(__file__).resolve().parents[2]/'tools'))
from compare_elf import read_elf
from medius_compiler_probe import loaded_bytes


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('original')
    ap.add_argument('rebuilt')
    ap.add_argument('memory_object')
    args = ap.parse_args()
    _, original, _ = read_elf(args.original)
    _, rebuilt, _ = read_elf(args.rebuilt)
    linked, compiled = symbols(args.rebuilt), symbols(args.memory_object)
    functions = {
        'rt_memory_free': (0x01EA95C0, 0x58),
        'rt_memory_register_callbacks': (0x01EA9768, 0x18),
        'rt_memory_get_aligned_address': (0x01EA9790, 0x48),
    }
    for name, (address, size) in functions.items():
        for table in (linked, compiled):
            entry = table[name]
            if entry[1] != size or entry[2] & 15 != 2 or entry[3] in (0, 0xFFF1):
                raise SystemExit('FAIL: missing compiled function or wrong size: '+name)
        if linked[name][0] != address:
            raise SystemExit('FAIL: wrong address: '+name)
        if loaded_bytes(original, address, size) != loaded_bytes(rebuilt, address, size):
            raise SystemExit('FAIL: byte mismatch: '+name)
        print('PASS: %s at 0x%08X, %d/%d exact compiled bytes' % (name, address, size, size))
    start, size = 0x01EA94D0, 0x308
    if loaded_bytes(original, start, size) != loaded_bytes(rebuilt, start, size):
        raise SystemExit('FAIL: rt_memory module differs')
    print('PASS: entire 776-byte rt_memory module matches retail, including retained assembly')


if __name__ == '__main__':
    main()
