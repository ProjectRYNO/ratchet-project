#ifndef GUBER_HERO_H
#define GUBER_HERO_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:4972; prototype-layout.
typedef struct { // 0x2c
    /* 0x00 */ int type;
    /* 0x04 */ int stage;
    /* 0x08 */ int endComboFrm;
    /* 0x0c */ int inputFrm;
    /* 0x10 */ int transFrm;
    /* 0x14 */ int jumpTransFrm;
    /* 0x18 */ int etcTransFrm;
    /* 0x1c */ int startDamFrm;
    /* 0x20 */ int stopDamFrm;
    /* 0x24 */ int startBlurFrm;
    /* 0x28 */ int stopBlurFrm;
} HeroAttackDef;

// dltypes.txt:5146; ghidra-layout.
typedef struct { // 0x70
    /* 0x00 */ int mobyNum;
    /* 0x04 */ float maxWalkSpeed;
    /* 0x08 */ float kneeHeight;
    /* 0x0c */ float kneeCheckDist;
    /* 0x10 */ float colRadius;
    /* 0x14 */ float colTop;
    /* 0x18 */ float colBot;
    /* 0x1c */ float colBotFall;
    /* 0x20 */ int jumpPushOffTime;
    /* 0x24 */ float jumpPeakFrm;
    /* 0x28 */ float jumpLandFrm;
    /* 0x2c */ float jumpGameLandFrm;
    /* 0x30 */ float jumpMaxHeight;
    /* 0x34 */ float jumpMinHeight;
    /* 0x38 */ int jumpMaxUpTime;
    /* 0x3c */ float jumpGravity;
    /* 0x40 */ float jumpMaxXySpeed;
    /* 0x44 */ float fallGravity;
    /* 0x48 */ float maxFallSpeed;
    /* 0x4c */ float walkAnimSpeedMul;
    /* 0x50 */ float walkAnimSpeedLimLower;
    /* 0x54 */ float walkAnimSpeedLimUpper;
    /* 0x58 */ float jogAnimSpeedMul;
    /* 0x5c */ float jogAnimSpeedLimLower;
    /* 0x60 */ float jogAnimSpeedLimUpper;
    /* 0x64 */ int pad[3];
} HeroPlayerConstants;

// dltypes.txt:20910; ghidra-layout.
typedef struct { // 0x18
    /* 0x00 */ signed char killingPlayerIndex;
    /* 0x01 */ unsigned char deathState;
    /* 0x02 */ signed char deadPlayerIndex;
    /* 0x03 */ signed char killingWeapon;
    /* 0x04 */ signed char killType;
    /* 0x08 */ unsigned int killerUID;
    /* 0x0c */ unsigned int deathData;
    /* 0x10 */ short int iTag;
    /* 0x12 */ short int iTagFlg;
    /* 0x14 */ int netFrameTime;
} tNW_KillDeathMessage;

#endif
