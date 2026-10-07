# iksemel XML library

## Accessors (2026-10-07)

The first library batch replaces six INCLUDE_ASM entries in `iksemel/src/iks.c`:

| Function | Retail entry | Original allocation |
| --- | --- | --- |
| iks_next | 0x01EE38EC | 0x14 |
| iks_parent | 0x01EE394C | 0x14 |
| iks_child | 0x01EE3960 | 0x14 |
| iks_type | 0x01EE3A84 | 0x14 |
| iks_name | 0x01EE3A98 | 0x14 |
| iks_cdata | 0x01EE3AAC | 0x14 |

Evidence: retail Ghidra program `/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose`
(`DL_Retail_BootELF_974.65.elf`, r5900 little-endian), original split instructions,
and the prototype `iksemel/src/iks.c`. Ghidra's inferred void signatures are not
authoritative: instructions consume a node pointer in a0 and return a word in v0.
The six functions return zero on null, otherwise the field at 0, 0x18, 8,
0x1C, 0x24, or 0x28. Retail lw sign-extends the word into the EE register.

`iks.h` documents the 0x30-byte node with one member per line and PS2 offsets.
The self-referential struct tag is required. dltypes.txt has an iks typedef and
enum, but no complete node layout; retail construction/insertion accesses
establish the fields. No external library implementation was copied.

Placement uses the existing manifest and source-local assembly sections for the
13 remaining routines. No splitter or linker-generator changes are needed.
Only this object's compiler flags add `-falign-functions=4`: the default eight-byte
alignment pads 20-byte functions to 24 bytes and overflows their original slots.
The rest of the compiler flags remain unchanged.

Run `python3 TESTS/check_iksemel.py ../assets/dl/boot_elf.elf build/boot_elf.elf`
inside `/ProjectRYNO/dl` (use the checkout's actual TESTS/tests spelling).
The verifier includes this check. It checks real compiled symbols, whole-module
bytes from 0x01EE3570 through 0x01EE3CEC, node ABI, and 774 original/rebuilt
instruction-interpreter cases. The existing interpreter rejects unsupported
instructions; cases include null nodes, null fields, arbitrary values, and the
high-bit/sign-extension boundaries. Stores and calls are forbidden.

## Next library work

`iks_next_tag` and `iks_has_children` were inspected but remain in assembly:
the trial C changed register allocation/branch scheduling. Allocation, insertion,
search/escaping, SAX/DOM parsing, and stack functions also remain to decompile.
Continue with library code before `game/`, as requested. A matching accessor is
not a claim that the entire XML library or full ELF is matching or decompiled.

## Verified result

Serial split followed by `make -B -j8 elf` succeeded. The complete new ELF's
loaded bytes and runtime headers equal the previous development build. All six
new C allocations and the entire iks.c module match retail exactly. The verifier
passed compiled-symbol/slot checks, 806 globals, 750 layout checks across 78
types, both sound suites, and the new 774-case accessor suite. Nine verifier
orchestration tests also passed. Reports: `build/iksemel-work/verification`;
build and baseline comparison logs are in `build/iksemel-work`.

The whole-ELF strict comparison remains NONMATCH with the existing 5,130
differing bytes. Progress is now 68 compiled functions, 12 matching slots and
56 nonmatching slots. No new gameplay or ISO pack was performed. Use the local
ELF override launcher with original disc assets for further runtime testing.
