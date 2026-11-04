#include "common.h"

#define MEDIUS_X509_SECTION(name) __attribute__((section(".medius_x509_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_x509_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct TBSCERTIFICATE TBSCERTIFICATE;
typedef void (*CERT_FREE)(TBSCERTIFICATE *);
typedef struct { unsigned char b[80]; } X509NAME;
typedef struct { unsigned int a, b; } DATETIME;
struct TBSCERTIFICATE {
    TBSCERTIFICATE *prev;
    TBSCERTIFICATE *next;
    TBSCERTIFICATE *pRootCert;
    CERT_FREE pFreeFunc;
    unsigned int version;
    unsigned int status;
    unsigned int hashAlgorithm;
    unsigned int serialLen;
    unsigned int pubKeyLen;
    unsigned int pubExp;
    unsigned int receiveTime;
    unsigned int validTime;
    DATETIME enableTime;
    DATETIME expireTime;
    unsigned char serialNum[20];
    unsigned char digest[20];
    X509NAME name;
    X509NAME issuer;
    unsigned char pubKey[256];
    unsigned char signature[256];
};

extern TBSCERTIFICATE *gpRootCerts;
extern TBSCERTIFICATE *gpInterMediateCerts;
extern TBSCERTIFICATE *gpScertRootCert;
int memcmp(const void *, const void *, unsigned int);
void __assert(const char *, int, const char *);
// x509.c source path string used by assert (0x0019A9A0)
extern char mediusX509SourceFile[];
// assert string "nDataSize == pCert->pubKeyLen" (0x0019AD18)
extern char mediusX509AssertPubKeyLen[];
void RSA2048Encrypt(unsigned char *, unsigned int, unsigned int, unsigned char *, unsigned int);
TBSCERTIFICATE *DeleteCertificate(TBSCERTIFICATE *pCert);
void DestroyCertificate(TBSCERTIFICATE *pCert);

TBSCERTIFICATE *MEDIUS_X509_SECTION(InsertCertificate) InsertCertificate(TBSCERTIFICATE *pCert)
{
    TBSCERTIFICATE *p;
    TBSCERTIFICATE **ppList;
    TBSCERTIFICATE *head;
    TBSCERTIFICATE *tail;
    if (pCert == 0) {
        return 0;
    }
    p = FindCertificate(&pCert->name);
    if (p != 0) {
        if (p->status & 0x80) {
            return 0;
        }
        DestroyCertificate(DeleteCertificate(p));
    }
    if (pCert->status & 0x80) {
        ppList = &gpRootCerts;
    } else {
        ppList = &gpInterMediateCerts;
    }
    head = *ppList;
    if (head == 0) {
        *ppList = pCert;
        pCert->prev = pCert;
        pCert->next = pCert;
    } else {
        tail = head->prev;
        pCert->next = head;
        pCert->prev = tail;
        tail->next = pCert;
        pCert->next->prev = pCert;
    }
    return pCert;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/x509", DeleteCertificate);

unsigned int MEDIUS_X509_SECTION(NotSameX509Name) NotSameX509Name(X509NAME *a, X509NAME *b)
{
    return memcmp(a, b, 0x10);
}

TBSCERTIFICATE *MEDIUS_X509_SECTION(FindCertificate) FindCertificate(X509NAME *pName)
{
    TBSCERTIFICATE *p;
    p = gpRootCerts;
    while (p != 0) {
        if (NotSameX509Name(&p->name, pName) == 0) {
            return p;
        }
        p = p->next;
        if (p == gpRootCerts) break;
    }
    p = gpInterMediateCerts;
    while (p != 0) {
        if (NotSameX509Name(&p->name, pName) == 0) {
            return p;
        }
        p = p->next;
        if (p == gpInterMediateCerts) break;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/x509", GetASN1Item);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/x509", CreateCertificate);

void MEDIUS_X509_SECTION(DestroyCertificate) DestroyCertificate(TBSCERTIFICATE *pCert)
{
    if (pCert != 0 && pCert->pFreeFunc != 0) {
        pCert->pFreeFunc(pCert);
        if (pCert == gpScertRootCert) {
            gpScertRootCert = 0;
        }
    }
}

void MEDIUS_X509_SECTION(CleanupCertificates) CleanupCertificates(void)
{
    TBSCERTIFICATE *p;
    while ((p = gpInterMediateCerts) != 0) {
        DeleteCertificate(p);
        DestroyCertificate(p);
    }
    while ((p = gpRootCerts) != 0) {
        DeleteCertificate(p);
        DestroyCertificate(p);
    }
    gpScertRootCert = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/x509", ParseCertificate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/x509", ParseTBSCertificate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/x509", ParseX509Name);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/x509", ParseUTCTime);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/x509", ParseGENTime);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/x509", VerifySignature);

unsigned int MEDIUS_X509_SECTION(GetCertificatePubKeyLen) GetCertificatePubKeyLen(TBSCERTIFICATE *pCert)
{
    return pCert->pubKeyLen;
}

unsigned int MEDIUS_X509_SECTION(EncryptByCertificate) EncryptByCertificate(TBSCERTIFICATE *pCert, unsigned char *pData, unsigned int nDataSize)
{
    if (nDataSize != pCert->pubKeyLen) {
        __assert(mediusX509SourceFile, 0x611, mediusX509AssertPubKeyLen);
        if (nDataSize != pCert->pubKeyLen) {
            return 0;
        }
    }
    RSA2048Encrypt(pCert->signature - pCert->pubKeyLen, pCert->pubKeyLen, pCert->pubExp, pData, nDataSize);
    return nDataSize;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/x509", AuthenticateCertificate);
