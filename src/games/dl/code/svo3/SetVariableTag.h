#ifndef SETVARIABLETAG_H
#define SETVARIABLETAG_H
#include "SVTag.h"

typedef struct { // 0xBC
    /* 0x000 */ SVTag base;
    /* 0xB4 */ int m_pageRefreshSeconds;
    /* 0xB8 */ char *m_myExternalIP;
} SetVariableTagState;
#endif
