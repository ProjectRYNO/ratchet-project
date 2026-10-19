# Deadlocked newlib libm — 2026-10-19

## Verified progress and source recommendation

**31/37 functions (83.78%) compile from C and match retail exactly**, totaling
15,956 instruction bytes and 1,762 compiled constant-pool bytes. The complete
21,272-byte block at `0x00131A90..0x00136DA8` matches, including the six remaining
assembly routines and original padding. This extends the initial 14/37 result.

Use **newlib 1.9.0 as the working baseline**, with `common/s_rint.c` verbatim
from **1.8.1**. The older `rint` matches in releases 1.7.1, 1.8.0 and 1.8.1;
1.8.2 introduces a volatile temporary and generates different instructions.
This is evidence for an older or vendor-modified source family, not a unique
identification of the original SDK release. There is no demonstrated need for
1.12 or 1.13 for the matched routines.

The six unfinished implementations are `__ieee754_asinf`, `__ieee754_expf`,
`__ieee754_logf`, `__ieee754_log10f`, `__ieee754_powf`, and `__ieee754_sqrtf`.
They retain explicit `INCLUDE_ASM`; importing upstream C does not count as
completed decompilation. Their upstream candidates remain in the tree.

## Source and compiler evidence

Ghidra's selected program was `DL_Retail_BootELF_974.65.elf`, project path
`/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose`, `r5900:LE:32:default`.
Retail disassembly confirmed fdlibm bit-word operations, double helper calling
conventions and exception wrappers. All final comparisons use the actual asset
ELF, not pseudocode or prototype code.

Nine releases were obtained from the [official archive](https://sourceware.org/ftp/newlib/):
1.7.1, 1.8.0, 1.8.1, 1.8.2, 1.9.0, 1.10.0, 1.11.0, 1.12.0 and 1.13.0.
[Release comparison](LIBM_RELEASE_COMPARISON.json) records archive hashes and
source differences. Of these 37 sources, 33 in 1.8.2 equal 1.9.0 after removing
comments/whitespace; only 23 in 1.12/1.13 equal 1.9.0.

The initial [compiler probes](LIBM_COMPILER_PROBES.json) favored SN GCC 2.95.3
v1.36 on small routines. The expanded matrix found **Sony GCC 2.9-ee-991111-01**
(`ee-gcc2.9-991111a.tar.xz`) reproduces 30 functions from unchanged 1.9.0 source,
including the large double-precision functions and error wrappers. Older `rint`
adds the 31st. [Follow-up evidence](LIBM_FOLLOWUP_PROBES.json) includes the broader
compiler/version/option comparisons, individually linked probes and the full-ELF
verification result. Relocation-masked diagnostic comparisons are explicitly
separate from the final unmasked linked-byte checks.

The Makefile pins the compiler download and SHA-256:
`f07d1f38afa847197fb816237dbce64e79b2d37b738cb93fa4df3ac7aa1d16f3`.
`make ee-gcc29a` installs it, depending on the existing native-compiler stat shim
and target headers. The profile is:

```text
compiler: Sony GCC 2.9-ee-991111-01
LIBM_COMPILE_FLAGS = -G0 -O2 -fno-builtin
assembler flags = -EL -G0
```

The target `sys/types.h` is force-included by absolute path for fdlibm integer
word types; the older compiler mishandles a relative forced include. The full
linked verification establishes that the installed target headers reproduce the
probed output. Neither fast-math nor the sound loop adapter is used.

## Original splits and data placement

The [source directory](../../code/newlib/libm/README.md) preserves all 37 original
translation units under `common/` and `math/`. Their wrappers include the corresponding
upstream source after a section declaration. The `upstream/` copies are excluded
from independent source discovery. Original copyrights and `COPYING.NEWLIB` remain;
all sources are verbatim 1.9.0 except the documented 1.8.1 `s_rint.c`.

`SCUS_974.65.yaml` still has each source at its original address. `game/lib.cpp`
contains the preceding library functions, and `game/lib_after_libm.cpp` the suffix.
Nineteen four-byte `0xCDCDCDCD` gaps following compiled functions are explicit
textbin padding. Slot ends are the actual original code ends. Splitting preserves
all compiled wrappers and regenerates only the unfinished assembly wrappers.

Fifteen referenced constant pools use exact original-address read-only-data slots
in `decompiled_functions.yaml`. Standard objcopy renames their sections without
changing contents. Standard strip first normalizes the old assembler's symbol-table
ordering. The library checker compares both object constant bytes and linked bytes
against retail, in addition to checking every instruction and public entry.

The six-byte `asinf` string ends midway through an original word. The splitter
splits that literal word into bytes so its two `CD` padding bytes remain in the
original data object, outside the compiled slot. It refuses to split a relocated
word. Regression fixtures cover this boundary and rejection. No slot is widened.
Unreferenced duplicate `.rodata` still uses `drop_unused_rodata.py`, which rejects
incoming relocations, exported symbols and writable/executable flags. Five
real-assembler fixtures test that guard.

## Verification and reproduction

From Deadlocked in the configured Linux container:

```sh
make split
make -j8 elf
python3 TESTS/check_libm.py ../assets/dl/boot.elf build/boot_elf.elf build/code
python3 ../tools/test_elf_tools.py
python3 ../tools/test_drop_unused_rodata.py
python3 TESTS/check_main_link_guards.py
```

Force affected objects to rebuild after changing headers or compiler flags.
Diagnostic compiler research is reproducible with an extracted release:

```sh
python3 ../tools/probe_libm.py --newlib /path/newlib-1.9.0/newlib --output /tmp/libm-probe --compiler sony991111a
```

The isolated snapshot `/tmp/libm-integration/dl` passed serial splitting, ELF
compilation/linking, strict libm code/data comparison, slot/runtime-header audit,
six ELF-tool fixtures, five unused-data fixtures and linker guard tests. The
strict whole-game comparator remains **NONMATCH: 3,917 differing loaded bytes**,
all outside libm, unchanged from the preceding baseline. All read-only data matches.
No gameplay or on-console mathematical edge-case execution was performed.

The snapshot retains documented accommodations for unrelated existing build issues:
committed `RTCommSock.cpp`, a `DnsCache.h` case alias, and a temporary
`D_168BAC = 0x00168BAC` medius linker alias. These are not live source changes or
proof that the untouched concurrent checkout clean-builds. Current libm source,
manifest, splitter and compiler changes were copied into that snapshot.

Verified artifact: ignored `build/medius_compiler_probe/libm31-2026-10-19.elf`.
SHA-256: `015dd4595d0b8aaa72463c06d8b8d56651e0291b7ab9838fad01f25597468fed`.
[LIBM.json](../progress/LIBM.json) and [LIBM.csv](../progress/LIBM.csv) record the
current per-function status. The broader SVO3 progress files are maintained separately.

## Remaining investigation

The six IEEE float kernels differ under Sony 991111/991111a, SN v1.14/v1.36/273a,
Sony 3.2/030926 and tested optimization/CPU profiles. Early-release sources did
not close those gaps. Several differences involve division scheduling: retail
avoids putting `div.s` in a return delay slot and has extra producer/division
spacing. This is a lead, not proof of a specific compiler patch. Preserve the
assembly until authentic source/compiler output matches; do not insert original
instruction words to manufacture a result.

Additional environment limits: the DTLS packaged compiler runs with its bundled
old libc but cannot read the current filesystem without a compatible stat shim;
the Sony 3.2 beta Windows executable requires an unavailable `cygwin_internal`
import under wibo. Neither failed attempt is counted as a successful comparison.
