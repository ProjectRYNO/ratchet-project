# Deadlocked newlib libm — 2026-10-19

## Result and source recommendation

Use **newlib 1.9.0 as the working source baseline**. The evidence points to the
older 1.8.2/1.9.0 fdlibm family, not a demonstrated need for 1.12/1.13. This is
not a unique identification of the original release: the matching functions
alone cannot distinguish 1.8.2 from 1.9.0, and 23 implementations are unfinished.
A vendor snapshot or local modifications remain possible.

**14/37 functions (37.84%) now compile from C and match retail exactly**, totaling
1,760 compiled instruction bytes. The complete 21,272-byte block at
`0x00131A90..0x00136DA8` matches, including retained assembly and padding. The
other 23 functions explicitly retain their original assembly; importing their
upstream C is not counted as decompilation progress.

The 14 matches are `__kernel_cosf`, `copysign`, `fabs`, `finite`, `isnan`,
`matherr`, `ceilf`, `copysignf`, `cosf`, `fabsf`, `finitef`, `floorf`, `isnanf`,
and `scalbnf`.

## Evidence

Ghidra's selected program was `DL_Retail_BootELF_974.65.elf`, project path
`/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose`, `r5900:LE:32:default`.
Retail disassembly of `fabsf`, `matherr`, and `fmod` confirmed the fdlibm bit-word
operations, double helper calling convention, and exception-wrapper structure.
The existing retail symbol map supplies the 37-function inventory. The final
comparison uses the actual asset ELF, not Ghidra's pseudocode or prototype code.

Nine archives were fetched from the [official release archive](https://sourceware.org/ftp/newlib/):
1.7.1, 1.8.0, 1.8.1, 1.8.2, 1.9.0, 1.10.0, 1.11.0, 1.12.0, and 1.13.0.
[Release comparison](LIBM_RELEASE_COMPARISON.json) records archive SHA-256 hashes
and source differences after removing comments and whitespace. Of these 37
sources, 33 in 1.8.2 equal 1.9.0; the differences are `ef_asin`, `ef_log`,
`s_scalbn`, and `sf_scalbn`. Only 23 of the 1.12/1.13 sources equal 1.9.0.

The initial compiler matrix tested Sony 2.9-ee-990721, Sony 2.96, EE GCC 3.2.3,
and SN GCC 2.95.3 v1.36 at O1/O2 on small functions across 1.9 through 1.13.
SN v1.36 reproduced the most of these functions. Full-function probes then
compared Sony 2.9 and SN v1.36 with the 1.9 source. Follow-up probes compared the
four release-distinguishing sources under 1.8.2, 1.9.0 and 1.12.0. In particular,
1.8.2/1.9.0 `scalbnf` matches with SN, while 1.12.0 does not under that profile.
The same older/newer distinction appears in `finitef` and `isnanf`.
[Compiler experiments](LIBM_COMPILER_PROBES.json) include diagnostic relocation-masked
differences; those are **not** the final exact-match gate. Only the fully linked,
unmasked `check_libm.py` result establishes the 14 exact functions.

## Imported source and build

The [source directory](../../code/newlib/libm/README.md) contains the 37 relevant
upstream files plus `fdlibm.h`, verbatim from 1.9.0, with original copyright notices
and `COPYING.NEWLIB`. Its `upstream/` directory is excluded from independent source
discovery. Matched wrappers include their upstream file after a placement declaration;
unfinished wrappers use explicit `INCLUDE_ASM`. No unrelated libc headers were imported.

The Makefile pins the existing SN v1.36/wibo tool installation and uses:

```text
LIBM_COMPILE_FLAGS = -G0 -O2 -fno-builtin
assembler flags = -EL -G0
```

The existing target `sys/types.h` is included explicitly for fdlibm's integer
word types. Checks on representative routines confirmed identical assembly with
the release headers and with the installed target headers plus that include.
This profile does not use the sound loop adapter or fast-math.

SN emits some unused static constants even when their values are immediate
instructions. `drop_unused_rodata.py` removes only this duplicate object section;
it fails on any incoming relocation, exported symbol, or writable/executable
section flag. Retail data stays in the original data object. Five real-assembler
fixture tests cover acceptance and rejection. Original `0xCDCDCDCD` gaps after
eight matched functions are explicit textbin padding, not C functions or copied
instructions. Slot ends remain at the original function bounds.

The former aggregate `game/lib.cpp` was divided at the math block: its prefix
stays in that file, the 37 original math translation units live under newlib/libm,
and its suffix is `game/lib_after_libm.cpp`. The split config and manifest retain
all original entry addresses. The loaded-byte audit checks the surrounding code.

## Verification and reproduction

From the Deadlocked directory in the configured Linux container:

```sh
make split
make -j8 elf
python3 TESTS/check_libm.py ../assets/dl/boot.elf build/boot_elf.elf build/code
python3 ../tools/test_drop_unused_rodata.py
```

After headers or flags change, force the affected objects to rebuild. For compiler
research, extract an official archive outside tracked source, then run:

```sh
python3 ../tools/probe_libm.py --newlib /path/newlib-1.9.0/newlib --output /tmp/libm-probe --compiler sn136
```

The final isolated snapshot was `/tmp/libm-integration/dl`. Serial split, full ELF
link, strict libm check, and slot/runtime-header audit passed. 989snd is still
59/59 exact, SDK 20/20, and iksemel 40/40 with all five tables. Whole-game strict
comparison remains NONMATCH at 3,917 loaded bytes outside libm, all in registered
slots, unchanged from the baseline. Gameplay and mathematical edge-case execution
on console were not tested; executable identity is the evidence for retained behavior.

The snapshot inherited the preceding sound verification's accommodations for
unrelated existing build issues: committed `RTCommSock.cpp`, the `DnsCache.h` case
alias, and a temporary `D_168BAC = 0x00168BAC` medius linker alias. These are not
changes to the live SVO3/medius sources or proof that the untouched checkout clean-builds.
The verified C, upstream files, and layout inputs were checked against the live
checkout. Artifact: ignored `build/medius_compiler_probe/libm-2026-10-19.elf`;
logs: `libm-*.log` in that directory. Hashes and per-function state are recorded
in [LIBM.json](../progress/LIBM.json) and [LIBM.csv](../progress/LIBM.csv).

Next candidates include `scalbn` (Sony 2.9 diagnostic instructions already agree
apart from relocations), the larger ieee754 routines, and their error wrappers.
Their constants, compiler register allocation, and exact linked bytes must still
be recovered. Do not replace the remaining assembly merely because upstream names match.
