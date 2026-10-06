#ifndef UPDATE_MOBY4244_H
#define UPDATE_MOBY4244_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:6124; ghidra-layout.
typedef struct { // 0x18
    /* 0x00 */ float maxYaw;
    /* 0x04 */ float maxElv;
    /* 0x08 */ float maxRange;
    /* 0x0c */ float scaleElv;
    /* 0x10 */ float scaleAng;
    /* 0x14 */ float blendFactorLimit;
} Weapon_ThirdPerson;

#endif
