# 989snd matching investigation — 2026-10-15

## Integrated status

The working changes on `7e84d27` integrate **42/59 exact functions (71.19%)**,
up from 6/59 (10.17%). All 59 remain compiled C. The complete 7,236-byte module
now has **3,021 differing bytes**, down from 4,404. All 18 retained instruction
fragments match. Per-function evidence is in
[989SND.json](../progress/989SND.json).

A serial split followed by a forced full build includes the current merged
Medius work. Both sound suites pass **2,720 + 293 cases** across all 59 functions.
The public-address/slot/runtime-layout audit passes. This does not establish
gameplay or IOP-driver behavior, and the **17 remaining nonmatching functions
keep the 100% goal open**.

SDK still passes 20/20 exact functions; iksemel still passes 40/40 exact
functions and all five jump tables. The whole-game strict comparison remains
nonmatching (12,368 changed loaded bytes); those differences are all within
registered replacement slots. Runtime headers and bytes outside the slots
match. These results are separate from the sound-only percentage.

## Integrated compiler and source changes

`Makefile` now pins SCE **2.9-ee-990721** and its bundled assembler specifically
for this object. `make ee-gcc29` checks the compiler archive's SHA-256 before
extraction and reuses the existing 32-bit stat shim. The source/header/Makefile
are explicit sound-object dependencies.

```text
SOUND_COMPILE_FLAGS = -G8 -O2 -fno-builtin -fno-common -fexceptions -fsjlj-exceptions -mno-check-zero-division
SOUND_AS_FLAGS = -EL -G8
archive SHA-256 = ad2ea68afff2be25d21a1d51a75e8a0eea8f259018e6580622355cd01b95676b
```

`-fexceptions` inhibits the unwanted sibling jumps. `-fsjlj-exceptions` retains
that code generation without adding DWARF frame-registration data or startup
constructors. No exception handler is introduced in the C source. The constant
divisor 741 does not need a runtime zero check.

Packet fields use explicit assignments. The previous compiler's two helper
workarounds are removed: file-load completion is inside the flush function,
and CD callback exchange is implemented directly at its public entry. The
stream-safe CD branches follow retail order. The Doppler multiplication retains
defined unsigned 32-bit wraparound before signed division.

The compiler currently uses `DIV1`/`MFLO1` for Doppler, while retail uses the
first unit. The differential interpreter now implements those two instructions
with separate LO1/HI1 state; three focused tests cover signed results, isolation
from LO, and rejection of unknown MMI opcodes. Unsupported instructions still
fail. All 107 existing Doppler behavior cases pass, but its two differing bytes
remain correctly classified as nonmatching.

## References checked

* The local `deadlocked-proto-decomp/989snd/ee/989snd.c` begins with
  `STATUS: NOT STARTED`. It contains partial recovered bodies, empty stubs,
  duplicate declarations, and prototype globals; it is not a verified matching
  build. Its explicit packet-field assignments are useful source evidence.
* [OpenRAC's toolchain notes](https://github.com/OpenRAC/rac1-decomp/blob/main/docs/TOOLCHAIN.md)
  identify SN Systems v1.14 for that game's 989snd and describe Sony 2.9 tail-call
  behavior. These are leads for another revision, not proof for Deadlocked.
* [OpenGOAL's project overview](https://github.com/open-goal/jak-project/blob/master/docs/project-overview.md)
  describes its sound implementation. It is not a matching Deadlocked EE client.
* Compiler candidates came from the
  [decomp.me compiler archive](https://github.com/decompme/compilers/releases/tag/compilers).
  No external source implementation was copied into production.

## Measured compiler evidence

The tests relocate actual compiled sections to retail addresses and resolve
external symbols from the already verified linked game. No relocation bits or
instructions are masked. Short sections receive zero padding for comparison;
overlong sections cannot match. This is a diagnostic link, **not a usable ELF**.

| Candidate | Result / interpretation |
| --- | --- |
| Existing ps2dev 3.2.3 sound flags | Reproduced 6/59 with the new probe; no overruns. |
| SCE 2.96, 3.2-030926, 3.2-040921 | No broad improvement across tested optimization/scheduling settings. |
| SCE 2.9-990721, 991111, 991111a, 991111-01 | Much closer wrapper scheduling. Initial exact-section comparisons found 19 matches before source changes and padding accounting. |
| Initial SCE 2.9-990721 packet-assignment probe | 35/59 candidate slot matches with three overflows; superseded by the integrated profile above. |
| SCE 2.9-990721, recovered branches, exceptions + SJLJ | **42/59 integrated matches**, no slot overruns; all sound cases pass. |
| SN Systems 2.95.3 v1.14, `-O2 -G8` | Only two matches in the experimental source; `sq` register saves differ from this retail library's `sd` saves. Adding `-mgp64` did not change that result. |

Several original one-argument wrappers place the return-address save between
argument setup instructions. Sony 2.9 reproduces that order; the newer compilers
tested do not. Replacing aggregate packet initializers with explicit field
stores also reproduces the retail `snd_SetMasterVolume` body under Sony 2.9.
This is strong evidence for further 2.9-family work, not a definitive compiler
identification for the entire object.

## Reproduce the initial probe (historical)

Run in an isolated Linux build environment with a verified linked game available.
The original compiler binaries need the same 32-bit stat shim used for 2.96.
Replace paths as appropriate; the example uses the investigation container.

```sh
python3 /ProjectRYNO/tools/probe_989snd.py \
  --game /ProjectRYNO/dl \
  --original /ProjectRYNO/assets/dl/boot.elf \
  --symbols-from /tmp/sdk-integration/dl/build/boot_elf.elf \
  --cc /probe/sony2.9-990721/bin/ee-gcc \
  --assembler /probe/sony2.9-990721/ee/bin/as \
  --shim /opt/ee-gcc2.96/ee296_statshim.so \
  --cflags '-O1 -G8 -fno-builtin -fno-common -fschedule-insns -fschedule-insns2' \
  --packet-assignments --output /probe/sound-reproducible
```

The tool writes generated probe source, commands, object, diagnostic ELF and
`results.json`, including hashes and per-function sizes, overruns and byte
differences. It never edits game source, Makefile, manifest, or the game ELF.
The old production-profile cross-check reproduced the starting 6/59 result:

```text
cc: /opt/ps2dev/ee/bin/ee-gcc
assembler: /opt/ps2dev/ee/bin/ee-as
cflags: -G8 -O2 -ffast-math -fno-exceptions -Os -fno-schedule-insns -fno-reorder-blocks -mno-check-zero-division
asflags: -EL -G8 -no-pad-sections
packet-assignments: off
```

## Resolved integration blockers and remaining work

The historical 35-match profile overflowed:

| Section | Generated / available bytes | Overrun |
| --- | --- | --- |
| `snd_StartSoundSystemEx`, including existing helper bodies | 628 / 568 | 60 |
| `snd_BankLoadByLoc_CB` | 388 / 344 | 44 |
| `snd_GetDopplerPitchMod` | 36 / 28 | 8 |

Without exceptions enabled, Sony 2.9 emits sibling jumps in wrappers where retail uses
`jal` and a return epilogue. Merely passing `-fno-optimize-sibling-calls` did
not remove them. The integrated exception/SJLJ settings resolve those jumps.

The direct callback now fits and matches its 48-byte slot after restoring retail
branch order. Removing the helper workarounds and selecting the new compiler
settings resolves every integrated overrun. No slots were widened and no
instructions were patched or substituted.

Remaining work is concentrated in startup, return-buffer preparation, RPC/bank
transport, stream-safe CD state, and three near-matching wrappers/arithmetic
functions. Several stateful functions save registers 16 bytes apart under this
compiler where retail packs saves 8 bytes apart. Neighboring Sony 2.9 releases,
including preserved Windows/DTLS builds, did not resolve that discrepancy;
Sony 2.96 has compact saves but the tested profiles do not match the wrapper
scheduling. This compiler choice is measured progress, not proof of the exact
original compiler for every function.

Continue from the 17 `exact: false` records in the JSON inventory. Preserve
callback ordering, 64-bit user data, reentrancy and the existing strict checks.
