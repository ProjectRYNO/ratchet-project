#include "common.h"
#include "game_section.h"


extern int *vu1_bufPtr __asm__("vu1_bufPtr");
int g_SandStormFlag __asm__("D_2209DC") GAME_GP_DATA = 0;
void PostEffects_Init_new() __asm__("PostEffects_Init_new");
void PostEffects_Blur(int, int, int, int, int) __asm__("PostEffects_Blur");
void PostEffects_BlurOnce(int, int, int, int, int) __asm__("PostEffects_BlurOnce");
void PostEffects_RegisterEngine_Blur(int, int, int, int, int, int) __asm__("PostEffects_RegisterEngine_Blur");
void PostEffects_Init() __asm__("PostEffects_Init");
void PostEffects_LocalAlloc(int *ptr, int size) __asm__("PostEffects_LocalAlloc");
void PostEffects_Blur256(int a, int b, int c) __asm__("PostEffects_Blur256");
void PostEffects_BlurOnce256(int a, int b, int c) __asm__("PostEffects_BlurOnce256");
void PostEffects_RegisterEngine_Blur64(int a, int b, int c, int d) __asm__("PostEffects_RegisterEngine_Blur64");
void PostEffects_RegisterEngine_Blur128(int a, int b, int c, int d) __asm__("PostEffects_RegisterEngine_Blur128");
void PostEffects_RegisterEngine_Blur256(int a, int b, int c, int d) __asm__("PostEffects_RegisterEngine_Blur256");
int PostEffects_LocalAlloc(int &, int) __asm__("PostEffects_LocalAlloc");
void PostEffects_RegisterEngine_Blur256(unsigned long *&, int &, int, int) __asm__("PostEffects_RegisterEngine_Blur256");
void PostEffects_RegisterEngineCleanup() __asm__("PostEffects_RegisterEngineCleanup");
int PE_GetEnvironmentType() __asm__("PE_GetEnvironmentType");



void *MobyGetInterface(int, int) __asm__("MobyGetInterface");
void ComposeCameraMatrix() __asm__("ComposeCameraMatrix");
void InitSnowParticles() __asm__("InitSnowParticles");
void PE_UpdateEnvEffectsForCameraWarp(void *camera) __asm__("PE_UpdateEnvEffectsForCameraWarp");

struct PESandStorm {
	/* 0x00 */ char unk00[0x57];
	/* 0x57 */ unsigned char cDepthOfFieldA;
	/* 0x58 */ char unk58[0x10];
	/* 0x68 */ unsigned char sandTexture[8];
};
PESandStorm *PE_pSandStorm __asm__("PE_pSandStorm") GAME_GP_DATA = 0;
unsigned char PE_bHeroOutdoors __asm__("PE_bHeroOutdoors") GAME_GP_DATA = 0;
int g_iDofPalette __asm__("D_220A1C") GAME_GP_DATA = 0;
extern int g_SandStormApplySize __asm__("g_SandStormApplySize");
extern int g_pSandStormTemp1 __asm__("D_21DF18");
extern int g_pSandStormTex __asm__("g_pSandStormTex");
extern int g_pSandStormPal __asm__("D_21DF10");
extern int g_pSandStormSrc __asm__("D_21DF14");
extern int g_PostEffectsFlags __asm__("g_PostEffectsFlags");
struct GsMemDef {
	/* 0x00 */ int unk00;
	/* 0x04 */ int draw;
	/* 0x08 */ int unk08[6];
};
extern GsMemDef GSmem __asm__("GSmem");
extern unsigned int g_DofPalette[2][256] __asm__("g_DofPalette");
struct AABuffDef {
	/* 0x000 */ char unk000[0x150];
	/* 0x150 */ short drawW;
	/* 0x152 */ short drawH;
	/* 0x154 */ int unk154[3];
};
extern AABuffDef aaBuff __asm__("aaBuff");
struct PEInfo {
	/* 0x00 */ int unk00[2];
	/* 0x08 */ int m_PrevScreenW;
	/* 0x0c */ int m_PrevScreenH;
	/* 0x10 */ float m_PrevPane_sx;
	/* 0x14 */ float m_PrevPane_sy;
	/* 0x18 */ int unk18[2];
};
extern PEInfo g_PeInfo __asm__("g_PeInfo");
extern int g_PostEffectsSrcH __asm__("g_PostEffectsSrcH");
extern int g_PostEffectsSrcW __asm__("g_PostEffectsSrcW");
extern unsigned long g_PostEffects_Common_new[10] __asm__("g_PostEffects_Common_new");
extern int g_PostEffectsCommonSize_new __asm__("D_21DF1C");
extern int g_pBloomTex1 __asm__("g_pBloomTex1");
extern int g_pBloomTemp1 __asm__("g_pBloomTemp1");
extern int g_pBloomTemp2 __asm__("g_pBloomTemp2");
void PostEffects_SandStorm_Init_Globals() __asm__("PostEffects_SandStorm_Init_Globals");
void PostEffects_SandStorm_Init_AlphaMappingPalette() __asm__("PostEffects_SandStorm_Init_AlphaMappingPalette");
void PostEffects_SandStorm_Init_CreateB() __asm__("PostEffects_SandStorm_Init_CreateB");
void PostEffects_FrameInit_new() __asm__("PostEffects_FrameInit_new");
void PostEffects_RegisterEngine_AddFilterCopy(unsigned long *&, int &, int, int, int, int, int, int) __asm__("PostEffects_RegisterEngine_AddFilterCopy___dupe2");
void PostEffects_SandStorm_Init_Apply() __asm__("PostEffects_SandStorm_Init_Apply");
void PostEffects_SandStorm_Init() __asm__("PostEffects_SandStorm_Init");
void PostEffects_SetDofRamp(unsigned char *) __asm__("PostEffects_SetDofRamp");
void PostEffects_CommonInit_new() __asm__("PostEffects_CommonInit_new");
void PostEffects_RegisterEngine_BloomInitApply_new(unsigned long *&, int &) __asm__("PostEffects_RegisterEngine_BloomInitApply_new");

/* ===== AL additions ===== */
typedef unsigned int alQword[4];
void FastMemCopy(void *, const void *, int) __asm__("FastMemCopy");
extern char FastPalTrns_8[] __asm__("FastPalTrns_8");
extern char Gif_Tex_Flush[] __asm__("Gif_Tex_Flush");
extern int g_pDofTemp1 __asm__("g_pDofTemp1");
extern int g_pDofTex __asm__("g_pDofTex");
extern int g_pDofPal __asm__("g_pDofPal");
extern int g_pDofSrc __asm__("g_pDofSrc");
void PostEffects_DofInitCreateB_new() __asm__("PostEffects_DofInitCreateB_new");
void PostEffects_DofInit_new() __asm__("PostEffects_DofInit_new");
void PostEffects_LoadPalToGs_imm(int, void *) __asm__("PostEffects_LoadPalToGs_imm");
extern int g_BloomApplySize_new __asm__("g_BloomApplySize_new");
extern int g_BloomApplySize_vu1 __asm__("g_BloomApplySize_vu1");
extern unsigned long g_BloomApply_new[] __asm__("g_BloomApply_new");
extern int g_RegEngBase __asm__("g_RegEngBase");
int g_BloomApply1A __asm__("g_BloomApply1A") GAME_GP_DATA = 0;
int g_BloomTexOffset __asm__("g_BloomTexOffset") GAME_GP_DATA = 0;
void PostEffects_AddPutToScreen_imm(int, int, int, bool, bool, int, int, int) __asm__("PostEffects_AddPutToScreen_imm");
void PostEffects_BloomApply_new() __asm__("PostEffects_BloomApply_new");
extern unsigned long g_DofCreateB_new[] __asm__("g_DofCreateB_new");
extern int g_DofCreateSizeB_new __asm__("g_DofCreateSizeB_new");
int g_RegEngResident __asm__("g_RegEngResident") GAME_GP_DATA = 0;
extern unsigned short regeng_mpg_qwc __asm__("D_118150");
extern char regeng_mpg[] __asm__("D_118160");
extern char regeng_vu_addr[] __asm__("D_3E80");
void VU1_addDataRef(void *, int) __asm__("VU1_addDataRef");
void PostEffects_RegisterEngineInit() __asm__("PostEffects_RegisterEngineInit");
extern unsigned int PE_sandStormPal[256] __asm__("PE_sandStormPal");
float Lerp(float, float, float) __asm__("Lerp___dupe2");

extern int g_BloomTexEnd __asm__("g_BloomTexEnd");
extern int g_pBloomPal __asm__("g_pBloomPal");
extern int g_pBloomTex2 __asm__("g_pBloomTex2");
extern int g_pBloomTempCopy __asm__("g_pBloomTempCopy");
extern int g_pBloomSrc __asm__("g_pBloomSrc");
extern unsigned int g_BloomPal[256] __asm__("g_BloomPal");
extern unsigned long g_BloomCreateA_new[] __asm__("g_BloomCreateA_new");
extern unsigned long g_BloomCreateC_new[] __asm__("g_BloomCreateC_new");
extern int g_BloomCreateSizeA_new __asm__("g_BloomCreateSizeA_new");
extern int g_BloomCreateSizeA_vu1 __asm__("g_BloomCreateSizeA_vu1");
extern int g_BloomCreateSizeC_new __asm__("g_BloomCreateSizeC_new");
extern int g_BloomCreateSizeC_vu1 __asm__("g_BloomCreateSizeC_vu1");
void PostEffects_RegisterEngine_BloomInitCreateA_new(unsigned long *&, int &) __asm__("PostEffects_RegisterEngine_BloomInitCreateA_new");
void PostEffects_RegisterEngine_BloomInitCreateC_new(unsigned long *&, int &) __asm__("PostEffects_RegisterEngine_BloomInitCreateC_new");
void PostEffects_BloomInit_new() __asm__("PostEffects_BloomInit_new");
void PostEffects_BloomCreateB_new(unsigned long *&, int &) __asm__("PostEffects_BloomCreateB_new");
void PostEffects_BloomCreate_new() __asm__("PostEffects_BloomCreate_new");
struct alPEInfo {
	/* 0x00 */ int unk00[6];
	/* 0x18 */ int m_ScreenW;
	/* 0x1c */ int m_ScreenH;
	/* 0x20 */ int unk20[3];
	/* 0x2c */ int m_PaneW;
	/* 0x30 */ int m_PaneH;
	/* 0x34 */ int m_Pane_x1;
	/* 0x38 */ int m_Pane_y1;
	/* 0x3c */ int m_Pane_x2;
	/* 0x40 */ int m_Pane_y2;
};
extern alPEInfo alPeInfo __asm__("g_PeInfo");
struct alScrnDef {
	/* 0x00 */ int size_x;
	/* 0x04 */ int size_y;
	/* 0x08 */ int unk08[2];
	/* 0x10 */ int ofs_x;
	/* 0x14 */ int ofs_y;
};
extern alScrnDef alScrn __asm__("Scrn");
unsigned char bTemp_ShowDestAlpha_2866 __asm__("bTemp_ShowDestAlpha_2866") GAME_GP_DATA = 0;
void PostEffects_DofCreateA_new() __asm__("PostEffects_DofCreateA_new");
void PostEffects_CreateFrameBufferAlphaFromDepth_imm() __asm__("PostEffects_CreateFrameBufferAlphaFromDepth_imm");
void PostEffects_AddRemapAlpha_imm(int, int, int, int, int, int, int, int, int) __asm__("PostEffects_AddRemapAlpha_imm");
void VU1_addGSregister(unsigned int, unsigned long, bool) __asm__("VU1_addGSregister");
void PostEffects_DofCreate_new() __asm__("PostEffects_DofCreate_new");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_LocalAlloc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_AddStrips);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_AddStrips);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_AddStrips___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F6940);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_Clear);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F6AE0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_AddFilterCopy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_AddFilterCopy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_AddFilterCopy___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_Blur);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_Blur);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_BlurOnce);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F7A40);

GAME_SECTION(PostEffects_Blur256) void PostEffects_Blur256(int a, int b, int c)
{
	PostEffects_Blur(a, b, 0x100, 0x100, c);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F7A70);

GAME_SECTION(PostEffects_BlurOnce256) void PostEffects_BlurOnce256(int a, int b, int c)
{
	PostEffects_BlurOnce(a, b, 0x100, 0x100, c);
}

GAME_SECTION(PostEffects_RegisterEngine_Blur256) void PostEffects_RegisterEngine_Blur256(int a, int b, int c, int d)
{
	PostEffects_RegisterEngine_Blur(a, b, c, 0x100, 0x100, d);
}

GAME_SECTION(PostEffects_RegisterEngine_Blur128) void PostEffects_RegisterEngine_Blur128(int a, int b, int c, int d)
{
	PostEffects_RegisterEngine_Blur(a, b, c, 0x80, 0x80, d);
}

GAME_SECTION(PostEffects_RegisterEngine_Blur64) void PostEffects_RegisterEngine_Blur64(int a, int b, int c, int d)
{
	PostEffects_RegisterEngine_Blur(a, b, c, 0x40, 0x40, d);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F7B38);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_AddBloomAccum);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F7EA0);

GAME_SECTION(PostEffects_SandStorm_Init_AlphaMappingPalette) void PostEffects_SandStorm_Init_AlphaMappingPalette()
{
	int i;
	float fFrac;
	unsigned char Ramp[256];
	int ci;

	for (i = 0; i < 0x100; i++) {
		fFrac = 1.0f - (float)i / 255.0f;
		Ramp[i] = (int)Lerp((float)i, (1.0f - fFrac * fFrac) * 255.0f, 0.8f);
	}
	for (i = 0; i < 0x100; i++) {
		ci = (i & 0xe7) | (i & 8) << 1 | (i & 0x10) >> 1;
		PE_sandStormPal[ci] = ((0xff - Ramp[i]) >> 1) << 24;
	}
	FlushCache(0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F7FD0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_SandStorm_Init_CreateB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F81D8);

GAME_SECTION(PostEffects_SandStorm_Init_Apply) void PostEffects_SandStorm_Init_Apply()
{
	g_SandStormApplySize = 0;
	if ((PE_pSandStorm->cDepthOfFieldA || PE_pSandStorm->sandTexture[0]) && PE_bHeroOutdoors && PE_pSandStorm->cDepthOfFieldA) {
		g_SandStormApplySize = 1;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_SandStorm_Init_Globals);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F8600);

GAME_SECTION(PostEffects_SandStorm_Init) void PostEffects_SandStorm_Init()
{
	int LocalGsLoc = 0x37e000;
	g_pSandStormTemp1 = PostEffects_LocalAlloc(LocalGsLoc, 0x40000);
	g_pSandStormTex = PostEffects_LocalAlloc(LocalGsLoc, 0x40000);
	g_pSandStormPal = PostEffects_LocalAlloc(LocalGsLoc, 0x400);
	g_pSandStormSrc = GSmem.draw;
	PostEffects_SandStorm_Init_Globals();
	PostEffects_SandStorm_Init_AlphaMappingPalette();
	PostEffects_SandStorm_Init_CreateB();
	PostEffects_SandStorm_Init_Apply();
	g_PostEffectsFlags |= 4;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F86A0);

GAME_SECTION(PE_GetEnvironmentType) int PE_GetEnvironmentType()
{
	switch (g_SandStormFlag) {
	case 1:
	case 2:
		return 1;
	case 3:
	case 4:
		return 2;
	case 5:
	case 0xb:
	case 0x10:
		return 3;
	default:
		return 0;
	}
}

GAME_SECTION(PE_UpdateEnvEffectsForCameraWarp) void PE_UpdateEnvEffectsForCameraWarp(void *camera)
{
	char *iface = (char *)MobyGetInterface(0x2022, 0x50);
	if (iface) {
		(*(void (**)(void *))(iface + 0x44))(camera);
		ComposeCameraMatrix();
		InitSnowParticles();
	}
}

GAME_SECTION(PostEffects_Init) void PostEffects_Init()
{
	PostEffects_Init_new();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_AddPutToScreen_imm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_CreateFrameBufferAlphaFromDepth_imm);

extern alQword *alVu1 __asm__("vu1_bufPtr");
GAME_SECTION(PostEffects_LoadPalToGs_imm) void PostEffects_LoadPalToGs_imm(int pPalGS_, void *pPal_)
{
	unsigned char *pc;
	alQword *q;

	FastMemCopy(alVu1, FastPalTrns_8, 0x70);
	pc = (unsigned char *)alVu1;
	*(short *)(pc + 0x24) = pPalGS_ >> 8;
	*(int *)(pc + 0x64) = (int)pPal_;
	q = alVu1 + 7;
	alVu1 = q;
	(*q)[0] = 0x30000003;
	(*q)[1] = (unsigned int)Gif_Tex_Flush;
	(*q)[2] = 0;
	(*q)[3] = 0x50000003;
	alVu1 = alVu1 + 1;
}

GAME_SECTION(PostEffects_SetDofRamp) void PostEffects_SetDofRamp(unsigned char *Ramp_)
{
	int i;
	unsigned int *pDofPalette;
	g_iDofPalette ^= 1;
	pDofPalette = g_DofPalette[g_iDofPalette];
	for (i = 0; i < 0x100; i++) {
		int ci = (i & 0xe7) | ((i & 8) << 1) | ((i & 0x10) >> 1);
		pDofPalette[ci] = ((0xff - Ramp_[i]) >> 1) << 24;
	}
	FlushCache(0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_AddRemapAlpha);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_AddRemapAlpha);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_AddRemapAlpha_imm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F9768);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_AddMulByAlpha);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_Init_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_FrameInit_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_CommonInit_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_BloomInit_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_BloomInitCreateA_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_BloomCreateB_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_BloomInitCreateC_new);

GAME_SECTION(PostEffects_RegisterEngine_BloomInitApply_new) void PostEffects_RegisterEngine_BloomInitApply_new(unsigned long *&pCurrent, int &RegEngBase)
{
	PostEffects_RegisterEngine_AddFilterCopy(pCurrent, RegEngBase, g_pBloomTex1, 0x40, 0x40, g_pBloomTemp2, 0x80, 0x80);
	PostEffects_RegisterEngine_AddFilterCopy(pCurrent, RegEngBase, g_pBloomTemp2, 0x80, 0x80, g_pBloomTemp1, 0x100, 0x100);
	PostEffects_RegisterEngine_Blur256(pCurrent, RegEngBase, g_pBloomTemp1, g_pBloomTemp2);
}

GAME_SECTION(PostEffects_BloomCreate_new) void PostEffects_BloomCreate_new()
{
	unsigned long *pCurrent;
	int RegEngBase;

	g_BloomTexOffset = 0x6000;
	(*alVu1)[0] = g_BloomCreateSizeA_new >> 4 | 0x30000000;
	(*alVu1)[1] = (unsigned int)g_BloomCreateA_new;
	(*alVu1)[2] = g_RegEngBase | 0x3000000;
	(*alVu1)[3] = 0x2000000;
	RegEngBase = 0;
	alVu1 = alVu1 + 1;
	pCurrent = (unsigned long *)(alVu1 + 1);
	g_RegEngBase = g_RegEngBase + g_BloomCreateSizeA_vu1;
	PostEffects_BloomCreateB_new(pCurrent, RegEngBase);
	(*alVu1)[0] = ((int)pCurrent + (-0x10 - (int)alVu1)) >> 4 | 0x10000000;
	(*alVu1)[2] = g_RegEngBase | 0x3000000;
	(*alVu1)[3] = 0x2000000;
	g_RegEngBase = g_RegEngBase + RegEngBase;
	alVu1 = (alQword *)pCurrent;
	PostEffects_LoadPalToGs_imm(g_pBloomPal, g_BloomPal);
	(*alVu1)[0] = g_BloomCreateSizeC_new >> 4 | 0x30000000;
	(*alVu1)[1] = (unsigned int)g_BloomCreateC_new;
	(*alVu1)[2] = g_RegEngBase | 0x3000000;
	(*alVu1)[3] = 0x2000000;
	g_RegEngBase = g_RegEngBase + g_BloomCreateSizeC_vu1;
	alVu1 = alVu1 + 1;
}

GAME_SECTION(PostEffects_BloomApply_new) void PostEffects_BloomApply_new()
{
	(*alVu1)[0] = g_BloomApplySize_new >> 4 | 0x30000000;
	(*alVu1)[1] = (unsigned int)g_BloomApply_new;
	(*alVu1)[2] = g_RegEngBase | 0x3000000;
	(*alVu1)[3] = 0x2000000;
	g_RegEngBase = g_RegEngBase + g_BloomApplySize_vu1;
	alVu1 = alVu1 + 1;
	PostEffects_AddPutToScreen_imm(g_pBloomTemp1, 0x100, 0x100, true, false, g_BloomApply1A, 0x808080, 0xffffff);
	g_BloomTexOffset = 0;
}

GAME_SECTION(PostEffects_DofInit_new) void PostEffects_DofInit_new()
{
	int LocalGsLoc;
	unsigned char Ramp[256];
	int i;

	LocalGsLoc = 0x37e000;
	g_pDofTemp1 = PostEffects_LocalAlloc(LocalGsLoc, 0x40000);
	g_pDofTex = PostEffects_LocalAlloc(LocalGsLoc, 0x40000);
	g_pDofPal = PostEffects_LocalAlloc(LocalGsLoc, 0x400);
	g_pDofSrc = GSmem.draw;
	PostEffects_DofInitCreateB_new();
	g_iDofPalette = 0;
	{
		unsigned char *p;
		i = 0xff;
		p = Ramp + 0xff;
		do {
			*p = i;
			i--;
			p--;
		} while (i >= 0);
	}
	PostEffects_SetDofRamp(Ramp);
	g_PostEffectsFlags |= 2;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_DofCreateA_new);

void PostEffects_Blur256(unsigned long **, int, int) __asm__("PostEffects_Blur256");
GAME_SECTION(PostEffects_DofInitCreateB_new) void PostEffects_DofInitCreateB_new()
{
	unsigned long *pCurrent;

	g_DofCreateB_new[0] = 0x1000000000000005;
	g_DofCreateB_new[1] = 0xe;
	g_DofCreateB_new[3] = 0x3f;
	g_DofCreateB_new[4] = 0xa0000000a0;
	g_DofCreateB_new[5] = 0x19;
	g_DofCreateB_new[6] = 0x100000000;
	g_DofCreateB_new[7] = 0x4f;
	g_DofCreateB_new[8] = 0x60;
	g_DofCreateB_new[9] = 0x15;
	g_DofCreateB_new[10] = 5;
	g_DofCreateB_new[0xb] = 9;
	pCurrent = g_DofCreateB_new + 0xc;
	g_DofCreateB_new[2] = 0;
	PostEffects_Blur256(&pCurrent, g_pDofTex, g_pDofTemp1);
	PostEffects_Blur256(&pCurrent, g_pDofTex, g_pDofTemp1);
	g_DofCreateSizeB_new = (char *)pCurrent - (char *)g_DofCreateB_new;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_DofCreate_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_FbCopyInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_GetFbTex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngineInit);

GAME_SECTION(PostEffects_RegisterEngineCleanup) void PostEffects_RegisterEngineCleanup()
{
	vu1_bufPtr[0] = 0x10000000;
	vu1_bufPtr[2] = 0x20000000;
	vu1_bufPtr[3] = 0;
	vu1_bufPtr += 4;
}
