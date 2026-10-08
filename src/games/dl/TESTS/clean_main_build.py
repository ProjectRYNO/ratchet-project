#!/usr/bin/env python3
"""Build from a fresh CLI extraction in an isolated container; retain reports and ISO."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--iso', required=True, type=Path)
args = parser.parse_args()
reference = Path('/reference')
root = Path('/ProjectRYNO')
game = root / 'dl'
reports = Path('/reports')
if game.exists():
    raise SystemExit('Use a fresh container: /ProjectRYNO/dl already exists')
game.mkdir(parents=True)
reports.mkdir(parents=True, exist_ok=True)
shutil.copytree(reference / 'dl/config', game / 'config', ignore=shutil.ignore_patterns('*.rom', '*.ld', '*.d'))
shutil.copytree(Path(__file__).resolve().parent, game / 'tests', ignore=shutil.ignore_patterns('keep', 'build', '__pycache__', '*.elf', '*.iso', '*.o'))
shutil.copy2(reference / 'dl/Makefile', game / 'Makefile')
for name in ('symbols/GLOBAL_VARIABLES.csv', 'types/RECOVERED_TYPES.json'):
    target = game / 'DOCS' / name
    target.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(reference / 'dl/DOCS' / name, target)
for directory, dirs, files in os.walk(reference / 'dl/code'):
    dirs[:] = [d for d in dirs if d != 'asm']
    destination = game / 'code' / Path(directory).relative_to(reference / 'dl/code')
    destination.mkdir(parents=True, exist_ok=True)
    for name in files:
        shutil.copy2(Path(directory) / name, destination / name)
(root / 'tools').mkdir(exist_ok=True)
for source in (reference / 'tools').glob('*.py'):
    shutil.copy2(source, root / 'tools' / source.name)

def hashes():
    return {str(p.relative_to(game)): hashlib.sha256(p.read_bytes()).hexdigest()
            for p in (game / 'code').rglob('*')
            if p.suffix in ('.cpp', '.c', '.h') and 'asm' not in p.parts
            and '{' in p.read_text(errors='replace')}

before = hashes()
(reports / 'source-hashes.json').write_text(json.dumps(before, indent=2) + '\n')

def run(name, command, check=True):
    print('Running ' + name, flush=True)
    with (reports / (name + '.log')).open('w') as log:
        result = subprocess.run(command, cwd=game, stdout=log, stderr=subprocess.STDOUT)
    if check and result.returncode:
        raise SystemExit(f'{name} failed ({result.returncode}); inspect /reports/{name}.log')
    return result.returncode

for target in ('full-clean', 'dump', 'ps2dev', 'rom', 'split', 'elf'):
    command = ['make'] + (['-j8'] if target == 'elf' else []) + [target]
    if target == 'dump':
        command.append('iso=' + str(args.iso))
    run('clean-' + target, command)
after = hashes()
if any(after.get(name) != digest for name, digest in before.items()):
    raise SystemExit('Splitting changed handwritten source; inspect source-hashes.json')
original = '../assets/dl/boot.elf'
rebuilt = 'build/boot_elf.elf'
for name, command in (
    ('elf-layout-and-slots', ['tests/check_main_elf.py', original, rebuilt, 'build/code/game/boot.o']),
    ('global-addresses', ['tests/check_global_map.py', rebuilt]),
    ('type-layouts', ['tests/check_type_layouts.py']),
    ('sound-wrappers', ['tests/test_989snd_wrappers.py', original, rebuilt]),
    ('sound-state', ['tests/test_989snd_state.py', original, rebuilt]),
):
    run(name, [sys.executable] + command)
matching = run('exact-matching', [sys.executable, '../tools/compare_elf.py', original, rebuilt], check=False)
if matching not in (0, 1):
    raise SystemExit('Strict comparison could not run')
run('pack-iso', ['make', 'iso'])
run('verify-iso', [sys.executable, '../tools/verify_boot_iso.py', str(args.iso), 'build/new_dl.iso', rebuilt])
shutil.copy2(game / rebuilt, reports / 'boot_elf.elf')
shutil.copy2(game / 'build/new_dl.iso', reports / 'new_dl_clean.iso')
summary = dict(status='PASS', fresh_cli_extraction=True, handwritten_source_preserved=True,
               executable_matching='PASS' if matching == 0 else 'NONMATCHING development build; see exact-matching.log',
               iso=str(reports / 'new_dl_clean.iso'), emulator='NOT RUN')
(reports / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
print(json.dumps(summary, indent=2), flush=True)
