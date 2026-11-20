#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/corefunc", srand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/corefunc", rand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/corefunc", rand16);

JUNK_ASM(func_00163440,
	"\tsq $3, 0x20($2)\n"
	"\tnop\n");
