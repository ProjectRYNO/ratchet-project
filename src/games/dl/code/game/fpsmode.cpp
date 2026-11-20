#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fpsmode", FPSCam_Init);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fpsmode", FPSCam_Reset);

JUNK_ASM(func_00457ED8,
	"\taddiu $29, $29, 0x90\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xd0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fpsmode", FPSCam_HandleExtension);
