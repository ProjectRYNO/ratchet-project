#ifndef MEDIUS_RSA_H
#define MEDIUS_RSA_H

#include "rt_crypt.h"
#include "LargeInt.h"

// 512-bit RSA over lint: blocks and keys are 64 bytes, zero-extended to 4096 bits.
#define RSA_PUBLIC_EXPONENT 17

// Name and layout from the retail ELF debug information.
typedef struct { // 0x40
    /* 0x00 */ unsigned int data[16];
} RSA_BLOCK;

#ifdef __cplusplus
extern "C" {
#endif

void RSAEncryptBlock(RSA_KEY *pPublicKey, unsigned int nPubExp, RSA_BLOCK *pPlainText, RSA_BLOCK *pCypherText);
void RSADecryptBlock(RSA_KEY *pPublicKey, RSA_KEY *pPrivateKey, RSA_BLOCK *pCypherText, RSA_BLOCK *pPlainText);
unsigned int RSAEncrypt(RSA_KEY *pPublicKey, unsigned char *pPlainText, unsigned char *pCypherText, int cbBytes);
unsigned int RSADecrypt(RSA_KEY *pPublicKey, RSA_KEY *pPrivateKey, unsigned char *pCypherText, unsigned char *pPlainText,
                        unsigned int cbBytes);
// LargeInt.c: modular exponentiation, pResult = pBase ^ pExp mod pMod.
void EMODM(lint *pResult, lint *pBase, lint *pExp, lint *pMod);

#ifdef __cplusplus
}
#endif

#endif
