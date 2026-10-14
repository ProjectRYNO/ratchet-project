# Build decisions and known issues

These entries explain current constraints. Recheck source/tool evidence before
changing a mechanism; this is not a ban on justified improvements.

## Decisions

| ID | Decision and reason | Evidence / consequences |
| --- | --- | --- |
| D01 | Keep function sections and original slot bounds. Public addresses and raw pointers constrain placement. | `decompiled_functions.yaml`, `split_dl.py`; a single section per source file can shift entries. Never enlarge a slot into its neighbor. |
| D02 | Run splitting before compilation, serially. | Split post-processing normalizes alignment and regenerates the linker layout. Compiling midway previously shifted addresses. |
| D03 | Force compilation after header/INCLUDE_ASM edits. | The Makefile lacks complete dependency tracking; stale objects previously kept old D_ references after symbol renames. |
| D04 | Preserve the 989snd object's size-oriented flags and retained remnant words. | `-Os -fno-schedule-insns -fno-reorder-blocks -mno-check-zero-division`; see the sound notes. Do not apply these globally or remove section guards. |
| D05 | Pack ROM from configured load ranges, not raw RAM-address objcopy output. | Deadlocked network code lives far away in memory; the split ROM is packed. See ELF reconstruction history. |
| D06 | Bind names to existing storage with extern/symbol mappings. | Allocating another C global is not a rename. Prototype layouts/addresses need retail validation. |
| D07 | Matching and development usability are separate results. | Nonmatching development builds may compile/run; exact matching remains the goal. The verifier returns nonmatching separately and offers a strict gate. A genuinely matching C build must not be rejected merely for having zero changed bytes. |
| D08 | Preserve source/module ownership and keep tests external. | Boot options belong in boot.cpp; header ABI checks and host-test branches do not belong in production declarations. |
| D09 | Switch jump tables of compiled functions get read-only data slots at their retail addresses (decided 2026-10-14). Retail keeps each SVO3 function's tables in the main `.rodata`; without a slot, `switch` code cannot match. | `tools/svo3_rodata_sections.py` moves each SVO3 function's `.rdata` into `.svo_<Module>_<fn>.rodata` (contents unchanged). `decompiled_functions.yaml` `rodata:` lists each slot (exactly the retail table extent, code-address entries only, owning function named). `split_dl.py` carves the retail data at slot bounds and places the compiled section with overflow assertions; unregistered sections are discarded, so a missing slot fails the link. `check_main_elf.py` allows changes only inside slots of registered compiled functions. Ten SVO3 table slots are registered; all ten match retail. Extended to iksemel on 2026-10-14: the same helper routes `.iks_*` tables; later tables of one iksemel function receive numbered sections, preserving inter-table padding. Five iksemel slots and all 40 functions now match without relocation masking. |
| D10 | Classify retail zero padding as `junk` textbin segments, not functions (decided 2026-10-14). | splat labelled `func_01F27658` inside 150,332 zero bytes after the last SVO3 function (0x01F0C844..0x01F31380). The range is now `junk/net.text/4c0844_4e5380`; the fake function and its slot were removed. Loaded bytes are unchanged. |

## Current issues / research backlog

| ID | Issue | Next evidence or action |
| --- | --- | --- |
| K01 | Existing C output is not fully byte-matching. | Use measured per-function slot results in the progress tracker; investigate compiler/ABI/codegen and padding without hiding differences. |
| K02 | Boot options intentionally differ for reserved padding and malformed input. | Reconcile the documented deterministic/bounded behavior with matching; do not silently reintroduce unsafe or undefined reads. |
| K03 | Full gameplay and audible sound are not established by the automated suites. | Record emulator scenarios using the smoke checklist; preserve the distinction between SDK mocks and hardware behavior. |
| K04 | RAC, GC, and UYA lack verified game Makefiles/profiles. | Establish each game's split/assembly matching baseline before borrowing the DL build design. |
| K05 | Some recovered types are prototype-only. | Validate retail access widths/offsets before using them; preserve the evidence labels in the type inventory. |
| K06 | Retired asset-bank repacking could corrupt debug-font extraction in rebuilt discs. | Superseded by boot-only CLI replacement, which preserves original game data. Full-disc byte comparison verifies preservation; keep emulator checks separate. |
| K07 | ps2dev ee-gcc 3.2.3 never emits MIPS sibling (tail) calls; retail does. Tail-calling functions and wrappers cannot fit retail slots. | **Decided 2026-10-13 (user):** SVO3 objects build with SCE ee-gcc 2.96-ee-001003-1 and its bundled `as` (Makefile `ee-gcc296` target, SVO3 rule); the rest of the game stays on 3.2.3. **Extended 2026-10-13 (user) to iksemel**, which ships with SVO3: 9/9 probed functions matched under 2.96 `-Os` vs 1/9 under 3.2.3; it uses the SVO3 flags minus `-mno-split-addresses` (`src/games/dl/DOCS/libraries/IKSEMEL.md`). The compiler is 32-bit and runs through `src/games/tools/ee296_statshim.c` (LD_PRELOAD) for bind-mount stat. Evidence: `src/games/dl/DOCS/libraries/SVO3_TAIL_CALL_BLOCKERS.md`. Do not widen slots. |
| K07 | ps2dev ee-gcc 3.2.3 never emits MIPS sibling (tail) calls; retail does. Tail-calling functions and wrappers cannot fit retail slots. | **Decided 2026-10-13 (user):** SVO3 objects build with SCE ee-gcc 2.96-ee-001003-1 and its bundled `as` (Makefile `ee-gcc296` target, SVO3 rule); the rest of the game stays on 3.2.3. The compiler is 32-bit and runs through `src/games/tools/ee296_statshim.c` (LD_PRELOAD) for bind-mount stat. Evidence: `src/games/dl/DOCS/libraries/SVO3_TAIL_CALL_BLOCKERS.md`. Do not widen slots. Sony `as` also runs with `-g` (no assembler delay-slot reordering, matching retail; only `.mdebug`, which the linker discards, changes). |

Medius compiler finding (2026-10-13): the recovered
`medius/rt_util/rt_memory` functions use SCE `2.96-ee-001003-1` plus bundled
`as`, with `-O2 -G0` and default split-address optimization. Three functions
(184 bytes) match retail exactly; the complete 776-byte module is preserved.
Only this verified object uses the new Medius rule. Other Medius components and
historical compiler identity remain unproven. See
[src/games/dl/DOCS/libraries/MEDIUS.md](../../src/games/dl/DOCS/libraries/MEDIUS.md)
for the controlled compiler matrix, flags, and verification limits.

SDK compiler finding (2026-10-13): `code/sdk` uses the SCE 2.96 compiler and
bundled assembler with its own `-O2 -G0` profile, preserving default split-address
optimization and alignment. Seven C probes across three modules match 744 retail
bytes; the fourth module still needs a C probe. Switching the four assembly-only
objects to this rule preserves every loaded byte in the isolated full rebuild.
See [SDK compiler evidence](../../src/games/dl/DOCS/libraries/SDK.md).

Historical failures to avoid repeating include exit/Exit filename collisions on
Windows, incorrect HI16/LO16 target aliases, misplaced section-relative linker
assignments, and stale lowercase test paths on Linux. The
[ELF reconstruction notes](../../src/games/dl/DOCS/build/ELF_REBUILD.md) and
[platform checks](../build/PLATFORM_VERIFICATION.md) describe the fixes.
See [989snd notes](../../src/games/dl/DOCS/sound/989SND_REUSE.md) for sound-specific
behavior and [type evidence](../../src/games/dl/DOCS/types/RECOVERED_TYPES.md) for
layout limits. Record new decisions with the concrete reason and evidence rather
than making a failed experiment into a universal rule.
