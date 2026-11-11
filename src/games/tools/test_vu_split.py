"""vu_split.py on a synthetic VIF stream; needs PS2SDK's dvp binutils (skipped without them)."""
import os
import struct
import unittest

from vu_split import convert

DVP = os.environ.get("PS2DEV_DIR", "/opt/ps2dev") + "/dvp/bin"
NOP_LOWER, NOP_UPPER = (0x8000033c), (0x000002ff)


def words(*values):
	return struct.pack("<%dI" % len(values), *values)


def branch(field):
	"""Lower b with its 11-bit offset field, beside an upper nop."""
	return words((0x40000000) | (field & 0x7ff), NOP_UPPER)


# A DMA cnt tag, then a microprogram in two MPG uploads (micro 0x0000 and 0x0010) with VIF codes
# between them, then padding. Upload A: a loi, and a branch into upload B. Upload B: a multi-field
# isw, a branch back within B, and a branch that wraps out of the program.
STREAM = (
	words(0x10000003, 0, 0, 0x4a020000)
	+ words(0x3fc90fdb, 0x800002ff)	# nop[i]  loi 1.5708
	+ branch(0)	# b to micro 0x0010, the first slot of upload B
	+ words(0, 0x4a030002)
	+ words(0x0a600005, NOP_UPPER)	# isw.zw vi00,5(vi00)
	+ branch(-2)	# b to micro 0x0010
	+ branch(-0x100)	# b out of the program
	+ words(0, 0)
)


@unittest.skipUnless(os.path.exists(DVP + "/dvp-as"), "needs dvp-as")
class VuSplitTests(unittest.TestCase):
	@classmethod
	def setUpClass(cls):
		cls.source, cls.summary = convert(STREAM, 0x100080, DVP)

	def test_matches_without_word_fallbacks(self):
		self.assertIn("1 programs, 5 instructions, 0 as .word, %d bytes match" % len(STREAM), self.summary)

	def test_program_label_is_the_analyzer_name(self):
		self.assertIn("\nmpg_0010008c:", self.source)
		self.assertIn("\nmpg_0010008c_0010:", self.source)

	def test_loi_keeps_exact_bits(self):
		self.assertIn("loi 0x3fc90fdb", self.source)

	def test_multi_field_isw_drops_trailing_fields(self):
		self.assertRegex(self.source, r"isw\.zw vi00,5\(vi00\)\n")

	def test_branch_within_upload_uses_label(self):
		self.assertIn("b mpg_0010008c_0010\n", self.source)

	def test_branch_across_uploads_keeps_offset(self):
		self.assertIn("b 0\t; -> mpg_0010008c_0010", self.source)

	def test_branch_out_of_program_notes_both_units(self):
		self.assertIn("b -256\t; -> micro 0x3828 on VU1, 0x0828 on VU0", self.source)

	def test_framing_is_commented(self):
		self.assertIn("; DMA cnt, qwc 3", self.source)
		self.assertIn("; VIF MPG 3 at 0x0010", self.source)


if __name__ == "__main__":
	unittest.main()
