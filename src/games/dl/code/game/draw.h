#ifndef DRAW_H
#define DRAW_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:661; prototype-layout.
typedef struct { // 0x12
    /* 0x00 */ short int start;
    /* 0x02 */ short int stop;
    /* 0x04 */ short int text_ofs[7];
} Subtitle;

// dltypes.txt:9772; ghidra-layout.
typedef struct { // 0x28
    /* 0x00 */ float scis_l;
    /* 0x04 */ float scis_r;
    /* 0x08 */ float scis_t;
    /* 0x0c */ float scis_b;
    /* 0x10 */ float size_x;
    /* 0x14 */ float size_y;
    /* 0x18 */ float center_x;
    /* 0x1c */ float center_y;
    /* 0x20 */ int splitScreenMode;
    /* 0x24 */ float xratio;
} FrustumDef;

#endif
