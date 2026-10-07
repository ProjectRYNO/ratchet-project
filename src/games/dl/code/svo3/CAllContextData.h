#ifndef CALLCONTEXTDATA_H
#define CALLCONTEXTDATA_H

struct CDrawContextBase;
struct CInputContextBaseState;
struct CMemoryContextBaseState;
struct CSystemContextBase;
struct CPage;
#include "CAudioContextBase.h"

struct CAllContextData { // 0x18
    /* 0x00 */ CDrawContextBase *drawContext;
    /* 0x04 */ CInputContextBaseState *inputContext;
    /* 0x08 */ CMemoryContextBaseState *memoryContext;
    /* 0x0C */ CAudioContextBaseState *audioContext;
    /* 0x10 */ CSystemContextBase *systemContext;
    /* 0x14 */ CPage *pMain;
};
#endif
