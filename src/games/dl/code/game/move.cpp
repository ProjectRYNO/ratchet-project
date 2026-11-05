#include "common.h"
#include "game_section.h"


typedef int s128 __attribute__((mode(TI)));
struct vec4 {
	/* 0x00 */ s128 q;
};
struct moby {
	/* 0x00 */ char unk00[0x10];
	/* 0x10 */ vec4 pos;
	/* 0x20 */ unsigned char bits;
	/* 0x21 */ char unk21[3];
	/* 0x24 */ void *pClass;
	/* 0x28 */ char unk28[0x34 - 0x28];
	/* 0x34 */ unsigned short state;
	/* 0x36 */ char unk36[0x58 - 0x36];
	/* 0x58 */ char *pJoints;
	/* 0x5c */ char unk5c[0xbc - 0x5c];
	/* 0xbc */ short oClass;
	/* 0xbe */ char unkbe[0x100 - 0xbe];
};
struct MoveVars_V2 {
	/* 0x000 */ unsigned int flagsA;
	/* 0x004 */ unsigned int flags;
	/* 0x008 */ int unk008;
	/* 0x00c */ int dirty;
	/* 0x010 */ char unk010[0x20];
	/* 0x030 */ unsigned char elevation;
	/* 0x031 */ unsigned char unk031;
	/* 0x032 */ unsigned char reaction;
	/* 0x033 */ unsigned char action;
	/* 0x034 */ char unk034[0xd4 - 0x34];
	/* 0x0d4 */ float standSpeed;
	/* 0x0d8 */ char unk0d8[0x104 - 0xd8];
	/* 0x104 */ float damper;
};
struct COLL_DAM_OUT;
MoveVars_V2 *MB_GetMoveVars(moby *) __asm__("MB_GetMoveVars_2");
float MobyMayaFrame(moby *) __asm__("MobyMayaFrame");
void FUN_00481298(moby *, float &, float *, vec4 *, char *, COLL_DAM_OUT *) __asm__("FUN_00481298");
int MB_Move_2(moby *, s128, float, float, int) __asm__("MB_Move_2");
void MVE_SpawnLavaSplash(moby *, MoveVars_V2 *) __asm__("MVE_SpawnLavaSplash");
float MB_IncomingAnimationMayaFrame(moby *) __asm__("MB_IncomingAnimationMayaFrame");
int MB_GetMoveAction(moby *) __asm__("MB_GetMoveAction");
int MB_GetMoveElevation(moby *) __asm__("MB_GetMoveElevation");
int MB_GetMoveReaction(moby *) __asm__("MB_GetMoveReaction");
void MB_ProcessDamage_2(moby *, float &, COLL_DAM_OUT *) __asm__("MB_ProcessDamage_2");
float MB_GetMoveDamper(moby *) __asm__("MB_GetMoveDamper");
int MB_SetMoveElevation(moby *, int) __asm__("MB_SetMoveElevation");
int MB_Stand_2(moby *) __asm__("MB_Stand_2");
int MB_StopReaction_2(moby *) __asm__("MB_StopReaction_2");



int MB_UpdateReaction(moby *) __asm__("MB_UpdateReaction_2");
void FUN_00484710(moby *, int, int) __asm__("FUN_00484710");
int MB_SetMoveDamper(moby *, float, int) __asm__("MB_SetMoveDamper");
int MB_SetMoveAngularSpeeds(moby *, float, float, float) __asm__("MB_SetMoveAngularSpeeds");
int MB_SetMoveDistanceThresholds(moby *, float, float, float, float) __asm__("MB_SetMoveDistanceThresholds");
int MB_SetMoveSpeedLimits(moby *, float, float, float, float, float, float, float) __asm__("MB_SetMoveSpeedLimits");
void MB_MoveSystemUpdateReaction(moby *) __asm__("MB_MoveSystemUpdateReaction");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_Move_2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", func_00480EB8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_Move_2___dupe2);

GAME_SECTION(MB_Stand_2) int MB_Stand_2(moby *pMoby)
{
	MoveVars_V2 *pVars = MB_GetMoveVars(pMoby);
	int ret;
	if (pVars) ret = MB_Move_2(pMoby, pMoby->pos.q, 0.0f, pVars->standSpeed, 0);
	else ret = 0;
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", func_00480F90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_Action_2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_StopAction_2);

GAME_SECTION(MB_StopReaction_2) int MB_StopReaction_2(moby *pMoby)
{
	MoveVars_V2 *pVars = MB_GetMoveVars(pMoby);
	if (!pVars) return 0;
	if (pVars->reaction >= 5) return 0;
	pVars->dirty = 1;
	pVars->flags |= 0x800;
	pVars->reaction = 0;
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", FUN_00481298);

GAME_SECTION(MB_ProcessDamage_2) void MB_ProcessDamage_2(moby *pMoby, float &hpDamage, COLL_DAM_OUT *cdo)
{
	char hitPart;
	float friendDamage;
	vec4 hitPos;
	FUN_00481298(pMoby, hpDamage, &friendDamage, &hitPos, &hitPart, cdo);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_UpdateReaction_2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", func_00483330);

GAME_SECTION(MB_GetMoveAction) int MB_GetMoveAction(moby *pMoby)
{
	MoveVars_V2 *pVars = MB_GetMoveVars(pMoby);
	if (!pVars) return 0;
	return pVars->action;
}

GAME_SECTION(MB_GetMoveReaction) int MB_GetMoveReaction(moby *pMoby)
{
	MoveVars_V2 *pVars = MB_GetMoveVars(pMoby);
	if (!pVars) return 0;
	return pVars->reaction;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", func_00483390);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MVE_GetBoundArea);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MVE_DrawImpactEffect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", func_00483648);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MVE_GetGroundInfo2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MVE_Collision2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_MoveSystemInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_InitCache);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_SetAnimCache);

GAME_SECTION(MB_IncomingAnimationMayaFrame) float MB_IncomingAnimationMayaFrame(moby *pMoby)
{
	return MobyMayaFrame(pMoby);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_IncomingMayaFrameTrigger);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_SwitchToDeathState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", FUN_00484710);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_MoveSystemUpdateAction);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", func_00485198);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_UpdateReactionEffects);

GAME_SECTION(MB_MoveSystemUpdateReaction) void MB_MoveSystemUpdateReaction(moby *pMoby)
{
	int r = MB_UpdateReaction(pMoby);
	if (r & 1) {
		if (r & 2) FUN_00484710(pMoby, -1, 1);
	} else if (r & 2) {
		MB_StopReaction_2(pMoby);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_MoveSystemUpdateAttach);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MVE_SpawnWaterSplash);

GAME_SECTION(MVE_SpawnLavaSplash) void MVE_SpawnLavaSplash(moby *pMoby, MoveVars_V2 *pMoveVars)
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MVE_SpawnHitGroundDust);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_UpdateMoveEffects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_MoveSystemUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_SetMoveAnim);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_GetBestAnimSlow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_UseLinearAnim);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_GetBestAnimFast);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", func_004887B0);

GAME_SECTION(MB_SetMoveElevation) int MB_SetMoveElevation(moby *pMoby, int elev)
{
	MoveVars_V2 *pVars = MB_GetMoveVars(pMoby);
	int old;
	if (!pVars) return 0;
	old = pVars->elevation;
	if (old != elev) {
		pVars->elevation = elev;
		pVars->dirty = 1;
	}
	return old;
}

GAME_SECTION(MB_GetMoveElevation) int MB_GetMoveElevation(moby *pMoby)
{
	MoveVars_V2 *pVars = MB_GetMoveVars(pMoby);
	if (!pVars) return -1;
	return pVars->elevation;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", func_00488850);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_SetMoveDistanceThresholds);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_SetMoveSpeedLimits);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_SetMoveAngularSpeeds);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_SetMoveDamper);

GAME_SECTION(MB_GetMoveDamper) float MB_GetMoveDamper(moby *pMoby)
{
	MoveVars_V2 *pVars = MB_GetMoveVars(pMoby);
	float ret = 1.0f;
	if (pVars && (pVars->flagsA & 0x20)) ret = pVars->damper;
	return ret;
}
