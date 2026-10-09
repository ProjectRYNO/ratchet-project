# SVO3 current handoff, 2026-10-09

**842/935 (90.1%) compiled; 93 INCLUDE_ASM entries remain**. The 90% milestone is reached; 100% remains unfinished.
This batch is uncommitted, based on the user's checkpoint 4dd4d88.
Keep game/ last and use the native ratchet-ps2-cli workflow.

## Browser/page, grid/list and login continuation (2026-10-09)

Current verified coverage: **842/935 (90.1%) compiled; 93 INCLUDE_ASM entries remain**. 57/97 files are assembly-free.
This batch adds 45 C/C++ replacements. Per-module counts:

- CreateGameTagModule: 5
- LoginTagModule: 2
- ListBoxTag: 6
- GenericListBoxTag: 6
- GridTag: 6
- SVBrowser: 10
- CPage: 10

Retail Ghidra and split instructions were checked against prototype sources and
dltypes. Recovered login/create-game response handling; list construction, drawing,
selection and input; grid selection, modal input and cell parsing; browser/page
construction, cleanup, transitions and download handling. Generic-list input uses
the retail callback at 0x1C; list-box input checks focus mode at 0x284. These differ
from misleading Ghidra field/method labels. Preserved assertion paths, repeated
callbacks and retail state/store ordering.

Sequential split and forced full ELF rebuild PASS. Whole-ELF compiled-origin,
entry-address and slot audit PASS: 93,193 changed loaded bytes are confined
to registered replacement slots; every other loaded byte and runtime header matches.
Strict executable comparison remains NONMATCH. This percentage measures compiled
functions, not exact matching or gameplay correctness.

Layout checks: PASS: independent header includes and 10 EE boot-option packing vectors; PASS: 1889 PS2 sizes/field offsets across 210 types and 101 headers
Global-address check PASS. PASS: 67 batch globals at verified retail addresses.
New behavior suites, gameplay, ISO packaging and full-clean tests were deferred
per the user's request to prioritize decompilation. No Makefile/linker changes,
slot widening, fallback substitutions or embedded retail instruction arrays.

Five parent candidates remain explicit assembly because they exceed their slots:
LoginTagModule ScanTags___dupe6 (0x88/0x84), ListBoxTag getSelectedItem (0xD4/0xD0)
and populateListboxItems (0x1CC/0x1C4), GridTag CalculateGridHeight (0xB0/0xA8)
and HandleColumnShuffling (0x130/0x12C). Source bodies are preserved in
SVO3_GRID_LIST_SLOT_BLOCKERS.md. Earlier blocker documents are historical;
consult current source before repeating experiments.


Artifact: `src/games/dl/build/boot_elf.elf`.
Original SHA-256: `ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7`.
Rebuilt SHA-256: `f3237ff01a09640fa1a9ee54409b7f4d2d5d1b0936ca136434dc5a4b37d4f88c`.
Project: 910 compiled / 7715 assembly;
159 matching / 751 nonmatching slots.
Validation logs: `build/svo-library-work/ninety-*`; second-agent recovery metadata:
`browser-page-next-results.json`. Durable remaining inventory: SVO3_REMAINING.csv.

Retail Ghidra: `/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose`, R5900 LE32.
Prototype: `D:/PS2/ISOs/deadlocked-proto-decomp`, including dltypes.txt.
Read repository skills/rules before continuing. User permits fitting nonmatching
C/C++ with new behavior suites deferred. Keep ALLOW_NONMATCHING=0 and original slots.
No pending oversized C bodies remain in production. The earlier approval-review
quota interruption was resolved when the user replenished their allowance.

Preserve PageRequestListener padding: GetLastContentType ends 0x01F0C844,
zero gap to 0x01F27658, NOP extent through 0x01F31380. Padding is not compiled code.
Owned build container: projectryno-svo75. No commit/push performed for this batch.
