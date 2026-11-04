#!/usr/bin/env python3
"""game_test.py SRC.cpp [--show FUNC] : compile a game test file and compare each .game_<fn> section with retail.

Run in the container from anywhere. Uses a private temp dir, so parallel runs are safe. Relocated
fields are masked, so global addresses are only proven by the full checkpoint. Retail asm is read
from /tmp/ckroot, or GASM=<dl tree> to use a private copy.
"""
import glob, os, re, subprocess, sys, tempfile

W = '/opt/wibo-1.2.0'
FLAGS = '-G8 -O2 -fopt-stack -mno-check-zero-division -fno-exceptions'
ROOT = os.environ.get('GASM', '/tmp/ckroot/dl')
TOOLS = '/ProjectRYNO/tools'
INC = '-I/ProjectRYNO/dl/code/include -I/ProjectRYNO/dl/code/game -I/ProjectRYNO/dl/code'

def sh(cmd):
	return subprocess.run(cmd, shell=True, capture_output=True, text=True)

def retail(fn):
	paths = glob.glob(ROOT + '/code/asm/nonmatchings/game/**/%s.s' % fn, recursive=True)
	if not paths:
		return None
	text = open(paths[0]).read()
	head = text.split('endlabel')[0]
	lines = re.findall(r'/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s*(.*)', head)
	return [(int(w[6:8] + w[4:6] + w[2:4] + w[:2], 16), a.strip()) for w, a in lines], paths[0]

def main():
	src = os.path.abspath(sys.argv[1])
	show = sys.argv[sys.argv.index('--show') + 1] if '--show' in sys.argv else None
	d = tempfile.mkdtemp(prefix='gt')
	r = sh('cd /ProjectRYNO/dl && %s /opt/ee-gcc2.95.3-136/bin/ee-gcc.exe -x c++ -S %s -DGTEST %s %s -o %s/a.s' % (W, FLAGS, INC, src, d))
	if r.returncode:
		print(r.stderr[-1800:])
		return 1
	sh('python3 %s/svo3_rodata_sections.py %s/a.s' % (TOOLS, d))
	sh('python3 %s/sound_loop_compat.py --likely %s/a.s %s/b.s' % (TOOLS, d, d))
	r = sh('cd /ProjectRYNO/dl && %s /opt/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe -EL -G8 -g -I/ProjectRYNO/dl/code/include %s/b.s -o %s/a.o' % (W, d, d))
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
