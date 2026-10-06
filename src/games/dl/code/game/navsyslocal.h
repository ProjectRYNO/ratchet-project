#ifndef NAVSYSLOCAL_H
#define NAVSYSLOCAL_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:7460; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ char effectorMode;
    /* 0x1 */ char bunkerType;
    /* 0x2 */ char padc[2];
    /* 0x4 */ float strength;
    /* 0x8 */ int type;
    /* 0xc */ int pad;
} EffectorVars;

#endif
