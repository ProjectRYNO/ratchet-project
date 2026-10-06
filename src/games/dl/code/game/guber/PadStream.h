#ifndef GUBER_PADSTREAM_H
#define GUBER_PADSTREAM_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:6331; ghidra-layout.
typedef struct { // 0x2
    /* 0x0 */ unsigned char data[2];
} pad_frame;

#endif
