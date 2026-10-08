#ifndef QUICKLINKTAG_H
#define QUICKLINKTAG_H
#include "SVTag.h"

typedef struct { // 0xC0
    /* 0x000 */ SVTag base;
    /* 0xB4 */ int m_padLinkButton;
    /* 0xB8 */ char *m_link;
    /* 0xBC */ unsigned int m_linkOption;
} QuickLinkTagState;
#endif
