#include "common.h"

#define MEDIUS_STRMGR_SECTION(name) __attribute__((section(".medius_strmgr_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_strmgr_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern int sprintf(char *buffer, const char *format, ...);
// "%s.%d" (rodata).
extern char mediusMessageIdFormat[];

int MEDIUS_STRMGR_SECTION(iCreateAndAllocateMessageID) iCreateAndAllocateMessageID(char *pcSessionKey, int iCounterVal, int iTypeCode, char *pcMessageID)
{
    sprintf(pcMessageID, mediusMessageIdFormat, pcSessionKey, iCounterVal);
    return 0;
}
