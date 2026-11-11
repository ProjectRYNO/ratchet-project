#ifndef MEDIUS_MD2_H
#define MEDIUS_MD2_H

// RSA Data Security MD2 (RFC 1319), with state and checksum kept in the context instead
// of being passed to the transform. Layout from the retail md2_* field accesses
// (md2Init clears 0x34 bytes); the debug-info MD2_CTX typedef names no members.
typedef struct { // 0x34
    /* 0x00 */ unsigned char state[16];
    /* 0x10 */ unsigned char checksum[16];
    /* 0x20 */ unsigned char buffer[16];
    /* 0x30 */ unsigned int count;
} MD2_CTX;

// A 16-byte block; retail copies state and input blocks by assignment.
typedef struct {
    unsigned char bytes[16];
} MD2_BLOCK;

#ifdef __cplusplus
extern "C" {
#endif

// RFC 1319 PI_SUBST permutation (core.data rodata); the debug information names it gS.
extern unsigned char rtCryptMd2Sbox[256];
// RFC 1319 PADDING: pointers to the 0..16-byte pad strings, indexed by pad length.
extern unsigned char *rtCryptMd2Padding[];

void KM_MD2(unsigned char *pMessage, unsigned int cbMessageSize, unsigned char *digest);
void md2Init(MD2_CTX *pMD2);
void md2Update(MD2_CTX *pMD2, unsigned char *pData, unsigned int nDataLen);
void md2Final(MD2_CTX *pMD2, unsigned char *digest);
void md2Transform(MD2_CTX *pMD2, unsigned char *block);

#ifdef __cplusplus
}
#endif

#endif
