#ifndef GROUP_CONTROL_H
#define GROUP_CONTROL_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:10761; prototype-layout.
typedef struct { // 0x20
    /* 0x00 */ float frontAttackApeture;
    /* 0x04 */ float trackingRatio;
    /* 0x08 */ float shotError;
    /* 0x0c */ int timeLastAttacked;
    /* 0x10 */ short int timeRefraction;
    /* 0x12 */ unsigned char allowedByState;
    /* 0x13 */ unsigned char hasMutex;
    /* 0x14 */ unsigned char pad[12];
} GC_EnemyAttackInformation;

#endif
