#!/usr/bin/env python3
import argparse
import re
from pathlib import Path

import yaml


COMMENT_RE = re.compile(r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/")
GLABEL_RE = re.compile(r"^\s*glabel\s+([A-Za-z_.$][A-Za-z0-9_.$]*)\s*$")
LOCAL_LABEL_RE = re.compile(r"\.L([0-9A-Fa-f]{8})")
SYMBOL_RE = re.compile(r"^\s*([A-Za-z_.$][A-Za-z0-9_.$]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate fallback addresses, never overriding object definitions.")
    parser.add_argument("--decompiled", type=Path)
    parser.add_argument("inputs", nargs="+")
    args = parser.parse_args()
    replacements = yaml.safe_load(args.decompiled.read_text()) if args.decompiled else {}
    excluded = set(replacements.get("functions", {})) | {"ENTRYPOINT"}

    definitions = {}

    asm_paths = []
    for arg in args.inputs:
        root = Path(arg)
        if not root.exists():
            continue
        if root.is_dir():
            asm_paths.extend(sorted(root.rglob("*.s")))
            continue

        for line in root.read_text(errors="ignore").splitlines():
            symbol = SYMBOL_RE.match(line)
            if symbol:
                if symbol.group(1) in excluded:
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
        if name not in excluded:
            print(f"PROVIDE({name} = 0x{definitions[name]:08X});")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
