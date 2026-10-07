#!/usr/bin/env python3
"""Differential EE checks for SVO memory context and chunk bookkeeping."""
import sys
from test_989snd_wrappers import WrapperMachine, STACK, MASK, signed
from check_main_elf import symbols
from compare_elf import read_elf

BASE=0x01800000
LENGTH=0x10420
VTABLE=STACK-0x1800
TEXT=STACK-0x1000
ALLOC=0x1ffff100
FREE=0x1ffff104
IDCOUNT=0x16e444
NAMES=['_CMemoryContextBase','CMemoryContextBase','svAllocSafe','svFreeSafe',
       'InitMemChunks','Cleanup','Init___dupe39','EnsureCleanBlocks']


class MemoryMachine(WrapperMachine):
    max_steps=300000

    def __init__(self,image,linked,args,allocation=BASE+0x100,callback_increment=0):
        self.storage=bytearray((i*19+7)&255 for i in range(LENGTH))
        self.id_count=123
        super().__init__(image,{},args+[0]*max(0,8-len(args)),0)
        self.linked=linked
        self.allocation=allocation
        self.callback_increment=callback_increment
        self.write(BASE+0x1041c,VTABLE,4)
        self.write(VTABLE+12,ALLOC,4)
        self.write(VTABLE+16,FREE,4)

    def read(self,address,size):
        address&=0xffffffff
        if BASE<=address and address+size<=BASE+LENGTH:
            return int.from_bytes(self.storage[address-BASE:address-BASE+size],'little')
        if address==IDCOUNT:
            assert size==4
            return self.id_count
        return super().read(address,size)

    def write(self,address,value,size):
        address&=0xffffffff
        if BASE<=address and address+size<=BASE+LENGTH:
            self.storage[address-BASE:address-BASE+size]=(value&((1<<(8*size))-1)).to_bytes(size,'little')
        elif address==IDCOUNT:
            assert size==4
            self.id_count=value&0xffffffff
        else:
            super().write(address,value,size)

    def put(self,address,data):
        for i,byte in enumerate(data):
            self.write(address+i,byte,1)

    def string(self,address):
        result=bytearray()
        while self.read(address+len(result),1):
            result.append(self.read(address+len(result),1))
            assert len(result)<2048
        return bytes(result)

    def intercept(self,pc):
        a,b,c=(self.reg[i]&0xffffffff for i in (4,5,6))
        if pc==ALLOC:
            assert a==BASE
            previous=self.read(BASE+0x10414,4)
            self.calls.append(('alloc',b,c,previous))
            self.write(BASE+0x10414,previous+self.callback_increment,4)
            result=self.allocation
        elif pc==FREE:
            assert a==BASE
            previous=self.read(BASE+0x10418,4)
            self.calls.append(('free',b,previous))
            self.write(BASE+0x10418,previous+self.callback_increment,4)
            result=0
        elif pc==self.linked['__builtin_delete'][0]:
            assert a==BASE and self.read(BASE+0x1041c,4)==0x16fe68
            assert self.read(BASE+0x10410,4)==0,'cleanup must precede delete'
            self.calls.append(('delete',a))
            result=0
        elif pc==self.linked['__SVO_Assert_Handler'][0]:
            assert a in (0x19c540,0x19c3a8)
            self.calls.append(('assert',a,b))
            result=0
        elif pc==self.linked['strlen'][0]:
            result=len(self.string(a))
        elif pc==self.linked['strcmp'][0]:
            x,y=self.string(a),self.string(b)
            result=(x>y)-(x<y)
        elif pc==self.linked['memset'][0]:
            assert c<=32
            self.put(a,bytes([b&255])*c)
            result=a
        elif pc==self.linked['strncpy'][0]:
            assert c==31
            data=self.string(b)[:c]
            self.put(a,data+bytes(c-len(data)))
            result=a
        else:
            return False
        for i in [2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25]:
            self.reg[i]=0xbad00000+i
        self.reg[2]=signed(result,32)&MASK
        return True


def main():
    if len(sys.argv)!=3:
        raise SystemExit('usage: check_svo_memory.py ORIGINAL REBUILT')
    old,new=sys.argv[1:]
    linked=symbols(new)
    for name in NAMES:
        assert linked[name][2]&15==2 and linked[name][3] not in (0,0xfff1),name
        assert name+'.NON_MATCHING' not in linked,name
    images=[read_elf(p)[1] for p in (old,new)]
    count=0
    for size in (0,1,32,0xfffffff8,0xffffffff):
        for align in (0,1,4,5,16,255,256,0xffffffff):
            for initial in (0,0xffffffff):
                for allocation in (0,BASE+0x100):
                    for image in images:
                        m=MemoryMachine(image,linked,[BASE,signed(size,32)&MASK,signed(align,32)&MASK,999,TEXT],allocation,7)
                        m.write(BASE+0x10414,initial,4)
                        before=bytes(m.storage)
                        calls,result=m.run(linked['svAllocSafe'][0])
                        expected=[] if align<256 else [('assert',0x19c540,0x52)]
                        expected.append(('alloc',(size+max(align,4)*2)&0xffffffff,align,initial))
                        assert result==allocation and calls==expected,(size,align,initial,calls)
                        assert m.read(BASE+0x10414,4)==(initial+8)&0xffffffff
                        assert m.storage[:0x10414]==before[:0x10414] and m.storage[0x10418:]==before[0x10418:]
                    count+=1
    for initial in (0,17,0xffffffff):
        for pointer in (0,BASE+0x100):
            for image in images:
                m=MemoryMachine(image,linked,[BASE,pointer],callback_increment=7)
                m.write(BASE+0x10418,initial,4)
                before=bytes(m.storage)
                calls,_=m.run(linked['svFreeSafe'][0])
                assert calls==[('free',pointer,initial)]
                assert m.read(BASE+0x10418,4)==(initial+8)&0xffffffff
                assert m.storage[:0x10418]==before[:0x10418] and m.storage[0x1041c:]==before[0x1041c:]
            count+=1
    for prefix,text in [(b'x'*64,b'abcdefghijklmnopqrstuvwxyz0123456789'),
                        (b'x'*40+b"free'd\0"+b'x'*17,b'short!'),
                        (b'x'*40+b'NOT SET\0'+b'x'*16,b'short!'),
                        (b'x'*64,b''),(b'x'*64,b'a')]:
        for initial in (123,0xffffffff):
            results=[]
            for image in images:
                m=MemoryMachine(image,linked,[BASE,0x1234,BASE+0x100,TEXT+64])
                m.id_count=initial
                m.put(TEXT,prefix+text+b'\0')
                # The retail tail pointer can precede file; model those actual surrounding bytes.
                expected_name=m.string(TEXT+64+len(text)-30)
                before=bytes(m.storage)
                calls,_=m.run(linked['Init___dupe39'][0])
                expected_calls=[('assert',0x19c540,0x1e2)] if expected_name==b'NOT SET' else []
                assert calls==expected_calls
                assert m.read(BASE,4)==0 and m.read(BASE+4,4)==BASE+0x100 and m.read(BASE+8,4)==0x1234
                assert m.string(BASE+12)==expected_name
                assert m.storage[44:48]==before[44:48] and m.storage[52:]==before[52:]
                assert m.read(BASE+48,4)==(0xffffffff if expected_name==b"free'd" else initial)
                assert m.id_count==(initial if expected_name==b"free'd" else (initial+1)&0xffffffff)
                results.append((bytes(m.storage),m.id_count,calls))
            assert results[0]==results[1]
            count+=1
    for name in ('InitMemChunks','CMemoryContextBase'):
        results=[]
        for image in images:
            m=MemoryMachine(image,linked,[BASE])
            before=bytes(m.storage)
            calls,_=m.run(linked[name][0])
            assert not calls and m.id_count==123+640
            assert m.read(BASE+0x10404,4)==0
            assert m.storage[0x8204:0x10404]==before[0x8204:0x10404]
            for i in range(640):
                chunk=BASE+4+i*52
                assert m.read(chunk,12)==0 and m.read(chunk+48,4)==123+i
                assert m.read(chunk+44,4)==int.from_bytes(before[4+i*52+44:4+i*52+48],'little')
            if name=='CMemoryContextBase':
                assert m.read(BASE,4)==0 and m.read(BASE+0x1041c,4)==0x16fe68
                assert m.storage[0x10408:0x1041c]==bytes(20)
            else:
                assert m.storage[:4]==before[:4] and m.storage[0x10408:]==before[0x10408:]
            results.append((bytes(m.storage),m.id_count))
        assert results[0]==results[1]
        count+=1
    for image in images:
        for flags in (0,1,2,3,0xffffffff):
            m=MemoryMachine(image,linked,[BASE,signed(flags,32)&MASK])
            before=bytes(m.storage)
            calls,_=m.run(linked['_CMemoryContextBase'][0])
            assert calls==([('delete',BASE)] if flags&1 else [])
            assert m.read(BASE+0x10410,4)==0 and m.read(BASE+0x1041c,4)==0x16fe68
            assert m.storage[:0x10410]==before[:0x10410] and m.storage[0x10414:0x1041c]==before[0x10414:0x1041c]
        m=MemoryMachine(image,linked,[BASE])
        before=bytes(m.storage)
        calls,result=m.run(linked['EnsureCleanBlocks'][0])
        assert not calls and result==1 and m.storage==before
        calls,_=m.run(linked['Cleanup'][0])
        assert not calls and m.read(BASE+0x10410,4)==0
        assert m.storage[:0x10410]==before[:0x10410] and m.storage[0x10414:]==before[0x10414:]
    print('PASS: %d allocation/free/chunk cases plus destructor/cleanup; full 640-chunk initialization (original/rebuilt EE)' % count)


if __name__=='__main__':
    main()
