#ifndef CREATEGAMETAGMODULE_H
#define CREATEGAMETAGMODULE_H
#include "SVTagModule.h"

typedef struct { // 0x214
    /* 0x000 */ SVTagModuleState base;
    /* 0x004 */ char m_createGameParamNames[257];
    /* 0x105 */ char m_createGameSubmitBaseURL[257];
    /* 0x206 */ unsigned char padding206[2];
    /* 0x208 */ char **m_createGameParamStrPtrs;
    /* 0x20C */ int m_createGameNumOfParams;
    /* 0x210 */ int m_SVOGameID;
} CreateGameTagModuleState;

#endif
