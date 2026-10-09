#ifndef CHTTP_H
#define CHTTP_H
#include "SVSock.h"
#include "SVChronograph.h"
#include "CQueryParams.h"
#include "IRequestListener.h"
struct HttpState;
typedef struct { // 0x20
    /* 0x00 */ char *scheme;
    /* 0x04 */ char *host;
    /* 0x08 */ int port;
    /* 0x0C */ char *filePath;
    /* 0x10 */ CQueryParamListState *params;
    /* 0x14 */ int methodType;
    /* 0x18 */ char *httpCommand;
    /* 0x1C */ void *context;
} URIRequest;

typedef struct { // 0x58 (vtable prefix)
    /* 0x00 */ unsigned char unrecovered00[0x0C];
    /* 0x0C */ int (*doRequest)(HttpState *, URIRequest *, IRequestListenerState *, void *);
    /* 0x10 */ unsigned char unrecovered10[0x24];
    /* 0x34 */ void (*HttpSendRequest)(HttpState *, char *, int, char **, int *);
    /* 0x38 */ long (*HttpsDownload)(HttpState *, char *, int, char **, int *, char **, int *);
    /* 0x3C */ void (*PrintHeader)(HttpState *);
    /* 0x40 */ void (*PrintFooter)(HttpState *);
    /* 0x44 */ void (*PrintRequestHeader)(HttpState *);
    /* 0x48 */ void (*PrintRequestFooter)(HttpState *);
    /* 0x4C */ long (*IsSecure)(HttpState *http);
    /* 0x50 */ void (*HttpCleanup)(HttpState *);
    /* 0x54 */ void (*States)(HttpState *http);
} HttpVtablePrefix;
struct HttpState { // 0x8AC4
    /* 0x0000 */ const HttpVtablePrefix *vtable;
    /* 0x0004 */ int m_HttpState;
    /* 0x0008 */ char m_scheme[16];
    /* 0x0018 */ int m_bConnectionOpen;
    /* 0x001C */ SVAddr *m_addr;
    /* 0x0020 */ SVSockState *m_sock;
    /* 0x0024 */ int m_port;
    /* 0x0028 */ int m_headerBytesReceived;
    /* 0x002C */ int m_bodyBytesReceived;
    /* 0x0030 */ unsigned int m_contentLength;
    /* 0x0034 */ char m_nextLocation[257];
    /* 0x0135 */ unsigned char padding135[3];
    /* 0x0138 */ CMemoryContextBaseState *m_memoryContextPtr;
    /* 0x013C */ CQueryParamListState m_QueryParams;
    /* 0x0540 */ SVChronographState m_timer;
    /* 0x0550 */ char m_szFilePath[257];
    /* 0x0651 */ unsigned char padding651[3];
    /* 0x0654 */ int m_iMethodType;
    /* 0x0658 */ char m_szHostname[64];
    /* 0x0698 */ char m_headerBuf[32768];
    /* 0x8698 */ int m_bDownloadingBody;
    /* 0x869C */ int m_status;
    /* 0x86A0 */ int m_timeoutFrameCounter;
    /* 0x86A4 */ char m_httpCommandStr[5];
    /* 0x86A9 */ unsigned char padding86A9[3];
    /* 0x86AC */ CQueryParamListState m_savedServerParams;
    /* 0x8AB0 */ int m_serverParamsTooLong;
    /* 0x8AB4 */ int m_bNeedToPost302;
    /* 0x8AB8 */ int m_eSocketType;
    /* 0x8ABC */ IRequestListenerState *m_pListener;
    /* 0x8AC0 */ void *m_pListenerContext;
};
#endif
