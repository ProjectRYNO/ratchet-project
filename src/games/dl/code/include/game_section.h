#ifndef GAME_SECTION_H
#define GAME_SECTION_H

/*
 * Game objects built with SN ProDG GCC 2.95.3 v1.36 (DOCS/libraries/GAME.md). Each function has its
 * own section so the linker can place it in its registered retail slot. Include after common.h.
 */
#define GAME_SECTION(name) __attribute__((section(".game_" #name)))

/* Functions not yet recovered stay in their own slots. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
	__asm__(".section .game_" #NAME ",\"ax\",@progbits\n" \
		".set noat\n.set noreorder\n" \
		".include \"" FOLDER "/" #NAME ".s\"\n" \
		".set reorder\n.set at\n.text\n")
#endif

#endif /* GAME_SECTION_H */
