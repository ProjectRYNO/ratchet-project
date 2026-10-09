# Recovered data types

> Current acceptance policy: [the shared game rules](../../../../../.agents/guides/GAME_WORKFLOW.md)
> require exact executable matching and preserved behavior. The nonmatching C
> validation described below is historical/diagnostic evidence, not a 1:1 pass.

77 types are declared in 39 module headers under `code/game`, following their
ownership in the prototype sources. `GameBootOptions` and `blockhdr` were local
to prototype `boot.cpp`; their declarations live in `boot.h` for reuse.
These are partial module headers, not complete reconstructions of every class.

Every member retains the dump's byte offset, and each struct carries its PS2
size. Bit-field comments use `byte:bit`, as in `dltypes.txt`. Header guards are
filename-based; subdirectory names distinguish module headers. Redundant struct
tags are omitted. No data allocations, Makefile changes, or linker changes are
needed for these declarations.

## Evidence and limits

Sources: the local `deadlocked-proto-decomp` tree and its `dltypes.txt`, plus
Ghidra's `/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf` program. The inventory in
[RECOVERED_TYPES.json](RECOVERED_TYPES.json) records source ownership, dump line,
size, field offsets, destination header, and evidence for each type.

* 45 types: Ghidra's named structure size, field names, and offsets match the dump.
* 31 types: recovered from the prototype and dump; no matching retail Ghidra structure was available.
* `GameBootOptions`: the retail encoder at `0x001579F0` confirms the packed
  fields and offsets. Ghidra did not have this named structure.

Ghidra layout agreement corroborates the type database; it does not prove every
retail function uses every field identically. Check retail accesses before using
prototype-only fields in new decompiled functions. Complex C++ classes, unknown
callback signatures, conflicting same-name definitions, and structures requiring
unrecovered dependencies remain deferred rather than being replaced with guessed
layouts. This pass prioritizes independent data structures from prototype headers.

## Boot options and runtime settings

`GameBootOptions` is the eight-byte serialized payload encoded as sixteen hex
digits. `screen_offset_x` is a 16-bit field at offset 4; `screen_offset_y` is a
16-bit field at offset 6. Its first word contains the display/audio bit fields.

`displayX` (`0x0021DAA8`) and `displayY` (`0x0021DAAC`) are separate 32-bit runtime
globals, known as `g_DispXPOS` and `g_DispYPOS` in Ghidra. The encoder packs their
low halves into `GameBootOptions`; the decoder restores them. They are not an
instance of the packed structure at those addresses.

`GameSettings` describes the settings storage at `bootSettings` (`0x00171D38`).
The retail boot encoder confirms `Stereo` at 8, `MusicVolume` at 12,
`EffectsVolume` at 16, `Wide` at 0xB3, and `Language` at 0xBD. `boot.cpp` now uses
those member names instead of pointer arithmetic. The remaining members and full
0xC4 extent come from the prototype/dump. No new copy of settings is allocated.
The explicit wire encoding retains deterministic padding and malformed-input
bounds from the existing implementation.

## Validation

Run `python3 tests/check_type_layouts.py` inside the project toolchain container.
The checks live outside production headers. They use the EE compiler to check
all recovered sizes and non-bit-field offsets (737 checks), each header in
isolation, and ten compiled boot-option bit-field packing vectors. The boot host tests exercise
known vectors, 4096 round trips, malformed input bounds, and untouched settings
bytes. The ELF audit checks compiled boot functions and unchanged unrelated bytes.

The Makefile does not track header dependencies. Force affected objects to
rebuild after changing a header (`make -B -j8 elf`), or use a clean build.

Verified for this change: a forced working-tree ELF build and an isolated
`full-clean -> ps2dev -> rom -> split -> elf` build passed. Both have identical
loaded bytes and runtime headers. Compared with the preceding compiled ELF,
16 bytes changed, all in the boot-option encoder's instruction scheduling;
all other loaded bytes and runtime headers were preserved. The clean build also
passed 2,720 sound-wrapper cases, 293 stateful sound cases, and the 806-global
address audit. Host boot tests passed their six argument/control-flow cases and
4,096 option round trips. Logs are under `build/type-recovery` (generated files).
No new emulator/gameplay test or ISO repack was performed for this type pass.


## iksemel node (2026-10-07)

Added `iks` in `code/iksemel/src/iks.h`: size 0x30 with all 12 offsets checked
using the EE compiler. Retail allocation/insertion/accessor instructions establish
the layout; dltypes.txt only supplies an incomplete iks_struct and node enum.
See [iksemel evidence and tests](../libraries/IKSEMEL.md).

## SVO3 core contexts (2026-10-07)

Added ten types across five headers: audio/system/input/memory contexts, explicitly
partial vtables, SVButtonMap, CMemChunk, and CConfigState. Retail instructions verify
the used offsets/strides; the prototype supplies field names and untouched-field
context. CSystemContextBase keeps an unrecovered 16-byte prefix; vtable prefixes
must not be treated as complete tables. The EE layout suite now checks 833 sizes/
offsets across 88 types and 45 headers, with independent header includes. See
[SVO3 evidence](../libraries/SVO3.md) for behavior and testing limits.

## Query parameters and plugin queue prefix

Recovered CQueryParam (0x08), CQueryParamListState (0x404), PluginMessage (0x08),
and CPluginQueuePrefix (0x590) from retail accesses/strides and prototype names.
The plugin declaration is explicitly a prefix, not the complete 0x638-byte class.
A focused EE compiler probe checks these sizes and used offsets. Behavior tests
are deferred under the user's decompilation-first preference; existing suites
remain available.

The following SVO3 batch adds PageHistoryState (0x2024), SVChronographState (0x10),
SVSockState (0xC), SVBrowserPrefix (0xA8), CDrawContextBase (0x4), its vtable prefix
(0x18), SVTagModuleState (0x4), and its destructor-vtable prefix (0xC). The system
vtable prefix now extends through GetElapsedMS at 0x38 (size 0x3C). All new sizes
and field offsets passed focused EE compilation. Browser and vtable prefixes are
incomplete views; they are not allocation sizes for derived/full objects. Form's
module allocates eight bytes in retail while the shared module base is four bytes.
Behavior and gameplay testing are deferred; the type inventory now has 100 entries.


The HTTP/DNS batch adds HTTPEntity (0x08), SVPath (0x14), DNSCacheEntry (0x8C)
and DNSCacheState (0x460), bringing the inventory to 104 types. A focused EE
compiler probe checks all four sizes and 12 field offsets. SVPath's port member
is retail reference storage (a pointer); DNS rtIP is an unaligned eight-byte
field, so a naturally aligned 64-bit member would give the wrong entry stride.
The prototype SVO_RT_LINKADDRESS declaration is not used to guess this layout.


The cookie/module-manager batch brings the inventory to 112 types. Added
CCookieJar (0x7F4), SVTagModuleListState (0x204), PluginExpectedMessage (0x24),
CPluginManagerState (0x58), CPluginBaseState (0x638) and its vtable prefix (0x14),
SVTag (0xB4) and its vtable prefix (0x40). SVTagModuleVtablePrefix now includes
FreeResources at 0x0C (size 0x10), and CPluginQueuePrefix identifies the 32
expected-message records at offset zero. Retail callback accesses establish the
used slots; unrecovered regions remain explicit. Focused EE compilation passes
ten sizes and 32 field offsets. Behavior/gameplay tests were deferred.


The URI batch adds URIEntryState (0x08), URIStoreState (0x204), URIRequestPrefix
(0x04), IURISchemeProviderState (0x04), its vtable prefix (0x20), sProviderEntry
(0x08) and CURISchemeMgrState (0x40). Inventory: 119 types. The EE layout probe
passes all seven sizes and 17 offsets. The request and vtable are partial views;
they must not be used as complete request allocations or complete interfaces.
Callback return values used by retail 64-bit register comparisons remain long.


The concrete-tag batch expands SVTag's 0xB4 layout and its verified vtable prefix
(0x4C), and the draw vtable prefix (0x48). New declarations are CNavInfoState
(0x10), CAllContextData (0x18), CPage's state prefix (0x5B14), RedirectTagState
(0xBC), LineTagState (0xC0) and RectangleTagState (0xD0). The system callback at
vtable offset 0x18 is HandleOnlineInitComplete. Retail draw call sites establish
independent integer and floating-point argument banks. CPage and vtables remain
partial views, not allocation sizes. Inventory: 125 declarations.

The focused EE compiler probe passes 12 type sizes and 87 field offsets for
the concrete-tag headers, including expanded existing context/vtable types.


## SVO3 50% batch

The inventory now contains 149 declarations. Added or expanded views cover
SVBrowser, download metadata and request buffers, XML adapters, the file queue,
HTTP/socket state and concrete widget/module prefixes. SVBrowser is 0x3140;
CPage's verified prefix extends through 0x6360 and the draw vtable through 0x5C.
Opaque regions remain explicitly unrecovered. Partial views must not determine
allocation sizes. The focused EE GCC probe passes 28 sizes and 158 offsets;
its source/log are build/svo-library-work/half-types.cpp and half-types.log.
The owning CInputContextBase and SVChronograph headers supply their anonymous
typedefs; no incompatible struct forward declarations are introduced.

## SVO3 form/list/page/text batch

Inventory: 159 declarations. FormTag (0x69EC), RadioElementGroup (0x184),
GenericListBoxTagState (0xE4) and ListBoxItem (0x1C) are recovered. ListBoxTagState
is now 0x288, RadioInputTagState 0x198 and CheckboxInputTagState 0x194.
TextInputTagState remains a 0x4E4 prefix of the 0x514 allocation; TextAreaTagState
remains a 0x180 prefix of 0x194. CPage remains a 0x6360 prefix of 0x637C.
Expanded views expose the fields used by the recovered functions and retain
explicit unrecovered regions. Named tag structs enable FormTag's mutually
referencing typed arrays without duplicate typedef tags.

Focused EE GCC checks pass 21 sizes and 223 offsets across the 14 changed/new
headers. Probe: build/svo-library-work/svo75-types.cpp. These checks establish
PS2 layouts, not gameplay behavior or exact instruction matching.

## SVO3 HTTP and widget defaults batch (2026-10-08)

Inventory: 168 declarations. CHttp now describes its 0x8AC4 allocation, with
explicit unrecovered gaps; typed socket, HTTP and request-listener vtable prefixes
cover the recovered callbacks. New widget headers describe QuickLinkTag (0xC0),
SetVariableTag (0xBC), TickerTag (0xC8) and ButtonTagState (0x15C). TextTagState
now spans 0x14C. List and generic-list vtables expose their virtual clear methods.

The focused EE GCC probe passes 16 sizes and 121 offsets (137 checks):
build/svo-library-work/svo-next-types.cpp. These establish layout only; new
behavior suites and gameplay checks remain deferred.


## SVO3 75 percent checkpoint (2026-10-08)

The inventory now contains 184 types in 100 headers. Full EE layout verification
passes 1,698 size/offset checks, independent header inclusion and ten boot packing
vectors. Expanded declarations cover grid/text widgets, HTTP/SSL and request
listeners, page display buffers, downloads, sockets, persistent data and MD5.
Retail instruction accesses establish offsets; prototype types support names.
The MD5 context preserves the retail 64-bit unsigned-long state representation.


## SVO3 page/widget continuation (2026-10-08)

The inventory now contains 188 types in 101 headers. Full EE layout verification
passes 1,755 size/offset checks, independent header inclusion and ten boot packing
vectors. Added ParseXMLVtablePrefix, SVTagInfo, SVTagScanResult and
TextEditableTagVtablePrefix; expanded page transition queues, persistent server
settings, widget drawing callbacks, SubmitInputTag and HttpSecure (0x9B00).
Retail offsets and callback argument banks were checked against instructions;
prototype names support declarations. These checks establish layout, not gameplay.


## Networking and image callback continuation (2026-10-08)

Inventory: 196 types/101 headers; 1,802 PS2 size/offset checks PASS, independent
header inclusion and ten boot packing vectors PASS. Added URIRequest,
HTTPSInterface, SVRTCommAddrState, RTLinkAddress, RTCommLookupParams,
RTCommChannelOptions, RTCommSockVtablePrefix and RTUnalignedWord. Expanded
CDrawContextVtablePrefix to 0x98 and recovered HTTP/listener callback signatures.
The packed unaligned word models observed LDL/LDR and SDL/SDR accesses; it does
not change storage allocation. Layout checks do not establish gameplay behavior.


Text input and HTTP callback recovery (2026-10-09): 1,809 size/offset checks across 196 types and 101 headers pass, as do independent header inclusion and ten boot packing vectors. Typed editability/input/drawing callbacks and SVSock::addrAsString retain existing offsets and sizes.


Text-area/image drawing callbacks (2026-10-09): recovered DrawTextArea at 0x48 and StoreDownloadedImage at 0x54 without changing CDrawContextVtablePrefix size. PASS: independent header includes and 10 EE boot-option packing vectors; PASS: 1811 PS2 sizes/field offsets across 196 types and 101 headers


Browser/page/grid/list/login continuation (2026-10-09): recovered CTagModuleActions, callback prefixes, full CPage tail (0x637C), persistent state (0x1B9C), browser VKB storage and list vtables. Retail split offsets and callback arguments take precedence over Ghidra labels. PASS: independent header includes and 10 EE boot-option packing vectors; PASS: 1889 PS2 sizes/field offsets across 210 types and 101 headers
