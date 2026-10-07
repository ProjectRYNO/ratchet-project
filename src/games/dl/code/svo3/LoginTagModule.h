#ifndef LOGINTAGMODULE_H
#define LOGINTAGMODULE_H
#include "SVTagModule.h"

typedef struct { // 0x08
    /* 0x00 */ SVTagModuleState base;
    /* 0x04 */ int m_bHaveUnhandledLoginResponse;
} LoginTagModuleState;

#endif
