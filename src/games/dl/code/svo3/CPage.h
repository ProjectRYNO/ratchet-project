#ifndef CPAGE_H
#define CPAGE_H
#include "SVDisplayBuffer.h"
#include "CInputContextBase.h"
#include "DownloadBinary.h"
#include "PageRequestListener.h"
#include "URISchemeMgr.h"
#include "PageHistory.h"
#include "SVChronograph.h"
struct SVTag;

// Retail page allocation, with typed request listener and callback tail.
struct CPage { // 0x637C
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
    /* 0x5B24 */ PageRequestListenerState m_requestListener;
    /* 0x5B48 */ SVDisplayBufferState m_displayBuffers[2];
    /* 0x6358 */ SVDisplayBufferState *m_pFrontDisplayBuffer;
    /* 0x635C */ SVDisplayBufferState *m_pBackDisplayBuffer;
    /* 0x6360 */ DownloadCallback m_pfSVMLPreTagCreateScanCB;
    /* 0x6364 */ DownloadCallback m_pfXMLScanCB;
    /* 0x6368 */ DownloadCallback m_pfSVMLTagCreateCB;
    /* 0x636C */ DownloadCallback m_pfBinaryDownloadCB;
    /* 0x6370 */ char *m_pCURIContent;
    /* 0x6374 */ int m_iCURIContentLength;
    /* 0x6378 */ int m_bPreserveCurrentPage;
};
extern "C" long followLink(CPage *page, char *link, int option);
struct SVTag;
struct CDrawContextBase;

struct PageProviderDownloadVtable { // 0x14
    /* 0x00 */ unsigned char prefix[0x10];
    /* 0x10 */ void (*download)(IURISchemeProviderState *);
};

struct PageAnimationVtable { // 0x70
    /* 0x00 */ unsigned char prefix[0x68];
    /* 0x68 */ long (*AnimateOut)(CDrawContextBase *);
    /* 0x6C */ long (*AnimateIn)(CDrawContextBase *);
};

struct PageDownloadVtable { // 0xC
    /* 0x00 */ unsigned char prefix[8];
    /* 0x08 */ void (*destroy)(DownloadBinaryState *, int);
};

struct PageTagInputVtable { // 0x10
    /* 0x00 */ unsigned char prefix[0x0C];
    /* 0x0C */ long (*HandleInput)(SVTag *, CPage *);
};

struct PageInputQueryVtable { // 0x40
    /* 0x00 */ unsigned char prefix[0x38];
    /* 0x38 */ long (*QueryBackInput)(CInputContextBaseState *);
    /* 0x3C */ long (*QueryRefreshInput)(CInputContextBaseState *);
};
struct CSystemContextBase;
struct PageStaticScreenVtable { // 0x30
    /* 0x00 */ unsigned char prefix[0x2C];
    /* 0x2C */ void (*EnterStaticScreen)(CSystemContextBase *, char *);
};
#endif
