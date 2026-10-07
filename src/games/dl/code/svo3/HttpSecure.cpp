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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", _HttpSecure);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", DoRegistrations);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpCleanup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HTTPS_Free);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HTTPS_Malloc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpsCallEngine);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpsDownload);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpsDownloadHello);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpSecure);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpSecureConnectingOnEnter);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpSecureConnectingOnUpdate1);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpSecureConnectingOnUpdate2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpSendRequest);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", HttpsKeyExchange);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", operator.delete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", operator.new___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HttpSecure", States);
