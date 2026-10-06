#!/usr/bin/env python3
"""Compare retail/recompiled stateful EE functions with deterministic SDK mocks.

Executes both actual ELF instruction streams. SDK/RPC completion is simulated;
this checks state, payloads, polling, cache calls and callback order, not IOP
timing or audible output. Unknown instructions and nonterminating paths fail.
"""
import argparse
from collections import Counter
from pathlib import Path
import random
import re
import yaml
from test_989snd_wrappers import (WrapperMachine, STATEFUL, STACK, MASK, signed,
                                  read_elf, symbols)

ROOT = Path(__file__).resolve().parents[1]
HEADER = (ROOT/'code/989snd/ee/989snd.h').read_text()
GLOBAL_NAMES = re.findall(r'extern[^;]*?\b(g\w+)(?:\[\d+\])?\s*;',HEADER)
SYMBOLS = {name:int(address,16) for name,address in re.findall(
    r'^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;',
    (ROOT/'config/symbols_core.text.txt').read_text(),re.M)}
GLOBALS = {name:SYMBOLS[name] for name in GLOBAL_NAMES}
CALLBACK, CD_CALLBACK, INPUT = 0x700000, 0x700100, 0x710000
RANGES = [(0x1BD480,0x1C2020),(0x21DCA8,0x21DD28),(0x21D9C0,0x21D9C4)]
SDK = '''sceSifInitRpc sceSifBindRpc sceSifCheckStatRpc sceSifCallRpc
FlushCache SyncDCache InvalidDCache sceCdRead sceCdSync sceCdBreak sceCdGetError
sceCdCallback printf memcpy'''.split()
VOID = set('''snd_StartSoundSystemEx snd_PrepareReturnBuffer snd_BankLoadByLoc_CB
snd_SetMasterVolumeDucker snd_SendIOPCommandNoWait snd_PostMessage
snd_SendCurrentBatch snd_CloseVAGStreaming'''.split())


class SoundMachine(WrapperMachine):
    max_steps = 500000

    def __init__(self,segments,linked,functions,name,args,options):
        super().__init__(segments,{},(args+[0]*16)[:16],989)
        self.reg[28] = linked['_gp'][0]
        self.hooks = {linked[n][0]:n for n in SDK}
        if not options.get('integrated'):
            self.hooks.update({a:n for n,a in functions.items() if n != name})
        self.hooks.update({CALLBACK:'callback',CD_CALLBACK:'cd_callback'})
        self.count = Counter()
        self.options = options
        self.name = name
        for start,end in RANGES:
            for address in range(start,end): self.memory[address] = 0
        for i in range(2):
            self.set('gSndCommandBuffePtr',GLOBALS['gSndCommandBuffer%d'%(i+1)],i*4)
            self.set('gSndCommandReturnDefPtr',GLOBALS['gSndCommandReturnDef%d'%(i+1)],i*4)
            self.set('gReturnValuesPtr',GLOBALS['gActualReturnValues%d'%(i+1)],i*4)
            self.set('gCommandBuffeBytesAvail',4092,i*4)
        self.set('gCdCallback',CD_CALLBACK)
        self.set('gLoadCB',CALLBACK)
        self.set('gLoadUserData',0xABCDEF0198765432,size=8)
        self.set('gLoadReturnDef',CALLBACK)
        self.set('gLoadReturnDef',0xFEDCBA9876543210,8,8)
        self.set('gSyncBuffer',0x10203040,4)
        for i in range(600): self.write(INPUT+i,(i*37+11)&255,1)
        # Descriptor used by EXTERNCALLWITHDATA.
        if options.get('external'):
            for i,value in enumerate((0x1234,0x5678,options['external'],INPUT+64)):
                self.write(INPUT+4*i,value,4)
        for key,value in options.get('globals',{}).items(): self.set(key,value)
        for key,offset,value,size in options.get('writes',[]): self.set(key,value,offset,size)

    def read(self,address,size):
        address &= 0xFFFFFFFF
        if all(address+i in self.memory for i in range(size)):
            return sum(self.memory[address+i] << (8*i) for i in range(size))
        return super().read(address,size)

    def write(self,address,value,size):
        address &= 0xFFFFFFFF
        assert (STACK-0x2000 <= address < STACK+0x1000 or
                INPUT <= address < INPUT+1024 or
                any(start <= address and address+size <= end for start,end in RANGES)), hex(address)
        for i in range(size): self.memory[address+i]=(value>>(8*i))&255

    def get(self,name,offset=0,size=4): return self.read(GLOBALS[name]+offset,size)
    def set(self,name,value,offset=0,size=4): self.write(GLOBALS[name]+offset,value,size)
    def blob(self,address,size): return bytes(self.read(address+i,1) for i in range(size))
    def snapshot(self): return tuple(self.blob(a,b-a) for a,b in RANGES)

    def intercept(self,pc):
        if pc not in self.hooks: return False
        name = self.hooks[pc]
        self.count[name] += 1
        n = self.count[name]
        a = [self.reg[i]&0xFFFFFFFF for i in range(4,12)]
        result = 0
        if name == 'sceSifInitRpc': self.calls.append((name,a[0]))
        elif name == 'sceSifBindRpc':
            self.calls.append((name,*a[:3]))
            self.write(a[0]+0x24,0 if n <= self.options.get('bind_wait',0) else 0x12345678,4)
        elif name == 'sceSifCheckStatRpc':
            self.calls.append((name,a[0]))
            result = int(n <= self.options.get('rpc_busy',0))
        elif name in ('SyncDCache','InvalidDCache'):
            self.calls.append((name,*a[:2]))
        elif name == 'FlushCache':
            self.calls.append((name,a[0]))
            if self.options.get('complete_cd') and n >= 2: self.set('gStats',0)
            if self.options.get('complete_load') and self.count['sceSifCallRpc']:
                self.set('gLoadReturnValue',0x345678)
        elif name == 'sceSifCallRpc':
            self.calls.append((name,*a[:3],self.blob(a[3],a[4]) if a[4] else b'',
                               a[4],a[5],a[6],a[7],self.read(self.reg[29],4)))
            result = self.options.get('rpc_result',0)
            if self.options.get('integrated') and result >= 0:
                if a[5] == GLOBALS['gLoadReturnValue']:
                    self.write(a[5],0x345678,4)
                else:
                    for offset in range(0,a[6],4): self.write(a[5]+offset,0x10203040+offset,4)
                    self.write(a[5],0xFFFFFFFF,4)
                    self.write(a[5]+a[6]-4,0xFFFFFFFF,4)
        elif name == 'memcpy':
            data = self.blob(a[1],a[2])
            for i,value in enumerate(data): self.write(a[0]+i,value,1)
            result = a[0]
        elif name == 'printf':
            # Message identity is stable; stack/register layout is not.
            self.calls.append((name,a[0]))
        elif name == 'snd_PrepareReturnBuffer':
            self.calls.append((name,*a[:2]))
            self.set('gCommBusy',a[0]); self.set('gAwaitingInts',a[1])
            self.write(a[0],0,4); self.write(a[0]+4*(a[1]+1),0,4)
        elif name == 'snd_GotReturns':
            self.calls.append((name,))
            result = int(n > self.options.get('returns_busy',0))
            if result: self.set('gCommBusy',0)
        elif name == 'snd_FlushSoundCommands':
            self.calls.append((name,self.get('gCaching')))
            if n > self.options.get('flush_busy',0):
                self.set('gCommBusy',0); self.set('gLoadBusy',0)
                which = self.get('gCommandFillBuffer')
                self.write(self.get('gSndCommandBuffePtr',which*4),0,4)
                self.set('gCommandBuffeBytesAvail',4092,which*4)
            else: result = 1
        elif name in ('snd_SendCurrentBatch','snd_PostMessage'):
            self.calls.append((name,self.get('gCommandFillBuffer'),self.get('gCaching')))
        elif name in ('snd_SendIOPCommandAndWait','snd_SendIOPCommandNoWait'):
            length = a[1]
            # NULL DuckerDef leaves the unused fields unspecified in retail too.
            if a[0] == 96 and self.read(a[2]+4,4) == 0xFFFFFFFF: length = 8
            self.calls.append((name,a[0],a[1],self.blob(a[2],length),
                               a[3] if name.endswith('NoWait') else None,
                               self.reg[8] if name.endswith('NoWait') else None))
            result = self.options.get('sync_result',0xA5F00D12)
        elif name == 'snd_StreamSafeCdSync':
            self.calls.append((name,a[0]))
            result = self.options.get('cd_sync',0)
            if self.options.get('cd_done'): self.set('gSSReadDone',1)
        elif name in ('callback','cd_callback'):
            self.calls.append((name,a[0],self.reg[5] if name=='callback' else None,
                self.get('gLoadReturnDef'),self.get('gLoadReturnDef',8,8),
                self.get('gLoadingFromFS'),self.get('gSSRead'),self.get('gSSReadDone')))
            if self.options.get('callback_mutates'):
                self.set('gLoadReturnDef',CALLBACK); self.set('gLoadReturnDef',0x123456789ABCDEF0,8,8)
                self.set('gLoadBusy',7); self.set('gLoadReturnValue',99)
        elif name in ('sceCdRead','sceCdSync','sceCdCallback','sceCdBreak','sceCdGetError'):
            argc = {'sceCdRead':4,'sceCdSync':1,'sceCdCallback':1}.get(name,0)
            self.calls.append((name,*a[:argc])); result = 0x12345
        else: raise AssertionError('unhandled call '+name)
        # ABI permits callers to lose all caller-saved integer registers.
        for register in list(range(2,16))+[24,25]: self.reg[register] = 0xBAD00000+register
        self.reg[2] = signed(result,32)&MASK
        return True


def cases():
    for flags in (0,1,2,3,0xFFFFFFFF):
        yield 'snd_StartSoundSystemEx',[flags],{'bind_wait':1}
    for busy in (0,1):
        for rpc in (0,1):
            for sentinels in (0,1,2,3):
                for silent in (0,1):
                    yield 'snd_GotReturns',[],{'rpc_busy':rpc,'globals':{
                        'gCommBusy':GLOBALS['gSyncBuffer'] if busy else 0,'gAwaitingInts':1,'gPrefs_Silent':silent},
                        'writes':[('gSyncBuffer',0,0xFFFFFFFF if sentinels&1 else 0,4),
                                  ('gSyncBuffer',8,0xFFFFFFFF if sentinels&2 else 0,4)]}
    for length in (0,1,2,255,256):
        yield 'snd_PrepareReturnBuffer',[GLOBALS['gActualReturnValues1'],length],{}
    for busy,sync,rpc in ((0,0,0),(1,0,0),(0,1,0),(0,0,2)):
        for silent in (0,1):
            yield 'snd_BankLoadByLoc_CB',[0x123456,0xABCDEF,CALLBACK,0xFEDCBA9876543210],{
                'globals':{'gLoadBusy':busy,'gPrefs_Silent':silent},'cd_sync':sync,'rpc_busy':rpc}
    for busy,result,rpc in ((0,0,0),(1,0,0),(0,-1,0),(0,0,2)):
        for silent in (0,1):
            yield 'snd_BankLoadFromEE',[INPUT],{'globals':{'gLoadBusy':busy,'gPrefs_Silent':silent},
                'rpc_result':result,'rpc_busy':rpc,'complete_load':True}
    for pointer in (0,INPUT): yield 'snd_SetMasterVolumeDucker',[3,pointer],{}
    for length in (0,1,3,4,7,32,508):
        for busy in (0,1):
            yield 'snd_SendIOPCommandAndWait',[12,length,INPUT],{'rpc_busy':busy,'returns_busy':busy,
                'globals':{'gCommBusy':GLOBALS['gSyncBuffer'] if busy else 0},
                'writes':[('gSndCommandBuffer1',0,2,4)]}
    for length in (1,4,499,500):
        yield 'snd_SendIOPCommandAndWait',[104,length+12,INPUT],{'external':length}
    for length in (0,1,3,4,7,32,508):
        for callback in (0,CALLBACK):
            for cache in (0,1):
                yield 'snd_SendIOPCommandNoWait',[12,length,INPUT,callback,0xFEDCBA9876543210],{
                    'globals':{'gCaching':cache}}
    for count,avail in ((256,4092),(1,4)):
        yield 'snd_SendIOPCommandNoWait',[12,32,INPUT,CALLBACK,0x123456789ABCDEF0],{
            'globals':{'gCaching':1},'writes':[('gSndCommandBuffer1',0,count,4),
                ('gCommandBuffeBytesAvail',0,avail,4)],'flush_busy':1}
    for length in (1,4,495,496):
        yield 'snd_SendIOPCommandNoWait',[104,length+12,INPUT,CALLBACK,0xABCDEF1234567890],{'external':length}
    for which in (0,1):
        yield 'snd_PostMessage',[],{'globals':{'gCommandFillBuffer':which}}
        for count in (1,2,256):
            yield 'snd_SendCurrentBatch',[],{'globals':{'gCommandFillBuffer':which},'rpc_busy':1,
                'writes':[('gSndCommandBuffer%d'%(which+1),0,count,4),
                          ('gCommandBuffeBytesAvail',which*4,4092-4*count,4)]}
    for streaming in (0,1,2):
        for busy in (0,1):
            options={'globals':{'gStreamingInited':streaming,'gLoadBusy':busy},'flush_busy':1}
            yield 'snd_InitVAGStreamingEx',[4,0x8000,3,1],options
            yield 'snd_CloseVAGStreaming',[],options
    for streaming in (0,1):
        for sync in (0,1):
            yield 'snd_StreamSafeCdRead',[0x123456,8,INPUT,INPUT+64],{
                'globals':{'gStreamingInited':streaming},'cd_sync':sync}
        for mode in (0,1,2):
            for busy in (0,1):
                yield 'snd_StreamSafeCdSync',[mode],{'globals':{'gStreamingInited':streaming,'gStats':busy},
                    'complete_cd':mode!=1}
        yield 'snd_StreamSafeCdBreak',[],{'globals':{'gStreamingInited':streaming}}
        yield 'snd_StreamSafeCdGetError',[],{'globals':{'gStreamingInited':streaming},'writes':[('gStats',16,0x32,4)]}
        for callback in (0,CALLBACK):
            yield 'snd_StreamSafeCdCallback',[callback],{'globals':{'gStreamingInited':streaming}}
    for mph in [0,1,-1,741,-741,0x7FFFFFFF,-0x80000000]+[random.Random(i).randint(-2**31,2**31-1) for i in range(100)]:
        yield 'snd_GetDopplerPitchMod',[signed(mph,32)&MASK],{}
    # Completion branches, including callback reentrancy and clearing order.
    for fs in (0,1):
        for complete in (0,1):
            for callback in (0,CALLBACK):
                for mutate in (False,True):
                    yield 'snd_FlushSoundCommands',[],{'globals':{'gCommBusy':GLOBALS['gSyncBuffer'],
                        'gLoadingFromFS':fs,'gLoadBusy':1,'gLoadReturnValue':123 if complete else 0xFFFFFFFF,
                        'gLoadCB':callback,'gSSRead':1},'returns_busy':1-complete,'cd_done':True,
                        'callback_mutates':mutate,'writes':[('gLoadReturnDef',0,callback,4),
                            ('gSndCommandBuffer2',0,2,4),('gSndCommandReturnDef2',0,callback,4),
                            ('gSndCommandReturnDef2',8,0xABCDEF0123456789,8),
                            ('gActualReturnValues2',4,0x1234,4)]}
    for cache in (0,1):
        yield 'snd_FlushSoundCommands',[],{'globals':{'gCaching':cache},'writes':[('gSndCommandBuffer1',0,2,4)]}
    # Run the real EE functions together, intercepting only SDK calls/callbacks.
    for name,args in (
        ('snd_StartSoundSystemEx',[2]),
        ('snd_BankLoadFromEE',[INPUT]),
        ('snd_BankLoadByLoc_CB',[123,456,CALLBACK,0xFEDCBA9876543210]),
        ('snd_SendIOPCommandAndWait',[12,32,INPUT]),
        ('snd_SendIOPCommandNoWait',[12,32,INPUT,CALLBACK,0xABCDEF0123456789]),
        ('snd_InitVAGStreamingEx',[4,0x8000,3,1]),
        ('snd_StreamSafeCdRead',[123,4,INPUT,INPUT+64]),
        ('snd_CloseVAGStreaming',[])):
        yield name,args,{'integrated':True,'complete_cd':True,
                         'globals':{'gStreamingInited':int(name in ('snd_StreamSafeCdRead','snd_CloseVAGStreaming'))}}
    for which in (0,1):
        for cache in (0,1):
            yield 'snd_FlushSoundCommands',[],{'integrated':True,
                'globals':{'gCommBusy':GLOBALS['gActualReturnValues%d'%(2-which)],
                    'gAwaitingInts':2,'gCommandFillBuffer':which,'gCaching':cache},
                'writes':[('gSndCommandBuffer%d'%(2-which),0,2,4),
                    ('gSndCommandReturnDef%d'%(2-which),0,CALLBACK,4),
                    ('gSndCommandReturnDef%d'%(2-which),8,0xFEDCBA9876543210,8),
                    ('gActualReturnValues%d'%(2-which),0,0xFFFFFFFF,4),
                    ('gActualReturnValues%d'%(2-which),4,123,4),
                    ('gActualReturnValues%d'%(2-which),12,0xFFFFFFFF,4),
                    ('gSndCommandBuffer%d'%(which+1),0,1,4),
                    ('gCommandBuffeBytesAvail',which*4,4088,4)]}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('original'); parser.add_argument('rebuilt')
    args=parser.parse_args()
    linked=symbols(args.rebuilt)
    for name,address in GLOBALS.items():
        assert linked[name][0] == address, 'global moved: '+name
    functions=yaml.safe_load((ROOT/'config/decompiled_functions.yaml').read_text())['functions']
    functions={n:a for n,a in functions.items() if n.startswith('snd_')}
    old,new=read_elf(args.original)[1],read_elf(args.rebuilt)[1]
    counts=Counter()
    for number,(name,arguments,options) in enumerate(cases()):
        machines=[SoundMachine(segments,linked,functions,name,arguments,options) for segments in (old,new)]
        try:
            results=[m.run(functions[name]) for m in machines]
            assert results[0][0]==results[1][0], 'call mismatch\n%r\n%r'%(results[0][0],results[1][0])
            if name not in VOID: assert results[0][1]==results[1][1], 'return mismatch: %r'%results
            if machines[0].snapshot()!=machines[1].snapshot():
                differences=[hex(a) for start,end in RANGES for a in range(start,end)
                             if machines[0].read(a,1)!=machines[1].read(a,1)]
                raise AssertionError('state mismatch: '+', '.join(differences[:30]))
        except Exception as error:
            raise AssertionError('case %d %s %r %r: %s'%(number,name,arguments,options,error)) from error
        counts[name]+=1
    assert set(counts)==STATEFUL, STATEFUL-set(counts)
    for name,count in counts.items(): print('PASS: %s (%d cases)'%(name,count))
    print('PASS: %d retail-versus-C stateful cases across %d functions'%(sum(counts.values()),len(counts)))


if __name__=='__main__': main()
