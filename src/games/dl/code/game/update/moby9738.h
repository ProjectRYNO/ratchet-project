#ifndef UPDATE_MOBY9738_H
#define UPDATE_MOBY9738_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

#ifndef __cplusplus
#include <stdbool.h>
#endif

// dltypes.txt:9248; prototype-layout.
typedef struct { // 0x3c
    /* 0x00 */ int iDivisions;
    /* 0x04 */ int iCenterColor;
    /* 0x08 */ int iEdgeColor;
    /* 0x0c */ float fCenterAmp;
    /* 0x10 */ float fEdgeAmp;
    /* 0x14 */ float fEdgeOfs;
    /* 0x18 */ float fEdgeScale;
    /* 0x1c */ int iRandTableSize;
    /* 0x20 */ float fRandStep;
    /* 0x24 */ bool bFrontSide;
    /* 0x28 */ int iNumFadeRows;
    /* 0x2c */ float fEdgeAmpFadeTarget;
    /* 0x30 */ float fCenterAmpFadeTarget;
    /* 0x34 */ int iCenterColorFadeTarget;
    /* 0x38 */ int iEdgeColorFadeTarget;
} FXU_DistortionShellStyle_t;

#endif
