#ifndef UPDATE_MOBY8454_H
#define UPDATE_MOBY8454_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:9107; prototype-layout.
typedef struct { // 0x20
    /* 0x00 */ float SegmentLength;
    /* 0x04 */ float Gravity;
    /* 0x08 */ float Damping;
    /* 0x0c */ float CollideRadius;
    /* 0x10 */ float ParentCollideRadius;
    /* 0x14 */ char NumIterations;
    /* 0x15 */ char NumControlledVerts;
    /* 0x16 */ char NumNonParentCollideableVerts;
    /* 0x17 */ char ConstraintOverlap;
    /* 0x18 */ float ControlledSegmentLength;
    /* 0x1c */ int pad[1];
} M8454_WhipParameters;

#endif
