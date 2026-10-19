"""Legacy six-instruction loop compatibility for SN compiler assembly.

Input is compiler assembly only; no reference ELF, address map, function list,
or original instructions are consulted. Requires the pinned SN GNU assembler
with -EL -G8 -g. Unsupported loops are retained with diagnostics.
This is a compatibility profile, not the modern R5900 hardware erratum fix.
"""
import argparse
import re
from pathlib import Path

BRANCHES = {'b', 'beq', 'bne', 'beqz', 'bnez', 'bgez', 'bltz', 'bgtz', 'blez'}
REG_NAMES = dict(zip(('zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra').split(), range(32)))
REG_NAMES['s8'] = 30

def reg(s):
    if not s.startswith('$'):
        return None
    s = s[1:]
    if s.isdigit() and 0 <= int(s) < 32:
        return int(s)
    return REG_NAMES.get(s)

def number(s):
    try:
        return int(s, 0)
    except ValueError:
        return None

def single_word(op, args, small_symbols=()):
    a = [x.strip() for x in args.split(',')] if args else []
    if op in {'lb', 'lbu', 'lh', 'lhu', 'lw', 'lwu', 'ld', 'sb', 'sh', 'sw', 'sd'}:
        if len(a) != 2 or reg(a[0]) is None:
            return False
        memory = re.fullmatch(r'(-?(?:0x[0-9a-fA-F]+|[0-9]+))\((\$[a-zA-Z0-9]+)\)', a[1])
        if memory:
            return reg(memory[2]) is not None and -32768 <= number(memory[1]) <= 32767
        return a[1] in small_symbols
    if op == 'nop':
        return not a
    if op == 'move':
        return len(a) == 2 and all(reg(x) is not None for x in a)
    if op == 'jal':
        return len(a) == 1 and bool(re.fullmatch(r'[A-Za-z_.$][\w.$]*', a[0]))
    if op in {'addu', 'subu', 'and', 'or', 'xor', 'slt', 'sltu'}:
        if len(a) != 3 or any(reg(x) is None for x in a[:2]):
            return False
        if reg(a[2]) is not None:
            return True
        n = number(a[2])
        if n is None:
            return False
        # The compiler uses addu for an addiu immediate. Subu negates it.
        return (op == 'addu' and -32768 <= n <= 32767) or (op == 'subu' and -32768 <= -n <= 32767)
    if op in {'addiu', 'slti', 'sltiu', 'andi', 'ori', 'xori'}:
        if len(a) != 3 or any(reg(x) is None for x in a[:2]):
            return False
        n = number(a[2])
        return n is not None and ((0 <= n <= 65535) if op in {'andi', 'ori', 'xori'} else (-32768 <= n <= 32767))
    return False

def branch_word(op, args):
    a = [x.strip() for x in args.split(',')]
    if not a or not re.fullmatch(r'[A-Za-z_.$][\w.$]*', a[-1]):
        return None
    if op == 'b' and len(a) == 1:
        return 0x10000000, a[-1]
    if op in {'beq', 'bne'} and len(a) == 3 and all(reg(x) is not None for x in a[:2]):
        return ((4 if op == 'beq' else 5) << 26) | (reg(a[0]) << 21) | (reg(a[1]) << 16), a[-1]
    if op in {'beqz', 'bnez', 'bgez', 'bltz', 'bgtz', 'blez'} and len(a) == 2 and reg(a[0]) is not None:
        base = {'beqz': 4 << 26, 'bnez': 5 << 26, 'bgez': (1 << 26) | (1 << 16), 'bltz': 1 << 26, 'bgtz': 7 << 26, 'blez': 6 << 26}[op]
        return base | (reg(a[0]) << 21), a[-1]
    return None

def adapt(source):
    # The pinned GNU assembler uses -G8. Only sized externs without offsets
    # can be proven to expand to a single GP-relative memory instruction.
    small_symbols = {name for name, size in re.findall(
        r'^\s*\.extern\s+([A-Za-z_.$][\w.$]*)\s*,\s*(\d+)\s*$', source, re.M)
        if 0 < int(size) <= 8}
    lines = source.splitlines()
    parsed = []
    reorder = True
    section = 0
    labels = {}
    for i, line in enumerate(lines):
        s = line.split('#', 1)[0].strip()
        if s.startswith(('.section ', '.section\t', '.text', '.data', '.bss')):
            section += 1
        if re.fullmatch(r'\.set\s+noreorder', s):
            reorder = False
        elif re.fullmatch(r'\.set\s+reorder', s):
            reorder = True
        if s.endswith(':'):
            labels[(section, s[:-1])] = i
        parts = s.split(None, 1)
        parsed.append((s, parts[0] if parts else '', parts[1] if len(parts) > 1 else '', reorder, section))
    edits = {}
    diagnostics = []
    for i, (s, op, args, reorder, section) in enumerate(parsed):
        if op not in BRANCHES:
            continue
        encoded = branch_word(op, args)
        if encoded is None:
            diagnostics.append(f'line {i+1}: unsupported branch operands; unchanged')
            continue
        word, target = encoded
        start = labels.get((section, target))
        if start is None or start >= i:
            continue
        count = 0
        reason = None
        for j in range(start+1, i):
            text, instr, operands, mode, _ = parsed[j]
            if not text or text.endswith(':') or re.fullmatch(r'\.set\s+(?:no)?(?:reorder|macro)', text):
                continue
            if not single_word(instr, operands, small_symbols):
                reason = f'unsupported instruction/directive {instr}'
                break
            count += 1 + int(instr == 'jal' and mode)
        if reason is None and not reorder:
            # An explicit delay instruction must exist and be exactly one word.
            j = i+1
            while j < len(parsed) and (not parsed[j][0] or re.fullmatch(r'\.set\s+(?:no)?macro', parsed[j][0])):
                j += 1
            if j >= len(parsed) or parsed[j][4] != section or parsed[j][3] or not single_word(parsed[j][1], parsed[j][2], small_symbols) or parsed[j][1] == 'jal':
                reason = 'unproven explicit branch delay instruction'
        if reason is not None:
            diagnostics.append(f'line {i+1}: {target}: {reason}; unchanged')
            continue
        count += 2  # branch itself and its explicit or assembler-generated delay
        if count > 6:
            continue
        padding = 6-count
        prefix = ['\tnop'] * padding
        # The label-relative expression is assembled from compiler control flow.
        # It prevents GNU as from silently changing a six-word legacy loop to seven.
        branch = f'\t.word 0x{word:08x} | ((({target} - . - 4) / 4) & 0xffff)'
        if reorder:
            edits[i] = prefix + ['\t.set noreorder', branch, '\tnop', '\t.set reorder']
        else:
            edits[i] = prefix + [branch]
        diagnostics.append(f'line {i+1}: {target}: normalized {count} to 6 instructions')
    output = '\n'.join('\n'.join(edits.get(i, [line])) for i, line in enumerate(lines)) + '\n'
    return output, diagnostics

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('input', type=Path)
    parser.add_argument('output', type=Path)
    parser.add_argument('--verbose', action='store_true')
    args = parser.parse_args()
    output, diagnostics = adapt(args.input.read_text())
    args.output.write_text(output)
    print('Legacy loop profile: %d short loops normalized' %
          sum('normalized ' in item for item in diagnostics))
    if args.verbose:
        for diagnostic in diagnostics:
            print(diagnostic)

if __name__ == '__main__':
    main()
