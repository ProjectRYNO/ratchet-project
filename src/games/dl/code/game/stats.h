#ifndef STATS_H
#define STATS_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

typedef struct { // 0x18
	/* 0x00 */ int name;
	/* 0x04 */ int desc;
	/* 0x08 */ int difficulty;
	/* 0x0c */ int bolts;
	/* 0x10 */ int xp;
	/* 0x14 */ unsigned char completed;
} ST_SkillPointInfo;

#endif
