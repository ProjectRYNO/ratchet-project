#include "common.h"
#include "game_section.h"
#include "mobyutil.h"


struct mobyVars {
	/* 0x00 */ char unk00[0x28];
	/* 0x28 */ void *pEffector;
};
void *MB_GetEffectorVars(moby *pMoby) __asm__("MB_GetEffectorVars");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", NAVL_GetEffectorsOfType);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", func_0048F000);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", NAVL_ProcessEffectors);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", func_0048F430);

GAME_SECTION(MB_GetEffectorVars) void *MB_GetEffectorVars(moby *pMoby)
{
	if (!pMoby || !pMoby->pVar || !(pMoby->modeBits & 0x20)) return 0;
	return ((mobyVars *)pMoby->pVar)->pEffector;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsyslocal", func_0048F478);
