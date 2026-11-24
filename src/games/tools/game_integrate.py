#!/usr/bin/env python3
"""game_integrate.py LIST : move verified game functions from test files into code/game/<obj>.cpp.

LIST holds lines of `TESTFILE FUNC`. Run in the container from /ProjectRYNO/dl. For each object it
keeps only the declarations the chosen bodies need, replaces each INCLUDE_ASM entry and registers the
function in the manifest. Register the object's slots first with game_register.py.
"""
import collections
import glob
import os
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
                block = re.match(r'extern\s+"C"\s*\{', head)
                if block or (not aggregate and '=' not in head.split('{')[0] and not head.startswith('extern "C"')):
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
        # The C name counts too: an alias of an already-declared label under a new name is still needed.
        names = {'label:' + label for label in labels}
        m = re.match(r'[^(\[=;{]*?(\w+)\s*(?:__asm__|[(\[=;{])', strip(chunk).strip(), re.S)
        if m and m[1] not in KEYWORDS:
            names.add(m[1])
        # So does a function's parameter list: an overload under an existing label must be kept, or its
        # definition is emitted under a mangled name.
        params = re.search(r'\(([^()]*)\)\s*__asm__', strip(chunk))
        if params:
            names.add('params:%s:%s' % (labels[0], re.sub(r'\s+', ' ', params[1]).strip()))
        return names
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
        # A function-pointer typedef names its type inside the parentheses: typedef void (*fn)();
        m = re.match(r'typedef[^(;{]*\(\s*\*\s*(\w+)\s*\)', code) or \
            re.search(r'(\w+)\s*(?:__attribute__\s*\(\(.*\)\)\s*)?;\s*$', code, re.S)
        if m:
            names.add(m[1])
            if '{' not in code:
                return names
    if not re.match(r'(typedef|struct|union|enum|class)\b', code) or '{' not in code.split('(')[0]:
        m = re.match(r'[^(\[=;{]*?(\w+)\s*(?:__asm__|[(\[=;{])', code, re.S)
        if m:
            names.add(m[1])
    return names


def header_names(text, base, seen):
    """Names declared by the code/game (and code/include) headers TEXT includes, followed transitively."""
    names = set()
    for inc in re.findall(r'^\s*#include\s+"([^"]+)"', text, re.M):
        for d in (base, ROOT + 'code/game/', ROOT + 'code/include/'):
            path = os.path.normpath(os.path.join(d, inc))
            if os.path.exists(path):
                break
        else:
            continue
        if path in seen or not path.endswith('.h'):
            continue
        seen.add(path)
        h = open(path, errors='replace').read().replace('\r\n', '\n')
        for c in chunks(h):
            names |= declared(c)
        names |= header_names(h, os.path.dirname(path) + '/', seen)
    return names


FILLER = re.compile(r'(unk|pad|spad|unused)[0-9a-fA-F_]*$')


def struct_fields(chunk):
    """Named fields of a struct chunk: {name: (offset or None, declaration)}; fillers are ignored."""
    body = strip(chunk)
    if '{' not in body:
        return {}
    body = chunk[chunk.index('{') + 1:chunk.rindex('}')]
    fields = {}
    for line in body.split('\n'):
        m = re.match(r'\s*(?:/\*\s*(0x[0-9a-fA-F]+)\s*\*/)?\s*([^;()]+?)\s*;\s*(?://.*)?$', line)
        if not m:
            continue
        decl = re.sub(r'\s+', ' ', m[2]).strip()
        name = re.search(r'(\w+)\s*(?:\[[^\]]*\])*\s*$', decl)
        if not name or FILLER.match(name[1]):
            continue
        fields[name[1]] = (int(m[1], 16) if m[1] else None, decl)
    return fields


def extern_types(text):
    """{asm label: declared type text} for extern variable declarations in TEXT."""
    out = {}
    for m in re.finditer(r'^\s*extern\s+(?!"C")([^;()]*?)\b(\w+)\s*((?:\[[^\]]*\])*)\s*__asm__\s*\(\s*"(\w+)"\s*\)\s*;', strip_comments(text), re.M):
        out[m[4]] = (re.sub(r'\s+', '', m[1] + m[3]), m[2])
    return out


def strip_comments(code):
    return re.sub(r'/\*.*?\*/|//[^\n]*', ' ', code, flags=re.S)


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
        includes = []
        placed = []
        seen_aggregates = {}
        existing = set()
        for c in chunks(text):
            existing |= declared(c)
        # Declarations the object already gets from its headers are never copied from a test file.
        seen_headers = set()
        from_headers = header_names(text, ROOT + 'code/game/', seen_headers)
        target_externs = extern_types(text)
        for path in seen_headers:
            for label, decl in extern_types(open(path, errors='replace').read()).items():
                target_externs.setdefault(label, decl)
        target_includes = set(re.findall(r'^#include\s+"([^"]+)"', text, re.M))
        for fn, files in fns.items():
            f = sorted(files, key=lambda x: (rank(x)[0], -counts[x], x))[0]
            test_text = open(WORK + f).read().replace('\r\n', '\n')
            missing = sorted(target_includes - set(re.findall(r'^#include\s+"([^"]+)"', test_text, re.M)))
            if missing:
                print('WARN %s: stale base for %s? it lacks %s that %s.cpp includes; only the function body is trusted'
                      % (f, fn, ', '.join(missing), obj))
            all_chunks = chunks(test_text)
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
                if strip(c).strip().startswith('#include'):
                    # Headers a test file adds (such as game_vu0.h) go after game_section.h below.
                    for inc in re.findall(r'^#include\s+"[^"]+"', c, re.M):
                        if inc not in includes:
                            includes.append(inc)
                    from_headers |= header_names(c, ROOT + 'code/game/', seen_headers)
                    continue
                if 'GAME_SECTION' in strip(c) or '#define KERNEL' in c:
                    continue
                if re.search(r'=====\s*A', c):
                    # Worker section markers never reach the module; the declaration after one still can.
                    print('WARN %s: dropped a worker marker: %s' % (f, re.search(r'[^\n]*=====\s*A[^\n]*', c).group(0).strip()[:80]))
                    c = re.sub(r'^[^\n]*=====\s*A[^\n]*\n?', '', c, flags=re.M)
                    if not strip(c).strip():
                        continue
                ext = extern_types(c)
                # The same variable under the same name with another type is an old view: skip it.
                # (A differently named view of the same label can be a deliberate matching view.)
                stale = [l for l, d in ext.items() if l in target_externs and target_externs[l][0] != d[0]]
                if stale:
                    l = stale[0]
                    if target_externs[l][1] == ext[l][1]:
                        print('WARN STALE %s: %s is already `%s %s`; skipped the `%s` view'
                              % (f, l, target_externs[l][0], target_externs[l][1], ext[l][0]))
                        continue
                    print('WARN %s: second view `%s %s` of %s (the object has `%s %s`); check it is needed'
                          % (f, ext[l][0], ext[l][1], l, target_externs[l][0], target_externs[l][1]))
                if re.match(r'\s*extern\s+"C"\s*\{', strip(c)):
                    # Keep only the C declarations the object does not already have (here or in a header).
                    inner = c[c.index('{') + 1:c.rindex('}')]
                    lines = [l for l in inner.split('\n') if l.strip() and not (
                        re.search(r'(\w+)\s*\(', strip(l)) and re.search(r'(\w+)\s*\(', strip(l))[1] in existing | from_headers)]
                    if not any(re.search(r'\w+\s*\(', strip(l)) for l in lines):
                        continue
                    c = 'extern "C" {\n' + '\n'.join(lines) + '\n}\n'
                names = declared(c)
                core = {n for n in names if not n.startswith('params:')}
                if core and core <= from_headers | existing and core & from_headers:
                    continue
                tag = re.match(r'\s*(?:typedef\s+)?(?:struct|union|class)\s+(\w+)\s*\{', strip(c))
                if tag and tag[1] in existing and c not in text:
                    # A test file's newer view of a struct replaces the old one; game_verify.sh checks it.
                    pattern = r'^(?:typedef\s+)?(?:struct|union|class)\s+%s\s*\{.*?^\}[^;\n]*;\n' % re.escape(tag[1])
                    old = re.search(pattern, text, re.S | re.M)
                    if old:
                        # Only a superset: every named field of the current definition must survive, at
                        # the same offset and with the same declaration (and so the same size).
                        mine, theirs = struct_fields(old.group(0)), struct_fields(c)
                        lost = [n for n, v in mine.items() if theirs.get(n) != v]
                        if lost:
                            print('WARN %s: kept %s.cpp\'s %s; the test file\'s version drops or changes %s'
                                  % (f, obj, tag[1], ', '.join(lost[:6])))
                            continue
                    new = c if c.endswith('\n') else c + '\n'
                    new = re.sub(r'^(?:/\*[^\n]*\*/\n)+', '', new)
                    text, n = re.subn(pattern, lambda m: new, text, count=1, flags=re.S | re.M)
                    if not n:
                        # Only a forward declaration exists: the test file's definition replaces it.
                        text = re.sub(r'^(?:struct|union|class)\s+%s\s*;\n' % re.escape(tag[1]), lambda m: new, text, count=1, flags=re.M)
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
        # A copied type that nothing uses any more (an old view of data the object now declares with
        # another type) is stale: leave it out.
        changed = True
        while changed:
            changed = False
            for c in list(kept):
                agg = re.match(r'\s*(?:typedef\s+)?(?:struct|union|class)\s+(\w+)?\s*\{', strip(c))
                if not agg:
                    continue
                names = {n for n in declared(c) if not n.startswith(('label:', 'params:'))}
                others = strip(text) + ''.join(strip(o) for o in kept if o is not c)
                if names and not any(re.search(r'\b%s\b' % re.escape(n), others) for n in names):
                    print('WARN STALE %s: dropped unused type %s' % (obj, ', '.join(sorted(names))))
                    kept.remove(c)
                    changed = True
        k = '#include "game_section.h"\n'
        if k not in text:
            print('not registered, skipped', obj)
            continue
        at = text.index(k) + len(k)
        new_includes = ''.join(inc + '\n' for inc in includes if inc not in text)
        text = text[:at] + new_includes + text[at:]
        at += len(new_includes)
        # Forward declarations go first: a struct replaced in place above the insertion point may
        # use a type the test file only forward-declares.
        forward = [c for c in kept if re.match(r'\s*(?:struct|union|class)\s+\w+\s*;\s*$', strip(c))]
        kept = [c for c in kept if c not in forward]
        text = text[:at] + ''.join(c if c.endswith('\n') else c + '\n' for c in forward) + text[at:]
        at += sum(len(c if c.endswith('\n') else c + '\n') for c in forward)
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
