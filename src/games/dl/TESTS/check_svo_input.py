#!/usr/bin/env python3
"""Retail-versus-rebuilt SVO input maps, callbacks, and constructor/destructor ABI."""
import sys
import random
from test_989snd_wrappers import WrapperMachine, STACK, MASK, signed
from check_main_elf import symbols
from compare_elf import read_elf

CONTEXT = STACK-0x1800
VTABLE = STACK-0x1400
MAP = STACK-0x1000
CALLBACK = 0x1ffff000
DEFAULTS = [0x1000,0x4000,0x8000,0x2000]+[0x20000]*4+[0x10000]*4+[4,8,1,2,0x40,0x10,0x40,0x20,0x10,0x80,4,1,2,0x10]
NAMES = ['_CAudioContextBase','CInputContextBase','DefineDefaultButtonMap',
         'SetDefaultButtonMap','HasActionOccurred','SetButtonMapForPage']


class InputMachine(WrapperMachine):
    max_steps = 3000

    def __init__(self, image, linked, args, value=0):
        super().__init__(image,{},args+[0]*max(0,8-len(args)),0)
        self.linked=linked
        self.value=value
        for i in range(0xDC):
            self.write(CONTEXT+i,(i*19+3)&255,1)
        self.write(CONTEXT+0xD8,VTABLE,4)
        for i in (3,5,6,7,8):
            self.write(VTABLE+i*4,CALLBACK+i*4,4)

    def snapshot(self):
        return bytes(self.read(CONTEXT+i,1) for i in range(0xDC))

    def intercept(self, pc):
        if pc==self.linked['__builtin_delete'][0]:
            assert self.read(CONTEXT,4)==0x16FE00, 'vtable must be reset before delete'
            self.calls.append(('delete',self.reg[4]&0xffffffff))
        elif pc in [CALLBACK+i*4 for i in (3,5,6,7,8)]:
            slot=(pc-CALLBACK)//4
            args=[slot,self.reg[4]&0xffffffff,self.reg[5]&0xffffffff]
            if slot==3:
                args.append(self.reg[6]&0xffffffff)
            self.calls.append(tuple(args))
        else:
            return False
        for i in [2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25]:
            self.reg[i]=0xbad00000+i
        self.reg[2]=signed(self.value,32)&MASK
        return True


def main():
    if len(sys.argv)!=3:
        raise SystemExit('usage: check_svo_input.py ORIGINAL REBUILT')
    original,rebuilt=sys.argv[1:]
    linked=symbols(rebuilt)
    for name in NAMES:
        assert linked[name][2]&15==2 and linked[name][3] not in (0,0xfff1),name
        assert name+'.NON_MATCHING' not in linked,name
    images=[read_elf(p)[1] for p in (original,rebuilt)]
    count=0
    for action in range(26):
        for button in (0,1,0x8000,0xFFFF,0x10000,0x20000,0xDEADFFFF):
            for value in (-128,-127,-1,0,1,127,128,-2147483648,2147483647):
                analog=4<=action<16 and button in (0x10000,0x20000)
                if analog:
                    vertical=action in (4,5,8,9)
                    slot=(8 if vertical else 6) if button==0x10000 else (7 if vertical else 5)
                    expected=min(value,0) if action%2==0 else max(value,0)
                    expected_call=(slot,CONTEXT,0x98765432)
                else:
                    expected=int(value!=0)
                    if 4<=action<16:
                        expected*=(-127 if action%2==0 else 127)
                    expected_call=(3,CONTEXT,0x98765432,button&0xffff)
                for image in images:
                    m=InputMachine(image,linked,[CONTEXT,signed(0x98765432,32)&MASK,action],value)
                    m.write(CONTEXT+0x70+action*4,button,4)
                    before=m.snapshot()
                    calls,result=m.run(linked['HasActionOccurred'][0])
                    assert calls==[expected_call] and signed(result,32)==expected,(action,button,value,calls,result)
                    assert m.snapshot()==before
                count+=1
    rng=random.Random(0x1eed628)
    for seed in range(16):
        values=[rng.getrandbits(32) for _ in range(26)]
        for image in images:
            for use_map in (False,True):
                m=InputMachine(image,linked,[CONTEXT,MAP if use_map else 0])
                for i,v in enumerate(values):
                    m.write(MAP+i*4,v,4)
                before=m.snapshot()
                calls,_=m.run(linked['DefineDefaultButtonMap'][0])
                assert not calls
                assert [m.read(CONTEXT+8+i*4,4) for i in range(26)]==(values if use_map else DEFAULTS)
                after=m.snapshot()
                assert before[:8]==after[:8] and before[0x70:]==after[0x70:]
            m=InputMachine(image,linked,[CONTEXT])
            for i,v in enumerate(values):
                m.write(CONTEXT+8+i*4,v,4)
            before=m.snapshot()
            calls,_=m.run(linked['SetDefaultButtonMap'][0])
            assert not calls and [m.read(CONTEXT+0x70+i*4,4) for i in range(26)]==values
            after=m.snapshot()
            assert before[:0x70]==after[:0x70] and before[0xD8:]==after[0xD8:]
        count+=3
    for image in images:
        m=InputMachine(image,linked,[CONTEXT])
        before=m.snapshot()
        calls,result=m.run(linked['CInputContextBase'][0])
        assert not calls and result==CONTEXT+100
        assert m.snapshot()[:8]==before[:8]
        assert m.snapshot()[8:0xD8]==bytes(0xD0)
        assert m.read(CONTEXT+0xD8,4)==0x16FE18
        m=InputMachine(image,linked,[CONTEXT,MAP])
        before=m.snapshot()
        calls,result=m.run(linked['SetButtonMapForPage'][0])
        assert not calls and result==0 and m.snapshot()==before
        for flags in (0,1,2,3,0xFFFFFFFF,0x80000000):
            m=InputMachine(image,linked,[CONTEXT,signed(flags,32)&MASK])
            before=m.snapshot()
            calls,_=m.run(linked['_CAudioContextBase'][0])
            assert calls==([('delete',CONTEXT)] if flags&1 else [])
            assert m.read(CONTEXT,4)==0x16FE00 and m.snapshot()[4:]==before[4:]
    print('PASS: %d input/map cases plus constructor, no-op, and 6 destructor cases (original/rebuilt EE)' % count)


if __name__=='__main__':
    main()
