#!/usr/bin/env python3
"""Build and verify a game; report nonmatching output separately from real failures."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import struct
import sys

from compare_elf import read_elf, runtime_layout

GAMES = Path(__file__).resolve().parents[1]


def exact_result(original, rebuilt):
    # Parse both inputs first: malformed/missing ELFs are errors, not NONMATCH.
    for path in (original, rebuilt):
        raw = path.read_bytes()
        if raw[:6] != b"\x7fELF\x01\x01":
            raise ValueError('Expected little-endian ELF32: ' + str(path))
        header = struct.unpack_from('<16sHHIIIIIHHHHHH', raw)
        if header[9] < 32 or not header[10]:
            raise ValueError('Missing/invalid ELF program headers')
        for i in range(header[10]):
            segment = struct.unpack_from('<8I', raw, header[5] + i * header[9])
            if segment[0] == 1 and (segment[4] > segment[5] or segment[1] + segment[4] > len(raw)):
                raise ValueError('Truncated or invalid ELF load segment')
    old = read_elf(original)[1]
    new = read_elf(rebuilt)[1]
    if not old or not new:
        raise ValueError('ELF has no loadable image')
    if runtime_layout(original) != runtime_layout(rebuilt):
        return {'status': 'FAIL', 'detail': 'Runtime ELF headers/load layout differ'}
    if len(old) != len(new) or any(a != b or len(x) != len(y) for (a, x), (b, y) in zip(old, new)):
        return {'status': 'FAIL', 'detail': 'Loaded segment extents differ'}
    differences = sum(sum(a != b for a, b in zip(before, after))
                      for (_, before), (_, after) in zip(old, new))
    return {'status': 'NONMATCH' if differences else 'PASS', 'differing_loaded_bytes': differences}


def result_code(checks, require_matching):
    if any(c['status'] == 'FAIL' for c in checks):
        return 1
    if require_matching and any(c['status'] == 'NONMATCH' for c in checks):
        return 2
    return 0


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('game', choices=['rac', 'gc', 'uya', 'dl'])
    parser.add_argument('--split', action='store_true', help='Run ps2dev, rom, split serially before building')
    parser.add_argument('--no-build', action='store_true', help='Audit existing output; does not prove freshness')
    parser.add_argument('--host-tests', action='store_true', help='Also run boot C++ host tests; requires g++')
    parser.add_argument('--require-matching', action='store_true', help='Exit 2 for nonmatching bytes, even when diagnostic checks pass')
    parser.add_argument('--jobs', type=int, default=8)
    parser.add_argument('--output', type=Path, help='New or empty report directory')
    args = parser.parse_args()
    if args.game != 'dl':
        parser.error('No verified profile yet for ' + args.game + '; implement that game profile before claiming verification.')
    if args.jobs < 1 or (args.no_build and args.split):
        parser.error('Use positive --jobs; --split cannot be combined with --no-build')
    game = GAMES / args.game
    tests = game / ('TESTS' if (game / 'TESTS').is_dir() else 'tests')
    original = GAMES / 'assets' / args.game / 'boot_elf.elf'
    rebuilt = game / 'build/boot_elf.elf'
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ')
    output = (args.output or game / 'build/verification' / stamp).resolve()
    if output.exists() and (not output.is_dir() or any(output.iterdir())):
        parser.error('Report directory must be new or empty: ' + str(output))
    output.mkdir(parents=True, exist_ok=True)
    checks = []
    report = dict(game=args.game, started_utc=stamp, mode='existing-output' if args.no_build else 'forced-build',
                  require_matching=args.require_matching, checks=checks,
                  runtime_testing='NOT RUN: ISO packing, emulator, and gameplay',
                  original=str(original), rebuilt=str(rebuilt))

    def record(name, status, **details):
        checks.append(dict(name=name, status=status, **details))
        print(name + ': ' + status, flush=True)

    def run(name, command):
        path = output / (name + '.log')
        try:
            with path.open('w') as log:
                result = subprocess.run([str(x) for x in command], cwd=game, stdout=log, stderr=subprocess.STDOUT)
            record(name, 'PASS' if result.returncode == 0 else 'FAIL', returncode=result.returncode,
                   command=[str(x) for x in command], log=path.name)
            return result.returncode == 0
        except OSError as error:
            record(name, 'FAIL', detail=str(error), log=path.name)
            return False

    try:
        report['original_sha256'] = digest(original)
        if not args.no_build:
            targets = (['ps2dev', 'rom', 'split'] if args.split else []) + ['elf']
            for target in targets:
                command = ['make'] + (['-B', '-j' + str(args.jobs)] if target == 'elf' else []) + [target]
                if not run('build-' + target, command):
                    return finish(report, output, args.require_matching)
        else:
            record('build', 'SKIP', detail='Existing output requested; source freshness not established')
        report['rebuilt_sha256'] = digest(rebuilt)
        comparison = exact_result(original, rebuilt)
        record('exact-matching', **comparison)
        py = sys.executable
        run('elf-layout-and-slots', [py, tests/'check_main_elf.py', original, rebuilt, game/'build/code/game/boot.o'])
        run('global-addresses', [py, tests/'check_global_map.py', rebuilt])
        run('type-layouts', [py, tests/'check_type_layouts.py'])
        run('sound-wrappers', [py, tests/'test_989snd_wrappers.py', original, rebuilt])
        run('sound-state', [py, tests/'test_989snd_state.py', original, rebuilt])
        run('progress', [py, GAMES/'tools/function_progress.py', args.game, '--elf', rebuilt, '--output', output/'progress'])
        if args.host_tests:
            compiler = shutil.which('g++')
            if not compiler:
                record('boot-host-tests', 'FAIL', detail='g++ is required by --host-tests')
            else:
                executable = output/'boot-main-test'
                if run('boot-main-compile', [compiler, '-std=c++98', '-O2', '-fno-builtin', '-Icode/include', tests/'boot_main_test.cpp', '-o', executable]):
                    run('boot-main-behavior', [executable])
                obj = output/'boot-options.o'
                executable = output/'boot-options-test'
                if run('boot-options-compile', [compiler, '-std=c++98', '-O2', '-fno-builtin', '-DPERMUTER', '-Dmain=tested_boot_main', '-Icode/include', '-ffunction-sections', '-fsanitize=address,undefined', '-c', 'code/game/boot.cpp', '-o', obj]):
                    if run('boot-options-link', [compiler, '-std=c++98', '-O2', '-fsanitize=address,undefined', '-Wl,--gc-sections', tests/'boot_options_test.cpp', obj, '-o', executable]):
                        run('boot-options-behavior', [executable])
        else:
            record('boot-host-tests', 'SKIP', detail='Use --host-tests to run host boot behavior checks')
        if digest(rebuilt) != report['rebuilt_sha256']:
            record('output-stability', 'FAIL', detail='ELF changed during verification; do not build concurrently')
    except (OSError, ValueError, KeyError, IndexError) as error:
        record('verification', 'FAIL', detail=str(error))
    except Exception as error:
        record('verification', 'FAIL', detail=type(error).__name__ + ': ' + str(error))
    return finish(report, output, args.require_matching)


def finish(report, output, require_matching):
    code = result_code(report['checks'], require_matching)
    report['exit_code'] = code
    report['finished_utc'] = datetime.now(timezone.utc).isoformat()
    report['result'] = ('FAILED' if code == 1 else 'NONMATCHING: strict gate failed' if code == 2 else
                        'CHECKS PASSED: nonmatching development build' if any(c['status']=='NONMATCH' for c in report['checks']) else
                        'CHECKS PASSED: executable matching')
    (output/'summary.json').write_text(json.dumps(report, indent=2) + '\n')
    print(report['result'], flush=True)
    print('Reports: ' + str(output), flush=True)
    return code


if __name__ == '__main__':
    raise SystemExit(main())
