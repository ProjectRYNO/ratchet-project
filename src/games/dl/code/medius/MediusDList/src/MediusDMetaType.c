#include "common.h"

#define MEDIUS_DMETA_SECTION(name) __attribute__((section(".medius_dmeta_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dmeta_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern int rt_memory_free(void **pointer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDMetaType", create);

void MEDIUS_DMETA_SECTION(destroy) destroy(void *pMetaType)
{
    if (pMetaType) rt_memory_free(&pMetaType);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDMetaType", getThisField);
