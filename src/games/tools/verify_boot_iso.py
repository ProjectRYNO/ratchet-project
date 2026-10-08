#!/usr/bin/env python3
"""Verify a boot-only ISO build against its original disc and compiled ELF."""
import argparse
import hashlib
import json
from pathlib import Path
import struct

SECTOR = 2048


def boot_record(stream):
    stream.seek(16 * SECTOR)
    pvd = stream.read(SECTOR)
    if pvd[:7] != b'\x01CD001\x01':
        raise ValueError('Missing primary ISO volume descriptor')
    sector = struct.unpack_from('<I', pvd, 158)[0]
    length = struct.unpack_from('<I', pvd, 166)[0]
    if length > 16 * 1024 * 1024:
        raise ValueError('Root directory is too large')
    stream.seek(sector * SECTOR)
    directory = stream.read(length)
    offset = 0
    while offset < len(directory):
        size = directory[offset]
        if not size:
            offset = (offset // SECTOR + 1) * SECTOR
            continue
        record = directory[offset:offset + size]
        if len(record) < 34 or len(record) != size:
            raise ValueError('Malformed ISO directory')
        name = record[33:33 + record[32]].split(b';')[0].upper()
        if name == b'SCUS_974.65':
            lba, be_lba = struct.unpack_from('<I', record, 2)[0], struct.unpack_from('>I', record, 6)[0]
            count, be_count = struct.unpack_from('<I', record, 10)[0], struct.unpack_from('>I', record, 14)[0]
            if lba != be_lba or count != be_count:
                raise ValueError('Boot directory endianness fields disagree')
            return sector * SECTOR + offset, lba, count, pvd
        offset += size
    raise ValueError('Boot executable not found')


def verify(original, rebuilt, elf):
    expected = elf.read_bytes()
    original_size, rebuilt_size = original.stat().st_size, rebuilt.stat().st_size
    with original.open('rb') as source, rebuilt.open('rb') as output:
        record, _, _, _ = boot_record(source)
        installed_record, lba, length, pvd = boot_record(output)
        if installed_record != record or lba * SECTOR != original_size or length != len(expected):
            raise ValueError('Boot ELF was not appended at the expected location')
        if rebuilt_size != original_size + ((length + SECTOR - 1) // SECTOR) * SECTOR:
            raise ValueError('Output ISO length differs')
        if struct.unpack_from('<I', pvd, 80)[0] != rebuilt_size // SECTOR or struct.unpack_from('>I', pvd, 84)[0] != rebuilt_size // SECTOR:
            raise ValueError('Volume size fields differ')
        output.seek(lba * SECTOR)
        if output.read(length) != expected:
            raise ValueError('Installed boot ELF does not match the compiled ELF')
        source.seek(0)
        output.seek(0)
        offset = 0
        while offset < original_size:
            before = source.read(min(1024 * 1024, original_size - offset))
            after = bytearray(output.read(len(before)))
            for start, count in ((16 * SECTOR + 80, 8), (record + 2, 16)):
                lo, hi = max(offset, start), min(offset + len(before), start + count)
                if lo < hi:
                    after[lo - offset:hi - offset] = before[lo - offset:hi - offset]
            if before != after:
                raise ValueError(f'Unrelated ISO bytes changed at block 0x{offset:X}')
            offset += len(before)
    return dict(status='PASS', original_bytes=original_size, output_bytes=rebuilt_size,
                boot_elf_sha256=hashlib.sha256(expected).hexdigest(),
                preserved='All original disc bytes except boot extent/size and primary volume size')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('original', type=Path)
    parser.add_argument('rebuilt', type=Path)
    parser.add_argument('elf', type=Path)
    args = parser.parse_args()
    print(json.dumps(verify(args.original, args.rebuilt, args.elf), indent=2))
