#include "common.h"
#include "rt_crypt.h"
#include "SHA1.h"

#define MEDIUS_CRYPT_SECTION(name) __attribute__((section(".medius_crypt_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_crypt_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#define RT_CIPHER_512BIT_SHA1 1
#define NetErrorNone 0

extern void *memset(void *pointer, int value, unsigned int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);
extern int rt_memory_allocate(void **pointer, unsigned long size);
extern int rt_memory_free(void **pointer);
extern void setNewSeed(unsigned int skew);
extern unsigned int randomMT(void);

// "rt_crypt version: 2.10.2" (rodata).
extern char rtCryptVersionString[];
// Set once InitializePRNG has seeded the Mersenne Twister.
extern unsigned char rtCryptPrngSeeded;

int MEDIUS_CRYPT_SECTION(NetUseCrypt) NetUseCrypt(void)
{
    rt_crypt_resolve_interface();
    return NetErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", rt_crypt_resolve_interface);

unsigned int MEDIUS_CRYPT_SECTION(IsNullRCKey) IsNullRCKey(RC_KEY *pKey)
{
    unsigned int i;

    if (pKey) {
        for (i = 0; i < 64; i++) {
            if (pKey->key[i]) return 0;
        }
    }
    return 1;
}

KEY_CHAIN *MEDIUS_CRYPT_SECTION(NewKeyChain) NewKeyChain(void)
{
    void *pMem;
    KEY_CHAIN *pKeyChain;

    rt_memory_allocate(&pMem, sizeof(KEY_CHAIN));
    pKeyChain = pMem;
    if (pKeyChain) {
        pKeyChain->prev = 0;
        pKeyChain->eCypherType = RT_CIPHER_512BIT_SHA1;
        pKeyChain->next = 0;
        pKeyChain->pPubKey = 0;
        pKeyChain->pEncrypt = 0;
        pKeyChain->pDecrypt = 0;
        pKeyChain->pPeerKey = 0;
        pKeyChain->nID = 0;
    }
    return pKeyChain;
}

void MEDIUS_CRYPT_SECTION(DeleteKeyChain) DeleteKeyChain(KEY_CHAIN *pKeyChain)
{
    void *pMem;

    pMem = pKeyChain;
    if (pKeyChain) {
        if (pKeyChain->pPubKey) rt_memory_free((void **)&pKeyChain->pPubKey);
        if (pKeyChain->pPeerKey) rt_memory_free((void **)&pKeyChain->pPeerKey);
        if (pKeyChain->pEncrypt) rt_memory_free((void **)&pKeyChain->pEncrypt);
        if (pKeyChain->pDecrypt) rt_memory_free((void **)&pKeyChain->pDecrypt);
        rt_memory_free(&pMem);
    }
}

void MEDIUS_CRYPT_SECTION(AppendKeyChain) AppendKeyChain(KEY_MASTER *pKeyMaster, KEY_CHAIN *pKeyChain)
{
    KEY_CHAIN *pLast;

    if (pKeyMaster) {
        pKeyChain->next = 0;
        if (pKeyMaster->first) {
            pLast = pKeyMaster->last;
            pKeyChain->prev = pLast;
            pLast->next = pKeyChain;
        } else {
            pKeyMaster->first = pKeyChain;
            pKeyChain->prev = 0;
        }
        pKeyMaster->last = pKeyChain;
    }
}

KEY_CHAIN *MEDIUS_CRYPT_SECTION(GetKeyChain) GetKeyChain(KEY_MASTER *pKeyMaster, unsigned int nID)
{
    KEY_CHAIN *pKeyChain = 0;

    nID &= 0x1FFFFFFF;
    if (pKeyMaster) pKeyChain = pKeyMaster->first;
    while (pKeyChain && pKeyChain->nID != nID) pKeyChain = pKeyChain->next;
    return pKeyChain;
}

void MEDIUS_CRYPT_SECTION(RemoveKeyChain) RemoveKeyChain(KEY_MASTER *pKeyMaster, KEY_CHAIN *pKeyChain)
{
    if (pKeyMaster && pKeyChain) {
        if (pKeyChain->next) pKeyChain->next->prev = pKeyChain->prev;
        else pKeyMaster->last = pKeyChain->prev;
        if (pKeyChain->prev) pKeyChain->prev->next = pKeyChain->next;
        else pKeyMaster->first = pKeyChain->next;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", func_01EB30B0);

char *MEDIUS_CRYPT_SECTION(KM_GetVersionStringPtr) KM_GetVersionStringPtr(void)
{
    return rtCryptVersionString;
}

void MEDIUS_CRYPT_SECTION(KM_SHA1) KM_SHA1(unsigned char *pMessage, unsigned int cbMessageSize, unsigned char *pDigest, unsigned int cbDigestSize)
{
    SHA_CTX context;

    SHAInit(&context);
    SHAUpdate(&context, pMessage, cbMessageSize);
    SHAFinal(&context, pDigest, cbDigestSize);
}

void MEDIUS_CRYPT_SECTION(KM_Salted_SHA1) KM_Salted_SHA1(unsigned char *pSalt, unsigned int cbSaltSize, unsigned char *pMessage, unsigned int cbMessageSize,
                    unsigned char *pDigest, unsigned int cbDigestSize)
{
    SHA_CTX context;

    SHAInit(&context);
    if (pSalt && cbSaltSize) SHAUpdate(&context, pSalt, cbSaltSize);
    SHAUpdate(&context, pMessage, cbMessageSize);
    SHAFinal(&context, pDigest, cbDigestSize);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_Create);

void MEDIUS_CRYPT_SECTION(KM_SetLocalClientID) KM_SetLocalClientID(unsigned int nKeyMaster, unsigned int nClientID)
{
    KEY_MASTER *pKeyMaster = GetKeyMaster(nKeyMaster);

    if (pKeyMaster) pKeyMaster->nClientID = nClientID;
}

unsigned int MEDIUS_CRYPT_SECTION(KM_SetPublicKey) KM_SetPublicKey(unsigned int nMasterID, unsigned int nClientID, RSA_KEY *pKey)
{
    KEY_MASTER *pKeyMaster;
    KEY_CHAIN *pKeyChain;

    pKeyMaster = GetKeyMaster(nMasterID);
    if (!pKeyMaster) return 0xFFFFFFFF;
    pKeyChain = GetKeyChain(pKeyMaster, nClientID);
    if (IsNullRSAKey(pKey)) {
        if (pKeyChain && pKeyChain->pPubKey) memset(pKeyChain->pPubKey, 0, sizeof(RSA_KEY));
    } else {
        if (!pKeyChain) {
            pKeyChain = NewKeyChain();
            pKeyChain->nID = nClientID;
            AppendKeyChain(pKeyMaster, pKeyChain);
        }
        if (!pKeyChain->pPubKey) rt_memory_allocate((void **)&pKeyChain->pPubKey, sizeof(RSA_KEY));
        memcpy(pKeyChain->pPubKey, pKey, sizeof(RSA_KEY));
    }
    return 0;
}

unsigned int MEDIUS_CRYPT_SECTION(KM_GetPublicKey) KM_GetPublicKey(unsigned int nMasterID, unsigned int nClientID, RSA_KEY *pKey)
{
    KEY_MASTER *pKeyMaster;
    KEY_CHAIN *pKeyChain;

    pKeyMaster = GetKeyMaster(nMasterID);
    if (pKeyMaster && (pKeyChain = GetKeyChain(pKeyMaster, nClientID)) && !IsNullRSAKey(pKeyChain->pPubKey)) {
        memcpy(pKey, pKeyChain->pPubKey, sizeof(RSA_KEY));
        return 0;
    }
    if (pKey) memset(pKey, 0, sizeof(RSA_KEY));
    return 0xFFFFFFFF;
}

unsigned int MEDIUS_CRYPT_SECTION(KM_SetLocalKeyPair) KM_SetLocalKeyPair(unsigned int nMasterID, RSA_KEYPAIR *pKeyPair)
{
    KEY_MASTER *pKeyMaster;

    pKeyMaster = GetKeyMaster(nMasterID);
    if (!pKeyMaster) return 0xFFFFFFFF;
    if (IsNullRSAKey(&pKeyPair->publicKey) || IsNullRSAKey(&pKeyPair->privateKey)) {
        if (pKeyMaster->pPubKey) memset(pKeyMaster->pPubKey, 0, sizeof(RSA_KEY));
        if (pKeyMaster->pPriKey) memset(pKeyMaster->pPriKey, 0, sizeof(RSA_KEY));
    } else {
        if (!pKeyMaster->pPubKey) rt_memory_allocate((void **)&pKeyMaster->pPubKey, sizeof(RSA_KEY));
        if (!pKeyMaster->pPriKey) rt_memory_allocate((void **)&pKeyMaster->pPriKey, sizeof(RSA_KEY));
        memcpy(pKeyMaster->pPubKey, &pKeyPair->publicKey, sizeof(RSA_KEY));
        memcpy(pKeyMaster->pPriKey, &pKeyPair->privateKey, sizeof(RSA_KEY));
    }
    return 0;
}

unsigned int MEDIUS_CRYPT_SECTION(KM_SetGameSessionKey) KM_SetGameSessionKey(unsigned int nMasterID, unsigned int nGameID, RC_KEY *pKey)
{
    KEY_MASTER *pKeyMaster;
    unsigned int result;

    pKeyMaster = GetKeyMaster(nMasterID);
    if (!pKeyMaster) return 0xFFFFFFFF;
    if (IsNullRCKey(pKey)) return 0xFFFFFFFF;
        if (!pKeyMaster->pGameKey) rt_memory_allocate((void **)&pKeyMaster->pGameKey, sizeof(RC_KEY));
        if (!pKeyMaster->pEncrypt) rt_memory_allocate((void **)&pKeyMaster->pEncrypt, sizeof(RCDATA));
        if (!pKeyMaster->pDecrypt) rt_memory_allocate((void **)&pKeyMaster->pDecrypt, sizeof(RCDATA));
        pKeyMaster->nGameID = nGameID;
        memcpy(pKeyMaster->pGameKey, pKey, sizeof(RC_KEY));
        RCInitialize(pKeyMaster->pEncrypt, pKey);
        RCInitialize(pKeyMaster->pDecrypt, pKey);
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_GetGameSessionKey);

unsigned int MEDIUS_CRYPT_SECTION(KM_AddSymmetricKey) KM_AddSymmetricKey(unsigned int nMasterID, unsigned int nID, RC_KEY *pKey)
{
    KEY_MASTER *pKeyMaster;
    KEY_CHAIN *pKeyChain;
    unsigned int result;

    pKeyMaster = GetKeyMaster(nMasterID);
    if (!pKeyMaster) return 0xFFFFFFFF;
    if (IsNullRCKey(pKey)) return 0xFFFFFFFF;
        pKeyChain = GetKeyChain(pKeyMaster, nID);
        if (!pKeyChain) {
            pKeyChain = NewKeyChain();
            pKeyChain->nID = nID;
            AppendKeyChain(pKeyMaster, pKeyChain);
        }
        if (!pKeyChain->pPeerKey) rt_memory_allocate((void **)&pKeyChain->pPeerKey, sizeof(RC_KEY));
        if (!pKeyChain->pEncrypt) rt_memory_allocate((void **)&pKeyChain->pEncrypt, sizeof(RCDATA));
        if (!pKeyChain->pDecrypt) rt_memory_allocate((void **)&pKeyChain->pDecrypt, sizeof(RCDATA));
        memcpy(pKeyChain->pPeerKey, pKey, sizeof(RC_KEY));
        RCInitialize(pKeyChain->pEncrypt, pKey);
        RCInitialize(pKeyChain->pDecrypt, pKey);
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_GetSymmetricKey);

int MEDIUS_CRYPT_SECTION(KM_CompareSymmetricKey) KM_CompareSymmetricKey(unsigned int nMasterID, unsigned int nID, RC_KEY *pKey)
{
    RC_KEY key;
    int i;

    if (IsNullRCKey(pKey)) return -1;
    if (KM_GetSymmetricKey(nMasterID, nID, &key)) return 1;
    i = 63;
    do {
        if (pKey->key[i] > key.key[i]) return 1;
        if (pKey->key[i] < key.key[i]) return -1;
    } while (i-- > 0);
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_DeleteSymmetricKey);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_CopyKeys);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_DigiSign);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_DigiVerify);

void MEDIUS_CRYPT_SECTION(KM_DeleteKeys) KM_DeleteKeys(unsigned int nMasterID, unsigned int nID)
{
    KEY_MASTER *pKeyMaster;
    KEY_CHAIN *pKeyChain;

    pKeyMaster = GetKeyMaster(nMasterID);
    pKeyChain = GetKeyChain(pKeyMaster, nID);
    if (pKeyChain) {
        RemoveKeyChain(pKeyMaster, pKeyChain);
        DeleteKeyChain(pKeyChain);
    }
}

void MEDIUS_CRYPT_SECTION(KM_Destroy) KM_Destroy(unsigned int nMasterID)
{
    KEY_MASTER *pKeyMaster;
    KEY_CHAIN *pKeyChain;
    void *pMem;

    pKeyMaster = GetKeyMaster(nMasterID);
    if (!pKeyMaster) return;
    while ((pKeyChain = pKeyMaster->last)) {
        RemoveKeyChain(pKeyMaster, pKeyChain);
        DeleteKeyChain(pKeyChain);
    }
    if (pKeyMaster->pPriKey) rt_memory_free((void **)&pKeyMaster->pPriKey);
    if (pKeyMaster->pPubKey) {
        pMem = pKeyMaster->pPubKey;
        rt_memory_free(&pMem);
        pKeyMaster->pPubKey = 0;
    }
    if (pKeyMaster->pGameKey) rt_memory_free((void **)&pKeyMaster->pGameKey);
    if (pKeyMaster->pEncrypt) rt_memory_free((void **)&pKeyMaster->pEncrypt);
    if (pKeyMaster->pDecrypt) rt_memory_free((void **)&pKeyMaster->pDecrypt);
    if (gCryptGlobals->gpKeyMaster == pKeyMaster) gCryptGlobals->gpKeyMaster = pKeyMaster->next;
    pKeyMaster->next->prev = pKeyMaster->prev;
    pKeyMaster->prev->next = pKeyMaster->next;
    if (gCryptGlobals->gpKeyMaster == pKeyMaster) gCryptGlobals->gpKeyMaster = 0;
    pMem = pKeyMaster;
    rt_memory_free(&pMem);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_Cleanup);

void MEDIUS_CRYPT_SECTION(InitializePRNG) InitializePRNG(void)
{
    if (!rtCryptPrngSeeded) {
        rtCryptPrngSeeded = 1;
        setNewSeed(0x035D2325);
    }
}

void MEDIUS_CRYPT_SECTION(KM_CreateRandomRCKey) KM_CreateRandomRCKey(RC_KEY *pNewKey)
{
    unsigned char i;

    InitializePRNG();
    for (i = 0; i < 16; i++) ((unsigned int *)pNewKey->key)[i] = randomMT();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_Encrypt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_Encrypt2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_Decrypt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", KM_Decrypt2);

void MEDIUS_CRYPT_SECTION(KM_RSAAdjust) KM_RSAAdjust(unsigned char *pMessage, RSA_KEY *pPubKey)
{
    unsigned char message[512];
    unsigned char key[512];

    memset(message, 0, sizeof(message));
    memset(key, 0, sizeof(key));
    memcpy(message, pMessage, sizeof(RSA_KEY));
    memcpy(key, pPubKey, sizeof(RSA_KEY));
    lintAddIP(message, key);
    memcpy(pMessage, message, sizeof(RSA_KEY));
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/rt_crypt", GetSoftwareKeyPair);
