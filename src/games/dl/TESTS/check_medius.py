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
        'rt_circ_buf_create': (0x01EA6C60, 0x9C),
        'rt_circ_buf_destroy': (0x01EA6D00, 0x50),
        'rt_circ_buf_clear': (0x01EA6D50, 0x20),
        'rt_circ_buf_normalize': (0x01EA70B0, 0x44),
        'rt_circ_buf_get_used': (0x01EA71C8, 0x24),
        'rt_circ_buf_get_used_nowrap': (0x01EA71F0, 0x54),
        'rt_circ_buf_get_avail': (0x01EA7248, 0x30),
        'rt_ip_string2ip': (0x01EA9140, 0x80),
        'rt_ip_ip2string': (0x01EA91C0, 0xAC),
        'rt_list_buf_create_pool': (0x01EB5FB0, 0x104),
        'rt_list_buf_destroy_pool': (0x01EB60B8, 0x48),
        'rt_list_buf_get_pool_used': (0x01EB6100, 0x64),
        'rt_list_buf_create': (0x01EB6168, 0x74),
        'rt_list_buf_destroy': (0x01EB61E0, 0x70),
        'rt_list_buf_clear': (0x01EB6250, 0x68),
        'rt_list_buf_insert': (0x01EB62B8, 0x150),
        'rt_list_buf_set_new_head': (0x01EB6408, 0x1C),
        'rt_list_buf_remove': (0x01EB6428, 0xE4),
        'rt_list_buf_append_data': (0x01EB6510, 0x1D8),
        'rt_list_buf_get_tail': (0x01EB66E8, 0x5C),
        'rt_list_buf_resize_buffer': (0x01EB6748, 0x40),
        'rt_time_get_local': (0x01EAB210, 0x14),
        'rt_time_get_msecs': (0x01EAB228, 0x48),
        'rt_time_start': (0x01EAB270, 0x14),
        'rt_time_get_time_stamp': (0x01EAB288, 0x14),
        'rt_time_elapsed': (0x01EAB2A0, 0x14),
        'rt_time_elapsed_msecs': (0x01EAB2C0, 0x4C),
        'rt_time_elapsed_usecs': (0x01EAB310, 0x4C),
        'rt_time_initialize': (0x01EAB3C0, 0x58),
        'rt_time_get_base_diff': (0x01EAB5B8, 0x58),
        'rt_time_elapsed_timestamp': (0x01EAB610, 0x5C),
        'rt_time_get_gmtime': (0x01EAB690, 0x14),
        'seedMT': (0x01EA9988, 0x4C),
        'seedMTUsingArray': (0x01EA99D8, 0x70),
        'reloadMT': (0x01EA9A48, 0x178),
        'randomMT': (0x01EA9BC8, 0xB4),
        'setNewSeed': (0x01EA9C80, 0x14),
        'rt_mutex_platform_create': (0x01EA9F90, 0x58),
        'rt_mutex_platform_destroy': (0x01EA9FE8, 0x34),
        'rt_mutex_platform_lock': (0x01EAA020, 0x34),
        'rt_mutex_platform_unlock': (0x01EAA060, 0x34),
        'rt_mutex_platform_get_thread_id': (0x01EAA098, 0x38),
        'rt_time_platform_get_time_stamp': (0x01EAB6A8, 0x58),
        'rt_time_platform_update_date_time': (0x01EAB700, 0x15C),
        'rt_time_platform_get_gmtime': (0x01EAB860, 0x14),
        'rt_time_platform_fast_elapsed_msecs': (0x01EABA70, 0x14),
        'rt_time_platform_init': (0x01EABA88, 0x5C),
        'rt_token_start': (0x01EABF38, 0x54),
        'rt_token_shutdown': (0x01EABF90, 0x40),
        'rt_token_is_valid': (0x01EABFD0, 0x10),
        'rt_token_free_owner': (0x01EABFF8, 0xA4),
        'rt_token_check_ownership': (0x01EAC0A0, 0x84),
        'rt_token_expand_table': (0x01EACA50, 0xBC),
        'rt_token_destroy_table': (0x01EACB10, 0x44),
        'rt_token_add_ownership': (0x01EACB58, 0x3C),
        'rt_token_remove_ownership': (0x01EACB98, 0x54),
        'rt_token_build_token_msg': (0x01EACBF0, 0x104),
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
                             ('rt_timebase', 0x01EABC10, 0x01EABF38),
                             ('rt_circ_buf', 0x01EA6C60, 0x01EA7408),
                             ('rt_ip', 0x01EA9140, 0x01EA926C),
                             ('rt_list_buf', 0x01EB5FB0, 0x01EB6914),
                             ('rt_time', 0x01EAB210, 0x01EAB6A8),
                             ('rt_mtrandgen', 0x01EA9988, 0x01EA9C98),
                             ('ps2/rt_mutex_platform', 0x01EA9F90, 0x01EAA0D0),
                             ('ps2/rt_time_platform', 0x01EAB6A8, 0x01EABC10),
                             ('rt_token', 0x01EABF38, 0x01EACEA0)):
        if args.objects and loaded_bytes(original, start, end - start) != loaded_bytes(rebuilt, start, end - start):
            raise SystemExit('FAIL: %s module differs' % name)
    if args.objects:
        check_globals(linked)
        print('PASS: rt_constraint, rt_string, rt_mutex, rt_pack, rt_msg_util, rt_timebase, rt_circ_buf, rt_ip, rt_list_buf, rt_time, rt_mtrandgen and ps2/rt_mutex_platform modules match retail, including retained assembly')


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
