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


def main():
    path = sys.argv[1]
    data = bytearray(open(path, 'rb').read())
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
