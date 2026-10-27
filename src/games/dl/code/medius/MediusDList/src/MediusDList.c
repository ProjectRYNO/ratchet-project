#include "common.h"
#include "../../rt_util/rt_pack.h"

#define MEDIUS_DLIST_SECTION(name) __attribute__((section(".medius_dlist_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dlist_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef int MediusErrorCode;
typedef int MediusBool;
typedef int MediusCallbackStatus;
typedef unsigned int MediusTransactionId;
typedef void (*MediusDListActionCallback)();
typedef struct MediusDType_ MediusDType;

typedef struct {
    /* 0x00 */ MediusCallbackStatus error;
    /* 0x04 */ int exceptExtent;
    /* 0x08 */ unsigned int retryTimeout;
} MediusExceptionEvent;

typedef struct {
    /* 0x00 */ RT_PACK_BUFFER buffer;
    /* 0x14 */ RT_PACK_BUFFER save;
    /* 0x28 */ unsigned char version;
    /* 0x2c */ unsigned int length;
    /* 0x30 */ unsigned char transactionState;
    /* 0x34 */ MediusTransactionId transactionId;
    /* 0x38 */ unsigned int clientContextId;
    /* 0x3c */ MediusCallbackStatus status;
    /* 0x40 */ MediusExceptionEvent exceptionEvent;
} MediusMessage;

typedef struct {
    MediusErrorCode (*constructIn)(MediusMessage *, void *);
} MediusMessageInterface;

typedef struct {
    /* 0x00 */ MediusDListActionCallback pUserCallback;
    /* 0x04 */ void *pUserData;
    /* 0x08 */ MediusDType *pUserType;
    /* 0x0c */ unsigned int fieldMask;
    /* 0x10 */ int serviceLevel;
} MediusDInterestCallback;

typedef struct {
    /* 0x00 */ int listId;
    /* 0x04 */ int pendingRequestId;
    /* 0x08 */ MediusTransactionId pendingTransactionId;
    /* 0x0c */ unsigned int instanceId;
    /* 0x10 */ unsigned int relationId;
    /* 0x14 */ int filterId;
    /* 0x18 */ MediusDListActionCallback pUserCallback;
    /* 0x1c */ void *pUserData;
    /* 0x20 */ MediusDType *pRowType;
    /* 0x24 */ unsigned int serviceLevel : 4;
    /* 0x28 */ MediusDInterestCallback *pInterestCallback;
    /* 0x2c */ void *pList;
} MediusDListSubscription;

// MediusDList interest id per list id (0x001B7908).
extern int mediusDListInterestIds[2];
// MediusDList subscription table, 32 entries of 0x30 (0x001B7930).
extern MediusDListSubscription mediusDListSubscriptions[32];
extern MediusMessageInterface MediusMessage_I;

void *memset(void *, int, unsigned int);
int rt_parse_reg_parser(int, int, void *);
void ParseMsg_(MediusMessage *pMsg);
void DestroyPlayerListMetaType(void);
void MediusDListCleanUpSubscriptions(void);
void ErrorEvent_(MediusDListSubscription *pSubscription, MediusMessage *pMsg, MediusCallbackStatus error, int extent, unsigned int retryTimeout);
int CallbackDListResponseHandler_(int connectionIndex, int worldId, int sourceClientIndex, void *pMsgData);
typedef void MediusDMetaType;
// MediusDList per-list player list meta types (0x001B7910).
extern MediusDMetaType *mediusDListMetaTypes[2];
// MediusDList player interest callback record (0x001B7918).
extern MediusDInterestCallback mediusDListPlayerInterestCallback;
MediusDMetaType *GetMediusDPlayerListMetaType(void);
MediusErrorCode RegisterCallbacks_(void);
MediusErrorCode SendDRequest_(MediusDListSubscription *pSubscription, int requestId, MediusTransactionId *pTransactionId);
MediusErrorCode SendSubscription_(MediusDListSubscription *pSubscription, MediusTransactionId *pTransactionId);
void FreeSubscription_(MediusDListSubscription *pSubscription);
typedef struct {
    unsigned int (*getMask)(MediusDType *);
} MediusDTypeInterface;
extern MediusDTypeInterface MediusDType_I;
MediusBool SuscriptionIsValid_(MediusDListSubscription *pSubscription);


unsigned int MEDIUS_DLIST_SECTION(GetNextInstanceId_) GetNextInstanceId_(void)
{
    int i;
    for (i = 0; i < 32; i++) {
        if (mediusDListSubscriptions[i].pUserCallback == 0) {
            return i;
        }
    }
    return 32;
}

MediusBool MEDIUS_DLIST_SECTION(SuscriptionIsValid_) SuscriptionIsValid_(MediusDListSubscription *pSubscription)
{
    if (pSubscription == 0) {
        return 0;
    }
    if (pSubscription < mediusDListSubscriptions && pSubscription > &mediusDListSubscriptions[32]) {
        return 0;
    }
    if (pSubscription->pUserCallback == 0) {
        return 0;
    }
    return (unsigned int)pSubscription->listId < 2;
}

void MEDIUS_DLIST_SECTION(MediusDListCleanUpSubscriptions) MediusDListCleanUpSubscriptions(void)
{
    MediusExceptionEvent event;
    MediusDListSubscription *pSubscription;
    int i;
    event.error = -937;
    event.exceptExtent = 200;
    event.retryTimeout = 0;
    pSubscription = mediusDListSubscriptions;
    for (i = 31; i >= 0; i--) {
        if (pSubscription->pUserCallback != 0) {
            pSubscription->pUserCallback(1, event.error, pSubscription->pendingTransactionId, &event, 0, 0, 0, pSubscription->pUserData);
            memset(pSubscription, 0, 0x30);
        }
        pSubscription++;
    }
}

MediusErrorCode MEDIUS_DLIST_SECTION(RegisterCallbacks_) RegisterCallbacks_(void)
{
    MediusErrorCode result = -1;
    if (rt_parse_reg_parser(0x22, 4, CallbackDListResponseHandler_) == 0) {
        result = 0;
    }
    return result;
}

MediusErrorCode MEDIUS_DLIST_SECTION(MediusDListInit) MediusDListInit(void)
{
    memset(mediusDListInterestIds, 0, 8);
    mediusDListInterestIds[0] = 0;
    mediusDListInterestIds[1] = 0;
    memset(mediusDListMetaTypes, 0, 8);
    mediusDListMetaTypes[0] = GetMediusDPlayerListMetaType();
    mediusDListMetaTypes[1] = GetMediusDPlayerListMetaType();
    memset(&mediusDListPlayerInterestCallback, 0, 0x14);
    return RegisterCallbacks_();
}

void MEDIUS_DLIST_SECTION(MediusDListCleanUp) MediusDListCleanUp(void)
{
    DestroyPlayerListMetaType();
    MediusDListCleanUpSubscriptions();
}

int MEDIUS_DLIST_SECTION(MediusGetInterestId) MediusGetInterestId(unsigned int id)
{
    int result = 1;
    if (id < 2) {
        result = mediusDListInterestIds[id];
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDList", SendSubscription_);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDList", subscribe);

unsigned int MEDIUS_DLIST_SECTION(NextSubscriptionId_) NextSubscriptionId_(unsigned int subscriptionMask, unsigned int lastInstanceId)
{
    int i;
    for (i = lastInstanceId; i < 32; i++) {
        if (mediusDListSubscriptions[i].pUserCallback != 0 && (subscriptionMask & (1 << i))) {
            return i;
        }
    }
    return 32;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDList", SendDRequest_);

MediusErrorCode MEDIUS_DLIST_SECTION(unsubscribe) unsubscribe(MediusDListSubscription *pSubscription, MediusTransactionId *pTransactionId)
{
    MediusErrorCode result;
    if (!SuscriptionIsValid_(pSubscription)) {
        return -21;
    }
    result = SendDRequest_(pSubscription, 2, pTransactionId);
    if (result == 0) {
        pSubscription->pendingRequestId = 2;
    }
    return result;
}

MediusErrorCode MEDIUS_DLIST_SECTION(refresh) refresh(MediusDListSubscription *pSubscription, MediusTransactionId *pTransactionId)
{
    MediusErrorCode result;
    if (!SuscriptionIsValid_(pSubscription)) {
        return -21;
    }
    result = SendDRequest_(pSubscription, 3, pTransactionId);
    if (result == 0) {
        pSubscription->pendingRequestId = 1;
    }
    return result;
}

MediusErrorCode MEDIUS_DLIST_SECTION(setLevel) setLevel(MediusDListSubscription *pSubscription, int level, MediusTransactionId *pTransactionId)
{
    MediusErrorCode result;
    if (!SuscriptionIsValid_(pSubscription)) {
        return -21;
    }
    if (pSubscription->serviceLevel == level) {
        return 0;
    }
    pSubscription->serviceLevel = level;
    if ((unsigned int)level < 3) {
        pSubscription->pList = 0;
    }
    result = SendSubscription_(pSubscription, pTransactionId);
    if (result == 0) {
        pSubscription->pendingRequestId = 1;
    }
    return result;
}

MediusErrorCode MEDIUS_DLIST_SECTION(setInterestCB) setInterestCB(MediusDInterestCallback **ppInterestCallback, int interestId, MediusDType *pType, int level, MediusDListActionCallback pAssocCallback, void *pAssocData)
{
    MediusErrorCode result = -21;
    if (interestId == 0 && pAssocCallback != 0 && pType != 0 && ppInterestCallback != 0) {
        mediusDListPlayerInterestCallback.pUserCallback = pAssocCallback;
        mediusDListPlayerInterestCallback.pUserData = pAssocData;
        mediusDListPlayerInterestCallback.pUserType = pType;
        mediusDListPlayerInterestCallback.serviceLevel = level;
        mediusDListPlayerInterestCallback.fieldMask = MediusDType_I.getMask(pType);
        *ppInterestCallback = &mediusDListPlayerInterestCallback;
        result = 0;
    }
    return result;
}

MediusErrorCode MEDIUS_DLIST_SECTION(associateInterestCB) associateInterestCB(MediusDInterestCallback *pInterestCallback, MediusDListSubscription *pSubscription)
{
    if (!SuscriptionIsValid_(pSubscription)) {
        return -21;
    }
    if (pInterestCallback == 0) {
        return -21;
    }
    pSubscription->pInterestCallback = pInterestCallback;
    return 0;
}

void MEDIUS_DLIST_SECTION(ErrorEvent_) ErrorEvent_(MediusDListSubscription *pSubscription, MediusMessage *pMsg, MediusCallbackStatus error, int extent, unsigned int retryTimeout)
{
    pMsg->exceptionEvent.exceptExtent = extent;
    pMsg->exceptionEvent.retryTimeout = retryTimeout;
    pMsg->exceptionEvent.error = error;
    pSubscription->pUserCallback(1, error, pMsg->transactionId, &pMsg->exceptionEvent, 0, 0, 0, pSubscription->pUserData);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDList", print___dupe2);

void MEDIUS_DLIST_SECTION(Fault_) Fault_(MediusDListSubscription *pSubscription, MediusMessage *pMsg)
{
    ErrorEvent_(pSubscription, pMsg, -966, 300, 0);
}

MediusBool MEDIUS_DLIST_SECTION(ActionValid_) ActionValid_(unsigned int action, unsigned int level)
{
    switch (action) {
    case 3:
    case 6:
        break;
    case 4:
    case 5:
        if (level < 2) {
            goto fail;
        }
        break;
    default:
        goto fail;
    }
    return 1;
fail:
    return 0;
}

MediusBool MEDIUS_DLIST_SECTION(ActionValidI_) ActionValidI_(unsigned int action, unsigned int level)
{
    switch (action) {
    case 3:
        break;
    case 4:
    case 5:
    case 6:
        if (level < 2) {
            goto fail;
        }
        break;
    default:
        goto fail;
    }
    return 1;
fail:
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDList", UpdateDList_);

void MEDIUS_DLIST_SECTION(FreeSubscription_) FreeSubscription_(MediusDListSubscription *pSubscription)
{
    memset(pSubscription, 0, 0x30);
}

void MEDIUS_DLIST_SECTION(ServiceTransaction_) ServiceTransaction_(MediusMessage *pMsg, MediusDListSubscription *pSubscription)
{
    if (pMsg->transactionId != 0 && pMsg->transactionId == pSubscription->pendingTransactionId) {
        if (pSubscription->pendingRequestId == 2) {
            FreeSubscription_(pSubscription);
            pSubscription->pendingRequestId = 0;
        } else {
            pSubscription->pendingRequestId = 0;
        }
        pSubscription->pendingTransactionId = 0;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDList", ParseMsg_);

int MEDIUS_DLIST_SECTION(CallbackDListResponseHandler_) CallbackDListResponseHandler_(int connectionIndex, int worldId, int sourceClientIndex, void *pMsgData)
{
    MediusMessage msg;
    if (MediusMessage_I.constructIn(&msg, pMsgData) != 0) {
        return -1;
    }
    ParseMsg_(&msg);
    return msg.length;
}
