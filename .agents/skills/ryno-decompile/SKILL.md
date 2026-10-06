---
name: ryno-decompile
description: Recover a ProjectRYNO retail function as C/C++ and integrate it into the fixed-address mixed assembly build. Use for INCLUDE_ASM replacements and behavioral corrections to decompiled functions.
---

# Decompile a retail function

Use [the shared game workflow](../../guides/GAME_WORKFLOW.md) for every game.
The concrete manifests, symbols, tools, and tests below describe Deadlocked;
verify or implement equivalents for the selected game rather than copying its
addresses. Require strict executable matching before calling a change complete.

Read [AGENTS.md](../../../AGENTS.md), the
[source conventions](../../../docs/decompilation/STYLE.md), and the
[validation workflow](../../guides/DEADLOCKED.md).

## Establish the function

Use Ghidra first when it is available. Confirm the active program is the intended
retail revision, not the prototype or another overlay. Record the address, name,
size/boundaries, callers, referenced globals, and original owning source file.
Select the program explicitly on tool calls; qualify address spaces for overlays.
Locate the same address/name in the split assembly and symbol/config files.

Read decompiled output together with instructions. Check delay slots, signed and
unsigned loads/comparisons, narrowing, 64-bit arguments/results, register-passed
arguments, struct returns, callbacks, and observable store/call order. Recover
callback signatures from actual callers; do not turn unknown arguments into void.
Consult prototype code and matching library sources for names and intent, but
verify retail differences. If reusing upstream code, preserve its attribution and
license requirements. An external reimplementation is not proof of PS2 ABI behavior.

## Implement and place

Keep the function in its original translation unit. Replace only its INCLUDE_ASM
entry, retaining untouched functions. Use the established EE C/C++ dialect
(GCC 3.2.3, C++98-compatible code), correct C linkage for assembly-facing names,
and verified globals/types. Do not assume host pointer or integer widths.

Inspect `config/decompiled_functions.yaml`, `tools/split_dl.py`, and
`tools/gen_matching_symbols.py` (tools are under `src/games/tools`). Register the
function's real entry address and its placement within the owning object's bounds.
Use an existing slot entry as the schema example: object, section, start, end.
The section attribute in source must match the manifest. Preserve remaining
assembly/remnant slots, ordering, and padding. Adding a new object may require
supported object bounds as well as a function entry; do not invent spare space.

Resplit, then force compilation. Inspect symbol type, address, compiled size, and
object section. A slot overrun requires smaller equivalent code or an explicitly
justified placement design, not a larger end address that overlaps its neighbor.
Account for compiler-generated helpers, pools, and constants too. Avoid global
compiler-flag changes to fit one function. Missing implementations must fail to
link, not resolve to the original address through a fallback.

## Demonstrate behavior

Run the strict original/rebuilt comparison, the ELF slot audit, and relevant
behavior checks from the workflow. Add focused
cases for new logic, boundaries, side effects, callback ordering, or ABI handling;
prefer original-versus-compiled comparison when the harness supports it. Do not
teach an interpreter to silently ignore unsupported instructions.

Record existing differences in undefined/malformed behavior as matching backlog,
not automatic exemptions. Do not introduce new deviations. Historical DL boot code
currently has these behaviors (preserve working code until reconciling matching):
explicit `__main()`, cache calls 0 and 2, bounded option decoding, and
deterministic reserved bits. For sound, read
[989snd notes](../../../src/games/dl/DOCS/sound/989SND_REUSE.md): this is the EE client,
not the IOP driver; callback user data is 64-bit and completion is reentrant.

Conclude with address/module, evidence, source/manifest changes, actual checks,
and remaining runtime uncertainty. Leave uncertain functions in assembly and
record what evidence is missing instead of claiming a completed decompilation.
