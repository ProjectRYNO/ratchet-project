#!/usr/bin/env python3
"""Strict retail comparison of libm and its compiled C replacements."""
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
    parser.add_argument('object_root', type=Path, help='build/code')
    parser.add_argument('--report', type=Path)
    args = parser.parse_args()
    inventory = json.loads((ROOT/'DOCS/progress/LIBM.json').read_text())
    manifest = yaml.safe_load((ROOT/'config/decompiled_functions.yaml').read_text())
    original, rebuilt = read_elf(args.original)[1], read_elf(args.rebuilt)[1]
    linked = symbols(args.rebuilt)
    count = compiled_bytes = 0
    rows = []
    assert len(inventory['functions']) == 37
    for row in inventory['functions']:
        name, start, end = row['name'], int(row['address'], 16), int(row['end'], 16)
        before, after = loaded_bytes(original, start, end-start), loaded_bytes(rebuilt, start, end-start)
        differences = sum(a != b for a, b in zip(before, after))
        assert differences == 0, '%s: %d differing bytes' % (name, differences)
        assert linked[name][0] == start, 'entry moved: '+name
        if row['compiled']:
            assert manifest['functions'][name] == start
            object_path = args.object_root / Path(row['source'][len('code/'):]).with_suffix('.o')
            compiled = symbols(object_path)
            owner = row['source'][len('code/'):-2]
            slot = next(s for s in manifest['objects'][owner]['slots'] if s['start'] == start)
            for table in (compiled, linked):
                address, size, info, section = table[name]
                assert info & 15 == 2 and section not in (0, 0xFFF1) and 0 < size <= slot['end']-start, 'invalid compiled definition: '+name
                assert name+'.NON_MATCHING' not in table, 'assembly fallback: '+name
            count += 1
            compiled_bytes += linked[name][1]
        else:
            assert name not in manifest['functions'], 'stale inventory: '+name
        rows.append(dict(name=name, compiled=row['compiled'], differing_bytes=differences))
    start, end = int(inventory['module_start'],16), int(inventory['module_end'],16)
    assert loaded_bytes(original,start,end-start) == loaded_bytes(rebuilt,start,end-start), 'module differs'
    constant_bytes = 0
    for bounds in manifest.get('rodata', {}).values():
        for slot in bounds['slots']:
            if not slot['object'].startswith('newlib/libm/'):
                continue
            address, length = slot['start'], slot['end'] - slot['start']
            assert loaded_bytes(original, address, length) == loaded_bytes(rebuilt, address, length), 'constant pool differs: ' + slot['object']
            from elftools.elf.elffile import ELFFile
            with (args.object_root / (slot['object'] + '.o')).open('rb') as stream:
                section = ELFFile(stream).get_section_by_name(slot['section'])
                assert section is not None and section['sh_size'] == length, 'invalid compiled constant pool: ' + slot['object']
                assert section.data() == loaded_bytes(original, address, length), 'object constants differ: ' + slot['object']
            constant_bytes += length
    report = dict(compiled_functions=count, exact_compiled_functions=count, total_functions=37,
                  exact_percent=round(100*count/37,2), compiled_bytes=compiled_bytes,
                  module_bytes=end-start, differing_bytes=0, constant_bytes=constant_bytes, functions=rows)
    if args.report:
        args.report.write_text(json.dumps(report,indent=2)+'\n')
    print('PASS: libm %d/37 functions compiled and byte-exact; %d compiled bytes; entire %d-byte module unchanged (remaining functions use assembly)' % (count, compiled_bytes, end-start))


if __name__ == '__main__':
    main()
