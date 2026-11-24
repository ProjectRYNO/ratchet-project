#ifndef MISSIONFUNC_H
#define MISSIONFUNC_H

struct MF_MissionSave { // 0xc
	/* 0x00 */ int xp;
	/* 0x04 */ int bolts;
	/* 0x08 */ unsigned char status;
	/* 0x09 */ unsigned char completes;
	/* 0x0a */ unsigned char difficulty;
};

struct MF_LevelSave { // 0x304
	/* 0x000 */ MF_MissionSave mission[64];
	/* 0x300 */ unsigned char status;
	/* 0x301 */ unsigned char jackpot;
};

struct MissionDef { // 0x60
	/* 0x00 */ int level_id;
	/* 0x04 */ int map_id;
	/* 0x08 */ int name_tag;
	/* 0x0c */ int desc_tag;
	/* 0x10 */ int obj_tag;
	/* 0x14 */ int mission_type;
	/* 0x18 */ int visibility_type;
	/* 0x1c */ int point_reward;
	/* 0x20 */ int bolt_reward;
	/* 0x24 */ int badge_reward;
	/* 0x28 */ int armor_level_reward;
	/* 0x2c */ unsigned char preReward[5];
	/* 0x31 */ unsigned char postReward[5];
	/* 0x38 */ int unlock[6];
	/* 0x50 */ int preVendor[2];
	/* 0x58 */ int postVendor[2];
};

struct MF_MissionRewardData { // 0x10
	/* 0x0 */ int xp;
	/* 0x4 */ int bolts;
	/* 0x8 */ int points;
	/* 0xc */ int reward_bolts;
};

struct MF_MissionDepreciationData { // 0x8
	/* 0x0 */ int rate;
	/* 0x4 */ int min;
};

struct MF_MissionRewards { // 0x418
	/* 0x000 */ MF_MissionRewardData mission[64];
	/* 0x400 */ MF_MissionDepreciationData xpDecay;
	/* 0x408 */ MF_MissionDepreciationData boltDecay;
	/* 0x410 */ MF_MissionDepreciationData rewardDecay;
};

#endif
