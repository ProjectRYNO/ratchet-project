#!/usr/bin/env python3
"""Differential test of original and rebuilt EE wrapper machine code.

This deliberately small MIPS interpreter runs only the integer instructions in
these wrappers. It stops at the existing RPC transport and compares command IDs,
payload bytes, callbacks, and all 64 bits of user data. Unsupported instructions
fail the test; this is not a substitute for PS2/emulator audio testing.
"""
import argparse
from pathlib import Path
import random
import struct
import sys
import yaml

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
from compare_elf import read_elf
from check_main_elf import symbols

MASK = (1 << 64) - 1
STACK = 0x01FF0000
RETURN = 0xFFFFFF00

# These stateful functions have their own SDK/callback differential harness.
STATEFUL = set('''snd_StartSoundSystemEx snd_FlushSoundCommands snd_GotReturns
snd_PrepareReturnBuffer snd_BankLoadByLoc_CB snd_BankLoadFromEE
snd_SetMasterVolumeDucker snd_SendIOPCommandAndWait snd_SendIOPCommandNoWait
snd_PostMessage snd_SendCurrentBatch snd_InitVAGStreamingEx snd_CloseVAGStreaming
snd_StreamSafeCdRead snd_StreamSafeCdSync snd_StreamSafeCdBreak
snd_StreamSafeCdGetError snd_StreamSafeCdCallback snd_GetDopplerPitchMod'''.split())

def signed(value, bits):
    value &= (1 << bits) - 1
    return value - (1 << bits) if value & (1 << (bits - 1)) else value


class WrapperMachine:
    max_steps = 1000

    def intercept(self, pc):
        return False

    def __init__(self, segments, transports, arguments, seed):
        self.segments = segments
        self.transports = transports
        self.reg = [0] * 32
        self.fpr = [0] * 32  # Raw bits for variadic argument saves.
        for i in range(1, 32):
            self.reg[i] = (0x123456789ABCDEF0 + i * 0x11223344556677) & MASK
        self.reg[4:12] = arguments[:8]
        self.reg[29], self.reg[31] = STACK, RETURN
        self.memory = {}
        self.seed = seed
        for i, value in enumerate(arguments[8:]):
            self.write(STACK + i * 8, value, 8)
        self.calls = []

    def read(self, address, size):
        address &= 0xFFFFFFFF
        if STACK - 0x2000 <= address and address + size <= STACK + 0x1000:
            return int.from_bytes(bytes(self.memory.get(address+i, ((address+i)*37 ^ self.seed) & 255)
                                        for i in range(size)), 'little')
        for base, data in self.segments:
            if base <= address and address + size <= base + len(data):
                return int.from_bytes(data[address-base:address-base+size], 'little')
        raise AssertionError('unexpected read at %#x' % address)

    def write(self, address, value, size):
        address &= 0xFFFFFFFF
        assert STACK - 0x2000 <= address and address + size <= STACK + 0x1000
        for i in range(size):
            self.memory[address+i] = (value >> (8*i)) & 255

    def run(self, entry):
        pc, pending = entry, None
        preserved = {i: self.reg[i] for i in list(range(16,24)) + [28,29,30]}
        lo = hi = 0
        for _ in range(self.max_steps):
            if pc == RETURN:
                assert all(self.reg[i] == value for i,value in preserved.items()), 'callee-saved register changed'
                return self.calls, self.reg[2] & 0xFFFFFFFF
            if self.intercept(pc):
                pc = self.reg[31] & 0xFFFFFFFF
                continue
            if pc in self.transports:
                mode = self.transports[pc]
                command, length, pointer = [self.reg[i] & 0xFFFFFFFF for i in (4,5,6)]
                assert length <= 0x200, 'unexpected command length'
                # EXTERNCALLWITHDATA carries an EE pointer after its 12-byte header;
                # the transport dereferences it. Compare the descriptor, not unrelated memory.
                capture_size = 16 if command == 0x68 else length
                payload = bytes(self.read(pointer+i, 1) for i in range(capture_size))
                callback = self.reg[7] & 0xFFFFFFFF if mode == 'async' else None
                user_data = self.reg[8] if mode == 'async' else None
                self.calls.append((mode, command, length, payload, callback, user_data))
                self.reg[2] = signed(0xA5F00D12, 32) & MASK
                pc = self.reg[31] & 0xFFFFFFFF
                continue
            word = self.read(pc, 4)
            op, rs, rt, rd, sh, fn = word>>26, (word>>21)&31, (word>>16)&31, (word>>11)&31, (word>>6)&31, word&63
            imm = signed(word, 16)
            target, old_pending = None, pending
            r = self.reg
            if op == 0:
                if fn == 0: r[rd] = signed(r[rt] << sh, 32) & MASK
                elif fn == 2: r[rd] = signed((r[rt] & 0xFFFFFFFF) >> sh, 32) & MASK
                elif fn == 3: r[rd] = (signed(r[rt],32) >> sh) & MASK
                elif fn == 8: target = r[rs] & 0xFFFFFFFF
                elif fn == 9:
                    target = r[rs] & 0xFFFFFFFF
                    r[rd] = pc + 8
                elif fn == 0xA:
                    if r[rt] == 0: r[rd] = r[rs]
                elif fn == 0xB:
                    if r[rt] != 0: r[rd] = r[rs]
                elif fn == 0x10: r[rd] = hi
                elif fn == 0x12: r[rd] = lo
                elif fn in (0x18, 0x19):
                    value = (signed(r[rs],32)*signed(r[rt],32) if fn == 0x18
                             else (r[rs]&0xFFFFFFFF)*(r[rt]&0xFFFFFFFF))
                    lo, hi = signed(value,32)&MASK, signed(value>>32,32)&MASK
                    r[rd] = lo  # R5900 MULT also writes rd.
                elif fn in (0x1A, 0x1B):
                    a,b = (signed(r[rs],32),signed(r[rt],32)) if fn == 0x1A else (r[rs]&0xFFFFFFFF,r[rt]&0xFFFFFFFF)
                    assert b, 'division by zero'
                    q = abs(a)//abs(b) * (-1 if (a<0) != (b<0) else 1)
                    lo,hi = signed(q,32)&MASK,signed(a-q*b,32)&MASK
                elif fn == 0x21: r[rd] = signed(r[rs]+r[rt],32) & MASK
                elif fn == 0x23: r[rd] = signed(r[rs]-r[rt],32) & MASK
                elif fn == 0x24: r[rd] = r[rs] & r[rt]
                elif fn == 0x25: r[rd] = r[rs] | r[rt]
                elif fn == 0x26: r[rd] = r[rs] ^ r[rt]
                elif fn == 0x27: r[rd] = ~(r[rs] | r[rt]) & MASK
                elif fn == 0x2A: r[rd] = int(signed(r[rs],64) < signed(r[rt],64))
                elif fn == 0x2B: r[rd] = int(r[rs] < r[rt])
                elif fn == 0x2D: r[rd] = (r[rs]+r[rt]) & MASK
                elif fn == 0x38: r[rd] = (r[rt] << sh) & MASK
                else: raise AssertionError('unsupported SPECIAL %#x at %#x' % (word,pc))
            elif op in (2,3):
                target = ((pc+4)&0xF0000000) | ((word&0x3FFFFFF)<<2)
                if op == 3: r[31] = pc + 8
            elif op in (1,4,5,6,7,0x14,0x15,0x16,0x17):
                if op == 1:
                    assert rt in (0,1,2,3), 'unsupported REGIMM'
                    taken = signed(r[rs],64) < 0 if rt in (0,2) else signed(r[rs],64) >= 0
                    likely = rt in (2,3)
                else:
                    condition = op & 0xF
                    taken = {4:r[rs]==r[rt],5:r[rs]!=r[rt],6:signed(r[rs],64)<=0,7:signed(r[rs],64)>0}[condition]
                    likely = op >= 0x14
                if taken: target = pc+4+imm*4
                elif likely:
                    assert old_pending is None
                    pc += 8
                    pending = None
                    continue
            elif op == 9: r[rt] = signed(r[rs]+imm,32) & MASK
            elif op == 0x19: r[rt] = (r[rs]+imm) & MASK
            elif op == 0xC: r[rt] = r[rs] & (word&0xFFFF)
            elif op == 0xD: r[rt] = r[rs] | (word&0xFFFF)
            elif op == 0xE: r[rt] = r[rs] ^ (word&0xFFFF)
            elif op == 0xA: r[rt] = int(signed(r[rs],64) < imm)
            elif op == 0xB: r[rt] = int(r[rs] < (imm & MASK))
            elif op == 0xF: r[rt] = signed((word&0xFFFF)<<16,32) & MASK
            elif op == 0x23: r[rt] = signed(self.read(r[rs]+imm,4),32) & MASK
            elif op in (0x20,0x21,0x24,0x25):
                size = 1 if op in (0x20,0x24) else 2
                value = self.read(r[rs]+imm,size)
                r[rt] = (signed(value,size*8)&MASK) if op < 0x24 else value
            elif op == 0x27: r[rt] = self.read(r[rs]+imm,4)
            elif op == 0x37: r[rt] = self.read(r[rs]+imm,8)
            elif op == 0x2B: self.write(r[rs]+imm,r[rt],4)
            elif op in (0x28,0x29): self.write(r[rs]+imm,r[rt],1 if op==0x28 else 2)
            elif op in (0x1A,0x1B,0x2C,0x2D):
                address = (r[rs]+imm)&0xFFFFFFFF
                offset = address & 7
                if op in (0x1A,0x2C):
                    count,base,shift = offset+1,address-offset,(7-offset)*8
                else:
                    count,base,shift = 8-offset,address,0
                mask = ((1 << (count*8))-1) << shift
                if op in (0x1A,0x1B):
                    r[rt] = (r[rt]&~mask) | (self.read(base,count)<<shift)
                else: self.write(base,r[rt]>>shift,count)
            elif op == 0x39: self.write(r[rs]+imm,self.fpr[rt],4)  # SWC1
            elif op == 0x3F: self.write(r[rs]+imm,r[rt],8)
            else: raise AssertionError('unsupported instruction %#x at %#x' % (word,pc))
            r[0] = 0
            pc = old_pending if old_pending is not None else pc+4
            pending = target
        raise AssertionError('wrapper did not return')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('original')
    parser.add_argument('rebuilt')
    args = parser.parse_args()
    config = yaml.safe_load((Path(__file__).resolve().parents[1]/'config/decompiled_functions.yaml').read_text())
    functions = {n:a for n,a in config['functions'].items() if n.startswith('snd_') and n not in STATEFUL}
    linked = symbols(args.rebuilt)
    transports = {linked['snd_SendIOPCommandAndWait'][0]:'sync', linked['snd_SendIOPCommandNoWait'][0]:'async'}
    old = read_elf(args.original)[1]
    new = read_elf(args.rebuilt)[1]
    returns = {'snd_SoundIsStillPlaying','snd_SRAMGetFreeMem','snd_InitMovieSoundEx','snd_GetTransStatus',
               'snd_GetMovieNAX','snd_DoExternCall','snd_DoExternCallWithData'}
    randomizer = random.Random(989)
    count = 0
    for name,address in functions.items():
        for case in range(68):
            values = [randomizer.getrandbits(64) for _ in range(16)]
            if case < 4:
                values = [[0, MASK, 0x8000000080000000, 0x7FFFFFFF7FFFFFFF][case]]*16
            if name == 'snd_DoExternCallWithData':
                values[2] = [0,1,4,499,500][case%5]
            a = WrapperMachine(old,transports,values,case).run(address)
            b = WrapperMachine(new,transports,values,case).run(address)
            assert a[0] == b[0], '%s case %d: RPC mismatch\n%r\n%r' % (name,case,a[0],b[0])
            if name in returns:
                assert a[1] == b[1], '%s: return mismatch' % name
            count += 1
        print('PASS:',name)
    print('PASS: %d original-versus-compiled EE cases across %d functions' % (count,len(functions)))

if __name__ == '__main__':
    main()
