# Deadlocked game code

The game code in `code/game/` was built with **SN ProDG GCC 2.95.3 v1.36**, the same compiler as the sound library, as C++ with GCC 2.x name mangling.

## Compiler profile

| Step | Setting |
|---|---|
| Compile | `ee-gcc.exe -x c++ -S -G8 -O2 -g -fopt-stack -mno-check-zero-division -fno-exceptions` |
| Rodata | `tools/svo3_rodata_sections.py` gives each function's jump tables their own section |
| Short loops | `tools/sound_loop_compat.py --likely` pads loops to retail's six words, including branch-likely loops |
| Assemble C++ | SN `Ps2EeAs.exe -G8`, the assembler the driver selects with `-snas` |
| Assemble retained asm | The PS2SDK `as -EL -G8 -no-pad-sections`, as in the generic rule, because `Ps2EeAs` cannot parse `macro.inc`; merged with `ld -r` |

`Ps2EeAs` is what makes globals and floats match. It reaches external globals with `lui/%lo` and uses `$gp` only in branch delay slots, where it cannot expand, and it adds the `nop` after `mtc1` and loads float constants through `$1`. GNU `as` does none of these. Symbols retail defines in the same file use `$gp` everywhere, so those functions need their data defined in that object.

Evidence: 341 functions are byte-exact in the linked ELF, across short loops, frames with calls, constant divides, jump tables, globals and floating point. VU0 code has not been tested.

Two tools make `Ps2EeAs` objects usable: `game_fix_symtab.py` reorders its invalid symbol table for GNU `ld` and trims its section padding, and `ld -r` needs `-EL` or the merged object comes out big-endian.

`-g` matters because its line labels make `Ps2EeAs` pad `div` opcodes it sees near a branch destination, giving retail's `nop nop div.s`.

`-ffast-math` is per file, set with a `// GAME_EXTRA_FLAGS: -ffast-math` line that the build and `game_test.py` both read. It makes GCC emit `max.s` and `min.s`, but it also turns divides by constants into multiplies, which breaks `transitionmulti`. So far only `tfragfunc` needs it, and retail may simply have used it for some files.

## Adding a game object

Objects opt in through `GAME_SN_NAMES` in the Makefile. Everything else stays assembly-only through the generic rule, so unconverted files cannot drift.

1. Register the object's slots with `tools/game_register.py`. Each `INCLUDE_ASM` entry gets its own `.game_<name>` slot, and `tools/game_asm_parts.py` builds retained assembly into it.
2. Put the section attribute first: `GAME_SECTION(name) char *name(...)`. After a pointer return type, this compiler silently ignores it.
3. Keep flat symbol names with an asm label on each declaration, so assembly callers still resolve: `char *msg_string(int) __asm__("msg_string");`.
4. Register each jump table as a slot under `rodata:` in `config/decompiled_functions.yaml`. Game tables live in `asm/build/data.data`, not a rodata file.

## Sources of names and types

`d:\PS2\ISOs\deadlocked-proto-decomp` holds prototype data. `dlfuncs.txt` has original function signatures, local names and register numbers, `dltypes.txt` has types, and `game_dl/` has decompiler output by file. `DOCS/Prototype_Directory_Func_List.txt` lists functions per source file. It comes from a prototype build, so retail can differ: the retail bytes decide.

## Tools

| Tool | Use |
|---|---|
| `game_test.py SRC [--show FUNC]` | Compile a test file and compare each section with retail. Safe in parallel. |
| `game_register.py NAME...` | Register an object's slots and add it to `GAME_SN_NAMES`. |
| `game_integrate.py LIST` | Move verified functions from test files into `code/game/`. |
| `game_labels.py NAME...` | Add any missing `__asm__` labels. |
| `game_symbols.py LOG` | Derive undefined data symbols from the retail instructions that reference them. |
| `game_tables.py` | Register unregistered jump tables as rodata slots. |
| `game_verify.sh` | Run the compare on the real `code/game` sources. |
| `game_round.sh` | Harvest, verify, build and checkpoint in one run. |

## Known limits

- **Same-file data:** retail uses `$gp` for symbols defined in the same source file. Declare those `GAME_GP_DATA` (see `game_section.h`), and `game_fix_symtab.py` turns the definition back into an external reference, so the real bytes stay in the retained data segment.
- **`bool`:** this compiler's `bool` is 4 bytes, but retail structs use 1-byte fields, so test files use `unsigned char`. A flag may be missing.
- **Inline asm:** the rules for game code are undecided, so functions that need it stay as retained assembly.

## Verification

Only the full checkpoint proves a match, because the per-function compare masks relocations and ignores jump table contents. It caught a wrong table entry in `MODELEVEL_HandleOcclusionExceptions` that the compare called exact. `check_main_elf` must report exactly 726 changed bytes.
