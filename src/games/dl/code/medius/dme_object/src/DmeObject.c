#include "common.h"

#define MEDIUS_DOBJ_SECTION(name) __attribute__((section(".medius_dobj_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dobj_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct { // 0x14
    /* 0x00 */ unsigned int MaxStructures;
    /* 0x04 */ unsigned int MaxFieldsPerStructure;
    /* 0x08 */ unsigned int MaxObjects;
    /* 0x0C */ unsigned int MaxDataStreamTypes;
    /* 0x10 */ unsigned int MaxDataStreams;
} NetUseObjectsInParams;

typedef struct NetTypeObject_ NetTypeObject;

typedef struct {
    /* 0x00 */ char pad0[8];
    /* 0x08 */ NetTypeObject *Obj;
} NetTypeObjectInfo;

typedef void *HDME;

extern void *gObjectInterfacePtr;

extern void *memset(void *, int, unsigned int);
extern int NetMutexLock(void);
extern int NetMutexUnlock(void);
extern int NetMapRtError(int rtError);
extern void DmeObjectResolveInterface(void);
extern int NetIRegisterObjectStart(void);
extern int NetIRegisterRemoteObjectCallback(int NetStructureIndex, void *ObjectCreationCallback, void *ObjectUpdateCallback, void *ObjectDeletionCallback);
extern char *NetIGetObject(int ObjectIndex);
extern int NetISendObjectFullUpdate(int TargetClientIndex, void *pObject, int flags);
extern int NetISetMyClientObject(int ObjectIndex);
extern int NetIReleaseObjectPrivateOwnership(int ObjectIndex);
extern int NetIGetSessionMasterClientIndex(int *SessionMasterClientIndex, HDME pConnInfo);

int MEDIUS_DOBJ_SECTION(NetRegisterObjectStart) NetRegisterObjectStart(void)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIRegisterObjectStart();
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DOBJ_SECTION(NetSetDefaultNetUseObjectsInParams) NetSetDefaultNetUseObjectsInParams(NetUseObjectsInParams *pInParams)
{
    int result = 0x17;
    if (pInParams) {
        memset(pInParams, 0, sizeof(NetUseObjectsInParams));
        pInParams->MaxStructures = 0x10;
        pInParams->MaxFieldsPerStructure = 0x40;
        pInParams->MaxObjects = 0x1000;
        pInParams->MaxDataStreamTypes = 0x10;
        pInParams->MaxDataStreams = 0x800;
        result = 0;
    }
    return result;
}

int MEDIUS_DOBJ_SECTION(NetUseObjects) NetUseObjects(NetUseObjectsInParams *pInParams)
{
    char *pInterface;
    DmeObjectResolveInterface();
    pInterface = (char *)gObjectInterfacePtr;
    *(unsigned int *)(pInterface + 0xF8) = pInParams->MaxStructures;
    *(unsigned int *)(pInterface + 0xFC) = pInParams->MaxFieldsPerStructure;
    *(unsigned int *)(pInterface + 0x100) = pInParams->MaxObjects;
    *(unsigned int *)(pInterface + 0x108) = pInParams->MaxDataStreamTypes;
    *(unsigned int *)(pInterface + 0x10C) = pInParams->MaxDataStreams;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObject", NetObjectField);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObject", func_01EC93E0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObject", NetCreateObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObject", func_01EC94B8);

int MEDIUS_DOBJ_SECTION(NetGetObject) NetGetObject(NetTypeObject **ObjectPtr, int ObjectIndex)
{
    int err = 0x17;
    char *pInfo;
    if (ObjectPtr) {
        *ObjectPtr = 0;
        err = NetMapRtError(NetMutexLock());
        if (err == 0) {
            pInfo = NetIGetObject(ObjectIndex);
            if (pInfo) *ObjectPtr = (NetTypeObject *)(pInfo + 8);
            err = NetMapRtError(NetMutexUnlock());
        }
    }
    return err;
}

int MEDIUS_DOBJ_SECTION(NetSetMyClientObject) NetSetMyClientObject(int ObjectIndex)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetISetMyClientObject(ObjectIndex);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DOBJ_SECTION(NetReleaseObjectPrivateOwnership) NetReleaseObjectPrivateOwnership(int ObjectIndex)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIReleaseObjectPrivateOwnership(ObjectIndex);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObject", NetRegisterStructure);

int MEDIUS_DOBJ_SECTION(NetRegisterRemoteObjectCallback) NetRegisterRemoteObjectCallback(int NetStructureIndex, void *ObjectCreationCallback, void *ObjectUpdateCallback, void *ObjectDeletionCallback)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIRegisterRemoteObjectCallback(NetStructureIndex, ObjectCreationCallback, ObjectUpdateCallback, ObjectDeletionCallback);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DOBJ_SECTION(NetSendObjectFullUpdate) NetSendObjectFullUpdate(int TargetClientIndex, int ObjectIndex)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetISendObjectFullUpdate(TargetClientIndex, NetIGetObject(ObjectIndex), 0);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DOBJ_SECTION(NetGetSessionMasterClientIndex) NetGetSessionMasterClientIndex(int *SessionMasterClientIndex, HDME pConnInfo)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIGetSessionMasterClientIndex(SessionMasterClientIndex, pConnInfo);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}
