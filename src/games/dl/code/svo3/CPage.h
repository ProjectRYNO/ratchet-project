#ifndef CPAGE_H
#define CPAGE_H
#include "SVDisplayBuffer.h"

// Verified prefix, not the complete 0x637C-byte page allocation.
struct CPage { // 0x6360 (prefix)
    /* 0x0000 */ unsigned char unrecovered[0x3A30];
    /* 0x3A30 */ int m_bIsActive;
    /* 0x3A34 */ unsigned char unrecovered3A34[0x20DC];
    /* 0x5B10 */ int m_state;
    /* 0x5B14 */ unsigned char unrecovered5B14[0x844];
    /* 0x6358 */ SVDisplayBufferState *m_pFrontDisplayBuffer;
    /* 0x635C */ SVDisplayBufferState *m_pBackDisplayBuffer;
};
extern "C" void followLink(CPage *page, char *link, int option);
#endif
