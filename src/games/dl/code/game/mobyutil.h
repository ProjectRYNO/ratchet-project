#ifndef MOBYUTIL_H
#define MOBYUTIL_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:3884; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ short int timer;
    /* 0x2 */ short int type;
    /* 0x4 */ int destColor;
    /* 0x8 */ int srcColor;
    /* 0xc */ int flags;
} FlashVars;

// dltypes.txt:9976; prototype-layout.
typedef struct { // 0x50
    /* 0x00 */ int anim;
    /* 0x04 */ float stride;
    /* 0x08 */ float frame0;
    /* 0x0c */ float frames;
    /* 0x10 */ int fromIdle;
    /* 0x14 */ int pad[3];
    /* 0x20 */ float heelRange[2];
    /* 0x28 */ float heelDown[2];
    /* 0x30 */ float heelUp[2];
    /* 0x38 */ float footRange[2];
    /* 0x40 */ float footDown[2];
    /* 0x48 */ float footUp[2];
} _2legAnim;

// dltypes.txt:12192; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ short int tagUCName;
    /* 0x2 */ short int tagName;
    /* 0x4 */ short int tagDesc;
    /* 0x6 */ short int imageIndex;
    /* 0x8 */ short int iconIndex;
    /* 0xc */ int price;
} BotAbility;

#endif
