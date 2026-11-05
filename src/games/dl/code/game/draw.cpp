#include "common.h"
#include "game_section.h"


struct MobyInstance {
	/* 0x00 */ char unk00[0x20];
	/* 0x20 */ unsigned char state;
};
struct RegisteredDrawRoutine_t {
	/* 0x00 */ void (*drawFunc)(MobyInstance *);
	/* 0x04 */ MobyInstance *pMoby;
	/* 0x08 */ RegisteredDrawRoutine_t *pNext;
	/* 0x0c */ RegisteredDrawRoutine_t *pTail;
};
struct FrustumDef {
	/* 0x00 */ char unk00[0x28];
};
extern int RegisteredDrawsCount __asm__("RegisteredDrawsCount");
extern void *pRegistered_PreDraws __asm__("pRegistered_PreDraws");
extern void *pRegistered_PostPreDraws __asm__("pRegistered_PostPreDraws");
extern void *pRegistered_MobyDraws __asm__("pRegistered_MobyDraws");
extern void *pRegistered_PostDraws __asm__("pRegistered_PostDraws");
extern void *pRegistered_FontDraws __asm__("pRegistered_FontDraws");
extern void *pRegistered_ScreenEffectDraws __asm__("pRegistered_ScreenEffectDraws");
extern RegisteredDrawRoutine_t RegisteredDrawRoutines[] __asm__("RegisteredDrawRoutines");
extern FrustumDef SpecialFrustums[] __asm__("D_3D74B0");
extern FrustumDef *WideScreenFrustumMap[] __asm__("D_3D7690");
extern unsigned char SettingsWide[] __asm__("D_171DEB");
unsigned char EffectDrawInProgress __asm__("EffectDrawInProgress") GAME_GP_DATA = 0;
void CleanRegisteredDraws() __asm__("CleanRegisteredDraws");
FrustumDef *GetFrustumDef(int) __asm__("GetFrustumDef");
void RegisterDrawFunction(void *&, void (*)(MobyInstance *), MobyInstance *) __asm__("RegisterDrawFunction");
void ExecuteDrawFunctions(void *&) __asm__("ExecuteDrawFunctions");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawIOPInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00446C78);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", SetupUVMatrix);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ComposeCameraMatrix);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", UpdateFog);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ParseOcclGrid);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", GetOcclGridFromPair);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", BuildOcclVisibility);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", UpdateOcclusion);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", CalcAdditionalScrnInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", InitViewContext);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", UpdateViewContext);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00448340);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", SetPalMode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ResetDrawGlobals);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ResetGsRegisters);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ResetGsRegistersPr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_004489D8);

GAME_SECTION(GetFrustumDef) FrustumDef *GetFrustumDef(int frustrumIndex)
{
	FrustumDef *def;
	if (SettingsWide[0] && (def = WideScreenFrustumMap[frustrumIndex])) return def;
	return &SpecialFrustums[frustrumIndex];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", GetScreenFrustumIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", GetScreenFrustumCoords);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", GetScreenFrustumScales);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00448C50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", SetupGifPaging);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DoGifPaging);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00448EA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", CalcWorldSpaceUV);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00448F90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", GetEffectTex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", LoadTexToGs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", LoadPalToGs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ConstructEffectTex0);

GAME_SECTION(CleanRegisteredDraws) void CleanRegisteredDraws()
{
	RegisteredDrawsCount = 0;
	pRegistered_PreDraws = 0;
	pRegistered_PostPreDraws = 0;
	pRegistered_MobyDraws = 0;
	pRegistered_PostDraws = 0;
	pRegistered_FontDraws = 0;
	pRegistered_ScreenEffectDraws = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", RegisterDrawFunction);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ExecuteDrawFunctions);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", FadeToBlack);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawLogoAndStart);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawSubtitles);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00449BE8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawScreenOverlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawRectOverlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_0044A070);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawSprite);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawSprite___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_0044A408);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawSpriteFont);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawSpriteFontGouraud);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawSpriteFontWithShadow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_0044AA50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawScreenGQuad);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawScreenGQuad___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", DrawTextShadow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_0044AD00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", FastDrawStripInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_0044B058);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", Screen_FadeOut);
