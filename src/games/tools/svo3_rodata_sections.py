#!/usr/bin/env python3
"""Give each SVO3/iksemel/Medius function's read-only data (its switch jump tables) its own section.

ee-gcc 2.96 writes every jump table to the shared `.rdata` section. Retail keeps each
function's tables at a fixed address in the main read-only data, so the linker must be able
to place them per function. Inside `.section .svo_<Module>_<fn>`, a `.rdata` directive is
rewritten to `.section .svo_<Module>_<fn>.rodata`. Table contents, alignment and order are
unchanged. Iksemel `.iks_<fn>` and Medius `.medius_<module>_<fn>` sections use the same
convention; subsequent tables receive `.rodata.1`, `.rodata.2`, etc., so retail inter-table
padding remains in its original data section. SVO3 routing is unchanged. A top-level `.rdata`
block of string literals (gcc does not always write it next to its user) goes to the
`.rodata` section of the one Medius function that references its labels.
Unregistered sections are discarded by the linker script, so a table without a
registered rodata slot fails the link instead of being placed silently.
"""
import re
import sys


def literal_owner(lines, start):
    """Medius function section that uses the labels defined in an `.rdata` block."""
    labels = []
    for line in lines[start + 1:]:
        if re.match(r'\s*\.(?:section|text|data|bss|rdata)\b', line):
            break
        match = re.match(r'(\$L\w+):', line)
        if match:
            labels.append(match[1])
    if not labels:
        return None
    pattern = re.compile(r'(?<![\w$])(?:%s)(?!\w)' % '|'.join(re.escape(l) for l in labels))
    owners = set()
    section = None
    for line in lines:
        match = re.match(r'\s*\.section\s+([^,\s]+)', line)
        if match:
            section = match[1]
        elif re.match(r'\s*\.(?:text|data|bss|rdata)\b', line):
            section = None
        elif section and section.startswith('.medius_') and not section.endswith('.rodata') \
                and pattern.search(line):
            owners.add(section)
    if len(owners) != 1:
        return None
    return owners.pop()


def rewrite(text):
    current = None
    out = []
    table_counts = {}
    lines = text.splitlines(keepends=True)
    for number, line in enumerate(lines):
        if (current is None or current.startswith('.medius_')) and re.match(r'\s*\.rdata\s*$', line):
            # gcc does not always write string literals next to their user; follow the labels.
            owner = literal_owner(lines, number)
            if owner:
                index = table_counts.get(owner, 0)
                table_counts[owner] = index + 1
                suffix = f'.{index}' if index else ''
                out.append(f'\t.section {owner}.rodata{suffix},"a",@progbits\n')
                continue
        match = re.match(r'\s*\.section\s+(\.(?:svo|iks|medius)_[^,\s]+)', line)
        if match:
            current = match[1]
        elif re.match(r'\s*\.(?:text|data|bss)\b', line):
            current = None
        elif (match := re.match(r'\s*lw\s+(\$\d+),(\$L\d+)\((\$\d+)\)\s*$', line)) and current:
            # Sony as 2.10-ee sometimes encodes the first instruction of this macro as `lw`
            # instead of `lui` (it depends on the preceding instruction), which loads from a
            # garbage address at runtime. Write out the expansion the macro is meant to produce.
            dest, table, index = match.groups()
            if current.startswith('.medius_') and dest != index:
                # Retail Medius builds the table address in the destination register.
                line = (f'\tlui\t{dest},%hi({table})\n\taddu\t{dest},{dest},{index}\n'
                        f'\tlw\t{dest},%lo({table})({dest})\n')
            else:
                line = (f'\t.set\tnoat\n\tlui\t$1,%hi({table})\n\taddu\t$1,$1,{index}\n'
                        f'\tlw\t{dest},%lo({table})($1)\n\t.set\tat\n')
        elif re.match(r'\s*\.rdata\s*$', line) and current:
            index = table_counts.get(current, 0)
            table_counts[current] = index + 1
            # iks_escape has two tables separated by retail padding.
            suffix = f'.{index}' if not current.startswith('.svo_') and index else ''
            line = f'\t.section {current}.rodata{suffix},"a",@progbits\n'
        out.append(line)
    return "".join(out)


def main():
    path = sys.argv[1]
    with open(path, encoding="utf-8") as f:
        text = f.read()
    new = rewrite(text)
    if new != text:
        with open(path, "w", encoding="utf-8", newline="\n") as f:
            f.write(new)


if __name__ == "__main__":
    main()
