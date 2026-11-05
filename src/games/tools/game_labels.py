#!/usr/bin/env python3
"""game_labels.py NAME... : give every GAME_SECTION free function its flat symbol name.

A definition without a `__asm__("name")` declaration compiles under its mangled C++ name, which
assembly callers and the manifest's address checks cannot see. This adds the missing declaration
just before the definition. Member functions need theirs in the class, so they are only reported.
"""
import re
import sys

ROOT = '/ProjectRYNO/dl/code/game/'
DEF = re.compile(r'^GAME_SECTION\((\w+)\)\s+([^\n{]*?)\s*\n?\{', re.M)


def fix(name):
    path = ROOT + name + '.cpp'
    raw = open(path, newline='').read()
    crlf = '\r\n' in raw
    text = raw.replace('\r\n', '\n')
    added = []
    for m in reversed(list(DEF.finditer(text))):
        fn, signature = m[1], m[2]
        if '__asm__("%s")' % fn in text:
            continue
        if '::' in signature:
            print('%s: member function %s has no label' % (name, fn))
            continue
        text = text[:m.start()] + '%s __asm__("%s");\n' % (signature, fn) + text[m.start():]
        added.append(fn)
    if added:
        open(path, 'w', newline='').write(text.replace('\n', '\r\n') if crlf else text)
        print('%s: added %s' % (name, ' '.join(reversed(added))))


for arg in sys.argv[1:]:
    fix(arg)
