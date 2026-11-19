#ifndef GAME_VU0_H
#define GAME_VU0_H

/*
 * VU0 macro-mode and 128-bit MMI support for game code (docs/decompilation/DECISIONS.md D20).
 * Include after game_section.h. Every function that uses these macros is listed in
 * DOCS/libraries/GAME_VU0.md.
 *
 * Game code is compiled with -mvu0-use-vf0-vf31, so the compiler allocates VU0 registers itself
 * (`j` constraint) and emits lqc2, sqc2, qmtc2 and qmfc2 for uint128 values, filling delay slots
 * as retail does. Only the VU0/MMI operations it cannot express go in inline asm, one operation
 * (or a fixed group retail keeps together) per statement, through VU0_ASM or MMI_ASM, so that
 * `grep -n "VU0_ASM\|MMI_ASM"` lists every place still written as asm.
 *
 * Revisit later: these asm statements stand in for the original mathfunc_inline.h-style helpers.
 * When those helpers are reconstructed (or an intrinsic form is found that compiles to the same
 * bytes), replace the asm here with C and remove the function from GAME_VU0.md.
 */

/* A 128-bit value: one VU0 register or one lq/sq quadword. Retail vec4 is `struct { uint128 m_v; }`. */
typedef unsigned int uint128 __attribute__((mode(TI)));

/* Inline asm for VU0 macro instructions (vadd, vmul*, vmadd*, vcallms, ...). */
#define VU0_ASM __asm__ __volatile__

/* Inline asm for 128-bit MMI instructions the compiler does not generate (p*, qfsrv, ...). */
#define MMI_ASM __asm__ __volatile__

#endif /* GAME_VU0_H */
