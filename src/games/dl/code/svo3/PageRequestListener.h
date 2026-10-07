#ifndef PAGEREQUESTLISTENER_H
#define PAGEREQUESTLISTENER_H
#include "CMemoryContextBase.h"
typedef struct { // 0x0C
    /* 0x00 */ char *data;
    /* 0x04 */ unsigned int length;
    /* 0x08 */ void *context;
} DownloadBuffer;
typedef struct { // 0x24
    /* 0x00 */ const void *vtable;
    /* 0x04 */ int m_completionStatus;
    /* 0x08 */ char *m_pBodyData;
    /* 0x0C */ unsigned int m_bodyDataLength;
    /* 0x10 */ int m_bodyContentType;
    /* 0x14 */ unsigned int m_bodyDataAmountReceived;
    /* 0x18 */ CMemoryContextBaseState *m_pMemoryContext;
    /* 0x1C */ unsigned int m_downloadBufferLength;
    /* 0x20 */ int m_bFinished;
} PageRequestListenerState;
#endif
