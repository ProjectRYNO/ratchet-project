#ifndef PROJECTGUI_GUIMAIN_H
#define PROJECTGUI_GUIMAIN_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

#ifndef __cplusplus
#include <stdbool.h>
#endif

// dltypes.txt:13829; ghidra-layout.
typedef struct { // 0xc
    /* 0x0 */ int iTeam;
    /* 0x4 */ bool bLocal;
    /* 0x8 */ int iScore;
} MPTeamData_s;

#endif
