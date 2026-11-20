#include "common.h"
#include "game_section.h"
#include "mathutil.h"


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathutil", VecSlerp);

JUNK_ASM(func_004FE840,
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathutil", GetVectorSphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathutil", GetVectorCircle);

JUNK_ASM(func_004FE930,
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\tsub.s $f0, $f1, $f0\n"
	"\tnop\n");

GAME_SECTION(WrapValue) int MathUtilities::WrapValue(int value, int low, int high)
{
	int range = high - low + 1;
	while (value < low) value += range;
	while (value > high) value -= range;
	return value;
}
