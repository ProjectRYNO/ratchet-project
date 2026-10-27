#include "common.h"

#define MEDIUS_DMELIST_SECTION(name) __attribute__((section(".medius_dmelist_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dmelist_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef enum { NetErrorNone = 0, NetErrorInvalidArg = 23 } NetErrorCode;

// Name and layout from the retail ELF debug information.
typedef struct { // 0x28
    /* 0x00 */ int bitmask[8];
    /* 0x20 */ int base_id;
    /* 0x24 */ int max_id;
} NetBitMask;

NetErrorCode MEDIUS_DMELIST_SECTION(NetBitMaskIsSet) NetBitMaskIsSet(NetBitMask *pBitMask, int mask_index, int *b_set)
{
    unsigned int bit;
    int mask;

    if (!pBitMask) return NetErrorInvalidArg;
    if (mask_index < pBitMask->base_id || mask_index >= pBitMask->max_id) return NetErrorInvalidArg;
    bit = mask_index - pBitMask->base_id;
    mask = 1 << (bit & 0x1F);
    *b_set = (pBitMask->bitmask[bit >> 5] & mask) != 0;
    return NetErrorNone;
}

NetErrorCode MEDIUS_DMELIST_SECTION(NetBitMaskSet) NetBitMaskSet(NetBitMask *pBitMask, int mask_index)
{
    unsigned int bit;

    if (!pBitMask) return NetErrorInvalidArg;
    if (mask_index < pBitMask->base_id || mask_index >= pBitMask->max_id) return NetErrorInvalidArg;
    bit = mask_index - pBitMask->base_id;
    pBitMask->bitmask[bit >> 5] |= 1 << (bit & 0x1F);
    return NetErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeList", NetGenerateClientList);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeList", NetGenerateJoinedClientList);
