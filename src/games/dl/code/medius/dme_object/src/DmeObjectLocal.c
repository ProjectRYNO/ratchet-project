#include "common.h"

#define MEDIUS_OBJL_SECTION(name) __attribute__((section(".medius_objl_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_objl_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct NetTypeObjectInfo_ {
    char pad0[4];
    int Status;
    unsigned char StructureIndex;
    char pad9[3];
    int OwnerClientIndex;
    int CreatorClientIndex;
    char pad14[0x38];
    struct NetTypeObjectInfo_ *next;
} NetTypeObjectInfo;

typedef struct {
    int pad0;
    unsigned int ClientObjectIndex;
    int NetObjectBufferStart;
    int NetObjectBufferCount;
    unsigned int NetDataStreamStart;
    unsigned int NetDataStreamCount;
} NetTypeClient;

typedef struct {
    unsigned char Status;
    char pad1[3];
    unsigned char BufferComplete;
    char pad5[7];
    int OwnerClientIndex;
} NetTypeDataStream;

typedef struct {
    int bIsSet;
    int ErrorCode;
} NetJoinOutParams;

typedef struct {
    int bDefaultSet;
} NetJoinInParams;

typedef struct {
    char pad0[0x138];
    char *ConnInfo;
    char pad13C[0x1C];
    void (**CreationCallbacks)(int, int);
    void (**UpdateCallbacks)(int, int, int);
    void (**DeletionCallbacks)(int, int);
    char pad164[0x18];
    NetTypeObjectInfo **Objects;
} MediusObjectLocals;

extern char *gObjectInterfacePtr;
// DmeObjectLocal module state: connection info, object callbacks and the object table.
extern MediusObjectLocals mediusObjectLocals;

extern NetTypeDataStream *NetGetStreamChannel(int);
extern NetTypeDataStream *NetIGetDataStream(int);
extern int NetJoin2(NetJoinInParams *);
extern NetTypeClient *NetIGetClient(void *, int);
extern int SendGroupedFieldUpdate(void *, int, int);
extern int NetFreeRemoteObject(int);
extern int NetFreeLocalObject(int);
extern int NetISendMyClientUpdate(void *, int);
extern int RemoveFromObjectUpdateList(int);

int MEDIUS_OBJL_SECTION(InitObjectUpdateList) InitObjectUpdateList(void)
{
    *(int *)(gObjectInterfacePtr + 0x12C) = 0;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", AddToObjectUpdateList);

int MEDIUS_OBJL_SECTION(RemoveFromObjectUpdateList) RemoveFromObjectUpdateList(int ObjectIndex)
{
    NetTypeObjectInfo *obj = NetIGetObject(ObjectIndex);
    NetTypeObjectInfo *cur;
    char *g;
    if (obj) {
        g = gObjectInterfacePtr;
        if (obj == *(NetTypeObjectInfo **)(g + 0x12C)) {
            *(NetTypeObjectInfo **)(g + 0x12C) = obj->next;
        } else {
            for (cur = *(NetTypeObjectInfo **)(g + 0x12C); cur; cur = cur->next) {
                if (obj == cur->next) {
                    cur->next = obj->next;
                    break;
                }
            }
        }
        obj->next = 0;
    }
    return 0;
}

NetTypeObjectInfo *MEDIUS_OBJL_SECTION(NetIGetObject) NetIGetObject(int ObjectIndex)
{
    if ((unsigned int)ObjectIndex < *(unsigned int *)(gObjectInterfacePtr + 0x100)) {
        return mediusObjectLocals.Objects[ObjectIndex];
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetGetMyPersistantObjectCount);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetIGetDataStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetGetStreamChannel);

int MEDIUS_OBJL_SECTION(NetIGetSessionMasterClientIndex) NetIGetSessionMasterClientIndex(int *pIndex, char *pConnInfo)
{
    if (!pIndex) return 0x17;
    *pIndex = 0x100;
    if (!pConnInfo) return 0x17;
    *pIndex = *(int *)(pConnInfo + 0x408);
    return 0;
}

void MEDIUS_OBJL_SECTION(RemoteObjectCreation) RemoteObjectCreation(int ClientIndex, int ObjectIndex)
{
    NetTypeObjectInfo *obj;
    void (*cb)(int, int);
    if ((unsigned int)ClientIndex < 0x100 && (obj = NetIGetObject(ObjectIndex)) != 0
        && (cb = mediusObjectLocals.CreationCallbacks[obj->StructureIndex]) != 0) {
        cb(ClientIndex, ObjectIndex);
    }
}

void MEDIUS_OBJL_SECTION(RemoteObjectUpdate) RemoteObjectUpdate(int ClientIndex, int ObjectIndex, int FieldIndex)
{
    NetTypeObjectInfo *obj;
    void (*cb)(int, int, int);
    if ((unsigned int)FieldIndex < *(unsigned int *)(gObjectInterfacePtr + 0xFC) || FieldIndex == -2 || FieldIndex == -1) {
        if ((obj = NetIGetObject(ObjectIndex)) != 0 && (cb = mediusObjectLocals.UpdateCallbacks[obj->StructureIndex]) != 0) {
            cb(ClientIndex, ObjectIndex, FieldIndex);
        }
    }
}

void MEDIUS_OBJL_SECTION(RemoteObjectDelete) RemoteObjectDelete(int ClientIndex, int ObjectIndex)
{
    NetTypeObjectInfo *obj;
    void (*cb)(int, int);
    if ((unsigned int)ClientIndex < 0x100 && (obj = NetIGetObject(ObjectIndex)) != 0
        && (cb = mediusObjectLocals.DeletionCallbacks[obj->StructureIndex]) != 0) {
        cb(ClientIndex, ObjectIndex);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetFreeRemoteObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetFreeLocalObject);

int MEDIUS_OBJL_SECTION(NetIFreeObject) NetIFreeObject(int ObjectIndex)
{
    char *conn = mediusObjectLocals.ConnInfo;
    NetTypeObjectInfo *obj;
    if (!conn) return 8;
    obj = NetIGetObject(ObjectIndex);
    if (!obj) return 8;
    if (obj->CreatorClientIndex == *(int *)(conn + 0x404)) {
        NetFreeLocalObject(ObjectIndex);
        return 0;
    }
    if (obj->OwnerClientIndex == *(int *)(conn + 0x404)) {
        RemoveFromObjectUpdateList(ObjectIndex);
    }
    NetFreeRemoteObject(ObjectIndex);
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", LocalObjectName2Index);

int MEDIUS_OBJL_SECTION(FindFreeLocalObject) FindFreeLocalObject(void)
{
    char *conn = mediusObjectLocals.ConnInfo;
    NetTypeClient *client;
    NetTypeObjectInfo *obj;
    int i, idx;
    if (!conn) return -1;
    client = NetIGetClient(conn, *(int *)(conn + 0x404));
    if (!client) return -1;
    for (i = 0; i < client->NetObjectBufferCount; ) {
        idx = i + client->NetObjectBufferStart;
        i++;
        obj = NetIGetObject(idx);
        if (obj && obj->Status != 2) return idx;
    }
    return -1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetIFreeAllObjects);

int MEDIUS_OBJL_SECTION(NetIJoin) NetIJoin(NetJoinInParams *pInParams, NetJoinOutParams *pOutParams)
{
    int result;
    if (!pOutParams) return 0x17;
    pOutParams->ErrorCode = 0x1E;
    pOutParams->bIsSet = 1;
    if (!pInParams) {
        pOutParams->ErrorCode = 0x17;
        return 0x17;
    }
    if (!pInParams->bDefaultSet) {
        pOutParams->ErrorCode = 0x26;
        return 0x26;
    }
    result = NetJoin2(pInParams);
    pOutParams->ErrorCode = result;
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetJoin2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetIRequestCreateRemoteNamedObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetICreateObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetIOpenDataStream);

int MEDIUS_OBJL_SECTION(NetIEndDataStream) NetIEndDataStream(int Channel)
{
    char *conn;
    NetTypeDataStream *ds;
    if ((unsigned int)Channel >= *(unsigned int *)(gObjectInterfacePtr + 0x10C)) return 0x17;
    conn = mediusObjectLocals.ConnInfo;
    if (!conn) return 9;
    ds = NetIGetDataStream(Channel);
    if (!ds) return 9;
    if (ds->OwnerClientIndex != *(int *)(conn + 0x404)) return 9;
    ds->BufferComplete = 1;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetIRequestObjectPrivateOwnership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetIReleaseObjectPrivateOwnership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", CheckFieldsForUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", SendGroupedFieldUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetISendObjectFullUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetIAddToDataStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", ElementErrorExceedsThreshold);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", GlobalFieldErrorExceedsThreshold);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetGetDataStreamPacket);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", SendCloseDataStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetIDataStreamBytesFree);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", SendClientDataStreams);

int MEDIUS_OBJL_SECTION(NetISendFieldUpdates) NetISendFieldUpdates(int ObjectIndex)
{
    return SendGroupedFieldUpdate(NetIGetObject(ObjectIndex), 0, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", SendClientNetObjectUpdates);

int MEDIUS_OBJL_SECTION(NetSetSessionMasterClientIndex) NetSetSessionMasterClientIndex(char *pConnInfo, int idx)
{
    int result = 0x17;
    if (pConnInfo) {
        *(int *)(pConnInfo + 0x408) = idx;
        result = 0;
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetCompleteJoin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetFreeAllDataStreams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetILeave);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", MyClientJoins);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetClientJoins);

void MEDIUS_OBJL_SECTION(ReserveNetObjectsAndDataStreamsForClient) ReserveNetObjectsAndDataStreamsForClient(NetTypeClient *ThisClient)
{
    unsigned int i;
    NetTypeDataStream *ds;
    if (ThisClient && ThisClient->NetDataStreamStart < *(unsigned int *)(gObjectInterfacePtr + 0x10C)) {
        for (i = 0; i < ThisClient->NetDataStreamCount; i++) {
            ds = NetIGetDataStream(i + ThisClient->NetDataStreamStart);
            if (ds) ds->Status = 1;
        }
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", DmeObjectResolveInterface);

int MEDIUS_OBJL_SECTION(NetISetMyClientObject) NetISetMyClientObject(int ObjectIndex)
{
    char *conn = mediusObjectLocals.ConnInfo;
    NetTypeClient *client;
    NetTypeObjectInfo *obj;
    if (!conn) return 8;
    client = NetIGetClient(conn, *(int *)(conn + 0x404));
    if (!client) return 0x15;
    obj = NetIGetObject(ObjectIndex);
    if (!obj) return 0x1E;
    if (obj->OwnerClientIndex != *(int *)(conn + 0x404)) return 8;
    client->ClientObjectIndex = ObjectIndex;
    NetISendMyClientUpdate(conn, -1);
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetClientLeaves);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", NetFindNextSessionMaster);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", CreateGlobalObjectInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectLocal", DestroyGlobalObjectInfo);
