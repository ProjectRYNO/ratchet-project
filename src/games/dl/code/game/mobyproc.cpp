#include "common.h"
#include "game_section.h"



typedef struct mobyLights {
	/* 0x00 */ char unk00[0x38];
	/* 0x38 */ unsigned long lights;
} mobyLights_t;
void SetMobyAmbientLights(mobyLights_t *moby, unsigned int r, unsigned int g, unsigned int b) __asm__("SetMobyAmbientLights");

void SetMobyLights(mobyLights_t *moby, unsigned long ambient, unsigned long a, unsigned long b, unsigned long c) __asm__("SetMobyLights");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", SetMobyLights);

GAME_SECTION(SetMobyAmbientLights) void SetMobyAmbientLights(mobyLights_t *moby, unsigned int r, unsigned int g, unsigned int b)
{
	*(unsigned int *)((char *)moby + 0x3c) = r | (g << 8) | (b << 16);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", GetMobyAmbientLights);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", AllocMobyVar);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", FreeMobyVar);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", FreeMobyGridLists);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", AllocMobyGridLists);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", UpdateMobyGrids);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", PostUpdateMoby);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", PostUpdateMobyBsphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", BuildMobyTextureDma);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", MobyAnimProc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", FUN_00470bf0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", SetMobyLightCuboid);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", func_00472510);
