#ifndef TICKERTAG_H
#define TICKERTAG_H
#include "SVTag.h"

typedef struct { // 0xC8
    /* 0x000 */ SVTag base;
    /* 0xB4 */ int m_fontSize;
    /* 0xB8 */ int m_align;
    /* 0xBC */ float m_displayLength;
    /* 0xC0 */ char *m_text;
    /* 0xC4 */ unsigned int m_type;
} TickerTagState;
#endif
