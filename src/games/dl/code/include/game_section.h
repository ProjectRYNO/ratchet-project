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
/*
 * Retail bytes that are not a function (DECISIONS.md D21), written inline in their own slot section.
 */
#undef JUNK_ASM
#define JUNK_ASM(NAME, BODY) \
	__asm__(".section .game_" #NAME ",\"ax\",@progbits\n.set noreorder\n.set noat\n" BODY ".set at\n.set reorder\n.text")

/*
 * End of a hand-written function body that returns by itself (DECISIONS.md D22): moves the jr $31 / nop
 * the compiler appends into a section the linker discards (sound_loop_compat.py repairs the debug records).
 */
#define GAME_ASM_TAIL(NAME) "\t.section .discard_game_" #NAME ",\"ax\",@progbits"

#endif /* GAME_SECTION_H */
