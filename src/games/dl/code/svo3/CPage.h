#ifndef CPAGE_H
#define CPAGE_H
#include "SVDisplayBuffer.h"
#include "PageHistory.h"
#include "SVChronograph.h"
struct SVTag;

// Verified prefix, not the complete 0x637C-byte page allocation.
struct CPage { // 0x6360 (prefix)
    /* 0x0000 */ unsigned char unrecovered0000[0x1A78];
    /* 0x1A78 */ int preTransitionCount;
    /* 0x1A7C */ unsigned char unrecovered1A7C[0x1A98];
    /* 0x3514 */ int postTransitionCount;
    /* 0x3518 */ unsigned char unrecovered3518[0x4F0];
    /* 0x3A08 */ int inTransitionCount;
    /* 0x3A0C */ unsigned char unrecovered3A0C[0x20];
    /* 0x3A2C */ int m_bIsPopup;
    /* 0x3A30 */ int m_bIsActive;
    /* 0x3A34 */ unsigned char unrecovered3A34[0xA4];
    /* 0x3AD8 */ PageHistoryState m_history;
    /* 0x5AFC */ SVChronographState m_pageRefreshTimer;
    /* 0x5B0C */ int m_pageRefreshSeconds;
    /* 0x5B10 */ int m_state;
    /* 0x5B14 */ void *m_callbackData;
    /* 0x5B18 */ SVTag *m_defTextEntryTag;
    /* 0x5B1C */ SVTag *m_defTextScrollTag;
    /* 0x5B20 */ unsigned char unrecovered5B20[0x28];
    /* 0x5B48 */ SVDisplayBufferState m_displayBuffers[2];
    /* 0x6358 */ SVDisplayBufferState *m_pFrontDisplayBuffer;
    /* 0x635C */ SVDisplayBufferState *m_pBackDisplayBuffer;
};
extern "C" void followLink(CPage *page, char *link, int option);
#endif
