#include "common.h"

#define MEDIUS_DMEIF_SECTION(name) __attribute__((section(".medius_dmeif_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dmeif_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void *gMsgClientInterfacePtr;
extern void *gStreamMediaInterfacePtr;
extern void *gCommPlatformInterfacePtr;
extern void *gObjectInterfacePtr;
extern void *gP2PInterfacePtr;
extern void *gUDPInterfacePtr;
extern void *gCryptInterfacePtr;
// GSM 06.10 audio codec interface (CreateCodec: 320-byte frames, 33 bytes encoded); no debug-info name.
extern void *mediusACodecGSMInterfacePtr;
extern void *gACodecLPCInterfacePtr;
extern void *gACodecLPC10InterfacePtr;
extern void *gVCodecJPEGInterfacePtr;

void MEDIUS_DMEIF_SECTION(ClearInterfacePointers) ClearInterfacePointers(void)
{
    gMsgClientInterfacePtr = 0;
    gStreamMediaInterfacePtr = 0;
    gCommPlatformInterfacePtr = 0;
    gObjectInterfacePtr = 0;
    gP2PInterfacePtr = 0;
    gUDPInterfacePtr = 0;
    gCryptInterfacePtr = 0;
    mediusACodecGSMInterfacePtr = 0;
    gACodecLPCInterfacePtr = 0;
    gACodecLPC10InterfacePtr = 0;
    gVCodecJPEGInterfacePtr = 0;
}
