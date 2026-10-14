# iksemel XML library

## Current scope (2026-10-14)

**All 40 functions are compiled C and byte-exact (100.00%).** The complete
7,428-byte library range 0x01EE32FC..0x01EE5000 matches retail. All five
compiler-generated jump tables (576 bytes) match at their retail addresses,
and their intervening strings/padding remain unchanged. No `INCLUDE_ASM`
implementation remains. See [measured results](../progress/IKSEMEL.json) and
[function progress](../progress/IKSEMEL.csv).

This applies the SVO3 fix documented in DECISIONS.md D09 and
[SVO3_HANDOFF.md](SVO3_HANDOFF.md#jump-tables-and-padding-2026-10-14-decisionsmd-d09d10).
The previously recovered `switch` bodies replace the four if-chains. The shared
`svo3_rodata_sections.py` helper now also routes `.iks_*` table data, and the
iksemel Makefile rule invokes it before assembling. Five `rodata:` slots use the
existing splitter/linker mechanism; no new linker relaxation or copied retail
table data is involved. All table targets are linked from compiler output.

| Function | Table address | Table bytes |
| --- | --- | ---: |
| escape_size | 0x0019AE40 | 116 |
| escape | 0x0019AEE0 | 116 |
| sax_core | 0x0019AFA0 | 112 |
| iks_escape, size loop | 0x0019B040 | 116 |
| iks_escape, copy loop | 0x0019B0C0 | 116 |

The two `iks_escape` tables require separate sections (`.rodata` and `.rodata.1`)
to preserve the original twelve padding bytes between them. The helper retains
SVO3's existing section routing; regression tests cover this and multiple iksemel
tables. The compiler flags are unchanged.

Validation from base revision `48d9259` plus this change: serial split and forced
full build pass. `check_iksemel.py` has **no nonmatching exemptions** and requires
all 40 compiled definitions, exact code/library bytes, all five exact tables,
and unchanged surrounding read-only data. It passes 45 layout checks, 25 globals,
774 accessor cases, 600 escape cases, and 306 sax_core differential cases.
Section-routing tests, the full placement audit, and the SDK's 20-function exact
comparison also pass. Whole-game strict comparison still reports 13,751 differing
bytes in other registered replacements (5,135 main, 8,616 network); this removes
all 2,083 iksemel differences. Runtime headers match. No gameplay test was run.

Reproduce after `make split`, then a forced build:

```sh
PYTHONPATH=../tools python3 TESTS/check_iksemel.py ../assets/dl/boot.elf build/boot_elf.elf
python3 TESTS/test_rodata_sections.py
```

The following sections preserve the earlier 90% stage and its recovery evidence.

## Earlier scope (2026-10-13)

**All 40 functions are compiled C: 36 byte-exact, 4 nonmatching.** Every byte of the
library range 0x01EE32FC-0x01EE5000 equals retail outside the four nonmatching slots.
Those four dispatch through retail `.rodata` jump tables (see
[Jump-table functions](#jump-table-functions)). No `INCLUDE_ASM` remains.

| Source file | Exact | Nonmatching |
| --- | ---: | --- |
| dom.c | 4/4 | |
| iks.c | 17/19 | `escape_size`, `escape` |
| ikstack.c | 6/6 | |
| sax.c | 7/8 | `sax_core` |
| utility.c | 2/3 | `iks_escape` |

Evidence: retail Ghidra program `/Retail_scus_974.65.elf.moose`
(`DL_Retail_BootELF_974.65.elf`, r5900 little-endian), the split instructions, and the
structure of upstream iksemel (LGPL-2.1, Gurer Ozen). This is an SCE-modified version:
the chunk allocator, the parser's buffer handling in `iks_parse`, `AllocateMoreAttrs`
and the root-tag error in `tagHook` differ from upstream. Every body was checked
against retail instructions, not copied from an upstream release.

## Toolchain: SCE ee-gcc 2.96 (DECISIONS.md K07)

The same C compiled by each candidate, first nine `iks.c` functions:

| Compiler / flags | Byte-exact |
| --- | ---: |
| ps2dev ee-gcc 3.2.3 `-O2` (previous rule) | 1/9 |
| SCE 2.96-ee-001003-1 `-G0 -O2` | 6/9 |
| SCE 2.96-ee-001003-1 `-G0 -Os` | 9/9 |

The fingerprints match SVO3: retained-frame tail calls (`iks_delete`, `iks_dom_new`,
`iks_parse`, `iks_parser_delete`), four `nop`s padding short loops (`iks_next_tag`,
`iks_stack_strecat`), `daddu` moves and `sd` callee saves. The user extended K07 to
iksemel on 2026-10-13.

`code/iksemel/*.c` builds with `ee-gcc -S` and Sony `as`, using the SVO3 flags minus
`-mno-split-addresses` (`IKSEMEL_COMPILE_FLAGS` in the Makefile). That option keeps
each `lui`/`lw` pair together. Retail `iks_stack_new` schedules the `lui` of
`my_malloc_func` at the top and the `lw` after the size clamp. Every other function
matches with or without it.

## Source-shape findings

- One alignment macro reproduces every site: `ALIGN8(x) ((x) + (8 - ((x) & 7)))`. It
  adds a full 8 to aligned sizes. Spelling it `x - (x & 7) + 8` changes
  `iks_stack_strecat`'s argument computation.
- Store order: 2.96 hoists the last store of a run into a free delay slot. Retail
  `iks_parser_reset` stores `uni_len` first, so it is the last statement in source
  (upstream order). `iks_stack_new` likewise needs `len, used, pad_0, last, next`.
- `tagHook` walks attributes with an index (`atts[i]`, `i += 2`). Pointer
  increments swap the callee-saved registers.
- `AllocateMoreAttrs` needs an early `return IKS_OK`. `iks_parse` places the
  existing-buffer path first (`if (prs->stack)`), and updates `stack_pos` before
  computing `diff`.
- `my_strcat`, `escape_size` and `escape` have external linkage, although upstream
  declares them `static`. Retail never calls `escape_size` or `escape`, and 2.96 drops
  unreferenced static functions, which would leave their slots empty.

## Types and globals

`iksemel.h` (private to the library; SVO3 includes only `iks.h`) adds:

- `ikstack` (0x18): chunk header `len, used, pad_0, last, next`, with data at 0x14. `pad_0`
  is only ever set to -1.
- `iksparser` (0x64): upstream `iksparser_struct` plus `token_pos` at 0x2C. That is the
  buffer offset `iks_parse` keeps while a tag is open, compacting with `memmove` and
  rebasing `atts` pointers by the move. Upstream's `tag_name` pointer at 0x28 is
  `int tag_open` here: `sax_core` only stores 1 or 0 into it.
- the hook typedefs, error and tag-type enums, and every library prototype.

The parser API stays out of `iks.h` because `svo3/CConfig.cpp` declares its own
incomplete `struct iksparser` for the same C functions.

Globals (`config/symbols_core.text.txt`, provenance in
[IKSEMEL_GLOBALS.csv](../symbols/IKSEMEL_GLOBALS.csv)): `my_malloc_func` (0x0016AC68)
and `my_free_func` (0x0016AC6C), which are zeroed `core.data` words; the six `tagHook`
error strings at 0x0019AD38-0x0019AE00; and two separate sets of entity strings,
`iksEntity*` (`escape`, 0x0019AEB8-0x0019AED8) and `iksEscape*` (`iks_escape`,
0x0019B010-0x0019B030), plus the sax_core entity names and CDATA brackets
(0x0019AF60-0x0019AF90). No storage is allocated in C.

## Placement

Each file uses `IKS_SECTION` and the slot-preserving `INCLUDE_ASM` from `iksemel.h`.
`config/decompiled_functions.yaml` registers every function slot for dom, ikstack,
sax and utility (iks.c already had slots), and all 40 compiled entry addresses. No
splitter or linker-generator change was needed. No iksemel object emits `.rodata`,
`.data` or `.bss`.

## Jump-table functions

Retail compiles four `switch` statements to jump tables in core.rdata. A compiled
`switch` emits its own copy of the table in the object's `.rodata`, which no iksemel
object can place. This is the same blocker as SVO3 `setPageState`/`handleSpecialKeys`,
pending the rodata/jump-table slot decision.

Following the SVO3 pattern, all four are written as if-chains. The three escape helpers need no
table and fit their original slots, but are **not byte-matching**:

| Function | Address | Compiled / slot | Retail table | Callers |
| --- | --- | --- | --- | --- |
| escape_size | 0x01EE3AE0 | 0x6C / 0x70 | `jtbl_0019AE40` | none in retail |
| escape | 0x01EE3BAC | 0x138 / 0x140 | `jtbl_0019AEE0` | none in retail |
| iks_escape | 0x01EE4DF0 | 0x210 / 0x210 | `jtbl_0019B040`, `jtbl_0019B0C0` | none in retail |

The chains group characters that share an outcome. `escape` selects the entity
string and length first, then makes one `my_strcat` call (like SVO3 `setPageState`'s
single `sprintf`). Because `c` is always one of the five special characters there,
`>` is its final `else`.

`sax_core` (0x01EE4204, `jtbl_0019AFA0`, called by `iks_parse`) is also an if-chain,
**nonmatching**, at 0x898 of its 0x89C slot. A straight translation needs 28 state
compares where retail uses a 9-instruction table dispatch. That is 0x944 bytes, and
the slot has no padding. Three behavior-preserving restructurings bring it inside:

1. The UTF-8 lead-byte check is a loop counting the 1 bits after bit 7, not five
   mask/compare branches. It stores the same `uni_max` and rejects the same bytes. The
   loop's `n > 6` exit is unreachable in practice, because 0xFE/0xFF are rejected first;
   it mirrors retail's final `else`.
2. C_CDATA handles `&` and `<` in one branch with one `cdataHook` flush. `&` still writes
   its NUL before the flush.
3. The six `<![CDATA[` letter states (C_SECT..C_SECT_CDATA_4) share one branch, which
   checks the expected letter and advances to `ctx + 1`.

Every other state is a direct translation of the verified `switch` form, which is
preserved in [IKSEMEL_SAX_CORE.md](IKSEMEL_SAX_CORE.md). Unlike the escape helpers,
`sax_core` runs in-game, for SVO3 page and configuration parsing.

Before the if-chain rewrite, each function's `switch` version was verified with the
probe (2026-10-13). With only the jump-table address fields masked, every instruction
equals retail (escape_size, escape, iks_escape, and sax_core's 551). The if-chains are
rewrites of that verified logic; sax_core's differs from it only in the three
restructurings above. Once rodata slots exist, the switch versions
below and in IKSEMEL_SAX_CORE.md become byte-exact replacements.

Retail iks.c rodata is contiguous from 0x0019AE40: the `escape_size` table, the five
entity strings, then the `escape` table. A single placement of iks.o's `.rodata`
may therefore suffice, if string literals replace the externs. This is untested.

Retail `escape_size` adds 4 for `&`, 5 for quotes and 3 for `<`/`>`, one less than
each entity's length. Unlike upstream, it under-counts. The if-chain keeps this.

```c
unsigned int escape_size(char *src, unsigned int len)
{
    unsigned int sz;
    char c;
    unsigned int i;

    sz = 0;
    for (i = 0; i < len; i++) {
        c = src[i];
        switch (c) {
            case '&': sz += 4; break;
            case '\'': sz += 5; break;
            case '"': sz += 5; break;
            case '<': sz += 3; break;
            case '>': sz += 3; break;
            default: sz++; break;
        }
    }
    return sz;
}

char *escape(char *dest, char *src, unsigned int len)
{
    char c;
    unsigned int i;
    unsigned int j = 0;

    for (i = 0; i < len; i++) {
        c = src[i];
        if ('&' == c || '<' == c || '>' == c || '\'' == c || '"' == c) {
            if (i - j > 0) dest = my_strcat(dest, src + j, i - j);
            j = i + 1;
            switch (c) {
                case '&': dest = my_strcat(dest, (char *)iksEntityAmp, 5); break;
                case '\'': dest = my_strcat(dest, (char *)iksEntityApos, 6); break;
                case '"': dest = my_strcat(dest, (char *)iksEntityQuot, 6); break;
                case '<': dest = my_strcat(dest, (char *)iksEntityLt, 4); break;
                case '>': dest = my_strcat(dest, (char *)iksEntityGt, 4); break;
            }
        }
    }
    if (i - j > 0) dest = my_strcat(dest, src + j, i - j);
    return dest;
}

char *iks_escape(ikstack *s, char *src, unsigned int len)
{
    char *ret;
    unsigned int i, j, nlen;

    if (!src || !s) return 0;
    if (len == -1) len = strlen(src);

    nlen = len;
    for (i = 0; i < len; i++) {
        switch (src[i]) {
            case '&': nlen += 4; break;
            case '<': nlen += 3; break;
            case '>': nlen += 3; break;
            case '\'': nlen += 5; break;
            case '"': nlen += 5; break;
        }
    }
    if (len == nlen) return src;

    ret = iks_stack_alloc(s, nlen + 1);
    if (!ret) return 0;

    for (i = j = 0; i < len; i++) {
        switch (src[i]) {
            case '&': memcpy(&ret[j], iksEscapeAmp, 5); j += 5; break;
            case '\'': memcpy(&ret[j], iksEscapeApos, 6); j += 6; break;
            case '"': memcpy(&ret[j], iksEscapeQuot, 6); j += 6; break;
            case '<': memcpy(&ret[j], iksEscapeLt, 4); j += 4; break;
            case '>': memcpy(&ret[j], iksEscapeGt, 4); j += 4; break;
            default: ret[j++] = src[i];
        }
    }
    ret[j] = '\0';

    return ret;
}
```

## Validation (2026-10-13)

Serial `make split`, then `make -B -j8 elf`, then `python3 ../tools/verify.py dl`:
exit 0. The report is in `build/iksemel-work/verification3`.

- `check_iksemel.py`: PASS. It covers:
  - 45 layout checks (iks, ikstack, iksparser);
  - library bytes equal to retail outside the 4 nonmatching slots;
  - 40 compiled functions at their slots (36 at exactly the retail size, 4 within it);
  - 25 globals and 774 accessor differential cases.
- 600 escape cases run retail and rebuilt `escape_size`, `escape` and `iks_escape` in the
  interpreter, with `strlen`, `memcpy` and `iks_stack_alloc` stubbed. Inputs are random
  strings of special and other bytes, plus null arguments, `len == -1` and allocation
  failure. The cases compare return values, calls and every byte written.
- 306 sax_core cases run retail and rebuilt on the same XML:
  - Stubs: malloc, free, memset, memcpy and strcmp, plus a tag hook and a cdata hook.
  - Inputs: tags, attributes, entities, comments, CDATA, PIs, UTF-8, malformed XML,
    input split into chunks, hooks that fail or are absent, and failing allocations.
    Six fixed cases cover growth of the attribute array and repeated whitespace.
  - Compared: per-call return values, every stub and hook call with its arguments and
    strings, and every byte written to the parser, buffer and heap.
  - Coverage: 26 of 28 states are the final state of some run; the other two are
    passed through. All four return codes occur.
- Mutation sweep (`build/iksemel-work/mutate.py`): each of the 131 `addiu rt, zero, imm`
  constants in the rebuilt sax_core was incremented in turn. The cases detect 122. The
  9 survivors cannot change observable behavior:
  - five changes to the `re` flag, which is only tested for zero;
  - the 0xFE and 0xFF early rejects, which the UTF-8 loop also rejects with the same
    result;
  - the UTF-8 loop's unreachable `n > 6` exit;
  - a C_TAG `>` state detour that ends in the same state.
- The escape cases detect a mutated `escape_size`. The shared interpreter gained
  LWL/LWR/SWL/SWR for the inlined entity copies.
- Slot audit (61,735 changed bytes, all in registered slots), global addresses, type
  layouts (1,937 checks, 213 types), sound and SVO3 suites, and the tracker: PASS.
- `compare_elf.py`: NONMATCH.
  - core.text: unchanged at 5,130 bytes.
  - net.text: 56,605 bytes. The 2,083 new bytes are all inside the four nonmatching slots.
- Progress: 7,589 assembly, 1,036 compiled, 645 matching and 391 nonmatching slots.
- NOT RUN: ISO packing, emulator or gameplay. `sax_core` runs in-game for SVO3 parsing;
  its runtime behavior rests on the differential cases, not an emulator test.

The probe harness (`build/iksemel-work/probe.py`, ignored) compiles a C file and
compares each function with retail, masking only relocated fields.
