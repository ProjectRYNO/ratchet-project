#!/usr/bin/env python3
"""Run splat and preserve Deadlocked's instruction and ELF memory layout.

Only generated INCLUDE_ASM wrappers/empty stubs are refreshed. Files containing
actual C/C++ implementations are retained. Original wrappers are backed up once
under build/split_source_backup before splat regenerates them.
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

import yaml

from asm_preprocess import preprocess_line


def is_generated_wrapper(text):
    text = re.sub(r"/\*.*?\*/|//[^\n]*", "", text, flags=re.S)
    text = re.sub(r"INCLUDE_(?:ASM|RODATA)\([^;]*\);", "", text)
    text = re.sub(r"\bvoid\s+\w+\s*\(\s*(?:void)?\s*\)\s*\{\s*\}", "", text)
    text = re.sub(r'^\s*#include\s+"common.h"\s*$', "", text, flags=re.M)
    text = re.sub(r"^\s*#(?:ifdef ALLOW_NONMATCHING|else|endif)\s*$", "", text, flags=re.M)
    return not text.strip()


def normalize_assembly(text, crt0=False):
    # Splat's per-function .align 3 inserts bytes before functions that were
    # originally only four-byte aligned. The ROM already contains all padding.
    text = re.sub(r"^\.align 3$", ".align 2", text, flags=re.M)
    text = re.sub(r"^\s*\.(?:ent|end)\b[^\n]*", "", text, flags=re.M)
    text = "".join(preprocess_line(line, crt0) for line in text.splitlines(keepends=True))

    def branch(match):
        # EE binutils 2.14 cannot relocate bgezal to a symbol in another object.
        # Express its original PC-relative displacement as an assembler operand.
        word = int.from_bytes(bytes.fromhex(match[1]), "little")
        offset = word & 0xFFFF
        if offset & 0x8000:
            offset -= 0x10000
        return match[0].rsplit(",", 1)[0] + f", . + ({4 + 4 * offset})"

    return re.sub(r"/\*\s*\w+\s+\w+\s+(\w{8})\s*\*/\s+bgezal\s+[^\n]+", branch, text)


def runtime_linker_script(text, config, replacements=None):
    replacements = replacements or {}
    # Splat's AT(ROM offset) is for ROM images. A PS2 ELF needs physical load
    # addresses equal to virtual addresses, with two independent PT_LOADs.
    text = re.sub(r" AT\([^)]*\)", "", text)
    lines = ["PHDRS { main PT_LOAD FLAGS(7); net PT_LOAD FLAGS(7); }"]
    current = None
    for line in text.splitlines():
        for obj, bounds in replacements.get("objects", {}).items():
            if line.strip() == f"build/code/{obj}.o(.text*);":
                lines.append(f'        ASSERT(ABSOLUTE(.) == 0x{bounds["text_start"]:X}, "{obj} moved from its original address");')
                lines.append(line)
                for slot in bounds.get("slots", []):
                    lines.append(f'        ASSERT(ABSOLUTE(.) <= 0x{slot["start"]:X}, "code overlaps {slot["section"]}");')
                    lines.append(f'        . = ABSOLUTE(0x{slot["start"]:X});')
                    lines.append(f'        build/code/{slot["object"]}.o({slot["section"]});')
                    lines.append(f'        ASSERT(ABSOLUTE(.) <= 0x{slot["end"]:X}, "{slot["section"]} exceeds its original allocation");')
                    lines.append(f'        . = ABSOLUTE(0x{slot["end"]:X});')
                lines.append(f'        ASSERT(ABSOLUTE(.) <= 0x{bounds["text_end"]:X}, "{obj} exceeds its original allocation");')
                line = f'        . = ABSOLUTE(0x{bounds["text_end"]:X});'
        match = re.match(r"    (\.[\w]+)\s", line)
        if match:
            current = match[1]
        if line == "    }" and current:
            line += " :net" if current.startswith(".net_") else " :main"
            current = None
        lines.append(line)
    # Do not let --no-check-sections hide the kind of overflow that broke the
    # previous build. These are bounds, not copied bytes or forced entrypoints.
    assertions = []
    for name, address in replacements.get("functions", {}).items():
        assertions.append(f'ASSERT({name} == 0x{address:X}, "compiled {name} moved from its original address")')
    segments = config["segments"]
    for segment, following in zip(segments, segments[1:]):
        if segment["type"] in ("pad", "bss"):
            continue
        end = following["start"] if isinstance(following, dict) else following[0]
        section = "." + segment["name"].replace(".", "_")
        assertions.append(f'ASSERT(SIZEOF({section}) <= 0x{end-segment["start"]:X}, "{section} exceeds its original allocation")')
    return "\n".join(lines + assertions) + "\n"


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("config", type=Path)
    args = ap.parse_args()
    config_path = args.config.resolve()
    config = yaml.safe_load(config_path.read_text())
    replacements_path = config_path.parent / "decompiled_functions.yaml"
    replacements = yaml.safe_load(replacements_path.read_text()) if replacements_path.exists() else {}
    opts = config["options"]
    root = (config_path.parent / opts["base_path"]).resolve()
    src = root / opts["src_path"]
    refreshed = []
    for path in src.rglob("*"):
        if path.suffix not in (".c", ".cpp"):
            continue
        original = path.read_bytes()
        if not is_generated_wrapper(original.decode("utf-8")):
            continue
        backup = root / "build/split_source_backup" / path.relative_to(src)
        backup.parent.mkdir(parents=True, exist_ok=True)
        if not backup.exists():
            backup.write_bytes(original)
        refreshed.append((path, original))
        path.unlink()
    try:
        subprocess.run([sys.executable, "-m", "splat", "split", str(config_path), "--disassemble-all"], cwd=root, check=True)
    except BaseException:
        for path, original in refreshed:
            path.write_bytes(original)
        raise
    for path in (root / opts["asm_path"]).rglob("*.s"):
        original = path.read_text()
        normalized = normalize_assembly(original, path.name == "crt0.s")
        if normalized != original:
            path.write_text(normalized, newline="\n")
    linker = root / opts["ld_script_path"]
    linker.write_text(runtime_linker_script(linker.read_text(), config, replacements), newline="\n")
    print(f"Refreshed {len(refreshed)} generated wrappers; backups: build/split_source_backup")


if __name__ == "__main__":
    main()
