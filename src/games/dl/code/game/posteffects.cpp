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
void PostEffects_RegisterEngineCleanup() __asm__("PostEffects_RegisterEngineCleanup");
int PE_GetEnvironmentType() __asm__("PE_GetEnvironmentType");



void *MobyGetInterface(int, int) __asm__("MobyGetInterface");
void ComposeCameraMatrix() __asm__("ComposeCameraMatrix");
void InitSnowParticles() __asm__("InitSnowParticles");
void PE_UpdateEnvEffectsForCameraWarp(void *camera) __asm__("PE_UpdateEnvEffectsForCameraWarp");

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_SandStorm_Init_Apply);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_SandStorm_Init_Globals);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", func_004F8600);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_SandStorm_Init);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_SetDofRamp);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/posteffects", PostEffects_RegisterEngine_BloomInitApply_new);

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
