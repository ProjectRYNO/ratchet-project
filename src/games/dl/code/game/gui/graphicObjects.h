#ifndef GUI_GRAPHICOBJECTS_H
#define GUI_GRAPHICOBJECTS_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:8290; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ float x;
    /* 0x4 */ float y;
    /* 0x8 */ float z;
    /* 0xc */ float w;
} Channel4f;

#endif
