# Rebuilding Deadlocked's boot ELF

The current build also includes 40 C replacements in the EE sound library.
See [989snd progress](989SND_REUSE.md) for their validation and remaining work.
The audit command below covers all registered boot and sound replacements.

The default build compiles the C/C++ translation units and assembles their
`INCLUDE_ASM` functions, then links a new executable. The original ELF is used
as extraction input and as a comparison reference. It is not copied into the
build output, and the linker does not read it.

Run these commands inside the ProjectRYNO build container, from `/ProjectRYNO/dl`:

```sh
make ps2dev
make rom
make split
make -B -j8 elf
python3 tests/check_main_elf.py ../assets/dl/boot_elf.elf build/boot_elf.elf build/code/game/boot.o
make iso
```

`-B` ensures existing objects compiled with the old flags are rebuilt. Run
`make` normally afterward; use `-B` when changing assembly included by a C/C++
wrapper, since the existing Makefile does not track those include dependencies.
The ELF is `build/boot_elf.elf`; the packed disc is `build/new_dl.iso`.

The baseline comparison requires identical entry point, runtime ELF header
fields, load addresses, sizes, permissions, alignment, and every loaded byte.
ELF file offsets, symbol tables, and section names can differ without changing
the loaded program. A deliberate decompilation/modification need not pass the
byte comparison, but should still preserve the game's required memory layout.

## What was broken

* `objcopy -O binary` used load addresses, producing a roughly 32 MB ROM. The
  configuration expects a packed `0x4EBFA0`-byte ROM with network code at
  `0x44E000`. The previous split read zeros instead of the network code.
  `elf_to_rom.py` now maps ELF load bytes into the configuration's ROM offsets.
* Windows cannot distinguish `exit.s` from `Exit.s`. The libc function now has
  the filename `libc_exit.s`, while its actual symbol remains `exit`.
* `.align 3`, input-section alignment, automatic section-end padding, and
  compiled empty C stubs moved functions. Generated wrappers now include the
  assembly for empty functions too; instruction alignment is four bytes and
  assembler section padding is disabled.
* The main `.text` segment begins with a block classified as rodata. It must
  precede the remaining code in the linker output.
* The old linker fix inserted `. = 0x001574E0` inside an output section. This
  was a section-relative assignment and moved the entry point to `0x271668`.
  No such assignment is needed once all functions are emitted correctly.
* Three address loads were misrelocated because separate HI16/LO16 pairs
  referenced different offsets into one large BSS symbol. Explicit symbols in
  `symbols_bss.txt` distinguish their targets.

`split_dl.py` runs splat, normalizes generated assembly for the two assemblers,
and gives the linker two runtime load segments instead of ROM-offset load
addresses. A padding segment keeps the main load length exact. Linker assertions
reject section overruns. The existing ELF header helper normalizes the ABI byte
after linking; it does not replace executable contents.

Only source files consisting entirely of generated assembly includes and empty
stubs are regenerated. Their original versions are saved once under
`build/split_source_backup`. Files with actual C/C++ implementations are retained.
Build diagnostics and backups are temporary: `make full-clean` removes them.

Validated toolchain: splat64 0.41.0, spimdisasm 1.41.0, EE GCC 3.2.3, and the
GNU MIPS binutils in the existing `projectryno` Docker image.

## Original assembly baseline validation

These results describe the assembly baseline before replacing `main` with C++.
The old `build/elf-investigation` logs were removed by a subsequent full-clean.

* A fresh `make rom`, `make split`, and forced rebuild completed successfully.
* A separate new container also passed `make full-clean`, `make ps2dev`,
  `make rom`, `make split`, and `make -j8 elf`, invoked separately. The toolchain
  was installed by the normal Makefile target, and `clean-compare.txt` confirms
  identical loaded bytes and runtime headers without any retained objects.
* All 5,158,456 bytes in the two load segments match the extracted original.
  The entry point is `0x001574E8`; runtime header fields also match.
* Four regression tests pass (`python3 ../tools/test_elf_tools.py`).
* `make iso` produced `build/new_dl.iso` (4,340,781,056 bytes).
* PCSX2 2.5.402 booted both the compiled ELF with the original disc and the
  rebuilt ISO through IOP, sound, and controller initialization, using a
  separate portable profile with cheats and memory cards disabled. Full
  gameplay has not been tested.

## First C++ replacement: main (initial validation)

`code/game/boot.cpp` now implements `main` in C++, replacing its `INCLUDE_ASM`.
It was recovered from the open Ghidra program and checked against the original
instructions at `0x00157C58`. Initially the other five functions remained
assembly includes. The generated original assembly is reference material and
is not linked for `main`.

The function processes `BOPT=`, `gooey`, and `multi` arguments, initializes lobby
controller settings, then runs the entry/ParseBin loop and flushes caches 0 and
2 between entries. The byte-sized parsed-options counter retains its wraparound
behavior. EE GCC 3.2.3 requires an explicit `__main()` runtime initialization
call here. Existing data symbols provide the option strings and globals.

The compiler emits 260 bytes (`0x104`), the original function size, at the
original address. The instructions are not byte-matching: 203 loaded bytes
change, all within main's `0x108`-byte allocation including trailing padding.
Every other loaded byte and runtime ELF header matches the extracted original.
`check_main_elf.py` also verifies that main is a real function defined in the
compiled object and ELF, with no `main.NON_MATCHING` assembly definition.
The whole-file loaded-byte comparison intentionally fails for this replacement.

Two build-tool details matter for subsequent decompilation:

* Splat's `do_c_func_detection` is enabled so a clean split regenerates the
  remaining assembly includes while preserving handwritten C++.
* `gen_matching_symbols.py` uses `PROVIDE` fallbacks so object definitions take
  precedence. Functions registered in `config/decompiled_functions.yaml` have
  no fallback address. The manifest also makes the generated linker script
  assert entry addresses and object bounds, padding smaller objects to keep
  later code fixed. Add equivalent bounds when converting other objects.

The Makefile changes for this experiment are limited to the symbol generator's
manifest argument and dependencies. Keep `ALLOW_NONMATCHING=0`; enabling it
suppresses the assembly that the mixed build still needs. Larger replacements
will require an explicit placement strategy because existing raw pointers and
assembly references constrain addresses.

Validation for this C++ version:

* A separate container passed full-clean, toolchain installation, ROM extraction,
  split, compilation, and the ELF audit, with no retained objects or assembly.
  The handwritten source remained unchanged after splitting.
* Six host argument cases, runtime initialization, two level transitions, and
  cache-call ordering pass in `tests/boot_main_test.cpp`.
* `tests/check_main_link_guards.py` verifies that a valid object links and that
  missing main, moved main, and oversized objects fail the link.
* The four extraction/split regression tests still pass.
* PCSX2 booted this ELF with the original ISO through sound and controller
  initialization in an isolated portable profile. Full gameplay is untested.
  This experiment did not repack the ISO; `make iso` packs the new ELF afterward.

Current diagnostic logs are under `build/main-test`, including `build.log`,
`clean-main-check.txt`, and `pcsx2-boot.log`. To run the additional checks:

```sh
python3 ../tools/test_elf_tools.py
python3 tests/check_main_link_guards.py
g++ -std=c++98 -O2 -fno-builtin -Icode/include tests/boot_main_test.cpp -o /tmp/boot-main-test
/tmp/boot-main-test
```

The last two commands use a host C++ compiler; that compiler is only needed for
the behavior test, not the PS2 build.

## Boot-option encoder and decoder

`code/game/boot_options.cpp` adds C++ replacements for
`GetBootOptionsFromSettings` at `0x001579F0` and
`ApplyBootOptionsToSettings` at `0x00157B30`. Their original includes have been
removed from `boot.cpp`. Three functions there still use assembly: `unpackbuff`,
`ParsePatch`, and `ParseBin`.

The wire format is eight little-endian bytes represented by sixteen uppercase
hexadecimal digits. The first word holds one-bit flags at bits 0, 1, and 2,
eleven-bit values at bits 3 and 14, and a three-bit value at bit 25. The second
word contains the low sixteen bits of the display X and Y positions.
The implementation uses the original globals and preserves unrelated settings.

Two intentional differences apply to undefined/malformed original behavior:

* The original encoder exposed uninitialized stack bits in reserved bits 28..31.
  The C++ encoder clears them. The original decoder ignores those bits.
* The original decoder could overrun its stack or read uninitialized bytes for
  long/short input. The replacement reads at most eight complete pairs and
  zero-fills missing pairs. Complete invalid pairs retain the original -1 nibble
  arithmetic; lowercase is not accepted as hexadecimal.

These changes do not alter the decoded settings for valid game-generated input.
The encoder writes sixteen characters plus a terminating null; callers need a
17-byte output buffer.

The functions use separate code sections, registered as fixed address slots in
`config/decompiled_functions.yaml`. `split_dl.py` inserts each section at its
original address, fills the unused space with zeros, and rejects overflow.
This allows shorter compiled functions without shifting main or later code.
No additional Makefile changes were needed for these two replacements.

Current ELF audit: encoder size `0x104` within its `0x140` allocation, decoder
size `0x128` within its `0x128` allocation (including the original trailing nop),
and main size `0x104` within its `0x108` allocation. All three are compiled
function symbols, with no corresponding original assembly definitions linked.
727 loaded bytes differ from the original, all within those three slots.
Every other loaded byte and runtime header matches. A separate full-clean
rebuild also passes this audit.

`tests/check_main_elf.py` now audits all three functions using the manifest.
`tests/boot_options_test.cpp` checks known vectors, field masking, untouched
settings, output bounds, malformed input, and 4096 deterministic round trips.
It passes with AddressSanitizer and UndefinedBehaviorSanitizer:

```sh
g++ -std=c++98 -O2 -fsanitize=address,undefined tests/boot_options_test.cpp -o /tmp/boot-options-test
/tmp/boot-options-test
```

The existing main behavior tests and extraction/split tests still pass. Linker
tests also cover separate function sections, incorrect entry addresses, and
slot overflow. Current build/reference diagnostics use the `options-*` and
`ghidra-*-boot-options.c` files under `build/main-test`.

The working-directory build and isolated full-clean build have identical
runtime headers and all 5,158,456 loaded bytes (their non-runtime ELF metadata
differs). PCSX2 loaded this new ELF from its build path with the original disc
and reached sound/controller initialization; see `options-pcsx2-boot.log`.
Full gameplay and boot-option behavior inside the emulator remain untested;
option behavior is covered by the host tests above. This step did not repack
the ISO. Run `make iso` after building to package the current ELF.
