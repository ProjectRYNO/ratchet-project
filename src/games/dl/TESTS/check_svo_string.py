#!/usr/bin/env python3
"""Retail-versus-rebuilt SVO string helpers; behavior, ABI, and matching status."""
import argparse
from pathlib import Path
import random

from test_989snd_wrappers import WrapperMachine, STACK, MASK, signed
from check_main_elf import symbols
from compare_elf import read_elf

FUNCTIONS = {
    'svstrncpy': (0x01EEDCD0, 0xE0), 'svsubstrncpy': (0x01EEDDB0, 0xC4),
    'svsnprintf': (0x01EEDE74, 0xDC), 'my_strcspn': (0x01EEDF50, 0x90),
    'svstrlen': (0x01EEDFE0, 0x20), 'svisalpha': (0x01EEE000, 0x28),
    'svisxdigit': (0x01EEE028, 0x48), 'svisdigit': (0x01EEE070, 0xC),
    'svisspace': (0x01EEE07C, 0x40),
}
CLASSIFIERS = {
    'svisalpha': (0x01EEE000, lambda c: 65 <= c <= 90 or 97 <= c <= 122),
    'svisxdigit': (0x01EEE028, lambda c: 48 <= c <= 57 or 65 <= c <= 70 or 97 <= c <= 102),
    'svisdigit': (0x01EEE070, lambda c: 48 <= c <= 57),
    'svisspace': (0x01EEE07C, lambda c: c in (9, 10, 11, 12, 13, 32)),
}
TEXT = STACK - 0x1000


def region(segments, start, end):
    for address, data in segments:
        if address <= start and end <= address + len(data):
            return data[start-address:end-address]
    raise AssertionError('Range outside loaded image')


class StringMachine(WrapperMachine):
    def __init__(self, segments, strlen_address, argument):
        super().__init__(segments, {}, [argument]+[0]*7, 0)
        self.strlen_address = strlen_address

    def intercept(self, pc):
        if pc != self.strlen_address:
            return False
        address = self.reg[4] & 0xFFFFFFFF
        assert address == TEXT, 'strlen received wrong pointer'
        length = 0
        while self.read(address + length, 1):
            length += 1
            assert length <= 1024, 'unterminated test input'
        self.calls.append(('strlen', address))
        self.reg[2] = length
        return True


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('original')
    parser.add_argument('rebuilt')
    args = parser.parse_args()
    old, new = (read_elf(p)[1] for p in (args.original, args.rebuilt))
    linked = symbols(args.rebuilt)
    # User-authorized nonmatching integration; preserve the two established exact matches.
    for name in ('svstrlen', 'svisdigit'):
        address, size = FUNCTIONS[name]
        assert region(old, address, address+size) == region(new, address, address+size), name
    for name, (address, size) in FUNCTIONS.items():
        actual, length, info, section = linked[name]
        assert actual == address and 0 < length <= size and info & 15 == 2 and section not in (0, 0xFFF1), name
        assert name+'.NON_MATCHING' not in linked, name
    randomizer = random.Random(0x1EEE070)
    inputs = list(range(-256, 512)) + [-2147483648, 2147483647, -2147483600, 2147483600]
    inputs += [signed(randomizer.getrandbits(32), 32) for _ in range(256)]
    count = 0
    for name, (address, expected) in CLASSIFIERS.items():
        for value in inputs:
            outputs = []
            for segments in (old, new):
                machine = WrapperMachine(segments, {}, [signed(value, 32) & MASK]+[0]*7, 0)
                calls, result = machine.run(address)
                assert not calls and result == int(expected(value)), (name, value, result)
                outputs.append(result)
            assert outputs[0] == outputs[1]
            count += 1
    texts = [b'', b'a', b'abc', b'abc\0ignored', bytes([255, 128, 127]), b'\0trailing']
    texts += [b'x'*n for n in (7, 8, 15, 16, 31, 32, 255, 256, 1024)]
    for text in texts:
        expected = len(text.split(b'\0', 1)[0]) + 1
        for segments in (old, new):
            machine = StringMachine(segments, linked['strlen'][0], TEXT)
            for i, byte in enumerate(text+b'\0'):
                machine.write(TEXT+i, byte, 1)
            before = bytes(machine.read(TEXT+i, 1) for i in range(len(text)+1))
            calls, result = machine.run(FUNCTIONS['svstrlen'][0])
            assert result == expected and calls == [('strlen', TEXT)], (text, result)
            assert before == bytes(machine.read(TEXT+i, 1) for i in range(len(text)+1)), 'input modified'
    from svo_string_cases import extended_cases
    extra = extended_cases(old, new, linked, FUNCTIONS)
    print('PASS: 9 compiled SVO strings; %d classifier, %d strlen, %d copy/search/format cases (EE; libc mocks)' % (count, len(texts), extra))


if __name__ == '__main__':
    main()
