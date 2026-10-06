#ifndef GUBER_LOCALHERO_H
#define GUBER_LOCALHERO_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:6275; ghidra-layout.
typedef struct { // 0x28
    /* 0x00 */ float LinearPredictionCutoff;
    /* 0x04 */ float LinearConvergenceThreshold;
    /* 0x08 */ float MaxLinearConvergenceDelta;
    /* 0x0c */ float MinLinearConvergenceDelta;
    /* 0x10 */ float MinSmoothConvergenceDelta;
    /* 0x14 */ float PositionErrorThreshold;
    /* 0x18 */ float MaxTrackSpeed;
    /* 0x1c */ float MaxConvergeSpeed;
    /* 0x20 */ float Accel;
    /* 0x24 */ float Decel;
} tDR_Profile;

#endif
