#include "common.h"
#include "RC4.h"

#define MEDIUS_RC4_SECTION(name) __attribute__((section(".medius_rc4_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_rc4_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

void MEDIUS_RC4_SECTION(RC4Init) RC4Init(RC4_CTX *pCtx, unsigned char *pKey, unsigned int nKeyLen)
{
    unsigned int i;
    unsigned int j;
    unsigned int k;
    unsigned char t;

    for (i = 0; i < 256; i++) pCtx->state[i] = i;
    pCtx->x = 0;
    pCtx->y = 0;
    k = 0;
    j = 0;
    for (i = 0; i < 256; i++) {
        t = pCtx->state[i];
        j = (j + (t + pKey[k])) & 0xFF;
        pCtx->state[i] = pCtx->state[j];
        pCtx->state[j] = t;
        k = ((k + 1) % nKeyLen) & 0xFF;
    }
}

void MEDIUS_RC4_SECTION(RC4Code) RC4Code(RC4_CTX *pCtx, unsigned char *pData, unsigned int nDataLen)
{
    unsigned int x = pCtx->x;
    unsigned int y = pCtx->y;
    unsigned int i;
    unsigned int a;
    unsigned int t;

    for (i = 0; i < nDataLen; i++) {
        x = (x + 1) & 0xFF;
        a = pCtx->state[x];
        y = (y + a) & 0xFF;
        t = (a + pCtx->state[y]) & 0xFF;
        pCtx->state[x] = t - a;
        pCtx->state[y] = t - pCtx->state[y];
        pData[i] ^= pCtx->state[t];
    }
    pCtx->x = x;
    pCtx->y = y;
}
