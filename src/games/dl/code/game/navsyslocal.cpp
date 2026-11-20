#include "common.h"
#include "game_section.h"
#include "mobyutil.h"


struct mobyVars {
	/* 0x00 */ char unk00[0x28];
	/* 0x28 */ void *pEffector;
};
void *MB_GetEffectorVars(moby *pMoby) __asm__("MB_GetEffectorVars");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", NAVL_GetEffectorsOfType);

JUNK_ASM(func_0048F000,
	"\taddiu $29, $29, 0x90\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", NAVL_ProcessEffectors);

JUNK_ASM(func_0048F430,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

GAME_SECTION(MB_GetEffectorVars) void *MB_GetEffectorVars(moby *pMoby)
{
	if (!pMoby || !pMoby->pVar || !(pMoby->modeBits & 0x20)) return 0;
	return ((mobyVars *)pMoby->pVar)->pEffector;
}

JUNK_ASM(func_0048F478,
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x290\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $2, $0, -0x1\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");
