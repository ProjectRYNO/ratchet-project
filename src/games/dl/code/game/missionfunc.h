#ifndef MISSIONFUNC_H
#define MISSIONFUNC_H

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

#endif
