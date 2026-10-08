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

extern "C" {

extern char svoDebugSource[];
extern char svoLibraryVersion[];
extern char svoVersionMessage[];

#define SECTION(name) __attribute__((section(".svo_SVO_DBG_" #name)))

SECTION(sv_connect_to_log_server) long sv_connect_to_log_server(void *memory, char *serverName, int port)
{
    return 0;
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVO_DBG", __SVO_Assert_Handler);

extern "C" SECTION(cleanFileString) void cleanFileString(char *text)
{
    int length = strlen(text);
    for (int i = length - 1; i >= 0; --i) {
        if (text[i] == '/' || text[i] == 92) {
            strcpy(text, text + i + 1);
            return;
        }
    }
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
