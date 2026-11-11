#!/usr/bin/env python3
"""Turn the extracted .vutext segment into VU assembly that dvp-as rebuilds byte for byte.

usage: vu_split.py IN.bin OUT.vsm [--base 0x100080] [--dvp /opt/ps2dev/dvp/bin]

.vutext holds DMA chains for VIF: DMA tags and VIF codes (framing) around MPG uploads (microcode).
Framing becomes commented .word data. Each microprogram, a run of MPG uploads to consecutive micro
addresses as Ghidra's "PS2 VU Microcode" analyzer groups them, becomes VU instructions under the
label mpg_XXXXXXXX (the EE address of its first MPG code, the analyzer's function name). Branch
targets inside the program become labels mpg_XXXXXXXX_YYYY (YYYY is the micro address).

The instruction text is dvp-objdump's. The file is assembled and compared with the input, and any
instruction that does not reassemble to its own bytes (an unused encoding, or a branch out of its
program) is written as a .word pair with the disassembly in a comment. This repeats until the
output matches; the tool fails rather than write a file that does not.
"""
import argparse
import os
import re
import struct
import subprocess
import sys
import tempfile

VIF_MPG = (0x4a)
BRANCHES = {"b", "bal", "ibeq", "ibne", "ibltz", "ibgtz", "iblez", "ibgez"}
VIF_NAMES = {
	0x00: "NOP", 0x01: "STCYCL", 0x02: "OFFSET", 0x03: "BASE", 0x04: "ITOP", 0x05: "STMOD",
	0x06: "MSKPATH3", 0x07: "MARK", 0x10: "FLUSHE", 0x11: "FLUSH", 0x13: "FLUSHA", 0x14: "MSCAL",
	0x15: "MSCALF", 0x17: "MSCNT", 0x20: "STMASK", 0x30: "STROW", 0x31: "STCOL", 0x4a: "MPG",
	0x50: "DIRECT", 0x51: "DIRECTHL",
}
DMA_IDS = {0: "refe", 1: "cnt", 2: "next", 3: "ref", 4: "refs", 5: "call", 6: "ret", 7: "end"}


def read_file(path):
	with open(path, "rb") as f:
		return f.read()


def word(data, at):
	return struct.unpack_from("<I", data, at)[0]


def is_microcode(data, at, count):
	"""No upper instruction sets bits 25 and 26, so a stray 0x4a byte in other data is not an upload."""
	return all(word(data, at + 8 * k + 4) & 0x06000000 == 0 for k in range(count))


def parse(data):
	"""Splits the segment into ("words", offset, end) and ("mpg", offset of the MPG code, num, micro address)."""
	items = []
	last = i = 0
	while i + 4 <= len(data):
		code = word(data, i)
		if (code >> 24) & 0x7f == VIF_MPG and (i + 4) % 8 == 0:
			num = (code >> 16) & 0xff or 256
			address = (code & 0xffff) * 8
			if i + 4 + num * 8 <= len(data) and address + num * 8 <= 0x4000 and is_microcode(data, i + 4, num):
				if last < i:
					items.append(("words", last, i))
				items.append(("mpg", i, num, address))
				i += 4 + num * 8
				last = i
				continue
		i += 4
	if last < len(data):
		items.append(("words", last, len(data)))
	return items


def programs(items):
	"""Groups uploads to consecutive micro addresses: [(MPG offset of the first, micro address, [uploads])]."""
	out = []
	for item in items:
		if item[0] != "mpg":
			continue
		if out and item[3] == out[-1][1] + sum(u[2] * 8 for u in out[-1][2]):
			out[-1][2].append(item)
		else:
			out.append((item[1], item[3], [item]))
	return out


def run(args, **kw):
	return subprocess.run(args, capture_output=True, text=True, **kw)


def section(dvp, obj, name):
	"""(file offset, size) of section NAME in an object."""
	out = run([dvp + "/dvp-objdump", "-h", obj], check=True).stdout
	m = re.search(r"\s%s\s+([0-9a-f]+)\s+[0-9a-f]+\s+[0-9a-f]+\s+([0-9a-f]+)" % re.escape(name), out)
	return int(m[2], 16), int(m[1], 16)


def disassemble(dvp, code, work):
	"""dvp-objdump text for each 8-byte slot of CODE, as (upper, lower) with branch targets as offsets.

	dvp-objdump decodes VU code only after the mapping symbol dvp-as emits, so this assembles NOP pairs
	of the same size and patches CODE into their .vutext.
	"""
	src, obj = os.path.join(work, "dis.vsm"), os.path.join(work, "dis.o")
	with open(src, "w") as f:
		f.write("\t.vu\n" + "\tNOP\tNOP\n" * (len(code) // 8))
	run([dvp + "/dvp-as", "-o", obj, src], check=True)
	offset, size = section(dvp, obj, ".vutext")
	assert size == len(code)
	blob = bytearray(read_file(obj))
	blob[offset:offset + size] = code
	with open(obj, "wb") as f:
		f.write(blob)
	text = run([dvp + "/dvp-objdump", "-d", obj], check=True).stdout
	lines = [l for l in text.splitlines() if re.match(r"\s+[0-9a-f]+:\t", l)]
	out = []
	for k in range(0, len(lines), 2):
		fields = lines[k].split("\t")
		out.append(tuple(re.sub(r"\s+", " ", x.strip()) for x in (fields[2:4] + ["", ""])[:2]))
	assert len(out) == len(code) // 8, (len(out), len(code))
	return out


def framing(data, base, start, end):
	"""Commented .word lines for the framing words in [start, end)."""
	lines = []
	at = start
	while at < end:
		w0 = word(data, at)
		# A DMA tag: 16-byte aligned, a known id, reserved bits clear, address word zero.
		if at % 16 == 0 and at + 8 <= end and word(data, at + 4) == 0 and (w0 & 0x0fff0000) == 0 \
				and (w0 >> 28) & 7 in (1, 7):
			lines.append("\t.word 0x%08x, 0x%08x\t; DMA %s, qwc %d" % (w0, 0, DMA_IDS[(w0 >> 28) & 7], w0 & 0xffff))
			at += 8
			continue
		cmd = (w0 >> 24) & 0x7f
		name = VIF_NAMES.get(cmd)
		if name == "MPG":
			note = "VIF MPG %d at 0x%04x" % ((w0 >> 16) & 0xff or 256, (w0 & 0xffff) * 8)
		elif name:
			note = "VIF %s%s 0x%04x" % (name, "[i]" if w0 >> 31 else "", w0 & 0xffff) if w0 & 0xffff else "VIF " + name
		else:
			note = "data"
		lines.append("\t.word 0x%08x\t\t; %s" % (w0, note))
		at += 4
	return lines


def render(data, base, items, groups, text, raw):
	"""The .vsm text, and the line number (1-based) of each instruction slot keyed by its offset."""
	lines = [
		"; Deadlocked .vutext: VIF DMA chains with VU microcode, generated from the retail segment by",
		"; tools/vu_split.py. dvp-as rebuilds it byte for byte. Addresses in names are EE addresses;",
		"; a suffix _YYYY is the micro address of a branch target.",
		"",
		"\t.vu",
	]
	slot_line = {}
	program_of = {}
	for start, address, uploads in groups:
		for u in uploads:
			program_of[u[1]] = (start, address, uploads)
	targets = {}
	for (start, address, uploads), dis in text.items():
		for offset, (upper, lower) in dis.items():
			target = branch_target(lower)
			if target is not None:
				targets.setdefault(start, set()).add(target)
	for item in items:
		if item[0] == "words":
			lines += framing(data, base, item[1], item[2])
			continue
		_, at, num, address = item
		start, first, uploads = program_of[at]
		lines += framing(data, base, at, at + 4)
		if at == start:
			lines += ["", "mpg_%08x:\t\t; micro 0x%04x" % (base + start, first)]
		dis = text[(start, first, tuple(uploads))]
		for k in range(num):
			offset = at + 4 + 8 * k
			micro = address + 8 * k
			if micro in targets.get(start, ()) and not (at == start and k == 0):
				lines.append("mpg_%08x_%04x:" % (base + start, micro))
			upper, lower = dis[offset]
			lo, hi = word(data, offset), word(data, offset + 4)
			target = branch_target(lower)
			if offset in raw:
				lines.append("\t.word 0x%08x, 0x%08x\t; %s\t%s" % (lo, hi, upper, lower))
			elif target is None:
				lines.append("\t%s\t\t%s" % (upper, lower))
			else:
				label = "mpg_%08x" % (base + start) if target == first else "mpg_%08x_%04x" % (base + start, target)
				if address <= target < address + num * 8:
					lines.append("\t%s\t\t%s" % (upper, re.sub(r"[0-9a-f]+$", label, lower)))
				else:
					# The VIF codes between uploads would put a label at the wrong distance, so a branch
					# into another upload (or out of the program) keeps its offset field, which dvp-as
					# takes as a number: (target - (pc + 8)) / 8.
					field = lo & 0x7ff
					field -= 0x800 if field & 0x400 else 0
					# Out of the program, the target wraps around micro memory, whose size is the unit's.
					note = label if in_program(target, first, uploads) else \
						"micro 0x%04x on VU1, 0x%04x on VU0" % (target & 0x3fff, target & 0xfff)
					lines.append("\t%s\t\t%s\t; -> %s" % (upper, re.sub(r"[0-9a-f]+$", str(field), lower), note))
			slot_line[offset] = len(lines)
	return "\n".join(lines) + "\n", slot_line


def branch_target(lower):
	"""The micro address a lower branch's text names (rewritten by disassemble_programs), or None."""
	m = re.match(r"(\S+) .*?([0-9a-f]+)$", lower)
	if not m or m[1] not in BRANCHES:
		return None
	return int(m[2], 16)


def in_program(target, first, uploads):
	return first <= target < first + sum(u[2] * 8 for u in uploads)


def disassemble_programs(dvp, data, groups, work):
	"""{program key: {slot offset: (upper, lower)}}, branch targets rewritten to micro addresses."""
	out = {}
	for start, first, uploads in groups:
		code = b"".join(data[u[1] + 4:u[1] + 4 + u[2] * 8] for u in uploads)
		dis = disassemble(dvp, code, work)
		slots = {}
		k = 0
		for u in uploads:
			for j in range(u[2]):
				upper, lower = dis[k]
				m = re.match(r"(\S+) (.*?)([0-9a-f]+)( <[^>]*>)?$", lower)
				if m and m[1] in BRANCHES:
					# dvp-objdump prints the target's offset in the patched object, which is the program.
					lower = "%s %s%x" % (m[1], m[2], first + int(m[3], 16))
				elif lower.startswith("loi "):
					# The printed float is rounded; the immediate's exact bits go in as hex.
					lower = "loi 0x%08x\t; %s" % (word(code, 8 * k), lower[4:])
				else:
					# dvp-as rejects the trailing fields dvp-objdump prints for a multi-field isw/ilw.
					lower = re.sub(r"^(i[sl]w\.[xyzw]{2,} .*\))[xyzw]+$", r"\1", lower)
				slots[u[1] + 4 + 8 * j] = (upper, lower)
				k += 1
		out[(start, first, tuple(uploads))] = slots
	return out


def assemble(dvp, source, work):
	"""(bytes of .vutext or None, {line number: error})."""
	src, obj = os.path.join(work, "out.vsm"), os.path.join(work, "out.o")
	with open(src, "w") as f:
		f.write(source)
	if os.path.exists(obj):
		os.remove(obj)
	result = run([dvp + "/dvp-as", "-o", obj, src])
	errors = {}
	for line in (result.stderr or "").splitlines():
		m = re.match(r".*?:(\d+): (Error|Warning): (.*)", line)
		if m:
			errors[int(m[1])] = m[3]
	if result.returncode != 0 or not os.path.exists(obj):
		return None, errors
	offset, size = section(dvp, obj, ".vutext")
	return read_file(obj)[offset:offset + size], errors


def convert(data, base, dvp):
	"""(.vsm text that dvp-as assembles to DATA, summary line). Raises RuntimeError if it cannot match."""
	if len(data) % 8:
		raise RuntimeError("vu_split: the segment is not a whole number of 64-bit words")
	items = parse(data)
	groups = programs(items)
	raw = set()
	with tempfile.TemporaryDirectory() as work:
		text = disassemble_programs(dvp, data, groups, work)
		for attempt in range(20):
			source, slot_line = render(data, base, items, groups, text, raw)
			built, errors = assemble(dvp, source, work)
			line_slot = {v: k for k, v in slot_line.items()}
			bad = {line_slot[n] for n in errors if n in line_slot}
			if built is None and not bad:
				raise RuntimeError("vu_split: dvp-as failed outside the microcode: %s" % errors)
			if built is not None and built == data and not errors:
				break
			if built is not None and len(built) == len(data):
				bad |= {o for o in slot_line if built[o:o + 8] != data[o:o + 8]}
			elif built is not None and not bad:
				# A size change shifts everything after it; take the first slot that differs.
				first = next(i for i in range(min(len(built), len(data))) if built[i] != data[i]) // 8 * 8
				bad |= {o for o in slot_line if o >= first - 8 and o < first + 8}
			if not bad - raw:
				raise RuntimeError("vu_split: no progress; differences outside the microcode")
			raw |= bad
		else:
			raise RuntimeError("vu_split: did not converge")
	total = sum(u[2] for g in groups for u in g[2])
	return source, "vu_split: %d programs, %d instructions, %d as .word, %d bytes match" % (
		len(groups), total, len(raw), len(data))


def main():
	ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	ap.add_argument("input")
	ap.add_argument("output")
	ap.add_argument("--base", type=lambda s: int(s, 0), default=0x100080)
	ap.add_argument("--dvp", default="/opt/ps2dev/dvp/bin")
	args = ap.parse_args()
	try:
		source, summary = convert(read_file(args.input), args.base, args.dvp)
	except RuntimeError as e:
		sys.exit(str(e))
	with open(args.output, "w", newline="\n") as f:
		f.write(source)
	print(summary)


if __name__ == "__main__":
	main()
