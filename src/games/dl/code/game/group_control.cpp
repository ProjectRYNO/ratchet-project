#include "common.h"
#include "game_section.h"
#include "mobyutil.h"


struct mobyVars {
	/* 0x00 */ char unk00[0x30];
	/* 0x30 */ void *pRole;
};
void *MB_GetRoleVars(moby *pMoby) __asm__("MB_GetRoleVars");


GAME_SECTION(MB_GetRoleVars) void *MB_GetRoleVars(moby *pMoby)
{
	if (pMoby && pMoby->pVar && (pMoby->modeBits & 0x20)) return ((mobyVars *)pMoby->pVar)->pRole;
	return 0;
}
