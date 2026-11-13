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
	/* 0x00 */ short state;
	/* 0x02 */ short transTimer;
	/* 0x04 */ float transTimerInv;
	/* 0x08 */ short gadget;
	/* 0x0a */ short mode;
	/* 0x0c */ char unk0c[0x40 - 0xc];
	/* 0x40 */ unsigned char blackOverlayAlpha;
	/* 0x41 */ char unk41[0xb8 - 0x41];
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

struct WpnTargetMoby {
	/* 0x00 */ char unk00[0x20];
	/* 0x20 */ unsigned char state;
	/* 0x21 */ char unk21[0x34 - 0x21];
	/* 0x34 */ unsigned short modeBits;
};
int FastDecTimer(int &) __asm__("FastDecTimer");
void WPN_UpdateCachedTargets(void *) __asm__("WPN_UpdateCachedTargets");
void WPN_UpgradeDrawFx(void *) __asm__("WPN_UpgradeDrawFx");

struct HelpDataMessage {
	/* 0x00 */ unsigned short timesUsed;
	/* 0x02 */ char unk02[0xa];
};
extern HelpDataMessage HelpDataMessages[] __asm__("HelpDataMessages");
extern int g_gameType __asm__("g_gameType");
extern int *WPN_HoloShields[10][4] __asm__("WPN_HoloShields");
extern "C" {
	void snd_ContinueAllSoundsInGroup(int);
	void snd_FlushSoundCommands();
}
void music_Unpause() __asm__("music_Unpause");
void Help_QueueMessage(short, short, short, void *, float, float, float, float) __asm__("Help_QueueMessage");
void *MobyGetInterface(int, int, int) __asm__("MobyGetInterface___dupe2");
void WPN_UpgradeModeUnInit() __asm__("WPN_UpgradeModeUnInit");
void WPN_TurnOffHoloShields() __asm__("WPN_TurnOffHoloShields");

/* ===== AM additions ===== */
struct BangleMoby {
	/* 0x00 */ char unk00[0x74];
	/* 0x74 */ short bangles;
	/* 0x76 */ char unk76[0xbc - 0x76];
	/* 0xbc */ short oClass;
	/* 0xbe */ char unkbe[2];
};
struct WpnGadgetDef {
	/* 0x00 */ char unk00[0x3c];
	/* 0x3c */ short ammoClass;
	/* 0x3e */ char unk3e[2];
};
WpnGadgetDef *GetGadgetDef(int, int) __asm__("GetGadgetDef");
void WPN_BangelizeWeapons(BangleMoby *, int, int) __asm__("WPN_BangelizeWeapons");
struct HoloClass {
	/* 0x00 */ char unk00[0x10];
	/* 0x10 */ int collision;
};
struct HoloMoby {
	/* 0x00 */ char unk00[0x24];
	/* 0x24 */ HoloClass *pClass;
	/* 0x28 */ char unk28[0x98 - 0x28];
	/* 0x98 */ int collData;
};
struct HoloHero {
	/* 0x0000 */ char unk0000[0x2f14];
	/* 0x2f14 */ int teamIndex;
};
struct HoloInterface {
	/* 0x00 */ void *unk00[2];
	/* 0x08 */ void (*turnOn)();
	/* 0x0c */ void (*turnOnTeam)(int);
};
extern HoloHero *g_HoloHero[10] __asm__("g_Hero");
extern volatile int g_gameRulesVol __asm__("g_gameRules");
void WPN_TurnOnHoloShields(int) __asm__("WPN_TurnOnHoloShields");

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

GAME_SECTION(WPN_UpgradeModeUnInit) void WPN_UpgradeModeUnInit()
{
	snd_ContinueAllSoundsInGroup(0xcd);
	music_Unpause();
	snd_FlushSoundCommands();
	if (g_gameType != 1) {
		if (HelpDataMessages[0x680].timesUsed == 0) Help_QueueMessage(0x2fab, 0x680, 2, 0, 0.0f, 1.0f, 0.0f, 64.0f);
		else if (HelpDataMessages[0x681].timesUsed == 0) Help_QueueMessage(0x2fac, 0x681, 2, 0, 0.0f, 1.0f, 0.0f, 64.0f);
	}
	_WPN_umv.gadget = -1;
	_WPN_umv.mode = -1;
}

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

GAME_SECTION(WPN_UpgradeDrawFx) void WPN_UpgradeDrawFx(void *pMoby)
{
	float fac = (float)_WPN_umv.transTimer * _WPN_umv.transTimerInv;
	if (_WPN_umv.state == 0 || _WPN_umv.state == 6 || _WPN_umv.state == 7) {
		_WPN_umv.blackOverlayAlpha = (int)((1.0f - fac) * 128.0f);
	} else if (_WPN_umv.state == 1) {
		_WPN_umv.blackOverlayAlpha = (int)(fac * 128.0f);
	}
}

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

GAME_SECTION(WPN_BangelizeWeapons) void WPN_BangelizeWeapons(BangleMoby *pMoby, int rootID, int wpnLvl)
{
	WpnGadgetDef *pGadget = GetGadgetDef(rootID, 0);
	switch (rootID) {
	case 2:
		if (wpnLvl != 9) {
			pMoby->bangles = 0;
			return;
		}
		pMoby->bangles = 1;
		break;
	case 3:
		if (wpnLvl == 9) {
			pMoby->bangles = 0x31;
		} else {
			pMoby->bangles = 3;
		}
		break;
	case 6:
		if (wpnLvl != 9) {
			pMoby->bangles = 0;
			return;
		}
		pMoby->bangles = 0xf;
		break;
	case 7:
		if (wpnLvl != 9) {
			pMoby->bangles = 0;
			return;
		}
		pMoby->bangles = 7;
		break;
	case 4:
		if (wpnLvl == 9) {
			pMoby->bangles = 0xc;
		} else {
			pMoby->bangles = 3;
		}
		break;
	case 8:
		if (wpnLvl == 9) {
			pMoby->bangles = 0xf;
		} else {
			pMoby->bangles = 1;
		}
		break;
	case 5:
		if (wpnLvl != 9) {
			pMoby->bangles = 1;
			return;
		}
		pMoby->bangles = 6;
		break;
	case 15:
		if (wpnLvl == 9) {
			pMoby->bangles = 0x1f;
		} else {
			pMoby->bangles = 3;
		}
		break;
	case 9:
		if (pMoby->oClass == 0x24f2) {
			if (wpnLvl == 9) {
				pMoby->bangles = 3;
			} else {
				pMoby->bangles = 0;
			}
		} else {
			if (pMoby->oClass != pGadget->ammoClass) {
				return;
			}
			if (wpnLvl == 9) {
				pMoby->bangles = 7;
			} else {
				pMoby->bangles = 6;
			}
		}
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	default:
		return;
	}
}

extern volatile int g_gameTypeVol __asm__("g_gameType");
extern int g_gameTypeAM __asm__("g_gameType");
HoloInterface *HoloGetInterface(int, int, int) __asm__("MobyGetInterface___dupe2");
GAME_SECTION(WPN_TurnOnHoloShields) void WPN_TurnOnHoloShields(int teamIndex)
{
	int i;
	int j;
	HoloInterface *pInterface;
	for (i = 0; i < 10; i++) {
		if (g_HoloHero[i] == 0 || (g_HoloHero[i]->teamIndex != teamIndex && (g_gameTypeVol != 0 || g_gameRulesVol != 1 || teamIndex < 0))) {
			for (j = 0; j < 4; j++) {
				HoloMoby *pMoby = (HoloMoby *)WPN_HoloShields[i][j];
				if (pMoby) {
					pMoby->collData = pMoby->pClass->collision;
				}
			}
		}
	}
	if (g_gameTypeAM == 0 && teamIndex == -1) {
		pInterface = HoloGetInterface(0x263b, 0, 0xc);
		if (pInterface && pInterface->turnOn) {
			pInterface->turnOn();
		}
	}
	if (g_gameTypeAM == 1) {
		pInterface = HoloGetInterface(0x265b, 0, 0x14);
		if (pInterface && pInterface->turnOnTeam) {
			pInterface->turnOnTeam(teamIndex);
		}
	}
}

GAME_SECTION(WPN_TurnOffHoloShields) void WPN_TurnOffHoloShields()
{
	int i;
	int j;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 4; j++) {
			if (WPN_HoloShields[i][j]) WPN_HoloShields[i][j][0x26] = 0;
		}
	}
	if (g_gameType == 0) {
		void *pInterface = MobyGetInterface(0x263b, 0, 0xc);
		if (pInterface && ((void (**)())pInterface)[1]) ((void (**)())pInterface)[1]();
	}
	if (g_gameType == 1) {
		void *pInterface = MobyGetInterface(0x265b, 0, 0x14);
		if (pInterface && ((void (**)(int))pInterface)[4]) ((void (**)(int))pInterface)[4](-1);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/weapons", func_004EE230);
