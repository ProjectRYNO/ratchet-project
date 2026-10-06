#ifndef BOOTUTIL_H
#define BOOTUTIL_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:6107; prototype-layout.
typedef struct { // 0x20
    /* 0x00 */ char bPercents[15];
    /* 0x0f */ char flags;
    /* 0x10 */ float oldHitPoints;
    /* 0x14 */ short int armorBits;
    /* 0x16 */ short int pad[5];
} ArmorVars;

#endif
