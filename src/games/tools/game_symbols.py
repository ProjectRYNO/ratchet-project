#!/usr/bin/env python3
"""game_symbols.py ELF_LOG : add data symbols a game link reports as undefined.

Each address is derived from the retail instructions at the referencing site: a HI16/LO16 pair, or a
GPREL16 access, with the object's own addend removed. All sites for a symbol must agree, and the
full checkpoint then proves the result. Run in the container from a built tree.
"""
import collections
import glob
import re
import subprocess
import sys

ROOT = '/ProjectRYNO/dl/'
GP = 0x22597F
SYMS = ROOT + 'config/symbols_core.text.txt'


def retail_words(fn):
    path = (glob.glob('code/asm/nonmatchings/game/*/%s.s' % fn) or glob.glob('code/asm/matchings/game/*/%s.s' % fn))[0]
    text = open(path).read().split('endlabel')[0]
    return [int(w[6:8] + w[4:6] + w[2:4] + w[:2], 16) for w in re.findall(r'/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/', text)]


def sext(v):
    return v - 0x10000 if v & 0x8000 else v


def main():
    log = open(sys.argv[1], errors='replace').read()
    wanted = set(re.findall(r"undefined reference to [`']([\w.]+)'", log))
    found = collections.defaultdict(set)
    for obj in glob.glob('build/code/game/*.cpp.o'):
        out = subprocess.run(['mips-linux-gnu-objdump', '-r', obj], capture_output=True, text=True).stdout
        section = None
        relocs = collections.defaultdict(list)
        for line in out.splitlines():
            m = re.match(r'RELOCATION RECORDS FOR \[(.+)\]', line)
            if m:
                section = m[1]
                continue
            m = re.match(r'([0-9a-f]{8}) (R_MIPS_\w+)\s+([\w.]+)', line)
            if m and section and section.startswith('.game_') and m[3] in wanted:
                relocs[(section, m[3])].append((int(m[1], 16), m[2]))
        for (section, sym), items in relocs.items():
            fn = section[6:]
            subprocess.run(['mips-linux-gnu-objcopy', '-O', 'binary', '-j', section, obj, '/tmp/gs.bin'], stderr=subprocess.DEVNULL)
            ours = open('/tmp/gs.bin', 'rb').read()
            words = retail_words(fn)
            hi = None
            for offset, kind in items:
                addend = sext(int.from_bytes(ours[offset:offset + 4], 'little') & 0xffff)
                value = words[offset // 4] & 0xffff
                if kind == 'R_MIPS_HI16':
                    hi = value
                elif kind == 'R_MIPS_LO16' and hi is not None:
                    found[sym].add((hi << 16) + sext(value) - addend)
                elif kind == 'R_MIPS_GPREL16':
                    found[sym].add(GP + sext(value) - addend)
    text = open(SYMS, newline='').read()
    nl = '\r\n' if '\r\n' in text else '\n'
    anchor = 'sdkHeapEnd = 0x0016468C;' + nl
    added = []
    taken = {}
    for path in glob.glob(ROOT + 'config/symbols*.txt'):
        for name, value in re.findall(r'^(\w+)\s*=\s*(0x[0-9A-Fa-f]+)', open(path, errors='replace').read(), re.M):
            taken.setdefault(int(value, 16), name)
    for sym in sorted(wanted):
        values = found.get(sym)
        if not values or len(values) != 1:
            print('UNRESOLVED', sym, [hex(v) for v in values or []])
            continue
        address = next(iter(values))
        if address in taken:
            print('ALIAS: use the label %s instead of %s (0x%08X)' % (taken[address], sym, address))
            continue
        taken[address] = sym
        added.append('%s = 0x%08X;%s' % (sym, address, nl))
    text = text.replace(anchor, anchor + ''.join(added), 1)
    open(SYMS, 'w', newline='').write(text)
    print(''.join(added).replace(nl, ' '))


main()
