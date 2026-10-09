#ifndef CPAGE_H
#define CPAGE_H
#include "SVDisplayBuffer.h"
#include "DownloadBinary.h"
#include "URISchemeMgr.h"
#include "PageHistory.h"
#include "SVChronograph.h"
struct SVTag;

// Verified prefix, not the complete 0x637C-byte page allocation.
struct CPage { // 0x6360 (prefix)
    /* 0x0000 */ DownloadBinaryState preTransition[11];
    /* 0x1A78 */ int preTransitionCount;
    /* 0x1A7C */ unsigned char preTransitionUsed[32];
    /* 0x1A9C */ DownloadBinaryState postTransition[11];
    /* 0x3514 */ int postTransitionCount;
    /* 0x3518 */ unsigned char postTransitionUsed[32];
    /* 0x3538 */ DownloadBinaryState inTransition[2];
    /* 0x3A08 */ int inTransitionCount;
    /* 0x3A0C */ unsigned char inTransitionUsed[32];
    /* 0x3A2C */ int m_bIsPopup;
    /* 0x3A30 */ int m_bIsActive;
    /* 0x3A34 */ iks *m_XML;
    /* 0x3A38 */ iksparser_struct *m_parser;
    /* 0x3A3C */ int m_lastHttpStatus;
    /* 0x3A40 */ int m_lastCURIContentType;
    /* 0x3A44 */ char m_scheme[16];
    /* 0x3A54 */ unsigned short m_port;
    /* 0x3A56 */ char m_serverName[128];
    /* 0x3AD6 */ unsigned char padding3AD6[2];
    /* 0x3AD8 */ PageHistoryState m_history;
    /* 0x5AFC */ SVChronographState m_pageRefreshTimer;
    /* 0x5B0C */ int m_pageRefreshSeconds;
    /* 0x5B10 */ int m_state;
    /* 0x5B14 */ void *m_callbackData;
    /* 0x5B18 */ SVTag *m_defTextEntryTag;
    /* 0x5B1C */ SVTag *m_defTextScrollTag;
    /* 0x5B20 */ IURISchemeProviderState *m_pRequestProvider;
    /* 0x5B24 */ unsigned char unrecovered5B24[0x24];
    /* 0x5B48 */ SVDisplayBufferState m_displayBuffers[2];
    /* 0x6358 */ SVDisplayBufferState *m_pFrontDisplayBuffer;
    /* 0x635C */ SVDisplayBufferState *m_pBackDisplayBuffer;
};
extern "C" void followLink(CPage *page, char *link, int option);
#endif
