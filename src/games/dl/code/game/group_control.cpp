#include "common.h"
#include "game_section.h"


struct mobyVars {
	/* 0x00 */ char unk00[0x30];
	/* 0x30 */ void *pRole;
};
struct moby {
	/* 0x00 */ char unk00[0x34];
	/* 0x34 */ unsigned short state;
	/* 0x36 */ char unk36[0xac - 0x36];
	/* 0xac */ mobyVars *pVar;
};
void *MB_GetRoleVars(moby *pMoby) __asm__("MB_GetRoleVars");


GAME_SECTION(MB_GetRoleVars) void *MB_GetRoleVars(moby *pMoby)
{
	if (pMoby && pMoby->pVar && (pMoby->state & 0x20)) return pMoby->pVar->pRole;
	return 0;
}
