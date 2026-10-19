#!/usr/bin/env python3
"""Drop compiler-emitted .rodata only when it has no references or exports.

Used for recovered libm routines whose constants are immediate instructions.
Retail read-only data remains in the original split data object. Refuse to
remove anything referenced by a relocation, exported, writable or executable.
"""
import argparse
from pathlib import Path
import subprocess
from elftools.elf.elffile import ELFFile


def check_unused(path):
    with path.open('rb') as stream:
        elf = ELFFile(stream)
        sections = list(elf.iter_sections())
        targets = {i for i, section in enumerate(sections) if section.name == '.rodata'}
        for index in targets:
            section = sections[index]
            if section['sh_flags'] & 5:
                raise ValueError('refusing writable or executable .rodata')
        for section in sections:
            if section['sh_type'] in ('SHT_REL', 'SHT_RELA'):
                symbols = elf.get_section(section['sh_link'])
                for relocation in section.iter_relocations():
                    symbol = symbols.get_symbol(relocation['r_info_sym'])
                    if symbol['st_shndx'] in targets:
                        raise ValueError('referenced .rodata: ' + symbol.name)
            elif section['sh_type'] == 'SHT_SYMTAB':
                for symbol in section.iter_symbols():
                    if symbol['st_shndx'] in targets and symbol['st_info']['bind'] != 'STB_LOCAL':
                        raise ValueError('exported .rodata: ' + symbol.name)
        return sum(sections[index]['sh_size'] for index in targets)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('--objcopy', default='/usr/bin/mips-linux-gnu-objcopy')
    parser.add_argument('--check-only', action='store_true')
    args = parser.parse_args()
    size = check_unused(args.object)
    if not args.check_only and size:
        subprocess.run([args.objcopy, '--remove-section=.rodata', str(args.object)], check=True)
    print('%s: %d unreferenced, non-exported .rodata bytes' % (args.object, size))


if __name__ == '__main__':
    main()
