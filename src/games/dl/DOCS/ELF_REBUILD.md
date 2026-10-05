# Rebuilding Deadlocked's boot ELF

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

## First C++ replacement: main

`code/game/boot.cpp` now implements `main` in C++, replacing its `INCLUDE_ASM`.
It was recovered from the open Ghidra program and checked against the original
instructions at `0x00157C58`. The other five functions in this file remain
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
