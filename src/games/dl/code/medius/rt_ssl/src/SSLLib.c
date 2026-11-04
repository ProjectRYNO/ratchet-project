#include "common.h"

#define MEDIUS_SSL_SECTION(name) __attribute__((section(".medius_ssl_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_ssl_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct SSL {
    int eState;
    int ePendingCipher;
    int eClientCipher;
    int eServerCipher;
    unsigned int serverMsgOff;
    unsigned int serverMsgLen;
    unsigned int nNetOutSize;
    unsigned int nAppOutSize;
    unsigned int pad20[5];
    void *pServerCert;
    unsigned char pad38[0x414 - 0x38];
    unsigned int uiServerMessageSize;
    unsigned int uiAppoutMessageSize;
    unsigned char *serverMsg;
    unsigned char *appoutMsg;
    unsigned char netoutMsg[2048];
} SSL;

typedef void *(*SSL_MALLOC)(unsigned int);
typedef void (*SSL_FREE)(void *);
typedef unsigned int (*SSL_RANDOM)(void);

extern SSL_MALLOC gMallocFunc;
extern SSL_FREE gFreeFunc;
extern SSL_RANDOM gRandomFunc;
extern unsigned int guiServerMessageSize;
extern unsigned int guiAppoutMessageSize;
extern int nSSLInstanceCount;
// SSLLib.c source path string used by assert (0x00199F28)
extern char mediusSSLLibSourceFile[];
// assert string "0 == nMsgSize" (0x0019A270)
extern char mediusSSLAssertZeroMsgSize[];
// assert string "pSSL->eState == SSLSTATE_SERVER_HELLO_DONE" (0x0019A280)
extern char mediusSSLAssertHelloDoneState[];
// assert string "nMsgLen == nMsgSize" (0x0019A2B0)
extern char mediusSSLAssertFinishedLen[];
// assert string on app-out buffer space (0x0019A310)
extern char mediusSSLAssertAppoutSpace[];

int memcmp(const void *, const void *, unsigned int);
void *memcpy(void *, const void *, unsigned int);
void __assert(const char *, int, const char *);
int rt_memory_allocate(void **p, unsigned long size);
void rt_memory_free(void **p);
unsigned int CreateNetMsg(SSL *pSSL, unsigned char cType, unsigned char *pMsg, unsigned int nSize);
unsigned int CreateFinishedMsg(SSL *pSSL, int bClient, unsigned char *pMsg, unsigned int nSize);
void CleanupCertificates(void);
void *DeleteCertificate(void *);
void DestroyCertificate(void *);
unsigned int randomMT(void);
void *MemAlloc(unsigned int nSize);
void MemFree(void *pData);

typedef void *(*SSL_MALLOC)(unsigned int);
typedef void (*SSL_FREE)(void *);
typedef unsigned int (*SSL_RANDOM)(void);
// assert string "nMsgSize == 2" in ParseAlertMsg (0x0019A3B8)
extern char mediusSSLAssertAlertMsgSize[];

void *MEDIUS_SSL_SECTION(MemAlloc) MemAlloc(unsigned int nSize)
{
    void *p[4];
    p[0] = 0;
    rt_memory_allocate(p, nSize);
    return p[0];
}

void MEDIUS_SSL_SECTION(MemFree) MemFree(void *pData)
{
    void *p[4];
    p[0] = pData;
    rt_memory_free(p);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", func_01EDF468);

int MEDIUS_SSL_SECTION(SSL_Initialize) SSL_Initialize(SSL_MALLOC pMallocFunc, SSL_FREE pFreeFunc, SSL_RANDOM pRandomFunc, int a_iServerMsgSize, int a_iAppoutMsgSize)
{
    gMallocFunc = pMallocFunc;
    gFreeFunc = pFreeFunc;
    gRandomFunc = pRandomFunc;
    if (pMallocFunc == 0) {
        gMallocFunc = MemAlloc;
    }
    if (pFreeFunc == 0) {
        gFreeFunc = MemFree;
    }
    if (pRandomFunc == 0) {
        gRandomFunc = randomMT;
    }
    if (a_iServerMsgSize > 0) {
        guiServerMessageSize = a_iServerMsgSize;
    }
    if (a_iAppoutMsgSize > 0) {
        guiAppoutMessageSize = a_iAppoutMsgSize;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", SSL_AddRootCertificate);

int MEDIUS_SSL_SECTION(SSL_AddCRL) SSL_AddCRL(unsigned char *pCRL, unsigned int nLen)
{
    return 2;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", SSL_Create);

int MEDIUS_SSL_SECTION(SSL_Destroy) SSL_Destroy(SSL *pSSL)
{
    if (pSSL != 0) {
        if (pSSL->pServerCert != 0) {
            DeleteCertificate(pSSL->pServerCert);
            DestroyCertificate(pSSL->pServerCert);
        }
        gFreeFunc(pSSL->appoutMsg);
        gFreeFunc(pSSL->serverMsg);
        gFreeFunc(pSSL);
        nSSLInstanceCount--;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", SSL_Callback);

int MEDIUS_SSL_SECTION(SSL_Cleanup) SSL_Cleanup(void)
{
    CleanupCertificates();
    gRandomFunc = 0;
    gFreeFunc = 0;
    gMallocFunc = 0;
    guiServerMessageSize = 0;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", ParseServerMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", ParseHandshake);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", ParseChangeCipherSpec);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", ParseServerHello);

unsigned int MEDIUS_SSL_SECTION(ParseServerHelloDone) ParseServerHelloDone(SSL *pSSL, unsigned char *pMsg, unsigned int nMsgSize)
{
    if (nMsgSize != 0) {
        __assert(mediusSSLLibSourceFile, 0x405, mediusSSLAssertZeroMsgSize);
    }
    if (pSSL->eState != 8) {
        __assert(mediusSSLLibSourceFile, 0x408, mediusSSLAssertHelloDoneState);
    }
    pSSL->eState = 9;
    return nMsgSize;
}

unsigned int MEDIUS_SSL_SECTION(VerifyServerFinished) VerifyServerFinished(SSL *pSSL, unsigned char *pMsg, unsigned int nMsgSize)
{
    unsigned char buf[48];
    unsigned char len;
    len = CreateFinishedMsg(pSSL, 0, buf, 0x24);
    if (len != nMsgSize) {
        __assert(mediusSSLLibSourceFile, 0x423, mediusSSLAssertFinishedLen);
    }
    return memcmp(pMsg, buf, len | nMsgSize);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", ParseCertificateMsg);

unsigned int MEDIUS_SSL_SECTION(ParseAppData) ParseAppData(SSL *pSSL, unsigned char *pMsg, unsigned int nMsgSize)
{
    if (pSSL->uiAppoutMessageSize - pSSL->nAppOutSize < nMsgSize) {
        __assert(mediusSSLLibSourceFile, 0x470, mediusSSLAssertAppoutSpace);
    }
    memcpy(pSSL->appoutMsg + pSSL->nAppOutSize, pMsg, nMsgSize);
    pSSL->nAppOutSize += nMsgSize;
    return nMsgSize;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", CreateFinishedMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", CalculateMAC);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_ssl/src/SSLLib", CreateNetMsg);

unsigned int MEDIUS_SSL_SECTION(ParseAlertMsg) ParseAlertMsg(SSL *pSSL, unsigned char *pMsg, unsigned int nMsgSize)
{
    if (nMsgSize != 2) {
        __assert(mediusSSLLibSourceFile, 0x573, mediusSSLAssertAlertMsgSize);
    }
    if (pMsg[1] == 0) {
        CreateAlertMsg(pSSL, 1, 0);
        pSSL->eState = 0x31;
    } else {
        pSSL->eState = 0x31;
    }
    return nMsgSize;
}

unsigned int MEDIUS_SSL_SECTION(CreateAlertMsg) CreateAlertMsg(SSL *pSSL, unsigned char cCategory, unsigned char cType)
{
    unsigned char msg[2];
    msg[0] = cCategory;
    msg[1] = cType;
    return CreateNetMsg(pSSL, 0x15, msg, 2);
}
