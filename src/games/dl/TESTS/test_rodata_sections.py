#!/usr/bin/env python3
"""Check jump-table section routing without changing table contents or SVO3 behavior."""
from pathlib import Path
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
from svo3_rodata_sections import rewrite


class TableSections(unittest.TestCase):
    def test_svo3_unchanged(self):
        source = '.section .svo_Test_run,"ax"\n.rdata\n.align 2\n.word $L1\n.section .svo_Test_run,"ax"\n.rdata\n.word $L2\n'
        expected = source.replace('.rdata\n', '\t.section .svo_Test_run.rodata,"a",@progbits\n')
        self.assertEqual(rewrite(source), expected)

    def test_separate_iksemel_tables(self):
        source = '.section .iks_iks_escape,"ax"\n.rdata\n.align 2\n.word $L1\n.section .iks_iks_escape,"ax"\n.rdata\n.align 2\n.word $L2\n'
        expected = source.replace('.rdata\n', '\t.section .iks_iks_escape.rodata,"a",@progbits\n', 1)
        expected = expected.replace('.rdata\n', '\t.section .iks_iks_escape.rodata.1,"a",@progbits\n', 1)
        self.assertEqual(rewrite(source), expected)
        self.assertEqual(rewrite(expected), expected)

    def test_function_boundary_and_unowned_data(self):
        source = '.section .iks_escape_size,"ax"\n.rdata\n.word $L1\n.section .iks_escape,"ax"\n.rdata\n.word $L2\n.text\n.rdata\n.word 7\n'
        expected = source.replace('.rdata\n', '\t.section .iks_escape_size.rodata,"a",@progbits\n', 1)
        expected = expected.replace('.rdata\n', '\t.section .iks_escape.rodata,"a",@progbits\n', 1)
        self.assertEqual(rewrite(source), expected)


if __name__ == '__main__':
    unittest.main()
