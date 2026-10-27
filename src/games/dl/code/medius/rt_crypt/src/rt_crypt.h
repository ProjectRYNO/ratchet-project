#ifndef MEDIUS_RT_CRYPT_H
#define MEDIUS_RT_CRYPT_H

// Key-master (KM_*) types. Names and layouts from the retail ELF debug information and,
// for CRYPT_DME_BASE_GLOBALS, the prototype (dltypes.txt).

typedef struct { // 0x40
    /* 0x00 */ unsigned int key[16];
} RSA_KEY;

typedef struct { // 0x80
    /* 0x00 */ RSA_KEY publicKey;
    /* 0x40 */ RSA_KEY privateKey;
} RSA_KEYPAIR;

typedef struct { // 0x40
    /* 0x00 */ unsigned char key[64];
} RC_KEY;

typedef struct { // 0x10C
    /* 0x000 */ unsigned int nSequence;
    /* 0x004 */ unsigned int x;
    /* 0x008 */ unsigned int y;
    /* 0x00C */ unsigned char state[256];
} RCDATA;

typedef unsigned int RT_CIPHER_TYPE;

typedef struct KEY_CHAIN { // 0x20
    /* 0x00 */ struct KEY_CHAIN *prev;
    /* 0x04 */ struct KEY_CHAIN *next;
    /* 0x08 */ unsigned int nID;
    /* 0x0C */ RT_CIPHER_TYPE eCypherType;
    /* 0x10 */ RSA_KEY *pPubKey;
    /* 0x14 */ RCDATA *pEncrypt;
    /* 0x18 */ RCDATA *pDecrypt;
    /* 0x1C */ RC_KEY *pPeerKey;
} KEY_CHAIN;

// Masters form a circular doubly linked list headed by CRYPT_DME_BASE_GLOBALS.gpKeyMaster.
typedef struct KEY_MASTER { // 0x30
    /* 0x00 */ struct KEY_MASTER *prev;
    /* 0x04 */ struct KEY_MASTER *next;
    /* 0x08 */ KEY_CHAIN *first;
    /* 0x0C */ KEY_CHAIN *last;
    /* 0x10 */ unsigned int nMasterID;
    /* 0x14 */ unsigned int nClientID;
    /* 0x18 */ unsigned int nGameID;
    /* 0x1C */ RSA_KEY *pPubKey;
    /* 0x20 */ RSA_KEY *pPriKey;
    /* 0x24 */ RCDATA *pEncrypt;
    /* 0x28 */ RCDATA *pDecrypt;
    /* 0x2C */ RC_KEY *pGameKey;
} KEY_MASTER;

// KM_Initialize/KM_GetLocalPublicKey select a key pair by flag: KM_FLAG_SERVER ->
// gServerKeyPair, KM_FLAG_UDP -> gUDPKeyPair, any other value -> gClientKeyPair.
#define KM_FLAG_SERVER 0x80000000
#define KM_FLAG_UDP 0xFFFFFFFF
#define KM_ERROR_NO_KEY 0xFFFFFFFD

typedef struct { // 0x204
    /* 0x000 */ KEY_MASTER *gpKeyMaster;
    /* 0x004 */ RSA_KEYPAIR gServerKeyPair;
    /* 0x084 */ RSA_KEYPAIR gClientKeyPair;
    /* 0x104 */ RSA_KEYPAIR gUDPKeyPair;
    /* 0x184 */ RSA_KEYPAIR gAppKeyPair;
} CRYPT_DME_BASE_GLOBALS;

#ifdef __cplusplus
extern "C" {
#endif

extern CRYPT_DME_BASE_GLOBALS *gCryptGlobals;

void KM_Initialize(unsigned int nFlag, RSA_KEYPAIR *pRsaKeyPair);
unsigned int IsNullRSAKey(RSA_KEY *pKey);
unsigned int KM_GetLocalPublicKey(unsigned int nFlag, RSA_KEY *pPublicKey);
KEY_MASTER *GetKeyMaster(unsigned int nMasterID);

int NetUseCrypt(void);
void rt_crypt_resolve_interface(void);
unsigned int IsNullRCKey(RC_KEY *pKey);
KEY_CHAIN *NewKeyChain(void);
void DeleteKeyChain(KEY_CHAIN *pKeyChain);
void AppendKeyChain(KEY_MASTER *pKeyMaster, KEY_CHAIN *pKeyChain);
KEY_CHAIN *GetKeyChain(KEY_MASTER *pKeyMaster, unsigned int nID);
void RemoveKeyChain(KEY_MASTER *pKeyMaster, KEY_CHAIN *pKeyChain);
char *KM_GetVersionStringPtr(void);
void KM_SHA1(unsigned char *pMessage, unsigned int cbMessageSize, unsigned char *pDigest, unsigned int cbDigestSize);
void KM_Salted_SHA1(unsigned char *pSalt, unsigned int cbSaltSize, unsigned char *pMessage, unsigned int cbMessageSize,
                    unsigned char *pDigest, unsigned int cbDigestSize);
unsigned int KM_Create(unsigned int nMasterID, unsigned int nID);
void KM_SetLocalClientID(unsigned int nKeyMaster, unsigned int nClientID);
unsigned int KM_SetPublicKey(unsigned int nMasterID, unsigned int nClientID, RSA_KEY *pKey);
unsigned int KM_GetPublicKey(unsigned int nMasterID, unsigned int nClientID, RSA_KEY *pKey);
unsigned int KM_SetLocalKeyPair(unsigned int nMasterID, RSA_KEYPAIR *pKeyPair);
unsigned int KM_SetGameSessionKey(unsigned int nMasterID, unsigned int nGameID, RC_KEY *pKey);
unsigned int KM_GetGameSessionKey(unsigned int nMasterID, unsigned int nGameID, RC_KEY *pKey);
unsigned int KM_AddSymmetricKey(unsigned int nMasterID, unsigned int nID, RC_KEY *pKey);
unsigned int KM_GetSymmetricKey(unsigned int nMasterID, unsigned int nID, RC_KEY *pKey);
int KM_CompareSymmetricKey(unsigned int nMasterID, unsigned int nID, RC_KEY *pKey);
void KM_DeleteSymmetricKey(unsigned int nMasterID, unsigned int nID);
void KM_DeleteKeys(unsigned int nMasterID, unsigned int nID);
void InitializePRNG(void);
void KM_CreateRandomRCKey(RC_KEY *pNewKey);
unsigned int KM_CopyKeys(unsigned int nSrcMasterID, unsigned int nSrcID, unsigned int nDestMasterID, unsigned int nDestID);
void KM_Destroy(unsigned int nMasterID);
void KM_Cleanup(unsigned int nMasterType);
void KM_RSAAdjust(unsigned char *pMessage, RSA_KEY *pPubKey);
// ps2/RC_platform (retained assembly).
void RCInitialize(RCDATA *pData, RC_KEY *pKey);
// LargeInt.c: adds the second 512-byte large integer into the first.
void lintAddIP(unsigned char *pSum, unsigned char *pAddend);

#ifdef __cplusplus
}
#endif

#endif
