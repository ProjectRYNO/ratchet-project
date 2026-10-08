#include "md5.h"
#include "SVPersistentData.h"
#include "CCookie.h"
#include "CHttp.h"
#include "URISchemeMgr.h"
#include "CMemoryContextBase.h"
#include "stdlib.h"
#include "string.h"
#include "SVOString.h"
#include "SVTagModule.h"
#include "CError.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_CHttp_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern "C" {
void SetHttpState(HttpState *http, int state);

extern "C" {
extern char svoHttpSource[];
extern char svoHttpVersionPrefix[];
long GetHttpState(HttpState *http);
char *parseHttpStatusLine(HttpState *http, char *cursor);
long parseHttpHeaderLine(HttpState *http, char **cursor, int *contentType);
}
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoHttpSource[];
void * CHttpoperator_new___dupe4(unsigned int size, CMemoryContextBaseState *memory) __asm__("operator.new___dupe4");

}
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
void CHttpoperator_delete___dupe3(void *memory) __asm__("operator.delete___dupe3");

}
extern "C" {
extern const HttpVtablePrefix svoHttpVtable;
void InitRequest(HttpState *, int);
void setSocketType(HttpState *, int);
long getSocketType(HttpState *);
void closeSocket(HttpState *);
void OnBodyChunkReceived(HttpState *, void *, char *, int);
long downloadBody(HttpState *);
long downloadHeaders(HttpState *);
void handleRedirect(HttpState *);
int formRequestText(HttpState *, char *, char *, int, int, char *);
SVSockState *createSVSock(CMemoryContextBaseState *);

}
extern "C" {
extern char svoHttpHeaderEnd[];
void OnHeaderParsed(HttpState *, int);
long parseHeaderBuf(HttpState *);
void HttpIdleOnEnter(HttpState *http);
void HttpGetHostByNameOnEnter(HttpState *http);
void HttpGetHostByNameOnUpdate(HttpState *http);
void HttpConnectWaitOnEnter(HttpState *http);
void HttpConnectWaitOnUpdate(HttpState *http);
void HttpSendOnEnter(HttpState *http);
void HttpSendOnUpdate(HttpState *http);
void HttpRecvOnEnter(HttpState *http);
void HttpRecvOnUpdate(HttpState *http);

}
extern "C" {
extern char svoHttpMD5Suffix[];
extern char svoHttpEmptyString[];
char *strlwr(char *);
}
extern "C" {

}
#define SECTION(name) __attribute__((section(".svo_CHttp_" #name)))

SECTION(HttpsDestroy___dupe2) void HttpsDestroy___dupe2(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(HttpsCleanup___dupe2) void HttpsCleanup___dupe2(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(PrintRequestHeader___dupe2) void PrintRequestHeader___dupe2(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(PrintRequestFooter___dupe2) void PrintRequestFooter___dupe2(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(PrintHeader___dupe2) void PrintHeader___dupe2(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(PrintFooter___dupe2) void PrintFooter___dupe2(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(HttpIdleOnUpdate) void HttpIdleOnUpdate(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(HttpCleanup___dupe2) void HttpCleanup___dupe2(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(IsSecure___dupe2) long IsSecure___dupe2(void *self)
{
    return 0;
}

SECTION(HttpsPrepareRequestForServerHello) int HttpsPrepareRequestForServerHello(HttpState *http, char *request, int length, char **encrypted, int *encryptedLength)
{
    *encryptedLength = length;
    *encrypted = request;
    return 0;
}

SECTION(HttpSendRequest___dupe2) void HttpSendRequest___dupe2(HttpState *http, char *request, int length, char **encrypted, int *encryptedLength)
{
    *encryptedLength = length;
    *encrypted = request;
}

SECTION(HttpsDownload___dupe2) int HttpsDownload___dupe2(HttpState *http, char *hello, int length, char **response, int *responseLength, char **sendBack, int *sendBackLength)
{
    *response = 0;
    *responseLength = 0;
    *sendBack = 0;
    *sendBackLength = 0;
    return 0;
}

SECTION(HttpRecvOnEnter) void HttpRecvOnEnter(HttpState *http)
{
    SetHttpState(http, 13);
}

SECTION(HttpSendOnUpdate) void HttpSendOnUpdate(HttpState *http)
{
    SetHttpState(http, 12);
}

SECTION(SetStatePostRequest) void SetStatePostRequest(HttpState *http)
{
    SetHttpState(http, 3);
}

SECTION(HttpIdleOnEnter) void HttpIdleOnEnter(HttpState *http)
{
    SetHttpState(http, 2);
}

SECTION(GetHttpState) long GetHttpState(HttpState *http)
{
    return http->m_HttpState;
}

SECTION(setSocketType) void setSocketType(HttpState *http, int type)
{
    http->m_eSocketType = type;
}

}

extern "C" SECTION(_Http) void _Http(HttpState *http, unsigned int flags)
{
    http->vtable = &svoHttpVtable;
    if (http->m_sock) __SVO_Assert_Handler(svoHttpSource, 0x58);
    if (http->m_pListener) __SVO_Assert_Handler(svoHttpSource, 0x59);
    DeRegister((IURISchemeProviderState *)http);
    _CQueryParamList(&http->m_savedServerParams, 2);
    _SVChronograph(&http->m_timer, 2);
    _CQueryParamList(&http->m_QueryParams, 2);
    _IURISchemeProvider((IURISchemeProviderState *)http, 0);
    if (flags & 1) CHttpoperator_delete___dupe3(http);
}

extern "C" SECTION(closeSocket) void closeSocket(HttpState *http)
{
    SVSockState *socket = http->m_sock;
    if (socket && http->m_bConnectionOpen) {
        const SVSockVtablePrefix *vtable = (const SVSockVtablePrefix *)socket->vtable;
        http->m_bConnectionOpen = 0;
        vtable->Close(socket, 0);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", DoRegistrations2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", doRequest___dupe2);

extern "C" SECTION(download___dupe2) void download___dupe2(HttpState *http)
{
    http->vtable->States(http);
    if (GetHttpState(http) == 2 && http->m_pListener) {
        IRequestListenerState *listener = http->m_pListener;
        listener->vtable->OnURIRequestCompletion(listener, http->m_pListenerContext, 1);
        http->m_pListener = 0;
        http->m_pListenerContext = 0;
    }
}

extern "C" SECTION(downloadBody) long downloadBody(HttpState *http)
{
    int finished = 0;
    if (!http->m_sock) __SVO_Assert_Handler(svoHttpSource, 0x228);
    IRequestListenerState *listener = http->m_pListener;
    if (!listener) __SVO_Assert_Handler(svoHttpSource, 0x22C);
    else {
        URIReceiveBuffer buffer;
        buffer.data = 0;
        buffer.size = 0;
        if (listener->vtable->OnURIRequestIsOkContinueDownload(listener, http->m_pListenerContext, &buffer)) {
            int received = 0;
            if (!buffer.size) finished = 1;
            else {
                SVSockState *socket = http->m_sock;
                if (!((const SVSockVtablePrefix *)socket->vtable)->Recv(socket, buffer.data, buffer.size, &received, &finished)) SetErrorCode(0x15);
                else if (received) OnBodyChunkReceived(http, buffer.context, buffer.data, received);
            }
        }
    }
    return finished;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", downloadHeaders);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", formRequestText);

extern "C" SECTION(freeResources___dupe2) void freeResources___dupe2(HttpState *http, long shutdown)
{
    IRequestListenerState *listener = http->m_pListener;
    if (listener) {
        listener->vtable->OnURIRequestCompletion(listener, http->m_pListenerContext, 0);
        http->m_pListener = 0;
        http->m_pListenerContext = 0;
    }
    closeSocket(http);
    SVSockState *socket = http->m_sock;
    if (socket) {
        ((const SVSockVtablePrefix *)socket->vtable)->destroy(socket, 3);
        http->m_sock = 0;
    }
    if (http->m_addr) http->m_addr = 0;
    if (!shutdown) InitRequest(http, getSocketType(http));
}

extern "C" SECTION(getSocketType) long getSocketType(HttpState *http)
{
    if (http->m_eSocketType <= 0) __SVO_Assert_Handler(svoHttpSource, 0x67A);
    return http->m_eSocketType;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", handleRedirect);

extern "C" SECTION(Http) void Http(HttpState *http, CMemoryContextBaseState *memory, int type)
{
    IURISchemeProvider((IURISchemeProviderState *)http);
    http->vtable = &svoHttpVtable;
    CQueryParamList(&http->m_QueryParams);
    SVChronograph(&http->m_timer, 0);
    CQueryParamList(&http->m_savedServerParams);
    http->m_HttpState = 0;
    setSocketType(http, 0);
    http->m_serverParamsTooLong = 0;
    http->m_memoryContextPtr = memory;
    http->m_bNeedToPost302 = 0;
    http->m_pListener = 0;
    http->m_pListenerContext = 0;
    http->m_bConnectionOpen = 0;
    http->m_addr = 0;
    http->m_sock = 0;
    InitRequest(http, type);
}

extern "C" SECTION(HttpConnectWaitOnEnter) void HttpConnectWaitOnEnter(HttpState *http)
{
    SVSockState *socket = http->m_sock;
    if (!((const SVSockVtablePrefix *)socket->vtable)->Connect(socket, http->m_addr, http->m_port)) {
        SetErrorCode(0xF);
        return;
    }
    http->m_bConnectionOpen = 1;
    socket = http->m_sock;
    if (((const SVSockVtablePrefix *)socket->vtable)->GetNonBlocking(socket)) SetHttpState(http, 6);
    else SetHttpState(http, http->vtable->IsSecure(http) ? 7 : 10);
}

extern "C" SECTION(HttpConnectWaitOnUpdate) void HttpConnectWaitOnUpdate(HttpState *http)
{
    SVSockState *socket = http->m_sock;
    if (((const SVSockVtablePrefix *)socket->vtable)->isConnected(socket)) {
        SetHttpState(http, http->vtable->IsSecure(http) ? 7 : 10);
    }
}

extern "C" SECTION(HttpGetHostByNameOnEnter) void HttpGetHostByNameOnEnter(HttpState *http)
{
    int complete = 0;
    SVSockState *socket = http->m_sock;
    SVAddr *address = ((const SVSockVtablePrefix *)socket->vtable)->dnsLookup(
        socket, http->m_szHostname, http->m_memoryContextPtr, &complete);
    http->m_addr = address;
    if (!address) SetErrorCode(0x12);
    else SetHttpState(http, complete ? 5 : 4);
}

extern "C" SECTION(HttpGetHostByNameOnUpdate) void HttpGetHostByNameOnUpdate(HttpState *http)
{
    SVSockState *socket = http->m_sock;
    SVAddr *address = http->m_addr;
    if (((const SVSockVtablePrefix *)socket->vtable)->dnsLookupUpdate(socket, &address))
        SetHttpState(http, 5);
}

extern "C" SECTION(HttpRecvOnUpdate) void HttpRecvOnUpdate(HttpState *http)
{
    if (!http->m_sock) __SVO_Assert_Handler(svoHttpSource, 0x4CF);
    if (GetErrorCode()) return;
    long finished = http->m_bDownloadingBody ? downloadBody(http) : downloadHeaders(http);
    if (finished) {
        http->vtable->PrintHeader(http);
        if (http->m_status != 200 && http->m_status != 302) SetErrorCode(9);
        http->vtable->PrintFooter(http);
        if (http->m_status == 302) { finished = 0; handleRedirect(http); }
        Stop___dupe3(&http->m_timer);
    }
    if (http->m_timeoutFrameCounter >= 0xE11) { SetErrorCode(2); return; }
    ++http->m_timeoutFrameCounter;
    if (finished) {
        http->vtable->HttpCleanup(http);
        SetHttpState(http, 1);
    }
}

extern "C" SECTION(HttpSendOnEnter) void HttpSendOnEnter(HttpState *http)
{
    char request[0x1C00];
    int length = formRequestText(http, http->m_szFilePath, request, http->m_iMethodType, 0x1C00, http->m_httpCommandStr);
    if (strlen(request) >= 0x1C00) __SVO_Assert_Handler(svoHttpSource, 0x51B);
    http->vtable->PrintRequestHeader(http);
    http->vtable->PrintRequestFooter(http);
    char *data;
    int bytes;
    http->vtable->HttpSendRequest(http, request, length, &data, &bytes);
    unsigned long sent;
    SVSockState *socket = http->m_sock;
    if (!((const SVSockVtablePrefix *)socket->vtable)->Send(socket, data, bytes, &sent)) SetErrorCode(0xF);
    SetHttpState(http, 11);
}

extern "C" SECTION(InitRequest) void InitRequest(HttpState *http, int type)
{
    http->m_bConnectionOpen = 0;
    if (http->m_addr) http->m_addr = 0;
    memset(http->m_headerBuf, 0, 0x8000);
    memset(http->m_nextLocation, 0, 0x101);
    http->m_port = 0;
    http->m_scheme[0] = 0;
    http->m_headerBytesReceived = 0;
    http->m_bodyBytesReceived = 0;
    http->m_status = 0;
    http->m_contentLength = 0;
    http->m_timeoutFrameCounter = 0;
    if (http->m_memoryContextPtr && !http->m_sock) http->m_sock = createSVSock(http->m_memoryContextPtr);
    setSocketType(http, type);
    SVSockState *socket = http->m_sock;
    int socketType = getSocketType(http);
    ((const SVSockVtablePrefix *)socket->vtable)->setSynchronous(socket, socketType);
}

extern "C" SECTION(IsBusy) long IsBusy(HttpState *http)
{
    long state = GetHttpState(http);
    return state != 0 && state != 2;
}

extern "C" SECTION(LoadStatePostGameFromPersistentData___dupe2) long LoadStatePostGameFromPersistentData___dupe2(HttpState *http, SVPersistentData *persist)
{
    CCookieJar *jar = getInstance(http->m_memoryContextPtr);
    if (!jar) __SVO_Assert_Handler(svoHttpSource, 0x44A);
    memcpy(jar->m_cookies, persist->cookieData, 2032);
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", md5request);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", md5requestLogin);

extern "C" SECTION(OnBodyChunkReceived) void OnBodyChunkReceived(HttpState *http, void *context, char *data, int bytesRead)
{
    http->m_timeoutFrameCounter = 0;
    IRequestListenerState *listener = http->m_pListener;
    http->m_bodyBytesReceived += bytesRead;
    listener->vtable->OnURIRequestChunkReceived(listener, http->m_pListenerContext, context, data, bytesRead);
}

extern "C" SECTION(OnHeaderParsed) void OnHeaderParsed(HttpState *http, int type)
{
    if (!http->m_sock) __SVO_Assert_Handler(svoHttpSource, 0x2CC);
    IRequestListenerState *listener = http->m_pListener;
    if (!listener) { __SVO_Assert_Handler(svoHttpSource, 0x2D0); return; }
    listener->vtable->OnURIRequestHeaderReceived(listener, http->m_pListenerContext, type, http->m_status, http->m_contentLength);
    if (http->m_status == 302) return;
    char *body = strstr(http->m_headerBuf, svoHttpHeaderEnd);
    if (!body) __SVO_Assert_Handler(svoHttpSource, 0x2DA);
    body += 4;
    int length = http->m_headerBytesReceived - (body - http->m_headerBuf);
    http->m_bDownloadingBody = 1;
    http->m_bodyBytesReceived = 0;
    URIReceiveBuffer buffer;
    listener = http->m_pListener;
    long ready = listener->vtable->OnURIRequestIsOkContinueDownload(listener, http->m_pListenerContext, &buffer);
    EnsureCleanBlocks(GetMemoryContext());
    if (ready) {
        if (buffer.size < length) __SVO_Assert_Handler(svoHttpSource, 0x2EC);
        memcpy(buffer.data, body, length);
        OnBodyChunkReceived(http, buffer.context, buffer.data, length);
    } else __SVO_Assert_Handler(svoHttpSource, 0x2F4);
    EnsureCleanBlocks(GetMemoryContext());
    memset(body, 0, length);
    EnsureCleanBlocks(GetMemoryContext());
}

extern "C" SECTION(operator.delete___dupe3) void CHttpoperator_delete___dupe3(void *memory)
{
    svFreeSafe(((HttpState *)memory)->m_memoryContextPtr, memory);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", operator.new___dupe4);

extern "C" SECTION(parseHeaderBuf) long parseHeaderBuf(HttpState *http)
{
    int contentType = 0;
    char *cursor = parseHttpStatusLine(http, http->m_headerBuf);
    if (!cursor) {
        __SVO_Assert_Handler(svoHttpSource, 0x2B3);
        http->m_status = 600;
    } else {
        while (parseHttpHeaderLine(http, &cursor, &contentType)) {}
    }
    return contentType;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", parseHttpHeaderLine);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", parseHttpStatusLine);

extern "C" SECTION(SaveStatePreGameToPersistentData) long SaveStatePreGameToPersistentData(HttpState *http, SVPersistentData *persist)
{
    CCookieJar *jar = getInstance(http->m_memoryContextPtr);
    if (!jar) __SVO_Assert_Handler(svoHttpSource, 0x454);
    memcpy(persist->cookieData, jar->m_cookies, 2032);
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", SetHttpState);

extern "C" SECTION(States___dupe2) long States___dupe2(HttpState *http)
{
    long state = GetHttpState(http);
    if (state == 1) { HttpIdleOnEnter(http); return 0; }
    if (state == 2) { HttpIdleOnUpdate(http); return 1; }
    if (state == 3) { HttpGetHostByNameOnEnter(http); return 0; }
    if (state == 4) { HttpGetHostByNameOnUpdate(http); return 0; }
    if (state == 5) { HttpConnectWaitOnEnter(http); return 0; }
    if (state == 6) { HttpConnectWaitOnUpdate(http); return 0; }
    if (state == 10) { HttpSendOnEnter(http); return 0; }
    if (state == 11) { HttpSendOnUpdate(http); return 0; }
    if (state == 12) { HttpRecvOnEnter(http); return 0; }
    if (state == 13) { HttpRecvOnUpdate(http); return 0; }
    int line = 0x66B;
    if (state == 0) line = 0x65C;
    else if (state == 7) line = 0x65F;
    else if (state == 8) line = 0x662;
    else if (state == 9) line = 0x665;
    else if (state == 14) line = 0x668;
    __SVO_Assert_Handler(svoHttpSource, line);
    return 0;
}
