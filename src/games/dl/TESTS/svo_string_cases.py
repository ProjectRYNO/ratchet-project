"""Copy/search/variadic behavior cases used by check_svo_string.py."""
from test_989snd_wrappers import WrapperMachine, STACK, MASK, signed

TEXT = STACK - 0x1000
DEST = STACK - 0x1800
SUBSTRING = STACK - 0x1400
VARARGS = [0x0123456789abcdef, 0xffffffffffffffff, 0x8000000000000000,
           0x1122334455667788, 0xaabbccddeeff0011, 0x12345678, 0, 0xfedcba9876543210]


class AssertStop(Exception):
    pass


class LibraryMachine(WrapperMachine):
    max_steps = 20000

    def __init__(self, segments, linked, arguments, stop_assert=False, formatted=0):
        super().__init__(segments, {}, arguments + [0]*max(0, 8-len(arguments)), 0)
        self.linked = linked
        self.stop_assert = stop_assert
        self.formatted = formatted
        self.fpr = [0x3f800000+i for i in range(32)]

    def bytes(self, address, count):
        return bytes(self.read(address+i, 1) for i in range(count))

    def put(self, address, data):
        for i, value in enumerate(data):
            self.write(address+i, value, 1)

    def string(self, address):
        data = bytearray()
        while self.read(address+len(data), 1):
            data.append(self.read(address+len(data), 1))
            assert len(data) < 2048
        return bytes(data)

    def intercept(self, pc):
        name = next((name for name in ('__SVO_Assert_Handler','strlen','strncmp','memset','vsprintf')
                     if pc == self.linked[name][0]), None)
        if not name:
            return False
        a,b,c = (self.reg[i]&0xffffffff for i in (4,5,6))
        if name == '__SVO_Assert_Handler':
            assert a == 0x19c3a8
            self.calls.append(('assert',b))
            if self.stop_assert:
                raise AssertStop()
            result = 0
        elif name == 'strlen':
            self.calls.append(('strlen',a))
            result = len(self.string(a))
        elif name == 'strncmp':
            self.calls.append(('strncmp',a,b,c))
            result = 0
            for i in range(c):
                x,y = self.read(a+i,1),self.read(b+i,1)
                if x != y:
                    result=x-y
                    break
                if not x:
                    break
        elif name == 'memset':
            assert a == DEST and b == 0 and c <= 64
            self.calls.append(('memset',a,b,c))
            self.put(a,bytes(c))
            result=a
        else:
            assert a == DEST and b == TEXT
            values = [self.read(c+i*8,8) for i in range(len(VARARGS))]
            assert values == VARARGS, ('variadic arguments',values)
            self.calls.append(('vsprintf',a,b,tuple(values)))
            self.put(a,b'formatted\0')
            result=self.formatted
        for i in [2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25]:
            self.reg[i]=0xbad00000+i
        self.reg[2]=signed(result,32)&MASK
        return True


def extended_cases(old, new, linked, functions):
    count=0
    for name in ('svstrncpy','svsubstrncpy'):
        for text in (b'',b'a',b'abcdef',bytes([255,128,1]),b'x'*64):
            for size in (0,1,2,3,6,7,32,64,65):
                expected=bytearray([0x55]*132)
                if size == 0:
                    expected[1]=0
                else:
                    copied=text[:size-1]+b'\0'
                    expected[2:2+len(copied)]=copied
                assertions=[]
                if size==0 and name=='svsubstrncpy':
                    assertions=[('assert',0x48)]
                if len(text)>=size and name=='svstrncpy':
                    assertions=[('assert',0x28)]
                for image in (old,new):
                    m=LibraryMachine(image,linked,[DEST,TEXT,size])
                    m.put(TEXT,text+b'\0')
                    m.put(DEST-2,bytes([0x55]*132))
                    calls,result=m.run(functions[name][0])
                    assert result==DEST and calls==assertions,(name,text,size,calls)
                    assert m.bytes(DEST-2,132)==expected,(name,text,size)
                    assert m.string(TEXT)==text
                count+=1
        invalid=[([DEST,0,2],0x1e if name=='svstrncpy' else 0x44),
                 ([0,TEXT,2],0x1f if name=='svstrncpy' else 0x45)]
        if name=='svstrncpy':
            invalid.append(([DEST,TEXT,0xa000],0x20))
        for arguments,line in invalid:
            for image in (old,new):
                m=LibraryMachine(image,linked,arguments,stop_assert=True)
                try:
                    m.run(functions[name][0])
                except AssertStop:
                    pass
                else:
                    raise AssertionError('missing assertion')
                assert m.calls==[('assert',line)]
            count+=1
    for text in (b'',b'abcdef',b'aaaaab',b'one two one',bytes([255,128,127])):
        for sub in (b'',b'a',b'abc',b'cde',b'ab',b'one',b'z',bytes([128,127])):
            expected=text.find(sub) if text else -1
            expected_calls=[('strlen',TEXT),('strlen',SUBSTRING)]
            for i in range(len(text)):
                expected_calls.append(('strncmp',TEXT+i,SUBSTRING,len(sub)))
                if text[i:i+len(sub)]==sub:
                    break
            for image in (old,new):
                m=LibraryMachine(image,linked,[TEXT,SUBSTRING])
                m.put(TEXT,text+b'\0')
                m.put(SUBSTRING,sub+b'\0')
                calls,result=m.run(functions['my_strcspn'][0])
                assert signed(result,32)==expected and calls==expected_calls,(text,sub,calls)
            count+=1
    for size in (0,1,8,16,64):
        for result in (-1,0,7,8,15,16,65):
            expected=[('memset',DEST,0,size),('vsprintf',DEST,TEXT,tuple(VARARGS))]
            if result == -1 or result >= size:
                expected.append(('assert',0x76))
            for image in (old,new):
                m=LibraryMachine(image,linked,[DEST,size,TEXT]+VARARGS,formatted=result)
                m.put(TEXT,b'%d\0')
                m.put(DEST,bytes([0x55]*80))
                calls,actual=m.run(functions['svsnprintf'][0])
                assert signed(actual,32)==result and calls==expected,(size,result,calls)
                expected_bytes=bytearray([0x55]*80)
                expected_bytes[:size]=bytes(size)
                expected_bytes[:10]=b'formatted\0'
                assert m.bytes(DEST,80)==expected_bytes
            count+=1
    for image in (old,new):
        m=LibraryMachine(image,linked,[0,8,TEXT]+VARARGS,stop_assert=True)
        try:
            m.run(functions['svsnprintf'][0])
        except AssertStop:
            pass
        else:
            raise AssertionError('missing null assertion')
        assert m.calls==[('assert',0x71)]
    return count+1
