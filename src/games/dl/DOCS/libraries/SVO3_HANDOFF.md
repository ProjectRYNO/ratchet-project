# SVO3 current handoff, 2026-10-14 (byte-matching push)

**934 functions: 853 byte-exact in the linked ELF, 81 compiled C functions that fit their slots
but are not exact. No SVO3 assembly remains.** Up from 603 exact at the start of this push.
Uncommitted. ALLOW_NONMATCHING=0, original slots unchanged.

## What is left ([SVO3_REMAINING.csv](SVO3_REMAINING.csv))

81 fit-not-exact functions, mostly register numbering, branch-likely/delay-slot choice and store
order. Notable blockers:

- CPage `Destroy{Pre,Post,In}TransitionArray` and the CPage constructor: retail keeps a dead
  clearing loop (`b` out of the loop at its head, body never executed) that 2.96 deletes in
  every source form tried, including inlined member functions.
- GridTag constructor: retail hoists ~25 field addresses into saved registers/stack before
  the first check; no C shape found.
- CPage `download` (one instruction): retail tests `preTransitionCount == 0` with a
  branch-likely; `> 0` gives the branch-likely but `blez`, every `== 0`/`!= 0` spelling tried gives
  a plain `beqz`. Its jump table already matches.
- UTF8 `CountCharacters`: `size` and `continuations` swap `$16`/`$17`; no declaration or loop
  shape tried changes it. Its jump table already matches.
- Navigation `autoNavigate`, RTCommSock `dnsLookupBlocking`/`WaitForConnect`, CHttp
  `parseHttpHeaderLine`, CPage `requestBinary`/`doRequest`: large register-allocation residue.

## Jump tables and padding (2026-10-14, DECISIONS.md D09/D10)

- Switch jump tables now link at their retail `.rodata` addresses. `tools/svo3_rodata_sections.py`
  (run by the SVO3 Makefile rule) moves each function's `.rdata` into `.svo_<Module>_<fn>.rodata`;
  `decompiled_functions.yaml` `rodata:` registers each slot (retail table extent, owning function);
  `split_dl.py` carves the retail data around the slots and asserts on overflow;
  `check_main_elf.py` allows changes only inside registered slots of compiled functions. A switch
  in a function without a registered slot fails the link (its section is discarded).
- Ten functions use it, all ten tables byte-identical to retail: CPage `setPageState`,
  `followLink`, `frameUpdate`, `download`; TextAreaTag `handleSpecialKeys`; TextInputTag
  `handleSpecialKeys___dupe2`; SVDownloadManager `download___dupe3`; CInputContextBase
  `HasActionOccurred`; UTF8 `GetNextCharIndexFromString`, `CountCharacters`. Eight of the ten
  functions are byte-exact.
- To add one: find the `jtbl_*` the retail asm loads, count its code-address words in
  `core.data/091E80.rodata.s`, add a `rodata:` slot, write the `switch` with case bodies in
  retail code order, then split and build.
- `func_01F27658` was a splat label inside 150,332 zero bytes after the last SVO3 function. The
  whole range 0x01F0C844..0x01F31380 is now `junk/net.text/4c0844_4e5380`; the fake function and
  its slot were removed (loaded bytes unchanged).
- `svoTextAreaNewline = 0x0019D408` names the retail `"
"` literal that TextAreaTag
  `handleSpecialKeys` copies (same convention as the other SVO3 string externs).

## Toolchain change in this push

`SVO3_AS_FLAGS` now includes `-g` (Sony `as`). With `-g` the assembler does not move
instructions into branch/jal delay slots, which retail clearly did not do; it gained exactness
with no regressions. It only changes the `.mdebug` section, which the linker script discards
(`/DISCARD/ : { *(*) }`); loaded bytes and audits are unaffected.

## 2.96 source-shape patterns established (in addition to the earlier list)

- **Real C++ constructors** for constructor-named functions, with raw storage when the state type
  can't be a member: `struct XCtor { char data[sizeof(XState)]; XCtor(args) __asm__("X"); };`
  (SVChronograph, RTCommSock). Not universal: CMemoryContextBase got worse (tail call).
- **Inline helper constructors for value structs:** `SVPathCtor(scheme, server, &port, path, 257)`
  (SVPath holds a C++ reference) reproduces retail's store-through-`this` sequence (CPage
  `doRequest`, `requestBinary`).
- **Late address computation:** `DLBuffer *second; if (!first->x && !(second = &m->m_buffers[1])->x)`
  (two SVDownloadManager functions). Splitting one reused variable into two changes allocation
  priority (SelectTag `changeCurOptionToNextLetterInAlphabet`).
- **Wider locals:** retail sometimes used a wider local type (RTCommSock `Connect`: `RTLinkAddress`
  local instead of `unsigned long` gives retail's frame layout).
- **Copy from a retail data symbol:** `extern L obj __asm__("svoHttpSchemes"); L copy = obj;`
  (CHttp/HttpSecure DoRegistrations).
- **Success-path-first nesting** (`if (!a) { if (!b) {...} return 1; } return 0;`) controls where the
  shared `return 0` block lands (RTCommSock `Send`, TagUtils `getIntAttrib`).
- **Indexed loops** `for (i...) { T *p = &arr[i]; ... }` give retail's counted `bgez` loops (CPage
  `scanObject`); `tags[i]` indexing instead of walking pointers (CPage `GenerateLagListInfo`).
- **Not the cause:** `-fno-strict-aliasing` (global test: 862 -> 806 exact), and none of
  `-fno-cse-follow-jumps`, `-fno-gcse`, `-fno-rerun-loop-opt`, `-fno-cse-skip-blocks`.
- **Rejected:** empty `__asm__ __volatile__("" : : "r"(x))` to force a dead load (CHttp
  `downloadBody`); it emits no bytes but is not real source.
- **Unsolved residual classes:** branch-likely choice (`beql`/`beqz`, e.g. CPage `download`,
  `callGenericDownloadCallback`, `LeaveCurrentPage`), scheduler order of independent argument
  moves (`SVMLparseCB`, `GetPageName`, `decodeEntityChar`), and loop-carried reuse of a reloaded
  pointer (CPage `FreeBack/FrontDisplayBuffer`; a `volatile` read gets within 2 lines but is not
  the original).

- **Store order:** 2.96 emits the LAST of a group of independent stores FIRST, then the rest in
  source order. To get retail order X1..Xn, write X2..Xn, X1.
- **Index-based loops** `for (i = 0; i < N && a[i]; i++) { T *t = a[i]; ... }` reproduce retail's
  "test a[0] in one register, walk a copied pointer" shape; pointer-walking source does not.
  Indexed `for (i = 0; i < 64; i++)` gives GCC loop reversal (count-down `bgez`).
- **Unrotated loops** (test at the top, several backward branches) come from `goto` loops or
  `for` loops whose body uses `continue`.
- **Counters initialised far before their loop** need an explicit pre-check
  (`if (i < n) { do { ... i++; } while (i < n); }`) — FormTag `Submit`.
- **Guard-first returns** (`if (!x) return 1; return f(x);`); single-exit `int result = 0; if (...)
  { ...; result = ...; } return result;`; `return obj->field = 1;`.
- **Separate local per vtable call** (`SVTag *a = f(); a->vt->X(a); SVTag *b = f(); ...`) fixes
  vtable-load ordering; **duplicated full calls per branch** let 2.96 cross-jump the common
  tail exactly like retail.
- **Real C++ constructors** (`Struct(args) __asm__("Name")`) fix epilogue `ld` order and
  branch-likely loop exits (PopupTag, PasswordInputTag, RectangleTag).
- **g++ 2.x DownloadBinary model:** `DownloadBinaryObj` (CPage.cpp) has the vptr after the data
  and a declared ctor bound to `DownloadBinary`; its implicit `operator=` saves/restores the vptr
  around a block copy. `InTransitArray`/`PostTransitArray` model the StaticArray objects, with
  `static inline` Pop/Push helpers that inline away (no extra symbols are emitted; checked).
- **g++ array-constructor loops** (counter n-1 down to -1) come from member arrays of a class
  with a declared constructor (CPage constructor `CPageShell`).
- Retail `lb` means signed `char` (CPage `*TransitionUsed` arrays changed to `char`, layout
  unchanged); `switch` case-body order follows source order; `(unsigned int)` switch values
  and extra case labels change the compare tree.

- **Switch shapes:** case bodies are emitted in source order, so order cases by retail code
  address (read the table). Retail often calls inside each case (`case 1: sprintf(buf, X); break;`)
  rather than selecting a value. `(unsigned int)` switch values or sparse cases give a compare tree
  instead of a second table. Identical case bodies differing only in a symbol are invisible to
  `sbs.py`/`byte-compare.py` (relocated words compare opcode bits only): check the linked table.
- **`do { switch ... } while (0);`** stops 2.96 turning `setPageState(...); break;` at the end of a
  `void` function into tail calls (CPage `frameUpdate`).
- **Inline member accessors** (`InTransitArray::GetCount()`) keep retail's separate
  `addiu base; lw off(base)` instead of a folded offset: g++ 2.x copies `this` per inlined call.
- **`goto` to a later label** places a block after the fall-through code (CInputContextBase
  `HasActionOccurred`: analog call and clamp before the button test).
- **Retail clearing loops** with three `nop`s are plain C byte loops (`for (i = 0; i < 257; i++)
  path[i] = 0;`); the EE assembler pads short loops.

## Behaviour corrections made while matching (review)

- SVBrowser `rt_comm_linkaddress_tostr` declaration: the earlier long→int conversion had made
  the 8-byte `RTLinkAddress` argument 32-bit (only half the address was passed). It now takes
  `RTLinkAddress` by value, as retail does; `RTCommInit` uses the prototype's 16-byte buffer.
- CPage `shutdown` is `void` (retail calls `SSL_Cleanup()` without using a result; callers
  ignore the return value).
- From agent 2: CHttp `States___dupe2` now hits the default assert for state 14 (retail compares
  against 0x7FFFFFFF); SVDownloadManager `doRequest___dupe4` copies `path+1` at position 0 as
  retail does; `init___dupe2`, the CInputContextBase constructor and PageRequestListener
  `OnURIRequestChunkReceived___dupe2` fall off the end of a non-void function to keep retail's
  `v0` (compiler warning, identical bytes).

## Validation (2026-10-14, final)

The working tree's `code/sdk/i18n.c`/`i18n.h` had in-progress edits from outside this session
that move later objects ("rt_memory moved from its original address"). They were not touched;
validation ran in an isolated container copy (`/tmp/ckroot`) with the committed `i18n.c` and a
`DnsCache.h` -> `DNSCache.h` link (the include's case only resolves on the Windows bind mount).

- Sequential `make split`, then `make -B -j8 elf`: PASS.
- `check_main_elf.py`: PASS, 19,602 changed loaded bytes (was 23,368), all inside registered
  function and jump-table slots.
- `check_global_map.py`: PASS (806). `check_type_layouts.py`: PASS (1,905 across 211 types).
- `compare_elf.py`: NONMATCH (expected while 81 functions are not exact).
- Linked-ELF slot compare: compiled exact 853, compiled differs 81, rodata slots exact 10/10.
- Progress: project 1,005 compiled / 7,619 assembly; 868 matching, 137 nonmatching slots.
- NOT RUN: behaviour suites, regressions, ISO packing, emulator/gameplay (deferred).

Rebuilt SHA-256 (isolated copy): `3f62a90b866922b645b52be5a0ecb0722f26199318c3a3b2913a5758ed7135bb`.

## Tools (build/svo-library-work/)

`perm.py` (test a replacement body; `--perm A B` permutes lines), `multi.py` (variants separated
by `----`, `--install`), `climb.py` (statement-order hill climber scored by diff lines plus
store-offset LCS), `install.py`, `family.py`, `cmpvar.sh` (per-function before/after for a
module), `hdrtest.sh` (effect of a header edit across modules), `try.sh`, `sbs.py`,
`byte-compare.py`, `ck4.sh` (full checkpoint). Note: `sbs.py` prints EE `cvt.w.s` as `.word`
on the retail side and objdump prints the same encoding as `trunc.w.s`, so those lines show as
`!!` although the bytes are equal; `byte-compare.py` is authoritative. Agent scratch files use
`h2_`/`h3_` prefixes.

---

# Earlier handoff, 2026-10-13 (toolchain switch)

**934/935 slots compiled from C/C++; 603 byte-exact, 331 fit their original slots.**
The one remaining `INCLUDE_ASM` is `PageRequestListener func_01F27658`. It is a 4-byte
label at the start of a NOP padding run, not a function; how to classify it is an open
user decision. Uncommitted; based on the user's checkpoint a1b6ccd. Keep ALLOW_NONMATCHING=0.

## Toolchain: SCE ee-gcc 2.96 for SVO3 (user decision, DECISIONS.md K07)

- `src/games/dl/Makefile`: the `ee-gcc296` target downloads `2.96-ee-001003-1` from the
  decompme/compilers release into `/opt/ee-gcc2.96` and builds the stat shim;
  `rom` depends on it. SVO3 objects: `ee-g++ -S`, then Sony `as -EL -G0`.
- Flags: `-G0 -Os -fno-exceptions -mno-split-addresses -falign-functions=4
  -falign-loops=1 -falign-jumps=1 -falign-labels=1`, plus newlib and the 3.2.3 builtin headers.
- `src/games/Dockerfile`: i386 multiarch, `gcc-multilib libc6:i386 xz-utils`.
- `src/games/tools/ee296_statshim.c`: LD_PRELOAD `__xstat`/`__lxstat`/`__fxstat` via the
  stat64 calls. Without it the 32-bit binaries fail with EOVERFLOW on Docker bind mounts.
- `long` is 64-bit under this ABI. 32-bit values were converted to `int`; genuine 64-bit
  members were kept: md5 state, RTCommSock addresses, soft-float double patterns and
  `Send`'s `unsigned long *sent`.
- Headers are not Makefile dependencies: `rm build/code/svo3/*.o` after header edits.

## 2.96 source-shape findings

- A `void` function ending in a call gets no sibling call unless it has an explicit `return;`.
- In if/else only the first branch is tail-called. Retail usually avoids this, so use two
  separate `if`s or put code after the call. C++ constructors inside branches do not
  tail-call; asm-labelled constructors (`Name(...) __asm__("Name")`) do.
- These shapes match retail: guard clauses `{ assert; return 0; }`, direct field reads
  instead of cached locals, locals declared in prototype order (stack layout), signed
  `for` counters in parsers, field-wise struct copies, and real `double` arithmetic
  (soft-float libcalls).
- `return tag->field = 1;` lets the stored constant double as the return value
  (GridTag `FindAndSetSelectedCell`, exact). A `do { } while (++i < 128)` loop with an
  unsigned counter reproduces retail's unrotated loop (CQueryParams `toString`, exact).
- Extra case labels (0x100, 0x200) reproduce retail switch compare-tree pivots.

## This session's final batch

- SVDownloadManager `draw___dupe2` (fits, 0x67C/0x684); 10 string globals mapped.
- FormTag `Submit` (fits, 0x574/0x59C). Slot 0x50 of the text-entry vtables is reached
  through a local `FormValueVtable` view. `DataCanBeEncryped` is called with the tag
  argument retail passes, through the `DataCanBeEncrypedTag` asm alias.
- GridTag `Draw___dupe23` (fits, 0xA28/0xA34). `CDrawContextVtablePrefix` 0x30..0x40 were
  recovered from the retail call ABI and synced to RECOVERED_TYPES.json: `DrawGridBorder`,
  `DrawGridHeader`, `DrawGridRow`, `DrawGridCell`, `DrawGridScrollbars`. `svoGridEmptyCellText`
  (0x19DE68, `" "`) is mapped. Retail passes `columns[c].colAlign` (the visible index) to
  DrawGridCell, while every other column access uses `columnIndexes[c]`. This is preserved.
- GridTag `FindAndSetSelectedCell` and CQueryParams `toString`: byte-exact.
- Earlier in the session: Navigation `getDistanceAutoNav`/`autoNavigate`, `lt_double` and
  `getFloatAttrib`. `pow` is now declared `extern "C"`, because 2.96 had mangled it to `pow__Fdd`.

### Jump-table functions (nonmatching, user decision pending)

Retail CPage `setPageState` and TextAreaTag `handleSpecialKeys` dispatch through
`.rodata` jump tables (`jtbl_0019B7F0`, `jtbl_0019D410`). A compiled switch places its
table at the end of the object's `.net_text`, outside the slot, and the retail table
cannot be reused. Both functions are therefore written as if-chains with no rodata and
are **not** byte-matching:

- `setPageState` (0x334/0x354): each chain selects the state name, then a single `sprintf`
  follows. Unknown states skip it, as in retail.
- `handleSpecialKeys` (0x1D0/0x1D4): cases 0x85/0x86 share their `UpdateCursorPosition`
  tail, and cases 0x87/0x88/0x89 share their `UpdateAfterTextEntry` tail, via `goto`.

Exact matches need splitter/linker support for per-function rodata slots.

## Validation (ck4, 2026-10-13)

- Sequential `make split`, then `make -B -j8 elf`: PASS.
- `check_main_elf.py`: PASS, 59,652 changed loaded bytes, all inside registered slots.
- `check_global_map.py`: PASS (806 names). `check_type_layouts.py`: PASS, 1,905
  sizes/offsets across 211 types and 101 headers.
- `compare_elf.py`: NONMATCH (expected).
- Object byte compare (`byte-compare.py`): C exact 603, C fits 331, assembly 1.
- Progress: project 1,002 compiled / 7,623 assembly; 615 matching, 387 nonmatching slots.
- NOT RUN: behavior suites, regressions, ISO packing, emulator/gameplay (deferred).

Original SHA-256: `ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7`.
Rebuilt SHA-256: `ec7561aa6e9dd2b746feb9b6f5e5587e890a79496b7d0f475ef6e6d6b864c8fd`.
Logs are `build/svo-library-work/ck4-*`. The helper scripts `try.sh`, `cand.py`,
`accept.sh`, `sbs.py` and `byte-compare.py` are in the same folder. Build container:
projectryno-svo75.

## Next work

1. User decisions: rodata/jump-table slots, and the classification of the `func_01F27658` padding.
2. Tighten the 331 fitting functions toward byte-exact. The usual residue is register
   allocation, delay-slot fills and store order; `sbs.py Module fn obj` shows the diff.

---

# Earlier handoff, 2026-10-12 (historical)

**861/935 (92.1%) compiled; 74 INCLUDE_ASM entries remain.** 60/97 files are
assembly-free. This batch is uncommitted, based on the user's checkpoint a1b6ccd.
Keep game/ last and use the native ratchet-ps2-cli workflow.

## Download/page/text/grid continuation (2026-10-12)

Completes the batch begun after a1b6ccd (`build/svo-library-work/hundred-*`), which
had replaced 27 INCLUDE_ASM entries in source without registering them or building.
19 C/C++ replacements fit their slots and are now registered:

- SVDownloadManager: `_SVDownloadManager`, `SVDownloadManager`, `doRequest___dupe4`,
  `formatDownloadStatusText`, `UpdateFileDownload`, `OnURIRequestIsOkContinueDownload`
- SVFileDownloadQueue `find___dupe2`; CPage `requestBinary`; SVBrowser `Initialize___dupe4`
- Attribute parsers: DataTag `getDataTypeAttrib`, ImageTag `getImageTypeAttrib`,
  TagUtils `getLinkOptionAttrib`, TickerTag `getTickerTypeAttrib`
- TextTag constructor, `Draw___dupe8`, `IsSelectable___dupe6`; TextAreaTag constructor;
  TextInputTag `InitialiseFromXml`; GridTag constructor

The other 8 bodies overrun their slots and were restored to INCLUDE_ASM. Their source
is preserved in [SVO3_TAIL_CALL_BLOCKERS.md](SVO3_TAIL_CALL_BLOCKERS.md).

Evidence: retail Ghidra disassembly/decompilation for the parsers (entry counts 3/4/9/2;
`strcasecmp` only in the ticker), the TextTag functions (offsets, assertion lines,
argument registers, the `this == -0xC4` check) and the header claims below.
The earlier batch also reviewed the HTTP/page/browser bodies (`hundred-http-results.json`).

Header changes, all instruction-confirmed:

- `SVPersistentData.homeURI[256]` at 0x280 (dltypes line 31287; retail Initialize passes
  persistent+0x280 to sprintf). Size 0x1B9C unchanged.
- `DownloadSystemVtable` prefix 0x38, `OkToFreeFileDownloadBuffer` at 0x34 (retail
  UpdateFileDownload `jalr` at 0x01F095A8 and 0x01F09654).
- `TextInputTagVtablePrefix` `defaultInit` at 0x74 and `registerWithForm` at 0x78
  (retail InitialiseFromXml `jalr` sites).

97 globals (attribute strings, assertion filenames, formats, download-manager vtable)
were added to `symbols_core.text.txt` and `DOCS/symbols/SVO3_GLOBALS.csv`. Every
address begins a retail string whose text matches its name; sampled Ghidra xrefs
land in the functions that use them.

## Validation

- Sequential `make split`, then `make -B -j8 elf`: PASS.
- `check_main_elf.py`: PASS, 101,803 changed loaded bytes, all inside registered slots.
- `check_global_map.py`: PASS (806 names). Batch globals: PASS, 97 at retail addresses.
- `check_type_layouts.py`: PASS, 1,895 sizes/offsets across 211 types.
- `compare_elf.py`: NONMATCH (expected; strict matching remains unfinished).
- Progress: project 929 compiled / 7,696 assembly; 160 matching, 769 nonmatching slots.
- NOT RUN: new behavior suites, full regressions, ISO packing, emulator/gameplay
  (deferred per the user's decompilation-first priority).

Original SHA-256: `ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7`.
Rebuilt SHA-256: `2af553272015a09f2fcabba11c70bd7ae399e02a4d909f8e9ec74b32377abb6d`.
Logs: `build/svo-library-work/finish-*`. Build container: projectryno-svo75.

## Reaching 100%: compiler blocker

ps2dev ee-gcc 3.2.3 cannot emit MIPS tail calls. 29 of the 74 remaining functions end
in a retail tail jump and cannot fit their slots with this compiler. Most of the other
small overruns come from the same compiler-generation gap. Evidence and the list of
affected functions: [SVO3_TAIL_CALL_BLOCKERS.md](SVO3_TAIL_CALL_BLOCKERS.md).
The UYA project's toolchain study points to SN Systems ProDG EE GCC 2.95.x as the
retail compiler; testing it is a toolchain decision for the user.

Functions without a recorded attempt and without tail jumps: Navigation
`autoNavigate`/`getDistanceAutoNav`, FormTag `Submit`, GridTag `Draw___dupe23`,
SVDownloadManager `draw___dupe2`/`okToNavigate___dupe4`/`shutdown___dupe3`,
QuickLinkTag `HandleInput___dupe39`, TickerTag `Draw___dupe27`, SVBrowser `DrawPages`,
DataTagModule `ScanTags___dupe5`, SVTagModule `ScanTags___dupe2`.
`PageRequestListener func_01F27658` is 4 bytes of padding, not compiled code.

Retail Ghidra: `/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose`, R5900 LE32.
Prototype: `D:/PS2/ISOs/deadlocked-proto-decomp`, including dltypes.txt.
Keep ALLOW_NONMATCHING=0 and the original slots. No commit/push performed.
