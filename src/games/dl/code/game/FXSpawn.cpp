#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXSpawn", Teleport_VehiclePlayer);

JUNK_ASM(func_0044E0E8,
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x60\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXSpawn", Lightning_SimpleTwoPoint);

JUNK_ASM(func_0044E1C0,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXSpawn", FXS_DrawFrozen);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXSpawn", ShadowVolume_Ice);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXSpawn", ShadowVolume_Electric);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXSpawn", ShadowVolume_Fire);
