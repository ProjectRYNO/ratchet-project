#ifndef TEXTTAG_H
#define TEXTTAG_H
#include "SVTag.h"

typedef struct { // 0x148 (verified prefix)
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ unsigned char unrecoveredB4[0x90];
    /* 0x144 */ char *m_link;
} TextTagState;

#endif
