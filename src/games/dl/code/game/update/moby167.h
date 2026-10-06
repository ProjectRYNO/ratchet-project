#ifndef UPDATE_MOBY167_H
#define UPDATE_MOBY167_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:7779; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ int beginColor;
    /* 0x4 */ int endColor;
    /* 0x8 */ short int maxScale;
    /* 0xa */ short int startScale;
    /* 0xc */ int lifeSpan;
} Part074_fixed;

#endif
