#ifndef CPAGE_H
#define CPAGE_H

// Verified prefix, not the complete 0x637C-byte page allocation.
struct CPage { // 0x5B14 (prefix)
    /* 0x0000 */ unsigned char unrecovered[0x5B10];
    /* 0x5B10 */ int m_state;
};
extern "C" void followLink(CPage *page, char *link, int option);
#endif
