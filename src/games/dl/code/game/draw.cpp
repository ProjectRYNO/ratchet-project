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
	/* 0x160 */ char unk160[0x300];
	/* 0x460 */ int CamUnderWater;
	/* 0x464 */ char unk464[0xc];
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

/* ===== AL additions ===== */
typedef unsigned int alQword[4];
extern alQword *vu1_bufPtr __asm__("vu1_bufPtr");
extern int GSloc __asm__("GSloc");
extern char FastPalTrns_4[] __asm__("FastPalTrns_4");
extern char FastPalTrns_8[] __asm__("FastPalTrns_8");
void FastMemCopy(void *, const void *, int) __asm__("FastMemCopy");
void VU1_texFlush() __asm__("VU1_texFlush");
char *ParseOcclGrid(int, int, int) __asm__("ParseOcclGrid");
char *GetOcclGridFromPair(int, int, int, int, int, int, float) __asm__("GetOcclGridFromPair");
int LoadPalToGs(void *, int) __asm__("LoadPalToGs");
struct alScrn {
	/* 0x00 */ int size_x;
	/* 0x04 */ int size_y;
	/* 0x08 */ int unk08[2];
	/* 0x10 */ int ofs_x;
	/* 0x14 */ int ofs_y;
};
extern alScrn alScrnVar __asm__("Scrn");
void DrawScreenGQuad(long *, int *) __asm__("DrawScreenGQuad");
void DrawScreenGQuad2(int, int, int, int, int, int *) __asm__("DrawScreenGQuad___dupe2");
extern unsigned int *OcclGrid __asm__("OcclGrid");
extern int screenMode __asm__("screenMode");
struct alAABuffDef {
	/* 0x000 */ char unk000[0x150];
	/* 0x150 */ short drawW;
	/* 0x152 */ short drawH;
	/* 0x154 */ int unk154[3];
};
extern alAABuffDef aaBuff __asm__("aaBuff");
int GetScreenFrustumIndex(int) __asm__("GetScreenFrustumIndex");
void GetScreenFrustumCoords(int, int &, int &, int &, int &) __asm__("GetScreenFrustumCoords");
struct ViewContext {
	/* 0x000 */ char unk000[0x228];
	/* 0x228 */ float fogNearDist;
	/* 0x22c */ float fogFarDist;
	/* 0x230 */ int unk230[2];
	/* 0x238 */ float fogNearIntensity;
	/* 0x23c */ float fogFarIntensity;
	/* 0x240 */ int scis_l;
	/* 0x244 */ int scis_r;
	/* 0x248 */ int scis_t;
	/* 0x24c */ int scis_b;
	/* 0x250 */ int fogR;
	/* 0x254 */ int fogG;
	/* 0x258 */ int fogB;
};
extern ViewContext VC __asm__("VC");
extern unsigned char LevelFogR __asm__("LevelFogR");
extern unsigned char LevelFogG __asm__("LevelFogG");
extern unsigned char LevelFogB __asm__("LevelFogB");
extern float LevelFogNearDist __asm__("LevelFogNearDist");
extern float LevelFogFarDist __asm__("LevelFogFarDist");
extern float LevelFogNearIntensity __asm__("LevelFogNearIntensity");
extern float LevelFogFarIntensity __asm__("LevelFogFarIntensity");
extern int LevelFogMode __asm__("LevelFogMode");
extern unsigned char WaterFogR __asm__("WaterFogR");
extern unsigned char WaterFogG __asm__("WaterFogG");
extern unsigned char WaterFogB __asm__("WaterFogB");
extern float WaterFogNearDist __asm__("WaterFogNearDist");
extern float WaterFogFarDist __asm__("WaterFogFarDist");
extern float WaterFogNearIntensity __asm__("WaterFogNearIntensity");
extern float WaterFogFarIntensity __asm__("WaterFogFarIntensity");
extern int PartClipDist __asm__("PartClipDist");
void UpdateViewContext() __asm__("UpdateViewContext");
void UpdateFog(int) __asm__("UpdateFog");
extern alQword *gif_page_markerA __asm__("gif_page_markerA");
extern alQword *gif_page_markerB __asm__("gif_page_markerB");
extern int GSbase __asm__("GSbase");
extern int GifLoadCnt __asm__("GifLoadCnt");
extern int EffectTexCnt __asm__("EffectTexCnt");
struct alEffectTex {
	/* 0x00 */ unsigned long tex0;
	/* 0x08 */ unsigned short ptex;
	/* 0x0a */ unsigned short ppal;
	/* 0x0c */ unsigned char uLog;
	/* 0x0d */ unsigned char vLog;
	/* 0x0e */ short format;
};
extern alEffectTex EffectTexs[] __asm__("EffectTexs");
unsigned long BackBufferTex __asm__("BackBufferTex") GAME_GP_DATA = 0;
unsigned long BackBufferTex64 __asm__("BackBufferTex64") GAME_GP_DATA = 0;
int AlphaPalAdr __asm__("AlphaPalAdr") GAME_GP_DATA = 0;
struct alHudHeader {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ int unk10;
	/* 0x14 */ int pal_count[5];
	/* 0x28 */ int unk28[7];
	/* 0x44 */ int tex_count4;
};
struct alHudTex {
	/* 0x00 */ int unk00;
	/* 0x04 */ unsigned short gsram;
	/* 0x06 */ short unk06;
};
struct alHudDef {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ alHudHeader *header;
	/* 0x10 */ int unk10[2];
	/* 0x18 */ alHudTex *texs;
	/* 0x1c */ alHudTex *pals;
};
extern alHudDef alHud __asm__("Hud");
struct alGSmem {
	/* 0x00 */ int unk00;
	/* 0x04 */ int draw;
	/* 0x08 */ int zbuf;
};
extern alGSmem alGSmemVar __asm__("GSmem");
void FontForceInitialize() __asm__("FontForceInitialize");
void BuildGifTextureDma() __asm__("BuildGifTextureDma");
void SetupGifPaging(int) __asm__("SetupGifPaging");
void DoGifPaging() __asm__("DoGifPaging");
extern char FastTexTrns[] __asm__("FastTexTrns");
int LoadTexToGs(void *, int, int, int) __asm__("LoadTexToGs");

void DrawRectOverlay(int, int, int, int, unsigned long) __asm__("DrawRectOverlay");
void DrawTextShadow(int, int, int, int, int, int) __asm__("DrawTextShadow");
struct alGifLoad {
	/* 0x0 */ void *pal;
	/* 0x4 */ unsigned char palFmt;
	/* 0x5 */ unsigned char texFmt;
	/* 0x6 */ short ploc;
	/* 0x8 */ void *tex;
	/* 0xc */ unsigned char uLog;
	/* 0xd */ unsigned char vLog;
	/* 0xe */ short tloc;
};
extern alGifLoad GifLoads[] __asm__("GifLoads");
extern char *EffectTexBase __asm__("EffectTexBase");
extern int g_BloomTexOffset __asm__("g_BloomTexOffset");
unsigned long PostEffects_GetFbTex(int) __asm__("PostEffects_GetFbTex");
unsigned long GetEffectTex(int, int) __asm__("GetEffectTex");
extern char reset_gs_regs_fixed[] __asm__("reset_gs_regs_fixed");
extern char reset_gs_regs_draw[] __asm__("reset_gs_regs_draw");
extern unsigned long reset_gs_regs_scis[] __asm__("reset_gs_regs_scis");
void VU1_addGSregister(unsigned int, unsigned long, bool) __asm__("VU1_addGSregister");
void ResetGsRegisters() __asm__("ResetGsRegisters");
struct alSceneDef {
	/* 0x00 */ char unk00[0x74];
	/* 0x74 */ int iframe;
};
extern alSceneDef Scene __asm__("Scene");
extern int g_easyAbort __asm__("g_easyAbort");
extern int g_CurrentFontName __asm__("g_CurrentFontName");
float FastCos(float) __asm__("FastCos");
unsigned long FastTweenColor(int, int, float) __asm__("FastTweenColor");
void FontSet(int) __asm__("FUN_00454350");
char *msg_string(int) __asm__("msg_string");
void FontPrint(float, float, unsigned long, char *, int, float, float, int, bool, unsigned long, float, float) __asm__("FontPrint");
void DrawLogoAndStart() __asm__("DrawLogoAndStart");

GAME_SECTION(DrawIOPInfo) void DrawIOPInfo()
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00446C78);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", SetupUVMatrix);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ComposeCameraMatrix);

GAME_SECTION(UpdateFog) void UpdateFog(int cameraIndex)
{
	if ((GameCamera + cameraIndex)->CamUnderWater != 0) {
		VC.fogR = WaterFogR;
		VC.fogG = WaterFogG;
		VC.fogB = WaterFogB;
		VC.fogNearDist = WaterFogNearDist;
		VC.fogFarDist = WaterFogFarDist;
		VC.fogNearIntensity = WaterFogNearIntensity;
		VC.fogFarIntensity = WaterFogFarIntensity;
		PartClipDist = 0x40000;
	} else {
		VC.fogR = LevelFogR;
		VC.fogG = LevelFogG;
		VC.fogB = LevelFogB;
		VC.fogNearDist = LevelFogNearDist;
		VC.fogFarDist = LevelFogFarDist;
		VC.fogNearIntensity = LevelFogNearIntensity;
		VC.fogFarIntensity = LevelFogFarIntensity;
		PartClipDist = 0x7d0000;
	}
	UpdateViewContext();
	LevelFogMode = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", ParseOcclGrid);

GAME_SECTION(GetOcclGridFromPair) char *GetOcclGridFromPair(int x0, int y0, int z0, int x1, int y1, int z1, float interp)
{
	char *pgrid;
	int x, y, z;

	if (interp < 0.5f) {
		if ((pgrid = ParseOcclGrid(x0, y0, z0)) != 0) {
			return pgrid;
		}
		x = x1;
		y = y1;
		z = z1;
	} else {
		if ((pgrid = ParseOcclGrid(x1, y1, z1)) != 0) {
			return pgrid;
		}
		x = x0;
		y = y0;
		z = z0;
	}
	return ParseOcclGrid(x, y, z);
}

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

GAME_SECTION(ResetGsRegisters) void ResetGsRegisters()
{
	(*vu1_bufPtr)[0] = 0x30000013;
	(*vu1_bufPtr)[1] = (unsigned int)reset_gs_regs_fixed;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000013;
	vu1_bufPtr++;
	(*vu1_bufPtr)[0] = 0x30000009;
	(*vu1_bufPtr)[1] = (unsigned int)reset_gs_regs_draw;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000009;
	vu1_bufPtr++;
	(*vu1_bufPtr)[0] = 0x10000003;
	(*vu1_bufPtr)[1] = 0;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000003;
	reset_gs_regs_scis[2] = (long)VC.scis_l | (long)VC.scis_r << 16 | (long)VC.scis_t << 32 | (long)VC.scis_b << 48;
	vu1_bufPtr++;
	reset_gs_regs_scis[4] = (long)VC.scis_l | (long)VC.scis_r << 16 | (long)VC.scis_t << 32 | (long)VC.scis_b << 48;
	FastMemCopy(vu1_bufPtr, reset_gs_regs_scis, 0x30);
	vu1_bufPtr += 3;
	VU1_addGSregister(0x3d, (long)VC.fogR | (long)VC.fogG << 8 | (long)VC.fogB << 16, false);
	VU1_addGSregister(0x51, 0, false);
}

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

GAME_SECTION(GetScreenFrustumCoords) void GetScreenFrustumCoords(int index, int &x0, int &y0, int &x1, int &y1)
{
	FrustumDef *pfrust = GetFrustumDef(index);

	x0 = (int)((float)aaBuff.drawW * pfrust->unk00[0]);
	y0 = (int)((float)aaBuff.drawH * pfrust->unk00[2]);
	x1 = (int)((float)aaBuff.drawW * pfrust->unk00[1]);
	y1 = (int)((float)aaBuff.drawH * pfrust->unk00[3]);
}

GAME_SECTION(GetScreenFrustumScales) void GetScreenFrustumScales(int index, float &sx, float &sy)
{
	FrustumDef *pfrust = GetFrustumDef(index);
	sx = pfrust->size_x;
	sy = pfrust->size_y;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00448C50);

GAME_SECTION(SetupGifPaging) void SetupGifPaging(int no_hud)
{
	gif_page_markerA = vu1_bufPtr++;
	GSloc = GSbase;
	GifLoadCnt = 0;
	for (int i = 0; i < EffectTexCnt; i++) {
		EffectTexs[i].tex0 = 0;
	}
	BackBufferTex = 0;
	BackBufferTex64 = 0;
	AlphaPalAdr = 0;
	if (no_hud == 0) {
		for (int i = 0; i < alHud.header->tex_count4; i++) {
			if (alHud.texs[i].gsram >= alGSmemVar.draw >> 8) {
				alHud.texs[i].gsram = 0;
			}
		}
		for (int i = 0; i < alHud.header->pal_count[4]; i++) {
			alHud.pals[i].gsram = 0;
		}
	}
	FontForceInitialize();
}

GAME_SECTION(DoGifPaging) void DoGifPaging()
{
	gif_page_markerB = vu1_bufPtr++;
	(*gif_page_markerA)[0] = 0x20000000;
	(*gif_page_markerA)[1] = (unsigned int)vu1_bufPtr;
	(*gif_page_markerA)[2] = 0;
	(*gif_page_markerA)[3] = 0;
	BuildGifTextureDma();
	VU1_texFlush();
	(*vu1_bufPtr)[0] = 0x20000000;
	(*vu1_bufPtr)[1] = (unsigned int)(gif_page_markerA + 1);
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0;
	vu1_bufPtr = vu1_bufPtr + 1;
	(*gif_page_markerB)[0] = 0x20000000;
	(*gif_page_markerB)[1] = (unsigned int)vu1_bufPtr;
	(*gif_page_markerB)[2] = 0;
	(*gif_page_markerB)[3] = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00448EA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", CalcWorldSpaceUV);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_00448F90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", GetEffectTex);

GAME_SECTION(LoadTexToGs) int LoadTexToGs(void *ram_addr, int u_log, int v_log, int format)
{
	int qsize;
	int tbw;
	int tex_loc;
	char *pc;
	int ret;

	tbw = u_log - 6;
	if (tbw < 0) {
		tbw = 0;
	}
	tbw = 1 << tbw;
	FastMemCopy(vu1_bufPtr, FastTexTrns, 0x70);
	switch (format) {
	case 0x14:
		qsize = (1 << (u_log + v_log)) >> 5;
		break;
	case 0x13:
		qsize = (1 << (u_log + v_log)) >> 4;
		break;
	case 2:
		qsize = (1 << (u_log + v_log)) >> 3;
		break;
	case 0:
		qsize = (1 << (u_log + v_log)) >> 2;
		break;
	}
	tex_loc = GSloc;
	ret = tex_loc >> 8;
	GSloc = tex_loc + qsize * 0x10;
	pc = (char *)vu1_bufPtr;
	pc[0x26] = tbw;
	pc[0x27] = format;
	*(int *)(pc + 0x64) = (int)ram_addr;
	*(short *)(pc + 0x24) = ret;
	*(int *)(pc + 0x30) = 1 << u_log;
	*(int *)(pc + 0x34) = 1 << v_log;
	*(int *)(pc + 0x50) = qsize | 0x8000;
	*(int *)(pc + 0x60) = qsize | 0x30000000;
	*(int *)(pc + 0x6c) = qsize | 0x50000000;
	vu1_bufPtr += 7;
	VU1_texFlush();
	return ret;
}

GAME_SECTION(LoadPalToGs) int LoadPalToGs(void *ram_addr, int format)
{
	int pal_loc = GSloc >> 8;

	if (format == 0x14) {
		FastMemCopy(vu1_bufPtr, FastPalTrns_4, 0x70);
		GSloc += 0x100;
	} else {
		FastMemCopy(vu1_bufPtr, FastPalTrns_8, 0x70);
		GSloc += 0x400;
	}
	alQword *pc = vu1_bufPtr;
	pc[6][1] = (unsigned int)ram_addr;
	*(short *)&pc[2][1] = pal_loc;
	vu1_bufPtr += 7;
	VU1_texFlush();
	return pal_loc;
}

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

GAME_SECTION(DrawScreenGQuad___dupe2) void DrawScreenGQuad2(int x0, int y0, int x1, int y1, int z, int *rgbas)
{
	long xys[4];

	x0 = x0 * 16 + alScrnVar.ofs_x - 8;
	y0 = y0 * 16 + alScrnVar.ofs_y - 8;
	x1 = x1 * 16 + alScrnVar.ofs_x - 8;
	y1 = y1 * 16 + alScrnVar.ofs_y - 8;
	xys[0] = x0 | ((long)y0 << 16) | ((long)z << 32);
	xys[1] = x1 | ((long)y0 << 16) | ((long)z << 32);
	xys[2] = x0 | ((long)y1 << 16) | ((long)z << 32);
	xys[3] = x1 | ((long)y1 << 16) | ((long)z << 32);
	DrawScreenGQuad(xys, rgbas);
}

GAME_SECTION(DrawTextShadow) void DrawTextShadow(int top, int bot, int left, int right, int alpha, int rgb)
{
	int overlayRgba = alpha << 24 | rgb;

	DrawRectOverlay(top, bot, left, right, overlayRgba);
	DrawRectOverlay(top + 1, bot - 1, left - 2, left, overlayRgba);
	DrawRectOverlay(top + 2, bot - 2, left - 3, left - 2, overlayRgba);
	DrawRectOverlay(top + 4, bot - 4, left - 4, left - 3, overlayRgba);
	DrawRectOverlay(top + 1, bot - 1, right, right + 2, overlayRgba);
	DrawRectOverlay(top + 2, bot - 2, right + 2, right + 3, overlayRgba);
	DrawRectOverlay(top + 4, bot - 4, right + 3, right + 4, overlayRgba);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_0044AD00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", FastDrawStripInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", func_0044B058);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw", Screen_FadeOut);
