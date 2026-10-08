#include "string.h"
#include "URISchemeMgr.h"
#include "HttpSecure.h"
#include "CMemoryContextBase.h"
#include "SVTagModule.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_HttpSecure_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

CMemoryContextBaseState *GetMemoryContext(void);
extern char svoHttpSecureSource[];


extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);

}
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoHttpSecureSource[];
void * HttpSecureoperator_new___dupe2(unsigned int size) __asm__("operator.new___dupe2");

}
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
void HttpSecureoperator_delete(void *memory) __asm__("operator.delete");

}
extern "C" {
extern const HttpSecureVtablePrefix svoHttpSecureVtable;
extern void (*svoSSLDestroy)(void *);
extern long (*svoSSLCallback)(SSLCallbackParams *, void *);
void _Http(HttpState *, unsigned int);

}
extern "C" {
long GetHttpState(HttpState *);
void HttpIdleOnEnter(HttpState *);
void HttpIdleOnUpdate(HttpState *);
void HttpGetHostByNameOnEnter(HttpState *);
void HttpGetHostByNameOnUpdate(HttpState *);
void HttpConnectWaitOnEnter(HttpState *);
void HttpConnectWaitOnUpdate(HttpState *);
void HttpSendOnEnter(HttpState *);
void HttpSendOnUpdate(HttpState *);
void HttpRecvOnEnter(HttpState *);
void HttpRecvOnUpdate(HttpState *);

}
#define SECTION(name) __attribute__((section(".svo_HttpSecure_" #name)))

SECTION(HttpsDestroy) void HttpsDestroy(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(HttpsCleanup) void HttpsCleanup(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(PrintRequestHeader) void PrintRequestHeader(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(PrintRequestFooter) void PrintRequestFooter(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(PrintHeader) void PrintHeader(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(PrintFooter) void PrintFooter(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(IsSecure) long IsSecure(void *self)
{
    return 1;
}

}

extern "C" SECTION(_HttpSecure) void _HttpSecure(HttpSecureState *http, unsigned int flags)
{
    http->base.vtable = &svoHttpSecureVtable.base;
    DeRegister((IURISchemeProviderState *)http);
    _Http(&http->base, 0);
    if (flags & 1) HttpSecureoperator_delete(http);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", DoRegistrations);

extern "C" SECTION(HttpCleanup) void HttpCleanup(HttpSecureState *http)
{
    svoSSLDestroy(http->engine);
    http->engine = 0;
}

extern "C" SECTION(HTTPS_Free) void HTTPS_Free(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HTTPS_Malloc);

extern "C" SECTION(HttpsCallEngine) void HttpsCallEngine(HttpSecureState *http, SSLCallbackParams *params)
{
    params->state = http->state;
    long result = svoSSLCallback(params, http->engine);
    http->state = params->state;
    if (result) __SVO_Assert_Handler(svoHttpSecureSource, 0x162);
}

extern "C" SECTION(HttpsDownload) long HttpsDownload(HttpSecureState *http, char *data, int length, char **output, int *outputLength, char **sendBack, int *sendLength)
{
    SSLCallbackParams params;
    memset(&params, 0, sizeof(params));
    params.received = data;
    params.receivedLength = length;
    ((const HttpSecureVtablePrefix *)http->base.vtable)->HttpsCallEngine(http, &params);
    *outputLength = params.decryptedLength;
    *output = params.decrypted;
    *sendLength = params.sendBackLength;
    *sendBack = params.sendBack;
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpsDownloadHello);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpSecure);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpSecureConnectingOnEnter);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpSecureConnectingOnUpdate1);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpSecureConnectingOnUpdate2);

extern "C" SECTION(HttpSendRequest) void HttpSendRequest(HttpSecureState *http, char *data, int length, char **output, int *outputLength)
{
    SSLCallbackParams params;
    memset(&params, 0, sizeof(params));
    params.request = data;
    params.requestLength = length;
    ((const HttpSecureVtablePrefix *)http->base.vtable)->HttpsCallEngine(http, &params);
    *outputLength = params.sendBackLength;
    *output = params.sendBack;
}

extern "C" SECTION(HttpsKeyExchange) long HttpsKeyExchange(HttpSecureState *http, char *data, int length, char **output, int *outputLength)
{
    SSLCallbackParams params;
    memset(&params, 0, sizeof(params));
    params.received = data;
    params.receivedLength = length;
    ((const HttpSecureVtablePrefix *)http->base.vtable)->HttpsCallEngine(http, &params);
    *outputLength = params.sendBackLength;
    *output = params.sendBack;
    return 0;
}

extern "C" SECTION(operator.delete) void HttpSecureoperator_delete(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

extern "C" SECTION(operator.new___dupe2) void * HttpSecureoperator_new___dupe2(unsigned int size)
{
    void *result = svAllocSafe(GetMemoryContext(), size, 0, 0x69, svoHttpSecureSource);
    if (!result) __SVO_Assert_Handler(svoHttpSecureSource, 0x6C);
    return result;
}

extern "C" SECTION(States) long States(HttpSecureState *http)
{
    long state = GetHttpState(&http->base);
    if (state == 1) { HttpIdleOnEnter(&http->base); }
    else if (state == 2) { HttpIdleOnUpdate(&http->base); return 1; }
    else if (state == 3) { HttpGetHostByNameOnEnter(&http->base); }
    else if (state == 4) { HttpGetHostByNameOnUpdate(&http->base); }
    else if (state == 5) { HttpConnectWaitOnEnter(&http->base); }
    else if (state == 6) { HttpConnectWaitOnUpdate(&http->base); }
    else if (state == 10) { HttpSendOnEnter(&http->base); }
    else if (state == 11) { HttpSendOnUpdate(&http->base); }
    else if (state == 12) { HttpRecvOnEnter(&http->base); }
    else if (state == 13) { HttpRecvOnUpdate(&http->base); }
    else if (state == 7) ((const HttpSecureVtablePrefix *)http->base.vtable)->ConnectingOnEnter(http);
    else if (state == 8) ((const HttpSecureVtablePrefix *)http->base.vtable)->ConnectingOnUpdate1(http);
    else if (state == 9) ((const HttpSecureVtablePrefix *)http->base.vtable)->ConnectingOnUpdate2(http);
    else if (state == 0) __SVO_Assert_Handler(svoHttpSecureSource, 0x278);
    else if (state == 0x7FFFFFFF) __SVO_Assert_Handler(svoHttpSecureSource, 0x27B);
    return 0;
}
