# Build decisions and known issues

These entries explain current constraints. Recheck source/tool evidence before
changing a mechanism; this is not a ban on justified improvements.

## Decisions

| ID | Decision and reason | Evidence / consequences |
| --- | --- | --- |
| D01 | Keep function sections and original slot bounds. Public addresses and raw pointers constrain placement. | `decompiled_functions.yaml`, `split_dl.py`; a single section per source file can shift entries. Never enlarge a slot into its neighbor. |
| D02 | Run splitting before compilation, serially. | Split post-processing normalizes alignment and regenerates the linker layout. Compiling midway previously shifted addresses. |
| D03 | Force compilation after header/INCLUDE_ASM edits. | The Makefile lacks complete dependency tracking; stale objects previously kept old D_ references after symbol renames. |
| D04 | Build 989snd with SN GCC 2.95.3 v1.36 and its bundled GNU assembler through pinned wibo; preserve remnant words and slot guards. | Updated 2026-10-16: `-G16 -O2 -fopt-stack -mno-check-zero-division`, assembler `-EL -G8 -g`. Use explicit 64-bit `mode(DI)` callback data: SN's `long long` is 128 bits. This supersedes the Sony 2.9 profile. See `989SND_MATCHING.md` and its verified inventory; do not apply sound flags globally or call remaining differences matching. |
| D05 | Pack ROM from configured load ranges, not raw RAM-address objcopy output. | Deadlocked network code lives far away in memory; the split ROM is packed. See ELF reconstruction history. |
| D06 | Bind names to existing storage with extern/symbol mappings. | Allocating another C global is not a rename. Prototype layouts/addresses need retail validation. |
| D07 | Matching and development usability are separate results. | Nonmatching development builds may compile/run; exact matching remains the goal. The verifier returns nonmatching separately and offers a strict gate. A genuinely matching C build must not be rejected merely for having zero changed bytes. |
| D08 | Preserve source/module ownership and keep tests external. | Boot options belong in boot.cpp; header ABI checks and host-test branches do not belong in production declarations. |
| D09 | Switch jump tables of compiled functions get read-only data slots at their retail addresses (decided 2026-10-14). Retail keeps each SVO3 function's tables in the main `.rodata`; without a slot, `switch` code cannot match. | `tools/svo3_rodata_sections.py` moves each SVO3 function's `.rdata` into `.svo_<Module>_<fn>.rodata` (contents unchanged). `decompiled_functions.yaml` `rodata:` lists each slot (exactly the retail table extent, code-address entries only, owning function named). `split_dl.py` carves the retail data at slot bounds and places the compiled section with overflow assertions; unregistered sections are discarded, so a missing slot fails the link. `check_main_elf.py` allows changes only inside slots of registered compiled functions. Ten SVO3 table slots are registered; all ten match retail. Extended to iksemel on 2026-10-14: the same helper routes `.iks_*` tables; later tables of one iksemel function receive numbered sections, preserving inter-table padding. Five iksemel slots and all 40 functions now match without relocation masking. |
| D10 | Classify retail zero padding as `junk` textbin segments, not functions (decided 2026-10-14). | splat labelled `func_01F27658` inside 150,332 zero bytes after the last SVO3 function (0x01F0C844..0x01F31380). The range is now `junk/net.text/4c0844_4e5380`; the fake function and its slot were removed. Loaded bytes are unchanged. |
| D11 | Write out SVO3/iksemel jump-table loads instead of using the `lw $r,$Lnn($r)` macro (decided 2026-10-18). Sony `as` 2.10-ee sometimes encodes the macro's first instruction as `lw` instead of `lui` depending on the preceding instruction; the linked code then loads its jump target from a garbage address. | `tools/svo3_rodata_sections.py` emits `lui $1,%hi(L)`, `addu $1,$1,r`, `lw r,%lo(L)($1)` (the macro's intended expansion, as retail has it). Found in UTF8 `UTF8_CountCharacters`; every other table load was already correct and is byte-identical after the change; iksemel unchanged (40/40). |

## Current issues / research backlog

| ID | Issue | Next evidence or action |
| --- | --- | --- |
| K01 | Existing C output is not fully byte-matching. | Use measured per-function slot results in the progress tracker; investigate compiler/ABI/codegen and padding without hiding differences. |
| K02 | Boot options intentionally differ for reserved padding and malformed input. | Reconcile the documented deterministic/bounded behavior with matching; do not silently reintroduce unsafe or undefined reads. |
| K03 | Full gameplay and audible sound are not established by the automated suites. | Record emulator scenarios using the smoke checklist; preserve the distinction between SDK mocks and hardware behavior. |
| K04 | RAC, GC, and UYA lack verified game Makefiles/profiles. | Establish each game's split/assembly matching baseline before borrowing the DL build design. |
| K05 | Some recovered types are prototype-only. | Validate retail access widths/offsets before using them; preserve the evidence labels in the type inventory. |
| K06 | Retired asset-bank repacking could corrupt debug-font extraction in rebuilt discs. | Superseded by boot-only CLI replacement, which preserves original game data. Full-disc byte comparison verifies preservation; keep emulator checks separate. |
| K07 | ps2dev ee-gcc 3.2.3 never emits MIPS sibling (tail) calls; retail does. Tail-calling functions and wrappers cannot fit retail slots. | **Decided 2026-10-13 (user):** SVO3 objects build with SCE ee-gcc 2.96-ee-001003-1 and its bundled `as` (Makefile `ee-gcc296` target, SVO3 rule); the rest of the game stays on 3.2.3. **Extended 2026-10-13 (user) to iksemel**, which ships with SVO3: 9/9 probed functions matched under 2.96 `-Os` vs 1/9 under 3.2.3; it uses the SVO3 flags minus `-mno-split-addresses` (`src/games/dl/DOCS/libraries/IKSEMEL.md`). The compiler is 32-bit and runs through `src/games/tools/ee296_statshim.c` (LD_PRELOAD) for bind-mount stat. Evidence: `src/games/dl/DOCS/libraries/SVO3_TAIL_CALL_BLOCKERS.md`. Do not widen slots. |
| K07 | ps2dev ee-gcc 3.2.3 never emits MIPS sibling (tail) calls; retail does. Tail-calling functions and wrappers cannot fit retail slots. | **Decided 2026-10-13 (user):** SVO3 objects build with SCE ee-gcc 2.96-ee-001003-1 and its bundled `as` (Makefile `ee-gcc296` target, SVO3 rule); the rest of the game stays on 3.2.3. The compiler is 32-bit and runs through `src/games/tools/ee296_statshim.c` (LD_PRELOAD) for bind-mount stat. Evidence: `src/games/dl/DOCS/libraries/SVO3_TAIL_CALL_BLOCKERS.md`. Do not widen slots. Sony `as` also runs with `-g` (no assembler delay-slot reordering, matching retail; only `.mdebug`, which the linker discards, changes). |

Medius compiler finding (2026-10-13): the recovered
`medius/rt_util/rt_memory` functions use SCE `2.96-ee-001003-1` plus bundled
`as`, with `-O2 -G0` and default split-address optimization. Three functions
(184 bytes) match retail exactly; the complete 776-byte module is preserved.
Only this verified object uses the new Medius rule. Other Medius components and
historical compiler identity remain unproven. See
[src/games/dl/DOCS/libraries/MEDIUS.md](../../src/games/dl/DOCS/libraries/MEDIUS.md)
for the controlled compiler matrix, flags, and verification limits.

SDK compiler finding (2026-10-13): `code/sdk` uses the SCE 2.96 compiler and
bundled assembler with its own `-O2 -G0` profile, preserving default split-address
optimization and alignment. Seven C probes across three modules match 744 retail
bytes; the fourth module still needs a C probe. Switching the four assembly-only
objects to this rule preserves every loaded byte in the isolated full rebuild.
See [SDK compiler evidence](../../src/games/dl/DOCS/libraries/SDK.md).

Historical failures to avoid repeating include exit/Exit filename collisions on
Windows, incorrect HI16/LO16 target aliases, misplaced section-relative linker
assignments, and stale lowercase test paths on Linux. The
[ELF reconstruction notes](../../src/games/dl/DOCS/build/ELF_REBUILD.md) and
[platform checks](../build/PLATFORM_VERIFICATION.md) describe the fixes.
See [989snd notes](../../src/games/dl/DOCS/sound/989SND_REUSE.md) for sound-specific
behavior and [type evidence](../../src/games/dl/DOCS/types/RECOVERED_TYPES.md) for
layout limits. Record new decisions with the concrete reason and evidence rather
than making a failed experiment into a universal rule.


### 2026-10-16: 989snd exceeds the 90% exact-function milestone

Fresh serial split and forced build verify 54/59 (91.53%) exact complete slots,
up from 51/59. Flush, bank-load callback, and EE bank load now match. The
prototype's four-word return buffer plus explicitly mapped scalar views of its
first word/status and the completion-record callback reproduce retail's mixed
GP/absolute accesses and independent reads; no new storage or instruction
patching is involved. Keep the SN v1.36 compiler `-G16` / assembler `-G8` profile.
The state suite asserts all shared-storage alias addresses. Sound behavior
3,013/3,013, ABI, globals, SDK, iksemel, and slot/runtime audits pass. Module
backlog is 1,291 bytes across five functions; whole-game strict comparison still
fails with 10,638 changed loaded bytes inside registered slots. Gameplay untested.
See `src/games/dl/DOCS/sound/989SND_MATCHING.md` and the 989SND progress JSON/CSV.


### 2026-10-17: 989snd sender recovery; 95% remains unfinished

Keep SN v1.36 and its current flags. The asynchronous sender now reproduces
retail packet-store/copy order and callback-index reloads, reducing 705 to 50
complete-slot differing bytes. All 54/59 exact functions remain; module backlog
is 636 bytes. Both sound suites (3013 cases), SDK, iksemel, slot/header audits
pass; strict whole-game result is 9983 differing loaded bytes inside registered
slots. Additional native assembler versions/options did not reproduce retail's
six-instruction short loops. No generated instruction rewriting was integrated.
The best startup countdown candidate overruns its slot and stays research-only.
See DOCS/sound/989SND_MATCHING.md for artifacts and rejected toolchain probes.

## 2026-10-19: 989snd reaches 100% with a source-derived assembler profile

All 59 C functions, 18 retained fragments, and 7,236 module bytes are exact.
SN GCC 2.95.3 v1.36 still uses `-G16 -O2 -fopt-stack -mno-check-zero-division`;
its GNU assembler uses `-EL -G8 -g`. The Makefile now inserts
`tools/sound_loop_compat.py` to reproduce the observed legacy six-instruction
short-loop profile, including the delay instruction. It consumes only compiler
assembly; branch encoding derives from operands and labels, without retail
ELF input, function-name exceptions or post-link copying. Four startup extern
views preserve the original second-element address forms without new storage.
The prior blanket rejection of assembly adaptation was an overly broad reading
of the rules against copied executable bytes and hidden assembly fallbacks.
This profile is explicit and independently tested; the exact historical
assembler version remains unidentified.

All 3,013 sound behavior cases, 17 compatibility tests (including five actual
assembler vectors), SDK 20/20 and iksemel 40/40 plus five tables pass. Strict sound
verification now runs through `tools/verify.py`; `TESTS/check_989snd.py` checks
compiled definitions, entry addresses, slot bounds and every module byte.
The isolated snapshot build needed the committed SVO3 RTCommSock source and
existing case-sensitive DnsCache header alias, plus a temporary medius D_168BAC
symbol alias. Those unrelated live files were not changed. Whole-game strict
comparison remains NONMATCH: 3,917 loaded bytes within registered slots, all
outside sound; runtime headers and other loaded bytes match. Gameplay untested.
See `src/games/dl/DOCS/sound/989SND_MATCHING.md` for reproducible evidence and limits.

## 2026-10-19: Recover the older newlib math sources

Imported the 37 math sources present in boot.elf from official newlib 1.9.0,
retaining attribution/license and excluding upstream copies from source discovery.
The evidence favors the older 1.8.2/1.9.0 family; it does not uniquely identify a
release. SN GCC 2.95.3 v1.36 with `-G0 -O2 -fno-builtin` and assembler `-EL -G0`
produces 14 exact C functions (37.84%), including the float cosine kernel and
scalbnf. Remaining functions keep explicit assembly. Source/compiler evidence,
archive hashes and follow-up targets are in `DOCS/libraries/NEWLIB_LIBM.md`.

Preserve the original CDCDCDCD alignment bytes as textbin fragments. Compiler
constants already materialized in instructions may leave duplicate unused
.rodata; the new helper refuses to remove it if any relocation, exported symbol,
or writable/executable flag makes removal unsafe. Five assembler fixtures test
that guard. No original executable instructions are copied into compiled functions.

All 21,272 libm bytes match; 1,760 are verified compiled function bytes. The
slot/header audit passes and existing 989snd/SDK/iksemel matches remain exact.
Whole-game strict differences remain 3,917 bytes outside libm. Verification uses
an isolated snapshot with the previously documented unrelated SVO3/header and
medius alias accommodations. Gameplay untested. The standard verifier now includes
`check_libm.py`; progress is scoped to LIBM.json/CSV to preserve concurrent SVO3 work.

## 2026-10-19: Expand libm to 31 exact C functions

Sony GCC 2.9-ee-991111-01 with `-G0 -O2 -fno-builtin` reproduces 30 of the 37
newlib 1.9.0 functions. Verbatim newlib 1.8.1 `rint` adds the 31st; 1.8.2 and
later introduce a volatile temporary and do not match. Pin this compiler archive
in the Makefile, preserve the older source attribution, and leave six unmatched
IEEE float kernels as explicit assembly. This does not establish one unique SDK release.

Reuse exact read-only-data placement for compiled numerical constants and strings.
The splitter now preserves partial-word padding after a six-byte string by splitting
only a literal word, never a relocation. Regression tests cover that boundary and
relocation rejection. No slot was widened. Unreferenced duplicate pools still use
the guarded removal helper. The library checker now verifies compiled pools too.

Full isolated ELF verification: 31/37 (83.78%), 15,956 compiled instruction bytes,
1,762 compiled constant bytes, and the entire 21,272-byte library match. Original
source splits survive splitting. Runtime-header/slot audit and placement safeguards
pass. Strict whole-game differences remain 3,917 bytes outside libm, unchanged from
the baseline. The same documented snapshot-only unrelated build accommodations
remain necessary; no gameplay testing was performed. See NEWLIB_LIBM.md and
LIBM_FOLLOWUP_PROBES.json for reproducible evidence and the remaining six targets.

## 2026-10-19: Complete libm at 37/37 exact C functions

Pin `ee-gcc2.9-991111-01.tar.xz` (SHA-256
`ed684fd98f89d36b0121caab311052089103e3b36241fcef4338cc9ea41c75b8`).
It reports the same version as the preceding `991111a` archive but emits the
retail floating-division workaround naturally. Five remaining float kernels
match unchanged 1.9.0 source; verbatim 1.8.2 `ef_asin.c` completes the last one.
Keep the already established 1.8.1 `s_rint.c`. No inline assembly, instruction
substitution, or padding adapter was needed. Related UYA compiler research supplied
the lead; Deadlocked's unmasked linked-byte checks establish the result.

All 37 functions are C and exact (100%): 21,180 instruction bytes, 2,046 compiled
constant bytes and all 23 four-byte alignment gaps. All original source splits
and public addresses remain. Full isolated ELF verification and slot/header audit
pass; strict whole-game comparison retains the same 3,917 differences outside
libm. The documented unrelated snapshot accommodations remain; gameplay untested.
See LIBM_FINAL_PROBES.json and NEWLIB_LIBM.md for provenance and reproduction.
