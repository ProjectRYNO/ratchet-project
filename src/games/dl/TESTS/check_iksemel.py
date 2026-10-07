#!/usr/bin/env python3
"""Check retail node ABI, exact iks.c bytes, and compiled accessor behavior."""
import argparse
import os
from pathlib import Path
import random
import subprocess
import tempfile

from test_989snd_wrappers import WrapperMachine, STACK, MASK, signed
from check_main_elf import symbols
from compare_elf import read_elf

FUNCTIONS = {
    'iks_next': (0x01EE38EC, 0x00),
    'iks_parent': (0x01EE394C, 0x18),
    'iks_child': (0x01EE3960, 0x08),
    'iks_type': (0x01EE3A84, 0x1C),
    'iks_name': (0x01EE3A98, 0x24),
    'iks_cdata': (0x01EE3AAC, 0x28),
}


def region(segments, start, end):
    for address, data in segments:
        if address <= start and end <= address + len(data):
            return data[start-address:end-address]
    raise AssertionError('Range outside loaded image')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('original')
    parser.add_argument('rebuilt')
    args = parser.parse_args()
    game = Path(__file__).resolve().parents[1]
    fields = 'next prev children last_child attributes last_attribute parent type stack name cdata cdata_size'.split()
    code = '#include <stddef.h>\n#include "iks.h"\n'
    code += 'typedef char check_size[(sizeof(iks) == 0x30) ? 1 : -1];\n'
    for i, field in enumerate(fields):
        code += 'typedef char check_%s[(offsetof(iks, %s) == %d) ? 1 : -1];\n' % (field, field, i*4)
    compiler = Path(os.environ.get('PS2DEV_DIR', '/opt/ps2dev'))/'ee/bin/ee-gcc'
    with tempfile.TemporaryDirectory(prefix='ryno-iks-') as directory:
        source = Path(directory)/'layout.c'
        source.write_text(code)
        subprocess.run([str(compiler), '-c', '-I'+str(game/'code/iksemel/src'), str(source),
                        '-o', str(Path(directory)/'layout.o')], check=True)
    old = read_elf(args.original)[1]
    new = read_elf(args.rebuilt)[1]
    linked = symbols(args.rebuilt)
    # Compare the entire original translation unit, including retained assembly.
    assert region(old, 0x01EE3570, 0x01EE3CEC) == region(new, 0x01EE3570, 0x01EE3CEC), 'iks.c bytes changed'
    randomizer = random.Random(0x1EE38EC)
    cases = 0
    for name, (address, offset) in FUNCTIONS.items():
        actual, size, info, section = linked[name]
        assert (actual, size, info & 15) == (address, 20, 2) and section not in (0, 0xFFF1), name
        assert name+'.NON_MATCHING' not in linked, name
        for case in range(129):
            node = 0 if case == 0 else STACK - 0x100
            values = [randomizer.getrandbits(32) for _ in range(12)]
            if case in (1, 2, 3, 4):
                values[offset//4] = [0, 1, 0x80000000, 0xFFFFFFFF][case-1]
            expected = 0 if not node else values[offset//4]
            outputs = []
            for segments in (old, new):
                machine = WrapperMachine(segments, {}, [node]+[0]*7, case)
                for i, value in enumerate(values):
                    machine.write(STACK - 0x100 + i*4, value, 4)
                before = dict(machine.memory)
                calls, result = machine.run(address)
                assert result == expected and not calls, (name, case)
                assert machine.reg[2] == (signed(expected, 32) & MASK), (name, 'EE sign extension')
                assert machine.memory == before, (name, 'unexpected store')
                outputs.append(result)
            assert outputs[0] == outputs[1]
            cases += 1
    print('PASS: iks ABI size + 12 offsets; exact module bytes; %d accessor differential cases' % cases)


if __name__ == '__main__':
    main()
