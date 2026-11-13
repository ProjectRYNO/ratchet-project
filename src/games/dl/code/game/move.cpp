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
	/* 0x36 */ char unk36[0x48 - 0x36];
	/* 0x48 */ float animSpeed;
	/* 0x4c */ char unk4c[0x54 - 0x4c];
	/* 0x54 */ unsigned char animSeqId;
	/* 0x55 */ unsigned char animFlags;
	/* 0x56 */ char unk56[0x58 - 0x56];
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
	/* 0x034 */ unsigned char unk034;
	/* 0x035 */ unsigned char lockAnim;
	/* 0x036 */ short numColl;
	/* 0x038 */ struct MoveVarsAnimCache *pAnimCache;
	/* 0x03c */ struct MoveVarsAnimCache *pAttachAnimCache;
	/* 0x040 */ char unk040[0x48 - 0x40];
	/* 0x048 */ int boundArea;
	/* 0x04c */ char unk04c[0x5c - 0x4c];
	/* 0x05c */ moby *pAttach;
	/* 0x060 */ char unk060[0x68 - 0x60];
	/* 0x068 */ float actionStartFrame;
	/* 0x06c */ void (*pActionCallback)(moby *, int);
	/* 0x070 */ char unk070[0x78 - 0x70];
	/* 0x078 */ float collRadius;
	/* 0x07c */ char unk07c[0x90 - 0x7c];
	/* 0x090 */ float stopDist;
	/* 0x094 */ float walkDist;
	/* 0x098 */ float runDist;
	/* 0x09c */ float walkSpeed;
	/* 0x0a0 */ float runSpeed;
	/* 0x0a4 */ float strafeSpeed;
	/* 0x0a8 */ float backSpeed;
	/* 0x0ac */ float flySpeed;
	/* 0x0b0 */ float linearAccel;
	/* 0x0b4 */ float linearDecel;
	/* 0x0b8 */ char unk0b8[0xc0 - 0xb8];
	/* 0x0c0 */ float angularAccel;
	/* 0x0c4 */ float angularDecel;
	/* 0x0c8 */ float angularLimit;
	/* 0x0cc */ float hitGroundSpeed;
	/* 0x0d0 */ char unk0d0[0xd4 - 0xd0];
	/* 0x0d4 */ float standSpeed;
	/* 0x0d8 */ char unk0d8[0xf8 - 0xd8];
	/* 0x0f8 */ float passThruSurface;
	/* 0x0fc */ int passThruSurfaceType;
	/* 0x100 */ char unk100[0x104 - 0x100];
	/* 0x104 */ float damper;
	/* 0x108 */ short moveDamperTimer;
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

struct ReactVars {
	/* 0x00 */ char unk00[0x15];
	/* 0x15 */ unsigned char deathState;
	/* 0x16 */ unsigned char deathEffectState;
	/* 0x17 */ unsigned char deathStateType;
	/* 0x18 */ char unk18[0x48 - 0x18];
	/* 0x48 */ int deathType;
	/* 0x4c */ char unk4c[0x60 - 0x4c];
	/* 0x60 */ unsigned short effectTimers[1];
};
struct GroupSpawnData {
	/* 0x00 */ char unk00[0x38];
	/* 0x38 */ int boundArea;
};
typedef GroupSpawnData *(*getSpawnData_t)(moby *);
getSpawnData_t *MobyGetInterface(int, int, int) __asm__("MobyGetInterface___dupe2");
ReactVars *MB_getReactVars(moby *) __asm__("MB_getReactVars");
void MB_setState(moby *, int, int) __asm__("MB_setState");
int MVE_GetBoundArea(moby *, MoveVars_V2 *) __asm__("MVE_GetBoundArea");
void MB_SwitchToDeathState(moby *) __asm__("MB_SwitchToDeathState");
int MB_UseLinearAnim(float, float, float) __asm__("MB_UseLinearAnim");

typedef GroupSpawnData *(*getSpawnData_t)(moby *);
struct MoveVarsAnimCache {
	/* 0x000 */ unsigned long actCache[32];
	/* 0x100 */ unsigned long reactCache[7];
	/* 0x138 */ unsigned long elvCache[5];
	/* 0x160 */ unsigned long motCache[3];
	/* 0x178 */ unsigned long dirCache[4];
	/* 0x198 */ unsigned long grpCache[33];
	/* 0x2a0 */ unsigned long alertCache[4];
};
void MB_InitCache(moby *, MoveVarsAnimCache *) __asm__("MB_InitCache");
void MB_SetAnimCache(moby *, MoveVarsAnimCache *, MoveVarsAnimCache *) __asm__("MB_SetAnimCache");
int MB_IncomingMayaFrameTrigger(moby *, float) __asm__("MB_IncomingMayaFrameTrigger");
void MB_UpdateMoveEffects(moby *) __asm__("MB_UpdateMoveEffects");
void MVE_SpawnWaterSplash(moby *, MoveVars_V2 *) __asm__("MVE_SpawnWaterSplash");
void MVE_SpawnHitGroundDust(moby *, MoveVars_V2 *) __asm__("MVE_SpawnHitGroundDust");
static inline int MB_CacheValid(MoveVarsAnimCache *pCache) { return pCache->actCache[0] != 0; }

typedef GroupSpawnData *(*getSpawnData_t)(moby *);
struct MoveAnimData {
	/* 0x00 */ unsigned char elv;
	/* 0x01 */ unsigned char alert;
	/* 0x02 */ unsigned char unk02;
	/* 0x03 */ unsigned char mot;
	/* 0x04 */ unsigned char dir;
	/* 0x05 */ unsigned char act;
	/* 0x06 */ unsigned char react;
	/* 0x07 */ unsigned char grp;
	/* 0x08 */ unsigned int flags;
	/* 0x0c */ float speed;
	/* 0x10 */ float turnSpeed;
	/* 0x14 */ float frameTrig;
};
typedef void (*ActionCallback)(moby *, int);
int MB_Action_2(moby *, int, ActionCallback, int, int, float, int) __asm__("MB_Action_2");
int MB_StopAction_2(moby *, int, int) __asm__("MB_StopAction_2");

typedef GroupSpawnData *(*getSpawnData_t)(moby *);
struct MoveAnimSeqInfo {
	/* 0x00 */ int unk00;
	/* 0x04 */ MoveAnimData *pData;
};
struct MoveAnimSeq {
	/* 0x00 */ char unk00[0x18];
	/* 0x18 */ MoveAnimSeqInfo *pInfo;
};
struct MoveMobyClass {
	/* 0x00 */ char unk00[0xc];
	/* 0x0c */ unsigned char seqCnt;
	/* 0x0d */ char unk0d[0x48 - 0xd];
	/* 0x48 */ MoveAnimSeq *seqs[1];
};
static inline MoveAnimData *MB_GetAnimData(moby *pMoby)
{
	return ((MoveMobyClass *)pMoby->pClass)->seqs[pMoby->animSeqId]->pInfo->pData;
}
void MB_MoveSystemUpdateAction(moby *, MoveVars_V2 *) __asm__("MB_MoveSystemUpdateAction");

typedef GroupSpawnData *(*getSpawnData_t)(moby *);

typedef GroupSpawnData *(*getSpawnData_t)(moby *);

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

GAME_SECTION(MB_Action_2) int MB_Action_2(moby *pMoby, int actionId, ActionCallback pCallback, int doNotInterrupt, int customMoveOverride, float startFrame, int forceImmediate)
{
	MoveVars_V2 *pMoveVars = MB_GetMoveVars(pMoby);
	if (!pMoveVars) return 0;
	if (pMoveVars->flags & 0x80) return 0;
	if (pMoveVars->action == actionId) return 1;
	if (!doNotInterrupt && pMoveVars->reaction) return 0;
	if (actionId >= 0x21) return 0;
	if (pMoveVars->action) MB_StopAction_2(pMoby, pMoveVars->action, 0);
	pMoveVars->action = actionId;
	pMoveVars->pActionCallback = pCallback;
	pMoveVars->actionStartFrame = startFrame;
	pMoveVars->flags &= 0xfffbffff;
	pMoveVars->dirty = 1;
	if (forceImmediate) pMoveVars->lockAnim = 0;
	if (doNotInterrupt) pMoveVars->flags |= 0x80;
	if (customMoveOverride) pMoveVars->flags |= 0x20000;
	if (pMoveVars->pActionCallback) pMoveVars->pActionCallback(pMoby, 0);
	return 1;
}

GAME_SECTION(MB_StopAction_2) int MB_StopAction_2(moby *pMoby, int actionId, int noActEndActions)
{
	MoveVars_V2 *pMoveVars = MB_GetMoveVars(pMoby);
	if (!pMoveVars) return 0;
	if (pMoveVars->action != actionId) return 1;
	if (actionId <= 0) return 1;
	ActionCallback pOldCallback = pMoveVars->pActionCallback;
	pMoveVars->flags = (int)pMoveVars->flags & ~0x80;
	pMoveVars->flags &= 0xfffdffff;
	pMoveVars->flags = (int)pMoveVars->flags & ~0x1000;
	pMoveVars->dirty = 1;
	pMoveVars->action = 0;
	pMoveVars->pActionCallback = 0;
	MoveAnimData *pData = MB_GetAnimData(pMoby);
	if (pData->act && pMoveVars->pAttach) pData = MB_GetAnimData(pMoveVars->pAttach);
	if (pData->flags & 2) pMoveVars->flags |= 0x800;
	if (noActEndActions) pMoveVars->flags |= 0x80;
	if (pOldCallback) pOldCallback(pMoby, 4);
	if (noActEndActions) pMoveVars->flags = (int)pMoveVars->flags & ~0x80;
	return 1;
}

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

GAME_SECTION(MB_InitCache) void MB_InitCache(moby *pMoby, MoveVarsAnimCache *pAnimCache)
{
	int turnAnimsFound = 0;
	int slowestWalk = -1;
	float slowestWalkSpeed = 100000.0f;
	unsigned long i;
	for (i = 0; i < ((MoveMobyClass *)pMoby->pClass)->seqCnt; i++) {
		MoveAnimData *pAnim = ((MoveMobyClass *)pMoby->pClass)->seqs[(int)i]->pInfo->pData;
		if (!pAnim) continue;
		if (pAnim->turnSpeed != 0.0f) turnAnimsFound = 1;
		if (pAnim->dir == 0 && 0.0f < pAnim->speed && pAnim->speed < slowestWalkSpeed) {
			slowestWalkSpeed = pAnim->speed;
			slowestWalk = (int)i;
		}
		unsigned long bit = 1L << (int)i;
		pAnimCache->actCache[pAnim->act] |= bit;
		pAnimCache->reactCache[pAnim->react] |= bit;
		pAnimCache->elvCache[pAnim->elv] |= bit;
		pAnimCache->motCache[pAnim->mot] |= bit;
		pAnimCache->dirCache[pAnim->dir] |= bit;
		pAnimCache->grpCache[pAnim->grp] |= bit;
		pAnimCache->alertCache[pAnim->alert] |= bit;
	}
	if (!turnAnimsFound && slowestWalk != -1) pAnimCache->motCache[0] |= 1L << slowestWalk;
}

GAME_SECTION(MB_SetAnimCache) void MB_SetAnimCache(moby *pMoby, MoveVarsAnimCache *pAnimCache, MoveVarsAnimCache *pAttachAnimCache)
{
	MoveVars_V2 *pMoveVars = MB_GetMoveVars(pMoby);
	if (!pMoveVars) return;
	pMoveVars->pAttachAnimCache = pAttachAnimCache;
	pMoveVars->pAnimCache = pAnimCache;
	if (pAnimCache && !MB_CacheValid(pAnimCache)) MB_InitCache(pMoby, pAnimCache);
	if (pMoveVars->pAttach && pMoveVars->pAttachAnimCache && !MB_CacheValid(pMoveVars->pAttachAnimCache)) MB_InitCache(pMoveVars->pAttach, pMoveVars->pAttachAnimCache);
}

GAME_SECTION(MB_IncomingAnimationMayaFrame) float MB_IncomingAnimationMayaFrame(moby *pMoby)
{
	return MobyMayaFrame(pMoby);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_IncomingMayaFrameTrigger);

GAME_SECTION(MB_SwitchToDeathState) void MB_SwitchToDeathState(moby *pMoby)
{
	ReactVars *rVars = MB_getReactVars(pMoby);
	if (rVars) {
		int deathType = rVars->deathType;
		if (rVars->effectTimers[0] && deathType != 6) deathType = 3;
		int state = rVars->deathState;
		if (state == 0xff) state = pMoby->bits;
		if ((unsigned int)(deathType - 5) < 2) {
			if (rVars->deathEffectState != 0xff) state = rVars->deathEffectState;
		}
		int deathStateType = rVars->deathStateType;
		if (deathStateType != 0xff) MB_setState(pMoby, state, deathStateType);
		else MB_setState(pMoby, state, -1);
	}
}

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

GAME_SECTION(MB_UpdateMoveEffects) void MB_UpdateMoveEffects(moby *pMoby)
{
	MoveVars_V2 *pMoveVars = MB_GetMoveVars(pMoby);
	if (!pMoveVars) return;
	if (pMoby->state & 1) return;
	if (!MB_GetMoveVars(pMoby)) return;
	if (MB_GetMoveVars(pMoby)->flags & 0x100) return;
	if (0.0f < pMoveVars->passThruSurface) {
		switch (pMoveVars->passThruSurfaceType) {
		case 0:
		case 13:
		case 14:
			MVE_SpawnWaterSplash(pMoby, pMoveVars);
			break;
		case 1:
			MVE_SpawnLavaSplash(pMoby, pMoveVars);
			break;
		}
	} else if (0.0f < pMoveVars->hitGroundSpeed) {
		MVE_SpawnHitGroundDust(pMoby, pMoveVars);
		pMoveVars->hitGroundSpeed = 0.0f;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_MoveSystemUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_SetMoveAnim);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/move", MB_GetBestAnimSlow);

GAME_SECTION(MB_UseLinearAnim) int MB_UseLinearAnim(float desiredSpeed, float compareSpeed, float animSpeed)
{
	int ret;
	if (desiredSpeed <= 0.0f) {
		ret = 0;
		if (animSpeed <= 0.0f && 0.0f < compareSpeed) return 1;
	} else {
		ret = 0;
		if (0.0f < animSpeed) {
			if (compareSpeed <= 0.0f) return 1;
			ret = 1;
			if (!((desiredSpeed - animSpeed) / (compareSpeed - animSpeed) < 0.5f)) ret = 0;
		}
	}
	return ret;
}

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

GAME_SECTION(MB_SetMoveDistanceThresholds) int MB_SetMoveDistanceThresholds(moby *pMoby, float collDist, float stopDist, float walkDist, float runDist)
{
	MoveVars_V2 *pMoveVars = MB_GetMoveVars(pMoby);
	if (!pMoveVars) return 0;
	pMoveVars->collRadius = collDist;
	pMoveVars->stopDist = stopDist;
	pMoveVars->walkDist = walkDist;
	pMoveVars->runDist = runDist;
	return 1;
}

GAME_SECTION(MB_SetMoveSpeedLimits) int MB_SetMoveSpeedLimits(moby *pMoby, float accel, float decel, float walkSpeed, float runSpeed, float strafeSpeed, float backSpeed, float flySpeed)
{
	MoveVars_V2 *pMoveVars = MB_GetMoveVars(pMoby);
	if (!pMoveVars) return 0;
	pMoveVars->linearAccel = accel;
	pMoveVars->linearDecel = decel;
	pMoveVars->walkSpeed = walkSpeed;
	pMoveVars->runSpeed = runSpeed;
	pMoveVars->strafeSpeed = strafeSpeed;
	pMoveVars->backSpeed = backSpeed;
	pMoveVars->flySpeed = flySpeed;
	return 1;
}

GAME_SECTION(MB_SetMoveAngularSpeeds) int MB_SetMoveAngularSpeeds(moby *pMoby, float angular_accel, float angular_decel, float angular_limit)
{
	MoveVars_V2 *pMoveVars = MB_GetMoveVars(pMoby);
	if (!pMoveVars) return 0;
	pMoveVars->angularAccel = angular_accel;
	pMoveVars->angularDecel = angular_decel;
	pMoveVars->angularLimit = angular_limit;
	return 1;
}

GAME_SECTION(MB_SetMoveDamper) int MB_SetMoveDamper(moby *pMoby, float amount, int ticks)
{
	MoveVars_V2 *pMoveVars = MB_GetMoveVars(pMoby);
	if (!pMoveVars) return 0;
	if ((pMoveVars->flagsA & 0x20) && ticks > 0) {
		pMoveVars->damper = amount;
		pMoveVars->moveDamperTimer = ticks;
		pMoveVars->dirty = 1;
	} else {
		pMoveVars->damper = 1.0f;
		pMoveVars->moveDamperTimer = 0;
	}
	return 1;
}

GAME_SECTION(MB_GetMoveDamper) float MB_GetMoveDamper(moby *pMoby)
{
	MoveVars_V2 *pVars = MB_GetMoveVars(pMoby);
	float ret = 1.0f;
	if (pVars && (pVars->flagsA & 0x20)) ret = pVars->damper;
	return ret;
}
