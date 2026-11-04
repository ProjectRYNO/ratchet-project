#include "common.h"
#include "SHA1.h"

#define MEDIUS_SHA1_SECTION(name) __attribute__((section(".medius_sha1_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_sha1_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void *memset(void *pointer, int value, unsigned int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);

void MEDIUS_SHA1_SECTION(SHAInit) SHAInit(SHA_CTX *shsInfo)
{
    *shsInfo = rtCryptShaInitState;
    endianTest(&shsInfo->bIsBigEndian);
}

void MEDIUS_SHA1_SECTION(SHAUpdate) SHAUpdate(SHA_CTX *shsInfo, unsigned char *pBuffer, unsigned int nCount)
{
    unsigned int tmp;
    int dataCount;

    tmp = shsInfo->countLo;
    if ((shsInfo->countLo = tmp + (nCount << 3)) < tmp) shsInfo->countHi++;
    shsInfo->countHi += nCount >> 29;
    dataCount = (int)(tmp >> 3) & 0x3F;
    if (dataCount) {
        unsigned char *p = (unsigned char *)shsInfo->data + dataCount;

        dataCount = SHS_DATASIZE - dataCount;
        if (nCount < dataCount) {
            memcpy(p, pBuffer, nCount);
            return;
        }
        memcpy(p, pBuffer, dataCount);
        longReverse(shsInfo->data, SHS_DATASIZE, shsInfo->bIsBigEndian);
        SHSTransform(shsInfo);
        pBuffer += dataCount;
        nCount -= dataCount;
    }
    while (nCount >= SHS_DATASIZE) {
        *(SHA_BLOCK *)shsInfo->data = *(SHA_BLOCK *)pBuffer;
        longReverse(shsInfo->data, SHS_DATASIZE, shsInfo->bIsBigEndian);
        SHSTransform(shsInfo);
        pBuffer += SHS_DATASIZE;
        nCount -= SHS_DATASIZE;
    }
    memcpy(shsInfo->data, pBuffer, nCount);
}

void MEDIUS_SHA1_SECTION(SHAFinal) SHAFinal(SHA_CTX *shsInfo, unsigned char *pDigest, unsigned int nDigestSize)
{
    int count;
    unsigned char *dataPtr;

    count = shsInfo->countLo;
    count = (count >> 3) & 0x3F;
    dataPtr = (unsigned char *)shsInfo->data + count;
    *dataPtr++ = 0x80;
    count = SHS_DATASIZE - 1 - count;
    if (count < 8) {
        memset(dataPtr, 0, count);
        longReverse(shsInfo->data, SHS_DATASIZE, shsInfo->bIsBigEndian);
        SHSTransform(shsInfo);
        memset(shsInfo->data, 0, SHS_DATASIZE - 8);
    } else {
        memset(dataPtr, 0, count - 8);
    }
    shsInfo->data[14] = shsInfo->countHi;
    shsInfo->data[15] = shsInfo->countLo;
    longReverse(shsInfo->data, SHS_DATASIZE - 8, shsInfo->bIsBigEndian);
    SHSTransform(shsInfo);
    if (nDigestSize > SHS_DIGESTSIZE) {
        memset(pDigest + SHS_DIGESTSIZE, 0, nDigestSize - SHS_DIGESTSIZE);
        nDigestSize = SHS_DIGESTSIZE;
    }
    SHAtoByte(pDigest, shsInfo->digest, nDigestSize);
    shsInfo->data[0] = 0;
}

void MEDIUS_SHA1_SECTION(endianTest) endianTest(unsigned int *bIsBigEndian)
{
    if ((*(unsigned short *)rtCryptShaEndianProbe >> 8) == '#')
        *bIsBigEndian = 1;
    else
        *bIsBigEndian = 0;
}
