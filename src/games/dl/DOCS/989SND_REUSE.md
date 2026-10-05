# 989snd reuse assessment

The existing public work is useful reference material, but it is not a complete,
compatible replacement for Deadlocked's EE library. The initial investigation
below was followed by a first implementation pass: **40 of 59 named EE sound
functions now compile from C**. The other 19 named functions and 18 remnant
entries still use assembly. This count describes functions, not code size; the
remaining transport/state-machine functions account for much of the code.

## First implementation pass

`code/989snd/ee/989snd.c` contains real C implementations for bank-unload and
cross-reference commands, volume/playback/reverb controls, sound play/stop/query
commands, group controls, sound-parameter updates, VAG stream commands, movie
audio commands, SRAM queries, and external calls. It also preserves Deadlocked's
two genuine cache-control no-ops as empty C functions. These were recovered
against Deadlocked's instructions, not copied from unfinished upstream stubs.

Each function has its own code section. The existing fixed-slot mechanism in
`config/decompiled_functions.yaml` places both compiled and retained assembly
sections at their original addresses. The loaded-byte audit permits differences
only for registered compiled functions; retained assembly and remnant slots
must still match byte for byte. The split preserves this handwritten C source
and regenerates its remaining includes during a clean build.

The only new Makefile adjustment is `-fno-schedule-insns` for this one object.
EE GCC 3.2.3's pre-allocation scheduler otherwise adds argument-copy instructions
that make many wrappers exceed their allocations. The scoped flag keeps all
40 implementations within their original bounds without changing other objects.

Validation completed for this pass:

* A separate full-clean build retained all handwritten sources and passed the
  compiled-symbol, fixed-address, and loaded-byte audit.
* There are 1,488 changed loaded bytes versus the extracted ELF, including the
  727 bytes from the earlier boot-function work. Every byte outside registered
  replacement slots and every runtime header matches the original.
* `tests/test_989snd_wrappers.py` passes 2,720 differential machine-code cases
  across the 40 functions. A limited MIPS interpreter runs original and rebuilt
  wrappers until the unchanged RPC transport, then compares command IDs,
  payload sizes/bytes, callback pointers, full 64-bit user data, and applicable
  return values. It exercises stack-passed arguments, boundary bit patterns,
  random values, VAG bit packing, and external-data descriptors; it also checks
  preservation of callee-saved registers. Unsupported instructions fail.
* Existing split/extraction and linker guard regressions pass.

The differential test covers wrapper behavior at the transport boundary. It
does not emulate the IOP or establish that all audio paths work during gameplay.
No ISO was repacked in this pass. Build/test logs are in `build/989snd-test`,
with independent clean-build results in its `clean` subdirectory.

```sh
make split
make -j8 elf
python3 tests/check_main_elf.py ../assets/dl/boot_elf.elf build/boot_elf.elf build/code/game/boot.o
python3 tests/test_989snd_wrappers.py ../assets/dl/boot_elf.elf build/boot_elf.elf
```

Remaining named functions cover startup, flushing/return buffers, synchronous
and asynchronous transport, batching, bank loading, volume ducking, streaming
initialization/shutdown, stream-safe CD operations, and Doppler pitch conversion.
Their original assembly remains linked and validated.

## Scope in this executable

`code/989snd/ee/989snd.c` has 77 assembly includes, covering the region
`0x00157D60` through `0x001599A4` (exclusive). There are 59 named `snd_*`
functions and 18 `func_*` entries consisting solely of stack adjustments and
nops. The latter are not ordinary callable functions and must not be blindly
converted from Ghidra's function output. Some Ghidra requests at these addresses
return no function or a misleading function spanning later code.

This is the EE-side command/RPC client. The IOP-side driver that loads banks,
streams audio, and drives the sound hardware is a separate part of the game.
The emulator previously reported the IOP driver's version as 3.1.7, built
May 10, 2005, with MIDI disabled. That banner alone does not prove an upstream
source-version match.

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

## Work required to complete the EE library

Recover the actual PS2 data structures and function signatures, retaining
32-bit pointers, 64-bit callback user data, and the existing global addresses.
Implement and test the synchronous/asynchronous transport, bank loading, and
stream-safe CD state machine against Deadlocked's assembly. Then convert the
small command wrappers and use the fixed-address function-section mechanism
to retain all entry addresses and reject code overruns. Preserve the remnant
bytes separately until their references and origin have been fully checked.

Validation needs RPC command/payload tests, completion and reentrant callback
tests, the loaded-byte audit outside the replacement allocations, a full-clean
build, and emulator checks that exercise music, effects, streaming, and movie
audio. Reaching the boot screen alone would not establish library correctness.

Reference downloads and Ghidra responses are in `build/989snd-test`; they are
temporary and are removed by full-clean. No external source is compiled into
the current build. At the end of the initial investigation (before the C wrapper
implementation), the ELF remained SHA-256
`61168f189d87ed14acf012bfbf171e770208b75d02c477f24b3706e4d36294c2`
through this investigation.
