# SVO3 continuation handoff, 2026-10-07

Task: remove all SVO3 INCLUDE_ASM functions using actual recovered C/C++, libraries
before game/. Still unfinished: 260 compiled functions and 675 assembly entries
across 97 source files. 40 files are entirely free of INCLUDE_ASM.

Latest batch: 38 replacements across SVTag, LogoutTag, BrowserInitTag, RedirectTag,
LineTag and RectangleTag. RedirectTag and RectangleTag are fully C++. Shared tag
selection, visibility, dimensions, navigation attributes, contexts and plugin
input handling are C++. Preserve all earlier uncommitted boot/sound/iksemel/SVO3
and tool work. See SVO3.md for behavior details and concrete placement blockers.

Evidence: explicit retail Ghidra program
/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose, split R5900 instructions,
prototype sources and dltypes. The 32 new globals name existing storage;
provenance is in ../symbols/SVO3_GLOBALS.csv. Type inventory: 125 declarations.
CPage and vtables remain prefixes, not allocation sizes. DrawLine and
DrawRectangle use independent GPR/FPR argument banks, confirmed in compiled
object disassembly. EE compile-time probe passes 12 sizes and 87 offsets.

Validation: serial make split, then make -B -j8 elf passed. Slot audit passes:
23,228 changed loaded bytes, all within registered C slots; every other loaded
byte and runtime header matches. Strict comparison reports NONMATCH: 5,130 core
text differences and 18,098 net text differences. 32 globals and all 43 function
entry addresses in this batch are correct; all 38 C bodies fit original bounds.
Project progress: 8,625 functions, 8,297 assembly and 328 compiled; 43 matching
compiled slots and 285 nonmatching slots. This batch adds 16 matching slots.
No new behavior suite, full regression, ISO or gameplay tests ran.
Reports/probes: build/svo-library-work/tags-* (ignored).
Original SHA-256: ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7.
Rebuilt SHA-256: 1165287afd5db93ccd2210f9e1add94999a285fd5a50dfd7d8b083a27f9931e3.

Next: use SVO3_REMAINING.csv. The SVTag XML constructor has Ghidra/instruction
research but remains unintegrated. Its allocator is still assembly. Three more
compact constructor blockers: LogoutTag/BrowserInitTag emit 0x38 for 0x34 slots;
LineTag emits 0x9C for 0x98. Recovered bodies are recorded in SVO3.md and ignored
constructor probes. Nine earlier compact-wrapper blockers remain documented in
PageHistory, SVChronograph, SVSock, SVTagModuleList, CPluginManager, SVURIStore and
URISchemeMgr. Do not widen slots or hide retained assembly as completed C.
PageIDTag's three functions were researched in retail Ghidra; split/prototype
verification and C integration are still needed. Other widget classes remain.

Keep ALLOW_NONMATCHING=0. Finish splitting before forced rebuilding after
manifest or symbol edits. HTTP retains its object-specific scheduling flag;
this batch only adds objects to the existing size flags. Keep byte matching,
placement and gameplay claims separate. game/ remains outside current scope.
The projectryno-iksemel container used here can be restarted; do not stop or reuse
another contributor's running container.
