#ifndef RTCOMMSOCK_H
#define RTCOMMSOCK_H

#include "SVSock.h"
typedef struct { // 0xA0
    /* 0x00 */ SVSockState base;
    /* 0x0C */ void *m_rtCommCID;
    /* 0x10 */ unsigned char m_OutBuffer[0x28];
    /* 0x38 */ char m_szHostnameBeingLookedUp[64];
    /* 0x78 */ int m_bNonBlocking;
    /* 0x7C */ void *m_pScratchBuffer;
    /* 0x80 */ const void *addressVtable;
    /* 0x84 */ unsigned int unrecovered84;
    /* 0x88 */ unsigned long address;
    /* 0x90 */ unsigned char unrecovered90[8];
    /* 0x98 */ int m_eSynchronous;
    /* 0x9C */ unsigned char padding9C[4];
} RTCommSockState;

#endif
