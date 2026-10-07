#ifndef REDIRECTTAG_H
#define REDIRECTTAG_H

#include "SVTag.h"
#include "CPage.h"

typedef struct { // 0xBC
    /* 0x00 */ SVTag base;
    /* 0xB4 */ char *m_link;
    /* 0xB8 */ int m_alreadyRedirected;
} RedirectTagState;
#endif
