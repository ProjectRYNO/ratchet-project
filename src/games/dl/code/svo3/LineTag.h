#ifndef LINETAG_H
#define LINETAG_H
#include "SVTag.h"
#include "CPage.h"

typedef struct { // 0xC0
    /* 0x00 */ SVTag base;
    /* 0xB4 */ float m_endX;
    /* 0xB8 */ float m_endY;
    /* 0xBC */ float m_thickness;
} LineTagState;
#endif
