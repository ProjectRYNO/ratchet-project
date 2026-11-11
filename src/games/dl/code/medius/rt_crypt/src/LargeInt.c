#include "common.h"
#include "LargeInt.h"

#define MEDIUS_LINT_SECTION(name) __attribute__((section(".medius_lint_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_lint_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void *memset(void *pointer, int value, unsigned int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);

void MEDIUS_LINT_SECTION(lintSetSmallValue) lintSetSmallValue(lint *pI, unsigned int value)
{
    memset(pI, 0, sizeof(lint));
    pI->data[0] = value;
}

int MEDIUS_LINT_SECTION(IsEven) IsEven(lint *pI)
{
    return !(pI->data[0] & 1);
}

int MEDIUS_LINT_SECTION(IsZero) IsZero(lint *pI)
{
    int i;

    for (i = 0; i < LINT_WORDS; i++) {
        if (pI->data[i]) return 0;
    }
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/LargeInt", func_01EACF30);

void MEDIUS_LINT_SECTION(lintSetBit) lintSetBit(lint *pI, unsigned int nBit)
{
    pI->data[nBit >> 5] |= 1 << nBit;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/LargeInt", lintIncrement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/LargeInt", func_01EACFB0);

void MEDIUS_LINT_SECTION(MOD) MOD(lint *pResult, lint *pI1, lint *pI2)
{
    lint tmp;

    memcpy(&tmp, pI1, sizeof(lint));
    MODIP(&tmp, pI2);
    memcpy(pResult, &tmp, sizeof(lint));
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/LargeInt", func_01EAD018);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/LargeInt", QRMOD);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/LargeInt", EMOD);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/LargeInt", func_01EAD358);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/LargeInt", EMODM);
