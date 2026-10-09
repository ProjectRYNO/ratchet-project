#include "SVBrowser.h"
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
#include "stdio.h"
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
extern char svoHttpSource[];
extern char svoHttpSetCookiePrefix[];
extern char svoHttpContentLengthPrefix[];
extern char svoHttpLocationPrefix[];
extern char svoHttpQueryDelimiter[];
extern char svoHttpHostDelimiter[];
extern char svoHttpPathDelimiter[];
extern char svoHttpParamDelimiter[];
extern char svoHttpContentTypePrefix[];
extern char svoHttpSVMLType[];
extern char svoHttpXMLType[];
extern char svoHttpHTMLType[];
extern char svoHttpGIFType[];
extern char svoHttpTM2Type[];
extern char svoHttpAMXType[];
extern char svoHttpBinaryType[];
void decodeURLEntityText(char *);
}
extern "C" {
extern char svoHttpSource[];
extern char svoHttpRequestFormat[];
extern char svoHttpVersionFormat[];
extern char svoHttpVersionValue[];
extern char svoHttpTargetTypeFormat[];
extern char svoHttpTargetIDFormat[];
extern char svoHttpTitleIDFormat[];
extern char svoHttpLoginMacFormat[];
extern char svoHttpMacFormat[];
extern char svoHttpBodyFormat[];
extern char svoHttpCRLF[];
void GetLoginInfo(SVBrowserPrefix *, char **, char **, int *, char **);
char *md5request(HttpState *, char *, char *, char *, char *);
char *md5requestLogin(HttpState *, char *, char *, char *, char *);
}
extern "C" {
extern char svoHttpSource[];
long GetHttpState(HttpState *);
extern char svoHttpStateIdleEnterOld[];
extern char svoHttpStateIdleUpdateOld[];
extern char svoHttpStateDNSLookupEnterOld[];
extern char svoHttpStateDNSLookupUpdateOld[];
extern char svoHttpStateConnectWaitEnterOld[];
extern char svoHttpStateConnectWaitUpdateOld[];
extern char svoHttpStateSendEnterOld[];
extern char svoHttpStateSendUpdateOld[];
extern char svoHttpStateReceiveEnterOld[];
extern char svoHttpStateReceiveUpdateOld[];
extern char svoHttpStateNotSetOld[];
extern char svoHttpStateSecureConnectEnterOld[];
extern char svoHttpStateSecureConnectUpdate1Old[];
extern char svoHttpStateSecureConnectUpdate2Old[];
extern char svoHttpStateMaxOld[];
extern char svoHttpStateDefaultOld[];
extern char svoHttpStateIdleEnterNew[];
extern char svoHttpStateIdleUpdateNew[];
extern char svoHttpStateDNSLookupEnterNew[];
extern char svoHttpStateDNSLookupUpdateNew[];
extern char svoHttpStateConnectWaitEnterNew[];
extern char svoHttpStateConnectWaitUpdateNew[];
extern char svoHttpStateSendEnterNew[];
extern char svoHttpStateSendUpdateNew[];
extern char svoHttpStateReceiveEnterNew[];
extern char svoHttpStateReceiveUpdateNew[];
extern char svoHttpStateNotSetNew[];
extern char svoHttpStateSecureConnectEnterNew[];
extern char svoHttpStateSecureConnectUpdate1New[];
extern char svoHttpStateSecureConnectUpdate2New[];
extern char svoHttpStateMaxNew[];
extern char svoHttpStateDefaultNew[];
}
extern "C" {
extern char *svoHttpSchemes[2] __attribute__((aligned(8)));
extern char svoHttpRedirectURL[];
extern char svoHttpPostCommand[];
extern char svoHttpGetCommand[];
void SetStatePostRequest(HttpState *);
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

extern "C" SECTION(DoRegistrations2) void DoRegistrations2(HttpState *http)
{
    char *schemes[2] __attribute__((aligned(8)));
    memcpy(schemes, svoHttpSchemes, sizeof(schemes));
    Register((IURISchemeProviderState *)http, schemes);
}

extern "C" SECTION(doRequest___dupe2) int doRequest___dupe2(HttpState *http, URIRequest *request, IRequestListenerState *listener, void *context)
{
    if (!request->filePath || strlen(request->filePath) > 256) __SVO_Assert_Handler(svoHttpSource, 0xB8);
    if (!request->host) __SVO_Assert_Handler(svoHttpSource, 0xB9);
    if (!http->m_memoryContextPtr) __SVO_Assert_Handler(svoHttpSource, 0xBB);
    if (strlen(request->scheme) >= 15) __SVO_Assert_Handler(svoHttpSource, 0xBC);
    svstrncpy(http->m_httpCommandStr, request->httpCommand, 5);
    if (!http->m_sock) return 0;
    if (!http->m_memoryContextPtr) __SVO_Assert_Handler(svoHttpSource, 0xC7);
    if (strlen(request->scheme) >= 15) __SVO_Assert_Handler(svoHttpSource, 0xC8);
    if (!listener) __SVO_Assert_Handler(svoHttpSource, 0xC9);
    http->m_pListener = listener;
    http->m_pListenerContext = context;
    http->m_headerBytesReceived = 0;
    http->m_bDownloadingBody = 0;
    if (http->m_addr) {
        http->m_addr = 0;
        if (http->m_bConnectionOpen) {
            SVSockState *socket = http->m_sock;
            ((const SVSockVtablePrefix *)socket->vtable)->Close(socket, 0);
            http->m_bConnectionOpen = 0;
        }
    }
    http->m_port = request->port;
    strcpy(http->m_scheme, request->scheme);
    svstrncpy(http->m_szFilePath, request->filePath, svstrlen(request->filePath));
    if (request->params) {
        SetFromParamList(&http->m_QueryParams, request->params, 0);
        FreeAll(request->params, 0);
    }
    http->m_iMethodType = request->methodType;
    svstrncpy(http->m_szHostname, request->host, svstrlen(request->host));
    SetStatePostRequest(http);
    Reset___dupe5(&http->m_timer);
    Start___dupe3(&http->m_timer);
    listener = http->m_pListener;
    listener->vtable->OnURIRequestStart(listener, http->m_pListenerContext);
    return 1;
}

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

extern "C" SECTION(formRequestText) int formRequestText(HttpState *http, char *filePath, char *request, int methodType, int requestLen, char *httpCommand)
{
    char address[128];
    char post[0x1800];
    char hash[48];
    if (!request || !filePath) __SVO_Assert_Handler(svoHttpSource, 0x11C);
    SVSockState *socket = http->m_sock;
    ((const SVSockVtablePrefix *)socket->vtable)->addrAsString(socket, http->m_addr, address, 128);
    char *cursor = request + svsnprintf(request, requestLen, svoHttpRequestFormat, httpCommand, filePath, address);
    CCookieJar *jar = getInstance(http->m_memoryContextPtr);
    if (!asHeaderString(jar, cursor, 0x1C00 - (cursor - request))) __SVO_Assert_Handler(svoHttpSource, 0x128);
    memset(post, 0, sizeof(post));
    int hasParams = NotEmpty(&http->m_QueryParams);
    if (hasParams && !toString(&http->m_QueryParams, post, sizeof(post))) __SVO_Assert_Handler(svoHttpSource, 0x131);
    if (methodType == 1) {
        char *user = 0;
        char *password = 0;
        char *ip = 0;
        int account = 0;
        GetLoginInfo(GetInstance(), &user, &password, &account, &ip);
        md5requestLogin(http, user, password, ip, hash);
    } else md5request(http, filePath, cursor, post, hash);
    cursor = strchr(cursor, 0);
    if (!cursor) __SVO_Assert_Handler(svoHttpSource, 0x14E);
    cursor += svsnprintf(cursor, 0x1C00 - (cursor - request), svoHttpVersionFormat, svoHttpVersionValue);
    SVBrowserPrefix *browser = GetInstance();
    cursor += svsnprintf(cursor, 0x1C00 - (cursor - request), svoHttpTargetTypeFormat, browser->m_targetInfo.targetType);
    cursor += svsnprintf(cursor, 0x1C00 - (cursor - request), svoHttpTargetIDFormat, browser->m_targetInfo.targetSpecialID);
    cursor += svsnprintf(cursor, 0x1C00 - (cursor - request), svoHttpTitleIDFormat, (int)browser->m_targetInfo.targetAppID);
    cursor += svsnprintf(cursor, 0x1C00 - (cursor - request), methodType == 1 ? svoHttpLoginMacFormat : svoHttpMacFormat, hash);
    if (hasParams && post[0]) cursor += svsnprintf(cursor, 0x1C00 - (cursor - request), svoHttpBodyFormat, strlen(post), post);
    svstrncpy(cursor, svoHttpCRLF, 0x1C00 - (cursor - request));
    return cursor + 2 - request;
}

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

extern "C" SECTION(handleRedirect) void handleRedirect(HttpState *http)
{
    if (!http->m_sock || !http->m_addr || !http->m_port) __SVO_Assert_Handler(svoHttpSource, 0x30C);
    http->m_bConnectionOpen = 0;
    SVSockState *socket = http->m_sock;
    ((const SVSockVtablePrefix *)socket->vtable)->Close(socket, 0);
    memset(http->m_headerBuf, 0, 0x8000);
    http->m_headerBytesReceived = 0;
    http->m_bodyBytesReceived = 0;
    http->m_status = 0;
    http->m_contentLength = 0;
    http->m_timeoutFrameCounter = 0;
    char location[272];
    sprintf(location, svoHttpRedirectURL, http->m_scheme, http->m_szHostname, http->m_port, http->m_nextLocation);
    URIRequest request;
    request.scheme = http->m_scheme;
    request.host = http->m_szHostname;
    request.port = http->m_port;
    request.filePath = http->m_nextLocation;
    request.methodType = 0;
    request.context = 0;
    if (http->m_bNeedToPost302) {
        request.params = &http->m_savedServerParams;
        request.httpCommand = svoHttpPostCommand;
        http->vtable->doRequest(http, &request, http->m_pListener, http->m_pListenerContext);
        http->m_bNeedToPost302 = 0;
    } else {
        request.params = 0;
        request.httpCommand = svoHttpGetCommand;
        IRequestListenerState *listener = http->m_pListener;
        if (!listener) __SVO_Assert_Handler(svoHttpSource, 0x341);
        else listener->vtable->OnURIRequestRedirectReceived(listener, http->m_pListenerContext, location);
        http->vtable->doRequest(http, &request, http->m_pListener, http->m_pListenerContext);
    }
}

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

extern "C" SECTION(md5request) char *md5request(HttpState *http, char *path, char *cookies, char *post, char *output)
{
    md5_context context;
    unsigned char digest[16];
    md5_starts(&context);
    md5_update(&context, (unsigned char *)path, (unsigned int)strlen(path));
    int hasCookies = *cookies;
    cookies += 8;
    if (hasCookies) md5_update(&context, (unsigned char *)cookies, (unsigned int)(strlen(cookies) - 2));
    char *chunk = post;
    for (int i = 0; i < 2; ++i) {
        if (chunk) md5_update(&context, (unsigned char *)chunk, (unsigned int)strlen(chunk));
        chunk = svoHttpMD5Suffix;
    }
    md5_finish(&context, digest);
    return md5_hex(digest, output);
}

extern "C" SECTION(md5requestLogin) char *md5requestLogin(HttpState *http, char *username, char *password, char *ip, char *output)
{
    md5_context context;
    unsigned char digest[16];
    char user[257];
    char pass[257];
    md5_starts(&context);
    char initial = svoHttpEmptyString[0];
    user[0] = initial;
    memset(user + 1, 0, 256);
    pass[0] = initial;
    memset(pass + 1, 0, 256);
    if (strlen(username) > 256) __SVO_Assert_Handler(svoHttpSource, 0x1D6);
    strcat(user, username);
    if (strlen(password) > 256) __SVO_Assert_Handler(svoHttpSource, 0x1D8);
    strcat(pass, password);
    char *chunks[3];
    chunks[0] = strlwr(user);
    chunks[1] = strlwr(pass);
    chunks[2] = ip;
    for (int i = 0; i < 3; ++i) {
        char *chunk = chunks[i];
        md5_update(&context, (unsigned char *)chunk, (unsigned int)strlen(chunk));
    }
    md5_finish(&context, digest);
    return md5_hex(digest, output);
}

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

extern "C" SECTION(parseHttpHeaderLine) long parseHttpHeaderLine(HttpState *http, char **cursor, int *contentType)
{
    char *header = *cursor;
    if (*header == '\r' || *header == '\n') {
        do { ++*cursor; } while (**cursor == '\r' || **cursor == '\n');
        return 0;
    }
    if (!strncmp(header, svoHttpSetCookiePrefix, 10)) {
        CCookieJar *jar = getInstance(http->m_memoryContextPtr);
        if (!jar || !parseSetCookieHeader(jar, *cursor)) {
            __SVO_Assert_Handler(svoHttpSource, 0x388);
            return 0;
        }
    } else if (!strncmp(*cursor, svoHttpContentLengthPrefix, 14)) {
        *cursor += 15;
        http->m_contentLength = strtol(*cursor, cursor, 10);
    } else if (!strncmp(*cursor, svoHttpLocationPrefix, 9)) {
        *cursor = strchr(*cursor, '/');
        if (!*cursor) __SVO_Assert_Handler(svoHttpSource, 0x396);
        *cursor += 2;
        *cursor = strchr(*cursor, '/');
        if (!*cursor) __SVO_Assert_Handler(svoHttpSource, 0x39A);
        char *end = *cursor;
        while (*end && !svisspace(*end)) ++end;
        char *location = http->m_nextLocation;
        memset(location, 0, 257);
        if (end - *cursor > 199) {
            http->m_serverParamsTooLong = 1;
            if (NotEmpty(&http->m_savedServerParams)) __SVO_Assert_Handler(svoHttpSource, 0x3AE);
            char *separator = svoHttpQueryDelimiter;
            while ((*cursor = strstr(*cursor, separator)) != 0) {
                char key[32];
                char value[0x3000];
                memset(key, 0, sizeof(key));
                memset(value, 0, sizeof(value));
                char *equals = *cursor;
                do { ++equals; } while (*equals != '=');
                ++*cursor;
                if (equals - *cursor > 31) __SVO_Assert_Handler(svoHttpSource, 0x3C8);
                memcpy(key, *cursor, equals - *cursor);
                *cursor = equals + 1;
                end = *cursor;
                if (*end == '&') value[0] = 0;
                else {
                    do { ++end; } while (*end != '&' && *end != '\r');
                    if (end - *cursor >= 0x3000) __SVO_Assert_Handler(svoHttpSource, 0x3E0);
                    memcpy(value, *cursor, end - *cursor);
                }
                decodeURLEntityText(key);
                decodeURLEntityText(value);
                Set(&http->m_savedServerParams, key, value, 0);
                if (*end == '\r') {
                    *cursor = strchr(header, '\n') + 1;
                    char *path = strstr(header + 9, svoHttpHostDelimiter) + 2;
                    path = strstr(path, svoHttpPathDelimiter);
                    char *query = strchr(path, '?');
                    *query = 0;
                    strncpy(location, path, strlen(path));
                    *query = '?';
                    http->m_bNeedToPost302 = 1;
                    return 1;
                }
                separator = svoHttpParamDelimiter;
            }
        } else strncpy(location, *cursor, end - *cursor);
    } else if (!strncmp(*cursor, svoHttpContentTypePrefix, 13)) {
        char *type = *cursor + 14;
        int result;
        if (!strncmp(type, svoHttpSVMLType, 9)) result = 1;
        else if (!strncmp(type, svoHttpXMLType, 8)) result = 2;
        else if (!strncmp(type, svoHttpHTMLType, 9)) result = 3;
        else if (!strncmp(type, svoHttpGIFType, 9) || !strncmp(type, svoHttpTM2Type, 9)) result = 5;
        else if (!strncmp(type, svoHttpAMXType, 15)) result = 4;
        else if (!strncmp(type, svoHttpBinaryType, 24)) result = 6;
        else result = 7;
        *contentType = result;
    }
    char *newline = strchr(*cursor, '\n');
    if (newline) {
        *cursor = newline + 1;
        return 1;
    }
    __SVO_Assert_Handler(svoHttpSource, 0x43F);
    return 0;
}

extern "C" SECTION(parseHttpStatusLine) char *parseHttpStatusLine(HttpState *http, char *cursor)
{
    int *status = &http->m_status;
    if (strncmp(cursor, svoHttpVersionPrefix, 7)) return 0;
    cursor += 9;
    if (!svisdigit((signed char)*cursor)) { *status = 600; return 0; }
    *status = atoi(cursor);
    char *end = strchr(cursor, 10);
    return end ? end + 1 : 0;
}

extern "C" SECTION(SaveStatePreGameToPersistentData) long SaveStatePreGameToPersistentData(HttpState *http, SVPersistentData *persist)
{
    CCookieJar *jar = getInstance(http->m_memoryContextPtr);
    if (!jar) __SVO_Assert_Handler(svoHttpSource, 0x454);
    memcpy(persist->cookieData, jar->m_cookies, 2032);
    return 1;
}

extern "C" SECTION(SetHttpState) void SetHttpState(HttpState *http, int nextState)
{
    char oldText[64];
    char newText[64];
    int state = GetHttpState(http);
    char *format;
    if (state == 1) format = svoHttpStateIdleEnterOld;
    else if (state == 2) format = svoHttpStateIdleUpdateOld;
    else if (state == 3) format = svoHttpStateDNSLookupEnterOld;
    else if (state == 4) format = svoHttpStateDNSLookupUpdateOld;
    else if (state == 5) format = svoHttpStateConnectWaitEnterOld;
    else if (state == 6) format = svoHttpStateConnectWaitUpdateOld;
    else if (state == 10) format = svoHttpStateSendEnterOld;
    else if (state == 11) format = svoHttpStateSendUpdateOld;
    else if (state == 12) format = svoHttpStateReceiveEnterOld;
    else if (state == 13) format = svoHttpStateReceiveUpdateOld;
    else if (state == 0) format = svoHttpStateNotSetOld;
    else if (state == 7) format = svoHttpStateSecureConnectEnterOld;
    else if (state == 8) format = svoHttpStateSecureConnectUpdate1Old;
    else if (state == 9) format = svoHttpStateSecureConnectUpdate2Old;
    else if (state == 2147483647) format = svoHttpStateMaxOld;
    else format = svoHttpStateDefaultOld;
    int oldLength = sprintf(oldText, format);
    http->m_HttpState = nextState;
    state = GetHttpState(http);
    if (state == 1) format = svoHttpStateIdleEnterNew;
    else if (state == 2) format = svoHttpStateIdleUpdateNew;
    else if (state == 3) format = svoHttpStateDNSLookupEnterNew;
    else if (state == 4) format = svoHttpStateDNSLookupUpdateNew;
    else if (state == 5) format = svoHttpStateConnectWaitEnterNew;
    else if (state == 6) format = svoHttpStateConnectWaitUpdateNew;
    else if (state == 10) format = svoHttpStateSendEnterNew;
    else if (state == 11) format = svoHttpStateSendUpdateNew;
    else if (state == 12) format = svoHttpStateReceiveEnterNew;
    else if (state == 13) format = svoHttpStateReceiveUpdateNew;
    else if (state == 0) format = svoHttpStateNotSetNew;
    else if (state == 7) format = svoHttpStateSecureConnectEnterNew;
    else if (state == 8) format = svoHttpStateSecureConnectUpdate1New;
    else if (state == 9) format = svoHttpStateSecureConnectUpdate2New;
    else if (state == 2147483647) format = svoHttpStateMaxNew;
    else format = svoHttpStateDefaultNew;
    int newLength = sprintf(newText, format);
    if (oldLength + newLength > 127) __SVO_Assert_Handler(svoHttpSource, 0x625);
}

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
