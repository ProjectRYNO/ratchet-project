#ifndef BUTTONTAG_H
#define BUTTONTAG_H
#include "SVTag.h"

typedef struct { // 0x15C
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ int m_fontSize;
    /* 0x0B8 */ int m_align;
    /* 0x0BC */ float m_displayLength;
    /* 0x0C0 */ char *m_link;
    /* 0x0C4 */ int m_drawBorder;
    /* 0x0C8 */ unsigned int m_linkOption;
    /* 0x0CC */ unsigned int m_textColor;
    /* 0x0D0 */ unsigned int m_highlightFillColor;
    /* 0x0D4 */ unsigned int m_highlightLineColor;
    /* 0x0D8 */ unsigned int m_highlightTextColor;
    /* 0x0DC */ char m_text[128];
} ButtonTagState;
#endif
