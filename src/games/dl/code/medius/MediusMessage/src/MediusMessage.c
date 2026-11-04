#include "common.h"
#include "../../rt_util/rt_pack.h"

#define MEDIUS_MMSG_SECTION(name) __attribute__((section(".medius_mmsg_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_mmsg_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef unsigned int MediusTransactionId;

typedef struct { // 0x18
    /* 0x00 */ int worldId;
    /* 0x04 */ int sourceClientIndex;
    /* 0x08 */ int msgClass;
    /* 0x0C */ int msgType;
    /* 0x10 */ MediusTransactionId transactionId;
    /* 0x14 */ unsigned int clientContextId;
} MediusMessageDest;

typedef struct { // 0xC
    /* 0x00 */ int status;
    /* 0x04 */ int exceptExtent;
    /* 0x08 */ unsigned int retryTimeout;
} MediusExceptionEvent;

typedef struct MediusMessage_ { // 0x4C
    /* 0x00 */ RT_PACK_BUFFER buffer;
    /* 0x14 */ RT_PACK_BUFFER save;
    /* 0x28 */ unsigned char version;
    /* 0x2C */ unsigned int length;
    /* 0x30 */ unsigned char transactionState;
    /* 0x34 */ MediusTransactionId transactionId;
    /* 0x38 */ unsigned int clientContextId;
    /* 0x3C */ int status;
    /* 0x40 */ MediusExceptionEvent exceptionEvent;
} MediusMessage;

int _packTransaction(int mode, RT_PACK_BUFFER *pBuffer, MediusMessage *pMsg);

MediusMessageDest MEDIUS_MMSG_SECTION(MediusMessageDestCreate) MediusMessageDestCreate(int worldId, int sourceClientIndex, int msgClass, int msgType, MediusTransactionId transactionId, unsigned int clientContextId)
{
    MediusMessageDest dest;
    dest.worldId = worldId;
    dest.sourceClientIndex = sourceClientIndex;
    dest.msgClass = msgClass;
    dest.msgType = msgType;
    dest.transactionId = transactionId;
    dest.clientContextId = clientContextId;
    return dest;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusMessage/src/MediusMessage", _getTransactionId);

int MEDIUS_MMSG_SECTION(_packTransaction) _packTransaction(int mode, RT_PACK_BUFFER *pBuffer, MediusMessage *pMsg)
{
    unsigned char *pState = &pMsg->transactionState;
    if (!rt_pack_1byte(mode, pBuffer, (char *)pState)) return -0xA;
    if (*pState) {
        if (!rt_pack_anything(mode, pBuffer, &pMsg->transactionId, 4)) return -0x15;
        if (!rt_pack_anything(mode, pBuffer, &pMsg->clientContextId, 4)) return -0x15;
        if (*pState >= 2) {
            if (!rt_pack_anything(mode, pBuffer, &pMsg->status, 4)) return -0x15;
        }
        if (pMsg->transactionState == 4) {
            if (!rt_pack_anything(mode, pBuffer, &pMsg->exceptionEvent.exceptExtent, 4)
                || !rt_pack_anything(mode, pBuffer, &pMsg->exceptionEvent.status, 4)
                || !rt_pack_anything(mode, pBuffer, &pMsg->exceptionEvent.retryTimeout, 4)) return -0x15;
        }
    }
    if (mode == RT_UNPACK) {
        pBuffer->end = pBuffer->cursor + pMsg->length;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusMessage/src/MediusMessage", _packMessage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusMessage/src/MediusMessage", constructIn);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusMessage/src/MediusMessage", constructOut);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusMessage/src/MediusMessage", send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusMessage/src/MediusMessage", sendResponse);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusMessage/src/MediusMessage", sendRequest);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusMessage/src/MediusMessage", sendResult);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusMessage/src/MediusMessage", sendException);

unsigned int MEDIUS_MMSG_SECTION(getObjectSize___dupe3) getObjectSize___dupe3(unsigned int size)
{
    return size + 0x98;
}
