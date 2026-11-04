#include "common.h"
#include "../../rt_util/rt_pack.h"

#define MEDIUS_DLSHARED_SECTION(name) __attribute__((section(".medius_dlshared_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dlshared_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef enum { MediusErrorNone = 0, MediusErrorInvalidParameter = -21 } MediusErrorCode;
typedef enum { MediusSuccess = 0 } MediusCallbackStatus;

// Pack buffer at offset 0 (the rest of the message is not used here).
typedef struct {
    RT_PACK_BUFFER buffer;
} MediusMessage;

// Layouts from the retail pack offsets; member names from Ghidra's debug-info decompile.
typedef struct {
    /* 0x00 */ MediusCallbackStatus error;
    /* 0x04 */ unsigned int fieldMask;
    /* 0x08 */ unsigned int timeStamp;
    /* 0x0C */ unsigned int assocMask;
    /* 0x10 */ unsigned int subscriptionMask;
    /* 0x14 */ char action;
    /* 0x15 */ char numRows;
} MediusDListUpdate;

typedef struct {
    /* 0x00 */ unsigned int header;
    /* 0x04 */ unsigned short listId;
    /* 0x08 */ unsigned int instanceId;
    /* 0x0C */ char request;
} MediusDListRequest;

MediusErrorCode MEDIUS_DLSHARED_SECTION(MediusDListUpdatePack) MediusDListUpdatePack(int mode, MediusMessage *msg, MediusDListUpdate *update)
{
    if (!rt_pack_anything(mode, &msg->buffer, update, 4)) return MediusErrorInvalidParameter;
    if (update->error != MediusSuccess) return MediusErrorNone;
    if (!rt_pack_anything(mode, &msg->buffer, &update->fieldMask, 4)
        || !rt_pack_anything(mode, &msg->buffer, &update->timeStamp, 4)
        || !rt_pack_anything(mode, &msg->buffer, &update->assocMask, 4)
        || !rt_pack_anything(mode, &msg->buffer, &update->subscriptionMask, 4)
        || !rt_pack_1byte(mode, &msg->buffer, &update->action))
        return MediusErrorInvalidParameter;
    return rt_pack_1byte(mode, &msg->buffer, &update->numRows) ? MediusErrorNone : MediusErrorInvalidParameter;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDList_shared", MediusDListSubscribePack);

MediusErrorCode MEDIUS_DLSHARED_SECTION(MediusDListRequestPack) MediusDListRequestPack(int mode, MediusMessage *msg, MediusDListRequest *pRequest)
{
    if (!rt_pack_anything(mode, &msg->buffer, pRequest, 4)
        || !rt_pack_anything(mode, &msg->buffer, &pRequest->listId, 2)
        || !rt_pack_anything(mode, &msg->buffer, &pRequest->instanceId, 4))
        return MediusErrorInvalidParameter;
    return rt_pack_1byte(mode, &msg->buffer, &pRequest->request) ? MediusErrorNone : MediusErrorInvalidParameter;
}
