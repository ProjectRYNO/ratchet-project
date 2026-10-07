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

#include "CHttp.h"

extern "C" {
void SetHttpState(HttpState *http, int state);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", _Http);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", closeSocket);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", DoRegistrations2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", doRequest___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", download___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", downloadBody);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", downloadHeaders);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", formRequestText);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", freeResources___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", getSocketType);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", handleRedirect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", Http);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", HttpConnectWaitOnEnter);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", HttpConnectWaitOnUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", HttpGetHostByNameOnEnter);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", HttpGetHostByNameOnUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", HttpRecvOnUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", HttpSendOnEnter);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", InitRequest);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", IsBusy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", LoadStatePostGameFromPersistentData___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", md5request);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", md5requestLogin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", OnBodyChunkReceived);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", OnHeaderParsed);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", operator.delete___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", operator.new___dupe4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", parseHeaderBuf);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", parseHttpHeaderLine);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", parseHttpStatusLine);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", SaveStatePreGameToPersistentData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", SetHttpState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CHttp", States___dupe2);
