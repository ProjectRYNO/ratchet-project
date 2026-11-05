#include "common.h"
#include "game_section.h"


struct mobyVars {
	/* 0x00 */ char unk00[0x28];
	/* 0x28 */ void *pEffector;
};
struct moby {
	/* 0x00 */ char unk00[0x34];
	/* 0x34 */ unsigned short state;
	/* 0x36 */ char unk36[0xac - 0x36];
	/* 0xac */ mobyVars *pVar;
};
void *MB_GetEffectorVars(moby *pMoby) __asm__("MB_GetEffectorVars");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", NAVL_GetEffectorsOfType);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", func_0048F000);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", NAVL_ProcessEffectors);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", func_0048F430);

GAME_SECTION(MB_GetEffectorVars) void *MB_GetEffectorVars(moby *pMoby)
{
	if (!pMoby || !pMoby->pVar || !(pMoby->state & 0x20)) return 0;
	return pMoby->pVar->pEffector;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", func_0048F478);
