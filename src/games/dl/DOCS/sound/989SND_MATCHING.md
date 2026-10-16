# 989snd matching investigation — 2026-10-16

## Verified integrated status

Working changes on `deea1ee`: **54/59 complete function slots match (91.53%)**.
All 59 named EE client functions compile from C. All 18 retained non-function
instruction fragments match. The complete 7,236-byte module still contains
**1,291 differing bytes**. This is not 100% matching.
Per-function measurements and source/header/ELF hashes are in
[989SND.json](../progress/989SND.json) and [989SND.csv](../progress/989SND.csv).

A fresh serial split and forced full build were completed in the isolated
`/tmp/sdk-integration/dl` snapshot; the final sound object was force-recompiled
and relinked after synchronizing the owning header. Both sound suites pass: **2,720 wrapper
and 293 stateful cases**, including 64-bit callback data and reentrant completion.
SDK remains 20/20 exact; iksemel remains 40/40 exact with all five jump tables.
The loaded-byte/placement audit passes. Whole-game strict comparison remains
nonmatching; every changed byte is inside registered replacement slots and all
runtime headers match. Gameplay and IOP-driver behavior have not been tested.

The October 16 continuation verified the previously unrecorded CD-read match and
made `snd_StreamSafeCdSync` exact. Its completion test compares explicitly with
one, its waiting loop tests before entering, and both shared-status reads use a
volatile structure pointer. This reproduces retail's reuse of the mode register
for the status address, removing the extra saved register. All 160 slot bytes
match. That earlier whole-game comparison reported 11,684 changed loaded bytes,
all inside registered replacement slots.

## Reproducible compiler profile

`Makefile` now uses **SN Systems GCC 2.95.3 v1.36**, its bundled GNU assembler
`2.9-ee-991111b`, and the pinned **wibo 1.2.0 i686** runner on Linux. `make
ee-gcc-sn136` downloads both tools with SHA-256 verification. No executable
instructions are patched and no slots are widened. The entire original C
translation unit is compiled together.

```text
SOUND_COMPILE_FLAGS = -G16 -O2 -fopt-stack -mno-check-zero-division
SOUND_AS_FLAGS = -EL -G8 -g
compiler archive SHA-256 = 3b6ae6897229ad005aaf1b0afaa1f3cb46e74b4c21a42e01130c07c0c598067f
wibo SHA-256 = 2575d3b0a2f408b2c2b0850db56f1af5d005a138394a6774eba77b6708ecc304
```

[Compiler archive](https://github.com/decompme/compilers/releases/tag/compilers),
[wibo runner](https://github.com/decompals/wibo/releases/tag/1.2.0).
Run `make -B build/code/989snd/ee/989snd.o`, then `make elf`, then both
`TESTS/test_989snd_wrappers.py` and `TESTS/test_989snd_state.py` with the original
and rebuilt ELF paths. Also run `TESTS/check_main_elf.py` and the strict
`../tools/compare_elf.py`; the latter still reports the matching backlog.

SN's `long long` is 128 bits, unlike Sony's 64-bit type. `SndUserData` therefore
uses explicit GCC `mode(DI)` to preserve the retail 64-bit ABI and 16-byte return
record. Early SN experiments without this correction were not comparable.
`-fopt-stack` gives compact scalar saves. The assembler's `-g` preserves compiler
NOPs and delay slots; it is needed for the exact Doppler DIV/MFLO return sequence.

The streaming packet and external callback wrappers now match without instruction
substitution. Source branch order retains the CD Break/GetError matches. Startup
uses a register-based delay counter, as retail does, and fits its original slot.
The return-buffer pointer advances after the first cache call; this reproduces
retail register lifetimes. The batch reset accesses the first packet word directly,
retaining the retail reload of the buffer index after that store.

## Earlier evidence and remaining work

Sony 2.9-990721 previously reached 44/59 after explicit packet stores, a byte-address
cache endpoint, and the volatile shared-status read. Its original source forces
16-byte save slots through `mips_reg_mode[0] = TImode`; the supported precision
attribute excludes that entry. The preserved 990430 source behaves the same,
and published 990721 patches do not change the compiler backend. Source releases:
[original Sony compiler sources](https://github.com/GirianSeed/ee-gcc/releases).

Disabling Sony's second scheduling pass matched Doppler alone but reduced the
whole-module result to four matches. Additional Sony 2.96 optimization profiles
were also worse. Those flags were not integrated. SN's alternative Ps2EeAs
assembler regressed the integrated profile and was not selected.

The local prototype is partial and is not a byte-matching reference. Related
[OpenRAC source](https://github.com/OpenRAC/rac1-decomp/blob/main/src/core/989snd.c)
and [toolchain notes](https://github.com/OpenRAC/rac1-decomp/blob/main/docs/TOOLCHAIN.md)
provided clues, but Deadlocked's retail instructions remain authoritative.

Remaining functions (complete-slot differing bytes):

| Function | Differing bytes |
| --- | ---: |
| `snd_StartSoundSystemEx` | 364 |
| `snd_SendIOPCommandAndWait` | 112 |
| `snd_SendIOPCommandNoWait` | 705 |
| `snd_InitVAGStreamingEx` | 67 |
| `snd_CloseVAGStreaming` | 43 |

Continue with short-loop padding, aliasing/reloads, shared status access and
source register lifetimes under the corrected SN ABI. Keep all slot and behavior
checks; do not classify a fitting or behavior-tested function as byte-exact.

Earlier October 16 probes did not improve the count: alternate streaming-close
loop forms, explicit R5900 assembler mode, SN assembler optimization/extensions,
and GP/address-splitting flags. The prototype declares a four-word bank-return
array, but substituting that declaration did not match retail bank-loading code;
that array-only experiment was not integrated. The later shared-storage views
below resolve the GP-relative versus absolute accesses.

## Earlier October 16 follow-up toward 90%

At this intermediate point the target was unfinished: 51/59 (86.44%), with three
additional matches needed. That pass reduced differing module bytes from
2,337 to 1,917 (420 fewer), without losing any existing exact function.

The synchronous sender now places the ordinary copy branch first and has separate
RPC calls for empty/nonempty payloads, as the retail instructions do. Its complete
slot improves from 433 to 112 differing bytes. Compiler `-G16`, with assembler
`-G8` retained, improves startup (428 to 353), flush (236 to 218), and the bank
callback (186 to 180), reproducing the latter's saved-register allocation.
This is a whole-translation-unit compiler setting, not a per-function override.

Fresh sound compilation/relink, 2,720 wrapper cases, 293 stateful cases, the
slot/runtime-layout audit, SDK 20/20, and iksemel 40/40 plus five jump tables pass.
The whole-game strict comparison still reports 11,264 changed loaded bytes;
all are inside registered replacement/jump-table slots. Gameplay was not tested.

The streaming init/close loops and sender polling loop still have different
padding. Historical GNU assemblers and the bundled SN Ps2EeAs were tested;
none added matches. Ps2EeAs retained only 41 exact functions because its global
address expansions differ. Older SN compiler builds reject `-fopt-stack`.
Volatile return-state access and global section attributes also added no exact
functions, so those experimental source/header changes were not integrated.

Related [OpenRAC assembler research](https://github.com/OpenRAC/rac1-decomp/blob/main/tools/ps2eeas_nops.py)
identifies call-containing short-loop padding in its 989snd build. Its generated
assembly rewriting was not adopted: this repository requires actual compiled
source and forbids substituting instructions to manufacture a match. Deadlocked's
retail loop spans remain the authority; the related game's padding rule is not
proof of the correct Deadlocked toolchain.

## Verified 90% milestone

The continuation reaches **54/59 (91.53%)**, adding complete matches for
`snd_FlushSoundCommands` (496-byte slot), `snd_BankLoadByLoc_CB` (344 bytes),
and `snd_BankLoadFromEE` (336 bytes). No earlier exact function was lost.
There are now five nonmatching functions and 1,291 differing module bytes,
626 fewer than the intermediate 1,917-byte result (1,046 fewer than HEAD).
Startup changes from 353 to 364 differing bytes with the shared-storage views;
that small regression remains explicitly counted.

The prototype declares `gLoadReturnValue[4]` (`dlglobals.txt:45`); the retail
instructions access its first word at `0x0021D9C0` and pass a four-byte cache/RPC
range. The remaining array elements' use is not established by these routines.
The array declaration plus scalar access views reproduce retail's mixed absolute
and GP-relative addressing under compiler `-G16` / assembler `-G8`.
`gLoadReturnWord` and `gLoadReturnStatus` both name that first word.
The loader independently reads status at `0x001584DC` and result at `0x00158514`;
using one scalar expression let GCC combine the reads. Separate external views
preserve both reads, and the polling path returns the value it just observed.
`gLoadReturnDone` names `gLoadReturnDef.done` at `0x0021DCF8` (offset zero).
These descriptive aliases are not claimed to be original prototype names.
All are ordinary externs with symbol mappings: no new storage, inline assembly,
instruction replacement, or slot widening. Splat's `allow_duplicated:true` marks
these intentional shared addresses. Provenance is in the global inventory CSV.

Flush uses a separate callback local for the loader completion and preserves the
retail order of clearing callback state, invoking it, then clearing the return
word. It also clears the CD-read flags in the retail order. The bank callback
retains its original 64-bit user-data field and register lifetimes.

Validation: serial `make split`, forced `make -B -j8 elf`, final forced sound
compile/relink, all 59 complete-slot comparisons and all 18 retained fragments,
2,720 wrapper plus 293 stateful differential cases, and nine SN v1.36 ABI
size/offset checks pass. The state suite checks every sound global's linked
address and the three alias relationships. The global-map audit passes for
807 recovered names. SDK stays 20/20 exact; iksemel stays 40/40 with five exact
jump tables and its existing differential/layout tests passing.

The runtime-header/allowed-slot audit passes. The separate whole-game strict
comparison remains **NONMATCH: 10,638 changed loaded bytes**, all inside
registered replacement/jump-table slots. This is a 989snd function-count
milestone, not a claim of a completely matching ELF. Gameplay/IOP timing and
audible output were not tested. The measured ELF is saved under
`build/medius_compiler_probe/sound-90-verified.elf` (ignored); its digest and the
source/header digests are in the progress JSON.
