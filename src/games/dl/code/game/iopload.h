#ifndef IOPLOAD_H
#define IOPLOAD_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:2397; ghidra-layout.
typedef struct { // 0x8
    /* 0x0 */ int offset;
    /* 0x4 */ int length;
} datablock;

#endif
