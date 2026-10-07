# SVO3 continuation handoff, 2026-10-07

The requested 50% function-count milestone is reached: **475/935 (50.8%)**
compiled, with **460 INCLUDE_ASM entries** across 97 files. 47 files are fully
C++; 50 still contain assembly. Full SVO3 decompilation remains unfinished.

Latest batch: 215 replacements in 42 original translation units. DownloadBinary,
the four XML adapter files, PageIDTag and PopupTag are newly free of INCLUDE_ASM.
Browser helpers, page request handling, file download queue, tag attributes,
HTTP callbacks, socket settings and widget/module helpers are partly recovered.
See [SVO3.md](SVO3.md) for the per-file counts and retail behavior details.
Preserve all earlier uncommitted boot/sound/iksemel/SVO3/tool work.

Evidence: explicit retail Ghidra program
/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose, split R5900 instructions,
prototype sources and dltypes. 55 new globals name existing storage; provenance
is in ../symbols/SVO3_GLOBALS.csv. Type inventory: 149 declarations. The focused
EE probe verifies 28 sizes and 158 offsets. CPage, HTTP, socket and several tag
views remain prefixes, not allocation sizes. SVBrowser's layout is 0x3140 with
unrecovered embedded text-field storage still opaque. Use owning headers for
SVButtonMap and SVChronographState; anonymous typedefs cannot be forward-declared
as named structs.

Validation: make split completed before make -B -j8 elf. Forced build passes.
All compiled entry/slot checks and loaded-header/unchanged-byte checks pass:
29,445 differing bytes, all in compiled slots. Strict comparison is NONMATCH:
5,130 core.text and 24,315 net.text differences. All 55 new global addresses pass.
The batch has 111 exact compiled slots and 104 nonmatching slots; project total
is 543 compiled / 8,082 assembly (8,625 total), with 154 matching and 389
nonmatching compiled slots. Behavior suites, gameplay, ISO packing and full
regressions were deliberately deferred per the user's decompilation priority.

Original SHA-256: ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7.
Rebuilt SHA-256: d5cc828e730617b7cb94246e259bf12987a7425c76f06ebd7ecc2e0815b31287.
Artifact: build/boot_elf.elf. Logs/probes: build/svo-library-work/half-* (ignored).

Next: use [SVO3_REMAINING.csv](SVO3_REMAINING.csv). Sixteen recovered candidates
remain assembly because their C bodies exceed retail slots; their complete trial
bodies and size measurements are preserved in
[SVO3_SLOT_BLOCKERS.md](SVO3_SLOT_BLOCKERS.md). Do not repeat them without a new
size/matching approach. Earlier blockers in PageHistory, SVChronograph, SVSock,
SVTagModuleList, CPluginManager, SVURIStore, URISchemeMgr, LogoutTag,
BrowserInitTag and LineTag remain documented in SVO3.md. The base SVTag XML
constructor and larger widget/browser/HTTP functions remain useful next targets.

The PageRequestListener object covers the original trailing net.text padding:
GetLastContentType ends at 0x01F0C844; preserve the zero gap to 0x01F27658 and
the retained NOP extent through 0x01F31380. Do not count that padding as C or
widen replacement slots. The unchanged-byte audit checks it.

Keep ALLOW_NONMATCHING=0. Finish splitting before forced rebuilding after
manifest/symbol edits. Only the existing object-specific size flag list changed;
no linker/build mechanism was replaced. Matching, compilation, layout and
in-game behavior remain separate claims. Keep game/ last.
The projectryno-iksemel container can be restarted for the next task; leave
other contributors' containers alone.
