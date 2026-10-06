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

## Current issues / research backlog

| ID | Issue | Next evidence or action |
| --- | --- | --- |
| K01 | Existing C output is not fully byte-matching. | Use measured per-function slot results in the progress tracker; investigate compiler/ABI/codegen and padding without hiding differences. |
| K02 | Boot options intentionally differ for reserved padding and malformed input. | Reconcile the documented deterministic/bounded behavior with matching; do not silently reintroduce unsafe or undefined reads. |
| K03 | Full gameplay and audible sound are not established by the automated suites. | Record emulator scenarios using the smoke checklist; preserve the distinction between SDK mocks and hardware behavior. |
| K04 | RAC, GC, and UYA lack verified game Makefiles/profiles. | Establish each game's split/assembly matching baseline before borrowing the DL build design. |
| K05 | Some recovered types are prototype-only. | Validate retail access widths/offsets before using them; preserve the evidence labels in the type inventory. |

Historical failures to avoid repeating include exit/Exit filename collisions on
Windows, incorrect HI16/LO16 target aliases, misplaced section-relative linker
assignments, and stale lowercase test paths on Linux. The
[ELF reconstruction notes](../../src/games/dl/DOCS/build/ELF_REBUILD.md) and
[platform checks](../build/PLATFORM_VERIFICATION.md) describe the fixes.
See [989snd notes](../../src/games/dl/DOCS/sound/989SND_REUSE.md) for sound-specific
behavior and [type evidence](../../src/games/dl/DOCS/types/RECOVERED_TYPES.md) for
layout limits. Record new decisions with the concrete reason and evidence rather
than making a failed experiment into a universal rule.
