#!/usr/bin/env python3
"""Historical newlib source/compiler research; never substitutes retail bytes."""
from pathlib import Path
import re,json,subprocess,os,struct,argparse
from elftools.elf.elffile import ELFFile
GAMES=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser(description="Diagnostic libm compiler fingerprint comparison. Relocation-masked differences are NOT an exact-match result; use check_libm.py on a linked ELF.")
parser.add_argument('--newlib',type=Path,required=True,help='extracted release newlib directory containing libc/ and libm/')
parser.add_argument('--output',type=Path,required=True)
parser.add_argument('--compiler',choices=['sony29','sn136'],default='sn136')
parser.add_argument('--functions',nargs='*')
parser.add_argument('--original',type=Path,default=GAMES/'assets/dl/boot.elf')
args=parser.parse_args()
out=args.output;out.mkdir(parents=True,exist_ok=True)
inventory=json.loads((GAMES/'dl/DOCS/progress/LIBM.json').read_text())['functions']
if args.functions:inventory=[r for r in inventory if r['name'] in args.functions]
syms={r['name']:int(r['address'],16) for r in inventory}
names=list(syms);mapfiles=[Path(r['upstream']).stem for r in inventory]
with args.original.open('rb') as f:
 e=ELFFile(f);segments=[(s['p_vaddr'],s.data()) for s in e.iter_segments() if s['p_type']=='PT_LOAD']
def retail(a,n):return next(d[a-b:a-b+n] for b,d in segments if b<=a and a+n<=b+len(d))
ccs={'sony29':['/opt/ee-gcc2.9-990721/bin/ee-gcc'],'sn136':['/opt/wibo-1.2.0','/opt/ee-gcc2.95.3-136/bin/ee-gcc.exe']}
assemblers={'sony29':['/opt/ee-gcc2.9-990721/ee/bin/as'],'sn136':['/opt/wibo-1.2.0','/opt/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe']}
env=dict(os.environ,LD_PRELOAD='/opt/ee-gcc2.96/ee296_statshim.so');results=[]
for v in [args.newlib.parent.name]:
 src=args.newlib;inc=['-I'+str(src/'libm/common'),'-I'+str(src/'libc/include'),'-isystem','/opt/ps2dev/ee/lib/gcc-lib/ee/3.2.3/include','-isystem','/opt/ps2dev/ee/ee/include']
 for cc,cmd in ccs.items():
  if cc != args.compiler:continue
  for name,file in zip(names,mapfiles):
   path=next(p for p in (src/'libm').rglob(file+'.c') if p.parent.name in ('common','math'));tag=v+'-'+cc+'-'+file;asm=out/(tag+'.s');obj=out/(tag+'.o')
   r=subprocess.run(cmd+['-S','-O2','-G0','-fno-builtin',*inc,str(path),'-o',str(asm)],env=env,capture_output=True,text=True)
   if r.returncode:print('ERR',tag,r.stderr[-600:]);continue
   r=subprocess.run(assemblers[cc]+['-EL','-G0',str(asm),'-o',str(obj)],env=env,capture_output=True,text=True)
   if r.returncode:print('ASERR',tag,r.stderr[-600:]);continue
   with obj.open('rb') as f:
    e=ELFFile(f);s=e.get_section_by_name('.symtab').get_symbol_by_name(name)[0];sec=e.get_section(s['st_shndx']);data=bytearray(sec.data()[s['st_value']:s['st_value']+s['st_size']]);orig=bytearray(retail(syms[name],len(data)));rels=[]
    for rs in e.iter_sections():
     if rs['sh_type']=='SHT_REL' and rs['sh_info']==s['st_shndx']:
      for r in rs.iter_relocations():
       off=r['r_offset']-s['st_value'];typ=r['r_info_type'];symbol=e.get_section(rs['sh_link']).get_symbol(r['r_info_sym']);rels.append(dict(off=off,type=typ,symbol=symbol.name,section=symbol['st_shndx'],value=symbol['st_value']))
       if typ in (5,6,7):data[off:off+2]=b'\0\0';orig[off:off+2]=b'\0\0'
       elif typ==4:data[off:off+3]=b'\0'*3;orig[off:off+3]=b'\0'*3;data[off+3]&=252;orig[off+3]&=252
    diff=sum(a!=b for a,b in zip(data,orig));result=dict(version=v,compiler=cc,file=str(path.relative_to(src/'libm')),function=name,address=syms[name],size=len(data),normalized_differences=diff,relocations=rels);results.append(result);print(name,cc,len(data),'normalized diff',diff,flush=True)
(out/'results.json').write_text(json.dumps(results,indent=2))
