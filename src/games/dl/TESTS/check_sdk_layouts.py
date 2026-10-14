#!/usr/bin/env python3
"""Check recovered SDK layout with the SCE 2.96 compiler used by production."""
import argparse
import json
import os
from pathlib import Path
import subprocess
import tempfile


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--compiler-root', default='/opt/ee-gcc2.96')
    args = ap.parse_args()
    root = Path(__file__).resolve().parents[1]
    records = json.loads((root / 'DOCS/types/RECOVERED_TYPES.json').read_text())
    records = [t for t in records if t['header'].startswith('code/sdk/')]
    lines = ['#include "code/sdk/i18n.h"', '#include "code/sdk/i18n.h"',
             '#include "code/sdk/eznet_rpc.h"', '#include "code/sdk/eznet_rpc.h"',
             '#define OFFSET(T, M) ((unsigned int)&(((T *)0)->M))',
             'typedef char pointer_size[(sizeof(void *) == 4) ? 1 : -1];']
    for t in records:
        lines.append('typedef char size_%s[sizeof(%s) == %s ? 1 : -1];' % (t['name'], t['name'], t['size']))
        for f in t['fields']:
            lines.append('typedef char offset_%s_%s[OFFSET(%s, %s) == %d ? 1 : -1];' %
                         (t['name'], f['name'], t['name'], f['name'], f['offset']))
    for field, offset in [('common.phase', 0), ('common.detail', 4), ('common.data', 8),
                          ('ppp.phone', 12), ('ppp.message', 268), ('ppp.speed', 348), ('ppp.auth', 380)]:
        lines.append('typedef char nested_%s[OFFSET(EzNetCtlInfo, %s) == %d ? 1 : -1];' %
                     (field.replace('.', '_'), field, offset))
    env = dict(os.environ, LD_PRELOAD=args.compiler_root + '/ee296_statshim.so')
    with tempfile.TemporaryDirectory(prefix='sdk-layouts-') as tmp:
        source = Path(tmp) / 'layouts.c'
        source.write_text('\n'.join(lines) + '\n')
        subprocess.run([args.compiler_root + '/bin/ee-gcc', '-fno-builtin', '-fsyntax-only',
                        '-I' + str(root), str(source)], env=env, check=True)
    print('PASS: SCE 2.96 SDK pointer width, three type sizes, and all declared/nested field offsets')


if __name__ == '__main__':
    main()
