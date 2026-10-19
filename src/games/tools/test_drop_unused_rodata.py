#!/usr/bin/env python3
"""Exercise the unused-data guard on real assembled MIPS objects."""
import shutil
import subprocess
import tempfile
from pathlib import Path
import unittest
from drop_unused_rodata import check_unused

AS = shutil.which('mips-linux-gnu-as')


@unittest.skipUnless(AS, 'requires mips-linux-gnu-as')
class GuardTests(unittest.TestCase):
    def assemble(self, source):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        root = Path(directory.name)
        (root/'test.s').write_text(source)
        subprocess.run([AS, '-EL', str(root/'test.s'), '-o', str(root/'test.o')], check=True, capture_output=True)
        return root/'test.o'

    def test_unused_local_constant(self):
        obj = self.assemble('.text\nnop\n.section .rodata\nlocal_value: .word 42\n')
        self.assertGreater(check_unused(obj), 0)

    def test_referenced_constant(self):
        obj = self.assemble('.text\n.word local_value\n.section .rodata\nlocal_value: .word 42\n')
        with self.assertRaisesRegex(ValueError, 'referenced'):
            check_unused(obj)

    def test_exported_constant(self):
        obj = self.assemble('.section .rodata\n.globl public_value\npublic_value: .word 42\n')
        with self.assertRaisesRegex(ValueError, 'exported'):
            check_unused(obj)

    def test_executable_section(self):
        obj = self.assemble('.section .rodata,"ax"\nnop\n')
        with self.assertRaisesRegex(ValueError, 'executable'):
            check_unused(obj)

    def test_writable_section(self):
        obj = self.assemble('.section .rodata,"aw"\n.word 42\n')
        with self.assertRaisesRegex(ValueError, 'writable'):
            check_unused(obj)


if __name__ == '__main__':
    unittest.main()
