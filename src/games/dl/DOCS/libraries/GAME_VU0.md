# Game VU0 and MMI functions

This page tracks the root `code/game` functions that use VU0 macro-mode or 128-bit MMI instructions,
under decision D20 in [DECISIONS.md](../../../../../docs/decompilation/DECISIONS.md).

> **To revisit later.** The inline asm in the functions listed below stands in for the original
> `mathfunc_inline.h`-style helpers. We can try to replace it with C at a later date, once those helpers
> are reconstructed or an intrinsic form is found that compiles to the same bytes. When a function no longer
> needs asm, move it to the "Plain C" table.

## How these functions are written

- **Compiler support.** Game code is built with `-mvu0-use-vf0-vf31`, set in `GAME_COMPILE_FLAGS` and as
  `game_test.py`'s default. SN GCC then:
  - allocates VU0 registers for `uint128` values passed with the `j` constraint;
  - emits `lqc2`, `sqc2`, `qmtc2` and `qmfc2`;
  - fills their delay slots, as retail does.

  Adding the flag left every existing match unchanged (726 changed bytes).
- **Plain C first.**
  - `uint128` (from `code/include/game_vu0.h`) is a 128-bit scalar, and retail's `vec4` is
    `struct vec4 { uint128 m_v; }`. Copies of either compile to `lq`/`sq`.
  - A function that returns a vector in `$2` returns `uint128`, not a struct.
  - Many functions that `vu_list.py` reports as "MMI" are only `vec4` copies and need no asm.
- **Asm only for the operation.**
  - Write VU0 operations (`vadd`, `vmul*`, `vmadd*`, `vcallms`, ...) with `VU0_ASM`, and MMI operations
    (`p*`, `qfsrv`, ...) with `MMI_ASM`.
  - Use `j` operands. The only hard-coded registers allowed are `vf0`, `ACC`, `I` and `Q`.
  - Retail interleaves loads between VU operations, which shows that each operation was its own statement.
    The compiler places the `lqc2` loads at their first use.
- **Not converted:** hand-written assembly, meaning split asm marked `handwritten` and modules outside
  `GAME_SN_NAMES` such as `fastfunc`, `shadowproc`, `mathfunc_asm`, `collproc` and `skyproc`. It stays
  `INCLUDE_ASM`.
- **Listing candidates:** `python build/game-work/vu_list.py [MAXSIZE]` (from the dl directory) lists the
  remaining root functions that use VU0/MMI instructions, with their size and the share of VU/MMI
  instructions.
- **Comparing:** `game_test.py` reads the VU0 instructions that splat left as `.byte` lines, so the compare
  stays aligned.

## Converted with inline asm (revisit)

| Function | Module | Kind | Notes |
|---|---|---|---|

## Plain C (no asm needed)

These functions were listed as VU0/MMI candidates but match as ordinary C using `uint128`/`vec4`.

| Function | Module | Notes |
|---|---|---|
| `NAVG_SetTargetWp` | navsysglobal | `vec4` copy (`lq`/`sq`) |
| `NAVG_WpSet` | navsysglobal | `vec4` copy through a stack temporary, node handle in the w word |
