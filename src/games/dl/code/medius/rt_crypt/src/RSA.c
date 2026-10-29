#include "common.h"
#include "RSA.h"

#define MEDIUS_RSA_SECTION(name) __attribute__((section(".medius_rsa_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_rsa_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void *memset(void *pointer, int value, unsigned int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);

void MEDIUS_RSA_SECTION(RSAEncryptBlock) RSAEncryptBlock(RSA_KEY *pPublicKey, unsigned int nPubExp, RSA_BLOCK *pPlainText, RSA_BLOCK *pCypherText)
{
    lint exp;
    lint mod;
    lint base;
    lint result;

    lintSetSmallValue(&exp, nPubExp);
    memcpy(&mod, pPublicKey, sizeof(RSA_KEY));
    memset(&mod.data[16], 0, sizeof(lint) - sizeof(RSA_KEY));
    memcpy(&base, pPlainText, sizeof(RSA_BLOCK));
    memset(&base.data[16], 0, sizeof(lint) - sizeof(RSA_BLOCK));
    EMODM(&result, &base, &exp, &mod);
    memcpy(pCypherText, &result, sizeof(RSA_BLOCK));
}

void MEDIUS_RSA_SECTION(RSADecryptBlock) RSADecryptBlock(RSA_KEY *pPublicKey, RSA_KEY *pPrivateKey, RSA_BLOCK *pCypherText, RSA_BLOCK *pPlainText)
{
    lint exp;
    lint mod;
    lint base;
    lint result;

    memcpy(&exp, pPrivateKey, sizeof(RSA_KEY));
    memset(&exp.data[16], 0, sizeof(lint) - sizeof(RSA_KEY));
    memcpy(&mod, pPublicKey, sizeof(RSA_KEY));
    memset(&mod.data[16], 0, sizeof(lint) - sizeof(RSA_KEY));
    memcpy(&base, pCypherText, sizeof(RSA_BLOCK));
    memset(&base.data[16], 0, sizeof(lint) - sizeof(RSA_BLOCK));
    EMODM(&result, &base, &exp, &mod);
    memcpy(pPlainText, &result, sizeof(RSA_BLOCK));
}

unsigned int MEDIUS_RSA_SECTION(RSAEncrypt) RSAEncrypt(RSA_KEY *pPublicKey, unsigned char *pPlainText, unsigned char *pCypherText, int cbBytes)
{
    unsigned int nDone = 0;

    for (; cbBytes >= 64; cbBytes -= 64) {
        RSAEncryptBlock(pPublicKey, RSA_PUBLIC_EXPONENT, (RSA_BLOCK *)pPlainText, (RSA_BLOCK *)pCypherText);
        nDone += 64;
        pPlainText += 64;
        pCypherText += 64;
    }
    return nDone;
}

unsigned int MEDIUS_RSA_SECTION(RSADecrypt) RSADecrypt(RSA_KEY *pPublicKey, RSA_KEY *pPrivateKey, unsigned char *pCypherText, unsigned char *pPlainText,
                        unsigned int cbBytes)
{
    unsigned int nDone = 0;

    for (; cbBytes >= 64; cbBytes -= 64) {
        RSADecryptBlock(pPublicKey, pPrivateKey, (RSA_BLOCK *)pCypherText, (RSA_BLOCK *)pPlainText);
        nDone += 64;
        pCypherText += 64;
        pPlainText += 64;
    }
    return nDone;
}
