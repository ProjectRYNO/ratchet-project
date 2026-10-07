#ifndef LISTBOXTAG_H
#define LISTBOXTAG_H
#include "SVTag.h"

typedef struct { // 0x284 (verified prefix)
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ unsigned char unrecoveredB4[0x1CC];
    /* 0x280 */ int m_turnOffDraw;
} ListBoxTagState;

#endif
