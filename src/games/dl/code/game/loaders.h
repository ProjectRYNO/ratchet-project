#ifndef LOADERS_H
#define LOADERS_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:9479; ghidra-layout.
typedef struct { // 0x20
    /* 0x00 */ int pifID;
    /* 0x04 */ int fileSize;
    /* 0x08 */ int uSize;
    /* 0x0c */ int vSize;
    /* 0x10 */ int texFormat;
    /* 0x14 */ int clutFormat;
    /* 0x18 */ int clutOrder;
    /* 0x1c */ int mipLevels;
} PifHeader;

#endif
