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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_SandStorm_Init_AlphaMappingPalette);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_LoadPalToGs_imm);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_BloomCreate_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_BloomApply_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_DofInit_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_DofCreateA_new);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_DofInitCreateB_new);

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
