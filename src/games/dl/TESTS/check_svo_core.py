#!/usr/bin/env python3
"""Differential EE checks for recovered SVO3 core callbacks and error state."""
import sys
from test_989snd_wrappers import WrapperMachine, STACK, MASK, signed
from check_main_elf import symbols
from compare_elf import read_elf
if len(sys.argv) != 3:
    raise SystemExit('usage: check_svo_core.py ORIGINAL REBUILT')
OLD, NEW = sys.argv[1:]
SYMS=symbols(NEW)
ERROR=0x21d9b0
assert SYMS['svoErrorCode'][0]==ERROR
assert SYMS['svoSystemContextSource'][0]==0x19c2d8
assert SYMS['svoAudioContextVtable'][0]==0x16fe00
CONTEXT=STACK-0x1000
VTABLE=STACK-0x1100
CALLBACK=0x1fffff00
class Machine(WrapperMachine):
    def __init__(self, segments, args, error=0, browser=True, context=True):
        super().__init__(segments,{},args+[0]*(8-len(args)),0)
        self.error=error & 0xffffffff
        self.browser=browser
        self.context=context
        self.write(CONTEXT+16,VTABLE,4)
        self.write(VTABLE+12,CALLBACK,4)
    def read(self,addr,size):
        if addr==ERROR:
            assert size==4
            return self.error
        return super().read(addr,size)
    def write(self,addr,value,size):
        if addr==ERROR:
            assert size==4
            self.error=value & 0xffffffff
        else: super().write(addr,value,size)
    def intercept(self,pc):
        if pc==SYMS['GetInstance'][0]:
            self.calls.append(('instance',self.error)); result=int(self.browser)
        elif pc==SYMS['GetSystemContext'][0]:
            self.calls.append(('context',self.error)); result=CONTEXT if self.context else 0
        elif pc==CALLBACK:
            self.calls.append(('callback',self.reg[4]&0xffffffff,self.reg[5]&0xffffffff,self.error));result=0
        elif pc==SYMS['__SVO_Assert_Handler'][0]:
            self.calls.append(('assert',self.reg[4]&0xffffffff,self.reg[5]&0xffffffff));result=0
        else:return False
        for i in [2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25]:self.reg[i]=0xBAD00000+i
        self.reg[2]=result
        return True
for name in ('SetErrorCode','GetErrorCode','FileDownloadCallback','EnterStaticScreen','GetElapsedMS','OkToFreeFileDownloadBuffer','CAudioContextBase'):
    assert SYMS[name][2]&15 == 2 and SYMS[name][3] not in (0,0xfff1), name
    assert name+'.NON_MATCHING' not in SYMS, name
images=[read_elf(p)[1] for p in (OLD,NEW)]
count=0
for error in [0,1,38,0xffffffff]:
    for code in [0,1,38,0xffffffff,0x80000000]:
        for browser in (False,True):
            for context in (False,True):
                expected_error=code if error==0 and code!=0 else error
                expected=[]
                if error==0 and code!=0:
                    expected.append(('instance',code))
                    if browser:
                        expected.append(('context',code))
                        if context:expected.append(('callback',CONTEXT,code,code))
                for image in images:
                    m=Machine(image,[signed(code,32)&MASK],error,browser,context)
                    calls,_=m.run(SYMS['SetErrorCode'][0])
                    assert calls==expected and m.error==expected_error,(error,code,browser,context,calls,expected)
                    m=Machine(image,[],expected_error)
                    calls,result=m.run(SYMS['GetErrorCode'][0])
                    assert not calls and result==expected_error
                count+=1
for image in images:
    for name,line,result in [('FileDownloadCallback',None,None),('EnterStaticScreen',0xe0,None),('GetElapsedMS',0xe7,0),('OkToFreeFileDownloadBuffer',0xf8,1)]:
        m=Machine(image,[CONTEXT,0xdeadbeef])
        before={k:v for k,v in m.memory.items()}
        calls,actual=m.run(SYMS[name][0])
        assert calls==([] if line is None else [('assert',0x19c2d8,line)])
        if result is not None:assert actual==result
        assert all(m.memory[k]==v for k,v in before.items())
    m=Machine(image,[CONTEXT])
    calls,result=m.run(SYMS['CAudioContextBase'][0])
    assert not calls and result==0x16fe00 and m.read(CONTEXT,4)==0x16fe00
print('PASS',count,'error-state scenarios plus base-context callbacks and audio constructor; original/rebuilt EE')
