#ifndef RTCOMMSOCK_H
#define RTCOMMSOCK_H

typedef struct { // 0x9C (verified prefix)
    /* 0x00 */ unsigned char unrecovered00[0x78];
    /* 0x78 */ int m_bNonBlocking;
    /* 0x7C */ unsigned char unrecovered7C[0x1C];
    /* 0x98 */ int m_eSynchronous;
} RTCommSockState;

#endif
