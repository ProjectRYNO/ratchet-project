#ifndef SELECTTAG_H
#define SELECTTAG_H
#include "SVTag.h"
#include "FormTag.h"

struct SelectTagState { // 0xF4 (verified prefix)
    /* 0x00 */ SVTag base;
    /* 0xB4 */ unsigned char unrecoveredB4[0x10];
    /* 0xC4 */ int m_numOptions;
    /* 0xC8 */ int m_currOptionIdx;
    /* 0xCC */ iks **m_options;
    /* 0xD0 */ char **m_values;
    /* 0x0D4 */ unsigned char unrecoveredD4[0x1C];
    /* 0x0F0 */ FormTag *m_parentForm;
};

#endif
