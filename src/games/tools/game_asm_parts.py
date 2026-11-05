#!/usr/bin/env python3
"""game_asm_parts.py SRC.cpp OUT.s : collect a game object's retained assembly.

Game C++ goes through SN's Ps2EeAs, which cannot parse the macros in macro.inc, so retained assembly
is assembled separately with the PS2SDK GNU as and merged afterwards with `ld -r`. Each INCLUDE_ASM entry keeps
its own `.game_<name>` section, so its slot is unchanged.
"""
import re
import sys


def main():
    src, out = sys.argv[1:3]
    text = open(src, encoding='utf-8', errors='replace').read()
    lines = []
    for folder, name in re.findall(r'^INCLUDE_ASM\("([^"]+)", (\w+)\);', text, re.M):
        lines += [
            f'.section .game_{name},"ax",@progbits',
            '.set noat', '.set noreorder',
            f'.include "{folder}/{name}.s"',
            '.set reorder', '.set at',
        ]
    with open(out, 'w', newline='\n') as f:
        f.write('\n'.join(lines) + '\n')


if __name__ == '__main__':
    main()
