#!/usr/bin/env python3
"""Inventory retail Ghidra global labels against prototype declarations.

Addresses come exclusively from the retail export. Prototype declarations supply
names and provenance, never addresses. No files used by the build are modified.
"""
import argparse
from collections import Counter, defaultdict
import csv
import json
from pathlib import Path
import re
from compare_elf import read_elf


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--ghidra',type=Path,required=True)
    parser.add_argument('--prototype',type=Path,required=True)
    parser.add_argument('--game',type=Path,required=True)
    parser.add_argument('--elf',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args()
    args.output.mkdir(parents=True,exist_ok=True)
    declarations=defaultdict(list)
    source=''
    unparsed=[]
    struct_depth=0
    for line_no,line in enumerate((args.prototype/'dlglobals.txt').read_text(errors='replace').splitlines(),1):
        if line.startswith('// FILE -- '): source=line[len('// FILE -- '):].strip()
        declaration=re.sub(r'/\*.*?\*/','',line).strip()
        if not declaration or declaration.startswith('//'): continue
        if struct_depth or re.match(r'(?:typedef\s+)?(?:struct|union|enum)\b.*\{',declaration):
            struct_depth+=declaration.count('{')-declaration.count('}')
            continue
        match=re.search(r'\(\s*\*\s*([A-Za-z_][\w:$]*)(?:\[[^\]]*\])*\s*\)',declaration)
        if not match: match=re.search(r'\b([A-Za-z_][\w:$]*)\s*(?:\[[^\]]*\]\s*)*;',declaration)
        if not match:
            unparsed.append({'line':line_no,'declaration':line});continue
        declarations[match[1]].append({'source':source,'line':line_no,'declaration':line.strip()})
    source_files=defaultdict(list)
    for path in args.prototype.rglob('*'):
        if path.suffix in ('.c','.cpp','.h') and 'output' not in path.parts:
            source_files[path.name].append(path)
    cache={}
    def corroborate(name,entry):
        source=entry['source'].replace('\\','/')
        candidates=source_files[Path(source).name]
        if '/game/' in source:
            exact=args.prototype/'game_dl'/source.split('/game/',1)[1]
            candidates=[exact] if exact.is_file() else []
        elif '/989snd/' in source:
            exact=args.prototype/'989snd'/source.split('/989snd/',1)[1]
            candidates=[exact] if exact.is_file() else []
        hits=[]
        for path in candidates:
            if path not in cache: cache[path]=path.read_text(errors='replace').splitlines()
            for n,line in enumerate(cache[path],1):
                # Require the declared variable, not a substring or a function use.
                if re.match(r'^\s*'+re.escape(entry['declaration'].rsplit(name,1)[0])+re.escape(name)+r'\b',line):
                    hits.append('%s:%d'%(path.relative_to(args.prototype).as_posix(),n))
                    break
        return hits
    _,_,sections=read_elf(args.elf)
    data_sections=[(name,s[3],s[3]+s[5]) for name,s in sections if s[2]&2 and not s[2]&4 and s[5]]
    existing={}
    address_names=defaultdict(list)
    for path in (args.game/'config').glob('symbols*.txt'):
        for name,address in re.findall(r'^\s*([\w.$]+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;',path.read_text(),re.M):
            existing[name]=int(address,16);address_names[int(address,16)].append(name)
    labels=[]
    for line in args.ghidra.read_text(encoding='utf-8-sig').splitlines():
        m=re.match(r'(.+?) @ ([0-9a-fA-F]+) \[Label\](?: \((.*?)\))? xrefs=(\d+)$',line)
        if m: labels.append({'name':m[1],'value':int(m[2],16),'retail_type':m[3] or '', 'xrefs':int(m[4])})
    occurrences=Counter(label['name'] for label in labels)
    by_address=Counter(label['value'] for label in labels)
    rows=[]
    for label in labels:
        name,address=label['name'],label['value']
        entries=declarations.get(name,[])
        region=next((n for n,start,end in data_sections if start<=address<end),'')
        row={'name':name,'retail_address':'0x%08X'%address,'section':region,
             'retail_type':label['retail_type'],'xrefs':label['xrefs'],
             'prototype_declaration':' | '.join(e['declaration'] for e in entries),
             'prototype_source':' | '.join(e['source'] for e in entries),
             'dlglobals_lines':';'.join(str(e['line']) for e in entries),
             'prototype_matches':'','status':'deferred','reason':''}
        if not re.fullmatch(r'[A-Za-z_]\w*',name): row['reason']='not a plain C identifier'
        elif not region: row['reason']='outside allocated retail data sections'
        elif address==0x22597F: row['reason']='global-pointer base, not a verified object address'
        elif name in existing:
            row['status']='existing' if existing[name]==address else 'conflict'
            row['reason']='already in symbol files' if row['status']=='existing' else 'name has another configured address'
        elif address_names[address]:
            row['status']='existing_alias';row['reason']='already named '+', '.join(address_names[address])
        elif occurrences[name]!=1: row['reason']='retail name is not unique'
        elif by_address[address]!=1: row['reason']='multiple retail names share this address'
        elif len(entries)!=1: row['reason']='missing prototype declaration' if not entries else 'prototype name is not unique'
        elif not label['xrefs']: row['reason']='no retail references'
        else:
            hits=corroborate(name,entries[0]);row['prototype_matches']=' | '.join(hits)
            if not hits: row['reason']='prototype source declaration not corroborated'
            else: row['status']='candidate';row['reason']='unique retail data label and matching prototype declaration/source'
        rows.append(row)
    rows.sort(key=lambda r:(int(r['retail_address'],16),r['name']))
    with (args.output/'inventory.csv').open('w',newline='',encoding='utf-8') as out:
        writer=csv.DictWriter(out,fieldnames=rows[0].keys());writer.writeheader();writer.writerows(rows)
    candidates=[r for r in rows if r['status']=='candidate']
    (args.output/'candidates.json').write_text(json.dumps(candidates,indent=2))
    # Preserve the prototype-only backlog instead of inventing retail addresses.
    retail_names={r['name'] for r in rows}
    backlog=[{'name':name,**entry} for name,entries in declarations.items() if name not in retail_names for entry in entries]
    (args.output/'prototype-unmapped.json').write_text(json.dumps(backlog,indent=2))
    (args.output/'unparsed.json').write_text(json.dumps(unparsed,indent=2))
    print('Retail labels:',len(labels),'Prototype names:',len(declarations),'Unparsed declarations:',len(unparsed))
    print('Statuses:',dict(Counter(r['status'] for r in rows)))
    print('Deferred reasons:',dict(Counter(r['reason'] for r in rows if r['status']=='deferred')))
    print('Prototype entries without a retail label:',len(backlog))


if __name__=='__main__': main()
