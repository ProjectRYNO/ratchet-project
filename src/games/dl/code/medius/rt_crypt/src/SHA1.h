#ifndef MEDIUS_SHA1_H
#define MEDIUS_SHA1_H

// Peter Gutmann's public-domain SHS code (shsInit/shsUpdate/shsFinal) under SHA* names.
// longReverse, SHSTransform and SHAtoByte are retained assembly in ps2/SHA1_platform.
#define SHS_DATASIZE 64
#define SHS_DIGESTSIZE 20

// Names and layout from the retail ELF debug information.
typedef struct { // 0x60
    /* 0x00 */ unsigned int data[16];
    /* 0x40 */ unsigned int digest[5];
    /* 0x54 */ unsigned int bIsBigEndian;
    /* 0x58 */ unsigned int countLo;
    /* 0x5C */ unsigned int countHi;
} SHA_CTX;

// A 64-byte input block; retail copies whole blocks into SHA_CTX.data by assignment.
typedef struct {
    unsigned char bytes[SHS_DATASIZE];
} SHA_BLOCK;

#ifdef __cplusplus
extern "C" {
#endif

// Initial SHA_CTX (digest seeded with the SHA-1 constants), copied whole by SHAInit.
extern SHA_CTX rtCryptShaInitState;
// The "#S" string literal endianTest reads as an unsigned short (rodata).
extern char rtCryptShaEndianProbe[];

void SHAInit(SHA_CTX *shsInfo);
void SHAUpdate(SHA_CTX *shsInfo, unsigned char *pBuffer, unsigned int nCount);
void SHAFinal(SHA_CTX *shsInfo, unsigned char *pDigest, unsigned int nDigestSize);
void endianTest(unsigned int *bIsBigEndian);
void longReverse(unsigned int *buffer, int byteCount, int bIsBigEndian);
void SHSTransform(SHA_CTX *shsInfo);
void SHAtoByte(unsigned char *output, unsigned int *input, unsigned int len);

#ifdef __cplusplus
}
#endif

#endif
