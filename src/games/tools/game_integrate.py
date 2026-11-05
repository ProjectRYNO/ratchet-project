#!/usr/bin/env python3
"""game_integrate.py LIST : move verified game functions from test files into code/game/<obj>.cpp.

LIST holds lines of `TESTFILE FUNC`. Run in the container from /ProjectRYNO/dl. For each object it
keeps only the declarations the chosen bodies need, replaces each INCLUDE_ASM entry and registers the
function in the manifest. Register the object's slots first with game_register.py.
"""
import collections
import glob
import re
import sys

ROOT = '/ProjectRYNO/dl/'
WORK = ROOT + 'build/game-work/'
ASM = '/tmp/ckroot/dl/code/asm/nonmatchings/game/'
KEYWORDS = set('''void int char short long float double unsigned signed const volatile extern static inline struct
union enum typedef bool return if else for while do switch case default break continue sizeof class public private
register __asm__ __attribute__ section true false goto'''.split())


def chunks(text):
    """Split a test file into top-level declarations, keeping each one's leading comments."""
    out = []
    i = 0
    start = 0
    depth = 0
    n = len(text)
    while i < n:
        if text.startswith('//', i):
            i = text.index('\n', i) + 1
            continue
        if text.startswith('/*', i):
            i = text.index('*/', i) + 2
            continue
        c = text[i]
        if c == '"':
            i += 1
            while text[i] != '"':
                i += 2 if text[i] == '\\' else 1
            i += 1
            continue
        if c == '#' and depth == 0 and text[start:i].strip(' \t\r\n') == '':
            j = i
            while True:
                j = text.index('\n', j)
                if text[j - 1] != '\\':
                    break
                j += 1
            out.append(text[start:j + 1])
            i = start = j + 1
            continue
        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0:
                head = re.sub(r'/\*.*?\*/|//[^\n]*', '', text[start:i], flags=re.S).lstrip()
                aggregate = re.match(r'(typedef|struct|union|enum|class)\b', head) and '(' not in head.split('{')[0]
                if not aggregate and '=' not in head.split('{')[0] and not head.startswith('extern "C"'):
                    out.append(text[start:i + 1] + '\n')
                    i += 1
                    while i < n and text[i] in ' \t\r\n':
                        i += 1
                    start = i
                    continue
        elif c == ';' and depth == 0:
            out.append(text[start:i + 1] + '\n')
            i += 1
            while i < n and text[i] in ' \t\r\n':
                i += 1
            start = i
            continue
        i += 1
    return out


def strip(code):
    return re.sub(r'/\*.*?\*/|//[^\n]*|"[^"]*"', ' ', code, flags=re.S)


def declared(chunk):
    labels = re.findall(r'__asm__\s*\(\s*"(\w+)"', chunk)
    if labels and not re.search(r'^\s*(?:typedef\s+)?(?:struct|union|enum|class)\b', strip(chunk)):
        return {'label:' + label for label in labels}
    code = strip(chunk).strip()
    names = set()
    if code.startswith('extern "C"') or code.startswith('extern  {'):
        return set(re.findall(r'(\w+)\s*\(', code))
    if code.startswith('#define'):
        m = re.match(r'#define\s+(\w+)', code)
        return {m[1]} if m else set()
    m = re.match(r'(?:typedef\s+)?(?:struct|union|enum|class)\s+(\w+)', code)
    if m:
        names.add(m[1])
    if code.startswith('typedef'):
        m = re.search(r'(\w+)\s*(?:__attribute__\s*\(\(.*\)\)\s*)?;\s*$', code, re.S)
        if m:
            names.add(m[1])
    if not re.match(r'(typedef|struct|union|enum|class)\b', code) or '{' not in code.split('(')[0]:
        m = re.match(r'[^(\[=;{]*?(\w+)\s*(?:__asm__|[(\[=;{])', code, re.S)
        if m:
            names.add(m[1])
    return names


def main():
    want = collections.defaultdict(list)
    for line in open(sys.argv[1]):
        f, fn = line.split()[:2]
        want[fn].append(f)
    by_obj = collections.defaultdict(lambda: collections.defaultdict(list))
    for fn, files in want.items():
        paths = glob.glob(ASM + '*/%s.s' % fn)
        if not paths:
            print('no root object for', fn)
            continue
        obj = paths[0].split('/')[-2]
        by_obj[obj][fn] = files
    y = ROOT + 'config/decompiled_functions.yaml'
    manifest = open(y, newline='').read()
    ynl = '\r\n' if '\r\n' in manifest else '\n'
    head, rest = manifest.split('objects:', 1)
    anchor = [l for l in head.split(ynl) if l.startswith('  sceGsSyncPath: ')][0] + ynl
    for obj, fns in sorted(by_obj.items()):
        # Prefer a plain test file; variants named *_b, *_t or *_best only when nothing else has it.
        def rank(f):
            return (bool(re.search(r'_(b|t|best)\.cpp$', f)), f)
        counts = collections.Counter(f for files in fns.values() for f in files)
        src = ROOT + 'code/game/%s.cpp' % obj
        text = open(src, newline='').read()
        crlf = '\r\n' in text
        text = text.replace('\r\n', '\n')
        kept = []
        placed = []
        seen_aggregates = {}
        existing = set()
        for c in chunks(text):
            existing |= declared(c)
        for fn, files in fns.items():
            f = sorted(files, key=lambda x: (rank(x)[0], -counts[x], x))[0]
            all_chunks = chunks(open(WORK + f).read().replace('\r\n', '\n'))
            body = [c for c in all_chunks if re.search(r'GAME_SECTION\(%s\)' % re.escape(fn), strip(c)) and '{' in strip(c)]
            if not body:
                print('no body', fn, f)
                continue
            line = 'INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/%s", %s);' % (obj, fn)
            if line in text:
                text = text.replace(line, body[0].rstrip('\n'), 1)
                placed.append(fn)
            elif not re.search(r'GAME_SECTION\(%s\)' % re.escape(fn), text):
                print('no entry', fn, obj)
                continue
            # Every declaration in the test file, skipping names the object already has.
            for c in all_chunks:
                if 'GAME_SECTION' in strip(c) or strip(c).strip().startswith('#include') or '#define KERNEL' in c:
                    continue
                names = declared(c)
                tag = re.match(r'\s*(?:typedef\s+)?(?:struct|union|class)\s+(\w+)\s*\{', strip(c))
                if tag and tag[1] in existing and c not in text:
                    # A test file's newer view of a struct replaces the old one; game_verify.sh checks it.
                    pattern = r'^(?:typedef\s+)?(?:struct|union|class)\s+%s\s*\{.*?^\}[^;\n]*;\n' % re.escape(tag[1])
                    new = c if c.endswith('\n') else c + '\n'
                    new = re.sub(r'^(?:/\*[^\n]*\*/\n)+', '', new)
                    text = re.sub(pattern, lambda m: new, text, count=1, flags=re.S | re.M)
                    continue
                if 'GAME_GP_DATA' in c and names <= existing:
                    # The function needs $gp access, so its definition replaces a plain extern.
                    for label in (n.split(':', 1)[1] for n in names if n.startswith('label:')):
                        text = re.sub(r'^extern [^;\n]*__asm__\("%s"\);\n' % re.escape(label), '', text, flags=re.M)
                        if c not in kept and 'GAME_GP_DATA' not in re.sub(r'^(?!.*__asm__\("%s"\)).*$' % re.escape(label), '', text, flags=re.M):
                            kept.append(c)
                    continue
                if (names and names <= existing) or c in kept:
                    continue
                kept.append(c)
                existing |= names
        k = '#include "game_section.h"\n'
        if k not in text:
            print('not registered, skipped', obj)
            continue
        at = text.index(k) + len(k)
        first = re.search(r'^(GAME_SECTION\(|INCLUDE_ASM\()', text[at:], re.M)
        at += first.start() if first else 0
        text = text[:at] + ''.join(c if c.endswith('\n') else c + '\n' for c in kept) + '\n' + text[at:]
        open(src, 'w', newline='').write(text.replace('\n', '\r\n') if crlf else text)
        print(obj, len(placed), ' '.join(placed))
    # Rebuilt from the sources, so a rerun after a failure registers everything already placed.
    slots = dict(re.findall(r'section: \.game_(\w+), start: (0x[0-9A-F]+)', rest))
    for path in sorted(glob.glob(ROOT + 'code/game/*.cpp')):
        for fn in re.findall(r'^GAME_SECTION\((\w+)\)', open(path, errors='replace').read(), re.M):
            if '  %s: ' % fn not in head and fn in slots:
                head = head.replace(anchor, anchor + '  %s: %s%s' % (fn, slots[fn], ynl), 1)
    open(y, 'w', newline='').write(head + 'objects:' + rest)


if __name__ == '__main__':
    main()
