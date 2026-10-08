#ifndef HIDDENINPUTTAG_H
#define HIDDENINPUTTAG_H
#include "SVTag.h"
#include "FormTag.h"
struct HiddenInputTagState { // 0x1BC
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ char m_value[256];
    /* 0x1B4 */ FormTag *m_parentForm;
    /* 0x1B8 */ int m_bSubmitAsEncryped;
};
#endif
