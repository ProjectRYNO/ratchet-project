#ifndef STATICIMAGETAG_H
#define STATICIMAGETAG_H
#include "SVTag.h"
#include "FormTag.h"

typedef struct { // 0x170
    /* 0x000 */ SVTag base;
    /* 0x0b4 */ char m_link[128];
    /* 0x134 */ char m_imageName[32];
    /* 0x154 */ float u0;
    /* 0x158 */ float v0;
    /* 0x15c */ int m_imageWidth;
    /* 0x160 */ int m_imageHeight;
    /* 0x164 */ int m_imageX;
    /* 0x168 */ int m_imageY;
    /* 0x16c */ int m_index;
} StaticImageTagState;
#endif
