#include "common.h"
#include "game_section.h"


typedef unsigned int s128 __attribute__((mode(TI)));
struct MobyInstance {
	/* 0x00 */ char unk00[0x34];
	/* 0x34 */ unsigned short modeBits;
	/* 0x36 */ char unk36[0xac - 0x36];
	/* 0xac */ void *pVar;
};
struct SubVars {
	/* 0x00 */ int unk00[2];
	/* 0x08 */ void *trackVars;
	/* 0x0c */ void *bogeyVars;
	/* 0x10 */ void *reactVars;
	/* 0x14 */ int unk14[2];
	/* 0x1c */ void *moveVars;
	/* 0x20 */ int unk20[3];
	/* 0x2c */ void *commandVars;
	/* 0x30 */ int unk30;
	/* 0x34 */ void *flashVars;
	/* 0x38 */ void *suckVars;
	/* 0x3c */ void *navigationVars;
};
struct TargetVars {
	/* 0x00 */ char unk00[0x2c];
	/* 0x2c */ short bogeyType;
};
struct BotSaveDef {
	/* 0x00 */ unsigned char botUpgrades[0x11];
	/* 0x11 */ unsigned char botPaintjobs[0xb];
	/* 0x1c */ unsigned char botHeads[8];
	/* 0x24 */ unsigned char curBotPaintJob[2];
	/* 0x26 */ unsigned char curBotHead[2];
	/* 0x28 */ char unk28[0x40];
};
struct BotAbility {
	/* 0x00 */ int unk00[4];
};
struct Bot_Communication {
	/* 0x000 */ unsigned char initialized;
	/* 0x001 */ char unk001[0x1f3];
	/* 0x1f4 */ unsigned char botAbilities[0x11];
};
struct MotionBlur {
	/* 0x000 */ char unk000[0x140];
	/* 0x140 */ short ringIndex;
	/* 0x142 */ short ringValidSize;
	/* 0x144 */ MobyInstance *pTrackedMoby;
	/* 0x148 */ int blurCnt;
	/* 0x14c */ int active;
};
struct FlashVars;
extern BotSaveDef BotSave __asm__("BotSave");
extern BotAbility Bot_AbilityDefinitions[] __asm__("D_3D8B60");
extern Bot_Communication Bot_Comm_Instance __asm__("Bot_Comm_Instance");
extern unsigned char CheatsActivated[] __asm__("CheatsActivated");
TargetVars *MB_getTargetVars(MobyInstance *) __asm__("MB_getTargetVars");
void MB_StartColorFlash(MobyInstance *, int, int, FlashVars *) __asm__("MB_StartColorFlash");
void SetMobyAmbientLights(MobyInstance *, int, int, int) __asm__("SetMobyAmbientLights");
float GetGroundZ(s128, int, float, MobyInstance *, float) __asm__("GetGroundZ");
void Bot_ResetGlobalComm() __asm__("Bot_ResetGlobalComm");
BotAbility *Bot_GetAbilityDef(unsigned int) __asm__("Bot_GetAbilityDef");
int Bot_GetCurrentPaintjob(unsigned int) __asm__("Bot_GetCurrentPaintjob");
bool Bot_HasHead(unsigned int) __asm__("Bot_HasHead");
bool Bot_HasPaintjob(unsigned int) __asm__("Bot_HasPaintjob");
void CreateMotionBlur(MobyInstance *, MotionBlur &) __asm__("CreateMotionBlur");
int Lerp(int, int, float) __asm__("Lerp");
int MB_GetBogeyType(MobyInstance *) __asm__("MB_GetBogeyType");
void MB_initMobyColorFlash(MobyInstance *, FlashVars &) __asm__("MB_initMobyColorFlash");
unsigned char Bot_HasAbility(int) __asm__("Bot_HasAbility");
float GetGroundZNoWater(s128) __asm__("GetGroundZNoWater");
void MB_SetAmbientLights(MobyInstance *, int) __asm__("MB_SetAmbientLights");
void MB_SetBogeyType(MobyInstance *, int) __asm__("MB_SetBogeyType");
void *MB_getReactVars(MobyInstance *) __asm__("MB_getReactVars");
float SubLerp(float, float, float) __asm__("SubLerp");
int Bot_GetCurrentHead(unsigned int) __asm__("Bot_GetCurrentHead");
Bot_Communication *Bot_GetGlobalComm() __asm__("Bot_GetGlobalComm");
float Delt(float &, float, float) __asm__("Delt");
void *MB_GetBogeyVars(MobyInstance *) __asm__("MB_GetBogeyVars");
void *MB_GetCommandVars(MobyInstance *) __asm__("MB_GetCommandVars");
void *MB_GetFlashVars(MobyInstance *) __asm__("MB_GetFlashVars");
void *MB_GetMoveVars_2(MobyInstance *) __asm__("MB_GetMoveVars_2");
void *MB_GetNavigationVars(MobyInstance *) __asm__("MB_GetNavigationVars");
void *MB_GetSuckVars(MobyInstance *) __asm__("MB_GetSuckVars");
void *MB_getTrackVars(MobyInstance *) __asm__("MB_getTrackVars");
void Bot_GrantAbility(int) __asm__("Bot_GrantAbility");
void Bot_GrantHead(unsigned int, int) __asm__("Bot_GrantHead");
float MB_WrapRot(float) __asm__("MB_WrapRot");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_QueueUpgradeScene);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_CheckQueuedUpgradeScene);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AddHoloshieldGadgetXP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_standardDeath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_BundleDamage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AllocateXPBundle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SpawnBolts);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_HandleBoltMultiplier);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_snapAnim);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_transAnim);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_transAnim___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00473A80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_setState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00473AD0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bias0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bias1);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00473B08);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_CubicInterpolate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_CubicInterpVec);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_CosineInterpolate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_CosineInterpolateUnit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00473CB8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_getJumpPeak);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SetOClass);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00473F20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SolveQuad);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", GetGroundZ);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00474088);

GAME_SECTION(GetGroundZNoWater) float GetGroundZNoWater(s128 pos)
{
	return GetGroundZ(pos, 0x20, 0.5f, 0, 32.0f);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004740C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", PointInsideComplexPoly);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SegmentIntersect2D);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00474290);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SetCollDamIn);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004742D0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", DamageSphereAtPos);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00474478);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CollDamageMobyDirect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CollDamageMobyDirect___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004746C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CollWaterHeight);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CollMovingSphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_RegisterLameShadow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00474DA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", TweenColor);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", _MB_damage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00474E18);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_computeLobVelocity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_randPrimPoints);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00475680);

GAME_SECTION(Lerp) int Lerp(int val0, int val1, float alpha)
{
	return val0 + (int)((float)(val1 - val0) * alpha);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Lerp___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Lerp___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00475708);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SubLerp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", GainDampLimit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00475798);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Delt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004757D8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SlideDelt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SlideDelt___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", AccelDelt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", AccelDelt___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", OrganicDelt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SubRots);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", DeltAng);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", AccelDeltAng);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00475EF8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", OrganicDeltAng);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", OrganicDeltSpeed);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MatAdjoint);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Float_To_RGBA);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", ReorderRGB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", ReorderRGB___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004765A0);

GAME_SECTION(MB_GetSuckVars) void *MB_GetSuckVars(MobyInstance *pMoby)
{
	void *r;
	if (!pMoby || !pMoby->pVar || !(pMoby->modeBits & 0x20)) r = 0;
	else r = ((SubVars *)pMoby->pVar)->suckVars;
	return r;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004765E8);

GAME_SECTION(MB_GetMoveVars_2) void *MB_GetMoveVars_2(MobyInstance *pMoby)
{
	void *r;
	if (!pMoby || !pMoby->pVar || !(pMoby->modeBits & 0x20)) r = 0;
	else r = ((SubVars *)pMoby->pVar)->moveVars;
	return r;
}

GAME_SECTION(MB_GetNavigationVars) void *MB_GetNavigationVars(MobyInstance *pMoby)
{
	void *r;
	if (!pMoby || !pMoby->pVar || !(pMoby->modeBits & 0x20)) r = 0;
	else r = ((SubVars *)pMoby->pVar)->navigationVars;
	return r;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_getReactVars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_getTargetVars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00476700);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_MistDeathEffect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SetDefaultLights);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CollLineValidate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", DecomposeMtx4ToAng);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetFlashVars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_StartColorFlash);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_EndColorFlash);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_UpdateColorFlash);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477648);

GAME_SECTION(MB_initMobyColorFlash) void MB_initMobyColorFlash(MobyInstance *pMoby, FlashVars &fv)
{
	MB_StartColorFlash(pMoby, 1, 0, &fv);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477678);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_WrapRot);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004776C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_isCrateOClass);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_isCrate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_isMorph);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004777C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_genericExplosion);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477A90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AddMobyToDynamicGroup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_DeleteMobyFromDynamicGroup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477B88);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_RandomizeVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_RandomizeVector___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_RandomizeVectorRange);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IsPntInCylinder);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IsPntInSphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IsPntInPath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477F30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SlerpVectors);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477FB8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_getTrackVars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_TrackMoby_OneFrame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_TrackMoby_OneFrame_Vel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004788E8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GadgetDamageIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_MP_GadgetDamageIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SetNtscPalTiming);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00478E20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_compressVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_decompressVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00478FD8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_MayaFrameTrigger);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004790B0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CreateMotionBlur);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", AddMotionBlurElem);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", UpdateMotionBlur);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", DeleteMotionBlur);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00479570);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SetAmbientLights);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004795B0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_BobMotion);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_BobMotion___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004796C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SwingMotion);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00479790);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AddVectorSphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00479818);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AttachMobyToJoint);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_ComputeTargetScore);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_getTarget);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", FUN_00479d28);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047AA28);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetLocalSpaceVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetWorldSpaceVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047AB20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_scaleRelativeXY);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_relativeXYComponent);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047AC20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_FindGravity_CageMatch);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_FindGravity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047ADE0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AddGravity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047AEA8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SphericalHeight);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AlignWithGravity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AlignWithNormal);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047B0F0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_DrawGlowFX);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047B2D0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_BlowCorn);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_BlowFlamingCorn);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047B7E8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", FUN_0047b7f8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047B978);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SpawnInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047BA28);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IsPntInArea);

GAME_SECTION(MB_GetBogeyVars) void *MB_GetBogeyVars(MobyInstance *pMoby)
{
	void *r;
	if (!pMoby || !pMoby->pVar || !(pMoby->modeBits & 0x20)) r = 0;
	else r = ((SubVars *)pMoby->pVar)->bogeyVars;
	return r;
}

GAME_SECTION(MB_GetBogeyType) int MB_GetBogeyType(MobyInstance *pMoby)
{
	TargetVars *tVars = MB_getTargetVars(pMoby);
	if (tVars == 0) return 0;
	return tVars->bogeyType;
}

GAME_SECTION(MB_SetBogeyType) void MB_SetBogeyType(MobyInstance *pMoby, int type)
{
	TargetVars *tVars = MB_getTargetVars(pMoby);
	if (tVars) tVars->bogeyType = type;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047BC68);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_UnlockBogey);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047BD18);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_FastBsphereCheck);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_PlaySoundsInSeq);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetCommandVars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047C050);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_InitializeCommandCache);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_DrawDestroyIcon);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_FindVisibleContextCommand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetCommandName);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047CE60);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IssueCommand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IssueCommand___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047D240);

GAME_SECTION(Bot_GetAbilityDef) BotAbility *Bot_GetAbilityDef(unsigned int a)
{
	BotAbility *r;
	if (a > 0x10) r = 0;
	else r = &Bot_AbilityDefinitions[a];
	return r;
}

GAME_SECTION(Bot_HasAbility) unsigned char Bot_HasAbility(int a)
{
	return Bot_GetGlobalComm()->botAbilities[a];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_HasCommandAbility);

GAME_SECTION(Bot_GrantAbility) void Bot_GrantAbility(int a)
{
	Bot_GetGlobalComm()->botAbilities[a] = 1;
	BotSave.botUpgrades[a] = 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_GrantPaintjob);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_HasPaintjob);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_GetCurrentPaintjob);

GAME_SECTION(Bot_GrantHead) void Bot_GrantHead(unsigned int headNum, int setAsCurrent)
{
	if (headNum < 8) {
		BotSave.botHeads[headNum] = 1;
		if (setAsCurrent & 1) BotSave.curBotHead[0] = headNum;
		if (setAsCurrent & 2) BotSave.curBotHead[1] = headNum;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_HasHead);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_GetCurrentHead);

GAME_SECTION(Bot_GetGlobalComm) Bot_Communication *Bot_GetGlobalComm()
{
	if (!Bot_Comm_Instance.initialized) Bot_ResetGlobalComm();
	return &Bot_Comm_Instance;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_ResetGlobalComm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047D6A8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetShadowSurface);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetRandomShadowPoints);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetRandomShadowSurfacePoint);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetRandomShadowSurfacePoints);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047EB40);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", FUN_0047eb50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", FUN_0047eb58);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SetMobyTeamTex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047EBB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SelectRespawnNode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_ValidateRespawnNode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_NumValidRespawnNodes);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GhostMe);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_Level99ColorTimeBased);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetXPBundle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047EEA8);
