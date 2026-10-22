# Deadlocked Medius library

## Pinned for later

These real functions are set aside and stay as retained assembly (`INCLUDE_ASM`), so
every module is still byte-identical to retail. Numbers are differing words against
retail for the best candidate so far. Pick them up from here; the shapes already tried
are in the linked notes. One-instruction padding fragments (`func_XXXXXXXX`) are not
real functions and are not listed.

| Module | Function | Best | Blocker / notes |
| --- | --- | --- | --- |
| rt_circ_buf | free, use, store, copy, normalize_with_buf, get_avail_nowrap, get_start_used_ptr, get_start_avail_ptr, is_wrapped | 2 to 28 | v0-compare pattern ([MEDIUS_OPEN_PATTERN.md](MEDIUS_OPEN_PATTERN.md)); try the positive-test shape that solved `rt_token_start` |
| rt_pack | rt_pack_cstring | 13 | register allocation in the rollback tail (batch 3) |
| rt_timebase | rt_timebase_update_globaltime | 1 | retail copies `roundTrip` (`move v1,a0`) (batch 4) |
| rt_list_buf | pool_alloc, pool_free | ~58, 13 | scan-loop peeling; `mflo` scheduled before the branch (batch 5) |
| rt_time | delay | 12 | v0-compare pattern |
| rt_time | timestamp_to_msecs, timestamp_to_usecs | 26, 13 | result kept in `v0` across the arithmetic (batch 6) |
| rt_time | calc_diff | 47 | first draft only, not worked on |
| ps2/rt_time_platform | get_date_time | 1 | `bnez` vs `bnezl` delay slot (batch 7) |
| ps2/rt_time_platform | update_base | 31 | empty delay slot after the unsigned-to-float conversion (batch 7) |
| ps2/rt_time_platform | timer_getcount | - | COP0 `mfc0 Count`; inline asm, keep as assembly unless asm-in-C is wanted |
| rt_token | create_table, release_ownership, grant_ownership, update_ownership | 8, 22, 31, 51 | v0-compare pattern; positive-test shape helps only partly |
| rt_token | list_check/grant/release/update_ownership, build_token_list_msg | - | not attempted |
| ps2/rt_mtrandgen_platform | ScrambleSeed, setNewSeed_platform | - | not attempted: COP0 Count/Random inline asm, RCNT hardware counters |

PS2 declarations: Medius objects compile with the open-source PS2SDK headers
(`PS2SDK_FLAGS` in the Makefile: `-D_EE`, `/opt/ps2dev/ps2sdk/{ee,common}/include`, plus the
ps2dev gcc include directory for `stddef.h`/`stdarg.h`, which the 2.96 package lacks).
Use them for EE kernel and libcdvd calls (`kernel.h`: `ee_sema_t`, `CreateSema`,
`GetThreadId`; `libcdvd-common.h`: `sceCdCLOCK`). Sony SDK calls that PS2SDK lacks
(`sceDevctl`, `sceScfGetLocalTimefromRTC`) are declared in `code/sdk/sce_missing.h`.
Add new ones there rather than in individual files.

## rt_util batch 7 (2026-10-22)

**94 Medius functions now compile to exact retail bytes** (69 after batch 6). Four new
modules are byte-identical to retail including retained assembly. All shapes started
from Ghidra's debug-info decompile.

Medius inventory: 94 of 1,462 INCLUDE_ASM entries replaced (6.43%).

| Module | Compiled (exact) | Retained assembly |
| --- | --- | --- |
| `rt_mtrandgen.c` | seedMT, seedMTUsingArray, reloadMT, randomMT, setNewSeed | fragment `func_01EA9BC0` |
| `ps2/rt_mutex_platform.c` | create, destroy, lock, unlock, get_thread_id | fragment `func_01EAA058` |
| `ps2/rt_time_platform.c` | get_time_stamp, update_date_time, get_gmtime, fast_elapsed_msecs, init | get_date_time, timer_getcount (COP0 `mfc0 Count`), update_base; fragment `func_01EABA68` |
| `rt_token.c` | start, shutdown, is_valid, free_owner, check_ownership, expand_table, destroy_table, add_ownership, remove_ownership, build_token_msg | grant/release/update_ownership, the four `list_*` functions, create_table, build_token_list_msg; fragments `func_01EABFE0`, `func_01EACE98` |

Not attempted: `ps2/rt_mtrandgen_platform.c` (`ScrambleSeed` reads COP0 Count/Random
with inline asm; `setNewSeed_platform` reads the RCNT hardware counters).

Types and globals:

- `rt_mtrandgen` is Shawn Cokus's `cokus.c` Mersenne Twister with an index instead of a
  pointer and a Medius output mixer. `RT_MT {state[625], left}` sits at `gMT`
  (0x001681B0, debug-info label). The mixer words are `rtMtMixA` (0x00168B78) and
  `rtMtMixB` (0x00168B7C), plus `mediusMtLastOutput` (0x00168B80, named `y` in the debug
  information; renamed so a one-letter global cannot clash in the whole-game link).
- `rt_mutex.h` now uses the debug-info `RT_MUTEX_DATA {bInitialized, nLockCount,
  ThreadID, PlatformVal, pPlatformData}` (0x14), replacing the batch 2 `RT_MUTEX`
  guess. `rt_mutex.c` still matches. RT_MUTEX_ERROR is 900. The kernel calls
  come from PS2SDK's `kernel.h` (`ee_sema_t` has the same layout as Sony's `SemaParam`);
  see "PS2 declarations" under "Pinned for later".
- `rt_time.h` gains the debug-info `RT_TIME_DATE` (0x24) and `RT_TIME_PLATFORM_BASE
  {Secs, Ticks, USecs, LastCount}`, a COP0 Count time base at 294,912,000 ticks per
  second. New globals: `rtTimePlatformInitialized` (0x00168BA1), `rtTimePlatformBase`
  (0x001B23E8), `rtTimePlatformDate` (0x001B23F8) and `rtTimeCdromDevice`
  (0x001965C8, `"cdrom0:"`). The string stays in retail rodata and the C code
  references it by symbol.
- `rt_token.h` has the debug-info `RT_TOKEN_SYSTEM_INFO {num_tokens, max_tokens,
  p_token_info_array}` and `RT_TOKEN_DATA {ownerID, state}`, plus RT_TOKEN_* results
  (56001..56007).
- All new globals are in MEDIUS_GLOBALS.csv and checked by `check_medius.py`.

Source-shape findings:

- **Prototypes matter for register choice.** `rt_token_build_token_msg` was 1 word off
  until `rt_msg_set_u2byte` was declared `int` (its real return type) instead of `void`.
- The store-order rotation rule held again: `SemaParam.maxCount` before `initCount`,
  `RT_TIME_DATE` copy-out with `MSecsWhenAquired` last, `destroy_table` clearing
  `p_token_info_array, max_tokens, num_tokens`, and the `rtMtMixB`/`rtMtMixA` updates.
- `rt_token_remove_ownership` indexes `pTokenSystem->p_token_info_array[tokenID]` in
  place for every access. A local `RT_TOKEN_DATA *` (via `&array[tokenID]`,
  `array + tokenID`, a `char *` offset, an `int` index or a copied base pointer)
  swaps the `addu` operands; only hand-written `(tokenID << 2) + base` arithmetic also
  matches.
- `rt_token_is_valid` is `if (tokenID >= 0xFFFF) return 0; return 1;` (`sltiu`, not `xori`).
- `rt_token_create_table` rounds with `tokenCount / 16 * 16 + 16` (srl/sll).

Open shapes:

- `rt_time_platform_get_date_time`: 1 word. Retail fills the first-time check's delay
  slot with a plain `bnez`, and we get `bnezl`. Tried `== 0`, a result variable,
  `!= 0` and braces.
- `rt_time_platform_update_base` (31 words): the unsigned-to-float conversion leaves
  retail's `b` delay slot empty, and ours fills it with `cvt.s.w`. Tried a float
  temporary, implicit and explicit casts, and the constant as `1e6 / ticks`.
- `create_table` (5), `release_ownership` (22), `grant_ownership` (31) and
  `update_ownership` (51) are the rt_circ_buf v0-compare pattern (MEDIUS_OPEN_PATTERN.md).
  `rt_token_start` matched with a positive test and the failure return last; the same
  shape does not finish the others. Declaring the result as an `RT_RESULT` enum does not
  change it.

## rt_util batch 6 (2026-10-20)

**69 Medius functions now compile to exact retail bytes** (58 after batch 5).
`rt_time.c` (0x01EAB210..0x01EAB6A8) is byte-identical to retail including retained
assembly, with 11 of its 15 real functions compiled. Shapes were taken from Ghidra's
debug-info decompile (see batch 5).

Medius inventory: 69 of 1,462 INCLUDE_ASM entries replaced (4.72%).

| Compiled (exact) | Retained assembly |
| --- | --- |
| get_local, get_msecs, start, get_time_stamp, elapsed, elapsed_msecs, elapsed_usecs, initialize, get_base_diff, elapsed_timestamp, get_gmtime | delay, calc_diff, timestamp_to_msecs, timestamp_to_usecs; fragments `func_01EAB2B8`, `func_01EAB418`, `func_01EAB670` |

New globals (in MEDIUS_GLOBALS.csv, checked by `check_medius.py`): `rtTimeInitialized`
(0x00168BA0, byte) and `rtTimeBaseStamp` (0x001B23E0, RT_TIME_STAMP). `rt_time.h` now
declares the module and RT_TIME_ERROR (1600) / RT_TIME_OVERFLOW (1601).

Source-shape findings:

- `elapsed_msecs`, `elapsed_usecs`, `get_base_diff` and `elapsed_timestamp` use one
  `result` preset to RT_INVALID_PARAM with nested `if`s (`if (result == 0) result = ...`).
  `get_msecs` uses early returns instead. `get_base_diff` tests
  `if (rtTimeInitialized || (result = rt_time_initialize()) == 0)`.
- `initialize` returns RT_TIME_ERROR early when already initialised.

Open shapes:

- `delay` (12 words) is the rt_circ_buf v0-compare pattern (MEDIUS_OPEN_PATTERN.md):
  retail keeps the result in `v0`, loads `elapsed` into `v0` for the compare, and
  returns a separate `0` on normal exit.
- `timestamp_to_msecs` (26) and `timestamp_to_usecs` (13) keep the result in `v0`
  across the arithmetic; `msecs` divides `USecs` unsigned (Ghidra's `(int)` cast is
  wrong). `calc_diff` (47) has not been worked on yet.

## rt_util batch 5 (2026-10-20)

**58 Medius functions now compile to exact retail bytes** (46 after batch 4). The branch
was rebased onto `origin/master` d1808b7 (SDK DMA/multitap, SVO3 98.1%) before this batch.
`rt_list_buf.c` (0x01EB5FB0..0x01EB6914) is byte-identical to retail including retained
assembly, with 12 of its 14 functions compiled.

Medius inventory: 58 of 1,462 INCLUDE_ASM entries replaced (3.97%).

| Compiled (exact) | Retained assembly |
| --- | --- |
| create_pool, destroy_pool, get_pool_used, create, destroy, clear, insert, set_new_head, remove, append_data, get_tail, resize_buffer | pool_alloc, pool_free |

**The retail ELF carries debug information for Medius.** Ghidra's program
`Retail_scus_974.65.elf.moose` has the original source path
(`/public/work/210/rt_util/rt_list_buf.c`), struct and field names, parameter names and
return types (`RT_RESULT`, and `void` for `destroy`/`clear`). Use it for every Medius
module. The bridge's dynamic tools may not reach the client; the GUI's HTTP API answers
directly, for example
`curl "http://127.0.0.1:8089/force_decompile?program=Retail_scus_974.65.elf.moose&function=0x01eb6788"`
and `/get_struct_layout?program=...&struct_name=RT_LIST_BUF`.

`rt_list_buf.h` uses those names (all in RECOVERED_TYPES.json):
`RT_LIST_BUF_POOL {nBufRefCnt, nBufSize, nBlkSize, nBlks, pBuf, pTbl}` (0x18),
`RT_LIST_BUF {nBufSize, nBufUsed, pBuf (the pool), pHead}` (0x10),
`RT_LIST_NODE {nDataSize, next}` (8-byte header, payload follows) and the scatter
descriptor `RT_DATA_VECTOR {aData[8] RT_DATA_INFO {pData, nSize}, nTotalSize, nLength}`
(0x48). RT_LIST_BUF_ERROR (300) is "node not in list" and RT_LIST_BUF_FULL (301) is "no
room or no pool blocks". The pool is a block allocator: `pTbl` holds one byte per block
after the block data, and the first block of a run stores `0x80 | runLength`.

Source-shape findings:

- **Allocation pointer reused as cursor.** `insert` keeps the `pool_alloc` result in
  one `unsigned char *` and copies it to the node pointer before advancing it past the
  header (`move s3,s2`). Using a typed node pointer from the start loses that move.
- `create_pool` writes the block count straight into `pBufPool->nBlks` and adjusts it
  in place (`pBufPool->nBlks -= (pBufPool->nBlks - nPoolSize % nBlockSize) / nBlockSize`). With
  locals, the store moves into the branch delay slot.
- `get_tail` keeps one result variable, preset to NULL, behind a combined guard.
- Retail product order is `count * nBlkSize` and `nBlks * nBlkSize`.
- **Duplicated tails are cross-jumped.** `remove` and `append_data` repeat the
  `pool_free`/update/`return 0` tail in the head branch and inside the search loop; 2.96
  merges them into one call. Writing a single shared tail (break or goto) loads the pool
  argument after the stores and costs 9 words. `append_data` also compares
  `*ppListNode == pPrev->next` in that operand order.
- The four `nop`s inside the `get_tail` and `remove` loops are R5900 short-loop padding
  from Sony `as`, not source.

Open shapes:

- `pool_free` (13 words): retail schedules `mflo` (quotient) before the remainder
  `bnez` and leaves the delay slot empty. Every tried shape puts `mflo` in the delay
  slot: early return, nested `if`, separate remainder variable, signed/char types,
  integer pointer casts.
- `pool_alloc` (about 60 words): retail peels the first scan iteration behind a
  `blez nBlks` guard and hoists `pTbl`. `0x80 | i` and `found * nBlkSize` are
  settled; `for`, `while`, `continue` and ternary scan loops all keep the jump-to-body
  form.
  Ghidra shows a byte-sized mark counter, and the scan index reused as the run end;
  neither closes the gap.

## rt_util batch 4 (2026-10-19)

**46 Medius functions now compile to exact retail bytes** (37 after batch 3). The branch
was fast-forwarded onto `origin/master` 437dd3a (989snd, newlib/libm and SVO3 progress)
before this batch. This batch adds two modules, both byte-identical to retail including
retained assembly:

- `rt_circ_buf.c`: 7 of its 16 real functions (0x01EA6C60..0x01EA7408).
- `rt_ip.c`: both functions (0x01EA9140..0x01EA926C). `rt_ip_string2ip` parses a
  dotted quad into `(ip >> 8) + (octet << 24)` per octet, ignoring non-digits; the
  first octet ends up in the low byte. `rt_ip_ip2string` reverses it. An octet of 100
  or more always prints its tens digit, which retail shares with the 10..99 path. In C
  that is a `goto` into the tens branch. Octet times ten is written
  `octet <<= 1; octet += octet << 2; octet += c - '0';` to match retail's add order.

Medius inventory: 46 of 1,462 INCLUDE_ASM entries replaced (3.15%).

| Compiled (exact) | Retained assembly |
| --- | --- |
| create, destroy, clear, normalize, get_used, get_used_nowrap, get_avail | free, use, store, copy, normalize_with_buf, get_avail_nowrap, get_start_used_ptr, get_start_avail_ptr, is_wrapped; `func_01EA73F8` (fragment) |

`rt_circ_buf.h` has the prototype `RT_CIRC_BUF {nStartPos, nEndPos, nSize, nUsed, pBuf,
pScratchBuf}` (0x18; in RECOVERED_TYPES.json), RT_CIRC_BUF_ERROR (200) and
RT_CIRC_BUF_NO_SCRATCH_BUF (201). `rt_circ_buf_copy` takes a third `size` argument:
`normalize_with_buf` passes `used` in a2.

Source-shape findings:

- **Zero-store rotation.** When a run of fields is set to 0, 2.96 emits the last store
  first. Retail `clear` stores nUsed, nStartPos, nEndPos, so the source order is
  `nStartPos, nEndPos, nUsed`. `destroy` and `create` follow the same rule.
- `get_used_nowrap` tests `if (buffer->nUsed)` positively. `normalize` returns
  RT_CIRC_BUF_NO_SCRATCH_BUF when forced without a scratch buffer, otherwise it
  tail-calls `normalize_with_buf`.

Open shapes: seven of the nine retained functions share one unsolved compiler pattern.
Retail compares a getter's out-value in `v0` and keeps `if (result) return result;
return 0;` unfolded. Retail evidence, every tried shape, untried ideas and the best
candidates (`store` is down to 2 words) are in
[MEDIUS_OPEN_PATTERN.md](MEDIUS_OPEN_PATTERN.md).

Build note: `origin/master` added `tools/drop_unused_rodata.py` (newlib/libm), which
imports pyelftools without a pin in `src/games/requirements.txt`, so a fresh image
failed `make elf`. This batch adds `pyelftools==0.33` (the version verified). Rebuild
the image (`docker compose build projectryno`) to pick it up.

Next: `rt_mtrandgen.c` is Shawn Cokus's Mersenne Twister (`seedMT` with 69069,
`reloadMT`, `randomMT`), modified by SCE. It uses an index at state+0x9C4 instead of
`left`/`next`, and a custom tempering that rotates by 7/25 and XORs three extra words
(0x00168B78..0x00168B80). Its statics (state at 0x001681B0) need names first, as for
rt_timebase. `func_01EA9BC0` is another 4-byte fragment.

Validation: serial split, forced build, `verify.py dl --split` exit 0. Every suite
passes, including upstream's libm and sound exact checks. `check_medius.py` reports
all 46 functions exact and all nine modules byte-identical. The placement audit
reports 2,172 changed bytes project-wide, all in registered slots. Snapshot: 7,462
assembly, 1,139 compiled, 1,109 matching and 30 nonmatching slots.

```sh
O=build/code/medius/rt_util
python3 TESTS/check_medius.py ../assets/dl/boot.elf build/boot_elf.elf $O/rt_memory.o \
  $O/rt_constraint.o $O/rt_string.o $O/rt_mutex.o $O/rt_pack.o $O/rt_msg_util.o \
  $O/rt_timebase.o $O/rt_circ_buf.o $O/rt_ip.o
```


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
