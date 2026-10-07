#ifndef RECTANGLETAG_H
#define RECTANGLETAG_H
#include "SVTag.h"
#include "CPage.h"

typedef struct { // 0xD0
    /* 0x00 */ SVTag base;
    /* 0xB4 */ float m_zVal;
    /* 0xB8 */ int m_lineThickness;
    /* 0xBC */ int m_cornerRadius;
    /* 0xC0 */ unsigned int m_gradientColor[4];
} RectangleTagState;
#endif
