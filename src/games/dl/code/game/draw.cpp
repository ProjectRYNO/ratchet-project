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
	/* 0x00 */ float unk00[4];
	/* 0x10 */ float size_x;
	/* 0x14 */ float size_y;
	/* 0x18 */ char unk18[0x10];
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



unsigned char ScreenColorEffectEnabled __asm__("D_21EB34") GAME_GP_DATA = 0;
unsigned char ScreenInsertCycEnabled __asm__("D_21EB40") GAME_GP_DATA = 0;
unsigned char ScreenInsertBkgEnabled __asm__("D_21EB50") GAME_GP_DATA = 0;
extern int OcclUpdate __asm__("OcclUpdate");
extern char OcclVisibility[0x80] __asm__("OcclVisibility");
extern int LameShadowCnt __asm__("LameShadowCnt");
extern int LetterBoxOn __asm__("LetterBoxOn");
extern int LetterBoxPixels __asm__("LetterBoxPixels");
extern int OcclMode __asm__("OcclMode");
struct WaterTile;
struct WaterTileBox;
extern WaterTile *WaterTiles __asm__("WaterTiles");
extern WaterTileBox *WaterTileBoxes __asm__("WaterTileBoxes");
extern int WaterTileCnt __asm__("WaterTileCnt");
extern int WaterPlaneActive __asm__("WaterPlaneActive");
struct DisplayEnv {
	/* 0x00 */ unsigned long smode2;
	/* 0x08 */ unsigned long dispfb;
	/* 0x10 */ unsigned long display;
	/* 0x18 */ unsigned long bgcolor;
};
extern DisplayEnv aaBuffDisp __asm__("aaBuffDisp");
struct CamStatics {
	/* 0x00 */ char unk00[0xc8];
	/* 0xc8 */ float fadeSpeed;
	/* 0xcc */ char unkcc[0x34];
};
struct CameraDef {
	/* 0x000 */ char unk000[0x60];
	/* 0x060 */ CamStatics camStatics;
	/* 0x160 */ char unk160[0x310];
};
extern CameraDef GameCamera[4] __asm__("GameCamera");
extern int *gNumLocalHeroes __asm__("gNumLocalHeroes");
extern float ScreenFade[4] __asm__("ScreenFade");
void BuildOcclVisibility() __asm__("BuildOcclVisibility");
void DrawIOPInfo() __asm__("DrawIOPInfo");
void UpdateOcclusion() __asm__("UpdateOcclusion");
void ResetDrawGlobals() __asm__("ResetDrawGlobals");
void ResetGsRegistersPr() __asm__("ResetGsRegistersPr");
void GetScreenFrustumScales(int, float &, float &) __asm__("GetScreenFrustumScales");
unsigned long ConstructEffectTex0(int, int, int, int, int) __asm__("ConstructEffectTex0");
bool Screen_FadeOut(float) __asm__("Screen_FadeOut");
#define GS_REG(a) (*(volatile unsigned long *)(a))

GAME_SECTION(DrawIOPInfo) void DrawIOPInfo()
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00446C78);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", SetupUVMatrix);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ComposeCameraMatrix);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", UpdateFog);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ParseOcclGrid);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", GetOcclGridFromPair);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", BuildOcclVisibility);

GAME_SECTION(UpdateOcclusion) void UpdateOcclusion()
{
	if (OcclUpdate == 0) {
		FastMemSet(OcclVisibility, -1, 0x80);
	} else if (OcclUpdate == 2) {
		BuildOcclVisibility();
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", CalcAdditionalScrnInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", InitViewContext);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", UpdateViewContext);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00448340);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", SetPalMode);

GAME_SECTION(ResetDrawGlobals) void ResetDrawGlobals()
{
	CleanRegisteredDraws();
	LameShadowCnt = 0;
	LetterBoxOn = 0;
	LetterBoxPixels = 0;
	ScreenColorEffectEnabled = 0;
	ScreenInsertCycEnabled = 0;
	ScreenInsertBkgEnabled = 0;
	OcclMode = 0;
	WaterTiles = 0;
	WaterTileBoxes = 0;
	WaterTileCnt = 0;
	WaterPlaneActive = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ResetGsRegisters);

GAME_SECTION(ResetGsRegistersPr) void ResetGsRegistersPr()
{
	GS_REG(0x120000e0) = 0;
	GS_REG(0x12000000) = 0xffa1;
	GS_REG(0x12000020) = aaBuffDisp.smode2;
	GS_REG(0x12000070) = aaBuffDisp.dispfb;
	GS_REG(0x12000090) = aaBuffDisp.dispfb;
	GS_REG(0x12000080) = aaBuffDisp.display;
	GS_REG(0x120000a0) = aaBuffDisp.display;
	GS_REG(0x120000d0) = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_004489D8);

GAME_SECTION(GetFrustumDef) FrustumDef *GetFrustumDef(int frustrumIndex)
{
	FrustumDef *def;
	if (SettingsWide[0] && (def = WideScreenFrustumMap[frustrumIndex])) return def;
	return &SpecialFrustums[frustrumIndex];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", GetScreenFrustumIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", GetScreenFrustumCoords);

GAME_SECTION(GetScreenFrustumScales) void GetScreenFrustumScales(int index, float &sx, float &sy)
{
	FrustumDef *pfrust = GetFrustumDef(index);
	sx = pfrust->size_x;
	sy = pfrust->size_y;
}

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
