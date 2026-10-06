#ifndef UPDATE_CORE_H
#define UPDATE_CORE_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:1236; prototype-layout.
typedef struct { // 0x8
    /* 0x0 */ int offset;
    /* 0x4 */ int length;
} binblock;

#endif
