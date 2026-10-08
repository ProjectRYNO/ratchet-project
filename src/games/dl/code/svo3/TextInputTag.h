#ifndef TEXTINPUTTAG_H
#define TEXTINPUTTAG_H
#include "SVTag.h"
#include "FormTag.h"

struct TextInputTagState { // 0x514
    /* 0x000 */ SVTag base;
    /* 0x0b4 */ FormTag *m_parentForm;
    /* 0x0b8 */ char m_text[512];
    /* 0x2b8 */ int m_bEditable;
    /* 0x2bc */ int m_numKeyboards;
    /* 0x2c0 */ int m_curEditOffset;
    /* 0x2c4 */ int m_fontSize;
    /* 0x2c8 */ int m_node;
    /* 0x2cc */ int m_obj;
    /* 0x2d0 */ int m_upRightOffset;
    /* 0x2d4 */ int m_upLeftOffset;
    /* 0x2d8 */ int m_maxLengthUTF8Chars;
    /* 0x2dc */ int m_curLeftOffset;
    /* 0x2e0 */ int m_curRightOffset;
    /* 0x2e4 */ char m_keyboardInput[512];
    /* 0x4e4 */ float m_maxWrap;
    /* 0x4e8 */ float m_opacity;
    /* 0x4ec */ float m_nx;
    /* 0x4f0 */ float m_ny;
    /* 0x4f4 */ int m_blinkCursor;
    /* 0x4f8 */ int m_drawCursor;
    /* 0x4fc */ unsigned int m_textColor;
    /* 0x500 */ unsigned int m_highlightFillColor;
    /* 0x504 */ unsigned int m_highlightLineColor;
    /* 0x508 */ unsigned int m_highlightTextColor;
    /* 0x50c */ int m_bSubmitAsEncryped;
    /* 0x510 */ int m_bRequiredForSubmit;
};

typedef struct { // 0x80 (vtable prefix)
    /* 0x00 */ SVTagVtablePrefix base;
    /* 0x4C */ unsigned char unrecovered4C[0x30];
    /* 0x7C */ float (*getSubstringPixelWidth)(TextInputTagState *, int, int);
} TextInputTagVtablePrefix;
#endif
