#!/usr/bin/env python3
"""Compare every 989snd slot and module byte; require compiled definitions."""
import argparse
import json
from pathlib import Path
import sys
import yaml
from check_main_elf import symbols
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
from compare_elf import read_elf
from medius_compiler_probe import loaded_bytes

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('original')
    parser.add_argument('rebuilt')
    parser.add_argument('object', help='build/code/989snd/ee/989snd.o')
    parser.add_argument('--report', type=Path)
    args = parser.parse_args()
    manifest = yaml.safe_load((ROOT/'config/decompiled_functions.yaml').read_text())
    module = manifest['objects']['989snd/ee/989snd']
    old, new = read_elf(args.original)[1], read_elf(args.rebuilt)[1]
    linked, compiled = symbols(args.rebuilt), symbols(args.object)
    functions, remnants = [], []
    for slot in module['slots']:
        name = slot['section'][len('.snd_'):]
        start, end = slot['start'], slot['end']
        differences = sum(a != b for a, b in zip(
            loaded_bytes(old, start, end-start), loaded_bytes(new, start, end-start)))
        if name not in manifest['functions']:
            assert differences == 0, 'retained fragment differs: '+name
            remnants.append(name)
            continue
        for table in (linked, compiled):
            address, size, info, section = table[name]
            assert info & 15 == 2 and section not in (0, 0xFFF1), 'not compiled: '+name
            assert 0 < size <= end-start, 'slot overrun: '+name
            assert name+'.NON_MATCHING' not in table, 'fallback: '+name
        assert linked[name][0] == start, 'entry moved: '+name
        functions.append(dict(name=name, address=hex(start), size=linked[name][1],
                              slot_size=end-start, differing_bytes=differences,
                              exact=differences == 0))
    assert len(functions) == 59 and len(remnants) == 18, '989snd inventory changed'
    start, end = module['text_start'], module['text_end']
    differences = sum(a != b for a, b in zip(
        loaded_bytes(old, start, end-start), loaded_bytes(new, start, end-start)))
    exact = sum(f['exact'] for f in functions)
    report = dict(compiled_functions=len(functions), exact_functions=exact,
                  module_bytes=end-start, differing_bytes=differences,
                  exact_remnants=len(remnants), functions=functions)
    if args.report:
        args.report.write_text(json.dumps(report, indent=2)+'\n')
    for function in functions:
        if not function['exact']:
            print('NONMATCH: %s (%d differing bytes)' %
                  (function['name'], function['differing_bytes']))
    print('%s: 989snd %d/59 exact compiled functions, %d/18 exact fragments; '
          '%d differing bytes in entire %d-byte module' %
          ('PASS' if differences == 0 else 'NONMATCH', exact, len(remnants), differences, end-start))
    return int(exact != 59 or differences != 0)


if __name__ == '__main__':
    raise SystemExit(main())
