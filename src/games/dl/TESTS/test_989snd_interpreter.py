"""Check the second divide unit independently of compiled sound source."""
import struct
import unittest

from test_989snd_wrappers import WrapperMachine, MASK


def execute(words, arguments):
    code = struct.pack('<%dI' % len(words), *words)
    machine = WrapperMachine([(0x1000, code)], {}, arguments + [0] * (8 - len(arguments)), 0)
    return machine.run(0x1000)[1]


class DivideUnitTests(unittest.TestCase):
    def test_signed_div1(self):
        # div1 a0,a1; mflo1 v0; jr ra; nop
        words = [0x7085001A, 0x70001012, 0x03E00008, 0]
        for dividend, divisor, expected in [(17, 5, 3), (-17, 5, -3),
                                            (17, -5, -3), (-17, -5, 3),
                                            (-2147483648, -1, -2147483648)]:
            with self.subTest(dividend=dividend, divisor=divisor):
                self.assertEqual(execute(words, [dividend & MASK, divisor & MASK]),
                                 expected & 0xFFFFFFFF)

    def test_lo_is_independent_of_lo1(self):
        # div a0,a1; div1 a2,a3; mflo v0; jr ra; nop
        self.assertEqual(execute([0x0085001A, 0x70C7001A, 0x00001012, 0x03E00008, 0],
                                 [35, 5, 99, 3]), 7)

    def test_unknown_mmi_still_fails(self):
        with self.assertRaisesRegex(AssertionError, 'unsupported MMI'):
            execute([0x7000003F, 0x03E00008, 0], [])


if __name__ == '__main__':
    unittest.main()
