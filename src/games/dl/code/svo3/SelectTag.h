#ifndef SELECTTAG_H
#define SELECTTAG_H
#include "SVTag.h"

typedef struct { // 0xD4 (verified prefix)
    /* 0x00 */ SVTag base;
    /* 0xB4 */ unsigned char unrecoveredB4[0x10];
    /* 0xC4 */ int m_numOptions;
    /* 0xC8 */ int m_currOptionIdx;
    /* 0xCC */ iks **m_options;
    /* 0xD0 */ char **m_values;
} SelectTagState;

#endif
