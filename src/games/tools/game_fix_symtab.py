#!/usr/bin/env python3
"""game_fix_symtab.py OBJ : make a Ps2EeAs object's symbol table valid for modern binutils.

SN's Ps2EeAs writes local symbols after globals, which the ELF format forbids and GNU ld rejects.
This reorders the table with locals first, remaps relocation entries and sets sh_info.

Ps2EeAs also pads each section with zero words, which can run past a retail slot. Trailing zero
words without a relocation are trimmed from `.game_*` sections; the linker's slot fill restores
any that retail has, and nop is also zero, so no loaded byte changes.

Retail reaches data defined in the same source file through $gp, and Ps2EeAs only does that for
symbols defined in .sdata. Such a variable is declared GAME_GP_DATA in the C++, and its real bytes
stay in the retained data segment. So here each .sdata definition becomes an external reference:
relocations against the section move to the named symbol, the symbol becomes undefined, and the
section is emptied. The final link then resolves it to the retail address.
"""
import glob
import os
import re
import struct
import sys

SHT_SYMTAB, SHT_RELA, SHT_REL = 2, 4, 9
R_MIPS_GPREL16 = 7
# Ps2EeAs biases gp-relative immediates against a section by this much.
GP_BIAS = 0x4000


def section_name(data, shstr, h):
    end = data.index(0, shstr[4] + h[0])
    return bytes(data[shstr[4] + h[0]:end])


def externalize_sdata(data, headers, shoff, shentsize, symtab, shstr):
    sdata = next((i for i, h in enumerate(headers) if section_name(data, shstr, h) == b'.sdata'), None)
    if sdata is None or headers[sdata][5] == 0:
        return
    offset, size, entsize = headers[symtab][4], headers[symtab][5], headers[symtab][9]
    named = {}
    section_syms = set()
    for at in range(offset, offset + size, entsize):
        name, value, _, info, _, shndx = struct.unpack_from('<IIIBBH', data, at)
        if shndx != sdata:
            continue
        if info & 0xf == 3:
            section_syms.add((at - offset) // entsize)
        elif info >> 4 != 0:
            named[value] = (at - offset) // entsize
    for h in headers:
        if h[1] != SHT_REL or h[6] != symtab:
            continue
        target = headers[h[7]]
        for at in range(h[4], h[4] + h[5], h[9]):
            where, info = struct.unpack_from('<II', data, at)
            if info >> 8 not in section_syms:
                continue
            if info & 0xff != R_MIPS_GPREL16:
                raise SystemExit('unsupported relocation against .sdata')
            word = struct.unpack_from('<I', data, target[4] + where)[0]
            imm = word & 0xffff
            imm = imm - 0x10000 if imm & 0x8000 else imm
            var = imm + GP_BIAS
            base = max((v for v in named if v <= var), default=None)
            if base is None:
                raise SystemExit('.sdata access with no named symbol at offset %d' % var)
            struct.pack_into('<I', data, target[4] + where, (word & 0xffff0000) | ((var - base) & 0xffff))
            struct.pack_into('<I', data, at + 4, (named[base] << 8) | R_MIPS_GPREL16)
    for index in named.values():
        at = offset + index * entsize
        struct.pack_into('<I', data, at + 4, 0)
        struct.pack_into('<H', data, at + 14, 0)
    struct.pack_into('<I', data, shoff + sdata * shentsize + 20, 0)


R_MIPS_HI16, R_MIPS_LO16 = 5, 6


def retail_words(fn):
    """Retail words of split function FN (as game_symbols.py reads them, .byte lines included)."""
    paths = glob.glob('code/asm/nonmatchings/game/*/%s.s' % fn) or glob.glob('code/asm/matchings/game/*/%s.s' % fn)
    if not paths:
        return None
    text = open(paths[0]).read().split('endlabel')[0]
    words = []
    for m in re.finditer(r'/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/|^\s*\.byte\s+(0x[0-9A-Fa-f]+(?:\s*,\s*0x[0-9A-Fa-f]+){3})\s*$', text, re.M):
        if m[1]:
            w = m[1]
            words.append(int(w[6:8] + w[4:6] + w[2:4] + w[:2], 16))
        else:
            b = [int(x, 16) for x in m[2].split(',')]
            words.append(b[0] | b[1] << 8 | b[2] << 16 | b[3] << 24)
    return words


def label_at(address):
    for path in sorted(glob.glob('config/symbols*.txt')) + ['build/undefined_syms_auto.txt']:
        if os.path.exists(path):
            for name, value in re.findall(r'^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', open(path, errors='replace').read(), re.M):
                if int(value, 16) == address:
                    return name
    return 'D_%X' % address


def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


def externalize_sdata_constants(data):
    """Point %hi/%lo pairs at an anonymous .sdata constant to the retail label instead.

    GCC puts a small initialized local array (e.g. `unsigned char v[4] = {2, 3, 4, 5};`) in .sdata as an
    unnamed $LC and reaches it with lui/addiu against the section symbol. Retail's copy of those bytes is
    already in the retained data at a labelled address. The address is read from the retail instructions
    at the same word offsets, the relocations are moved to that label (a new undefined symbol the final
    link resolves) and the instruction addends are cleared. The .sdata contents are then dropped with the
    rest of .sdata by externalize_sdata."""
    shoff = struct.unpack_from('<I', data, 32)[0]
    shentsize, shnum, shstrndx = struct.unpack_from('<HHH', data, 46)
    headers = [list(struct.unpack_from('<10I', data, shoff + i * shentsize)) for i in range(shnum)]
    shstr = headers[shstrndx]

    def name_of(h):
        return bytes(data[shstr[4] + h[0]:data.index(0, shstr[4] + h[0])])
    sdata = next((i for i, h in enumerate(headers) if name_of(h) == b'.sdata'), None)
    if sdata is None:
        return data
    symtab = next(i for i, h in enumerate(headers) if h[1] == SHT_SYMTAB)
    offset, size, entsize = headers[symtab][4], headers[symtab][5], headers[symtab][9]
    section_syms = set()
    for at in range(offset, offset + size, entsize):
        _, _, _, info, _, shndx = struct.unpack_from('<IIIBBH', data, at)
        if shndx == sdata and info & 0xf == 3:
            section_syms.add((at - offset) // entsize)
    edits = []
    for h in headers:
        if h[1] != SHT_REL or h[6] != symtab:
            continue
        target = headers[h[7]]
        tname = name_of(target)
        relocs = [struct.unpack_from('<II', data, at) + (at,) for at in range(h[4], h[4] + h[5], h[9])]
        hi = None
        for where, info, at in relocs:
            if info >> 8 not in section_syms or info & 0xff not in (R_MIPS_HI16, R_MIPS_LO16):
                continue
            if not tname.startswith(b'.game_'):
                raise SystemExit('unsupported relocation against .sdata outside a .game_ section')
            words = retail_words(tname[6:].decode())
            if words is None or where // 4 >= len(words):
                raise SystemExit('no retail instruction for .sdata relocation in %s' % tname.decode())
            if info & 0xff == R_MIPS_HI16:
                hi = (where, at, words[where // 4] & 0xffff)
                continue
            if hi is None:
                raise SystemExit('.sdata %lo without %hi in ' + tname.decode())
            address = (hi[2] << 16) + sext16(words[where // 4] & 0xffff)
            edits.append((label_at(address), target[4], hi[0], hi[1], where, at))
    if not edits:
        return data
    # append the new undefined global symbols (after every existing one) and their names
    strtab = headers[symtab][6]
    names = sorted(set(e[0] for e in edits))
    strings = bytearray(data[headers[strtab][4]:headers[strtab][4] + headers[strtab][5]])
    symbols = bytearray(data[offset:offset + size])
    index = {}
    for name in names:
        index[name] = len(symbols) // entsize
        symbols += struct.pack('<IIIBBH', len(strings), 0, 0, 0x10, 0, 0)
        strings += name.encode() + b'\0'
    for name, base, hi_where, hi_at, lo_where, lo_at in edits:
        for where, at, kind in ((hi_where, hi_at, R_MIPS_HI16), (lo_where, lo_at, R_MIPS_LO16)):
            word = struct.unpack_from('<I', data, base + where)[0]
            struct.pack_into('<I', data, base + where, word & 0xffff0000)
            struct.pack_into('<I', data, at + 4, (index[name] << 8) | kind)
    for sec, blob in ((strtab, strings), (symtab, symbols)):
        while len(data) % 16:
            data.append(0)
        headers[sec][4], headers[sec][5] = len(data), len(blob)
        data += blob
    for i, h in enumerate(headers):
        struct.pack_into('<10I', data, shoff + i * shentsize, *h)
    return data


def main():
    path = sys.argv[1]
    data = bytearray(open(path, 'rb').read())
    data = externalize_sdata_constants(data)
    shoff = struct.unpack_from('<I', data, 32)[0]
    shentsize, shnum = struct.unpack_from('<HH', data, 46)
    headers = [list(struct.unpack_from('<10I', data, shoff + i * shentsize)) for i in range(shnum)]
    symtab = next(i for i, h in enumerate(headers) if h[1] == SHT_SYMTAB)
    offset, size, entsize = headers[symtab][4], headers[symtab][5], headers[symtab][9]
    symbols = [bytes(data[offset + i:offset + i + entsize]) for i in range(0, size, entsize)]
    # Index 0 is the null symbol and stays first.
    order = sorted(range(len(symbols)), key=lambda i: (i != 0, symbols[i][12] >> 4 != 0, i))
    new_index = {old: new for new, old in enumerate(order)}
    for new, old in enumerate(order):
        data[offset + new * entsize:offset + (new + 1) * entsize] = symbols[old]
    locals_count = sum(1 for s in symbols if s[12] >> 4 == 0)
    struct.pack_into('<I', data, shoff + symtab * shentsize + 28, locals_count)
    for h in headers:
        if h[1] in (SHT_REL, SHT_RELA) and h[6] == symtab:
            step = h[9]
            for at in range(h[4], h[4] + h[5], step):
                info = struct.unpack_from('<I', data, at + 4)[0]
                struct.pack_into('<I', data, at + 4, (new_index[info >> 8] << 8) | (info & 0xff))
    shstr = headers[struct.unpack_from('<H', data, 50)[0]]
    externalize_sdata(data, headers, shoff, shentsize, symtab, shstr)
    relocated = {}
    for h in headers:
        if h[1] in (SHT_REL, SHT_RELA) and h[6] == symtab:
            relocated.setdefault(h[7], set()).update(
                struct.unpack_from('<I', data, at)[0] for at in range(h[4], h[4] + h[5], h[9]))
    for i, h in enumerate(headers):
        end = data.index(0, shstr[4] + h[0])
        if not bytes(data[shstr[4] + h[0]:end]).startswith(b'.game_') or h[1] != 1:
            continue
        size = h[5]
        while size >= 4 and data[h[4] + size - 4:h[4] + size] == b'\0\0\0\0' and size - 4 not in relocated.get(i, ()):
            size -= 4
        struct.pack_into('<I', data, shoff + i * shentsize + 20, size)
    open(path, 'wb').write(data)


if __name__ == '__main__':
    main()
