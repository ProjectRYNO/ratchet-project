#include "common.h"
#include "OID.h"

#define MEDIUS_OID_SECTION(name) __attribute__((section(".medius_oid_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_oid_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern int memcmp(const void *a, const void *b, unsigned int size);
extern OIDDATA gOIDs[];

OID MEDIUS_OID_SECTION(GetOID) GetOID(unsigned char *pMsg, unsigned int nMsgSize)
{
    OIDDATA *pEntry;

    for (pEntry = gOIDs; pEntry->oid != OID_UNKNOWN; pEntry++) {
        if (nMsgSize == pEntry->nSize && !memcmp(pMsg, pEntry->data, nMsgSize)) return pEntry->oid;
    }
    return OID_UNKNOWN;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_cert/src/OID", func_01EE15D0);
