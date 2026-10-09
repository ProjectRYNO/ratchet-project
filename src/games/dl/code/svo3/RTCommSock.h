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

typedef struct { // 0x18
    /* 0x00 */ const void *vtable;
    /* 0x04 */ unsigned int padding04;
    /* 0x08 */ unsigned long address[2];
} SVRTCommAddrState;
typedef struct { // 0x08
    /* 0x00 */ unsigned int Addr[2];
} RTLinkAddress;
typedef struct { // 0x10C
    /* 0x000 */ char szHostName[256];
    /* 0x100 */ RTLinkAddress NSServerIP;
    /* 0x108 */ void (*pfCommLookupCB)(const void *);
} RTCommLookupParams;
typedef struct { // 0x10
    /* 0x00 */ int type;
    /* 0x04 */ int maxMsgLen;
    /* 0x08 */ unsigned int nonBlockingConnect;
    /* 0x0C */ unsigned int synchronousReceive;
} RTCommChannelOptions;
typedef struct { // 0x4C (vtable prefix)
    /* 0x00 */ SVSockVtablePrefix base;
    /* 0x44 */ long (*getSynchronous)(RTCommSockState *);
    /* 0x48 */ long (*getErrNo)(RTCommSockState *);
} RTCommSockVtablePrefix;
typedef struct __attribute__((packed)) { // 0x08
    /* 0x00 */ unsigned long value;
} RTUnalignedWord;

#endif
