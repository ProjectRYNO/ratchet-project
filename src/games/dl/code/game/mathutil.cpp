#include "common.h"
#include "game_section.h"

struct MathUtilities {
	int WrapValue(int value, int low, int high) __asm__("WrapValue");
};

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathutil", VecSlerp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathutil", func_004FE840);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathutil", GetVectorSphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathutil", GetVectorCircle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathutil", func_004FE930);

GAME_SECTION(WrapValue) int MathUtilities::WrapValue(int value, int low, int high)
{
	int range = high - low + 1;
	while (value < low) value += range;
	while (value > high) value -= range;
	return value;
}
