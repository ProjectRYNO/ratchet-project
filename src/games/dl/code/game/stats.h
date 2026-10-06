#ifndef STATS_H
#define STATS_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

#ifndef __cplusplus
#include <stdbool.h>
#endif

// dltypes.txt:15364; ghidra-layout.
typedef struct { // 0x18
    /* 0x00 */ int name;
    /* 0x04 */ int desc;
    /* 0x08 */ int difficulty;
    /* 0x0c */ int bolts;
    /* 0x10 */ int xp;
    /* 0x14 */ bool completed;
} ST_SkillPointInfo;

#endif
