# Function progress

[FUNCTIONS.csv](FUNCTIONS.csv) inventories source INCLUDE_ASM entries and the
registered compiled replacements. [SUMMARY.json](SUMMARY.json) records counts,
time, and original/rebuilt ELF hashes for this snapshot. This is not the entire
Ghidra symbol table: retained remnant word arrays are not labeled completed C
functions, and source assembly entries may include padding/unknown routines.

Read the columns separately:

* `implementation`: assembly or compiled, inferred from source and manifest.
* `address`: a unique configured address, or a func_HEX address; blank when unresolved.
* `slot_match`: measured equality for a compiled function's entire allocation,
  including padding. Assembly entries say not_measured, not automatically matching.
* `compiled_size` and `slot_end`: measured linked size and configured bound.
* `test_scope`: names available suites, **not proof they passed in a new run**.
* `question`: default next investigation; `notes`: maintained research context.

The initial snapshot has 8,534 assembly entries and 62 compiled replacements;
6 compiled slots match and 56 do not. Regenerate for current results rather than
assuming those counts remain true. Equal slot bytes do not establish whole-ELF
matching or new in-game test coverage. File metadata hashes can differ even when
all loaded bytes match.

Keep manual notes in [FUNCTION_NOTES.json](FUNCTION_NOTES.json), keyed as
`code/path/file.cpp:function_name`. The generator preserves this input; it rewrites
only FUNCTIONS.csv and SUMMARY.json. Update notes with addresses/evidence and
specific unresolved questions rather than marking untested work complete.

Refresh the tracked snapshot inside `/ProjectRYNO/dl` after a verified rebuild:

```sh
python3 ../tools/function_progress.py dl --output DOCS/progress
```

The [verification command](../../../../../docs/build/VERIFICATION.md) also writes a
separate progress snapshot beside each verification report. Prefer that report
when deciding what a particular tested ELF contains. Commit tracked snapshot
updates only with the source/evidence they describe.


The 2026-10-07 iksemel batch adds six byte-matching C accessors: the refreshed
snapshot has 8,528 assembly entries, 68 compiled functions, 12 matching slots,
and 56 nonmatching slots. See [library notes](../libraries/IKSEMEL.md).

The subsequent SVO3 batch adds two byte-matching C functions: the refreshed
snapshot has 8,526 assembly entries, 70 compiled functions, 14 matching slots,
and 56 nonmatching slots. See [library notes](../libraries/SVO3.md).

The SVO3 follow-up adds 30 tested C/C++ replacements with nonmatching integration
explicitly authorized by the user. That snapshot had 8,496 assembly entries,
100 compiled functions, 18 matching slots and 82 nonmatching slots. Within SVO3,
32 functions are compiled and 903 remain assembly. The combined verifier passes;
the full ELF still differs from retail in 7,747 loaded bytes. See the SVO3 notes
for scope, remaining inventory and runtime-testing limits.

The decompilation-first SVO3 batch adds nine C replacements. The current snapshot
has 8,487 assembly entries, 109 compiled functions, 20 matching slots and 89
nonmatching slots. SVO3 has 41 compiled functions and 894 assembly entries. The
rebuild and ELF placement audit pass; 8,590 loaded bytes differ from retail, all
inside registered compiled slots. New behavior tests, full regressions and gameplay
testing were deferred for this batch at the user's request.

The next SVO3 batch adds 124 C/C++ functions across 28 files, bringing SVO3 to
165 compiled functions and 770 remaining assembly entries. 34 of its 97 source
files are free of INCLUDE_ASM. The corrected tracker includes dotted operator
symbols: project totals are 8,625 functions, 8,392 assembly and 233 compiled
(24 matching slots, 209 nonmatching). This adds 29 formerly omitted symbols to the
inventory rather than adding new game functions. The rebuilt ELF passes placement
checks but differs in 16,337 loaded bytes. Behavior/gameplay tests remain deferred
for this batch. See the SVO3 notes for three small wrappers still awaiting slot fit.


The HTTP/DNS continuation adds 15 C++ functions, removing INCLUDE_ASM entirely
from HttpUtils.cpp and DNSCache.cpp. SVO3 now has 180 compiled functions and 755
assembly entries; 36 of 97 files are free of INCLUDE_ASM. The current project
snapshot has 8,377 assembly functions, 248 compiled, 24 matching slots and 224
nonmatching slots. Compilation/placement and the focused type/global checks pass;
18,537 loaded bytes differ, all within compiled slots. Behavior and gameplay
checks remain deferred. See the HTTP/DNS section of the SVO3 library notes.


The cookie/module-manager continuation adds 13 compiled functions across CCookie,
SVTagModuleList and CPluginManager. CCookie is assembly-free; three newly recovered
wrappers remain assembly because their compiled bodies exceed the retail slots.
SVO3 now has 193 compiled functions and 742 assembly entries, with 37 of 97 files
free of INCLUDE_ASM. Project totals are 8,364 assembly and 261 compiled functions
(24 matching slots, 237 nonmatching). The ELF build/placement audit and focused
ABI/global checks pass; 19,762 loaded bytes differ inside compiled slots.
Behavior and gameplay checks remain deferred.


The URI continuation adds 29 C++ functions across SVURIStore, URISchemeMgr and
RedirectTagModule. The redirect factory file is assembly-free; three oversized
URI wrappers remain visible assembly. SVO3 has 222 compiled functions and 713
assembly entries, with 38/97 files free of INCLUDE_ASM. Project totals are 8,335
assembly and 290 compiled (27 matching slots, 263 nonmatching). Build/placement
and focused ABI/global checks pass; 21,689 loaded bytes differ only inside
compiled slots. Three new slots match exactly, but behavior/gameplay checks
remain deferred. See the URI section in the library notes.


The 2026-10-08 SVO3 checkpoint reaches 702/935 compiled functions (75.1%), with
233 assembly entries and 48/97 assembly-free files. Project totals: 770 compiled,
7,855 assembly, 156 matching slots and 614 nonmatching slots. Build, placement,
layout and global checks pass. Strict comparison reports 57,204 changed loaded
bytes inside compiled slots. MD5 compression passed 64 differential cases;
other new behavior and gameplay checks remain deferred. See the current
[SVO3 handoff](../libraries/SVO3_HANDOFF.md) for evidence and remaining work.


The next 2026-10-08 continuation reaches **741/935 SVO3 compiled (79.3%)**,
194 assembly entries and 53/97 assembly-free files. Whole project: 809 compiled,
7,816 assembly, 156 matching and 653 nonmatching slots. Build, placement, layout
and global checks pass. Strict comparison remains NONMATCH: 64,599 loaded bytes
differ inside compiled slots. MD5 passed 64 compression and 72 update cases;
other new behavior and gameplay checks remain deferred. See the current handoff
for saved oversized candidates and automatic-review-blocked work.


The networking/image continuation reaches **772/935 (82.6%) compiled, 163 INCLUDE_ASM**, with 54/97 assembly-free files. Build, layout, slot/address and globals checks pass. Strict comparison remains NONMATCH (70,499 loaded bytes inside compiled slots). New behavior/gameplay checks deferred. See the current SVO3 handoff.


Text input continuation: **776/935 (83.0%) compiled; 159 INCLUDE_ASM entries remain**. Build, layout, globals and slot audit pass; strict comparison remains NONMATCH. Gameplay remains untested.


HTTP continuation: **781/935 (83.5%) compiled; 154 INCLUDE_ASM entries remain**. Build, ABI, globals and slot audit pass. Strict matching remains NONMATCH; new behavior/gameplay tests deferred.


Text-area/select/image continuation: **797/935 (85.2%) compiled; 138 INCLUDE_ASM entries remain**. Full build, slot audit, layout and globals pass. Strict comparison remains NONMATCH; gameplay untested.
