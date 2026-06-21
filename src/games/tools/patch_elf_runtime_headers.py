#!/usr/bin/env python3
import struct
import sys
from pathlib import Path


PT_LOAD = 1
ELF_MAGIC = b"\x7fELF"
ELFCLASS32 = 1
ELFDATA2LSB = 1


def main() -> int:
    if len(sys.argv) != 2:
        print(f"usage: {Path(sys.argv[0]).name} ELF", file=sys.stderr)
        return 2

    path = Path(sys.argv[1])
    data = bytearray(path.read_bytes())
    if data[:4] != ELF_MAGIC or data[4] != ELFCLASS32 or data[5] != ELFDATA2LSB:
        raise ValueError(f"{path} is not a little-endian ELF32 file")

    data[8] = 0

    e_phoff = struct.unpack_from("<I", data, 0x1C)[0]
    e_phentsize = struct.unpack_from("<H", data, 0x2A)[0]
    e_phnum = struct.unpack_from("<H", data, 0x2C)[0]

    for index in range(e_phnum):
        off = e_phoff + index * e_phentsize
        p_type = struct.unpack_from("<I", data, off)[0]
        if p_type != PT_LOAD:
            continue

        p_vaddr = struct.unpack_from("<I", data, off + 0x08)[0]
        struct.pack_into("<I", data, off + 0x0C, p_vaddr)
        struct.pack_into("<I", data, off + 0x1C, 0x1000)

    path.write_bytes(data)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
