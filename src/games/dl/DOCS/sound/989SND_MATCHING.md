# 989snd matching investigation — 2026-10-15

## Verified integrated status

Working changes on `0691b50`: **49/59 complete function slots match (83.05%)**.
All 59 named EE client functions compile from C. All 18 retained non-function
instruction fragments match. The complete 7,236-byte module still contains
**2,542 differing bytes**. This is not 100% matching.
Per-function measurements and source/header/ELF hashes are in
[989SND.json](../progress/989SND.json) and [989SND.csv](../progress/989SND.csv).

The sound object was force-recompiled and the complete game relinked from the
existing serial-split/full-build snapshot. Both sound suites pass: **2,720 wrapper
and 293 stateful cases**, including 64-bit callback data and reentrant completion.
SDK remains 20/20 exact; iksemel remains 40/40 exact with all five jump tables.
The loaded-byte/placement audit passes. Whole-game strict comparison remains
nonmatching; every changed byte is inside registered replacement slots and all
runtime headers match. Gameplay and IOP-driver behavior have not been tested.

## Reproducible compiler profile

`Makefile` now uses **SN Systems GCC 2.95.3 v1.36**, its bundled GNU assembler
`2.9-ee-991111b`, and the pinned **wibo 1.2.0 i686** runner on Linux. `make
ee-gcc-sn136` downloads both tools with SHA-256 verification. No executable
instructions are patched and no slots are widened. The entire original C
translation unit is compiled together.

```text
SOUND_COMPILE_FLAGS = -G8 -O2 -fopt-stack -mno-check-zero-division
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
| `snd_StartSoundSystemEx` | 428 |
| `snd_FlushSoundCommands` | 236 |
| `snd_BankLoadByLoc_CB` | 186 |
| `snd_BankLoadFromEE` | 239 |
| `snd_SendIOPCommandAndWait` | 433 |
| `snd_SendIOPCommandNoWait` | 705 |
| `snd_InitVAGStreamingEx` | 67 |
| `snd_CloseVAGStreaming` | 43 |
| `snd_StreamSafeCdRead` | 85 |
| `snd_StreamSafeCdSync` | 120 |

Continue with short-loop padding, aliasing/reloads, shared status access and
source register lifetimes under the corrected SN ABI. Keep all slot and behavior
checks; do not classify a fitting or behavior-tested function as byte-exact.
