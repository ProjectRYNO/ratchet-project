#!/usr/bin/env python3
import re
import sys
from pathlib import Path


COMMENT_RE = re.compile(r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/")
GLABEL_RE = re.compile(r"^\s*glabel\s+([A-Za-z_.$][A-Za-z0-9_.$]*)\s*$")
LOCAL_LABEL_RE = re.compile(r"\.L([0-9A-Fa-f]{8})")
SYMBOL_RE = re.compile(r"^\s*([A-Za-z_.$][A-Za-z0-9_.$]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")


def main() -> int:
    if len(sys.argv) < 2:
        print(f"usage: {Path(sys.argv[0]).name} ASM_DIR [ASM_DIR ...]", file=sys.stderr)
        return 2

    definitions = {}

    asm_paths = []
    for arg in sys.argv[1:]:
        root = Path(arg)
        if not root.exists():
            continue
        if root.is_dir():
            asm_paths.extend(sorted(root.rglob("*.s")))
            continue

        for line in root.read_text(errors="ignore").splitlines():
            symbol = SYMBOL_RE.match(line)
            if symbol:
                if symbol.group(1) == "ENTRYPOINT":
                    continue
                definitions.setdefault(symbol.group(1), int(symbol.group(2), 16))

    for path in asm_paths:
        lines = path.read_text(errors="ignore").splitlines()
        pending = []

        for line in lines:
            for local in LOCAL_LABEL_RE.findall(line):
                name = f".L{local.upper()}"
                definitions.setdefault(name, int(local, 16))

            glabel = GLABEL_RE.match(line)
            if glabel:
                pending.append(glabel.group(1))
                continue

            comment = COMMENT_RE.search(line)
            if comment and pending:
                addr = int(comment.group(1), 16)
                for name in pending:
                    definitions.setdefault(name, addr)
                pending.clear()

    for name in sorted(definitions):
        print(f"{name} = 0x{definitions[name]:08X};")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
