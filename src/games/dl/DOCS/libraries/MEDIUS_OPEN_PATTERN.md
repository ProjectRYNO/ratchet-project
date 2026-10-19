# Medius open pattern: getter result compared in v0 (2026-10-19)

Status: **unsolved.** Nine `rt_circ_buf.c` functions stay in assembly because of it.
The module still matches retail byte-for-byte through retained assembly; see
[MEDIUS.md](MEDIUS.md).

| Function | Address | Best candidate | Remaining difference |
| --- | --- | --- | --- |
| rt_circ_buf_store | 0x01EA6EC0 | below | 2 words: compare register only |
| rt_circ_buf_free | 0x01EA6D70 | below | 25 words, 8 bytes short |
| rt_circ_buf_use | 0x01EA6E18 | `free` with `nEndPos`/`get_avail`/`+=` | same as free |
| rt_circ_buf_normalize_with_buf | 0x01EA70F8 | MEDIUS.md batch 4 | shared `return 0` block |
| rt_circ_buf_get_start_used_ptr | 0x01EA72C8 | below | 8 words |
| rt_circ_buf_get_start_avail_ptr | 0x01EA7338 | `used` → `avail`, `nStartPos` → `nEndPos` | 8 words |
| rt_circ_buf_copy | 0x01EA6FD0 | MEDIUS.md batch 4 | 28 words, 4 bytes long |
| rt_circ_buf_get_avail_nowrap | 0x01EA7278 | MEDIUS.md batch 4 | 6 words |
| rt_circ_buf_is_wrapped | 0x01EA73A8 | MEDIUS.md batch 4 | 16 words |

Toolchain and flags as for every Medius object: SCE ee-gcc 2.96 with
`MEDIUS_COMPILE_FLAGS` (`-G0 -O2 -fno-builtin -fno-common -ffunction-sections`). The
last two rows look like separate issues; the first seven share the pattern.

## The pattern

Each affected function calls `rt_circ_buf_get_used`/`get_avail` with a stack local,
checks the returned result, then compares the local. Retail, `rt_circ_buf_free`:

```text
jal   rt_circ_buf_get_used        ; a1 = &used (sp+0)
bnel  v0, zero, exit              ; if (result) return result
ld    s0, 0x10(sp)
lw    v0, 0x0(sp)                 ; <- used loaded into v0
sltu  v0, v0, s1                  ; <- compare in v0
bnez  v0, exit
li    v0, 200                     ;    RT_CIRC_BUF_ERROR in the delay slot
...
jal   rt_circ_buf_normalize
bnez  v0, exit2                   ; if (result) return result
ld    s0, 0x10(sp)
move  v0, zero                    ; return 0, not folded into "return result"
```

Two traits:

1. **The getter's out-value is loaded and compared in `v0`.** Every candidate so far
   uses `v1`. In `store`, this is the only remaining difference.
2. **A result check followed by an explicit `return 0` survives.**
   `result = f(); if (result) return result; return 0;` is folded by 2.96 into
   `return result` (or a tail call). Retail keeps the `bnez v0` / `move v0, zero` pair.
   In `normalize_with_buf`, the `move v0, zero` block is shared with an earlier
   `return 0` (`if (!nStartPos) return 0;`).

Retail `free`/`use` also store the new position from a conditional chosen with
branches (`beql`), and reload `nUsed` after that store. 2.96 turns the candidates into
`movz` and hoists the load. This may be a side effect of the same idiom.

Both traits suggest a common source construct that has not been identified. Likely
candidates: a status macro (for example `RT_CHECK(x)` assigning a result and
returning), a single `result` variable carried to one shared exit, or the out-value
read through a helper or macro. The prototype `dltypes.txt` has `RT_RESULT` with
`RT_RESULT_OK = 0`; result variables may be that enum type.

## Tried without success

- `if (result) return result;` / `if (result != 0)` / `if ((result = f()) != 0)` /
  `if (result != 0) return result; else return 0;`.
- Comparison spelled `used < size` and `size > used`. In `store`, `size > avail` plus
  storing `nUsed` before `nEndPos` gives the 2-word candidate.
- `free`/`use` position update as `if/else` stores, `?:`, a `tail` temporary, or
  through `unsigned int *position = &buffer->nStartPos`.
- Pointer getters: `if (!used) return ...` (8 words), `if (used) {...}` (14),
  `result = RT_CIRC_BUF_ERROR` / `result = 0` single exit (16), and `&buffer->pBuf[pos]`.
- `if (!size) return 0` vs `if (size == 0) return 0` (no effect).

Untried ideas for the next session:

- Declare `result` as an `RT_RESULT` enum, and/or initialise it
  (`RT_RESULT result = RT_RESULT_OK;`).
- One function-wide `result` with a single `return result;` at a label, reached by
  `goto` from each failure (the shared-exit shape seen in `normalize_with_buf`).
- A macro that assigns and tests in one expression, for example
  `#define RT_RETURN_IF_ERR(x) if ((result = (x)) != RT_RESULT_OK) return result`.
- Volatile or `register` locals; or `-O2` variants such as `-fno-schedule-insns2`
  per object. Flags must stay consistent across the matched rt_util objects.
- The SVO3 notes record similar delay-slot and register findings for 2.96;
  SVO3_HANDOFF.md may hint at the house style.

## Best candidates

`rt_circ_buf_store` (2 words: only `v1` → `v0` for `avail`):

```c
int rt_circ_buf_store(RT_CIRC_BUF *buffer, unsigned char *source, unsigned int size)
{
    int result;
    unsigned int avail = 0;
    unsigned int tail;

    if (!buffer) return RT_INVALID_PARAM;
    if (!source) return RT_INVALID_PARAM;
    if (!size) return RT_INVALID_PARAM;
    result = rt_circ_buf_get_avail(buffer, &avail);
    if (result != 0) return result;
    if (size > avail) return RT_CIRC_BUF_ERROR;
    tail = buffer->nSize - buffer->nEndPos;
    if (tail >= size) {
        memcpy(buffer->pBuf + buffer->nEndPos, source, size);
        buffer->nUsed += size;
        buffer->nEndPos += size;
        if (buffer->nEndPos == buffer->nSize) buffer->nEndPos = 0;
    } else {
        memcpy(buffer->pBuf + buffer->nEndPos, source, tail);
        size -= tail;
        buffer->nUsed += tail;
        memcpy(buffer->pBuf, source + tail, size);
        buffer->nUsed += size;
        buffer->nEndPos = size;
    }
    return 0;
}
```

`rt_circ_buf_free` (25 words; `use` is identical with `nEndPos`, `get_avail` and `+=`):

```c
int rt_circ_buf_free(RT_CIRC_BUF *buffer, unsigned int size)
{
    int result;
    unsigned int used = 0;
    unsigned int tail;

    if (!buffer) return RT_INVALID_PARAM;
    if (!size) return 0;
    result = rt_circ_buf_get_used(buffer, &used);
    if (result) return result;
    if (used < size) return RT_CIRC_BUF_ERROR;
    tail = buffer->nSize - buffer->nStartPos;
    if (size < tail)
        buffer->nStartPos += size;
    else
        buffer->nStartPos = size - tail;
    buffer->nUsed -= size;
    result = rt_circ_buf_normalize(buffer, 0);
    if (result) return result;
    return 0;
}
```

`rt_circ_buf_get_start_used_ptr` (8 words; retail falls through to the store and
branches to the exit for `!used` with 200 in the delay slot):

```c
int rt_circ_buf_get_start_used_ptr(RT_CIRC_BUF *buffer, unsigned char **pointer)
{
    int result;
    unsigned int used = 0;

    if (!buffer) return RT_INVALID_PARAM;
    if (!pointer) return RT_INVALID_PARAM;
    result = rt_circ_buf_get_used(buffer, &used);
    if (result) return result;
    if (!used) return RT_CIRC_BUF_ERROR;
    *pointer = buffer->pBuf + buffer->nStartPos;
    return 0;
}
```

## How to test a candidate

Put the function in a scratch file with `#include "../../code/medius/rt_util/rt_circ_buf.h"`
and run the relocation-masking probe from `/ProjectRYNO/dl`:

```sh
python3 build/medius-work/probe.py FILE.c --show rt_circ_buf_store \
  --flags "-G0 -O2 -fno-builtin -fno-common -ffunction-sections"
```

`probe.py` is ignored build tooling (a copy of `build/iksemel-work/probe.py`). It masks
HI16/LO16 fields, so a probe MATCH must still be confirmed after integration with
`TESTS/check_medius.py` against the linked ELF (see MEDIUS.md batch 3).
Once one function matches, move it from INCLUDE_ASM into `rt_circ_buf.c`, register it
in `decompiled_functions.yaml` (`functions:`), add it to `check_medius.py`, then run
split, a forced build and `verify.py`.
