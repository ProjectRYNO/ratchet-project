#include "common.h"
#include "game_section.h"

int mf_NewLevels __asm__("mf_NewLevels") GAME_GP_DATA = 0;
int MF_GetNewLevelMask() __asm__("MF_GetNewLevelMask");
int mf_NewTournaments __asm__("mf_NewTournaments") GAME_GP_DATA = 0;
int MF_GetNewTournamentMask() __asm__("MF_GetNewTournamentMask");
int mf_deathsInMission __asm__("mf_deathsInMission") GAME_GP_DATA = 0;
void MF_ClearMissionSpecificData() __asm__("MF_ClearMissionSpecificData");
void MF_ClearMidMissionData() __asm__("MF_ClearMidMissionData");
int mf_midMissionMobySaveIndex __asm__("mf_midMissionMobySaveIndex") GAME_GP_DATA = 0;
extern char mf_midMissionMobySave[] __asm__("mf_midMissionMobySave");
void FastMemSet(void *, int, int) __asm__("FastMemSet");

struct LevelControllerInterface {
	/* 0x00 */ int unk00;
	/* 0x04 */ void (*SetupSwitchMissionIndex)(int);
	/* 0x08 */ int unk08[2];
	/* 0x10 */ void (*ExitPostMissionScreen)(void *);
};
LevelControllerInterface *mf_levelControllerInterface __asm__("mf_levelControllerInterface") GAME_GP_DATA = 0;
void *mf_levelController __asm__("mf_levelController") GAME_GP_DATA = 0;
void MF_ExitPostMissionScreen() __asm__("MF_ExitPostMissionScreen");

struct LevelChunkDef {
	/* 0x00 */ int active_id;
	/* 0x04 */ int unk04[4];
};
struct MissionDef {
	/* 0x00 */ char unk00[0x18];
	/* 0x18 */ int visibility_type;
	/* 0x1c */ int points;
	/* 0x20 */ int bolt_reward;
};
struct MissionStat {
	/* 0x00 */ int xp;
	/* 0x04 */ int bolts;
	/* 0x08 */ unsigned char status;
	/* 0x09 */ unsigned char rewards;
	/* 0x0a */ char unk0a[2];
};
struct LevelStat {
	/* 0x000 */ MissionStat missions[64];
	/* 0x300 */ int unk300;
};
int mf_activeMissionIndex __asm__("mf_activeMissionIndex") GAME_GP_DATA = 0;
unsigned char mf_switchMissionsInLevel1WithMenu __asm__("mf_switchMissionsInLevel1WithMenu") GAME_GP_DATA = 0;
extern int Level __asm__("Level");
extern LevelChunkDef LevelChunk __asm__("LevelChunk");
extern LevelStat mf_levelStats[] __asm__("mf_levelStats");
int ConvertMissionIndex(int, int) __asm__("ConvertMissionIndex");
MissionDef *GetMissionDef(int) __asm__("GetMissionDef");
void MF_SetupSwitchMissionIndex(int) __asm__("MF_SetupSwitchMissionIndex");
int MF_AllocatePointReward(int, int) __asm__("MF_AllocatePointReward");
unsigned char CheckUnlockMission(int) __asm__("CheckUnlockMission");
void MF_UpdateMissionProgress(int, int) __asm__("MF_UpdateMissionProgress");

struct SpawnPointData {
	/* 0x00 */ char unk00[0x20];
};
struct SpawnPointList {
	/* 0x000 */ SpawnPointData spawnPoint[8];
	/* 0x100 */ int index;
	/* 0x104 */ int size;
	/* 0x108 */ int unk108[2];
};
struct Hero {
	/* 0x0000 */ char unk0000[0x2f10];
	/* 0x2f10 */ int mpIndex;
};
extern SpawnPointList mf_spawnPointList[] __asm__("mf_spawnPointList");
extern int g_gameType __asm__("g_gameType");
extern int g_gameRules __asm__("g_gameRules");
Hero *GB_GetLocalHeroFromSlot(int) __asm__("GB_GetLocalHeroFromSlot");
bool MF_GetBestSpawnPointByOther(SpawnPointData **, Hero *, SpawnPointList *) __asm__("MF_GetBestSpawnPointByOther");
SpawnPointData *MF_GetBestSpawnPoint(Hero *) __asm__("MF_GetBestSpawnPoint");

extern float boltMultiplierPerLevel[] __asm__("boltMultiplierPerLevel");
int IsGameInChallengeMode() __asm__("IsGameInChallengeMode");
int MF_AllocateMissionBoltReward(int, int) __asm__("MF_AllocateMissionBoltReward");
int MF_GetDepreciatedValue(int, float, float, float, float) __asm__("MF_GetDepreciatedValue");
static inline MissionStat *MF_GetMissionStat(int level, int missionIndex)
{
	int l = (level - 1) % 20;
	return (MissionStat *)((missionIndex * sizeof(MissionStat) + l * sizeof(LevelStat)) + (char *)mf_levelStats);
}
struct MissionReward {
	/* 0x00 */ int xp;
	/* 0x04 */ int bolts;
	/* 0x08 */ int unk08[2];
};
struct RewardDecay {
	/* 0x00 */ int rate;
	/* 0x04 */ int min;
};
struct RewardData {
	/* 0x000 */ MissionReward mission[64];
	/* 0x400 */ RewardDecay xpDecay;
	/* 0x408 */ RewardDecay boltDecay;
};
struct RewardMoby {
	/* 0x00 */ char unk00[0xb4];
	/* 0xb4 */ short bolts;
	/* 0xb6 */ unsigned short xp;
};
extern RewardData mf_rewardData __asm__("mf_rewardData");
int MF_AllocateXPReward(RewardMoby *) __asm__("MF_AllocateXPReward");
int MF_AllocateBoltReward(RewardMoby *) __asm__("MF_AllocateBoltReward");
static inline int *MF_GetMissionBolts(int level, int missionIndex)
{
	int l = (level - 1) % 20;
	return (int *)((missionIndex * sizeof(MissionStat) + l * sizeof(LevelStat)) + (char *)&mf_levelStats[0].missions[0].bolts);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", MF_SetupSwitchMissionIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", func_0046A300);

GAME_SECTION(MF_ExitPostMissionScreen) void MF_ExitPostMissionScreen()
{
	if (mf_levelControllerInterface && mf_levelControllerInterface->ExitPostMissionScreen) {
		mf_levelControllerInterface->ExitPostMissionScreen(mf_levelController);
	}
}

GAME_SECTION(MF_GetNewLevelMask) int MF_GetNewLevelMask()
{
	return mf_NewLevels;
}

GAME_SECTION(MF_GetNewTournamentMask) int MF_GetNewTournamentMask()
{
	return mf_NewTournaments;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", MF_UpdateProgress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", MF_UpdateLevelProgress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", MF_UpdateMissionProgress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", MF_IsMissionIndexVisibleToMenu);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", MF_GetNextMissionIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", func_0046B048);

GAME_SECTION(MF_AllocateXPReward) int MF_AllocateXPReward(RewardMoby *pMoby)
{
	int xpReward;
	if (IsGameInChallengeMode()) return pMoby->xp;
	{
		xpReward = MF_GetDepreciatedValue(pMoby->xp, (float)MF_GetMissionStat(Level, mf_activeMissionIndex)->xp, (float)mf_rewardData.mission[mf_activeMissionIndex].xp, (float)mf_rewardData.xpDecay.rate / 100.0f, (float)mf_rewardData.xpDecay.min / 100.0f);
		MF_GetMissionStat(Level, mf_activeMissionIndex)->xp += xpReward;
	}
	return xpReward;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", MF_AllocateBoltReward);

GAME_SECTION(MF_GetDepreciatedValue) int MF_GetDepreciatedValue(int rewardAmount, float accumulated, float limit, float decayRate, float minRate)
{
	float remainingReward = (float)rewardAmount;
	float loopLimit = limit;
	float loopDecayRate = 1.0f;
	float reward = 0.0f;
	float nextLoopDecayRate;
	for (; 0.0f < remainingReward; remainingReward *= decayRate, loopLimit += limit * loopDecayRate) {
		if (accumulated < loopLimit) {
			float d = loopLimit - accumulated;
			float rewardToGive = remainingReward <? d;
			reward += rewardToGive;
			remainingReward -= rewardToGive;
		}
		nextLoopDecayRate = loopDecayRate * decayRate;
		if (nextLoopDecayRate < minRate) {
			reward += (remainingReward / loopDecayRate) * minRate;
			break;
		}
		loopDecayRate = nextLoopDecayRate;
	}
	return (int)reward;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", func_0046B328);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", MF_AllocatePointReward);

GAME_SECTION(MF_AllocateMissionBoltReward) int MF_AllocateMissionBoltReward(int level, int missionIndex)
{
	int boltReward = GetMissionDef(ConvertMissionIndex(level, missionIndex))->bolt_reward;
	if (IsGameInChallengeMode()) {
		boltReward = (int)((float)boltReward * boltMultiplierPerLevel[(Level - 1) % 20]);
		boltReward /= 1000;
		boltReward *= 1000;
	} else {
		int completes = MF_GetMissionStat(level, missionIndex)->rewards;
		if (completes >= 3) boltReward = 0;
		else if (completes) boltReward >>= completes;
	}
	return boltReward;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", func_0046B4A8);

GAME_SECTION(MF_ClearMissionSpecificData) void MF_ClearMissionSpecificData()
{
	MF_ClearMidMissionData();
	mf_deathsInMission = 0;
}

GAME_SECTION(MF_GetBestSpawnPoint) SpawnPointData *MF_GetBestSpawnPoint(Hero *pHero)
{
	Hero *pOtherHero = 0;
	SpawnPointData *pSpawnPoint;
	if (g_gameType == 0 && g_gameRules == 1) {
		pOtherHero = GB_GetLocalHeroFromSlot(pHero->mpIndex == 0);
	}
	if (pOtherHero && MF_GetBestSpawnPointByOther(&pSpawnPoint, pOtherHero, 0)) return pSpawnPoint;
	if (MF_GetBestSpawnPointByOther(&pSpawnPoint, pOtherHero, &mf_spawnPointList[pHero->mpIndex])) return pSpawnPoint;
	{
		SpawnPointList *pCP = &mf_spawnPointList[pHero->mpIndex];
		if (pCP->size > 0) return &pCP->spawnPoint[pCP->index];
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", MF_GetBestSpawnPointByOther);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", func_0046B6D0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionfunc", MF_CheckSpawnPoint);

GAME_SECTION(MF_ClearMidMissionData) void MF_ClearMidMissionData()
{
	FastMemSet(mf_midMissionMobySave, 0, 0x80);
	mf_midMissionMobySaveIndex = 0;
}
