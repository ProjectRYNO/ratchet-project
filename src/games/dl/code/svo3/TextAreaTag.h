#ifndef TEXTAREATAG_H
#define TEXTAREATAG_H
#include "SVTag.h"

typedef struct { // 0xBC (verified prefix)
    /* 0x00 */ SVTag base;
    /* 0xB4 */ char *m_text;
    /* 0xB8 */ int m_maxTextSize;
} TextAreaTagState;

#endif
