#include "common.h"
#include "md2.h"

#define MEDIUS_MD2_SECTION(name) __attribute__((section(".medius_md2_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_md2_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void *memset(void *pointer, int value, unsigned int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);

void MEDIUS_MD2_SECTION(KM_MD2) KM_MD2(unsigned char *pMessage, unsigned int cbMessageSize, unsigned char *digest)
{
    MD2_CTX context;

    md2Init(&context);
    md2Update(&context, pMessage, cbMessageSize);
    md2Final(&context, digest);
}

void MEDIUS_MD2_SECTION(md2Init) md2Init(MD2_CTX *pMD2)
{
    memset(pMD2, 0, sizeof(*pMD2));
}

void MEDIUS_MD2_SECTION(md2Update) md2Update(MD2_CTX *pMD2, unsigned char *pData, unsigned int nDataLen)
{
    unsigned int i;
    unsigned int index;
    unsigned int partLen;

    index = pMD2->count;
    pMD2->count = (index + nDataLen) & 0xF;
    partLen = 16 - index;
    if (nDataLen >= partLen) {
        memcpy(&pMD2->buffer[index], pData, partLen);
        md2Transform(pMD2, pMD2->buffer);
        for (i = partLen; i + 15 < nDataLen; i += 16) md2Transform(pMD2, &pData[i]);
        index = 0;
    } else {
        i = 0;
    }
    memcpy(&pMD2->buffer[index], &pData[i], nDataLen - i);
}

void MEDIUS_MD2_SECTION(md2Final) md2Final(MD2_CTX *pMD2, unsigned char *digest)
{
    unsigned int padLen;

    padLen = 16 - pMD2->count;
    md2Update(pMD2, rtCryptMd2Padding[padLen], padLen);
    md2Update(pMD2, pMD2->checksum, 16);
    *(MD2_BLOCK *)digest = *(MD2_BLOCK *)pMD2->state;
    memset(pMD2, 0, sizeof(*pMD2));
}

void MEDIUS_MD2_SECTION(md2Transform) md2Transform(MD2_CTX *pMD2, unsigned char *block)
{
    unsigned int i;
    unsigned int j;
    unsigned int t;
    unsigned char x[48];

    *(MD2_BLOCK *)&x[0] = *(MD2_BLOCK *)pMD2->state;
    *(MD2_BLOCK *)&x[16] = *(MD2_BLOCK *)block;
    for (i = 0; i < 16; i++) x[i + 32] = pMD2->state[i] ^ block[i];
    t = 0;
    for (i = 0; i < 18; i++) {
        for (j = 0; j < 48; j++) t = x[j] ^= rtCryptMd2Sbox[t];
        t = (t + i) & 0xFF;
    }
    *(MD2_BLOCK *)pMD2->state = *(MD2_BLOCK *)&x[0];
    t = pMD2->checksum[15];
    for (i = 0; i < 16; i++) t = pMD2->checksum[i] ^= rtCryptMd2Sbox[block[i] ^ t];
    memset(x, 0, sizeof(x));
}
