#!/usr/bin/env python3
import sys
import struct

def patch_elf(filename):
    with open(filename, 'r+b') as f:
        data = bytearray(f.read())
    e_shoff = struct.unpack_from('<I', data, 32)[0]
    e_shentsize = struct.unpack_from('<H', data, 46)[0]
    e_shnum = struct.unpack_from('<H', data, 48)[0]
    patched = 0
    for i in range(e_shnum):
        sh_offset = e_shoff + i * e_shentsize
        sh_type = struct.unpack_from('<I', data, sh_offset + 4)[0]
        if sh_type == 0x70000005:
            struct.pack_into('<I', data, sh_offset + 4, 1)
            patched += 1
    if patched:
        with open(filename, 'wb') as f:
            f.write(data)
        print(f"Patched {patched} sections in {filename}")

if __name__ == '__main__':
    for f in sys.argv[1:]:
        patch_elf(f)
