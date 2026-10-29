#include "common.h"
#include "../../../rt_util/rt_memory.h"

#define MEDIUS_LNPLAT_SECTION(name) __attribute__((section(".medius_lnplat_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_lnplat_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef int RT_4BYTE;
typedef RT_MEMORY_ALIGNED LIBNETB_MEM_ALIGNED;

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/platform", libnetb_mem_alloc);

RT_4BYTE MEDIUS_LNPLAT_SECTION(libnetb_mem_free) libnetb_mem_free(void **pp_block)
{
    RT_4BYTE result = -1;

    if (rt_memory_free(pp_block) == 0) result = 0;
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/platform", libnetb_mem_align_alloc);

RT_4BYTE MEDIUS_LNPLAT_SECTION(libnetb_mem_align_free) libnetb_mem_align_free(LIBNETB_MEM_ALIGNED *p_aligned)
{
    RT_4BYTE result = -1;

    if (rt_memory_align_free(p_aligned) == 0) result = 0;
    return result;
}
