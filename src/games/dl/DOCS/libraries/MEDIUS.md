# Deadlocked Medius library

## rt_util batch 3 (2026-10-14)

**37 Medius functions now compile to exact retail bytes** (30 after batch 2). This
batch adds `rt_timebase.c`: 7 of its 8 functions are exact, and the whole
0x01EABC10..0x01EABF38 module matches retail, including the retained assembly.
Medius inventory: 37 of 1,462 INCLUDE_ASM entries replaced (2.53%).

rt_timebase is the Medius clock synchroniser. `update_globaltime` records half of each
round trip in a 100-entry history. `get_percentiledelay` bubble-sorts a copy and
returns entry `count / 20` (at least entry 1), roughly the 5th percentile. When that
value is at least the new half-delay, the global time is reset to server time plus the
half-delay. `get_globaltime` advances the global time by local-time deltas, and
`is_query_ready` gates queries on `rtTimebaseQueryInterval` (3000 ms in retail data).

Globals: the prototype dlglobals.txt lists none for rt_timebase.c (file statics), so
the six names describe their retail use. Each is mapped in `symbols_core.text.txt`,
with evidence in the new [MEDIUS_GLOBALS.csv](../symbols/MEDIUS_GLOBALS.csv), and
verified by `check_medius.py`:

| Name | Address | Section | Role |
| --- | --- | --- | --- |
| rtTimebaseLastLocalTime | 0x00168BA4 | core.data | last rt_time_get_local value |
| rtTimebaseGlobalTime | 0x00168BA8 | core.data | synchronised global time |
| rtTimebaseStarted | 0x00168BAC | core.data | set by rt_timebase_start |
| rtTimebaseQueryInterval | 0x00168BB0 | core.data | 3000 ms query gate |
| rtTimebaseDelays | 0x001B2420 | core.bss | RT_TIMEBASE_DELAYS (0x198) |
| rtTimebaseQueryTimer | 0x001B25B8 | core.bss | RT_TIME_STAMP query timer |

Types: `rt_time.h` holds the prototype `RT_TIME_VAL` and `RT_TIME_STAMP {Secs, USecs}`
and the rt_time prototypes used here. `rt_timebase.h` holds `RT_TIMEBASE_DELAYS
{delay[100], count 0x190, index 0x194}`, recovered from retail accesses. Both are in
RECOVERED_TYPES.json.

Source-shape findings: `get_globaltime` computes `delta = now - last`, stores `last`,
then adds the delta. The bubble sort compares `sorted[j] > sorted[j + 1]`. `restart`
clears `rtTimebaseLastLocalTime` before `rtTimebaseGlobalTime`.

**Probe limitation found.** `probe.py` masks the low 16 bits of HI16/LO16 relocations.
Two globals that share a `%hi` (0x168BA4/0x168BA8) can therefore be swapped without the
probe noticing. The first rt_timebase_restart build swapped them; the real link and
`check_medius.py` caught it. Always confirm with the linked ELF.

`rt_timebase_update_globaltime` (0x01EABCE0, 0xBC) remains assembly. The best
candidate is 4 bytes short: retail copies `roundTrip` (`move v1,a0`) before halving
it, and none of the tried shapes reproduces that (separate `half`, reassigning the
parameter, nested start check). Candidates are under `build/medius-work/` (ignored).

Validation: `check_medius.py` reports all 37 functions exact and all seven modules
byte-identical, with 6 globals at retail addresses. The placement audit passes with
13,749 changed bytes, all in other libraries' slots. `verify.py dl --split` exits 0.

```sh
O=build/code/medius/rt_util
python3 TESTS/check_medius.py ../assets/dl/boot.elf build/boot_elf.elf $O/rt_memory.o \
  $O/rt_constraint.o $O/rt_string.o $O/rt_mutex.o $O/rt_pack.o $O/rt_msg_util.o $O/rt_timebase.o
```

Next: rt_circ_buf (17), rt_list_buf (14), rt_parse (11), rt_token (21), rt_time (18).


## rt_util batch 2 (2026-10-14)

**30 Medius functions now compile to exact retail bytes** (14 after batch 1, 3 before).
Three more `rt_util` modules join the first three. All six match retail byte-for-byte,
including retained assembly:

| Module | Exact | Retail range | Retained assembly |
| --- | ---: | --- | --- |
| rt_memory.c | 9/9 | 0x01EA94D0..0x01EA97D8 | `func_01EA9548` (fragment) |
| rt_msg_util.c | 8/8 | 0x01EA97E0..0x01EA9984 | none |
| rt_mutex.c | 4/4 | 0x01EA9D98..0x01EA9F7C | `func_01EA9ED0` (fragment) |
| rt_pack.c | 4/5 | 0x01EAA0D0..0x01EAA4BC | `rt_pack_cstring` (real function, unmatched) |
| rt_constraint.c | 4/4 | 0x01EA8DF0..0x01EA8EC8 | `func_01EA8E68` (fragment) |
| rt_string.c | 1/1 | 0x01EAB1B8..0x01EAB210 | none |

Medius source inventory: 30 of 1,462 INCLUDE_ASM entries replaced (2.05%).

Source-shape findings (same toolchain and `MEDIUS_COMPILE_FLAGS` as batch 1):

- rt_pack's guards are separate `if`s that each set `lastError`. The first is written
  `buffer->end <= buffer->cursor`, so `end` loads before `cursor`. Merging them with
  `||` changes the branch layout. The space check is `(unsigned)(end - cursor) < n`;
  for n == 1 the compiler turns it into the retail `end != cursor` test.
- `rt_pack_cu2byte` (compressed u16: values >= 0x80 use two bytes with bit 7 set;
  >= 0x7FFF is RT_INVALID_PARAM) and `rt_pack_anything` re-read `cursor` after the
  pack/unpack branch. An unknown mode only advances the cursor.
- `rt_mutex_lock` increments `lockCount` separately in the owned and newly-locked
  branches, so `*count` re-reads it after the join. Unlock returns
  RT_MUTEX_NOT_OWNED (901) and RT_MUTEX_NOT_LOCKED (902).
- rt_msg_util setters use `result = RT_INVALID_PARAM; if (buffer) {...; result = 0;}`.
  Getters keep `result` but return early for each null pointer. Two-byte setters store
  `buffer[0]` first in source; the scheduler emits the high byte first. The u4
  accessors walk the buffer with post-increments.

Types: `rt_pack.h` has the prototype `RT_PACK_BUFFER {begin, end, cursor, bitOffset,
lastError}`. `rt_mutex.h` has `RT_MUTEX`. The prototype names no mutex type, so its
fields (created byte 0x0, lockCount 0x4, ownerThread 0x8, platform semaphore 0xC)
come from retail accesses. Its 0x10 size is the highest observed offset, not a
verified sizeof (recorded in RECOVERED_TYPES.json).

`rt_pack_cstring` (0x01EAA3B8, 0x104) remains assembly. The best candidate is the
same size with 13 differing words: register allocation in its rollback tail, and the
ordering of the null-string error. The retail length is `(short)strnlen + 1`, formed
by `length = rt_strnlen(string, 0x7FFF); length++;`. The tail re-tests
`cursor[-1]` after restoring `cursor = start`. Candidate:
`build/medius-work/p_ax.c` (ignored).

`check_medius.py` now takes every compiled Medius object and merges only *defined*
symbols. A first version let an undefined reference in rt_pack.o shadow rt_strnlen's
definition. It requires all 30 functions exact and all six modules byte-identical.

Validation: serial split, forced build and `verify.py dl --split` exit 0. Every suite
passes; the placement audit reports 13,749 changed bytes, all in registered slots of
other libraries. Snapshot: 7,538 assembly, 1,086 compiled, 978 matching and 108
nonmatching slots. No ISO, emulator or gameplay test.

```sh
python3 TESTS/check_medius.py ../assets/dl/boot.elf build/boot_elf.elf \
  build/code/medius/rt_util/rt_memory.o build/code/medius/rt_util/rt_constraint.o \
  build/code/medius/rt_util/rt_string.o build/code/medius/rt_util/rt_mutex.o \
  build/code/medius/rt_util/rt_pack.o build/code/medius/rt_util/rt_msg_util.o
```

Next: rt_timebase (8; first map its globals at 0x00168BA4/0x00168BA8/0x00168BB0 and
the 0x001B2420 history block from dlglobals), then rt_circ_buf and rt_list_buf.


## rt_util batch 1 (2026-10-14)

**14 Medius functions compile to exact retail bytes (3 before this batch).** Three
`rt_util` modules are fully decompiled; only splitter fragments remain in assembly:

| Module | Functions | Retail range | Retained assembly |
| --- | ---: | --- | --- |
| rt_memory.c | 9/9 exact | 0x01EA94D0..0x01EA97D8 | `func_01EA9548` (4-byte fragment) |
| rt_constraint.c | 4/4 exact | 0x01EA8DF0..0x01EA8EC8 | `func_01EA8E68` (12-byte fragment + padding) |
| rt_string.c | 1/1 exact | 0x01EAB1B8..0x01EAB210 | none |

The two fragments sit between functions and contain stray delay-slot copies, like
the two retained SDK fragments; they are not functions. Medius source inventory:
14 of 1,462 INCLUDE_ASM entries replaced (0.96%).

**Compiler flags changed.** `MEDIUS_COMPILE_FLAGS` drops the `-falign-*` options and
uses SCE 2.96 default alignment (now identical to the SDK profile). Retail pads labels
that follow an unconditional branch to 8 bytes with a `nop` (`rt_memory_allocate`,
`rt_memory_allocate_init_zero`, `rt_memory_align_alloc`); `-falign-jumps=1` removes
that padding. The three previously matched functions also match with default
alignment. `rt_strnlen` and its 4-`nop` short loop, unmatched in the original probe,
now match with default alignment too.

Source-shape findings:

- Size types follow the widening instructions. `rt_memory_allocate(_init_zero)` take a
  64-bit `unsigned long` size; `malloc`/`memset` and the aligned functions use 32-bit
  sizes, so callers truncate with `dsll32`/`dsra32` and widen with `dsrl32`.
- `rt_memory_allocate` tests `!gpfMallocCallback` first, like `rt_memory_free`.
- `rt_memory_align_alloc` returns through one `result`
  (`if (!result) result = rt_memory_get_aligned_address(...)`); a direct `return`
  becomes a tail call that retail does not have.
- `rt_memory_align_alloc_init_zero` uses `result = RT_MEMORY_ALLOC_ERROR` and
  `if (memory && size) {...}`; `rt_memory_allocate_init_zero` uses plain early returns.
- `rt_strnlen` initialises `end = s + n` in its declaration; retail computes it in the
  null check's delay slot.

Types and globals (prototype names from dltypes.txt/dlglobals.txt, offsets confirmed
by retail accesses; EE layout checks added to RECOVERED_TYPES.json):

- `rt_memory.h`: `RT_MEMORY_ALIGNED { pAlloc; pUse; }`, `RT_MEMORY_ALLOC_ERROR` (100).
- `rt_constraint.h`: `RT_U1BYTE_CONSTRAINT`, `RT_4BYTE_CONSTRAINT`,
  `RT_U4BYTE_CONSTRAINT` (`lowVal`, `highVal`), `RT_CSTRING_CONSTRAINT`
  (`minSize`, `maxSize`).
- `rt_string.h`: `rt_strnlen`.
- `gpfReallocCallback` = 0x001681A8 (mapped in GLOBAL_VARIABLES.csv): the prototype
  declares it between the malloc (0x1681A4) and free (0x1681AC) callbacks, and
  retail `rt_memory_register_another_callback` stores its argument there.

Placement: `decompiled_functions.yaml` registers object bounds and slots for
rt_constraint and rt_string and all 14 entry addresses; both objects joined
`MEDIUS_OBJECTS`. Since D09, unregistered code sections are discarded, so a missing
slot fails the link (observed and fixed during this batch).

Validation (serial split, forced build, `verify.py dl --split`, exit 0):
`check_medius.py` (all 14 functions exact at their addresses; rt_memory,
rt_constraint and rt_string modules byte-identical including retained assembly),
placement/outside-slot audit (13,749 changed bytes, all in registered slots), 807
global addresses, 1,974 layout checks across 222 types, and every other suite pass.
Strict comparison is NONMATCH only from other libraries' registered nonmatching
replacements. Project snapshot: 7,554 assembly, 1,070 compiled, 962 matching and
108 nonmatching slots. No ISO, emulator or gameplay test.

```sh
python3 TESTS/check_medius.py ../assets/dl/boot.elf build/boot_elf.elf \
  build/code/medius/rt_util/rt_memory.o build/code/medius/rt_util/rt_constraint.o \
  build/code/medius/rt_util/rt_string.o
```

Next candidates in rt_util: rt_pack (5), rt_mutex (5), rt_msg_util (8), rt_timebase (8).

## Compiler investigation

## Result (2026-10-13)

The strongest **tested** candidate is Sony SCE `ee-gcc 2.96-ee-001003-1`
with its bundled `GNU assembler 2.10-ee-001003-1`. Three recovered memory
functions now compile to all 184 original bytes, including relocated calls and
global references. This establishes a useful Medius toolchain, not the historical
compiler identity or a guarantee that every Medius component uses the same build.

Target: `src/games/dl`, USA retail `SCUS_974.65`, reference
`src/games/assets/dl/boot.elf`, SHA-256
`ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7`.
The initial Medius source inventory was 84 C files / 1,462 INCLUDE_ASM entries.
This batch replaces three; 1,459 remain. **Function progress: 3/1,462 = 0.21% decompiled and byte-matching.** Count only actual INCLUDE_ASM invocations, excluding macro definitions. Retained original assembly is not counted as decompiled progress.

## Controlled comparison

The same four C bodies were compiled at `-O1`, `-O2`, `-Os`, and `-O3`, with
`-G0`, no builtin substitution, four-byte function alignment, and one-byte
loop/jump/label alignment. Each compiler used its bundled assembler. Objects
were linked at retail addresses and compared to the original ELF's PT_LOAD
bytes without relocation masks. The fourth probe, `rt_strnlen`, remains
unmatched and is not integrated.

| Compiler | O1 | O2 | Os | O3 |
| --- | ---: | ---: | ---: | ---: |
| SCE 2.96-ee-001003-1 | 0/4 | **3/4** | **3/4** | **3/4** |
| SCE 3.2-ee-040921 | 0/4 | 0/4 | 0/4 | 0/4 |
| ps2dev GCC 3.2.3 | 0/4 | 1/4 | 1/4 | 0/4 |

The ps2dev match is only callback registration. The probes do not distinguish
O2 from Os/O3 for the three matching functions; O2 is the working selection.
Other Sony versions and SN/ProDG were not tested. SVO3's compiler findings
motivated the comparison, but Medius was measured independently.

Use default split-address optimization. SVO3's `-mno-split-addresses` failed to
reproduce the Medius memory probes during the initial comparison. The dedicated
`MEDIUS_COMPILE_FLAGS` preserve the winning settings:

```text
-G0 -O2 -fno-builtin -fno-common -ffunction-sections
-falign-functions=4 -falign-loops=1 -falign-jumps=1 -falign-labels=1
```

Assembler flags are `-EL -G0 -g -Icode/include`. The existing `ee-gcc296`
installation/stat shim is reused. Only `medius/rt_util/rt_memory.o` currently
uses the Medius rule; add further objects after their replacements are verified.
Other libraries' compiler rules are preserved.

## Integrated functions

| Function | Retail entry | Exact bytes |
| --- | --- | ---: |
| rt_memory_free | 0x01EA95C0 | 88 |
| rt_memory_register_callbacks | 0x01EA9768 | 24 |
| rt_memory_get_aligned_address | 0x01EA9790 | 72 |

Source ownership is `code/medius/rt_util/rt_memory.c`. Retail Ghidra and split
instructions were used together. Existing callback storage stays at its mapped
retail addresses; no duplicate globals are allocated. Null handling, callback
store order, unsigned-short alignment, and the retail error return (100) are
preserved. `rt_memory_free` expects a valid pointer-to-pointer, as retail does.

The manifest places both retained assembly and compiled functions at their
original addresses. The two existing trailing nops around 0x01EA9544 and
0x01EA954C are retained within their assembly slots. No original instructions
are substituted into the C implementations.

## Verification and limits

An isolated source snapshot in `projectryno-medius-probe` at
`/tmp/medius-integration` was split and built separately from the active SVO3
checkout. Its existing `RTCommSock.cpp` included `DnsCache.h` while the file was
`DNSCache.h`; a snapshot-only symlink supplied that spelling for the Linux build.
No SVO3 source fix was applied to the user's checkout. Absolute source paths were
rewritten only in the snapshot to keep INCLUDE_ASM reads isolated.

- `check_medius.py`: all three are real compiled function definitions at their
  retail addresses, with exact sizes and bytes. All 776 bytes of the containing
  rt_memory module match retail, including retained assembly.
- `check_main_elf.py`: placement/runtime-header/outside-slot audit passes.
- Strict comparison against the pre-Medius baseline: zero changed loaded bytes
  and identical runtime headers.
- Strict comparison against retail: **NONMATCH**, with 34,164 pre-existing
  differences (5,130 main + 29,034 network) in this isolated snapshot. The Medius
  additions introduce none. This is not a matching whole game.
- No ISO packaging, emulator, gameplay, or separate runtime behavior test was run.

Concurrent SVO3 work can change whole-project totals. These counts describe the
saved snapshot, not later builds. The main FUNCTIONS.csv/SUMMARY.json are not
regenerated from this older snapshot over concurrent work; Medius progress and
per-function research notes are recorded separately here.

## Reproduce

The fixed probe source is `dl/TESTS/medius_compiler_probes.c`; the script is
`tools/medius_compiler_probe.py`. Full results, executable SHA-256 fingerprints,
compiler/assembler version output, and source/reference hashes are preserved in
[MEDIUS_COMPILER_RESULTS.json](MEDIUS_COMPILER_RESULTS.json).

Inside the Linux build environment:

```sh
python3 /ProjectRYNO/tools/medius_compiler_probe.py \
  --output /ProjectRYNO/dl/build/medius-compiler-results \
  --shim /opt/ee-gcc2.96/ee296_statshim.so \
  --compiler sony296 /opt/ee-gcc2.96/bin/ee-gcc /opt/ee-gcc2.96/ee/bin/as \
  --compiler ps2dev323 /opt/ps2dev/ee/bin/ee-gcc /opt/ps2dev/ee/bin/ee-as
```

Add `--compiler sony32 PATH/bin/ee-gcc PATH/ee/bin/as` for the archived Sony
3.2 toolchain. Compiler archives are local tools and are not committed. The
working experiment has that toolchain at `/probe/sony32` in the probe container.
After splitting and rebuilding the game, run from `dl`:

```sh
python3 TESTS/check_medius.py ../assets/dl/boot.elf build/boot_elf.elf \
  build/code/medius/rt_util/rt_memory.o
python3 TESTS/check_main_elf.py ../assets/dl/boot.elf build/boot_elf.elf \
  build/code/game/boot.o
python3 ../tools/compare_elf.py ../assets/dl/boot.elf build/boot_elf.elf
```

Ignored experiment artifacts and integration logs are under
`dl/build/medius_compiler_probe/`. The next useful work is to recover the remaining
memory functions and improve the strnlen probe, then test another Medius component
before expanding the compiler rule across the library.

## Type recovery

See [Medius type placement](../types/MEDIUS_TYPES.md) and its 85-header inventory
for dltypes.txt ownership, proposed header locations, and validation requirements.
