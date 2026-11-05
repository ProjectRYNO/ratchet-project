#!/usr/bin/env python3
"""game_tables.py : register each game function's jump table as a rodata slot.

Reads `.game_<fn>.rodata` sections from the built objects, and the table's address from the retail
asm's `jtbl_<address>` reference. Only the checkpoint proves the table contents. Run in the
container from a built tree.
"""
import glob
import re
import subprocess

ROOT = '/ProjectRYNO/dl/'


def retail_asm(fn):
    for sub in ('nonmatchings', 'matchings'):
        paths = glob.glob('code/asm/%s/game/*/%s.s' % (sub, fn))
        if paths:
            return open(paths[0]).read()
    return ''


def main():
    y = ROOT + 'config/decompiled_functions.yaml'
    text = open(y, newline='').read()
    nl = '\r\n' if '\r\n' in text else '\n'
    anchor = '  asm/build/data.data:' + nl + '    slots:' + nl
    rows = ''
    for path in sorted(glob.glob('build/code/game/*.cpp.o')):
        name = path.split('/')[-1][:-len('.cpp.o')]
        out = subprocess.run(['mips-linux-gnu-objdump', '-h', path], capture_output=True, text=True).stdout
        for section, size in re.findall(r'^\s*\d+ (\.game_\S+\.rodata)\s+([0-9a-f]+)', out, re.M):
            if section + ',' in text:
                continue
            fn = section[6:-7]
            tables = sorted(set(re.findall(r'jtbl_([0-9A-F]{8})', retail_asm(fn))))
            if len(tables) != 1:
                print('CHECK BY HAND', fn, tables)
                continue
            start = int(tables[0], 16)
            end = start + int(size, 16)
            rows += '      - {object: game/%s, function: %s, section: %s, start: 0x%08X, end: 0x%08X}%s' % (name, fn, section, start, end, nl)
            print('table', fn, hex(start), hex(end))
    if rows:
        open(y, 'w', newline='').write(text.replace(anchor, anchor + rows, 1))


main()
