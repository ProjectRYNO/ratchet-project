#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/quad", QuadResetQuad);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/quad", QuadScaleQuad);

JUNK_ASM(func_004FBA50,
	"\taddiu $29, $29, 0x170\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/quad", QuadDrawBillboard);
