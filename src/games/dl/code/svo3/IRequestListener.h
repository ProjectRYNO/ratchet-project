#ifndef IREQUESTLISTENER_H
#define IREQUESTLISTENER_H
struct IRequestListenerState;
typedef struct { // 0x0C
    /* 0x00 */ char *data;
    /* 0x04 */ int size;
    /* 0x08 */ void *context;
} URIReceiveBuffer;
typedef struct { // 0x20 (vtable prefix)
    /* 0x00 */ unsigned char unrecovered00[8];
    /* 0x08 */ void (*OnURIRequestStart)(IRequestListenerState *, void *);
    /* 0x0C */ long (*OnURIRequestHeaderReceived)(IRequestListenerState *, void *, int, int, unsigned int);
    /* 0x10 */ void (*OnURIRequestRedirectReceived)(IRequestListenerState *, void *, char *);
    /* 0x14 */ void (*OnURIRequestChunkReceived)(IRequestListenerState *listener, void *listenerContext, void *context, char *data, int bytesRead);
    /* 0x18 */ long (*OnURIRequestIsOkContinueDownload)(IRequestListenerState *, void *, URIReceiveBuffer *);
    /* 0x1C */ void (*OnURIRequestCompletion)(IRequestListenerState *listener, void *context, int status);
} IRequestListenerVtablePrefix;
struct IRequestListenerState { // 0x04
    /* 0x00 */ const IRequestListenerVtablePrefix *vtable;
};
#endif
