#!/usr/bin/env python3
"""game_test.py SRC.cpp [--show FUNC] : compile a game test file and compare each .game_<fn> section with retail.

Run in the container from anywhere. Uses a private temp dir, so parallel runs are safe. Relocated
fields are masked, so global addresses are only proven by the full checkpoint. Retail asm is read
from /tmp/ckroot, or GASM=<dl tree> to use a private copy. A manifest slot that covers several split functions
(a merged group of hand-written functions) is compared against their concatenated retail words, gaps as nop.
"""
import glob, os, re, subprocess, sys, tempfile

W = '/opt/wibo-1.2.0'
FLAGS = os.environ.get('GAME_FLAGS', '-G8 -O2 -g -fopt-stack -mno-check-zero-division -fno-exceptions -mvu0-use-vf0-vf31')
AS = os.environ.get('GAME_AS', '/opt/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/Ps2EeAs.exe')
AS_FLAGS = os.environ.get('GAME_AS_FLAGS', '-G8')
ROOT = os.environ.get('GASM', '/tmp/ckroot/dl')
TOOLS = '/ProjectRYNO/tools'
INC = '-I/ProjectRYNO/dl/code/include -I/ProjectRYNO/dl/code/game -I/ProjectRYNO/dl/code'

def sh(cmd):
	return subprocess.run(cmd, shell=True, capture_output=True, text=True)

def retail(fn):
	one = retail_one(fn)
	if one is None:
		return None
	slot = merged_slot(fn)
	if slot is None:
		return one
	start, end, members = slot
	words = []
	pos = start
	for addr, name in members:
		w, _ = retail_one(name)
		while pos < addr:
			words.append((0, '(gap) nop'))
			pos += 4
		words += w
		pos += len(w) * 4
	return words, one[1]

_slots = None

def merged_slot(fn):
	global _slots
	if _slots is None:
		_slots = {}
		text = open(ROOT + '/config/decompiled_functions.yaml').read()
		for m in re.finditer(r'object: (game/[\w/]+), section: \.game_(\w+), start: (0x[0-9A-Fa-f]+), end: (0x[0-9A-Fa-f]+)', text):
			_slots[m[2]] = (m[1], int(m[3], 16), int(m[4], 16))
	if fn not in _slots:
		return None
	obj, start, end = _slots[fn]
	members = []
	for p in glob.glob(ROOT + '/code/asm/nonmatchings/' + obj + '/*.s'):
		m = re.search(r'/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/', open(p).read())
		if m and start <= int(m[1], 16) < end:
			members.append((int(m[1], 16), os.path.basename(p)[:-2]))
	if len(members) < 2:
		return None
	return start, end, sorted(members)

def retail_one(fn):
	paths = glob.glob(ROOT + '/code/asm/nonmatchings/game/**/%s.s' % fn, recursive=True) or glob.glob(ROOT + '/code/asm/matchings/game/**/%s.s' % fn, recursive=True)
	if not paths:
		return None
	text = open(paths[0]).read()
	head = text.split('endlabel')[0]
	words = []
	# splat writes VU0 macro instructions it cannot disassemble (vmula*, vmsub*, ...) as `.byte`
	# lines; keep them in order so the compare stays aligned.
	for m in re.finditer(r'/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s*(.*)|^\s*\.byte\s+(0x[0-9A-Fa-f]+(?:\s*,\s*0x[0-9A-Fa-f]+){3})\s*$', head, re.M):
		if m[1]:
			w = m[1]
			words.append((int(w[6:8] + w[4:6] + w[2:4] + w[:2], 16), m[2].strip()))
		else:
			b = [int(x, 16) for x in m[3].split(',')]
			words.append((b[0] | b[1] << 8 | b[2] << 16 | b[3] << 24, '.byte (VU0 op)'))
	return words, paths[0]

def main():
	src = os.path.abspath(sys.argv[1])
	show = sys.argv[sys.argv.index('--show') + 1] if '--show' in sys.argv else None
	d = tempfile.mkdtemp(prefix='gt')
	extra = re.findall(r'^// GAME_EXTRA_FLAGS: (.*)$', open(src, errors='replace').read(), re.M)
	r = sh('cd /ProjectRYNO/dl && %s /opt/ee-gcc2.95.3-136/bin/ee-gcc.exe -x c++ -S %s %s -DGTEST %s %s -o %s/a.s' % (W, FLAGS, ' '.join(x.strip() for x in extra), INC, src, d))
	if r.returncode:
		print(r.stderr[-1800:])
		return 1
	sh('python3 %s/svo3_rodata_sections.py %s/a.s' % (TOOLS, d))
	if os.environ.get('GAME_LOOP', '1') == '1':
		sh('python3 %s/sound_loop_compat.py --likely %s/a.s %s/b.s' % (TOOLS, d, d))
	else:
		sh('cp %s/a.s %s/b.s' % (d, d))
	run = W if AS.endswith('.exe') else 'LD_PRELOAD=/opt/ee-gcc2.96/ee296_statshim.so'
	r = sh('cd /ProjectRYNO/dl && %s %s %s -I/ProjectRYNO/dl/code/include -o %s/a.o %s/b.s' % (run, AS, AS_FLAGS, d, d))
	if r.returncode:
		print(r.stderr[-1200:])
		return 1
	obj = d + '/a.o'
	secs = re.findall(r'^\s*\d+ (\.game_\S+)\s+([0-9a-f]+)', sh('mips-linux-gnu-objdump -h ' + obj).stdout, re.M)
	exact = total = 0
	for sec, size in secs:
		if sec.endswith('.rodata') or int(size, 16) == 0:
			continue
		fn = sec[6:]
		ret = retail(fn)
		if ret is None:
			print('%s: no retail asm' % fn)
			continue
		tgt, path = ret
		sh('mips-linux-gnu-objcopy -O binary -j %s %s %s/o.bin' % (sec, obj, d))
		data = open(d + '/o.bin', 'rb').read()
		ours = [int.from_bytes(data[i:i + 4], 'little') for i in range(0, len(data), 4)]
		masks = {}
		for line in sh('mips-linux-gnu-objdump -r -j %s %s' % (sec, obj)).stdout.splitlines():
			m = re.match(r'([0-9a-f]{8}) (R_MIPS_\w+)', line)
			if m:
				masks[int(m[1], 16) // 4] = 0xfc000000 if m[2] == 'R_MIPS_26' else 0xffff0000
		while len(ours) > len(tgt) and ours[-1] == 0:
			ours.pop()
		diff = [i for i in range(min(len(ours), len(tgt))) if (ours[i] & masks.get(i, 0xffffffff)) != (tgt[i][0] & masks.get(i, 0xffffffff))]
		total += 1
		if not diff and len(ours) == len(tgt):
			exact += 1
			print('%s: size 0x%X EXACT' % (fn, len(tgt) * 4))
		else:
			print('%s: size 0x%X/0x%X, %d words differ at %s' % (fn, len(ours) * 4, len(tgt) * 4, len(diff) + abs(len(ours) - len(tgt)), ' '.join(hex(i * 4) for i in diff[:12])))
		if show == fn:
			dis = sh('mips-linux-gnu-objdump -d -z -M gpr-names=numeric -j %s %s' % (sec, obj)).stdout
			mine = [re.sub(r'\s+', ' ', x.split('\t', 2)[-1]).split(' <')[0] for x in dis.splitlines() if re.match(r'\s+[0-9a-f]+:\t', x)]
			for i in range(max(len(mine), len(tgt))):
				a = tgt[i][1][:42] if i < len(tgt) else ''
				b = mine[i][:42] if i < len(mine) else ''
				print('%s%04x %-42s | %s' % ('*' if i in diff else ' ', i * 4, a, b))
	print('%d/%d exact' % (exact, total))
	sh('rm -rf ' + d)

main()
