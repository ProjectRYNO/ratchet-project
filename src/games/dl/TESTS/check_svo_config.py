#!/usr/bin/env python3
"""SVO config loader EE differential checks with file/XML/libc mocks."""
import re
import sys
from test_989snd_wrappers import WrapperMachine, MASK, signed
from check_main_elf import symbols
from compare_elf import read_elf

BASE=0x01800000
FILENAME=BASE+0x200
IP=BASE+0x400
PATH=BASE+0x600
PORT=BASE+0x900
PARSER=BASE+0xC00
NODE=BASE+0xD00


class AssertStop(Exception):
    pass


class ConfigMachine(WrapperMachine):
    max_steps=10000

    def __init__(self,image,linked,args,descriptor=3,length=12,node=True,ip=b'127.0.0.1',path=b'index.xml',port=b'1234',stop_assert=True,read_result=12):
        self.storage=bytearray([0x55]*0x2000)
        super().__init__(image,{},args+[0]*max(0,8-len(args)),0)
        self.linked=linked
        self.descriptor=descriptor
        self.length=length
        self.node=node
        self.fields={b'ip':(IP,ip),b'path':(PATH,path),b'port':(PORT,port)}
        self.stop_assert=stop_assert
        self.read_result=read_result
        self.node_output=0
        self.data_pointer=0
        self.put(FILENAME,b'config.xml\0')
        for address,value in self.fields.values():
            if value is not None:
                self.put(address,value+b'\0')

    def read(self,address,size):
        address&=0xffffffff
        if BASE<=address and address+size<=BASE+len(self.storage):
            return int.from_bytes(self.storage[address-BASE:address-BASE+size],'little')
        return super().read(address,size)

    def write(self,address,value,size):
        address&=0xffffffff
        if BASE<=address and address+size<=BASE+len(self.storage):
            self.storage[address-BASE:address-BASE+size]=(value&((1<<(8*size))-1)).to_bytes(size,'little')
        else:
            super().write(address,value,size)

    def put(self,address,data):
        for i,v in enumerate(data):
            self.write(address+i,v,1)

    def string(self,address):
        result=bytearray()
        while self.read(address+len(result),1):
            result.append(self.read(address+len(result),1))
            assert len(result)<4096
        return bytes(result)

    def intercept(self,pc):
        names=('memset','sprintf','sceOpen','sceLseek','sceRead','sceClose','iks_dom_new',
               'iks_parse','iks_find_cdata','iks_parser_delete','iks_delete','atoi','__SVO_Assert_Handler')
        name=next((n for n in names if pc==self.linked[n][0]),None)
        if name is None:
            return False
        a,b,c,d=(self.reg[i]&0xffffffff for i in (4,5,6,7))
        if name=='memset':
            assert b==0 and c in (64,256,4096)
            if c==4096:
                self.data_pointer=a
                self.calls.append(('memset-data',c))
            else:
                assert self.read(BASE+64,4)==0xffffffff and self.read(BASE+324,4)==0
                self.calls.append(('memset-config',a-BASE,c))
            self.put(a,bytes(c))
            result=a
        elif name=='sprintf':
            assert b==0x19c378 and self.string(b)==b'%s%s'
            assert c==self.read(0x16e418,4) and d==FILENAME
            value=self.string(c)+self.string(d)
            self.put(a,value+b'\0')
            self.calls.append(('sprintf',value))
            result=len(value)
        elif name=='sceOpen':
            self.calls.append(('open',self.string(a),b))
            result=self.descriptor
        elif name=='sceLseek':
            assert a==self.descriptor and b==0 and c in (0,2)
            self.calls.append(('seek',c))
            result=self.length if c==2 else 0
        elif name=='sceRead':
            assert a==self.descriptor and b==self.data_pointer
            assert c==self.length&0xffffffff
            self.calls.append(('read',signed(c,32)))
            result=self.read_result
        elif name=='sceClose':
            assert a==self.descriptor
            self.calls.append(('close',a))
            result=0
        elif name=='iks_dom_new':
            assert self.read(a,4)==0
            self.node_output=a
            self.calls.append(('dom-new',))
            result=PARSER
        elif name=='iks_parse':
            assert a==PARSER and b==self.data_pointer and c==0 and d==1
            self.write(self.node_output,NODE if self.node else 0,4)
            self.calls.append(('parse',))
            result=0
        elif name=='iks_find_cdata':
            assert a==NODE
            key=self.string(b)
            self.calls.append(('field',key))
            address,value=self.fields[key]
            result=address if value is not None else 0
        elif name=='iks_parser_delete':
            assert a==PARSER and self.read(BASE+324,4)==0x55555555
            self.calls.append(('parser-delete',))
            result=0
        elif name=='iks_delete':
            assert a==NODE and self.read(BASE+324,4)==0x55555555
            self.calls.append(('node-delete',))
            result=0
        elif name=='atoi':
            assert a==PORT
            text=self.string(a)
            self.calls.append(('atoi',text))
            match=re.match(rb'[0-9]+',text)
            result=int(match[0]) if match else 0
        else:
            assert a in (0x19c380,0x19c3a8)
            self.calls.append(('assert',a,b))
            if self.stop_assert:
                raise AssertStop()
            result=0
        for i in [2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25]:
            self.reg[i]=0xbad00000+i
        self.reg[2]=signed(result,32)&MASK
        return True


def main():
    if len(sys.argv)!=3:
        raise SystemExit('usage: check_svo_config.py ORIGINAL REBUILT')
    old,new=sys.argv[1:]
    linked=symbols(new)
    for name in ('CConfig','loadConfigurationFile'):
        assert linked[name][2]&15==2 and linked[name][3] not in (0,0xfff1),name
        assert name+'.NON_MATCHING' not in linked,name
    images=[read_elf(p)[1] for p in (old,new)]
    for image in images:
        m=ConfigMachine(image,linked,[BASE])
        before=bytes(m.storage)
        calls,result=m.run(linked['CConfig'][0])
        assert calls==[('memset-config',68,256),('memset-config',0,64)] and result==BASE
        assert m.storage[:64]==bytes(64) and m.read(BASE+64,4)==0xffffffff
        assert m.storage[68:328]==bytes(260)
        assert m.storage[328:]==before[328:]
    cases=[]
    for length in (1,12,4095):
        for port in (b'0',b'65535',b'123trailing',b'2147483647'):
            cases.append((dict(length=length,port=port),None))
    cases += [(dict(descriptor=-1),None),(dict(read_result=-1),None)]
    for length in (-1,0,4096):
        cases.append((dict(length=length),('assert',0x19c380,0x48 if length<=0 else 0x4b)))
        cases.append((dict(length=length,stop_assert=False),None))
    cases += [(dict(node=False),('assert',0x19c380,0x7e)),
              (dict(ip=None),('assert',0x19c380,0x84)),
              (dict(path=None),('assert',0x19c3a8,0x1e)),
              (dict(ip=b'x'*64),('assert',0x19c3a8,0x28)),
              (dict(path=b'x'*256),('assert',0x19c3a8,0x28))]
    for port in (None,b'',b'-1',b' 1',b'abc',b'\xff'):
        cases.append((dict(port=port),('assert',0x19c380,0x8c)))
    for options,assertion in cases:
        results=[]
        for image in images:
            m=ConfigMachine(image,linked,[BASE,FILENAME],**options)
            result=None
            try:
                _,result=m.run(linked['loadConfigurationFile'][0])
            except AssertStop:
                assert assertion and m.calls[-1]==assertion,(options,m.calls)
            else:
                assert assertion is None,(options,m.calls)
                assert result==(0 if m.descriptor<0 else 1)
                if result:
                    assert m.string(BASE)==m.fields[b'ip'][1]
                    assert m.string(BASE+68)==m.fields[b'path'][1]
                    assert m.read(BASE+324,4)==1
                    assert m.calls[-2:]==[('parser-delete',),('node-delete',)]
                    expected_port=int(re.match(rb'[0-9]+',m.fields[b'port'][1])[0])
                    assert m.read(BASE+64,4)==expected_port
                    assert [call[0] for call in m.calls if call[0]!='assert']==[
                        'memset-data','sprintf','open','seek','seek','read','close',
                        'dom-new','parse','field','field','field','atoi','parser-delete','node-delete']
                    expected_asserts=[]
                    if m.length<=0:
                        expected_asserts=[('assert',0x19c380,0x48)]
                    elif m.length>=4096:
                        expected_asserts=[('assert',0x19c380,0x4b),('assert',0x19c380,0x4f)]
                    assert [call for call in m.calls if call[0]=='assert']==expected_asserts
                else:
                    assert m.storage[:328]==bytes([0x55]*328)
            results.append((result,m.calls,bytes(m.storage)))
        assert results[0]==results[1],options
    print('PASS: constructor and %d config load/error cases (original/rebuilt EE; file/XML/libc mocks)' % len(cases))


if __name__=='__main__':
    main()
