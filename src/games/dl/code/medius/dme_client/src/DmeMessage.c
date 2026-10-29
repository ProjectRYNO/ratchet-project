#include "common.h"

#define MEDIUS_DMEMSG_SECTION(name) __attribute__((section(".medius_dmemsg_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dmemsg_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

char *strncpy(char *, const char *, unsigned int);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeMessage", ClientConnectsPacketHandler);

int MEDIUS_DMEMSG_SECTION(ServerVersionPacketHandler) ServerVersionPacketHandler(char *pCtx, int a1, int a2, char *pVersion)
{
    if (pCtx == 0) {
        return -1;
    }
    strncpy(pCtx + 0x418, pVersion, 0x10);
    return 0x10;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeMessage", RequestServersPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeMessage", ServerResponsePacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeMessage", PingPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeMessage", UpdateClientStatusPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeMessage", RegisterDMEmessages);
