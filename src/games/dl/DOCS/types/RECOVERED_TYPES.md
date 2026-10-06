# Recovered data types

> Current acceptance policy: [the shared game rules](../../../../../.agents/guides/GAME_WORKFLOW.md)
> require exact executable matching and preserved behavior. The nonmatching C
> validation described below is historical/diagnostic evidence, not a 1:1 pass.

77 types are declared in 39 module headers under `code/game`, following their
ownership in the prototype sources. `GameBootOptions` and `blockhdr` were local
to prototype `boot.cpp`; their declarations live in `boot.h` for reuse.
These are partial module headers, not complete reconstructions of every class.

Every member retains the dump's byte offset, and each struct carries its PS2
size. Bit-field comments use `byte:bit`, as in `dltypes.txt`. Header guards are
filename-based; subdirectory names distinguish module headers. Redundant struct
tags are omitted. No data allocations, Makefile changes, or linker changes are
needed for these declarations.

## Evidence and limits

Sources: the local `deadlocked-proto-decomp` tree and its `dltypes.txt`, plus
Ghidra's `/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf` program. The inventory in
[RECOVERED_TYPES.json](RECOVERED_TYPES.json) records source ownership, dump line,
size, field offsets, destination header, and evidence for each type.

* 45 types: Ghidra's named structure size, field names, and offsets match the dump.
* 31 types: recovered from the prototype and dump; no matching retail Ghidra structure was available.
* `GameBootOptions`: the retail encoder at `0x001579F0` confirms the packed
  fields and offsets. Ghidra did not have this named structure.

Ghidra layout agreement corroborates the type database; it does not prove every
retail function uses every field identically. Check retail accesses before using
prototype-only fields in new decompiled functions. Complex C++ classes, unknown
callback signatures, conflicting same-name definitions, and structures requiring
unrecovered dependencies remain deferred rather than being replaced with guessed
layouts. This pass prioritizes independent data structures from prototype headers.

## Boot options and runtime settings

`GameBootOptions` is the eight-byte serialized payload encoded as sixteen hex
digits. `screen_offset_x` is a 16-bit field at offset 4; `screen_offset_y` is a
16-bit field at offset 6. Its first word contains the display/audio bit fields.

`displayX` (`0x0021DAA8`) and `displayY` (`0x0021DAAC`) are separate 32-bit runtime
globals, known as `g_DispXPOS` and `g_DispYPOS` in Ghidra. The encoder packs their
low halves into `GameBootOptions`; the decoder restores them. They are not an
instance of the packed structure at those addresses.

`GameSettings` describes the settings storage at `bootSettings` (`0x00171D38`).
The retail boot encoder confirms `Stereo` at 8, `MusicVolume` at 12,
`EffectsVolume` at 16, `Wide` at 0xB3, and `Language` at 0xBD. `boot.cpp` now uses
those member names instead of pointer arithmetic. The remaining members and full
0xC4 extent come from the prototype/dump. No new copy of settings is allocated.
The explicit wire encoding retains deterministic padding and malformed-input
bounds from the existing implementation.

## Validation

Run `python3 tests/check_type_layouts.py` inside the project toolchain container.
The checks live outside production headers. They use the EE compiler to check
all recovered sizes and non-bit-field offsets (737 checks), each header in
isolation, and ten compiled boot-option bit-field packing vectors. The boot host tests exercise
known vectors, 4096 round trips, malformed input bounds, and untouched settings
bytes. The ELF audit checks compiled boot functions and unchanged unrelated bytes.

The Makefile does not track header dependencies. Force affected objects to
rebuild after changing a header (`make -B -j8 elf`), or use a clean build.

Verified for this change: a forced working-tree ELF build and an isolated
`full-clean -> ps2dev -> rom -> split -> elf` build passed. Both have identical
loaded bytes and runtime headers. Compared with the preceding compiled ELF,
16 bytes changed, all in the boot-option encoder's instruction scheduling;
all other loaded bytes and runtime headers were preserved. The clean build also
passed 2,720 sound-wrapper cases, 293 stateful sound cases, and the 806-global
address audit. Host boot tests passed their six argument/control-flow cases and
4,096 option round trips. Logs are under `build/type-recovery` (generated files).
No new emulator/gameplay test or ISO repack was performed for this type pass.
