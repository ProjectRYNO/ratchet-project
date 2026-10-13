#ifndef REDIRECTTAG_H
#define REDIRECTTAG_H

#include "SVTag.h"
#include "CPage.h"

struct RedirectTagState { // 0xBC
    /* 0x00 */ SVTag base;
    /* 0xB4 */ char *m_link;
    /* 0xB8 */ int m_alreadyRedirected;
    RedirectTagState(iks *xml, CAllContextData *contexts) __asm__("RedirectTag");
};
#endif
