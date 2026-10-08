#ifndef SUBMITINPUTTAG_H
#define SUBMITINPUTTAG_H
#include "SVTag.h"
#include "FormTag.h"
struct SubmitInputTagState { // 0x158
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ unsigned char unrecoveredB4[0xA0];
    /* 0x154 */ FormTag *m_parentForm;
};
#endif
