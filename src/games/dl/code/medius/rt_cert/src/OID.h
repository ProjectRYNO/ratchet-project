#ifndef MEDIUS_OID_H
#define MEDIUS_OID_H

typedef enum { OID_UNKNOWN = 0 } OID;

// One gOIDs entry: an OID and its DER encoding. Field names are ours; the prototype
// declares OIDDATA gOIDs[] without a layout. The table ends with OID_UNKNOWN.
typedef struct { // 0x18
    /* 0x00 */ OID oid;
    /* 0x04 */ unsigned int nSize;
    /* 0x08 */ unsigned char data[16];
} OIDDATA;

#endif
