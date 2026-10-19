# Deadlocked newlib libm — 2026-10-19

## Verified result

**37/37 functions (100%) are compiled from C and byte-identical to retail.**
There are no remaining function assembly fallbacks in this library. Verification
covers 21,180 compiled instruction bytes, 2,046 compiled constant-pool bytes,
and the complete 21,272-byte math block at `0x00131A90..0x00136DA8` including padding.

All 37 original source-file splits under `newlib/libm/common` and `math` remain
in `SCUS_974.65.yaml`, with the original public entry addresses. The prefix remains
in `game/lib.cpp` and the suffix in `game/lib_after_libm.cpp`.

## Exact source and compiler combination

Use verbatim **newlib 1.9.0** sources, with two older files:

| Source | Release |
| --- | --- |
| `math/ef_asin.c` | 1.8.2 |
| `common/s_rint.c` | 1.8.1 |
| Other 35 C sources and `fdlibm.h` | 1.9.0 |

These are from the [official archive](https://sourceware.org/ftp/newlib/), with
copyright notices and `COPYING.NEWLIB` retained. `upstream/` is excluded from
independent compilation; each wrapper includes its source after a placement
declaration. No inline assembly or instruction rewriting was needed.

The older `asin` branch structure matches; 1.9.0's differs. The older `rint`
temporary is nonvolatile; 1.8.2 and later introduce volatile storage that does
not match. This combination reproduces the executable, but does not uniquely
identify a stock original SDK release. There is no need for 1.12/1.13 here.

The matching compiler archive is specifically:

```text
ee-gcc2.9-991111-01.tar.xz
SHA-256: ed684fd98f89d36b0121caab311052089103e3b36241fcef4338cc9ea41c75b8
compiler: Sony GCC 2.9-ee-991111-01
compiler flags: -G0 -O2 -fno-builtin
assembler flags: -EL -G0
```

**Do not substitute `ee-gcc2.9-991111a.tar.xz`.** It reports the same compiler
version but lacks the matching floating-point division output. That archive
supported the earlier 31/37 milestone. The separate `-991111-01` archive naturally
emits the required division scheduling and two-nop workaround, resolving five
remaining routines; the older `asin` source resolves the sixth. The driver trace
confirmed it runs its own archive's `cc1`.

The Makefile pins the archive URL/hash and installs it through `make ee-gcc29-01`.
It uses the existing native-compiler stat shim and target headers, force-including
`sys/types.h` by absolute path. The full linked comparison verifies that this
header setup reproduces all 37 functions. No sound-loop adapter or fast-math is used.

## Evidence and research trail

Ghidra program: `DL_Retail_BootELF_974.65.elf`, project path
`/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose`, `r5900:LE:32:default`.
Retail disassembly confirmed the math operations, helper ABI and division sequence.
Final verification uses the actual asset ELF, not pseudocode or prototype code.

[Release comparison](LIBM_RELEASE_COMPARISON.json) records nine official release
archives and hashes. [Initial probes](LIBM_COMPILER_PROBES.json) and
[31-function follow-up](LIBM_FOLLOWUP_PROBES.json) preserve earlier experiments.
[Final evidence](LIBM_FINAL_PROBES.json) records the exact compiler archive,
source versions, assembler experiments, all individually linked candidates and
the full-ELF 37/37 result. Relocation-masked probes are diagnostic only; the linked
checks compare actual bytes without masks.

The division-workaround lead came from
[OpenRAC's UYA research](https://github.com/OpenRAC/rac3-uya-decomp/blob/ac0eb2a87cc1706e1d15025f8a17838d17f9175c/docs/full_match_roadmap.md).
Its compiler names were a lead, not proof: our final selection is based on archive
hash and Deadlocked's actual linked output. No per-function padding tables or
instruction patches from that project were imported.

## Placement and safeguards

The 23 original four-byte `CDCDCDCD` alignment gaps remain explicit textbin
padding. Function slots end at the actual code boundaries. All C wrappers survive
serial splitting; none uses `INCLUDE_ASM`.

Nineteen referenced constant pools use exact original-address data slots.
Standard objcopy renames their sections without modifying contents; standard
strip normalizes the old assembler's symbol-table ordering first. The libm checker
compares both compiled object constants and linked bytes with retail.

The six-byte `asinf` string ends inside a word. The splitter preserves its two
following `CD` padding bytes outside the compiled slot by splitting the literal
word; it refuses to split relocations. Regression fixtures cover both cases.
Unreferenced duplicate `.rodata` uses the existing guarded removal helper, which
rejects incoming relocations, exported symbols and writable/executable flags.
No original instruction words are copied into a supposedly compiled function.

## Verification and reproduction

From Deadlocked in the configured Linux container:

```sh
make split
make -j8 elf
python3 TESTS/check_libm.py ../assets/dl/boot.elf build/boot_elf.elf build/code
python3 TESTS/check_main_elf.py ../assets/dl/boot.elf build/boot_elf.elf build/code/game/boot.o
python3 ../tools/compare_elf.py ../assets/dl/boot.elf build/boot_elf.elf
```

Force affected objects to rebuild after compiler/header changes. For diagnostic
source comparisons, `tools/probe_libm.py --compiler sony01` selects the final
compiler profile; provide `--newlib` and `--output` paths as shown by `--help`.

The isolated snapshot `/tmp/libm-integration/dl` passed serial splitting, compilation,
linking, all libm instruction/data checks, and the runtime-header/slot audit.
The strict whole-game comparison remains **NONMATCH: 3,917 differing bytes outside
libm**, unchanged from the preceding baseline. All read-only data matches. This
100% claim is for libm, not the whole executable. Gameplay was not tested.

The snapshot retains documented unrelated build accommodations: committed
`RTCommSock.cpp`, a `DnsCache.h` case alias, and temporary medius linker alias
`D_168BAC = 0x00168BAC`. These are not changes to live concurrent SVO3 work or proof
that the untouched concurrent checkout clean-builds. Current libm inputs were
copied into the snapshot; subsequent validation also used the live libm inventory.

Artifact: ignored `build/medius_compiler_probe/libm37-2026-10-19.elf`.
SHA-256: `2e1283399004eacffe115cc09128eaa2757ff5f658b49a7171cd972d46d25189`.
[LIBM.json](../progress/LIBM.json) and [LIBM.csv](../progress/LIBM.csv) track all 37
functions. Broader concurrent SVO3 progress remains separately maintained.
