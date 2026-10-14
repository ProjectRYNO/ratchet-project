#!/usr/bin/env python3
"""Compare fixed DL Medius C across EE compilers using fully relocated retail bytes."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess

from compare_elf import read_elf

FUNCTIONS = {
    'rt_strnlen': (0x01EAB1B8, 0x58),
    'rt_memory_get_aligned_address': (0x01EA9790, 0x48),
    'rt_memory_free': (0x01EA95C0, 0x58),
    'rt_memory_register_callbacks': (0x01EA9768, 0x18),
}


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def loaded_bytes(segments, address, size):
    for base, data in segments:
        if base <= address and address + size <= base + len(data):
            return data[address-base:address-base+size]
    raise ValueError('Missing loaded range at 0x%08X' % address)


def main():
    games = Path(__file__).resolve().parents[1]
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--original', type=Path, default=games/'assets/dl/boot.elf')
    ap.add_argument('--source', type=Path, default=games/'dl/TESTS/medius_compiler_probes.c')
    ap.add_argument('--output', type=Path, required=True)
    ap.add_argument('--compiler', nargs=3, action='append', metavar=('NAME', 'CC', 'AS'), required=True)
    ap.add_argument('--shim', type=Path, help='32-bit LD_PRELOAD stat shim for Sony executables')
    ap.add_argument('--cross', default='/usr/bin/mips-linux-gnu')
    args = ap.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    _, segments, _ = read_elf(args.original)
    reference = {name: loaded_bytes(segments, *bounds) for name, bounds in FUNCTIONS.items()}
    report = dict(original_sha256=digest(args.original), source_sha256=digest(args.source), compilers=[], results=[])
    for name, cc, assembler in args.compiler:
        env = dict(os.environ)
        if args.shim:
            env['LD_PRELOAD'] = str(args.shim.resolve())
        metadata = dict(name=name, cc=cc, assembler=assembler, cc_sha256=digest(cc), assembler_sha256=digest(assembler))
        for key, exe in [('version', cc), ('assembler_version', assembler)]:
            metadata[key] = subprocess.run([exe, '--version'], env=env, capture_output=True, text=True, check=True).stdout.strip()
        report['compilers'].append(metadata)
        for opt in ['O1', 'O2', 'Os', 'O3']:
            folder = args.output/(name+'_'+opt+'_G0')
            folder.mkdir(exist_ok=True)
            flags = ['-'+opt, '-G0', '-fno-builtin', '-fno-common', '-ffunction-sections', '-falign-functions=4', '-falign-loops=1', '-falign-jumps=1', '-falign-labels=1']
            commands = [
                [cc, *flags, '-S', str(args.source.resolve()), '-o', str(folder/'probe.s')],
                [assembler, '-EL', '-G0', str(folder/'probe.s'), '-o', str(folder/'probe.o')],
                [args.cross+'-strip', '-x', '-N', 'dummy-symbol-name', str(folder/'probe.o')],
            ]
            # Fixed retail call/data targets; no relocation masking or byte substitution.
            script = 'SECTIONS {\n'+''.join('.text.%s 0x%x : { *(.text.%s) }\n' % (n, a, n) for n, (a, _) in FUNCTIONS.items())+'}\n'
            script += 'gpfFreeCallback = 0x1681ac; gpfMallocCallback = 0x1681a4; free = 0x11efb0; _gp = 0x22597f;\n'
            (folder/'probe.ld').write_text(script)
            commands.append([args.cross+'-ld', '-EL', '--no-warn-mismatch', '-T', str(folder/'probe.ld'), str(folder/'probe.o'), '-o', str(folder/'probe.elf')])
            with (folder/'commands.log').open('w') as log:
                for command in commands:
                    log.write(repr(command)+'\n'); log.flush()
                    subprocess.run(command, env=env, stdout=log, stderr=subprocess.STDOUT, check=True)
            elf_path = folder/'probe.elf'
            data = elf_path.read_bytes()
            _, _, sections = read_elf(elf_path)
            sections = dict(sections)
            exact = []
            for function, original in reference.items():
                section = sections['.text.'+function]
                compiled = data[section[4]:section[4]+section[5]]
                match = compiled == original
                report['results'].append(dict(compiler=name, optimization=opt, function=function, flags=flags, size=len(compiled), retail_size=len(original), exact=match, equal_bytes=sum(a==b for a,b in zip(compiled, original))))
                if match: exact.append(function)
            print('%s %s: %d/4 exact: %s' % (name, opt, len(exact), ', '.join(exact)))
    (args.output/'results.json').write_text(json.dumps(report, indent=2)+'\n')


if __name__ == '__main__':
    main()
