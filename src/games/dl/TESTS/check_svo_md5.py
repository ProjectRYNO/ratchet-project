#!/usr/bin/env python3
"""Focused retail-versus-compiled checks for SVO's 64-bit MD5 state.

The EE implementation keeps high state bits unlike conventional uint32 MD5.
Compare the entire context, not just the final 128-bit digest.
"""
import random
import sys
from test_989snd_wrappers import WrapperMachine, STACK, MASK
from check_main_elf import symbols
from compare_elf import read_elf

CONTEXT = STACK - 0x1000
DATA = STACK - 0x1800

class Machine(WrapperMachine):
    max_steps = 20000

    def __init__(self, image, args):
        super().__init__(image, {}, args + [0] * (8 - len(args)), 0)

    def bytes(self, address, size):
        return bytes(self.read(address + i, 1) for i in range(size))


def main():
    if len(sys.argv) != 3:
        raise SystemExit('usage: check_svo_md5.py ORIGINAL REBUILT')
    images = [read_elf(p)[1] for p in sys.argv[1:]]
    syms = symbols(sys.argv[2])
    randomizer = random.Random(0x989)
    count = 0
    for case in range(64):
        context = bytes(randomizer.randrange(256) for _ in range(112))
        block = bytes(randomizer.randrange(256) for _ in range(64))
        results = []
        for image in images:
            machine = Machine(image, [CONTEXT, DATA])
            for i, value in enumerate(context): machine.write(CONTEXT + i, value, 1)
            for i, value in enumerate(block): machine.write(DATA + i, value, 1)
            if case < 32: machine.run(syms['md5_starts'][0])
            machine.reg[4:6] = [CONTEXT, DATA]
            machine.run(syms['md5_process'][0])
            results.append(machine.bytes(CONTEXT, 112))
        assert results[0] == results[1], ('md5_process', case, results)
        count += 1
    print('PASS: %d retail-versus-compiled MD5 compression cases, all 64 state bits' % count)

if __name__ == '__main__':
    main()
