#include "common.h"
#include "game_section.h"


typedef struct skyShell {
	/* 0x00 */ short unk00;
	/* 0x02 */ unsigned short flags;
} skyShell_t;
typedef struct skyData {
	/* 0x00 */ char unk00[6];
	/* 0x06 */ short numShells;
	/* 0x08 */ short sprite_cnt;
	/* 0x0a */ short sprite_max;
	/* 0x0c */ short texCnt;
	/* 0x0e */ short fx_cnt;
	/* 0x10 */ long *tex;
	/* 0x14 */ char unk14[8];
	/* 0x1c */ struct skySprite *sprites;
	/* 0x20 */ skyShell_t *shells[1];
} skyData_t;
extern skyData_t *Sky __asm__("Sky");
void SkyDrawShellGouraud(skyShell_t *) __asm__("SkyDrawShellGouraud");
void SkyDrawShellTextured(skyShell_t *) __asm__("SkyDrawShellTextured");
typedef struct skySprite {
	/* 0x00 */ unsigned char type;
	/* 0x01 */ char unk01[3];
	/* 0x04 */ unsigned int rgba;
	/* 0x08 */ char unk08[4];
	/* 0x0c */ unsigned int user;
	/* 0x10 */ char unk10[0x10];
} skySprite_t;
void SkyDrawShell(int index) __asm__("SkyDrawShell");

extern int *vu1_bufPtr __asm__("vu1_bufPtr");
extern int GSbase __asm__("GSbase");
extern int *sky_gif_page_markerA __asm__("sky_gif_page_markerA");
extern int *sky_gif_page_markerB __asm__("sky_gif_page_markerB");
void BuildGifTextureDma() __asm__("BuildGifTextureDma");
void VU1_texFlush() __asm__("VU1_texFlush");
void DoSkyGifPaging() __asm__("DoSkyGifPaging");
extern int GSloc __asm__("GSloc");
extern int GifLoadCnt __asm__("GifLoadCnt");
extern "C" int rand();
extern int gameMode __asm__("gameMode");
extern int worldUpdateTime __asm__("worldUpdateTime");
extern int skyWorldUpdateTime __asm__("skyWorldUpdateTime");
void SkyInitNightSprites(int, int) __asm__("SkyInitNightSprites");
void UpdateSkyShellMatrix(int, int) __asm__("UpdateSkyShellMatrix");
void SkySpriteProc() __asm__("SkySpriteProc");
void SkyLevelGeneric() __asm__("SkyLevelGeneric");
void SetupSkyGifPaging() __asm__("SetupSkyGifPaging");
void SkyUpdateNightSprites() __asm__("SkyUpdateNightSprites");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", SkyInitNightSprites);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", SkyUpdateNightSprites);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", UpdateSkyShellMatrix);

GAME_SECTION(SkyLevelGeneric) void SkyLevelGeneric()
{
	int do_stars = 0;
	int star_shell;
	int update_cnt;
	int ishell;
	if (Sky->sprite_max != 0) do_stars = Sky->fx_cnt >= 2;
	star_shell = 0;
	if (do_stars) {
		if (Sky->sprite_cnt == 0) SkyInitNightSprites(Sky->sprite_max, 0);
		else SkyUpdateNightSprites();
		star_shell = gameMode == 6;
	}
	update_cnt = worldUpdateTime - skyWorldUpdateTime;
	if (update_cnt > 2) update_cnt = 2;
	for (ishell = 0; ishell < Sky->numShells; ishell++) {
		UpdateSkyShellMatrix(ishell, update_cnt);
		SkyDrawShell(ishell);
		if (do_stars && ishell == star_shell) SkySpriteProc();
	}
	skyWorldUpdateTime = worldUpdateTime;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", SetupSkyGifPaging);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", DoSkyGifPaging);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", func_004DF090);

GAME_SECTION(SkyDrawShell) void SkyDrawShell(int index)
{
	if (index < Sky->numShells) {
		skyShell_t *shell = Sky->shells[index];
		if (shell->flags & 1) SkyDrawShellGouraud(shell);
		else SkyDrawShellTextured(shell);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", SkyDrawShellTextured);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", SkyDrawShellGouraud);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", SkySpriteProc);
