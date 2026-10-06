#!/usr/bin/env python3
"""Run inside a disposable container with /reference and /reports mounted."""
import hashlib
import os
from pathlib import Path
import shutil
import subprocess

reference = Path('/reference')
root = Path('/ProjectRYNO')
game = root / 'dl'
reports = Path('/reports')
game.mkdir(parents=True, exist_ok=True)
for name in ('config', 'tests'):
    shutil.copytree(reference / 'dl' / name, game / name, dirs_exist_ok=True)
shutil.copy2(reference / 'dl/Makefile', game / 'Makefile')
(game / 'DOCS').mkdir(exist_ok=True)
shutil.copy2(reference / 'dl/DOCS/GLOBAL_VARIABLES.csv', game / 'DOCS/GLOBAL_VARIABLES.csv')
for directory, dirs, files in os.walk(reference / 'dl/code'):
    dirs[:] = [d for d in dirs if d != 'asm']
    destination = game / 'code' / Path(directory).relative_to(reference / 'dl/code')
    destination.mkdir(parents=True, exist_ok=True)
    for name in files:
        shutil.copy2(Path(directory) / name, destination / name)
(root / 'tools').mkdir(exist_ok=True)
for source in (reference / 'tools').glob('*.py'):
    shutil.copy2(source, root / 'tools' / source.name)
(root / 'assets/dl').mkdir(parents=True, exist_ok=True)
shutil.copy2(reference / 'assets/dl/boot_elf.elf', root / 'assets/dl/boot_elf.elf')
shutil.copy2(reference / 'dl/DOCS/RECOVERED_TYPES.json', game / 'DOCS/RECOVERED_TYPES.json')
source = game / 'code/game/boot.cpp'
before = hashlib.sha256(source.read_bytes()).hexdigest()
sound_source = game / 'code/989snd/ee/989snd.c'
sound_before = hashlib.sha256(sound_source.read_bytes()).hexdigest()
for target in ('full-clean', 'ps2dev', 'rom', 'split', 'elf'):
    print('Running make ' + target, flush=True)
    with (reports / ('clean-' + target + '.log')).open('w') as log:
        subprocess.run(['make', '-j8', target], cwd=game, stdout=log, stderr=subprocess.STDOUT, check=True)
with (reports / 'type-layouts.txt').open('w') as log:
    subprocess.run(['python3', 'tests/check_type_layouts.py'], cwd=game,
                   stdout=log, stderr=subprocess.STDOUT, check=True)
assert hashlib.sha256(source.read_bytes()).hexdigest() == before, 'split changed boot.cpp'
assert hashlib.sha256(sound_source.read_bytes()).hexdigest() == sound_before, 'split changed handwritten 989snd.c'
with (reports / 'clean-main-check.txt').open('w') as log:
    subprocess.run(['python3', 'tests/check_main_elf.py', '../assets/dl/boot_elf.elf',
                    'build/boot_elf.elf', 'build/code/game/boot.o'], cwd=game,
                   stdout=log, stderr=subprocess.STDOUT, check=True)
with (reports / 'clean-sound-behavior.txt').open('w') as log:
    subprocess.run(['python3', 'tests/test_989snd_wrappers.py', '../assets/dl/boot_elf.elf',
                    'build/boot_elf.elf'], cwd=game, stdout=log, stderr=subprocess.STDOUT, check=True)
with (reports / 'clean-sound-state.txt').open('w') as log:
    subprocess.run(['python3', 'tests/test_989snd_state.py', '../assets/dl/boot_elf.elf',
                    'build/boot_elf.elf'], cwd=game, stdout=log, stderr=subprocess.STDOUT, check=True)
with (reports / 'clean-global-map.txt').open('w') as log:
    subprocess.run(['python3', 'tests/check_global_map.py', 'build/boot_elf.elf'],
                   cwd=game, stdout=log, stderr=subprocess.STDOUT, check=True)
print('PASS: full-clean retained handwritten sources, passed the ELF/global audits and both sound differential suites', flush=True)
