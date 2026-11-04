#include "common.h"

#define MEDIUS_OBJMSG_SECTION(name) __attribute__((section(".medius_objmsg_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_objmsg_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct NetTypeClientInfo {
    unsigned char pad0[0xC];
    int ClientStatus;
    unsigned char pad10[0xC];
    unsigned int SMMigrateOrder;
    int bConnected;
} NetTypeClientInfo;

typedef struct NetConnInfo {
    NetTypeClientInfo *ppClientInfo[256];
    NetTypeClientInfo *pMyClientInfo;
    int MyClientIndex;
} NetConnInfo;

typedef NetConnInfo *HDME;

extern char *gObjectInterfacePtr;
extern int NetIGetSessionMasterClientIndex(int *SessionMasterClientIndex, HDME pConnInfo);
extern int NetClientLeaves(HDME pConnInfo, int ClientIndex);
extern int NetFreeRemoteObject(int);
extern int SendMyClientStatus(HDME pConnInfo, int TargetClientIndex);
extern NetTypeClientInfo *NetGetClientInfo(HDME pConnInfo, int ClientIndex);
extern int AcceptClientIntoGame(HDME pConnInfo, int ClientIndex, int a, int b);

int MEDIUS_OBJMSG_SECTION(DeleteNetObjectPacketHandler) DeleteNetObjectPacketHandler(HDME pConnInfo, int WorldID, int SourceClientIndex, void *pVoid)
{
    NetFreeRemoteObject(*(unsigned short *)pVoid);
    return 2;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", ElectSessionMaster);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", NetObjectFullUpdatePacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", FieldUpdatePacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", FindFreeDataStreamBlock);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", RequestOwnershipPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", GrantOwnershipPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", ReleaseOwnershipPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", DataStreamUpdatePacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", DataStreamEndPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", ArbitrateJoinPacketHandler);

int MEDIUS_OBJMSG_SECTION(SMMigrateOrderPacketHandler) SMMigrateOrderPacketHandler(HDME pConnInfo, int WorldID, int SourceClientIndex, void *pVoid)
{
    int SMIndex;
    NetTypeClientInfo *pInfo;
    SMIndex = 0x100;
    if (pConnInfo == 0) {
        return 4;
    }
    if ((unsigned int)SourceClientIndex >= 0x100) {
        return 4;
    }
    if (pConnInfo != *(HDME *)(gObjectInterfacePtr + 0x138)) {
        return 4;
    }
    pInfo = pConnInfo->pMyClientInfo;
    if (pInfo == 0) {
        return 4;
    }
    if (NetIGetSessionMasterClientIndex(&SMIndex, pConnInfo) != 0) {
        return 4;
    }
    if (SMIndex != 0x100) {
        pInfo->SMMigrateOrder = *(unsigned int *)pVoid;
        SendMyClientStatus(pConnInfo, -1);
    }
    return 4;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", GetFreeNetObjectBlock);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", AcceptClientIntoGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", AcceptClientPacketHandler);

int MEDIUS_OBJMSG_SECTION(ClientLeavesPacketHandler) ClientLeavesPacketHandler(HDME pConnInfo, int WorldID, int ClientIndex, void *pVoid)
{
    NetClientLeaves(pConnInfo, ClientIndex);
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_object/src/DmeObjectMessage", ClientUpdatePacketHandler);
