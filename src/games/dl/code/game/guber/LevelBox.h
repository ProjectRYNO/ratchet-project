#ifndef GUBER_LEVELBOX_H
#define GUBER_LEVELBOX_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:11654; ghidra-layout.
typedef struct { // 0x18
    /* 0x00 */ int points;
    /* 0x04 */ int badgeType;
    /* 0x08 */ int badges;
    /* 0x0c */ int armorLevel;
    /* 0x10 */ int completeMission;
    /* 0x14 */ int playedScene;
} UnlockData;

// dltypes.txt:14698; ghidra-layout.
typedef struct { // 0x5
    /* 0x0 */ char gadget;
    /* 0x1 */ char basic_mod;
    /* 0x2 */ char post_mod;
    /* 0x3 */ char weapon_mod;
    /* 0x4 */ char bot;
} RewardData;

// dltypes.txt:14706; ghidra-layout.
typedef struct { // 0x8
    /* 0x0 */ char gadget;
    /* 0x1 */ char bot1;
    /* 0x2 */ char bot2;
    /* 0x3 */ char wrench;
    /* 0x4 */ char pfxMod;
    /* 0x5 */ char replayGadget;
    /* 0x6 */ char replayWrench;
    /* 0x7 */ char replayBot;
} VendorData;

#endif
