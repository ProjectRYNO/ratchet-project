#ifndef RADIOINPUTTAG_H
#define RADIOINPUTTAG_H
#include "SVTag.h"

typedef struct { // 0xBC (verified prefix)
    /* 0x00 */ SVTag base;
    /* 0xB4 */ int m_fontSize;
    /* 0xB8 */ int m_isChecked;
} RadioInputTagState;

#endif
