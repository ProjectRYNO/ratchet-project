# SVO3 continuation handoff, 2026-10-07

Current verified checkpoint: **562/935 (60.1%) compiled, 373 INCLUDE_ASM**.
The 75% request is not complete: 702 compiled functions are required, another
140 from this checkpoint. There are still 47 entirely C++ files and 50 mixed
files across the 97-file inventory. Keep game/ last.

Latest batch adds 87 functions in 16 modules: FormTag, form-parent registration,
list-box access/mutation, page helpers, text/password helpers and tag destructors.
See [SVO3.md](SVO3.md) for the exact per-module increment and behavioral details.
One new slot matches; 86 do not. Integration of nonmatching C++ is authorized;
exact matching and gameplay equivalence remain separate unfinished requirements.
New behavior tests were deferred per the user's decompilation-first preference.

Evidence: retail Ghidra program
`/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose`, split instructions,
`D:\PS2\ISOs\deadlocked-proto-decomp` and its dltypes.txt.
Use Ghidra first, then instructions to resolve misleading FID matches and ABI.
The prototype does not prove retail behavior. Preserve loop bounds, assertion
order, virtual calls, signed loads and independent integer/float argument banks.

Validation: make split finished before make -B -j8 elf; build PASS. Slot/public
address/compiled-origin/runtime-header/unchanged-byte audit PASS. Changed loaded
bytes: 37,366, all in registered C slots. Strict comparison NONMATCH (5,130
core.text, 32,236 net.text). All 40 new global labels PASS. Focused EE layout
probe PASS: 21 sizes + 223 offsets. Inventory: 159 types. No new behavior suite,
ISO packaging, gameplay, full-clean build or full regression was run.
Whole project: 630 compiled / 7,995 ASM; 155 matching, 475 nonmatching slots.

Original SHA-256:
`ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7`.
Rebuilt SHA-256:
`4d162c667219f7eaa6711acebea6cd877fba2f227524bb72bb5d8c918455bbcf`.
Artifact: src/games/dl/build/boot_elf.elf. Current reference is
src/games/assets/dl/boot.elf. Logs/probes: build/svo-library-work/svo75-* (ignored).

Next work: [SVO3_REMAINING.csv](SVO3_REMAINING.csv). Ten newly recovered oversized
candidates are saved in [SVO3_75_SLOT_BLOCKERS.md](SVO3_75_SLOT_BLOCKERS.md);
the earlier 16 are in [SVO3_SLOT_BLOCKERS.md](SVO3_SLOT_BLOCKERS.md). Do not retry
these without a new size approach. Never widen their retail slots. FormTag has
only its constructor and Submit left. The constructor was researched but not
implemented: action required (assert 0x63); encoding defaults to a 34-byte copy;
method recognizes POST/GET/LOGIN, missing method asserts 0x90, unknown 0x8A.
Submit still needs instruction-level recovery. Larger list/grid/page/HTTP logic
remains; constructor/destructor and callback signatures need careful checking.

Build migration: use the current projectryno image, ratchet-ps2-cli and boot.elf
reference, not the old Wrench container or boot_elf.elf reference filename.
`make iso` depends on elf and uses assets/dl/config.ini; packaging preserves
source ISO assets and replaces the boot executable only. CLI help was checked.
Read docs/build/RATCHET_PS2_CLI.md and the updated Makefile before packaging.
The projectryno-svo75 container belongs to this batch and is stopped after work;
it can be restarted. Other contributors' containers must be left alone.

Preserve other-agent uncommitted CLI/container/tool/docs changes. No commit or
push was made for this batch. The previous 50% batch is commit 96ee92d, already
pushed. Only PasswordInputTag.o was added to the existing size-flags list here.
No linker generator or build mechanism was replaced. ALLOW_NONMATCHING stays 0.

PageRequestListener preserves trailing net.text padding: GetLastContentType ends
at 0x01F0C844; the zero gap to 0x01F27658 and NOP extent through 0x01F31380 remain
original. Do not count that padding as compiled code or enlarge replacement slots.
