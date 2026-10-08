#ifndef IMAGETAG_H
#define IMAGETAG_H
#include "SVTag.h"
#include "FormTag.h"

typedef struct { // 0x170
    /* 0x000 */ SVTag base;
    /* 0x0b4 */ int m_align;
    /* 0x0b8 */ float m_displayLength;
    /* 0x0bc */ char m_link[128];
    /* 0x13c */ unsigned int m_imageType;
    /* 0x140 */ int m_iID;
    /* 0x144 */ float m_fu0;
    /* 0x148 */ float m_fv0;
    /* 0x14c */ float m_fu1;
    /* 0x150 */ float m_fv1;
    /* 0x154 */ int Width;
    /* 0x158 */ int Height;
    /* 0x15c */ int PosX;
    /* 0x160 */ int PosY;
    /* 0x164 */ float u0;
    /* 0x168 */ float v0;
    /* 0x16c */ char *ImageBuf;
} ImageTagState;
#endif
