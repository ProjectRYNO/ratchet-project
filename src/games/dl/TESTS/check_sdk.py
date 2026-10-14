#!/usr/bin/env python3
"""Require unmasked retail SDK bytes and real compiled definitions."""
import argparse
import json
from pathlib import Path
import sys
from check_main_elf import symbols
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
from compare_elf import read_elf
from medius_compiler_probe import loaded_bytes


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('original')
    ap.add_argument('rebuilt')
    ap.add_argument('object_directory', help='build/code/sdk')
    args = ap.parse_args()
    expected = json.loads(Path(__file__).with_name('sdk_expected.json').read_text())
    _, original, _ = read_elf(args.original)
    _, rebuilt, _ = read_elf(args.rebuilt)
    linked = symbols(args.rebuilt)
    objects = {m: symbols(Path(args.object_directory) / (m + '.o')) for m in expected['modules']}
    total = 0
    for name, spec in expected['functions'].items():
        address, size = spec['address'], spec['size']
        for table in (linked, objects[spec['module']]):
            entry = table[name]
            assert entry[1] == size and entry[2] & 15 == 2 and entry[3] not in (0, 0xFFF1), name
            assert name + '.NON_MATCHING' not in table, name
        assert linked[name][0] == address, name
        assert loaded_bytes(original, address, size) == loaded_bytes(rebuilt, address, size), name
        total += size
        print('PASS: %s, %d exact compiled bytes' % (name, size))
    for module, (start, end) in expected['modules'].items():
        assert loaded_bytes(original, start, end-start) == loaded_bytes(rebuilt, start, end-start), module
        print('PASS: entire %s module, including padding and retained fragments' % module)
    print('PASS: %d functions, %d exact compiled bytes' % (len(expected['functions']), total))


if __name__ == '__main__':
    main()
