#ifndef TEXTINPUTTAG_H
#define TEXTINPUTTAG_H
#include "SVTag.h"
#include "FormTag.h"

struct TextInputTagState { // 0x4E4 (verified prefix)
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ FormTag *m_parentForm;
    /* 0x0B8 */ char m_text[512];
    /* 0x2B8 */ int m_bEditable;
    /* 0x2BC */ unsigned char unrecovered2BC[4];
    /* 0x2C0 */ int m_curEditOffset;
    /* 0x2C4 */ unsigned char unrecovered2C4[0x14];
    /* 0x2D8 */ int m_maxLengthUTF8Chars;
    /* 0x2DC */ int m_curLeftOffset;
    /* 0x2E0 */ int m_curRightOffset;
    /* 0x2E4 */ char m_keyboardInput[512];
};

#endif
