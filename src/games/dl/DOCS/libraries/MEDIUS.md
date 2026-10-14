# Deadlocked Medius compiler investigation

## Result (2026-10-13)

The strongest **tested** candidate is Sony SCE `ee-gcc 2.96-ee-001003-1`
with its bundled `GNU assembler 2.10-ee-001003-1`. Three recovered memory
functions now compile to all 184 original bytes, including relocated calls and
global references. This establishes a useful Medius toolchain, not the historical
compiler identity or a guarantee that every Medius component uses the same build.

Target: `src/games/dl`, USA retail `SCUS_974.65`, reference
`src/games/assets/dl/boot.elf`, SHA-256
`ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7`.
The initial Medius source inventory was 84 C files / 1,462 INCLUDE_ASM entries.
This batch replaces three; 1,459 remain. **Function progress: 3/1,462 = 0.21% decompiled and byte-matching.** Count only actual INCLUDE_ASM invocations, excluding macro definitions. Retained original assembly is not counted as decompiled progress.

## Controlled comparison

The same four C bodies were compiled at `-O1`, `-O2`, `-Os`, and `-O3`, with
`-G0`, no builtin substitution, four-byte function alignment, and one-byte
loop/jump/label alignment. Each compiler used its bundled assembler. Objects
were linked at retail addresses and compared to the original ELF's PT_LOAD
bytes without relocation masks. The fourth probe, `rt_strnlen`, remains
unmatched and is not integrated.

| Compiler | O1 | O2 | Os | O3 |
| --- | ---: | ---: | ---: | ---: |
| SCE 2.96-ee-001003-1 | 0/4 | **3/4** | **3/4** | **3/4** |
| SCE 3.2-ee-040921 | 0/4 | 0/4 | 0/4 | 0/4 |
| ps2dev GCC 3.2.3 | 0/4 | 1/4 | 1/4 | 0/4 |

The ps2dev match is only callback registration. The probes do not distinguish
O2 from Os/O3 for the three matching functions; O2 is the working selection.
Other Sony versions and SN/ProDG were not tested. SVO3's compiler findings
motivated the comparison, but Medius was measured independently.

Use default split-address optimization. SVO3's `-mno-split-addresses` failed to
reproduce the Medius memory probes during the initial comparison. The dedicated
`MEDIUS_COMPILE_FLAGS` preserve the winning settings:

```text
-G0 -O2 -fno-builtin -fno-common -ffunction-sections
-falign-functions=4 -falign-loops=1 -falign-jumps=1 -falign-labels=1
```

Assembler flags are `-EL -G0 -g -Icode/include`. The existing `ee-gcc296`
installation/stat shim is reused. Only `medius/rt_util/rt_memory.o` currently
uses the Medius rule; add further objects after their replacements are verified.
Other libraries' compiler rules are preserved.

## Integrated functions

| Function | Retail entry | Exact bytes |
| --- | --- | ---: |
| rt_memory_free | 0x01EA95C0 | 88 |
| rt_memory_register_callbacks | 0x01EA9768 | 24 |
| rt_memory_get_aligned_address | 0x01EA9790 | 72 |

Source ownership is `code/medius/rt_util/rt_memory.c`. Retail Ghidra and split
instructions were used together. Existing callback storage stays at its mapped
retail addresses; no duplicate globals are allocated. Null handling, callback
store order, unsigned-short alignment, and the retail error return (100) are
preserved. `rt_memory_free` expects a valid pointer-to-pointer, as retail does.

The manifest places both retained assembly and compiled functions at their
original addresses. The two existing trailing nops around 0x01EA9544 and
0x01EA954C are retained within their assembly slots. No original instructions
are substituted into the C implementations.

## Verification and limits

An isolated source snapshot in `projectryno-medius-probe` at
`/tmp/medius-integration` was split and built separately from the active SVO3
checkout. Its existing `RTCommSock.cpp` included `DnsCache.h` while the file was
`DNSCache.h`; a snapshot-only symlink supplied that spelling for the Linux build.
No SVO3 source fix was applied to the user's checkout. Absolute source paths were
rewritten only in the snapshot to keep INCLUDE_ASM reads isolated.

- `check_medius.py`: all three are real compiled function definitions at their
  retail addresses, with exact sizes and bytes. All 776 bytes of the containing
  rt_memory module match retail, including retained assembly.
- `check_main_elf.py`: placement/runtime-header/outside-slot audit passes.
- Strict comparison against the pre-Medius baseline: zero changed loaded bytes
  and identical runtime headers.
- Strict comparison against retail: **NONMATCH**, with 34,164 pre-existing
  differences (5,130 main + 29,034 network) in this isolated snapshot. The Medius
  additions introduce none. This is not a matching whole game.
- No ISO packaging, emulator, gameplay, or separate runtime behavior test was run.

Concurrent SVO3 work can change whole-project totals. These counts describe the
saved snapshot, not later builds. The main FUNCTIONS.csv/SUMMARY.json are not
regenerated from this older snapshot over concurrent work; Medius progress and
per-function research notes are recorded separately here.

## Reproduce

The fixed probe source is `dl/TESTS/medius_compiler_probes.c`; the script is
`tools/medius_compiler_probe.py`. Full results, executable SHA-256 fingerprints,
compiler/assembler version output, and source/reference hashes are preserved in
[MEDIUS_COMPILER_RESULTS.json](MEDIUS_COMPILER_RESULTS.json).

Inside the Linux build environment:

```sh
python3 /ProjectRYNO/tools/medius_compiler_probe.py \
  --output /ProjectRYNO/dl/build/medius-compiler-results \
  --shim /opt/ee-gcc2.96/ee296_statshim.so \
  --compiler sony296 /opt/ee-gcc2.96/bin/ee-gcc /opt/ee-gcc2.96/ee/bin/as \
  --compiler ps2dev323 /opt/ps2dev/ee/bin/ee-gcc /opt/ps2dev/ee/bin/ee-as
```

Add `--compiler sony32 PATH/bin/ee-gcc PATH/ee/bin/as` for the archived Sony
3.2 toolchain. Compiler archives are local tools and are not committed. The
working experiment has that toolchain at `/probe/sony32` in the probe container.
After splitting and rebuilding the game, run from `dl`:

```sh
python3 TESTS/check_medius.py ../assets/dl/boot.elf build/boot_elf.elf \
  build/code/medius/rt_util/rt_memory.o
python3 TESTS/check_main_elf.py ../assets/dl/boot.elf build/boot_elf.elf \
  build/code/game/boot.o
python3 ../tools/compare_elf.py ../assets/dl/boot.elf build/boot_elf.elf
```

Ignored experiment artifacts and integration logs are under
`dl/build/medius_compiler_probe/`. The next useful work is to recover the remaining
memory functions and improve the strnlen probe, then test another Medius component
before expanding the compiler rule across the library.

## Type recovery

See [Medius type placement](../types/MEDIUS_TYPES.md) and its 85-header inventory
for dltypes.txt ownership, proposed header locations, and validation requirements.
