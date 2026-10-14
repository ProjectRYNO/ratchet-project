#include "SVTagModule.h"
#include "CError.h"
#include "stdio.h"
#include "string.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SVO_DBG_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"
#include "CDrawContextBase.h"

extern "C" {

extern char svoDebugSource[];
extern char svoLibraryVersion[];
extern char svoVersionMessage[];

#define SECTION(name) __attribute__((section(".svo_SVO_DBG_" #name)))

SECTION(sv_connect_to_log_server) int sv_connect_to_log_server(void *memory, char *serverName, int port)
{
    return 0;
}

}

extern "C" {
extern int svoAssertTrip;
extern char svoAssertMessage[];
extern char svoAssertMessageFormat[];
extern char svoAssertBanner[];
extern char svoAssertLineFormat[];
extern char svoAssertFooter[];
void cleanFileString(char *text);
CDrawContextBase *GetDrawContext(void);
}
extern "C" SECTION(__SVO_Assert_Handler) void __SVO_Assert_Handler(const char *file, int line)
{
    char localFile[256];
    svoAssertTrip = 1;
    strncpy(localFile, file, 0xFF);
    cleanFileString(localFile);
    sprintf(svoAssertMessage, svoAssertMessageFormat, localFile, line);
    CDrawContextBase *draw = GetDrawContext();
    if (draw) {
        if (draw->vtable->RenderAssert(draw, svoAssertMessage)) return;
        for (;;) {
        }
    }
    printf(svoAssertBanner);
    printf(svoAssertLineFormat, localFile, line);
    printf(svoAssertFooter);
    for (;;) {
    }
}

extern "C" SECTION(cleanFileString) void cleanFileString(char *text)
{
    int len;
    int cur;
    int i;
    len = strlen(text);
    cur = len - 1;
    i = 0;
loop:
    if (i < len) {
        i++;
        if (text[cur] == '/' || text[cur] == 92) goto found;
        cur--;
        goto loop;
    }
    return;
found:
    strcpy(text, &text[cur] + 1);
}

extern "C" SECTION(SV_CheckVersion) char *SV_CheckVersion(char *headerVersion)
{
    if (!headerVersion) {
        SetErrorCode(35);
        __SVO_Assert_Handler(svoDebugSource, 0x69);
    }
    char message[192];
    if (sprintf(message, svoVersionMessage, svoLibraryVersion, headerVersion) > 176)
        __SVO_Assert_Handler(svoDebugSource, 0x73);
    if (strcmp(headerVersion, svoLibraryVersion)) {
        SetErrorCode(35);
        __SVO_Assert_Handler(svoDebugSource, 0x78);
    }
    return svoLibraryVersion;
}
