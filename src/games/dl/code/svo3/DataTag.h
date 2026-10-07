#ifndef DATATAG_H
#define DATATAG_H
#include "SVTag.h"

typedef struct { // 0xBC
    /* 0x00 */ SVTag base;
    /* 0xB4 */ int m_dataTagType;
    /* 0xB8 */ int m_bAllowNavigationDuringDownload;
} DataTagState;

#endif
