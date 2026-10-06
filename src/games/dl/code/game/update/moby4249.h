#ifndef UPDATE_MOBY4249_H
#define UPDATE_MOBY4249_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:6637; prototype-layout.
typedef struct { // 0x1c
    /* 0x00 */ short int targetPosX;
    /* 0x02 */ short int targetPosY;
    /* 0x04 */ short int targetPosZ;
    /* 0x08 */ int timeStamp;
    /* 0x0c */ unsigned int sourceUID;
    /* 0x10 */ unsigned int targetUID;
    /* 0x14 */ unsigned int shotUID;
    /* 0x18 */ char type;
    /* 0x19 */ char miscInfo;
} tNW_ShotSpawnMessage;

#endif
