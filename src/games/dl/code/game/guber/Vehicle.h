#ifndef GUBER_VEHICLE_H
#define GUBER_VEHICLE_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:21062; prototype-layout.
typedef struct { // 0x18
    /* 0x00 */ unsigned char flags;
    /* 0x04 */ unsigned int UID;
    /* 0x08 */ int timeStamp;
    /* 0x0c */ short int rot_x;
    /* 0x0e */ short int rot_y;
    /* 0x10 */ short int rot_z;
    /* 0x12 */ short int pos_x;
    /* 0x14 */ short int pos_y;
    /* 0x16 */ short int pos_z;
} tNW_VehiclePosRotUpdateMessage;

#endif
