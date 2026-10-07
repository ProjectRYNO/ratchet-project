#ifndef CHTTP_H
#define CHTTP_H

typedef struct { // 0x8ABC (verified prefix)
    /* 0x0000 */ void *vtable;
    /* 0x0004 */ int m_HttpState;
    /* 0x0008 */ unsigned char unrecovered08[0x8AB0];
    /* 0x8AB8 */ int m_eSocketType;
} HttpState;

#endif
