#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/tiefunc", ResetTieLightingCache);

JUNK_ASM(func_004E4B38,
	"\tlui $31, (0x70000000 >> 16)\n"
	"\tnop\n"
	"\tlui $31, (0x70000000 >> 16)\n"
	"\tnop\n");
