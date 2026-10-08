# SVO3 continuation handoff, 2026-10-08

Current verified checkpoint: **702/935 (75.1%) compiled, 233 INCLUDE_ASM**.
The requested 75% milestone is reached. 48/97 files are assembly-free; 49 are mixed.
This commit includes the preceding 23-function batch and the latest 117 functions.
Keep game/ last. Matching and gameplay equivalence remain unfinished requirements.

Evidence: retail Ghidra program
`/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose`, split instructions,
`D:\PS2\ISOs\deadlocked-proto-decomp` and its dltypes.txt.
Use Ghidra first, then instructions to resolve misleading FID matches and ABI.
Preserve retail loop bounds, assertion order, virtual calls, signed loads and
independent integer/float argument banks. Prototype behavior is not retail proof.

Validation: make split followed by make -B -j8 elf PASS. Slot/public-address,
compiled-origin/runtime-header/unchanged-byte audit PASS: 57,204 changed loaded
bytes, all in compiled slots. Strict comparison NONMATCH (5,130 core.text,
52,074 net.text). All 806 existing mapped globals and 107 batch aliases PASS.
Full layout verification PASS: 1,698 size/offset checks, 184 types, 100 headers,
independent header inclusion and ten boot packing vectors. MD5 compression PASS
for 64 original-versus-compiled cases, checking all 64 state bits. MD5 finish/hex
and other new behavior tests are deferred. No ISO, gameplay or full-clean check.
Whole project: 770 compiled / 7,855 ASM; 156 matching / 614 nonmatching slots.

Original SHA-256:
`ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7`.
Rebuilt SHA-256:
`2ccc670b1ef404fd48896a678d5ba069b379780f775850f7069da46a33317923`.
Artifact: src/games/dl/build/boot_elf.elf. Reference:
src/games/assets/dl/boot.elf. Logs: build/svo-library-work/svo-target-* (ignored).

Next work: [SVO3_REMAINING.csv](SVO3_REMAINING.csv). Forty-seven oversized bodies
are saved in [SVO3_TARGET_SLOT_BLOCKERS.md](SVO3_TARGET_SLOT_BLOCKERS.md), six in
[SVO3_NEXT_SLOT_BLOCKERS.md](SVO3_NEXT_SLOT_BLOCKERS.md), plus earlier blockers in
SVO3_75_SLOT_BLOCKERS.md and SVO3_SLOT_BLOCKERS.md. Read measured sizes before
retrying; never widen retail slots. See SVO3.md for module counts and limitations.

Use the current projectryno image, native ratchet-ps2-cli and boot.elf reference,
not Wrench/Wine. Read docs/build/RATCHET_PS2_CLI.md and the Makefile before packing.
GridTag/md5 use the existing per-object size flags. No linker changes.
ALLOW_NONMATCHING remains 0. Leave other contributors' containers/work untouched.

PageRequestListener preserves trailing net.text padding: GetLastContentType ends
at 0x01F0C844; the zero gap to 0x01F27658 and NOP extent through 0x01F31380 remain
original. Do not count that padding as compiled code or enlarge replacement slots.
