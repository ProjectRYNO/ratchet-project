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
        'KM_MD5': (0x01EB1B30, 0x5C),
        'KM_Salted_MD5': (0x01EB1B90, 0x90),
        'md5Init': (0x01EB1C20, 0x3C),
        'md5Update': (0x01EB1C60, 0x15C),
        'md5Final': (0x01EB1DC0, 0xC8),
        'RC4Init': (0x01EAE190, 0xA0),
        'RC4Code': (0x01EAE230, 0x8C),
        'KM_MD2': (0x01EB0D18, 0x5C),
        'md2Init': (0x01EB0D78, 0x1C),
        'md2Update': (0x01EB0D98, 0xC0),
        'md2Final': (0x01EB0E58, 0x8C),
        'md2Transform': (0x01EB0EE8, 0x158),
        'SHAInit': (0x01EAE980, 0xC8),
        'SHAUpdate': (0x01EAEA48, 0x198),
        'SHAFinal': (0x01EAEBE0, 0x10C),
        'endianTest': (0x01EAECF0, 0x28),
        'KM_MD4': (0x01EB1040, 0x5C),
        'md4Init': (0x01EB10A0, 0x3C),
        'md4Update': (0x01EB10E0, 0xE8),
        'md4Final': (0x01EB11C8, 0xB0),
        'md4Transform': (0x01EB1278, 0x808),
        'Encode': (0x01EB1A80, 0x50),
        'Decode': (0x01EB1AD0, 0x60),
        'KM_Initialize': (0x01EA8EC8, 0xD0),
        'IsNullRSAKey': (0x01EA8F98, 0x40),
        'KM_GetLocalPublicKey': (0x01EA8FD8, 0x114),
        'GetKeyMaster': (0x01EA90F0, 0x4C),
        'NetUseCrypt': (0x01EB2CB0, 0x20),
        'IsNullRCKey': (0x01EB2EE0, 0x40),
        'NewKeyChain': (0x01EB2F20, 0x50),
        'DeleteKeyChain': (0x01EB2F70, 0x80),
        'AppendKeyChain': (0x01EB2FF0, 0x38),
        'GetKeyChain': (0x01EB3028, 0x34),
        'RemoveKeyChain': (0x01EB3060, 0x4C),
        'KM_GetVersionStringPtr': (0x01EB30B8, 0xC),
        'KM_SHA1': (0x01EB30C8, 0x6C),
        'KM_Salted_SHA1': (0x01EB3138, 0xA0),
        'KM_SetLocalClientID': (0x01EB32C8, 0x2C),
        'KM_SetPublicKey': (0x01EB32F8, 0xE8),
        'KM_SetLocalKeyPair': (0x01EB3470, 0xE8),
        'KM_SetGameSessionKey': (0x01EB3558, 0xCC),
        'KM_AddSymmetricKey': (0x01EB36A0, 0x104),
        'KM_CompareSymmetricKey': (0x01EB3838, 0xA8),
        'KM_GetPublicKey': (0x01EB33E0, 0x8C),
        'KM_DeleteKeys': (0x01EB3C70, 0x6C),
        'KM_Destroy': (0x01EB3CE0, 0x124),
        'KM_RSAAdjust': (0x01EB4990, 0x94),
        'lintSetSmallValue': (0x01EACEA0, 0x3C),
        'IsEven': (0x01EACEE0, 0x10),
        'IsZero': (0x01EACEF0, 0x38),
        'lintSetBit': (0x01EACF38, 0x24),
        'MOD': (0x01EACFC0, 0x54),
        'RSAEncryptBlock': (0x01EAE578, 0xC0),
        'RSADecryptBlock': (0x01EAE638, 0xD4),
        'RSAEncrypt': (0x01EAE710, 0x88),
        'RSADecrypt': (0x01EAE798, 0x94),
        'ClearInterfacePointers': (0x01E9FF08, 0x5C),
        'iCreateAndAllocateMessageID': (0x01EDEB28, 0x30),
        'GetOID': (0x01EE1550, 0x80),
        'NetIRegisterMessage': (0x01EA6258, 0x28),
        'NetIRegParseMessage': (0x01EA6280, 0x28),
        'NetIRegisterApplicationMessage': (0x01EA62A8, 0x20),
        'destroy': (0x01EDA770, 0x24),
        'rt_parse_shutdown': (0x01EAA610, 0xF8),
        'rt_parse_update': (0x01EAAE98, 0x1C),
        'NetBitMaskIsSet': (0x01E9FF68, 0x6C),
        'NetBitMaskSet': (0x01E9FFD8, 0x68),
        'MediusDListUpdatePack': (0x01EDA408, 0xF0),
        'MediusDListRequestPack': (0x01EDA5C0, 0xA4),
        'CreateSequence': (0x01ED3A50, 0x8C),
        'DestroySequence': (0x01ED3AE0, 0x24),
        'CreateVSequence': (0x01ED3EA8, 0x78),
        'DestroyVSequence': (0x01ED3F20, 0x24),
        'MediusUpdateClanStats': (0x01ED5320, 0x7C),
        'MediusGetServerTime': (0x01ED5CB8, 0x74),
        'MediusDnasSignature': (0x01ED6418, 0x60),
        'MediusAccountRegistration': (0x01ED6910, 0x84),
        'MediusAccountUpdateStats': (0x01ED6998, 0x7C),
        'MediusAnonymousLogin': (0x01ED6AA8, 0x80),
        'MediusCreateGame': (0x01ED6B28, 0x88),
        'MediusTextFilter': (0x01ED6BB0, 0x80),
        'MediusCreateChannel': (0x01ED6C30, 0x84),
        'MediusJoinChannel': (0x01ED6DB0, 0x80),
        'MediusGetGamePlayers': (0x01ED6E48, 0x7C),
        'MediusGetPlayerInfo': (0x01ED6EC8, 0x7C),
        'MediusGetGameInfo': (0x01ED6F48, 0x7C),
        'MediusGetChannelInfo': (0x01ED6FC8, 0x7C),
        'MediusFindPlayer': (0x01ED7048, 0x80),
        'MediusSendGenericChatMessage': (0x01ED70C8, 0x64),
        'MediusSendBinaryMessage': (0x01ED7130, 0x60),
        'MediusAddToBuddyList': (0x01ED7198, 0x7C),
        'MediusRemoveFromBuddyList': (0x01ED7218, 0x7C),
        'MediusGetIgnoreList': (0x01ED72A0, 0x7C),
        'MediusAddToIgnoreList': (0x01ED7320, 0x7C),
        'MediusRemoveFromIgnoreList': (0x01ED73A0, 0x7C),
        'MediusSendPlayerReport': (0x01ED7530, 0x5C),
        'MediusSendWorldReport': (0x01ED7590, 0x5C),
        'MediusSendEndGameReport': (0x01ED75F0, 0x64),
        'MediusGetAnnouncements': (0x01ED7658, 0x7C),
        'MediusGetAllAnnouncements': (0x01ED76D8, 0x7C),
        'MediusSetGameListFilter': (0x01ED7758, 0x74),
        'MediusClearGameListFilter': (0x01ED77D0, 0x74),
        'MediusGetGameListFilter': (0x01ED7848, 0x7C),
        'MediusGetMyIP': (0x01ED7948, 0x7C),
        'MediusAccountGetID': (0x01ED79D8, 0x7C),
        'MediusGetLocations': (0x01ED7A58, 0x7C),
        'MediusGenericChatSetFilter': (0x01ED7AF0, 0x7C),
        'MediusSetLocalizationParams': (0x01ED7CA8, 0x7C),
        'MediusGetBuddyList_ExtraInfo': (0x01ED7E20, 0x74),
        'MediusGetTotalRankings': (0x01ED7E98, 0x74),
        'MediusGetLobbyPlayerNames_ExtraInfo': (0x01ED7F10, 0x74),
        'MediusGetGames_ExtraInfo': (0x01ED7F88, 0x74),
        'MediusGetChannels_ExtraInfo': (0x01ED8000, 0x74),
        'MediusUpdateLadderStatsWide': (0x01ED8178, 0x74),
        'MediusGetLadderStatsWide': (0x01ED81F8, 0x74),
        'MediusToken': (0x01ED83D8, 0x74),
        'MediusSetAutoChatHistory': (0x01ED8450, 0x74),
        'NetAddressToBinaryAddress': (0x01E9EE28, 0xEC),
        'InitSequence': (0x01ED3B08, 0x58),
        'InitializePRNG': (0x01EB3ED0, 0x40),
        'KM_CreateRandomRCKey': (0x01EB3F10, 0x58),
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
                             ('rt_token', 0x01EABF38, 0x01EACEA0),
                             ('md5', 0x01EB1B30, 0x01EB1E88),
                             ('RC4', 0x01EAE190, 0x01EAE2BC),
                             ('md2', 0x01EB0D18, 0x01EB1040),
                             ('SHA1', 0x01EAE980, 0x01EAED18),
                             ('md4', 0x01EB1040, 0x01EB1B30),
                             ('rt_crypt_public', 0x01EA8EC8, 0x01EA913C),
                             ('rt_crypt', 0x01EB2CB0, 0x01EB4B40),
                             ('LargeInt', 0x01EACEA0, 0x01EAD5D4),
                             ('RSA', 0x01EAE578, 0x01EAE82C),
                             ('DmeInterfaceManager', 0x01E9FF08, 0x01E9FF64),
                             ('stringmanager', 0x01EDEB28, 0x01EDEB58),
                             ('OID', 0x01EE1550, 0x01EE15D8),
                             ('DmeRegister', 0x01EA6258, 0x01EA62C8),
                             ('MediusDMetaType', 0x01EDA668, 0x01EDA870),
                             ('rt_parse', 0x01EAA4C0, 0x01EAB1B8),
                             ('DmeList', 0x01E9FF68, 0x01EA01EC),
                             ('MediusDList_shared', 0x01EDA408, 0x01EDA664),
                             ('sequence', 0x01ED3A50, 0x01ED3EA4),
                             ('vsequence', 0x01ED3EA8, 0x01ED4378),
                             ('MediusClans', 0x01ED5320, 0x01ED5524),
                             ('MediusClient', 0x01ED5528, 0x01ED84C4),
                             ('DmeAddress', 0x01E9EBD8, 0x01E9F050)):
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
