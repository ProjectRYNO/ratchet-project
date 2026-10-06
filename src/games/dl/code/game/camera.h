#ifndef CAMERA_H
#define CAMERA_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:3691; ghidra-layout.
typedef struct { // 0x14
    /* 0x00 */ float azimuth;
    /* 0x04 */ float elevation;
    /* 0x08 */ float radius;
    /* 0x0c */ float rotY;
    /* 0x10 */ float rotZ;
} Polar;

// dltypes.txt:4051; ghidra-layout.
typedef struct { // 0xc
    /* 0x0 */ float azimuth;
    /* 0x4 */ float elevation;
    /* 0x8 */ float radius;
} PolarSm;

// dltypes.txt:4163; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ float strength;
    /* 0x4 */ float adjust;
    /* 0x8 */ int time;
    /* 0xc */ int div;
} CameraShake;

#endif
