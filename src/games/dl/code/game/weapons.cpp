#include "common.h"
#include "game_section.h"


typedef struct wpnTarget {
	/* 0x00 */ int unk00;
	/* 0x04 */ void *target;
	/* 0x08 */ char unk08[8];
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_CheckCacheForTargetable);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_KillAllSoundsForPendingScene);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_SetOClass);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_RC3InitWeaponsOnMovingTrain);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EDEA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_BangelizeWeapons);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_TurnOnHoloShields);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", WPN_TurnOffHoloShields);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EE230);
