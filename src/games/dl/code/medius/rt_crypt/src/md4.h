#ifndef MEDIUS_MD4_H
#define MEDIUS_MD4_H

// RSA Data Security MD4 (RFC 1320), with the transform taking the context instead of
// the state array. Layout from the retail md4_* accesses (md4Final clears 0x58 bytes);
// the debug information uses OpenSSL-style names (A..D, Nl, Nh, data) for the same words.
typedef struct { // 0x58
    /* 0x00 */ unsigned int state[4];
    /* 0x10 */ unsigned int count[2];
    /* 0x18 */ unsigned char buffer[64];
} MD4_CTX;

#ifdef __cplusplus
extern "C" {
#endif

// RFC 1320 PADDING: 0x80 followed by zeros (core.data).
extern unsigned char rtCryptMd4Padding[];

void KM_MD4(unsigned char *pMessage, unsigned int cbMessageSize, unsigned char *digest);
void md4Init(MD4_CTX *pMD4);
void md4Update(MD4_CTX *pMD4, unsigned char *input, unsigned int inputLen);
void md4Final(MD4_CTX *pMD4, unsigned char *digest);
void md4Transform(MD4_CTX *pMD4, unsigned char *block);
void Encode(unsigned char *output, unsigned int *input, unsigned int len);
void Decode(unsigned int *output, unsigned char *input, unsigned int len);

#ifdef __cplusplus
}
#endif

#endif
