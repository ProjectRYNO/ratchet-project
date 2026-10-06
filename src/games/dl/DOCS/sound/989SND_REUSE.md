# 989snd EE decompilation

> Current acceptance policy: [the shared game rules](../../../../../.agents/guides/GAME_WORKFLOW.md)
> require exact executable matching and preserved behavior. The nonmatching C
> validation described below is historical/diagnostic evidence, not a 1:1 pass.

All **59 named EE sound functions compile from C** in
`code/989snd/ee/989snd.c`. This includes startup, RPC transport and batching,
asynchronous completion, bank loading, ducking, stream-safe CD operations,
movie/stream command wrappers, and Doppler conversion. There are no remaining
`INCLUDE_ASM` functions in this translation unit.

This covers the EE client in `boot.elf`, not the separate IOP sound driver.
Eighteen `func_*` entries are stack-adjustment/nop remnants, not callable
functions. Their original words remain as constant arrays in fixed sections;
the audit requires those bytes to remain exact. Executable function bodies are
compiled C, not original ELF code copied into the output.

## Recovery and layout

The open retail Ghidra program was consulted first. The prototype sources and
`dltypes.txt`, `dlfuncs.txt`, and `dlglobals.txt` in
`D:/PS2/ISOs/deadlocked-proto-decomp` supplied names, signatures, and layouts.
Prototype addresses were not substituted for retail addresses. The new
`989snd.h` binds typed declarations to existing retail state, using 32-bit
pointers and 64-bit callback data. Struct comments document the recovered
sizes and field offsets.

All 54 recovered global names used by the sound and boot code are registered in
`config/symbols_core.text.txt`. Their C/C++ declarations use plain names without
assembler aliases. The mappings were cross-checked against the open retail
Ghidra program. The migration required no Makefile or linker-code changes.
The clean-build audit verifies all 54 addresses and identical runtime headers
and loaded bytes before and after the rename. Both sound differential suites
and the boot tests pass; migration reports are in `build/global-symbols`.

Every public entry retains its original address, from `0x00157D60` through
`0x00159988`. The manifest and linker reject missing compiled functions and slot
overruns. Two small C helpers occupy spare space inside the initialization slot:
file-load completion and CD callback replacement. They do not move public
entries or consume remnant bytes.

The existing object-specific Makefile flag line now uses `-Os`,
`-fno-schedule-insns`, `-fno-reorder-blocks`, and `-mno-check-zero-division`.
These avoid code growth from this old EE compiler. The last flag removes a
redundant check for the constant divisor 741. Other objects retain their flags.
The split tool and main build rules did not need changes for this pass.
The RPC binding retry delay is a volatile C countdown; its instruction timing
is not identical to the original nop-based delay.

## Validation

* An independent full-clean, ROM preparation, split, and ELF build preserved
  the handwritten source and produced all 62 registered compiled functions
  (59 sound functions and the three earlier boot functions).
* The ELF audit finds **5,131 changed loaded bytes**, all inside registered C
  slots. Every other loaded byte, all remnant words, runtime headers, and entry
  address match the extracted ELF. No fallback assembly bodies are linked for
  the compiled functions.
* The working-directory ELF and independent clean ELF have identical runtime
  headers and all 5,158,456 loaded bytes.
* `tests/test_989snd_wrappers.py` checks 2,720 original-versus-compiled machine
  code cases across the original 40 functions.
* `tests/test_989snd_state.py` checks 293 cases across the remaining 19, including
  RPC payloads, queue limits/alignment, polling, cache endpoints, callback
  clearing/reentrancy, full 64-bit user data, CD delegation, and arithmetic
  boundaries. Twelve cases execute the sound functions together, mocking only
  SDK calls and application callbacks. Unsupported instructions fail the tests.
* PCSX2 booted the independently compiled ELF with the original disc through
  sound-driver and controller initialization (`pcsx2-boot.log`).
* The four ELF tool regressions and seven linker-guard cases pass.

Logs and the independent ELF are in `build/989snd-final`. The final full-clean
run passes the ELF audit and both differential suites; its logs are under
`build/989snd-final/clean`. The focused tests are no longer ignored by Git,
despite the repository's general exclusion of scratch test directories.

These tests simulate SDK completion, not IOP timing or audible output. Full
gameplay coverage of music, effects, movies, and streaming remains necessary.
No ISO was repacked in this pass.

Run split and compilation sequentially: split normalizes generated assembly
after splat finishes, and compiling before that step completes can insert padding.

```sh
make split
make -j8 elf
python3 tests/check_main_elf.py ../assets/dl/boot_elf.elf build/boot_elf.elf build/code/game/boot.o
python3 tests/test_989snd_wrappers.py ../assets/dl/boot_elf.elf build/boot_elf.elf
python3 tests/test_989snd_state.py ../assets/dl/boot_elf.elf build/boot_elf.elf
```

## Scope in this executable

The EE library occupies `0x00157D60` through `0x001599A4` (exclusive): 59 named
functions and 18 remnant entries. The IOP driver loads banks, streams audio,
and drives the sound hardware separately. Its observed banner identifies
version 3.1.7, built May 10, 2005, with MIDI disabled. That banner does not
establish compatibility with another game's source version.

## External references checked

* [Ziemas/989snd](https://github.com/Ziemas/989snd), specifically
  [ee/989snd.c at 5cc91510](https://github.com/Ziemas/989snd/blob/5cc91510ed26b6a3f03f2d502d3d3b67d7dfb7cc/ee/989snd.c).
* [OpenGOAL's sound adapter](https://github.com/open-goal/jak-project/blob/master/game/sound/sndshim.cpp)
  and its `game/sound/989snd` implementation.

OpenGOAL's adapter creates a host-side C++ sound player and uses simulated SPU
memory. Several hardware-facing operations are deliberately empty or return
fixed values there. It does not provide Deadlocked's EE-to-IOP RPC transport,
and cannot be substituted for it in a PS2 boot ELF.

The standalone PS2 decompilation is closer, but its checked EE file contains
160 address-annotated function bodies, 133 of which contain `UNIMPLEMENTED()`.
Of the 59 named functions used by Deadlocked:

| Upstream status | Count |
| --- | ---: |
| Body present without an unfinished marker | 16 |
| Body contains an `UNIMPLEMENTED()` path | 43 |

The first category is not a claim of correctness or binary compatibility.
The second includes both empty stubs and partially implemented functions.
See [the per-entry inventory](989SND_INVENTORY.csv) for addresses and status.

## Concrete differences checked against Deadlocked

* `snd_StartCaching` (`0x00159120`) and `snd_SendCache` (`0x00159128`) are
  actual no-ops in Deadlocked (return plus a nop). They should remain no-ops
  when decompiled, even if another version has useful caching implementations.
* `snd_FlushSoundCommands` sends a waiting batch when `gCaching == 0`.
  The checked upstream implementation tests the opposite condition.
* Deadlocked invalidates the load-return buffer before testing it. The upstream
  flush implementation instead calls a general cache writeback.
* Deadlocked clears the load callback and its 64-bit user data before invoking
  the saved callback. Upstream clears them afterward. This matters if the
  callback starts another operation.
* `snd_SendIOPCommandAndWait` uses a 12-byte synchronous return transfer in
  Deadlocked; upstream uses the size of a 16-word buffer. The external-data
  command path is implemented in Deadlocked but unfinished upstream.
* `snd_SendIOPCommandNoWait` also has an external-data command path, command
  alignment, finite queue capacity, and callback records that need to match
  the original. Replacing this with an upstream stub would break normal use.
