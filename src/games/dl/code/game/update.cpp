#include "common.h"
#include "game_section.h"


struct moby {
	/* 0x00 */ char unk00[0x20];
	/* 0x20 */ unsigned char bits;
	/* 0x21 */ char unk21[0x34 - 0x21];
	/* 0x34 */ unsigned short state;
	/* 0x36 */ char unk36[0xbc - 0x36];
	/* 0xbc */ short oClass;
	/* 0xbe */ char unkbe[0x100 - 0xbe];
};
extern int LameShadowCnt __asm__("LameShadowCnt");
void CleanRegisteredDraws() __asm__("CleanRegisteredDraws");
void Camera_DestroyReticule(moby *) __asm__("Camera_DestroyReticule");
void ResetGameCounters() __asm__("ResetGameCounters");
extern moby *MobyInstancePermEnd __asm__("MobyInstancePermEnd");
void HideMobysForScene(int) __asm__("HideMobysForScene");


GAME_SECTION(ResetGameCounters) void ResetGameCounters()
{
	CleanRegisteredDraws();
	LameShadowCnt = 0;
	Camera_DestroyReticule(0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/update", func_004E55B8);

GAME_SECTION(HideMobysForScene) void HideMobysForScene(int hide)
{
	for (moby *pmoby = MobyInstancePermEnd; pmoby->bits != 0xff; pmoby++) {
		if (pmoby->bits & 0x80) continue;
		if (pmoby->oClass != 0x183a && pmoby->oClass != 0x183c) continue;
		if (hide) pmoby->state |= 0x80;
		else pmoby->state &= ~0x80;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/update", mode_sceneInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/update", mode_sceneUnInit);
