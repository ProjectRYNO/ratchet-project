---
name: ryno-symbols-types
description: Recover ProjectRYNO global names and PS2 data layouts using retail Ghidra, prototype sources, and dlglobals/dltypes dumps. Use for symbol mappings, extern declarations, module headers, and ABI verification.
---

# Recover symbols and types

Use [the shared game workflow](../../guides/GAME_WORKFLOW.md) for every game.
The concrete manifests, symbols, tools, and tests below describe Deadlocked;
verify or implement equivalents for the selected game rather than copying its
addresses. Require strict executable matching before calling a change complete.

Read [AGENTS.md](../../../AGENTS.md),
[global mapping evidence](../../../src/games/dl/DOCS/symbols/GLOBAL_VARIABLES.md),
[type evidence](../../../src/games/dl/DOCS/types/RECOVERED_TYPES.md), and
[source conventions](../../../docs/decompilation/STYLE.md).

## Globals

Confirm the retail program/revision and address space in Ghidra. Inspect the
label's references, containing ELF section, existing aliases, and actual accesses.
Cross-check the name and source owner in `dlglobals.txt` and the prototype tree.
A matching name alone does not validate its address, width, array bound, or type.

Check every configured symbol file before adding a mapping. The existing
`symbols_core.text.txt` is also consumed by `gen_matching_symbols.py`, so its
recovered-global block provides names to both splitting and linking. Merely
putting a declaration in an arbitrary symbols file may not supply the link name.
Keep existing aliases unless there is a demonstrated reason to migrate them.

Use `extern` in the owning header and map the existing storage. Avoid inline asm
aliases such as `__asm__("D_...")` for a name the symbol configuration can supply.
Do not introduce a C initializer/definition just to name existing retail data.
Reject guessed version-wide address deltas, unqualified overlay matches,
ambiguous duplicate labels, and code/GP-base labels mistaken for data.
`M9454_Sparkles` at `_gp` (0x0022597F) is a known misleading example.

`src/games/tools/map_dl_globals.py` produces candidates/reports from a Ghidra
export; it does not authorize blind import. Keep accepted provenance in
`DOCS/symbols/GLOBAL_VARIABLES.csv` and unresolved research in `GLOBALS_UNMAPPED.csv`.
Inspect current tool arguments with `--help`; the mapping document has an example.
Resplit and force rebuild after symbol edits; run the global-address and ELF audits.

## Structs and declarations

Find the original module owner before choosing a header. Read the full definition
and dependencies. Compare dump offsets with Ghidra layouts and retail field
accesses. Distinguish prototype-only layouts, Ghidra database agreement, and
instruction-confirmed fields; a pre-imported Ghidra type is not independent proof.
Do not bulk-copy the dump's conflicting system types, malformed typedefs, unknown
C++ methods, or guessed callback prototypes into common headers.

Use filename-derived valid guards, no RYNO_ prefix (`SND_EE_H` for 989snd.h).
Write one typed member per line, size after the opening struct declaration, and
byte-offset comments before fields. Omit redundant tags unless a forward/self
reference needs one. Preserve packing/alignment from evidence, not convenience;
never add `packed` merely to silence a failed layout check.

PS2 layouts must be checked with the EE compiler, not inferred from a host build.
Do not modernize legacy integer typedefs without verifying their actual ABI.
Keep checks in `tests/check_type_layouts.py`, with the corresponding records in
`DOCS/types/RECOVERED_TYPES.json`. Record source ownership, dump lines, offsets, sizes,
and evidence status. Extend the checker when a new layout needs alignment,
bit-field, union, or other checks the current test does not cover.

`GameBootOptions` is an 8-byte wire payload. Its 16-bit screen offsets are packed
copies of the separate 32-bit `displayX`/`displayY` globals, not a struct instance
at their addresses. `bootSettings` is GameSettings storage; preserve this distinction.

Follow the [build/validation workflow](../../guides/DEADLOCKED.md).
Force rebuilds after header edits. A passing ABI check proves the declaration's
layout, not that every field has been verified in the retail game.
