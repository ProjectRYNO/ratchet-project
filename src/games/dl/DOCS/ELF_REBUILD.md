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
python3 ../tools/compare_elf.py ../assets/dl/boot_elf.elf build/boot_elf.elf
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
The pre-investigation sources/configuration are also archived at
`build/elf-investigation/before-split.tar.gz`.

Validated toolchain: splat64 0.41.0, spimdisasm 1.41.0, EE GCC 3.2.3, and the
GNU MIPS binutils in the existing `projectryno` Docker image.

## Validation results

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

The comparison, compiler, packer, and emulator logs are retained under
`build/elf-investigation/`, including `final-compare.txt`, `final-build.log`,
`final-iso.log`, and `pcsx2-iso-boot.log`.
