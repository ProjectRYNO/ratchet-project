# SVO3 library

## Current scope (2026-10-07)

SVO3 is **not fully decompiled**. The corrected source inventory has 935 functions
across 97 files: **260 compiled C/C++ functions and 675 INCLUDE_ASM entries**.
40 translation units are entirely free of INCLUDE_ASM; 57 still contain assembly.
This inventory includes dotted operator symbols previously missed by the tracker.
The table below describes earlier batches; subsequent batches are recorded below.

| Source file | Compiled functions | Coverage |
| --- | ---: | --- |
| SVOString.cpp | 9 | Copy/substring/format helpers and ASCII classifiers |
| CError.cpp | 2 | First-error latch and system callback dispatch |
| CSystemContextBase.cpp | 4 | Base callbacks, assertion paths, elapsed-time fallback |
| CAudioContextBase.cpp | 1 | Retail vtable initialization and return register |
| CInputContextBase.cpp | 6 | Audio destructor, input initialization, maps, action dispatch |
| CMemoryContextBase.cpp | 8 | Allocation/free bookkeeping and memory-chunk initialization |
| CConfig.cpp | 2 | Initialization and file/XML configuration loading |
| CQueryParams.cpp | 8 | Query storage, serialization, copying and freeing; behavior tests deferred |
| CPluginBase.cpp | 1 | Message queue reset; behavior tests deferred |

The user explicitly authorized behavior-tested nonmatching C/C++ replacements
on 2026-10-07. Such functions remain unfinished **matching** work. The progress
tracker reports measured slot matching separately from compiled status. No
replacement uses original machine-word arrays or fallback function symbols.

## Evidence and placement

Reviewed the retail Ghidra program
`/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose`
(`DL_Retail_BootELF_974.65.elf`, r5900 little-endian), its split instructions, and
matching files under the local prototype `svo3/` tree. `dltypes.txt` corroborates
context/chunk/button-map layouts; retail field accesses, constructor loops,
callback dispatches and allocation strides determine the implemented ABI.

Functions retain their original translation units, public labels and allocation
bounds in `config/decompiled_functions.yaml`. Source section attributes place
each compiled function independently. Object-specific size/alignment/scheduling
flags keep the code in those bounds; global compiler flags and linker generators
are unchanged. In particular, the audio destructor remains in CInputContextBase.cpp,
where the original split groups it.

Existing data is named in `symbols_core.text.txt`, using ordinary externs:
error state at 0x0021D9B0, context vtables, assertion filenames, memory-chunk ID
counter, and configuration prefix/keys. No duplicate globals or strings are
allocated. Vtable headers explicitly describe only the recovered prefixes.
Unrecovered context bytes remain marked, rather than assigned guessed types.

## Behavior that must be preserved

* svstrlen includes the terminating NUL; the classifiers are ASCII-only and use
  unsigned range arithmetic for arbitrary int inputs.
* svstrncpy asserts on truncation; svsubstrncpy truncates without that assertion.
  Retail zero-capacity handling can write before the destination; no new recovery
  policy was substituted. Null-pointer assertion tests stop at the handler.
* my_strcspn searches for a substring, not a character set. Empty input returns -1,
  including when the substring is empty.
* svsnprintf calls vsprintf and checks its result afterward; it is not a bounded
  formatting replacement. Variadic integer/64-bit register and stack forwarding
  is tested; real formatting and floating-point rendering are not exercised.
* SetErrorCode latches the first nonzero error before the browser/context lookup
  and callback. Later errors and zero are ignored.
* HasActionOccurred narrows digital button masks to unsigned 16 bits. Directional
  digital results are +/-127; analog results are filtered by direction. Ordinary
  actions return a boolean. Constructor fields not initialized by retail stay intact.
* svAllocSafe adds twice max(align,4), preserves the allocator alignment argument,
  and increments the counter after every attempt, even NULL. Free counters also
  update after their callback; unsigned bookkeeping preserves retail wraparound.
* Chunk Init unconditionally starts 30 bytes before the filename end, even for short
  strings. Tests include surrounding bytes, freed/not-set sentinels, ID wraparound,
  and preservation of untouched alignment fields and backup chunks.
* Configuration loading ignores sceRead and parser return codes, repeats its length
  assertion, checks only the first port character before atoi, and sets the loaded
  flag after deleting parser/node. The unusual destination-address assertion is
  preserved. These are retail behaviors, not recommended new API designs.

## Verification

Build sequence: `make split` completes before `make -B -j8 elf`. For the first 32 replacements, the shared
verifier runs these suites automatically:

* check_svo_string.py: 4,112 classifier cases, 15 strlen cases, and 171 copy/search/
  format cases; compiled-symbol/slot checks; keeps svstrlen and svisdigit byte-exact.
* check_svo_core.py: 80 error-state scenarios, base callbacks, and audio constructor.
* check_svo_input.py: 1,686 input/map cases plus constructors, no-op and destructor
  flags; checks callback arguments, side effects and callee-saved registers.
* check_svo_memory.py: 178 allocation/free/chunk cases plus destructor/cleanup;
  executes full 640-chunk initialization against both images.
* check_svo_config.py: constructor and 31 file/XML success/error cases, including
  dependency failure results, cleanup order and assertion paths.

These execute original/rebuilt EE instructions with explicit dependency mocks.
The small interpreter now implements SWC1 stores for variadic register saves;
unsupported instructions still fail. Layout checks include new context, vtable
prefix, button-map, chunk and config types. ISO packing, emulator boot and gameplay
are separate checks and have not been run for this batch.

Generated evidence lives in `build/svo-core-work/`: baseline.elf, serial split/build
logs, and verification reports. See the tracked function progress for the measured
matching results; diagnostic validation does not imply whole-ELF matching.

The final forced build and combined verifier passed all diagnostic suites. Strict
retail comparison reports 7,747 differing loaded bytes (nonmatching); runtime headers
match. Relative to the pre-change build, the first load segment is unchanged and
2,617 bytes differ in the network-code segment, inside the registered replacement
slots. The new build contains 100 compiled functions project-wide: 18 matching
slots and 82 nonmatching slots. SVO3 has six matching compiled slots and 26
nonmatching slots. Nine verifier orchestration unit tests also passed.

## Remaining work

[SVO3_REMAINING.csv](SVO3_REMAINING.csv) records all 770 remaining entries with
retail addresses and sizes. It is a snapshot, not a second source of build truth;
refresh it with the function tracker as replacements land. Keep working within
SVO3 before moving to another library, and leave game/ until the libraries are done.

CQueryParams.cpp and CPluginBase.cpp are now integrated. The next untouched
modules remain enumerated in the inventory; do not treat prior Ghidra review as
compiled or behavior-tested work.

## Decompilation-first follow-up

The user requested less testing and more source recovery. This follow-up replaces
all eight CQueryParams routines (0x01EF21FC..0x01EF262C) and
CPluginBase.emptyMessageQueue (0x01F04BF0..0x01F04C2C). Validation is limited to
compilation, an EE layout compile check, ELF placement auditing and measured
matching status. No new behavior suites, full regressions or gameplay tests were
run for these nine replacements.

The query list is 128 key/value pairs plus its index at 0x400. Set reloads the
index after allocator callbacks; FreeAll frees key before value and clears the
key again after the value callback. toString scans until a missing pair, escapes
both strings, preserves retail's strictly-greater-than capacity check, and consumes
the list only on success. The destructor does not implicitly free strings. The
constructor combines zero-initialization into one memset of the 0x404-byte state
to fit its original 0x20-byte slot; this is not instruction-matching.

The plugin reset clears 32 event/sender pairs and resets the indices/current
message. Its header explicitly exposes a verified 0x590-byte prefix, not the full
prototype 0x638-byte class. No unverified trailing fields are used.

Reports for this pass are under `build/svo-query-work/`; the earlier full-suite
results above apply to the preceding build only. The tracked function inventory
marks these new functions as compile/placement checked with behavior tests deferred.

The rebuilt ELF passes placement auditing: all 8,590 changed loaded bytes are
inside registered compiled-function slots; all other loaded bytes and runtime
headers match retail. Project-wide progress is 109 compiled functions (20 matching
slots, 89 nonmatching) and 8,487 assembly entries. That earlier SVO3 build had 41 compiled
functions across nine complete translation units and 894 remaining assembly entries.
Byte matching and behavior validation remain separate unfinished work.

## Library and tag-module follow-up (2026-10-07)

This batch adds **124 compiled functions across 28 source files**:

* UTF8_Util.cpp: all nine byte classification, navigation, editing and counting routines.
* PageHistory.cpp: six routines; its constructor remains in assembly pending a slot-fit solution.
* SVChronograph.cpp: eleven routines, including the custom delete; custom new remains assembly.
* SVSock.cpp: constructor and custom delete; custom new remains assembly.
* 24 tag-module files: four routines each (tag recognition, construction, singleton
  access, resource cleanup). These are Button, Line, Rectangle, HiddenInput,
  PasswordInput, SubmitInput, RadioInput, TextInput, Text, Ticker, PageID,
  BrowserInit, CheckboxInput, Form, GenericListBox, Grid, ListBox, Logout, Popup,
  QuickLink, Select, SetVariable, StaticImage and TextArea TagModule.cpp.

All 24 tag-module files and UTF8_Util.cpp now have no INCLUDE_ASM. Their underlying
widget/tag implementations are separate files and mostly still assembly; removing
the module wrappers does not claim those classes are decompiled.

Retail Ghidra, split instructions and prototype declarations determine each
module's allocation size, assertion conditions/line numbers and constructor argument
order. Input modules still fetch the type attribute before checking the tag name.
TextInput passes its final zero argument; Form allocates an eight-byte module,
whereas the other modules allocate four. Singleton publication follows vtable
initialization. Cleanup calls the retail destructor with flags 3, then clears the
singleton. Existing strings, vtables and singleton slots are named in
[symbol provenance](../symbols/SVO3_GLOBALS.csv); no replacement data is allocated.

PageHistory ignores query strings when comparing the top entry, shifts 31 entries
when full, and retains its home-page behavior when popping the last entry. Timer
Reset changes start/lastlap only; ElapsedMS preserves its negative result while
resetting the timer. UTF8 preserves retail quirks: 0xD0..0xDF count as three-byte
starts, a short continuation buffer reports success, append uses strcat, and the
width callback always receives the original byte count. These are recovered retail
behaviors, not modern UTF-8 validation guarantees.

### Unresolved small wrappers

| Function | Retail address | Slot | Current C output | Recovered body |
| --- | --- | --- | --- | --- |
| PageHistory constructor | 0x01EF0734 | 0x14 | 0x1C | return init(history) |
| SVChronograph custom new | 0x01EF0B3C | 0x3C | 0x40 | svAllocSafe(GetMemoryContext(), size, 0, 0x5D, source) |
| SVSock custom new | 0x01EF58C4 | 0x30 | 0x34 | svAllocSafe(memory, size, 0, 0x18, source) |

Retail uses tail jumps in these three wrappers. The current compiler emits a
call/return sequence even with explicit sibling-call optimization. They remain
explicit INCLUDE_ASM entries in their original slots, excluded from compiled
counts. Do not widen their slots or hide their status with fallback definitions.

### Validation of this batch

* Serial make split, then make -B -j8 elf: pass.
* Focused EE layout compilation: pass for the new types and expanded system-vtable prefix.
* All 115 added named-storage addresses checked against the linked ELF: pass.
* Dotted-symbol inventory parsing check and git diff --check: pass.
* ELF placement audit: pass; all **16,337** changed loaded bytes lie within
  registered compiled-function slots. Every other loaded byte and runtime header matches retail.
* Strict comparison: **NONMATCH**; matching remains unfinished.
* Project tracker: 233 compiled functions, 24 matching slots, 209 nonmatching slots;
  8,392 assembly entries. The tracker now includes 29 previously omitted dotted
  source symbols, so historical total counts are not directly comparable.
* No new behavior suites, full regression suite, ISO packaging or emulator/gameplay
  tests were run for this batch, following the user's decompilation-first preference.

Reports are under build/svo-library-work. The rebuilt ELF SHA-256 is
6378cc9d33357eb93d37a18f45384af3c3cdd88e50a6560be36483bca268191b.


## HTTP utilities and DNS cache (2026-10-07)

Added 15 C++ replacements: all nine functions in HttpUtils.cpp
(0x01F0682C..0x01F07050) and all six in DNSCache.cpp
(0x01F07FE4..0x01F0845C). Both files are now free of INCLUDE_ASM.
Retail Ghidra and split instructions establish behavior; prototype headers and
`dltypes.txt` (HTTPEntity 30925, SVPath 30930, Entry 32000, DNSCache 32011)
supply names and corroborating layouts. Four types and ten existing-storage
symbols are recorded in the type/global inventories. CQueryParams now includes
the owning HTTP header instead of repeating an escapeString declaration.

Every function has its original fixed slot. HTTP uses instruction scheduling
with the existing object-specific size flags to fit decodeURLEntityChar;
DNS loops use entry pointers rather than repeated index multiplications. Neither
change widens a slot or changes global build flags. No original function bodies
are restored through fallback symbols or machine-word arrays.

Preserved retail details:

- escapeString uses signed characters for strchr/formatting and the retail
  assertion/termination order. Its percent format is existing retail data.
- Named HTML entities use the retail map. Numeric entities require a following
  semicolon and a signed 64-bit strtol result below 256.
- URL decoding accepts uppercase A..F/digits as the first hexadecimal character;
  strtol can consume more than two digits. `%22` advances only two characters,
  leaving the last `2` for the next call. These are retail quirks, not corrections.
- Text decoding runs at least once, then clears the consumed tail. Empty/malformed
  input is not newly guarded. URL parsing keeps its fixed 15-byte scheme copy,
  default port 80, six-byte port buffer and original slash-inclusive copy length.
- printFormattedBody has no printing calls in retail; it still copies 35-byte
  chunks into a local buffer. The C source preserves that loop.
- DNS entries are 0x8C bytes with an unaligned eight-byte address at 0x80 and age
  at 0x88; the eight-entry singleton is 0x460 bytes. Construction clears only the
  first name byte, address and age. Its exit callback has no observable work.
- CacheStore/CacheStore2 skip the name comparison when choosing a new oldest
  entry. A hit resets age without replacing the address. Retrieve compares up
  to 128 characters and resets age on a hit.
- DNS normalization deliberately retains the retail request to copy 65 bytes
  into a 64-byte local buffer and then terminate at byte 63. Long input can
  overwrite stack storage; compiler-dependent malformed-input behavior is
  unfinished matching work, not a claim of equivalence. The 129-byte entry-name
  copy request is also preserved (the normalized source is at most 63 bytes).

Validation remains compilation/placement focused, per the user's request.
New behavior suites, full regression tests, ISO packing and gameplay tests are
not part of this batch. Exact instruction and malformed-input matching remain
unfinished even when the ELF placement audit passes.

The rebuilt ELF passes the slot audit: 18,537 loaded bytes differ, all inside
registered compiled slots; every other loaded byte and runtime header matches.
Strict comparison remains NONMATCH (5,130 core.text and 13,407 net.text bytes).
All 15 replacements are real compiled functions at their original addresses,
and all ten newly named globals resolve to the verified retail addresses.
The type probe passes four sizes and 12 offsets. Project totals: 8,625 source
functions, 8,377 assembly, 248 compiled; 24 matching slots and 224 nonmatching.
SVO3 totals: 180 compiled, 755 assembly; 36 of 97 files free of INCLUDE_ASM.
Rebuilt SHA-256: `ac4b0f6099ce549519b96d4403558c87a450f6059388e76a3d3b38c2688a72eb`.
Logs/probes are under ignored `build/svo-library-work/http-dns-*`.


## Cookies and module/plugin managers (2026-10-07)

Added 13 C++ functions across three original translation units:

- CCookie.cpp: all five functions, 0x01EEFEB8..0x01EF03CC; no INCLUDE_ASM remains.
- SVTagModuleList.cpp: constructor, singleton access, resource release and module
  insertion, 0x01EF2C94..0x01EF2DB8. Its allocator remains assembly.
- CPluginManager.cpp: initialization, update dispatch, message delivery and queue
  clearing, 0x01F04C40..0x01F04E88. Constructor/allocator remain assembly.

Evidence is the explicit retail Ghidra program, complete split instructions,
prototype headers and dltypes.txt: CCookieJar line 30776, SVTagModuleList 30800,
PluginExpectedMessage 31715, CPluginManager 31720, SVTag 31877 and CPluginBase
33436. Eleven globals name existing retail storage. Eight new types and two
expanded declarations are in the type inventory; a focused EE probe passes ten
sizes and 32 offsets. SVTag and CPluginBaseState retain explicit unrecovered
regions; their vtable declarations are prefixes, not complete interfaces.

Retail behavior retained:

- Cookie entries are 16 packed 127-byte name-NUL-value strings. Empty values
  delete an existing entry; the first vacant entry is remembered while scanning
  for an existing name. The final byte of each entry is checked before use.
- Header serialization preserves the original capacity check before adding the
  `Cookie: ` prefix or separator; it uses the retail format strings and clears
  the destination first. No new bounds behavior is substituted.
- Set-cookie parsing rejects `Cookie:` request headers, skips whitespace after
  the first colon, truncates its 127-byte local copy at byte 126, and requires
  both `=` and a trailing `;`. A missing colon is not newly guarded. Invalid
  input and assertion continuation still need behavioral/matching work.
- Cookie cleanup frees the singleton using the memory context of the receiver,
  then clears the singleton. Initialization reloads the singleton after calls.
- Module-list cleanup invokes vtable offset 0x0C (FreeResources), clears each
  visited slot afterwards, then deletes and clears the global list singleton.
  Insertion uses the first null slot; it does not increment m_nextTagUID.
- Plugin manager loops reload the plugin count after callbacks. Message delivery
  checks up to 32 expected-message records per plugin, stops on the first empty
  sender name, calls GetTagName for each nonempty record, and delivers every
  matching listener. It reloads the plugin pointer after callbacks as retail does.
- Update forwards the full 64-bit register value to the Process callback. Message
  events are saved/reloaded as 32-bit values. These distinctions are explicit in
  the declarations rather than copied from Ghidra's generic callback types.

Three recovered wrappers still exceed their fixed retail slots with current
EE flags. Independent C compilation measured the constructor at 0x1C bytes
(retail 0x14), and each allocator at 0x40 bytes (retail 0x3C):

```cpp
void CPluginManager(CPluginManagerState *manager) {
    Initialize___dupe5(manager);
}
void *SVTagModuleListNew(unsigned int size) {
    return svAllocSafe(GetMemoryContext(), size, 0, 0x51, svoTagModuleListSource);
}
void *PluginManagerNew(unsigned int size) {
    return svAllocSafe(GetMemoryContext(), size, 0, 0xDD, svoPluginManagerSource);
}
```

These remain explicit INCLUDE_ASM entries in their own original sections and
are excluded from the compiled-function registration. This brings the known
compact-wrapper backlog to six, including the earlier PageHistory, SVChronograph
and SVSock wrappers. No slot was widened. Batch probes/logs are ignored under
`build/svo-library-work/cookie-module-*`. New behavior suites, ISO packaging and
gameplay checks remain deferred per the user's decompilation-first preference.

Serial split and forced ELF rebuild pass. The placement audit verifies all new
functions as compiled symbols at their original addresses; 19,762 changed loaded
bytes are confined to registered compiled slots. All other loaded bytes and
runtime headers match. Strict comparison reports NONMATCH (5,130 core.text,
14,632 net.text differences). All eleven new storage mappings resolve correctly.
Project inventory: 8,625 functions, 8,364 assembly, 261 compiled; 24 matching
slots and 237 nonmatching. SVO3: 193 compiled, 742 assembly; 37 of 97 files free
of INCLUDE_ASM. Rebuilt SHA-256: `f1d26593065042f4d9c1e6075c5aaead75f4fd833d6cd9b0feaf63f3b59eb064`.


## URI storage, scheme manager and redirect factory (2026-10-07)

Added 29 C++ replacements across three original translation units:

- SVURIStore.cpp: eleven functions within 0x01F04068..0x01F045E8. Its allocation
  wrapper remains assembly. The first function, FreeResources___dupe43, releases
  the redirect module singleton and stays in this original split file.
- URISchemeMgr.cpp: fifteen functions within 0x01F07050..0x01F075F4. Register and
  CURISchemeMgr remain assembly because their recovered C exceeds the slots.
- RedirectTagModule.cpp: all three functions, 0x01F03F44..0x01F04068, now C++.
  Together with FreeResources___dupe43 this recovers the whole redirect factory;
  RedirectTag itself is still assembly.

Evidence: explicit retail Ghidra program and full split instructions, prototype
SVURIStore/URISchemeMgr headers and dltypes.txt (URIRequest 30169, sProviderEntry
30180, CURISchemeMgr 30185, URIEntry 31302, URIStore 31319, IURISchemeProvider
33616). Ten named globals bind existing retail storage. Seven new declarations
bring the inventory to 119 types; an EE probe checks seven sizes and 17 offsets.
URIRequestPrefix exposes only the first pointer, not the complete 0x20 request;
the provider vtable is a prefix through offset 0x1C. Other argument types remain
forward declarations where no field access is needed.

Preserved URI-store behavior:

- Entry initialization clears value then lookup. Entry cleanup frees both
  strings without nulling the fields; store cleanup visits all 64 entries and
  does not reset the count. It is not safe to assume cleanup is idempotent.
- setURIProps asserts empty pointers, allocates lookup then value, performs the
  retail late input assertion, and copies both strings. Reusing a local source
  filename pointer and inspecting the two existing pointer words together keeps
  this body at 0x118 bytes. The latter changes normal load order only; invalid
  object/address behavior is not claimed equivalent.
- Store construction calls each entry initializer before clearing the whole
  entry array. Adding an existing lookup leaves its value unchanged. Add/find
  reload the count after calls, keep the signed retail bound checks, and do not
  add new malformed-input guards.
- LoadInFromMemory ignores its size argument, repeats the initial delimiter
  search, modifies the input into name/value strings, and processes at most 64
  pairs. A missing second delimiter remains an unchecked dereference in retail;
  no parser correction is introduced under the guise of decompilation.

Preserved scheme-manager behavior:

- The singleton occupies 0x40 bytes immediately before DNSCache storage. Its
  initialized flag and atexit ordering match retail. Destructors only perform
  conditional builtin deletion; they do not call shutdown implicitly.
- Registration scans all eight entries, keeps the last vacant slot, rejects a
  duplicate only when both scheme and provider match, and retains caller-owned
  scheme pointers. Earlier successful registrations remain after a later error.
  DeRegister clears every matching entry, including null matches.
- GetProvider/GetFreeProvider return the first current match and reload the
  provider after strcmp/IsBusy calls. If a callback clears that entry, scanning
  continues. IsBusy is checked as a full 64-bit register value.
- Requests pass request/listener/context to vtable offset 0x0C, ignore its result,
  and return the selected provider. Shutdown invokes offset 0x18 with flag 1 for
  every registered entry (including repeated providers), without clearing slots.
- Persistent-data loading keeps each callback's full 64-bit return value and
  stops at the first zero. init clears scheme then provider and preserves the
  last-entry address in the return register, although the prototype declares void.

Three recovered wrappers remain explicit assembly. Current compiler output:
URIStoreNew 0x40 / retail 0x3C, Register 0x40 / retail 0x3C, CURISchemeMgr 0x20 /
retail 0x1C. This brings the documented compact-wrapper backlog to nine. Bodies:

```cpp
void *URIStoreNew(unsigned int size) {
    return svAllocSafe(GetMemoryContext(), size, 0, 0x4A, svoURIStoreSource);
}
int Register(IURISchemeProviderState *provider, char **schemes) {
    return Register___dupe2(Get(), provider, schemes);
}
void *CURISchemeMgr(CURISchemeMgrState *manager) {
    return memset(manager, 0, 0x40);
}
```

No retail slot was widened, no original function fallback restored, and no ELF
bytes were substituted for source. Existing per-object flags suffice; no new
optimization override was required. New behavior suites, ISO packaging and
emulator/gameplay checks remain deferred. Batch logs/probes use ignored
`build/svo-library-work/uri-*` paths.

Serial split and forced rebuild pass. The placement audit verifies all 29 new
compiled functions at their original addresses. All ten new globals resolve to
the recorded retail addresses. There are 21,689 changed loaded bytes, all within
registered compiled slots; every other loaded byte and runtime header matches.
Strict comparison remains NONMATCH (5,130 core.text, 16,559 net.text differences).
Three new slots match exactly: URIEntry, IURISchemeProvider, HasProvider. The other 26
new slots remain nonmatching; slot equality does not replace gameplay validation.
SVO3 now has 222 compiled functions and 713 assembly entries; 38/97 files are
assembly-free. Project totals: 8,335 assembly, 290 compiled; 27 matching slots
and 263 nonmatching. Rebuilt SHA-256: `15df9fe5a6cacc5665a174a495d4305beb710399e650fe801881f4a4b0823769`.


## Concrete tags and shared SVTag batch (2026-10-07)

38 new C++ replacements across six original translation units: SVTag (15/17),
LogoutTag (4/5), BrowserInitTag (4/5), RedirectTag (5/5), LineTag (5/6), and
RectangleTag (5/5). RedirectTag and RectangleTag are now entirely C++.
Evidence: explicit retail Ghidra decompilations, every replaced split function,
prototype source declarations and dltypes. 32 new symbol mappings name existing
strings, vtables, the rectangle gradient-name table and browser-init latch.

Preserved details:
- SVTag initialization leaves lineColor, contexts and type byte untouched. It
  dispatches SetVisible through offset 0x48 before resetting navigation and the
  final selection flags. FreeContexts frees without clearing its pointer.
- SetContexts copies the 24-byte context record. Selection respects virtual
  IsSelectable and the never-selectable flag. Visibility stores the supplied
  integer without normalization. Dimensions retain their independent FPR ABI.
- Plugin input emits cursor-select, then checks activation, only for a selected
  tag. The action is pad mask 0x11/action 0x10; plugin events are 8 then 0.
- Logout and redirect updates operate only when page state at 0x5B10 is idle.
  Redirect's completion flag is stored after followLink; its URL is XML-owned
  and entity-decoded in place. Browser initialization calls system vtable slot
  0x18 before setting its one-time latch at 0x0016F6AC.
- Rectangle gradient parsing stops at the first missing attribute. Drawing
  supplies a null gradient only when all four colors are zero. DrawLine uses
  f12-f17 and a0-a3; DrawRectangle uses f12-f16 and a0-a7. Runtime assertions
  and their source lines remain intact.

Placement backlog: LogoutTag and BrowserInitTag constructors emit 0x38 for
0x34-byte retail tail-call slots; LineTag emits 0x9C for 0x98. Their recovered
bodies are the base constructor, derived vtable assignment and DefaultInit;
LineTag additionally reads endX/endY/thickness, lineColor and class, in that order.
They remain visible INCLUDE_ASM entries; ignored probes preserve the C bodies.
The SVTag allocator and XML constructor remain assembly pending integration.
No slot was widened. Only new object names were added to the existing Makefile
size flags. LineTag's default initialization schedules its independent thickness
store before the other stores to fit 0x58 bytes without changing final values.

New behavior/gameplay suites are deferred at the user's request. Validation and
strict matching results for this batch are recorded in SVO3_HANDOFF.md.

Batch validation: forced ELF build and placement audit pass (23,228 changed
loaded bytes, all within C slots). Strict comparison remains NONMATCH. The 16
new matching slots are: `SetSelectable`, `GetDimensions`, `SetDimensions`, `GetQueryParams`, `SetVisible`, `GetVisible`, `GetNavInfo`, `FreeResources___dupe7`, `FreeResources___dupe12`, `HandleInput___dupe38`, `IsSelectable___dupe8`, `FreeResources___dupe34`, `HandleInput___dupe49`, `FreeResources___dupe42`, `HandleInput___dupe52`, `FreeResources___dupe60`.
All 32 new global addresses and 43 batch entry addresses pass. EE layout probe
passes 12 sizes and 87 offsets. No runtime/behavior tests were added or run.
