"""Synthetic loop-profile tests; optional assembly uses the pinned SN GNU as."""
import argparse
import io
from pathlib import Path
import subprocess
import tempfile
import unittest
from sound_loop_compat import adapt, branch_word, single_word

ASSEMBLE = False
PREFIX = '.text\n.globl sample\nsample:\n'


class LoopProfileTests(unittest.TestCase):
    def transform(self, body):
        return adapt(PREFIX+body)[0]

    def unchanged(self, body):
        source = PREFIX+body
        output, _ = adapt(source)
        self.assertEqual(output, source)

    def test_empty_loop(self):
        output = self.transform('.Lagain:\n b .Lagain\n')
        self.assertEqual(output.count('\tnop\n'), 5)
        self.assertIn('0x10000000', output)
        self.assertIn('(.Lagain - . - 4)', output)

    def test_conditional_explicit_delay_is_preserved(self):
        output = self.transform('.set noreorder\n.Lagain:\n bne $2,$3,.Lagain\n addiu $2,$2,-1\n.set reorder\n')
        self.assertIn('0x14430000', output)
        self.assertEqual(output.count('addiu $2,$2,-1'), 1)
        self.assertEqual(output.count('\tnop\n'), 4)

    def test_call_loop(self):
        output = self.transform('.Lagain:\n jal tick\n bnez $2,.Lagain\n')
        self.assertEqual(output.count('jal tick'), 1)
        self.assertEqual(output.count('\tnop\n'), 3)

    def test_sized_gp_delay(self):
        output = self.transform('.extern completion,4\n.Lagain:\n jal tick\n.set noreorder\n beq $2,$0,.Lagain\n lw $2,completion\n.set reorder\n')
        self.assertIn('0x10400000', output)
        self.assertEqual(output.count('lw $2,completion'), 1)

    def test_sufficient_length(self):
        self.unchanged('.Lagain:\n jal first\n jal second\n jal third\n bnez $2,.Lagain\n')

    def test_unknown_macro(self):
        self.unchanged('.Lagain:\n li $2,0x12345678\n bnez $2,.Lagain\n')

    def test_oversized_immediate(self):
        self.unchanged('.Lagain:\n addu $2,$2,65536\n bnez $2,.Lagain\n')

    def test_alignment_in_loop(self):
        self.unchanged('.Lagain:\n .p2align 4\n b .Lagain\n')

    def test_unknown_delay_macro(self):
        self.unchanged('.set noreorder\n.Lagain:\n bne $2,$3,.Lagain\n lw $2,unsized\n.set reorder\n')

    def test_branch_likely(self):
        self.unchanged('.Lagain:\n bnel $2,$3,.Lagain\n nop\n')

    def test_forward_branch(self):
        self.unchanged(' b .Lexit\n nop\n.Lexit:\n nop\n')

    def test_section_boundary(self):
        self.unchanged('.Lagain:\n.section .other,"ax"\n b .Lagain\n')

    def test_nested_branch_is_not_rewritten(self):
        self.unchanged('.Lagain:\n beqz $2,.Lexit\n b .Lagain\n.Lexit:\n nop\n')

    def test_rename_invariance(self):
        body = '.Lagain:\n jal tick\n bnez $2,.Lagain\n'
        self.assertEqual(self.transform(body).replace('.Lagain', '.Lrenamed'),
                         self.transform(body.replace('.Lagain', '.Lrenamed')))

    def test_idempotence(self):
        output = self.transform('.Lagain:\n jal tick\n bnez $2,.Lagain\n')
        self.assertEqual(adapt(output)[0], output)

    def test_operand_guards(self):
        self.assertFalse(single_word('lw', '$2,32768($3)'))
        self.assertFalse(single_word('subu', '$2,$2,-32768'))
        self.assertFalse(single_word('ori', '$2,$2,65536'))
        self.assertIsNone(branch_word('beq', '$2,100,.Lagain'))
        self.assertEqual(branch_word('bltz', '$s0,.Lagain')[0], 0x06000000)

    def test_assembled_vectors(self):
        if not ASSEMBLE:
            self.skipTest('use --assemble in the build container for SN assembler vectors')
        from elftools.elf.elffile import ELFFile
        vectors = [
            ('.Lagain:\n addiu $2,$2,-1\n addiu $3,$3,1\n addiu $4,$4,1\n addiu $5,$5,1\n bnez $2,.Lagain\n', [0x2442ffff,0x24630001,0x24840001,0x24a50001,0x1440fffb,0]),
            ('.Lagain:\n b .Lagain\n', [0,0,0,0,0x1000fffb,0]),
            ('.set noreorder\n.Lagain:\n bne $2,$3,.Lagain\n addiu $2,$2,-1\n.set reorder\n', [0,0,0,0,0x1443fffb,0x2442ffff]),
            ('.Lagain:\n jal tick\n bnez $2,.Lagain\n', [0x0c000000,0,0,0,0x1440fffb,0]),
            ('.extern completion,4\n.Lagain:\n jal tick\n.set noreorder\n beq $2,$0,.Lagain\n lw $2,completion\n.set reorder\n', [0x0c000000,0,0,0,0x1040fffb,0x8f820000]),
        ]
        with tempfile.TemporaryDirectory(prefix='sound-loops-') as directory:
            source, obj = Path(directory)/'fixture.s', Path(directory)/'fixture.o'
            for body, expected in vectors:
                with self.subTest(body=body):
                    source.write_text(self.transform(body))
                    subprocess.run(['/opt/wibo-1.2.0', '/opt/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe',
                                    '-EL', '-G8', '-g', str(source), '-o', str(obj)], check=True, capture_output=True)
                    elf = ELFFile(io.BytesIO(obj.read_bytes()))
                    data = elf.get_section_by_name('.text').data()
                    self.assertEqual(data[:24], b''.join(w.to_bytes(4, 'little') for w in expected))
                    self.assertFalse(any(data[24:]), 'unexpected extra instructions')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--assemble', action='store_true')
    args = parser.parse_args()
    ASSEMBLE = args.assemble
    unittest.main(argv=[__file__])
