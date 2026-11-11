#include "common.h"
#include "game_section.h"




typedef struct wpnTarget {
	/* 0x00 */ void *pTarget;
	/* 0x04 */ void *target;
	/* 0x08 */ int timer;
	/* 0x0c */ int unk0c;
} wpnTarget_t;
extern wpnTarget_t WPN_targetCache[32] __asm__("WPN_targetCache");
void WPN_ClearCachedTargets(void *target) __asm__("WPN_ClearCachedTargets");


typedef struct wpnUpgradeVars {
	/* 0x00 */ char unk00[8];
	/* 0x08 */ short gadget;
	/* 0x0a */ short mode;
	/* 0x0c */ char unk0c[0xac];
	/* 0xb8 */ void *mobys[4];
} wpnUpgradeVars_t;
extern wpnUpgradeVars_t _WPN_umv __asm__("_WPN_umv");
extern int WPN_UpdateCountDown __asm__("WPN_UpdateCountDown");
int WPN_IsUpgradeMoby(void *moby) __asm__("WPN_IsUpgradeMoby");
void WPN_SetUpgradeGadgetMode(int gadget, int mode) __asm__("WPN_SetUpgradeGadgetMode");

struct MobyInstance;
struct WPN_VelOrientCache {
	/* 0x00 */ int unk00[7];
	/* 0x1c */ MobyInstance *pParent;
};
struct WpnMoby {
	/* 0x00 */ char unk00[0x34];
	/* 0x34 */ unsigned short modeBits;
	/* 0x36 */ char unk36[0x76];
	/* 0xac */ void *pVar;
	/* 0xb0 */ char unkb0[0xc];
	/* 0xbc */ short unkbc;
};
struct WpnHero {
	/* 0x000 */ char unk000[0x2ec];
	/* 0x2ec */ WpnMoby *groundMoby;
};
extern WPN_VelOrientCache WPN_velOrientationCache[] __asm__("WPN_velOrientationCache");
int WPN_OnMovingTrainUntil __asm__("D_2208D4") GAME_GP_DATA = 0;
WpnMoby *WPN_TrackMoby __asm__("WPN_TrackMoby") GAME_GP_DATA = 0;
extern int gameMode __asm__("gameMode");
extern int worldUpdateTime __asm__("worldUpdateTime");
WpnHero *GB_GetLocalHeroFromSlot(int) __asm__("GB_GetLocalHeroFromSlot");
int HandGadgetID(WpnHero *) __asm__("HandGadgetID");
void Camera_SetFov(int, float, int, int, float, float, float) __asm__("Camera_SetFov");
void SetTfragDistsByFOV(int) __asm__("SetTfragDistsByFOV");
void InitMobyInstance(WpnMoby *, int, bool) __asm__("InitMobyInstance");
void PostUpdateMoby(WpnMoby *) __asm__("PostUpdateMoby");
void WPN_CacheTarget(MobyInstance *, MobyInstance *, int) __asm__("WPN_CacheTarget");
int WPN_CheckCacheForTargetable(MobyInstance *, MobyInstance *) __asm__("WPN_CheckCacheForTargetable");
void WPN_RemoveVelOrientExternal(int) __asm__("WPN_RemoveVelOrientExternal");
void WPN_KillAllSoundsForPendingScene(WpnHero *) __asm__("WPN_KillAllSoundsForPendingScene");
void WPN_SetOClass(WpnMoby *, int) __asm__("WPN_SetOClass");
int WPN_RC3InitWeaponsOnMovingTrain(WpnHero *) __asm__("WPN_RC3InitWeaponsOnMovingTrain");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_DrawReticule);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004E9490);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_MP_CalcProjectileVelocity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_CalculateTrajectory);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_AddGravity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_GetUp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_MP_AddGravity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_MP_GetUp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EA5E0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_CacheTarget);

GAME_SECTION(WPN_CheckCacheForTargetable) int WPN_CheckCacheForTargetable(MobyInstance *pParent, MobyInstance *pTarget)
{
	int i;
	int targetable = 1;
	for (i = 0; i < 0x20; i++) {
		if (WPN_targetCache[i].target == pParent && WPN_targetCache[i].pTarget == pTarget) {
			targetable = 0;
			break;
		}
	}
	return targetable;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EA6C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_UpdateCachedTargets);

GAME_SECTION(WPN_ClearCachedTargets) void WPN_ClearCachedTargets(void *target)
{
	int i;
	for (i = 0; i < 32; i++) {
		if (WPN_targetCache[i].target == target) WPN_targetCache[i].target = 0;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_AttachVelOrientExternal);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_RemoveVelOrientExternal);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_VelOrientExternal);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EAAD8);

GAME_SECTION(WPN_KillAllSoundsForPendingScene) void WPN_KillAllSoundsForPendingScene(WpnHero *pHero)
{
	if (pHero == 0) pHero = GB_GetLocalHeroFromSlot(0);
	if (HandGadgetID(pHero) == 5 && gameMode == 8) {
		Camera_SetFov(0, 1.1100293f, 0, 3, 0.005f, 0.2f, 0.0f);
		SetTfragDistsByFOV(1);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EAB68);

GAME_SECTION(WPN_SetUpgradeGadgetMode) void WPN_SetUpgradeGadgetMode(int gadget, int mode)
{
	if (WPN_UpdateCountDown == 0) {
		if (_WPN_umv.gadget != gadget || _WPN_umv.mode != mode) {
			_WPN_umv.gadget = gadget;
			_WPN_umv.mode = mode;
			WPN_UpdateCountDown = 0x2d;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_UpgradeModeInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_UpgradeModeUnInit);

GAME_SECTION(WPN_SetOClass) void WPN_SetOClass(WpnMoby *pMoby, int oClass)
{
	void *pVar = pMoby->pVar;
	InitMobyInstance(pMoby, oClass, false);
	pMoby->pVar = pVar;
	FastMemSet(pVar, 0, 0x80);
	if ((pMoby->modeBits & 4) == 0) PostUpdateMoby(pMoby);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_CreateMoby);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_DeleteMoby);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", FUN_004eb388);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_PostFX_Showcase);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_PostFX_Screen);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_FontTicker);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_FontScroll);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_drawIcon);

GAME_SECTION(WPN_IsUpgradeMoby) int WPN_IsUpgradeMoby(void *moby)
{
	int i;
	if (!moby) return 0;
	for (i = 0; i < 4; i++) {
		if (_WPN_umv.mobys[i] == moby) return 1;
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004ED7F0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_ShowcaseGadget);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_Showcase_Side);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_Showcase_Visor);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_ShowcaseGadgets);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_UpgradeDrawFx);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EDD80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_AddHeroExternal_Pos);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EDE10);

GAME_SECTION(WPN_RC3InitWeaponsOnMovingTrain) int WPN_RC3InitWeaponsOnMovingTrain(WpnHero *pHero)
{
	if (pHero == 0) pHero = GB_GetLocalHeroFromSlot(0);
	int ret;
	if (WPN_OnMovingTrainUntil >= worldUpdateTime) {
		WPN_TrackMoby = pHero->groundMoby;
		if (WPN_TrackMoby) {
			ret = WPN_TrackMoby->unkbc;
		} else {
			ret = 1;
		}
	} else {
		WPN_TrackMoby = 0;
		ret = 0;
	}
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EDEA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_BangelizeWeapons);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_TurnOnHoloShields);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_TurnOffHoloShields);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EE230);
