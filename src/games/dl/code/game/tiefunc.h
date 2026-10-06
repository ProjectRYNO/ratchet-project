#ifndef TIEFUNC_H
#define TIEFUNC_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:11186; prototype-layout.
typedef struct { // 0x8
    /* 0x0 */ short int vert_cnt;
    /* 0x2 */ short int tri_cnt;
    /* 0x4 */ short int strip_cnt;
    /* 0x6 */ short int pad;
} TieLod;

#endif
