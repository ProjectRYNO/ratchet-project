#!/usr/bin/env python3
"""Give each SVO3 function's read-only data (its switch jump tables) its own section.

ee-gcc 2.96 writes every jump table to the shared `.rdata` section. Retail keeps each
function's tables at a fixed address in the main read-only data, so the linker must be able
to place them per function. Inside `.section .svo_<Module>_<fn>`, a `.rdata` directive is
rewritten to `.section .svo_<Module>_<fn>.rodata`. Table contents, alignment and order are
unchanged. Unregistered sections are discarded by the linker script, so a table without a
registered rodata slot fails the link instead of being placed silently.
"""
import re
import sys


def rewrite(text):
    current = None
    out = []
    for line in text.splitlines(keepends=True):
        match = re.match(r'\s*\.section\s+(\.svo_[^,\s]+)', line)
        if match:
            current = match[1]
        elif re.match(r'\s*\.(?:text|data|bss)\b', line):
            current = None
        elif re.match(r'\s*\.rdata\s*$', line) and current:
            line = f'\t.section {current}.rodata,"a",@progbits\n'
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
