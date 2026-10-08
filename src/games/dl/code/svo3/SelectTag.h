#ifndef SELECTTAG_H
#define SELECTTAG_H
#include "SVTag.h"
#include "FormTag.h"

struct SelectTagState { // 0xF4
    /* 0x000 */ SVTag base;
    /* 0xb4 */ int m_fontSize;
    /* 0xb8 */ int m_align;
    /* 0xbc */ float m_displayLength;
    /* 0xc0 */ char *m_text;
    /* 0xc4 */ int m_numOptions;
    /* 0xc8 */ int m_currOptionIdx;
    /* 0xcc */ iks **m_options;
    /* 0xd0 */ char **m_values;
    /* 0xd4 */ int m_enableGroupSelection;
    /* 0xd8 */ unsigned int m_textColor;
    /* 0xdc */ unsigned int m_highlightTextColor;
    /* 0xe0 */ unsigned int m_highlightLineColor;
    /* 0xe4 */ unsigned int m_highlightFillColor;
    /* 0xe8 */ int m_bSubmitAsEncryped;
    /* 0xec */ int m_bRequiredForSubmit;
    /* 0xf0 */ FormTag *m_parentForm;
};
#endif
