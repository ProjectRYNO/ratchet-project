#!/usr/bin/env python3
"""Inventory source-backed functions; never infer matching from decompiled status."""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import sys
from datetime import datetime, timezone
import yaml
from compare_elf import read_elf

GAMES = Path(__file__).resolve().parents[1]


def sha256(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def inventory(game, original, rebuilt):
    manifest = yaml.safe_load((game / 'config/decompiled_functions.yaml').read_text())
    notes_path = game / 'DOCS/progress/FUNCTION_NOTES.json'
    notes = json.loads(notes_path.read_text()) if notes_path.exists() else {}
    tests = game / ('TESTS' if (game / 'TESTS').is_dir() else 'tests')
    sys.path.insert(0, str(tests))
    from check_main_elf import symbols
    linked = symbols(rebuilt)
    old_segments = read_elf(original)[1]
    new_segments = read_elf(rebuilt)[1]
    def region(segments, start, end):
        for base, data in segments:
            if base <= start and end <= base + len(data):
                return data[start-base:end-base]
        raise ValueError('Function slot outside loaded image: 0x%X' % start)
    known = {}
    for path in sorted((game / 'config').glob('symbols*.txt')):
        for name, value in re.findall(r'^\s*([\w.$]+)\s*=\s*(0x[0-9a-fA-F]+)\s*;', path.read_text(), re.M):
            known.setdefault(name, set()).add(int(value, 16))
    slots = [slot for obj in manifest['objects'].values() for slot in obj.get('slots', [])]
    rows = []
    for source in sorted((game / 'code').rglob('*')):
        if source.suffix not in ('.c', '.cpp') or 'asm' in source.relative_to(game / 'code').parts:
            continue
        owner = source.relative_to(game).as_posix()
        for name in re.findall(r'^\s*INCLUDE_ASM\(\s*"[^"]+"\s*,\s*([\w.$]+)\s*\);', source.read_text(), re.M):
            addresses = known.get(name, set())
            if len(addresses) == 1:
                address = next(iter(addresses))
            elif not addresses and re.fullmatch(r'func_[0-9A-Fa-f]{8}', name):
                address = int(name[5:], 16)
            else:
                address = None
            rows.append(dict(name=name, source=owner, address='' if address is None else '0x%08X' % address,
                             implementation='assembly', slot_end='', compiled_size='', slot_match='not_measured',
                             differing_bytes='', test_scope='not inventoried', question='Recover ABI and retail behavior before replacing assembly.'))
    for name, address in manifest['functions'].items():
        slot = next(s for s in slots if s['start'] == address)
        sources = [game / ('code/' + slot['object'] + ext) for ext in ('.c', '.cpp')]
        source = next(p for p in sources if p.exists())
        value, size, info, section = linked[name]
        if value != address or info & 15 != 2 or section in (0, 0xFFF1) or size <= 0 or address + size > slot['end']:
            raise ValueError('Not a placed compiled function: ' + name)
        old = region(old_segments, address, slot['end'])
        new = region(new_segments, address, slot['end'])
        changed = sum(a != b for a, b in zip(old, new))
        scope = ('compile/placement only; behavior tests deferred by user' if slot['object'] in ('svo3/CQueryParams', 'svo3/CPluginBase', 'svo3/PageHistory', 'svo3/SVChronograph', 'svo3/SVSock', 'svo3/UTF8_Util', 'svo3/HttpUtils', 'svo3/DNSCache', 'svo3/CCookie', 'svo3/SVTagModuleList', 'svo3/CPluginManager', 'svo3/SVURIStore', 'svo3/URISchemeMgr', 'svo3/SVTag', 'svo3/LogoutTag', 'svo3/BrowserInitTag', 'svo3/RedirectTag', 'svo3/LineTag', 'svo3/RectangleTag', 'svo3/DownloadBinary', 'svo3/ParseXML', 'svo3/ParseSVMLAddObjects', 'svo3/ParseSVMLForDownloads', 'svo3/ParseXMLInfo', 'svo3/PageRequestListener', 'svo3/SVFileDownloadQueue', 'svo3/TagUtils', 'svo3/SVBrowser', 'svo3/buttonTag', 'svo3/CheckboxInputTag', 'svo3/CHttp', 'svo3/HttpSecure', 'svo3/SetVariableTag', 'svo3/TextTag', 'svo3/TickerTag', 'svo3/CDrawContextBase', 'svo3/FormTag', 'svo3/HiddenInputTag', 'svo3/PopupTag', 'svo3/QuickLinkTag', 'svo3/SubmitInputTag', 'svo3/DataTag', 'svo3/ImageTag', 'svo3/PageIDTag', 'svo3/RadioInputTag', 'svo3/SelectTag', 'svo3/StaticImageTag', 'svo3/TextInputTag', 'svo3/CPage', 'svo3/CreateGameTagModule', 'svo3/GenericListBoxTag', 'svo3/ListBoxTag', 'svo3/LoginTagModule', 'svo3/Navigation', 'svo3/RTCommSock', 'svo3/SVDownloadManager', 'svo3/SVO_DBG', 'svo3/SVTagModule', 'svo3/TextAreaTag', 'svo3/ImageTagModule', 'svo3/DataTagModule') or slot['object'].endswith('TagModule') else
                 'check_svo_config.py; EE file/XML callback cases' if slot['object'] == 'svo3/CConfig' else
                 'check_svo_string.py; EE differential cases and two retained exact matches' if slot['object'] == 'svo3/SVOString' else
                 'check_svo_input.py; EE maps and callback cases' if slot['object'] == 'svo3/CInputContextBase' else
                 'check_svo_memory.py; EE allocation/chunk/callback cases' if slot['object'] == 'svo3/CMemoryContextBase' else
                 'check_svo_core.py; EE error and context callback cases' if slot['object'] in ('svo3/CError', 'svo3/CSystemContextBase', 'svo3/CAudioContextBase') else
                 'check_iksemel.py; exact module bytes and EE differential cases' if name in ('iks_next', 'iks_parent', 'iks_child', 'iks_type', 'iks_name', 'iks_cdata') else
                 '989snd differential suites; mocked SDK/IOP' if name.startswith('snd_') else
                 'boot_main_test.cpp; host mocks' if name == 'main' else 'boot_options_test.cpp; host vectors' if name in ('GetBootOptionsFromSettings', 'ApplyBootOptionsToSettings') else 'not inventoried')
        rows.append(dict(name=name, source=source.relative_to(game).as_posix(), address='0x%08X' % address,
                         implementation='compiled', slot_end='0x%08X' % slot['end'], compiled_size='0x%X' % size,
                         slot_match='nonmatching' if changed else 'matching', differing_bytes=changed,
                         test_scope=scope, question='Match compiler output and slot padding.' if changed else
                         'Slot bytes match; retain ABI checks and test in-game.'))
    keys = set()
    for row in rows:
        key = row['source'] + ':' + row['name']
        if key in keys:
            raise ValueError('Duplicate function in source: ' + key)
        keys.add(key)
        row['notes'] = notes.get(key, '')
    rows.sort(key=lambda r: (int(r['address'], 16) if r['address'] else 0x100000000, r['source'], r['name']))
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('game', choices=['dl'])
    parser.add_argument('--elf', type=Path)
    parser.add_argument('--output', type=Path, help='Defaults to GAME/build/progress; overwrites generated CSV/summary only')
    args = parser.parse_args()
    game = GAMES / args.game
    original = GAMES / 'assets' / args.game / 'boot_elf.elf'
    rebuilt = args.elf or game / 'build/boot_elf.elf'
    output = args.output or game / 'build/progress'
    rows = inventory(game, original, rebuilt)
    output.mkdir(parents=True, exist_ok=True)
    with (output / 'FUNCTIONS.csv').open('w', newline='', encoding='utf-8') as stream:
        writer = csv.DictWriter(stream, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    summary = dict(generated_utc=datetime.now(timezone.utc).isoformat(), game=args.game,
                   original_sha256=sha256(original), rebuilt_sha256=sha256(rebuilt),
                   source_functions=len(rows), assembly=sum(r['implementation']=='assembly' for r in rows),
                   compiled=sum(r['implementation']=='compiled' for r in rows),
                   matching_slots=sum(r['slot_match']=='matching' for r in rows),
                   nonmatching_slots=sum(r['slot_match']=='nonmatching' for r in rows),
                   scope='Source INCLUDE_ASM entries and manifest replacements only; not a complete retail symbol inventory. Test scope names suites, not proof of a new run.')
    (output / 'SUMMARY.json').write_text(json.dumps(summary, indent=2) + '\n')
    print('Progress: %(assembly)d assembly, %(compiled)d compiled, %(matching_slots)d matching compiled slots, %(nonmatching_slots)d nonmatching compiled slots' % summary)


if __name__ == '__main__':
    main()
