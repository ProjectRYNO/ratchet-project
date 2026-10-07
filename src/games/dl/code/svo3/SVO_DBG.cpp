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

#define SECTION(name) __attribute__((section(".svo_SVO_DBG_" #name)))

SECTION(sv_connect_to_log_server) long sv_connect_to_log_server(void *memory, char *serverName, int port)
{
    return 0;
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVO_DBG", __SVO_Assert_Handler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVO_DBG", cleanFileString);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVO_DBG", SV_CheckVersion);
