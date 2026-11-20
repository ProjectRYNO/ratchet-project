#ifndef GAME_VU0_H
#define GAME_VU0_H

/*
 * VU0 macro-mode and 128-bit MMI support for game code (docs/decompilation/DECISIONS.md D20).
 * Include after game_section.h. Every function that uses these macros is listed in
 * DOCS/libraries/GAME_VU0.md.
 *
 * Game code is compiled with -mvu0-use-vf0-vf31, so the compiler allocates VU0 registers itself
 * (`j` constraint) and emits lqc2, sqc2, qmtc2 and qmfc2 for s128 values, filling delay slots
 * as retail does. Only the VU0/MMI operations it cannot express go in inline asm, one operation
 * (or a fixed group retail keeps together) per statement, through VU0_ASM or MMI_ASM, so that
 * `grep -n "VU0_ASM\|MMI_ASM"` lists every place still written as asm.
 *
 * Revisit later: these asm statements stand in for the original mathfunc_inline.h-style helpers.
 * When those helpers are reconstructed (or an intrinsic form is found that compiles to the same
 * bytes), replace the asm here with C and remove the function from GAME_VU0.md.
 */

/*
 * 128-bit values are s128/u128 from types.h (TImode, 16 bytes on every EE compiler): one VU0
 * register or one lq/sq quadword. Retail vec4 is `struct { s128 v; }` (dltypes.txt), in game/vector.h.
 */
#include "types.h"

/* Inline asm for VU0 macro instructions (vadd, vmul*, vmadd*, vcallms, ...). */
#define VU0_ASM __asm__ __volatile__

/* Inline asm for 128-bit MMI instructions the compiler does not generate (p*, qfsrv, ...). */
#define MMI_ASM __asm__ __volatile__

/*
 * Non-volatile forms for operations that produce outputs (qmtc2 from a GPR, vadd/vmul with "+j",
 * plzcw, pextuw, ...): the scheduler may move other instructions across them, as it did in retail.
 * Statements without outputs (vmula* into ACC, vcallms) must stay VU0_ASM.
 */
#define VU0_OP __asm__
#define MMI_OP __asm__

/*
 * VU0 microprogram entry points (vcallms targets, VU0 micro byte addresses), identified from the
 * reversed microcode in code/asm/build/vutext/vutext.vsm. Pass them as an immediate operand, which
 * encodes exactly like a literal: VU0_ASM("vcallms %0" : : "i"(VU0_COS_SIN));
 *
 * Resident math library: InitOnce loads the chain at 0x10f1e0 (mpg_0010f1ec, micro 0xb10-0xfb0).
 */
#define VU0_SIN_COS (0xc60)          /* in vf15.x = angle; out vf15.x = sin, vf15.y = cos */
#define VU0_COS_SIN (0xc78)          /* in vf15.x = angle; out vf15.x = cos, vf15.y = sin (FastCos) */
#define VU0_QUAT_TO_MATRIX (0xd28)   /* in vf15 = quaternion; out vf27-vf29 = rotation matrix rows */
#define VU0_ACOS (0xda0)             /* in vf15.x; out vf15.x = acos (polynomial * sqrt(1 - |x|)) */
#define VU0_SAVE_VF16_23 (0xe10)     /* store vf16-vf23 to VU0 data 16-23 */
#define VU0_SAVE_VF16_23_1_14 (0xe50) /* store vf16-vf23, then vf1-vf14 */
#define VU0_SAVE_VF1_14 (0xe90)      /* store vf1-vf14 to VU0 data 1-14 */
#define VU0_LOAD_VF16_23 (0xf00)     /* reload vf16-vf23 */
#define VU0_LOAD_VF1_14 (0xf40)      /* reload vf1-vf14 */

/* Animation programs (mobyanim / mobyfunc / transition): valid only while that program is loaded. */
#define VU0_MAT3_MUL (0xa40)         /* _dma_7 (0x117a60, micro 0xa40): vf5-vf7 x vf1-vf3 -> vf20-vf22 */
#define VU0_ANIM_SAVE_REGS (0x0)     /* _dma_1 (0x1170d0, micro 0x0): AnimSaveRegs */
#define VU0_ANIM_RESTORE_REGS (0xf0) /* _dma_1: AnimRestoreRegs */
#define VU0_ANIM_RESOLVE_MATS (0x738) /* _dma_1: AnimResolveMats */

#endif /* GAME_VU0_H */
