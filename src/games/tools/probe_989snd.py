#!/usr/bin/env python3
"""Probe a 989snd compiler profile; this does not build a usable game ELF.

Relocations resolve to a previously verified game's symbols. Sections retain
retail addresses, but deliberately may overlap for diagnosis: overruns are
reported and can never count as matching. No instruction/relocation masking.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys

import yaml

from compare_elf import read_elf
from medius_compiler_probe import loaded_bytes


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--game', type=Path, required=True)
    parser.add_argument('--original', type=Path, required=True)
    parser.add_argument('--symbols-from', type=Path, required=True)
    parser.add_argument('--cc', required=True)
    parser.add_argument('--assembler', required=True)
    parser.add_argument('--cflags', default='-O2 -G8 -fno-builtin -fno-common')
    parser.add_argument('--asflags', default='-EL -G8')
    parser.add_argument('--shim')
    parser.add_argument('--cross', default='mips-linux-gnu')
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--packet-assignments', action='store_true',
                        help='Probe explicit stores instead of packet array initializers')
    args = parser.parse_args()
    game = args.game.resolve()
    test_dir = game / 'TESTS'
    if not test_dir.is_dir():
        test_dir = game / 'tests'
    sys.path.insert(0, str(test_dir))
    from check_main_elf import symbols

    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=True)
    source = (game / 'code/989snd/ee/989snd.c').read_text()
    if args.packet_assignments:
        def stores(match):
            return ('unsigned int data[' + match[1] + '];\n' +
                    '\n'.join('    data[%d] = %s;' % (i, value.strip())
                              for i, value in enumerate(match[2].split(','))))
        source = re.sub(r'unsigned int data\[(\d+)\] = \{([^{}]+)\};', stores, source)
    (out / '989snd.c').write_text(source)
    (out / '989snd.h').write_bytes((game / 'code/989snd/ee/989snd.h').read_bytes())
    manifest = yaml.safe_load((game / 'config/decompiled_functions.yaml').read_text())
    slots = manifest['objects']['989snd/ee/989snd']['slots']
    definitions = symbols(args.symbols_from)
    owned = {slot['section'][5:] for slot in slots}
    script = 'SECTIONS {\n' + ''.join(
        '%s 0x%x : { *(%s) }\n' % (s['section'], s['start'], s['section'])
        for s in slots) + '}\n'
    script += '\n'.join('%s = 0x%x;' % (name, value[0])
                        for name, value in definitions.items()
                        if value[3] and name not in owned and not name.startswith('snd_') and
                        re.fullmatch(r'[A-Za-z_][A-Za-z_0-9]*', name))
    (out / 'probe.ld').write_text(script)
    env = dict(os.environ)
    if args.shim:
        env['LD_PRELOAD'] = args.shim
    commands = [
        [args.cc, *shlex.split(args.cflags), '-S', str(out / '989snd.c'), '-o', str(out / 'probe.s')],
        [args.assembler, *shlex.split(args.asflags), str(out / 'probe.s'), '-o', str(out / 'probe.o')],
        # Legacy Sony assemblers emit local symbols after sh_info; normalize
        # symbol metadata before the modern linker, leaving code untouched.
        [args.cross + '-strip', '-x', '-N', 'dummy-symbol-name', str(out / 'probe.o')],
        [args.cross + '-ld', '-EL', '--no-warn-mismatch', '--no-check-sections',
         '-T', str(out / 'probe.ld'), str(out / 'probe.o'), '-o', str(out / 'probe.elf')],
    ]
    with (out / 'commands.log').open('w') as log:
        for command in commands:
            log.write(repr(command) + '\n')
            log.flush()
            subprocess.run(command, env=env, stdout=log, stderr=subprocess.STDOUT, check=True)
    original = read_elf(args.original)[1]
    sections = dict(read_elf(out / 'probe.elf')[2])
    data = (out / 'probe.elf').read_bytes()
    compiled_symbols = symbols(out / 'probe.elf')
    rows = []
    for slot in slots:
        name = slot['section'][5:]
        if name not in manifest['functions']:
            continue
        value, size, info, index = compiled_symbols[name]
        assert value == slot['start'] and info & 15 == 2 and index not in (0, 0xfff1), name
        section = sections[slot['section']]
        compiled = data[section[4]:section[4] + section[5]]
        reference = loaded_bytes(original, slot['start'], slot['end'] - slot['start'])
        padded = compiled.ljust(len(reference), b'\0')
        rows.append(dict(name=name, address=hex(value), function_size=size,
                         section_size=len(compiled), slot_size=len(reference),
                         overrun=max(0, len(compiled) - len(reference)),
                         exact=padded == reference,
                         differing_bytes=sum(a != b for a, b in zip(padded, reference)) +
                         max(0, len(compiled) - len(reference))))
    report = dict(compiler=args.cc, assembler=args.assembler, cflags=args.cflags,
                  asflags=args.asflags, packet_assignments=args.packet_assignments,
                  compiler_sha256=hashlib.sha256(Path(args.cc).read_bytes()).hexdigest(),
                  assembler_sha256=hashlib.sha256(Path(args.assembler).read_bytes()).hexdigest(),
                  original_sha256=hashlib.sha256(args.original.read_bytes()).hexdigest(),
                  symbols_elf_sha256=hashlib.sha256(args.symbols_from.read_bytes()).hexdigest(),
                  source_sha256=hashlib.sha256(source.encode()).hexdigest(),
                  exact_functions=sum(row['exact'] for row in rows),
                  compiled_functions=len(rows), functions=rows)
    (out / 'results.json').write_text(json.dumps(report, indent=2) + '\n')
    print('%d/%d exact; %d overflowing sections; probe only, not a game build' %
          (report['exact_functions'], len(rows), sum(bool(row['overrun']) for row in rows)))


if __name__ == '__main__':
    main()
