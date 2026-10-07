#ifndef TEXTINPUTTAG_H
#define TEXTINPUTTAG_H
#include "SVTag.h"

typedef struct { // 0x2DC (verified prefix)
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ void *m_parentForm;
    /* 0x0B8 */ char m_text[512];
    /* 0x2B8 */ unsigned char unrecovered2B8[0x20];
    /* 0x2D8 */ int m_maxLengthUTF8Chars;
} TextInputTagState;

#endif
