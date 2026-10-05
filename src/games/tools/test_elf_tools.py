"""Regression tests for the extraction/layout failures in the Deadlocked build."""
import struct
import tempfile
import unittest
from pathlib import Path

from compare_elf import runtime_layout
from elf_to_rom import extract
from split_dl import is_generated_wrapper, normalize_assembly


def fixture(offset=0x100, physical=0x100080):
    data = bytearray(offset + 8)
    ident = b"\x7fELF\x01\x01\x01" + bytes(9)
    struct.pack_into("<16sHHIIIIIHHHHHH", data, 0,
                     ident, 2, 8, 1, 0x100080, 52, 0, 0x20924001, 52, 32, 2, 40, 0, 0)
    struct.pack_into("<8I", data, 52, 1, offset, 0x100080, physical, 4, 8, 7, 0x1000)
    struct.pack_into("<8I", data, 84, 1, offset+4, 0x1E9A000, 0x1E9A000, 4, 4, 7, 0x1000)
    data[offset:offset+8] = b"MAINNET!"
    return data


class ElfToolsTests(unittest.TestCase):
    def test_network_uses_config_offset_not_ram_gap(self):
        config = {"segments": [
            {"name": "main", "type": "code", "start": 0, "vram": 0x100080},
            {"name": "padding", "type": "pad", "start": 8, "vram": 0x100088},
            {"name": "net", "type": "code", "start": 16, "vram": 0x1E9A000},
            [20],
        ]}
        self.assertEqual(extract(fixture(), config), b"MAIN" + bytes(12) + b"NET!")
        with self.assertRaises(ValueError):
            extract(fixture()[:-1], config)

    def test_layout_ignores_file_offsets_but_checks_physical_addresses(self):
        with tempfile.TemporaryDirectory() as tmp:
            paths = [Path(tmp)/str(i) for i in range(3)]
            for path, data in zip(paths, [fixture(), fixture(0x200), fixture(physical=0)]):
                path.write_bytes(data)
            self.assertEqual(runtime_layout(paths[0]), runtime_layout(paths[1]))
            self.assertNotEqual(runtime_layout(paths[0]), runtime_layout(paths[2]))

    def test_preserve_real_c_implementations(self):
        self.assertTrue(is_generated_wrapper('#include "common.h"\nINCLUDE_ASM("some/path", fn);\nvoid empty(void) {}'))
        self.assertFalse(is_generated_wrapper('#include "common.h"\nvoid fn(void) { counter++; }'))
        self.assertFalse(is_generated_wrapper('static int counter;\nvoid empty(void) {}'))

    def test_cross_object_branch_and_function_alignment(self):
        source = '.align 3\n/* 3DF628 004DF6A8 31001105 */ bgezal $8, _ssp_load_tex\n'
        expected = '.align 2\n/* 3DF628 004DF6A8 31001105 */ bgezal $8, . + (200)\n'
        self.assertEqual(normalize_assembly(source), expected)
        self.assertEqual(normalize_assembly(expected), expected)


if __name__ == "__main__":
    unittest.main()
