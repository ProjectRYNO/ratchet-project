#!/usr/bin/env python3
"""Check iksemel ABI, library bytes, compiled placement, globals and differential behavior."""
import argparse
import csv
import os
from pathlib import Path
import random
import subprocess
import tempfile

import yaml

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
# dom.c through utility.c, from tagHook to the end of iks_escape.
LIBRARY = (0x01EE32FC, 0x01EE5000)
# Retail dispatches these through .rodata jump tables; their C uses if-chains, so the
# slot bytes differ. Everything else in LIBRARY must equal retail.
NONMATCHING = {'escape_size', 'escape', 'iks_escape', 'sax_core'}
LAYOUTS = [
    ('iks', 0x30, [(f, i*4) for i, f in enumerate(
        'next prev children last_child attributes last_attribute parent type stack name cdata cdata_size'.split())]),
    ('ikstack', 0x18, [('len', 0), ('used', 4), ('pad_0', 8), ('last', 12), ('next', 16), ('data', 20)]),
    ('iksparser', 0x64, [(f, i*4) for i, f in enumerate(
        's user_data tagHook cdataHook deleteHook stack stack_max stack_pos context oldcontext '
        'tag_open token_pos tagtype attmax attcur attflag atts valflag entpos'.split())]
        + [('entity', 0x4C), ('nr_bytes', 0x54), ('nr_lines', 0x58), ('uni_max', 0x5C), ('uni_len', 0x60)]),
]
MEMCPY, STRLEN, STACK_ALLOC = 0x0011A370, 0x0011AB04, 0x01EE3DB0
SRC, DEST, HEAP = STACK - 0x1C00, STACK - 0x1400, STACK - 0xC00
SPECIAL = b'&<>\'"'


class EscapeMachine(WrapperMachine):
    """Runs the escape helpers with strlen, memcpy and iks_stack_alloc stubbed."""
    max_steps = 40000

    def __init__(self, segments, arguments, seed, allocation):
        super().__init__(segments, {}, arguments + [0] * (8 - len(arguments)), seed)
        self.allocation = allocation

    def intercept(self, pc):
        r = self.reg
        a0, a1, a2 = [r[i] & 0xFFFFFFFF for i in (4, 5, 6)]
        if pc == STRLEN:
            n = 0
            while self.read(a0 + n, 1):
                n += 1
            r[2] = n
        elif pc == MEMCPY:
            for i in range(a2):
                self.write(a0 + i, self.read(a1 + i, 1), 1)
            r[2] = a0
        elif pc == STACK_ALLOC:
            r[2] = self.allocation
        else:
            return False
        self.calls.append((pc, a0, a1, a2))
        return True


MEMSET, STRCMP = 0x0011A518, 0x0011A8A0
MALLOC_PTR, FREE_PTR = 0x0016AC68, 0x0016AC6C
FAKE_MALLOC, FAKE_FREE, TAG_HOOK, CDATA_HOOK = 0x00F00000, 0x00F00010, 0x00F00020, 0x00F00030
PARSER, BUFFER, HEAP_BASE = STACK - 0x1F80, STACK - 0x1E00, STACK - 0x1600
WELL_FORMED = [b'<a>', b'</a>', b'<b x="1" y=\'2\'>', b'<c/>', b'<d z="q"/>', b'<f />', b'<g\r h="1"\t/>',
               b'text', b' ', b'\n', b'\r\n', b'\t', b'&amp;', b'&lt;', b'&gt;', b'&quot;', b'&apos;',
               b'<!-- c -->', b'<!---->', b'<!-- - -->', b'<![CDATA[ x ] y ]] z ]]>', b'<![CDATA[]]>',
               b'<?xml v="1"?>', b'<!DOCTYPE x>', b'\xc3\xa9', b'\xe2\x82\xac', b'\xf0\x9f\x98\x80',
               b'<e ' + b' '.join(b'a%d="%d"' % (i, i) for i in range(14)) + b'>',
               b'<m ' + b' '.join(b'a%d="%d"' % (i, i) for i in range(12)) + b'/>',
               b'<n ' + b' '.join(b'a%d="%d"' % (i, i) for i in range(12)) + b'>',
               b'<h >', b'<i a="1" >', b'<j\tk="1">', b'<k\nl="2">', b'<!-- a -- b -->']
XML = WELL_FORMED + [b'&bogus;', b'&toolongname;', b'&', b'<![CDX', b'\xc3', b'\x80', b'\xfe', b'\xff',
                     b'\xc0\x80', b'\xfd\xbf', b'<a  b = "c">', b'<a/ >', b'</a x>', b'</a/>', b'<a b>',
                     b'<a b=c>', b'</ a>', b'<!-x', b'<!-- a --x', b'>', b'<', b'"', b'=', b'/']
# Paths random cases reach only by chance: attribute-array growth failing (the first
# malloc is the initial array, the second its growth) and a second whitespace byte.
ATTRIBUTES_12 = b' '.join(b'a%d="%d"' % (i, i) for i in range(12))
SAX_FIXED = [(b'<e ' + ATTRIBUTES_12 + b' a12="12" a13="13">', 2), (b'<m ' + ATTRIBUTES_12 + b'/>', 2),
             (b'<n ' + ATTRIBUTES_12 + b'>', 2), (b'<e ' + ATTRIBUTES_12 + b'>', 1),
             (b'<o \r p="1"\r\n/>', 0), (b'<q\t\n\rr="1" \t/>', 0)]


class SaxMachine(WrapperMachine):
    """Runs sax_core with the allocator, string helpers and parser hooks stubbed."""
    max_steps = 200000

    def __init__(self, segments, seed, results, failing_malloc):
        super().__init__(segments, {}, [0] * 8, seed)
        self.heap = HEAP_BASE
        self.results = results
        self.failing_malloc = failing_malloc
        self.mallocs = 0

    def read(self, address, size):
        if size == 4 and address & 0xFFFFFFFF in (MALLOC_PTR, FREE_PTR):
            return FAKE_MALLOC if address & 0xFFFFFFFF == MALLOC_PTR else FAKE_FREE
        return super().read(address, size)

    def string(self, address):
        text = b''
        while len(text) < 0x200:
            value = self.read(address + len(text), 1)
            if not value:
                break
            text += bytes([value])
        return text

    def intercept(self, pc):
        r = self.reg
        a0, a1, a2, a3 = [r[i] & 0xFFFFFFFF for i in (4, 5, 6, 7)]
        if pc == MEMSET:
            for i in range(a2):
                self.write(a0 + i, a1 & 0xFF, 1)
            r[2] = a0
            event = ('memset', a0, a1 & 0xFF, a2)
        elif pc == MEMCPY:
            for i in range(a2):
                self.write(a0 + i, self.read(a1 + i, 1), 1)
            r[2] = a0
            event = ('memcpy', a0, a1, a2)
        elif pc == STRCMP:
            left, right = self.string(a0), self.string(a1)
            r[2] = ((left > right) - (left < right)) & MASK
            event = ('strcmp', left, right)
        elif pc == FAKE_MALLOC:
            self.mallocs += 1
            if self.mallocs == self.failing_malloc:
                r[2] = 0
            else:
                r[2] = self.heap
                self.heap += (a0 + 7) & ~7
                assert self.heap <= STACK - 0x400, 'test heap exhausted'
            event = ('malloc', a0, r[2])
        elif pc == FAKE_FREE:
            r[2] = 0
            event = ('free', a0)
        elif pc in (TAG_HOOK, CDATA_HOOK):
            if pc == TAG_HOOK:
                atts = []
                while a2 and len(atts) < 64:
                    pointer = self.read(a2 + 4 * len(atts), 4)
                    if not pointer:
                        break
                    atts.append(self.string(pointer))
                event = ('tag', a0, a1, self.string(a1), a2, tuple(atts), a3)
            else:
                event = ('cdata', a0, a1, bytes(self.read(a1 + i, 1) for i in range(a2)), a2)
            r[2] = self.results.pop(0) if self.results else 0
        else:
            return False
        self.calls.append(event)
        return True


def sax_cases(old, new, linked):
    randomizer = random.Random(0x1EE4204)
    address = linked['sax_core'][0]
    cases = 0
    for case in range(300 + len(SAX_FIXED)):
        if case < 300:
            pool = WELL_FORMED if case % 2 else XML
            text = b''.join(randomizer.choice(pool) for _ in range(randomizer.randrange(1, 12)))
            if case % 5 == 4 and text:
                index = randomizer.randrange(len(text))
                text = text[:index] + bytes([randomizer.randrange(1, 256)]) + text[index+1:]
            text = text[:0x300]
            chunks = sorted(randomizer.sample(range(1, len(text)), min(2, len(text) - 1))) if case % 3 else []
            results = [0] * randomizer.randrange(0, 6) + [3] if case % 11 == 10 else []
            tag_hook = 0 if case % 13 == 12 else TAG_HOOK
            cdata_hook = 0 if case % 17 == 16 else CDATA_HOOK
            failing_malloc = randomizer.randrange(1, 4) if case % 7 == 6 else 0
        else:
            text, failing_malloc = SAX_FIXED[case - 300]
            chunks, results, tag_hook, cdata_hook = [], [], TAG_HOOK, CDATA_HOOK
        outcomes = []
        for segments in (old, new):
            machine = SaxMachine(segments, case, list(results), failing_malloc)
            parser = [0] * 25
            parser[1], parser[2], parser[3], parser[5] = 0x1234, tag_hook, cdata_hook, BUFFER
            for i, value in enumerate(parser):
                machine.write(PARSER + 4 * i, value, 4)
            for i, value in enumerate(text + b'\0'):
                machine.write(BUFFER + i, value, 1)
            returns = []
            for low, high in zip([0] + chunks, chunks + [len(text)]):
                machine.reg[4:7] = [PARSER, BUFFER + low, high - low]
                machine.reg[29], machine.reg[31] = STACK, 0xFFFFFF00
                result = machine.run(address)[1]
                returns.append(result)
                if result:
                    break
            written = {a: v for a, v in machine.memory.items() if a < STACK - 0x200}
            outcomes.append((returns, machine.calls, written))
        assert outcomes[0] == outcomes[1], ('sax_core', case, text, outcomes[0][0], outcomes[1][0])
        cases += 1
    return cases


def region(segments, start, end):
    for address, data in segments:
        if address <= start and end <= address + len(data):
            return data[start-address:end-address]
    raise AssertionError('Range outside loaded image')


def escape_cases(old, new, linked):
    randomizer = random.Random(0x1EE3AE0)
    cases = 0
    for name in ('escape_size', 'escape', 'iks_escape'):
        address = linked[name][0]
        for case in range(200):
            text = bytes(randomizer.choice(SPECIAL + b'abz;= \x80\xff') for _ in range(randomizer.randrange(0, 40)))
            if case % 7 == 0:
                text = text.translate(None, SPECIAL)
            length = len(text)
            if name == 'escape_size':
                arguments = [SRC, length]
            elif name == 'escape':
                arguments = [DEST, SRC, length]
            else:
                stack = 0 if case == 3 else 0x1000
                source = 0 if case == 4 else SRC
                # EE registers hold 32-bit arguments sign-extended, so len == -1 is all ones.
                arguments = [stack, source, MASK if case % 2 else length]
            allocation = 0 if case == 5 else HEAP
            outcomes = []
            for segments in (old, new):
                machine = EscapeMachine(segments, arguments, case, allocation)
                for i, value in enumerate(text + b'\0'):
                    machine.write(SRC + i, value, 1)
                calls, result = machine.run(address)
                written = {a: v for a, v in machine.memory.items() if a < STACK - 0x200}
                outcomes.append((result, calls, written))
            assert outcomes[0] == outcomes[1], (name, case, text)
            cases += 1
    return cases


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('original')
    parser.add_argument('rebuilt')
    args = parser.parse_args()
    game = Path(__file__).resolve().parents[1]
    code = '#include <stddef.h>\n#include "iksemel.h"\n'
    checks = 0
    for name, size, offsets in LAYOUTS:
        code += 'typedef char size_%s[(sizeof(%s) == %d) ? 1 : -1];\n' % (name, name, size)
        for field, offset in offsets:
            code += 'typedef char check_%s_%s[(offsetof(%s, %s) == %d) ? 1 : -1];\n' % (
                name, field, name, field, offset)
        checks += 1 + len(offsets)
    compiler = Path(os.environ.get('PS2DEV_DIR', '/opt/ps2dev'))/'ee/bin/ee-gcc'
    with tempfile.TemporaryDirectory(prefix='ryno-iks-') as directory:
        source = Path(directory)/'layout.c'
        source.write_text(code)
        subprocess.run([str(compiler), '-c', '-I'+str(game/'code/iksemel/src'), str(source),
                        '-o', str(Path(directory)/'layout.o')], check=True)
    old = read_elf(args.original)[1]
    new = read_elf(args.rebuilt)[1]
    linked = symbols(args.rebuilt)
    manifest = yaml.safe_load((game/'config/decompiled_functions.yaml').read_text())
    compiled = exact = 0
    skipped = []
    for obj, bounds in manifest['objects'].items():
        if not obj.startswith('iksemel/'):
            continue
        for slot in bounds['slots']:
            name = slot['section'][len('.iks_'):]
            if name not in manifest['functions']:
                assert name not in NONMATCHING, name
                continue
            actual, size, info, section = linked[name]
            allocation = slot['end'] - slot['start']
            assert (actual, info & 15) == (slot['start'], 2), name
            assert section not in (0, 0xFFF1) and name+'.NON_MATCHING' not in linked, name
            if name in NONMATCHING:
                assert size <= allocation, name
                skipped.append((slot['start'], slot['end']))
            else:
                assert size == allocation, name
                exact += 1
            compiled += 1
    # Compare the whole library, including retained assembly, outside the nonmatching slots.
    start = LIBRARY[0]
    for low, high in sorted(skipped) + [(LIBRARY[1], LIBRARY[1])]:
        assert region(old, start, low) == region(new, start, low), 'iksemel bytes changed in %#x-%#x' % (start, low)
        start = high
    with (game/'DOCS/symbols/IKSEMEL_GLOBALS.csv').open() as inventory:
        names = 0
        for row in csv.DictReader(inventory):
            assert linked[row['name']][0] == int(row['address'], 16), row['name']
            names += 1
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
    escapes = escape_cases(old, new, linked)
    parses = sax_cases(old, new, linked)
    print('PASS: %d iksemel layout checks; library bytes exact outside %d nonmatching slots; '
          '%d compiled functions (%d exact); %d globals; %d accessor, %d escape and %d sax_core '
          'differential cases' % (checks, len(skipped), compiled, exact, names, cases, escapes, parses))


if __name__ == '__main__':
    main()
