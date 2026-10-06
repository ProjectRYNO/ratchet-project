#!/usr/bin/env python3
"""Exercise the generated guards with real MIPS assembler/linker inputs."""
from pathlib import Path
import subprocess
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
from split_dl import runtime_linker_script

with tempfile.TemporaryDirectory() as temporary:
    root = Path(temporary)
    (root / 'build/code/game').mkdir(parents=True)
    source = '''SECTIONS
{
    .core_text 0x157738 : SUBALIGN(4)
    {
        build/code/game/boot.o(.text*);
    }
}
'''
    replacements = {'objects': {'game/boot': {'text_start': 0x157738, 'text_end': 0x157D60}},
                    'functions': {'main': 0x157C58}}
    script = runtime_linker_script(source, {'segments': []}, replacements)
    (root / 'layout.ld').write_text(script)
    cases = [
        ('valid', 0x520, 0x104, True, True),
        ('missing main', 0x520, 0x104, False, False),
        ('main moved', 0x51C, 0x104, True, False),
        ('oversized object', 0x520, 0x110, True, False),
    ]
    for name, prefix, size, define, expected in cases:
        assembly = '.text\n.space %d\n' % prefix
        if define:
            assembly += '.globl main\n.type main,@function\nmain:\n'
        assembly += '.space %d\n' % size
        (root / 'input.s').write_text(assembly)
        subprocess.run(['mips-linux-gnu-as', '-EL', '-no-pad-sections', 'input.s',
                        '-o', 'build/code/game/boot.o'], cwd=root, check=True)
        result = subprocess.run(['mips-linux-gnu-ld', '-EL', '-T', 'layout.ld',
                                 'build/code/game/boot.o', '-o', 'test.elf'],
                                cwd=root, capture_output=True, text=True)
        if (result.returncode == 0) != expected:
            raise SystemExit('FAIL: ' + name + '\n' + result.stderr)
        print('PASS: ' + name + (' links' if expected else ' is rejected'))

    replacements['objects']['game/boot']['slots'] = [
        {'object': 'game/boot', 'section': '.boot_replacement',
         'start': 0x157C58, 'end': 0x157D60}]
    (root / 'layout.ld').write_text(runtime_linker_script(source, {'segments': []}, replacements))
    for name, padding, size, expected in [
        ('separate function section', 0, 0x104, True),
        ('misaligned function in slot', 4, 0x100, False),
        ('oversized function slot', 0, 0x10C, False),
    ]:
        (root / 'input.s').write_text('.text\n.space 0x520\n'
            '.section .boot_replacement,"ax",@progbits\n.space %d\n'
            '.globl main\n.type main,@function\nmain:\n.space %d\n' % (padding, size))
        subprocess.run(['mips-linux-gnu-as', '-EL', '-no-pad-sections', 'input.s',
                        '-o', 'build/code/game/boot.o'], cwd=root, check=True)
        result = subprocess.run(['mips-linux-gnu-ld', '-EL', '-T', 'layout.ld',
                                 'build/code/game/boot.o', '-o', 'test.elf'],
                                cwd=root, capture_output=True, text=True)
        if (result.returncode == 0) != expected:
            raise SystemExit('FAIL: ' + name + '\n' + result.stderr)
        print('PASS: ' + name + (' links' if expected else ' is rejected'))
