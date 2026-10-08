#ifndef HTTPSECURE_H
#define HTTPSECURE_H
#include "CHttp.h"
struct HttpSecureState;
typedef struct { // 0x30
    /* 0x00 */ int state;
    /* 0x04 */ unsigned char unrecovered04[12];
    /* 0x10 */ char *received;
    /* 0x14 */ int receivedLength;
    /* 0x18 */ char *request;
    /* 0x1C */ int requestLength;
    /* 0x20 */ char *sendBack;
    /* 0x24 */ int sendBackLength;
    /* 0x28 */ char *decrypted;
    /* 0x2C */ int decryptedLength;
} SSLCallbackParams;
typedef struct { // 0x70 (vtable prefix)
    /* 0x00 */ HttpVtablePrefix base;
    /* 0x58 */ void (*HttpsCallEngine)(HttpSecureState *, SSLCallbackParams *);
    /* 0x5C */ unsigned char unrecovered5C[8];
    /* 0x64 */ void (*ConnectingOnEnter)(HttpSecureState *);
    /* 0x68 */ void (*ConnectingOnUpdate1)(HttpSecureState *);
    /* 0x6C */ void (*ConnectingOnUpdate2)(HttpSecureState *);
} HttpSecureVtablePrefix;
struct HttpSecureState { // 0x8ACC (verified prefix)
    /* 0x0000 */ HttpState base;
    /* 0x8AC4 */ void *engine;
    /* 0x8AC8 */ int state;
};
#endif
