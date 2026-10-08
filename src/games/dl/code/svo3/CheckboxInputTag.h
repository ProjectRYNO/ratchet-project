#ifndef CHECKBOXINPUTTAG_H
#define CHECKBOXINPUTTAG_H
#include "SVTag.h"
#include "FormTag.h"
struct CheckboxInputTagState { // 0x194
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ int m_fontSize;
    /* 0x0B8 */ int m_isChecked;
    /* 0x0BC */ char m_text[100];
    /* 0x120 */ char m_value[100];
    /* 0x184 */ unsigned int m_textColor;
    /* 0x188 */ unsigned int m_highlightColor;
    /* 0x18C */ FormTag *m_parentForm;
    /* 0x190 */ int m_bSubmitAsEncryped;
};
#endif
