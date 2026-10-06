#!/usr/bin/env python3
"""Verify recovered global names in the actual linked ELF against the inventory."""
import argparse
import csv
from pathlib import Path
import re
from check_main_elf import symbols

ROOT=Path(__file__).resolve().parents[1]


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('elf')
    args=parser.parse_args()
    rows=list(csv.DictReader((ROOT/'DOCS/symbols/GLOBAL_VARIABLES.csv').open()))
    configured={name:int(address,16) for name,address in re.findall(
        r'^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;',
        (ROOT/'config/symbols_core.text.txt').read_text(),re.M)}
    linked=symbols(args.elf)
    names=set()
    for row in rows:
        if row['status']!='mapped': continue
        name,address=row['name'],int(row['retail_address'],16)
        assert name not in names, 'duplicate mapped name: '+name
        names.add(name)
        assert row['prototype_matches'] and row['dlglobals_lines'], 'missing provenance: '+name
        assert configured.get(name)==address, 'configured address mismatch: '+name
        assert name in linked, 'name missing from ELF: '+name
        assert linked[name][0]==address, 'linked address mismatch: '+name
        assert linked[name][3]!=0, 'undefined global: '+name
    assert names, 'empty map'
    print('PASS: %d recovered global names resolve to their recorded retail addresses'%len(names))


if __name__=='__main__': main()
