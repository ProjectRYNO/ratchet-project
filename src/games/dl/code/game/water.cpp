#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/water", WaterTile_LookupTile);

JUNK_ASM(func_004E8438,
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/water", WaterTile_PutDrop);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/water", WaterTile_GetHeight);

JUNK_ASM(func_004E8D38,
	"\taddiu $29, $29, 0x120\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xb0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n"
	"\tsw $0, 0x10($2)\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x120\n"
	"\tnop\n");
