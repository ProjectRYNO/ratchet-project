#!/usr/bin/env python3
"""Require exact compiled DL Medius memory slots and unchanged module bytes."""
import argparse
import csv
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
    ap.add_argument('objects', nargs='*', help='further compiled Medius objects')
    args = ap.parse_args()
    _, original, _ = read_elf(args.original)
    _, rebuilt, _ = read_elf(args.rebuilt)
    linked, compiled = symbols(args.rebuilt), symbols(args.memory_object)
    for path in args.objects:
        compiled.update({name: entry for name, entry in symbols(path).items() if entry[3] != 0})
    functions = {
        'rt_memory_free': (0x01EA95C0, 0x58),
        'rt_memory_register_callbacks': (0x01EA9768, 0x18),
        'rt_memory_get_aligned_address': (0x01EA9790, 0x48),
        'rt_memory_allocate': (0x01EA94D0, 0x74),
        'rt_memory_allocate_init_zero': (0x01EA9550, 0x70),
        'rt_memory_align_alloc': (0x01EA9618, 0x90),
        'rt_memory_align_alloc_init_zero': (0x01EA96A8, 0x70),
        'rt_memory_align_free': (0x01EA9718, 0x50),
        'rt_memory_register_another_callback': (0x01EA9780, 0x10),
    }
    functions.update({
        'rt_constraint_check_RT_U1BYTE': (0x01EA8DF0, 0x28),
        'rt_constraint_check_RT_4BYTE': (0x01EA8E18, 0x28),
        'rt_constraint_check_RT_U4BYTE': (0x01EA8E40, 0x28),
        'rt_constraint_check_RT_CSTRING': (0x01EA8E80, 0x48),
        'rt_strnlen': (0x01EAB1B8, 0x58),
        'rt_mutex_create': (0x01EA9D98, 0x48),
        'rt_mutex_destroy': (0x01EA9DE0, 0x48),
        'rt_mutex_lock': (0x01EA9E28, 0xA8),
        'rt_mutex_unlock': (0x01EA9ED8, 0xA4),
        'rt_init_pack_buffer': (0x01EAA0D0, 0x60),
        'rt_pack_anything': (0x01EAA130, 0xE8),
        'rt_pack_1byte': (0x01EAA218, 0x90),
        'rt_pack_cu2byte': (0x01EAA2A8, 0x110),
        'rt_msg_set_ubyte': (0x01EA97E0, 0x1C),
        'rt_msg_get_ubyte': (0x01EA9800, 0x24),
        'rt_msg_set_u2byte': (0x01EA9828, 0x24),
        'rt_msg_get_u2byte': (0x01EA9850, 0x38),
        'rt_msg_set_u4byte': (0x01EA9888, 0x38),
        'rt_msg_get_u4byte': (0x01EA98C0, 0x60),
        'rt_msg_set_u2byte_be': (0x01EA9928, 0x24),
        'rt_msg_get_u2byte_be': (0x01EA9950, 0x34),
        'rt_timebase_get_globaltime': (0x01EABC10, 0x58),
        'rt_timebase_get_localtime': (0x01EABC68, 0x14),
        'rt_timebase_restart': (0x01EABC80, 0x50),
        'rt_timebase_reset_globaltime': (0x01EABCD0, 0xC),
        'rt_timebase_get_percentiledelay': (0x01EABDA0, 0xD4),
        'rt_timebase_is_query_ready': (0x01EABE78, 0x64),
        'rt_timebase_start': (0x01EABEE0, 0x54),
    } if args.objects else {})
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
    for name, start, end in (('rt_constraint', 0x01EA8DF0, 0x01EA8EC8), ('rt_string', 0x01EAB1B8, 0x01EAB210),
                             ('rt_mutex', 0x01EA9D98, 0x01EA9F7C), ('rt_pack', 0x01EAA0D0, 0x01EAA4BC),
                             ('rt_msg_util', 0x01EA97E0, 0x01EA9984),
                             ('rt_timebase', 0x01EABC10, 0x01EABF38)):
        if args.objects and loaded_bytes(original, start, end - start) != loaded_bytes(rebuilt, start, end - start):
            raise SystemExit('FAIL: %s module differs' % name)
    if args.objects:
        check_globals(linked)
        print('PASS: rt_constraint, rt_string, rt_mutex, rt_pack, rt_msg_util and rt_timebase modules match retail, including retained assembly')


def check_globals(linked):
    path = Path(__file__).resolve().parents[1]/'DOCS/symbols/MEDIUS_GLOBALS.csv'
    with path.open() as inventory:
        rows = list(csv.DictReader(inventory))
    for row in rows:
        if linked.get(row['name'], (None,))[0] != int(row['address'], 16):
            raise SystemExit('FAIL: global not at its retail address: '+row['name'])
    print('PASS: %d Medius globals at their retail addresses' % len(rows))


if __name__ == '__main__':
    main()
