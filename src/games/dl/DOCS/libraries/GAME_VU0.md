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
- **Moving a float or int into a VU register.** Retail's `mfc1 $3, $f12` / `daddu $2, $3, $0` / `qmtc2 $2, $vfN`
  comes from a sign-extended `long` copy fed to a non-volatile `qmtc2` asm:

  ```c
  long bits = *(int *)&alpha;
  __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"(bits));
  ```

  Each of these forms fails:
  - a `float` or `int` `j` operand crashes the compiler;
  - a union goes through the stack;
  - an `(unsigned)` cast adds `dsll32`/`dsrl32`.
- **Volatile or not.** VU operations that have outputs can be plain `__asm__` with in-place `+j` operands,
  which lets the scheduler interleave the `qmtc2`/`lqc2` moves like retail. Statements without outputs
  (`vmula*` into `ACC`, `vcallms`) are volatile by nature and act as barriers.
- **Pinning a VU register (last resort).** When the instructions and their order match but GCC picks
  different `vf` registers, bind the variable to the retail register:

  ```c
  register uint128 a __asm__("vf2") = v0;
  ```

  Spell it `vfN`, without the `$`. This took `Lerp___dupe3` from 7 differing words to 2.
- **A float result from a VU register.** Write `VU0_OP("qmfc2.ni %0, %1" : "=r"(f) : "j"(v));` with a
  `float f`. The compiler emits the `mtc1` itself. Never hard-code a GPR or write `mtc1` in the asm;
  `MB_relativeXYComponent` is parked because it only matched that way.
- **Scratch quadwords stored to the stack.** These come from `volatile uint128` locals.
- **Real sizes for globals.** Give global objects their real size (for example `IntFXReg`). A small object
  becomes small data and gets a different address split.
- **Decoding `.byte` VU ops.** For a word `op`:
  - special2 function = `((op >> 6) & 0x1f) * 4 + ((op & 0x3f) - 0x3c)`
  - dest = `(op >> 21) & 0xf`
  - ft = `(op >> 16) & 0x1f`
  - fs = `(op >> 11) & 0x1f`

  For example, `vopmula.xyz` and `vmaddaw.xyz` appear only as `.byte` in the split asm.
- **Parked near misses.** In `WPN_AddGravity` and `Lerp___dupe3`, the GPR copy (`daddu`) that feeds a
  `qmtc2` is scheduled one instruction away from retail's position.
- **Not converted:** hand-written assembly, meaning split asm marked `handwritten` and modules outside
  `GAME_SN_NAMES` such as `fastfunc`, `shadowproc`, `mathfunc_asm`, `collproc` and `skyproc`. It stays
  `INCLUDE_ASM`.
- **Listing candidates:** `python build/game-work/vu_list.py [MAXSIZE]` (from the dl directory) lists the
  remaining root functions that use VU0/MMI instructions, with their size and the share of VU/MMI
  instructions.
- **Comparing:** `game_test.py` reads the VU0 instructions that splat left as `.byte` lines, so the compare
  stays aligned.

## VU0 microprogram entry points

`vcallms` targets have names in `code/include/game_vu0.h`. Write `VU0_ASM("vcallms %0" : : "i"(VU0_SIN_COS));`,
which encodes the same as the literal. They were identified from the reversed microcode
(`code/asm/build/vutext/vutext.vsm`). Call counts are `vcallms` uses in the remaining split game asm.

| Name | Entry | Program | What it does | Calls |
|---|---|---|---|---|
| `VU0_SIN_COS` | 0xc60 | resident library | angle in `vf15.x` → `vf15.x` = sin, `vf15.y` = cos | 250 |
| `VU0_COS_SIN` | 0xc78 | resident library | angle in `vf15.x` → `vf15.x` = cos, `vf15.y` = sin (`FastCos`) | 3 |
| `VU0_QUAT_TO_MATRIX` | 0xd28 | resident library | quaternion in `vf15` → rotation rows `vf27`–`vf29` | 13 |
| `VU0_ACOS` | 0xda0 | resident library | `vf15.x` → acos (A&S polynomial × √(1−x)) | 1 |
| `VU0_SAVE_VF16_23` | 0xe10 | resident library | store `vf16`–`vf23` to VU0 data 16–23 | 11 |
| `VU0_SAVE_VF16_23_1_14` | 0xe50 | resident library | store `vf16`–`vf23`, then `vf1`–`vf14` | 0 |
| `VU0_SAVE_VF1_14` | 0xe90 | resident library | store `vf1`–`vf14` | 11 |
| `VU0_LOAD_VF16_23` | 0xf00 | resident library | reload `vf16`–`vf23` | 10 |
| `VU0_LOAD_VF1_14` | 0xf40 | resident library | reload `vf1`–`vf14` | 11 |
| `VU0_MAT3_MUL` | 0xa40 | `_dma_7` | `vf5`–`vf7` × `vf1`–`vf3` → `vf20`–`vf22` | 2 |
| `VU0_ANIM_SAVE_REGS` | 0x0 | `_dma_1` | `AnimSaveRegs` | 1 |
| `VU0_ANIM_RESTORE_REGS` | 0xf0 | `_dma_1` | `AnimRestoreRegs` | 1 |
| `VU0_ANIM_RESOLVE_MATS` | 0x738 | `_dma_1` | `AnimResolveMats` | 2 |

- **Resident library:** `InitOnce` loads the chain at 0x10f1e0 (`mpg_0010f1ec`, micro 0xb10–0xfb0) at boot.
- **Animation programs:** `_dma_1` (0x1170d0) and `_dma_7` (0x117a60) are swapped in by mobyfunc and
  transition through `VU0_loadMicroProgram`. Their entries are valid only while that program is loaded.
- **Other user of 0x0:** `CmeUnpack` calls micro 0x0 while a different program is loaded, so it does not
  use `VU0_ANIM_SAVE_REGS`.

## Converted with inline asm (revisit)

| Function | Module | Kind | Notes |
|---|---|---|---|
| `MB_GetWorldSpaceVector` | mobyutil | VU0 | three `VU0_ASM` accumulator ops, then `VU0_OP` vmaddw/vadd; `v`/`r`/`pos` pinned to vf3/vf1/vf4 |
| `MB_AlignWithGravity` | mobyutil | VU0 | -1.0f via `long` bits + `VU0_OP` qmtc2, then `vmulx`; registers pinned to vf1/vf2 |
| `Camera_CopyLastQuatToPolar` | camera | VU0 | one `VU0_OP` vadd with `+j`; the rest is plain C |
| `CubicLine_Update` | FXUtil | VU0 | √2 via `long` bits + qmtc2; two 3-op `VU0_OP` quaternion-rotate groups, registers pinned |
| `sound_GetFade___dupe2` | sound | VU0 | distance: vmaxw/vsub/vmul `VU0_OP`, vadday/vmaddz/vsqrt/vwaitq `VU0_ASM`, float out via qmfc2 `"=r"` |
| `MB_getJumpPeak` | mobyutil | MMI | two `MMI_ASM("pextuw ...")` with float outputs in GPRs |
| `GetMobyBangleStats` | mobyfunc | MMI | `MMI_OP("plzcw ...")`; non-volatile so the scheduler moves the `li`/store across it |

## Plain C (no asm needed)

These functions were listed as VU0/MMI candidates but match as ordinary C using `uint128`/`vec4`.

| Function | Module | Notes |
|---|---|---|
| `NAVG_SetTargetWp` | navsysglobal | `vec4` copy (`lq`/`sq`) |
| `NAVG_WpSet` | navsysglobal | `vec4` copy through a stack temporary, node handle in the w word |
| `NAVG_NodeGetCenter` | navsysglobal | `vec4` copy |
| `NAVG_WpSetPos` | navsysglobal | `vec4` copies through a stack temporary |
| `NAVG_WpGetNode` | navsysglobal | volatile word read gives retail's `lw`+`andi` |
| `sound_SetOffset` | sound | `vec4` store |
| `lineEmitterSetAttrib` | sound | jump table; `vec4` stores |
| `SetCollDamIn` | mobyutil | `vec4` passed by value as the 5th argument |
| `MB_IsPntInPath` | mobyutil | `vec4` by value |
| `MB_SpawnInit` | mobyutil | `vec4` copies |
