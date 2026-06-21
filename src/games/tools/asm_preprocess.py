#!/usr/bin/env python3
import re
import sys


INTERNAL_FUNC_RE = re.compile(r"\bfunc_([0-9A-Fa-f]{8})\b")


def bytes_directive(hex_bytes):
    parts = [hex_bytes[i : i + 2] for i in range(0, len(hex_bytes), 2)]
    return ".byte " + ", ".join(f"0x{part}" for part in parts)


def preprocess_line(line, local_internal_funcs=False):
    if local_internal_funcs:
        line = re.sub(r"^(\s*)alabel\s+func_([0-9A-Fa-f]{8})\s*$", r"\1.L\2:", line)
        line = INTERNAL_FUNC_RE.sub(lambda match: f".L{match.group(1).upper()}", line)

    line = re.sub(
        r"^(\s*(?:nonmatching|glabel|endlabel)\s+)~([A-Za-z_][A-Za-z0-9_]*)\b",
        r"\1__dt__\2",
        line,
    )

    if "*/" not in line:
        return line

    comment, insn = line.split("*/", 1)
    stripped_insn = insn.lstrip()
    if not stripped_insn.startswith("v") or (
        "ACC," not in stripped_insn
        and "Q" not in stripped_insn
        and "R" not in stripped_insn
        and "I" not in stripped_insn
    ):
        return line

    words = comment.replace("/*", " ").split()
    if not words:
        return line

    # binutils' mips assembler does not accept some PS2 VU accumulator
    # operand spellings emitted by splat. The disassembly comment has the
    # original little-endian instruction bytes, so emit those directly.
    indent = line[: len(line) - len(line.lstrip())]
    return f"{indent}{bytes_directive(words[-1])}\n"


def main():
    inputs = [open(path, "r", encoding="utf-8") for path in sys.argv[1:]]
    if not inputs:
        inputs = [sys.stdin]

    try:
        for stream in inputs:
            name = getattr(stream, "name", "")
            local_internal_funcs = name.replace("\\", "/").endswith("/crt0.s")
            for line in stream:
                line = re.sub(r"^\s*\.ent\b.*", "", line)
                line = re.sub(r"^\s*\.end\b.*", "", line)
                sys.stdout.write(preprocess_line(line, local_internal_funcs))
    finally:
        for stream in inputs:
            if stream is not sys.stdin:
                stream.close()


if __name__ == "__main__":
    main()
