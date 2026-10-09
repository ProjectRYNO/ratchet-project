#ifndef SUBMITINPUTTAG_H
#define SUBMITINPUTTAG_H
#include "SVTag.h"
#include "FormTag.h"
struct SubmitInputTagState { // 0x158
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ int m_fontSize;
    /* 0x0B8 */ int m_align;
    /* 0x0BC */ char m_value[128];
    /* 0x13C */ float m_displayLength;
    /* 0x140 */ unsigned int m_buttonType;
    /* 0x144 */ unsigned int m_textColor;
    /* 0x148 */ unsigned int m_highlightFillColor;
    /* 0x14C */ unsigned int m_highlightLineColor;
    /* 0x150 */ unsigned int m_highlightTextColor;
    /* 0x154 */ FormTag *m_parentForm;
};
#endif
