#ifndef INFLUENCE_H
#define INFLUENCE_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:10707; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ int worldTimeReserved;
    /* 0x4 */ short unsigned int currentPhase;
    /* 0x6 */ short unsigned int fraction;
    /* 0x8 */ short unsigned int index;
    /* 0xa */ short unsigned int numSectors;
    /* 0xc */ short unsigned int uid;
    /* 0xe */ short unsigned int paddingOfRenewableSunpowerDrivenPantsResources[1];
} IM_LoadBalancer;

// dltypes.txt:10717; ghidra-layout.
typedef struct { // 0xa0
    /* 0x00 */ float pX[8];
    /* 0x20 */ float pY[8];
    /* 0x40 */ float pZ[8];
    /* 0x60 */ float pScore[8];
    /* 0x80 */ short unsigned int pHash[8];
    /* 0x90 */ unsigned char foundPointMaximum;
    /* 0x91 */ unsigned char foundPoints;
    /* 0x92 */ unsigned char paddingOfWayTooMuchPadding[2];
    /* 0x94 */ unsigned int paddingOfTasteSensations[3];
} IM_PointList;

// dltypes.txt:10729; prototype-layout.
typedef struct { // 0x4
    /* 0x0 */ unsigned char xDistance;
    /* 0x1 */ unsigned char yDistance;
    /* 0x2 */ unsigned char radius;
    /* 0x3 */ unsigned char strength;
} IM_SectorCover;

#endif
