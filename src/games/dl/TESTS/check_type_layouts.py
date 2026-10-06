#!/usr/bin/env python3
"""Compile recovered layouts with the EE compiler; no checks enter game code."""
import json
from pathlib import Path
import subprocess
import struct
import tempfile

ROOT = Path(__file__).resolve().parents[1]
EE = '/opt/ps2dev/ee/bin/ee-g++'

def main():
    types = json.loads((ROOT / 'DOCS/RECOVERED_TYPES.json').read_text())
    lines = ['#include <stddef.h>']
    for header in sorted({t['header'] for t in types}):
        lines += ['#include "' + header + '"', '#include "' + header + '"']
    checks = 0
    for t in types:
        name = t['name']
        lines.append('typedef char size_%s[(sizeof(%s) == %s) ? 1 : -1];' % (name, name, t['size']))
        checks += 1
        for f in t['fields']:
            if f['bitfield']:
                continue
            lines.append('typedef char offset_%s_%s[(offsetof(%s, %s) == %d) ? 1 : -1];' %
                         (name, f['name'], name, f['name'], f['offset']))
            checks += 1
    with tempfile.TemporaryDirectory(prefix='dl-types-') as tmp:
        source = Path(tmp) / 'layouts.cpp'
        source.write_text('\n'.join(lines) + '\n')
        subprocess.run([EE, '-std=c++98', '-fsyntax-only', '-I' + str(ROOT), str(source)], check=True)
        # Each header must work on its own, without accidental include ordering.
        for header in sorted({t['header'] for t in types}):
            source.write_text('#include "' + header + '"\n')
            subprocess.run([EE, '-std=c++98', '-fsyntax-only', '-I' + str(ROOT), str(source)], check=True)
        # Verify actual EE bit-field packing, not the host compiler's ABI.
        vectors = [[0] * 8]
        for i in range(8):
            vector = [0] * 8
            vector[i] = 1
            vectors.append(vector)
        vectors.append([1, 1, 1, 2047, 2047, 7, 0x1234, 0xABCD])
        source.write_text('#include "code/game/boot.h"\n'
                          'GameBootOptions probe[] __attribute__((section(".layout_probe"))) = {\n' +
                          ',\n'.join('{' + ','.join(map(str, v)) + '}' for v in vectors) + '\n};\n')
        obj = Path(tmp) / 'probe.o'
        binary = Path(tmp) / 'probe.bin'
        subprocess.run([EE, '-c', '-I' + str(ROOT), str(source), '-o', str(obj)], check=True)
        subprocess.run(['/opt/ps2dev/ee/bin/ee-objcopy', '-O', 'binary', '-j', '.layout_probe',
                        str(obj), str(binary)], check=True)
        expected = b''.join(struct.pack('<IHH', v[0] | v[1] << 1 | v[2] << 2 | v[3] << 3 |
                                        v[4] << 14 | v[5] << 25, v[6], v[7]) for v in vectors)
        assert binary.read_bytes() == expected, 'GameBootOptions EE bit-field packing differs'
    print('PASS: independent header includes and 10 EE boot-option packing vectors')
    print('PASS: %d PS2 sizes/field offsets across %d types and %d headers' %
          (checks, len(types), len({t['header'] for t in types})))

if __name__ == '__main__':
    main()
