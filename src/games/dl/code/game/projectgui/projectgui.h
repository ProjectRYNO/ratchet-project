#ifndef PROJECTGUI_PROJECTGUI_H
#define PROJECTGUI_PROJECTGUI_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

#ifndef __cplusplus
#include <stdbool.h>
#endif

// dltypes.txt:13709; ghidra-layout.
typedef struct { // 0xc
    /* 0x0 */ int state;
    /* 0x4 */ int counter;
    /* 0x8 */ bool trigger;
} HudState_State;

#endif
