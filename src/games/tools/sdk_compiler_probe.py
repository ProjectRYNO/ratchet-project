#!/usr/bin/env python3
"""Compare fixed SDK C probes against fully relocated Deadlocked retail bytes."""
import argparse, sys, os, json, subprocess
from pathlib import Path
games = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(games/'tools'))
from medius_compiler_probe import digest, loaded_bytes
from compare_elf import read_elf
sys.path.insert(0, str(games/'dl/TESTS'))
from check_main_elf import symbols
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--output', type=Path, required=True)
parser.add_argument('--source', type=Path, default=games/'dl/TESTS/sdk_compiler_probes.c')
parser.add_argument('--original', type=Path, default=games/'assets/dl/boot.elf')
parser.add_argument('--compiler', nargs=3, action='append', required=True, metavar=('NAME', 'CC', 'AS'))
parser.add_argument('--shim', type=Path, help='32-bit Sony LD_PRELOAD stat shim; used for compiler names starting with sony')
args = parser.parse_args()
root = args.output.resolve()
root.mkdir(parents=True, exist_ok=True)
source = args.source.resolve()
functions={'ezNetCtlSwapMessageTables':(0x1e9aa78,0x4c),'getMsgEntry':(0x1e9aac8,0x84),'cbFormatAuthMessage':(0x1e9acb0,0x48),'cbFormatPPPStatus':(0x1e9acf8,0x7c),'cbFormatPhoneNumber':(0x1e9ae30,0x18),'ezNetCnfGetCombination':(0x1e9a2b0,0xb0),'ezNetCtlDownInterface':(0x1e9a7c8,0x8c)}
bindings={'snprintf':0x11d878,'strncmp':0x11ae00,'scePrintf':0x1294f0,'sceSifCallRpc':0x12a718,'sdkErrorMessages':0x165f80,'sdkPhaseMessages':0x165f84,'sdkStateMessages':0x165f88,'sdkErrorEnglish':0x165d80,'sdkPhaseEnglish':0x165e20,'sdkStateEnglish':0x165f00,'sdkPPPprefix':0x1946a8,'sdkMessageLog':0x194678,'sdkMessageFunction':0x194680,'sdkMessageMissing':0x194690,'sdkCnfLog':0x193fe0,'sdkCnfFunction':0x1940f0,'sdkCnfEmpty':0x194108,'sdkCnfBadIndex':0x194118,'sdkCtlLog':0x1941b0,'sdkCtlFunction':0x194300,'sdkCtlNotRunning':0x194218,'sdkCtlRunning':0x1ad3ac,'sdkCtlClient':0x1ad380,'sdkCtlBuffer':0x1ad200,'_gp':0x22597f}
original=args.original.resolve()
_,segments,_=read_elf(original)
configs=args.compiler
report={'original_sha256':digest(original),'source_sha256':digest(source),'functions':functions,'bindings':bindings,'compilers':[],'results':[]}
for name,cc,assembler in configs:
 env=dict(os.environ)
 if name.startswith('sony') and args.shim:env['LD_PRELOAD']=str(args.shim.resolve())
 report['compilers'].append(dict(name=name,cc_sha256=digest(cc),assembler_sha256=digest(assembler),version=subprocess.check_output([cc,'--version'],env=env,text=True).strip(),assembler_version=subprocess.check_output([assembler,'--version'],env=env,text=True).strip()))
 for opt in ['O1','O2','Os','O3']:
  for split in ['default','no_split']:
   for alignment in ['default','minimal','eight']:
    flags=['-'+opt,'-G0','-fno-builtin','-fno-common','-ffunction-sections']
    if split=='no_split':flags+=['-mno-split-addresses']
    if alignment=='minimal':flags+=['-falign-functions=4','-falign-loops=1','-falign-jumps=1','-falign-labels=1']
    if alignment=='eight':flags+=['-falign-functions=8','-falign-loops=8','-falign-jumps=8','-falign-labels=1']
    folder=root/(name+'_'+opt+'_'+split+'_'+alignment);folder.mkdir(exist_ok=True)
    commands=[[cc,*flags,'-S',str(source),'-o',str(folder/'probe.s')],[assembler,'-EL','-G0',str(folder/'probe.s'),'-o',str(folder/'probe.o')],['mips-linux-gnu-strip','-x','-N','dummy-symbol-name',str(folder/'probe.o')]]
    with (folder/'commands.log').open('w') as log:
     for command in commands:
      log.write(repr(command)+'\n');log.flush();subprocess.run(command,env=env if command[0] in [cc,assembler] else None,stdout=log,stderr=subprocess.STDOUT,check=True)
     matched=[]
     for function,(address,size) in functions.items():
      script='SECTIONS { .text.%s 0x%x : { *(.text.%s) } /DISCARD/ : { *(.text.*) } }\n'%(function,address,function)+''.join('%s = 0x%x;\n'%(n,a) for n,a in bindings.items())
      ldfile=folder/(function+'.ld');ldfile.write_text(script)
      elf=folder/(function+'.elf')
      command=['mips-linux-gnu-ld','-EL','--no-warn-mismatch','-T',str(ldfile),str(folder/'probe.o'),'-o',str(elf)]
      log.write(repr(command)+'\n');log.flush();subprocess.run(command,stdout=log,stderr=subprocess.STDOUT,check=True)
      table=symbols(elf);_,compiled,_=read_elf(elf)
      actual_size=table[function][1];data=loaded_bytes(compiled,address,actual_size);reference=loaded_bytes(segments,address,size)
      exact=data==reference
      report['results'].append(dict(compiler=name,optimization=opt,split=split,alignment=alignment,function=function,size=actual_size,retail_size=size,exact=exact,equal_bytes=sum(a==b for a,b in zip(data,reference)),flags=flags))
      if exact:matched.append(function)
    if matched:print(folder.name,len(matched),','.join(matched),flush=True)
(root/'results.json').write_text(json.dumps(report,indent=2)+'\n')
