#ifndef TEXTEDITABLETAG_H
#define TEXTEDITABLETAG_H
#include "SVTag.h"
#include "CInputContextBase.h"
typedef struct { // 0x70 (vtable prefix)
    /* 0x00 */ SVTagVtablePrefix base;
    /* 0x4C */ unsigned char unrecovered4C[0x1C];
    /* 0x68 */ void (*HandleTextEntry)(SVTag *, CInputContextBaseState *);
    /* 0x6C */ void (*ScrollText)(SVTag *, signed char);
} TextEditableTagVtablePrefix;
#endif
