#include "common.h"
#include "game_section.h"


struct ST_EnemyKill {
	/* 0x00 */ int id;
	/* 0x04 */ int count;
};
struct ST_MissionRewardData {
	/* 0x00 */ int type;
	/* 0x04 */ int subtype;
	/* 0x08 */ int unk08[4];
};
struct StarSave {
	/* 0x00 */ short spent;
	/* 0x02 */ short unk02[7];
};
extern ST_EnemyKill ST_EnemyKills[] __asm__("ST_EnemyKills");
ST_MissionRewardData *ST_GetMissionRewardData(int, int) __asm__("ST_GetMissionRewardData___dupe2");
void ST_RegisterEnemyKill(int) __asm__("ST_RegisterEnemyKill");
extern ST_MissionRewardData ST_Rewards[] __asm__("ST_Rewards");
ST_MissionRewardData *ST_GetMissionRewardData(int) __asm__("ST_GetMissionRewardData");
extern int Level __asm__("Level");
int ST_GetNumAcquiredSkillPoints() __asm__("ST_GetNumAcquiredSkillPoints");
int ST_GetNumAcquiredSkillPoints(int level) __asm__("ST_GetNumAcquiredSkillPoints___dupe2");
extern int SkillPoints[] __asm__("D_171BA8");
extern StarSave DifficultyStars __asm__("D_171B5C");
int ST_GetNumDifficultyStars() __asm__("ST_GetNumDifficultyStars");
int ST_GetNumRemainingDifficultyStars() __asm__("ST_GetNumRemainingDifficultyStars");
int ST_AcquiredAllSkillPoints() __asm__("ST_AcquiredAllSkillPoints");
int ST_GetTotalNumAcquiredSkillPoints() __asm__("ST_GetTotalNumAcquiredSkillPoints");


struct SkillPointDef {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ int textId;
	/* 0x10 */ int descId;
	/* 0x14 */ int unk14[2];
	/* 0x1c */ int type;
	/* 0x20 */ int reward;
	/* 0x24 */ int percent;
};
struct ST_SkillPointInfo {
	/* 0x00 */ int textId;
	/* 0x04 */ int descId;
	/* 0x08 */ int type;
	/* 0x0c */ int percent;
	/* 0x10 */ int reward;
	/* 0x14 */ unsigned char acquired;
};
struct ST_MissionData {
	/* 0x00 */ int bSuccess;
	/* 0x04 */ int iTime;
	/* 0x08 */ int unk08[5];
	/* 0x1c */ int iSkillPoints;
	/* 0x20 */ int unk20[21];
};
struct MissionDef {
	/* 0x00 */ int unk00[6];
	/* 0x18 */ int hidden;
};
struct MissionProgress {
	/* 0x00 */ char unk00[0xa];
	/* 0x0a */ unsigned char stars;
	/* 0x0b */ char unk0b;
};
struct LevelProgress {
	/* 0x000 */ MissionProgress missions[0x40];
	/* 0x300 */ int unk300;
};
extern ST_MissionData ST_MissionStatistics __asm__("D_MISSIONSTATS");
extern LevelProgress LevelProgressTable[] __asm__("D_LEVELPROGRESS");
extern int mf_missionStatus __asm__("mf_missionStatus");
extern int worldUpdateTime __asm__("worldUpdateTime");
int FUN_004fce78(int, int *, int *) __asm__("FUN_004fce78");
int ConvertSkillPointIndex(int, int) __asm__("ConvertSkillPointIndex");
SkillPointDef *GetSkillPointDef(int) __asm__("GetSkillPointDef");
int ConvertMissionIndex(int, int) __asm__("ConvertMissionIndex");
MissionDef *GetMissionDef(int) __asm__("GetMissionDef");
void FastMemSet(void *, int, int) __asm__("FastMemSet");
int ST_GetNumExterminatorCardsCollected() __asm__("ST_GetNumExterminatorCardsCollected");
void ST_GetSkillPointInfo(int, int, ST_SkillPointInfo &) __asm__("ST_GetSkillPointInfo");
void ST_GetMissionStatistics(ST_MissionData *) __asm__("ST_GetMissionStatistics");


GAME_SECTION(ST_GetMissionRewardData) ST_MissionRewardData *ST_GetMissionRewardData(int iReward)
{
	return &ST_Rewards[iReward];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stats", ST_GetMissionRewardData___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stats", ST_GetMissionRewards);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stats", ST_GetMissionStatistics);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stats", func_004FC288);

GAME_SECTION(ST_GetNumAcquiredSkillPoints) int ST_GetNumAcquiredSkillPoints()
{
	return ST_GetNumAcquiredSkillPoints(Level);
}

GAME_SECTION(ST_GetNumAcquiredSkillPoints___dupe2) int ST_GetNumAcquiredSkillPoints(int level)
{
	int count = 0;
	int i;
	for (i = 0; i < 0xf; i++) count += (SkillPoints[(level - 1) % 0x14] >> i) & 1;
	return count;
}

GAME_SECTION(ST_GetSkillPointInfo) void ST_GetSkillPointInfo(int level, int skillPoint, ST_SkillPointInfo &info)
{
	SkillPointDef *pSkillDef;
	if (skillPoint < 0x1e) skillPoint += (level - 1) % 0x14 * 0x1e;
	pSkillDef = GetSkillPointDef(ConvertSkillPointIndex(level, skillPoint));
	info.textId = pSkillDef->textId;
	info.descId = pSkillDef->descId;
	info.type = pSkillDef->type;
	info.percent = (int)((float)pSkillDef->percent * 0.01f) * 100;
	info.reward = pSkillDef->reward;
	info.acquired = (SkillPoints[(level - 1) % 0x14] >> (skillPoint - (level - 1) % 0x14 * 0x1e)) & 1;
}

GAME_SECTION(ST_GetTotalNumAcquiredSkillPoints) int ST_GetTotalNumAcquiredSkillPoints()
{
	int total = 0;
	int level, i, n;
	for (level = 1; level < 0x10; level++) {
		n = 0;
		if (level != 0xf) n = level == 0x23 ? 0 : 0xf;
		for (i = 0; i < n; i++) total += (*(SkillPoints + (level - 1) % 0x14) >> i) & 1;
	}
	return total;
}

GAME_SECTION(ST_AcquiredAllSkillPoints) int ST_AcquiredAllSkillPoints()
{
	int i;
	for (i = 1; i < 0x10; i++) {
		if (i == 3 || i == 9 || i == 0xc || i == 0xf) continue;
		if ((SkillPoints[(i - 1) % 0x14] & 0x7fff) != 0x7fff) return 0;
	}
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stats", ST_GetNumDifficultyStars);

GAME_SECTION(ST_GetNumRemainingDifficultyStars) int ST_GetNumRemainingDifficultyStars()
{
	return ST_GetNumDifficultyStars() - DifficultyStars.spent;
}

/* NOT EXACT */
GAME_SECTION(ST_RegisterEnemyKill) void ST_RegisterEnemyKill(int id)
{
	int i;
	for (i = 0; ST_EnemyKills[i].id != -1; i++) {
		if (ST_EnemyKills[i].id == id) break;
	}
	if (ST_EnemyKills[i].id != -1) ST_EnemyKills[i].count++;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stats", FUN_004fc6f0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stats", FUN_004fce78);

GAME_SECTION(ST_GetNumExterminatorCardsCollected) int ST_GetNumExterminatorCardsCollected()
{
	int numCards = 0;
	if (FUN_004fce78(0x26fa, 0, 0)) numCards++;
	if (FUN_004fce78(0x26fb, 0, 0)) numCards++;
	if (FUN_004fce78(0x26fc, 0, 0)) numCards++;
	if (FUN_004fce78(0x26fd, 0, 0)) numCards++;
	if (FUN_004fce78(0x26fe, 0, 0)) numCards++;
	if (FUN_004fce78(0x2716, 0, 0)) numCards++;
	return numCards;
}
