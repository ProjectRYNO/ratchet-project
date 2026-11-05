#ifndef GAME_SECTION_H
#define GAME_SECTION_H

/*
 * Game objects built with SN ProDG GCC 2.95.3 v1.36 (DOCS/libraries/GAME.md). Each function has its
 * own section so the linker can place it in its registered retail slot. Include after common.h.
 * Retained assembly is collected by tools/game_asm_parts.py and assembled separately, because
 * SN's Ps2EeAs cannot parse macro.inc.
 */
#define GAME_SECTION(name) __attribute__((section(".game_" #name)))

/*
 * Data retail defines in the same source file, which its code reaches through $gp. Declare it as
 * `int name __asm__("name") GAME_GP_DATA = 0;`. The value is unused: tools/game_fix_symtab.py turns
 * the definition back into a reference, so the real bytes stay in the retained data segment.
 */
#define GAME_GP_DATA __attribute__((section(".sdata")))

#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)

#endif /* GAME_SECTION_H */
