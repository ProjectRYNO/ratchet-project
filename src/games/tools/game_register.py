#!/usr/bin/env python3
"""game_register.py NAME... : convert code/game/NAME.cpp to per-function slots. Run in the container from /ProjectRYNO/dl.

Adds game_section.h, registers one manifest slot per INCLUDE_ASM entry and adds the object to the
Makefile's SN object list. Addresses come from the split asm in /tmp/ckroot.
"""
import glob, re, sys, yaml
root = '/ProjectRYNO/dl/'
OFFSET = 0x100080

def segments():
	out = []
	for line in open(root + 'config/SCUS_974.65.yaml'):
		m = re.match(r'\s+- \[(0x[0-9A-Fa-f]+),\s*(\w+)(?:,\s*([\w/.]+))?\]', line)
		if m:
			out.append((int(m[1], 16), m[3]))
	return out

segs = segments()
manifest_text = open(root + 'config/decompiled_functions.yaml', newline='').read().replace('\r\n', '\n')
for name in sys.argv[1:]:
	obj = 'game/' + name
	if '\n  %s:\n' % obj in manifest_text:
		continue
	path = root + 'code/game/%s.cpp' % name
	src = open(path, newline='').read()
	nl = '\r\n' if '\r\n' in src else '\n'
	names = re.findall(r'INCLUDE_ASM\("[^"]*", (\w+)\);', src)
	addrs = []
	for n in names:
		t = open('/tmp/ckroot/dl/code/asm/nonmatchings/game/%s/%s.s' % (name, n)).read()
		addrs.append(int(re.search(r'/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/', t)[1], 16))
	i = [k for k, s in enumerate(segs) if s[1] == obj][0]
	end = segs[i + 1][0] + OFFSET
	assert addrs == sorted(addrs), name
	assert addrs[0] == segs[i][0] + OFFSET, (name, hex(addrs[0]), hex(segs[i][0] + OFFSET))
	if '#include "game_section.h"' not in src:
		src = src.replace('#include "common.h"' + nl, '#include "common.h"' + nl + '#include "game_section.h"' + nl, 1)
		open(path, 'w', newline='').write(src)
	y = root + 'config/decompiled_functions.yaml'
	u = open(y, newline='').read()
	ynl = '\r\n' if '\r\n' in u else '\n'
	block = ['  %s:' % obj, '    text_start: 0x%08X' % addrs[0], '    text_end: 0x%08X' % end, '    slots:']
	for n, a, b in zip(names, addrs, addrs[1:] + [end]):
		block.append('      - {object: %s, section: .game_%s, start: 0x%08X, end: 0x%08X}' % (obj, n, a, b))
	k = '  sdk/mrpc/libmrpc:' + ynl
	assert k in u
	u = u.replace(k, ynl.join(block) + ynl + k, 1)
	open(y, 'w', newline='').write(u)
	m = root + 'Makefile'
	v = open(m, newline='').read()
	vnl = '\r\n' if '\r\n' in v else '\n'
	k = 'GAME_SN_NAMES ='
	line = [l for l in v.split(vnl) if l.startswith(k)][0]
	if (' ' + name + ' ') not in line + ' ':
		v = v.replace(line, line + ' ' + name, 1)
		open(m, 'w', newline='').write(v)
	print(obj, len(names), 'slots', hex(addrs[0]), hex(end))
