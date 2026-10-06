#ifndef NETWORK_NWOBJECTS_H
#define NETWORK_NWOBJECTS_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:3244; prototype-layout.
typedef struct { // 0x18c
    /* 0x000 */ short int maxAmmo[20];
    /* 0x028 */ float metersPerSecond[20];
    /* 0x078 */ float shotsPerSecond[20];
    /* 0x0c8 */ float gadgetDamage1[20];
    /* 0x118 */ float gadgetDamage2[20];
    /* 0x168 */ float kBuggyDriverDamage;
    /* 0x16c */ float kBuggyPassengerDamage;
    /* 0x170 */ float M4222_DAMAGE_HP;
    /* 0x174 */ float kMineBomberDamage;
    /* 0x178 */ float M4290_FireDamage;
    /* 0x17c */ int check1;
    /* 0x180 */ int check2;
    /* 0x184 */ int check3;
    /* 0x188 */ int check4;
} tGadgetConstants;

// dltypes.txt:15975; prototype-layout.
typedef struct { // 0x30c
    /* 0x000 */ int kEnableChecksum;
    /* 0x004 */ int kEnableCDChecksum;
    /* 0x008 */ int kEnableChecksumMsgs;
    /* 0x00c */ int kChecksumBlocks[192];
} tChecksumConstants;

#endif
