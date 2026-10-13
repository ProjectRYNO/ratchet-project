#ifndef DATATAG_H
#define DATATAG_H
#include "SVTag.h"

struct DataTagState { // 0xBC
    /* 0x00 */ SVTag base;
    /* 0xB4 */ int m_dataTagType;
    /* 0xB8 */ int m_bAllowNavigationDuringDownload;
    DataTagState(iks *xml, CAllContextData *contexts) __asm__("DataTag");
};

#endif
