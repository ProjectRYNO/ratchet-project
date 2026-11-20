#include "common.h"
#include "game_section.h"
#include "mobyutil.h"



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

JUNK_ASM(func_004E55B8,
	"\tsw $3, 0x0($28)\n"
	"\tnop\n");

GAME_SECTION(HideMobysForScene) void HideMobysForScene(int hide)
{
	for (moby *pmoby = MobyInstancePermEnd; pmoby->state != 0xff; pmoby++) {
		if (pmoby->state & 0x80) continue;
		if (pmoby->oClass != 0x183a && pmoby->oClass != 0x183c) continue;
		if (hide) pmoby->modeBits |= 0x80;
		else pmoby->modeBits &= ~0x80;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/update", mode_sceneInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/update", mode_sceneUnInit);
