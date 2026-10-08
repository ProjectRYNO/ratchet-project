#ifndef TEXTTAG_H
#define TEXTTAG_H
#include "SVTag.h"

typedef struct { // 0x14C
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ int m_fontSize;
    /* 0x0B8 */ int m_align;
    /* 0x0BC */ unsigned int m_textColor;
    /* 0x0C0 */ float m_displayLength;
    /* 0x0C4 */ char m_text[128];
    /* 0x144 */ char *m_link;
    /* 0x148 */ unsigned int m_linkOption;
} TextTagState;
#endif
