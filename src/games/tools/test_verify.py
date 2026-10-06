"""Test verifier classification and orchestration without invoking make or an SDK."""
import contextlib
import io
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import unittest
from unittest.mock import patch
import verify


def elf(payload=b'ORIG', address=0x1000):
    data = bytearray(0x104)
    ident = b'\x7fELF\x01\x01\x01' + bytes(9)
    struct.pack_into('<16sHHIIIIIHHHHHH', data, 0, ident, 2, 8, 1, address, 52, 84,
                     0x20924001, 52, 32, 1, 40, 1, 0)
    struct.pack_into('<8I', data, 52, 1, 0x100, address, address, 4, 8, 7, 4)
    data[0x100:] = payload
    return data


class VerifyTests(unittest.TestCase):
    def run_fixture(self, payload=b'EDIT', flags=(), fail=None, malformed=False, address=0x1000):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            game = root/'dl'
            (game/'build').mkdir(parents=True)
            (game/'TESTS').mkdir()
            (root/'assets/dl').mkdir(parents=True)
            (root/'assets/dl/boot_elf.elf').write_bytes(elf())
            (game/'build/boot_elf.elf').write_bytes(b'bad ELF' if malformed else elf(payload, address))
            output = root/'reports'
            commands = []
            def run(command, **kwargs):
                commands.append(command)
                return subprocess.CompletedProcess(command, 1 if fail and any(fail in arg for arg in command) else 0)
            with patch.object(verify, 'GAMES', root), patch('sys.argv', ['verify.py','dl','--output',str(output),*flags]), patch('subprocess.run',side_effect=run), contextlib.redirect_stdout(io.StringIO()):
                code = verify.main()
            return code, json.loads((output/'summary.json').read_text()), commands

    def test_nonmatching_development_build_is_usable(self):
        code, report, _ = self.run_fixture(flags=['--no-build'])
        self.assertEqual(code, 0)
        self.assertEqual(next(c for c in report['checks'] if c['name']=='exact-matching')['status'], 'NONMATCH')
        self.assertIn('nonmatching development', report['result'])

    def test_strict_mode_fails_nonmatching(self):
        code, _, _ = self.run_fixture(flags=['--no-build','--require-matching'])
        self.assertEqual(code, 2)

    def test_real_failure_is_never_waived(self):
        code, _, _ = self.run_fixture(flags=['--no-build','--require-matching'],fail='check_global_map.py')
        self.assertEqual(code, 1)

    def test_failed_build_does_not_audit_stale_output(self):
        code, report, commands = self.run_fixture(fail='make')
        self.assertEqual(code, 1)
        self.assertEqual(len(commands), 1)
        self.assertEqual(report['checks'][0]['name'], 'build-elf')
        self.assertNotIn('rebuilt_sha256', report)

    def test_split_and_compile_are_serial_stages(self):
        code, _, commands = self.run_fixture(flags=['--split'])
        self.assertEqual(code, 0)
        self.assertEqual([c[-1] for c in commands if c[0]=='make'], ['ps2dev','rom','split','elf'])

    def test_malformed_elf_is_error_not_nonmatching(self):
        code, report, _ = self.run_fixture(flags=['--no-build'],malformed=True)
        self.assertEqual(code, 1)
        self.assertFalse(any(c['status']=='NONMATCH' for c in report['checks']))

    def test_runtime_layout_failure_is_hard_failure(self):
        code, _, _ = self.run_fixture(flags=['--no-build'],address=0x2000)
        self.assertEqual(code, 1)

    def test_exact_match_passes_strict_gate(self):
        code, report, _ = self.run_fixture(payload=b'ORIG',flags=['--no-build','--require-matching'])
        self.assertEqual(code, 0)
        self.assertEqual(next(c for c in report['checks'] if c['name']=='exact-matching')['differing_loaded_bytes'], 0)

    def test_truncated_load_is_error(self):
        with tempfile.TemporaryDirectory() as directory:
            a, b = Path(directory)/'a', Path(directory)/'b'
            a.write_bytes(elf()); b.write_bytes(elf()[:-1])
            with self.assertRaises(ValueError): verify.exact_result(a,b)


if __name__ == '__main__':
    unittest.main()
