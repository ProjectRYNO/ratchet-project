#include "common.h"
#include "game_section.h"
#include "mobyutil.h"


void *MB_GetRoleVars(moby *pMoby) __asm__("MB_GetRoleVars");


GAME_SECTION(MB_GetRoleVars) void *MB_GetRoleVars(moby *pMoby)
{
	if (pMoby && pMoby->pVar && (pMoby->modeBits & 0x20)) return ((SubVars *)pMoby->pVar)->roleVars;
	return 0;
}
