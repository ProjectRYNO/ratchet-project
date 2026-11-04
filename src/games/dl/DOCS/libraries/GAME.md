# Deadlocked game code

The game code in `code/game/` was built with **SN ProDG GCC 2.95.3 v1.36**, the same compiler as the sound library, as C++ with GCC 2.x name mangling.

## Compiler profile

| Step | Setting |
|---|---|
| Compile | `ee-gcc.exe -x c++ -S -G8 -O2 -fopt-stack -mno-check-zero-division -fno-exceptions` |
| Rodata | `tools/svo3_rodata_sections.py` gives each function's jump tables their own section |
| Short loops | `tools/sound_loop_compat.py --likely` pads loops to retail's six words, including branch-likely loops |
| Assemble | SN `as.exe -EL -G8 -g` |

Evidence: `WrapValue`, `InBootUpTopPage` and `GetFormattedPlanetName` are byte-exact in the linked ELF. Those cover a short-loop leaf, a frame with calls, a constant divide and a jump table. Other flags may still be needed for floating-point and VU0 code, which has not been tested yet.

## Adding a game object

Objects opt in through `GAME_SN_NAMES` in the Makefile. Everything else stays assembly-only through the generic rule, so unconverted files cannot drift.

1. Register the object's slots. Each `INCLUDE_ASM` entry gets its own `.game_<name>` slot, and `code/include/game_section.h` makes retained assembly use it.
2. Put the section attribute first: `GAME_SECTION(name) char *name(...)`. After a pointer return type, this compiler silently ignores it.
3. Keep flat symbol names with an asm label on each declaration, so assembly callers still resolve: `char *msg_string(int) __asm__("msg_string");`.
4. Register each jump table as a slot under `rodata:` in `config/decompiled_functions.yaml`. Game tables live in `asm/build/data.data`, not a rodata file.

## Sources of names and types

`d:\PS2\ISOs\deadlocked-proto-decomp` holds prototype data. `dlfuncs.txt` has original function signatures, local names and register numbers, `dltypes.txt` has types, and `game_dl/` has decompiler output by file. `DOCS/Prototype_Directory_Func_List.txt` lists functions per source file. It comes from a prototype build, so retail can differ: the retail bytes decide.

## Verification

Only the full checkpoint proves a match, because the per-function compare masks relocations. `check_main_elf` must report exactly 726 changed bytes.
