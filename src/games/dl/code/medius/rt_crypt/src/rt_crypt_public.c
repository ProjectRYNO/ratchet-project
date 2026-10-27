#include "common.h"
#include "rt_crypt.h"

#define MEDIUS_CRYPTPUB_SECTION(name) __attribute__((section(".medius_cryptpub_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_cryptpub_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void *memset(void *pointer, int value, unsigned int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);

void MEDIUS_CRYPTPUB_SECTION(KM_Initialize) KM_Initialize(unsigned int nFlag, RSA_KEYPAIR *pRsaKeyPair)
{
    if (nFlag == KM_FLAG_UDP) {
        if (pRsaKeyPair) memcpy(&gCryptGlobals->gUDPKeyPair, pRsaKeyPair, sizeof(RSA_KEYPAIR));
        else memset(&gCryptGlobals->gUDPKeyPair, 0, sizeof(RSA_KEYPAIR));
    } else if (nFlag == KM_FLAG_SERVER) {
        if (pRsaKeyPair) memcpy(&gCryptGlobals->gServerKeyPair, pRsaKeyPair, sizeof(RSA_KEYPAIR));
        else memset(&gCryptGlobals->gServerKeyPair, 0, sizeof(RSA_KEYPAIR));
    } else {
        if (pRsaKeyPair) memcpy(&gCryptGlobals->gClientKeyPair, pRsaKeyPair, sizeof(RSA_KEYPAIR));
        else memset(&gCryptGlobals->gClientKeyPair, 0, sizeof(RSA_KEYPAIR));
    }
}

unsigned int MEDIUS_CRYPTPUB_SECTION(IsNullRSAKey) IsNullRSAKey(RSA_KEY *pKey)
{
    unsigned int i;
    unsigned int *p;

    if (pKey) {
        p = pKey->key;
        for (i = 0; i < 16; i++) {
            if (*p++) return 0;
        }
    }
    return 1;
}

unsigned int MEDIUS_CRYPTPUB_SECTION(KM_GetLocalPublicKey) KM_GetLocalPublicKey(unsigned int nFlag, RSA_KEY *pPublicKey)
{
    unsigned int result;

    if (nFlag == KM_FLAG_SERVER) {
        result = 0;
        if (IsNullRSAKey(&gCryptGlobals->gServerKeyPair.publicKey)) result = KM_ERROR_NO_KEY;
        if (pPublicKey) memcpy(pPublicKey, &gCryptGlobals->gServerKeyPair.publicKey, sizeof(RSA_KEY));
    } else if (nFlag == KM_FLAG_UDP) {
        result = 0;
        if (IsNullRSAKey(&gCryptGlobals->gUDPKeyPair.publicKey)) result = KM_ERROR_NO_KEY;
        if (pPublicKey) memcpy(pPublicKey, &gCryptGlobals->gUDPKeyPair.publicKey, sizeof(RSA_KEY));
    } else {
        result = 0;
        if (IsNullRSAKey(&gCryptGlobals->gClientKeyPair.publicKey)) result = KM_ERROR_NO_KEY;
        if (pPublicKey) memcpy(pPublicKey, &gCryptGlobals->gClientKeyPair.publicKey, sizeof(RSA_KEY));
    }
    if (pPublicKey && result) memset(pPublicKey, 0, sizeof(RSA_KEY));
    return result;
}

KEY_MASTER *MEDIUS_CRYPTPUB_SECTION(GetKeyMaster) GetKeyMaster(unsigned int nMasterID)
{
    KEY_MASTER *pFirst;
    KEY_MASTER *pMaster = gCryptGlobals->gpKeyMaster;

    if (pMaster && pMaster->nMasterID != nMasterID) {
        pFirst = pMaster;
        pMaster = pMaster->next;
        while (1) {
            if (pMaster == pFirst) pMaster = 0;
            if (!pMaster) break;
            if (pMaster->nMasterID == nMasterID) break;
            pMaster = pMaster->next;
        }
    }
    return pMaster;
}
