#include "common.h"

#define MEDIUS_DME_SECTION(name) __attribute__((section(".medius_dme_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dme_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct {
    int bDefaultSet;
    char pad4[0x18];
    int SessionMasterStatus;
    char pad20[0x28];
} NetJoinInParams;

typedef struct {
    char pad0[0xC];
    int GlobalBufferPoolSize;
} NetUsePeerToPeerInParams;

extern void *memset(void *, int, unsigned int);
extern int sprintf(char *, const char *, ...);
extern int NetMutexLock(void);
extern int NetMutexUnlock(void);
extern int NetMapRtError(int rtError);
extern int NetIRegisterMemoryCallbacks(void *);
extern unsigned int NetIGetLocalTime(void);
extern unsigned int NetIGetTime(void *);
extern int NetIDisconnect(void *);
extern int NetIGetMyIpAddress(char *);
extern int NetIGetNetUpdateErrors(void *);
extern int NetISetDefaultResolveAddrParams(void *);

typedef struct {
    /* 0x00 */ char pad00[0x1C];
    /* 0x1C */ int (*pfLeave)(void *pLeaveParams);
    /* 0x20 */ char pad20[0xC];
    /* 0x2C */ int (*pfJoin)(void *pInParams, void *pOutParams);
} medius_DmeObjectInterface;
typedef struct {
    /* 0x00 */ char pad00[0x2C];
    /* 0x2C */ int (*pfJoinChannel)(void *pConnInfo, void *pParams);
    /* 0x30 */ char pad30[0x4];
    /* 0x34 */ int (*pfGetChannelInfo)(void *pConnInfo, unsigned int ChannelNum, void *pChannelInfo);
    /* 0x38 */ char pad38[0x4];
    /* 0x3C */ int (*pfEndRecording)(void *pConnInfo, void *pParams);
    /* 0x40 */ int (*pfGetCurrentChannelState)(void *pConnInfo, void *pState);
} medius_DmeStreamMediaInterface;
typedef struct {
    /* 0x000 */ char pad000[0x158];
    /* 0x158 */ int bDisableTimebase;
} NetConnectInParams;
typedef struct {
    /* 0x000 */ char pad000[0xB4];
    /* 0x0B4 */ int bDisableTimebase;
} NetHostPeerToPeerInParams;
typedef struct {
    /* 0x000 */ char pad000[0x460];
    /* 0x460 */ int MaxClients;
} NetTypeConnectionInfo;
typedef struct {
    /* 0x00 */ NetTypeConnectionInfo *ConnectionHandle;
    /* 0x04 */ char TransportFlags;
    /* 0x08 */ int MessageType;
    /* 0x0C */ int TargetClient;
    /* 0x10 */ char pad10[0x24];
    /* 0x34 */ int max_id;
    /* 0x38 */ int MessageLength;
    /* 0x3C */ unsigned char *MessageData;
} NetSendMessageInParams;
typedef struct {
    char pad00[0x30];
} NetSendMessageOutParams;
typedef struct {
    /* 0x00 */ int bDefaultSet;
    /* 0x04 */ int CharacterEncodingType;
    /* 0x08 */ int LanguageType;
    /* 0x0C */ int ApplicationID;
    /* 0x10 */ char pad10[0x4C];
    /* 0x5C */ void *pApplicationKeyPair;
    /* 0x60 */ int ConnectivityType;
    /* 0x64 */ char pad64[0x8];
} NetInitializeInParams;
typedef struct {
    /* 0x00 */ char pad00[0x20];
    /* 0x20 */ unsigned int MSecsWhenAquired;
    /* 0x24 */ char pad24[0xC];
} RT_TIME_DATE;
extern medius_DmeObjectInterface *gObjectInterfacePtr;
extern medius_DmeStreamMediaInterface *gStreamMediaInterfacePtr;
extern int gbTimebaseEnabled;
extern int NetIUpdate(void);
extern int NetIGetConnectStatus(void *, void *);
extern int NetIGetMyClientIndex(void *, void *);
extern int NetIGetAverageDelayToClient(void *, void *);
extern int NetIRegisterApplicationMessage(void *, void *);
extern int NetIResolveAddr(void *, void *);
extern int NetISetSendAggregationInterval(void *, unsigned int, unsigned int);
extern int NetIConnect(NetConnectInParams *, void *);
extern int NetIHostPeerToPeer(NetHostPeerToPeerInParams *, void *);
extern int NetISendMessage(NetSendMessageInParams *, NetSendMessageOutParams *, int);
extern void rt_time_get_gmtime(RT_TIME_DATE *);
extern void seedMT(unsigned int);

int MEDIUS_DME_SECTION(NetGetClientVersion) NetGetClientVersion(char *ReturnedVersion)
{
    int result = 0x17;

    if (ReturnedVersion) {
        sprintf(ReturnedVersion, "%d.%02d.%04d", 2, 10, 0x68);
        result = 0;
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", func_01E9DDC8);

int MEDIUS_DME_SECTION(NetSetDefaultInitializeParams) NetSetDefaultInitializeParams(NetInitializeInParams *pParams)
{
    RT_TIME_DATE td;
    int result = 0x17;
    if (pParams) {
        memset(pParams, 0, 0x6C);
        rt_time_get_gmtime(&td);
        seedMT(td.MSecsWhenAquired);
        pParams->bDefaultSet = 1;
        pParams->LanguageType = 1;
        pParams->ConnectivityType = 0;
        pParams->pApplicationKeyPair = 0;
        pParams->CharacterEncodingType = 0;
        pParams->ApplicationID = -1;
        result = 0;
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", NetInitialize);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", NetClose);

int MEDIUS_DME_SECTION(NetGetAverageDelayToClient) NetGetAverageDelayToClient(void *pConnInfo, void *pParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIGetAverageDelayToClient(pConnInfo, pParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetSetSendAggregationInterval) NetSetSendAggregationInterval(void *pConnInfo, unsigned int ClientTimeMSecs, unsigned int ServerTimeMSecs)
{
    int result;
    int err = NetMapRtError(NetMutexLock());
    if (err != 0) return err;
    result = NetISetSendAggregationInterval(pConnInfo, ClientTimeMSecs, ServerTimeMSecs);
    err = NetMapRtError(NetMutexUnlock());
    if (err != 0) return err;
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", func_01E9E130);

int MEDIUS_DME_SECTION(NetRegisterApplicationMessage) NetRegisterApplicationMessage(void *pConnInfo, void *pParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIRegisterApplicationMessage(pConnInfo, pParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetSendMessage) NetSendMessage(char TransportFlags, NetTypeConnectionInfo *pConnInfo, int TargetClientIndex, int MessageClass, int MessageType, int MessageLength, unsigned char *MessageData)
{
    NetSendMessageInParams in;
    NetSendMessageOutParams out;
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result;
        memset(&in, 0, 0x40);
        in.TransportFlags = TransportFlags;
        in.TargetClient = TargetClientIndex;
        in.max_id = pConnInfo->MaxClients;
        in.MessageType = MessageType;
        in.MessageLength = MessageLength;
        in.MessageData = MessageData;
        in.ConnectionHandle = pConnInfo;
        result = NetISendMessage(&in, &out, MessageClass);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetSendApplicationMessage) NetSendApplicationMessage(char TransportFlags, NetTypeConnectionInfo *pConnInfo, int TargetClientIndex, int MessageType, int MessageLength, unsigned char *MessageData)
{
    NetSendMessageInParams in;
    NetSendMessageOutParams out;
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result;
        memset(&in, 0, 0x40);
        in.TransportFlags = TransportFlags;
        in.TargetClient = TargetClientIndex;
        in.max_id = pConnInfo->MaxClients;
        in.MessageType = MessageType;
        in.MessageLength = MessageLength;
        in.MessageData = MessageData;
        in.ConnectionHandle = pConnInfo;
        result = NetISendMessage(&in, &out, 2);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", func_01E9E338);

int MEDIUS_DME_SECTION(NetRegisterMemoryCallbacks) NetRegisterMemoryCallbacks(void *pParams)
{
    int result = NetIRegisterMemoryCallbacks(pParams);
    return result;
}

int MEDIUS_DME_SECTION(NetConnect) NetConnect(NetConnectInParams *pInParams, void *pOutParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIConnect(pInParams, pOutParams);
        if (pInParams->bDisableTimebase && result) {
            gbTimebaseEnabled = 0;
        }
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetSetDefaultJoinParams) NetSetDefaultJoinParams(NetJoinInParams *pParams)
{
    int result = 0x17;
    if (pParams) {
        memset(pParams, 0, 0x48);
        pParams->SessionMasterStatus = 2;
        pParams->bDefaultSet = 1;
        result = 0;
    }
    return result;
}

int MEDIUS_DME_SECTION(NetHostPeerToPeer) NetHostPeerToPeer(NetHostPeerToPeerInParams *pInParams, void *pOutParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIHostPeerToPeer(pInParams, pOutParams);
        if (pInParams->bDisableTimebase && result) {
            gbTimebaseEnabled = 0;
        }
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetSetDefaultResolveAddrParams) NetSetDefaultResolveAddrParams(void *pParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetISetDefaultResolveAddrParams(pParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetResolveAddr) NetResolveAddr(void *pConnInfo, void *pParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIResolveAddr(pConnInfo, pParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", func_01E9E558);

int MEDIUS_DME_SECTION(NetGetMyIpAddress) NetGetMyIpAddress(char *ReturnedIpAddress)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIGetMyIpAddress(ReturnedIpAddress);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetGetMyClientIndex) NetGetMyClientIndex(void *pConnInfo, void *pParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIGetMyClientIndex(pConnInfo, pParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetGetLocalTime) NetGetLocalTime(unsigned int *LocalTime)
{
    if (!LocalTime) return 0x17;
    *LocalTime = NetIGetLocalTime();
    return 0;
}

int MEDIUS_DME_SECTION(NetGetTime) NetGetTime(void *ConnectionHandle, unsigned int *GlobalTime)
{
    if (!GlobalTime) return 0x17;
    if (!ConnectionHandle) return 0x17;
    *GlobalTime = NetIGetTime(ConnectionHandle);
    return 0;
}

int MEDIUS_DME_SECTION(NetGetConnectStatus) NetGetConnectStatus(void *pConnInfo, void *pParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIGetConnectStatus(pConnInfo, pParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", NetSetDefaultStreamMediaParams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", func_01E9E790);

int MEDIUS_DME_SECTION(NetUpdate) NetUpdate(void)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIUpdate();
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetGetNetUpdateErrors) NetGetNetUpdateErrors(void *pNetUpdateErrorStruct)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIGetNetUpdateErrors(pNetUpdateErrorStruct);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetLeave) NetLeave(void *pLeaveParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = gObjectInterfacePtr->pfLeave(pLeaveParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetSetDefaultDisconnectParams) NetSetDefaultDisconnectParams(void *pDisconnectParams)
{
    int result = 0x17;
    if (pDisconnectParams) {
        memset(pDisconnectParams, 0, 0x10);
        result = 0;
    }
    return result;
}

int MEDIUS_DME_SECTION(NetDisconnect) NetDisconnect(void *pDisconnectParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = NetIDisconnect(pDisconnectParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetStreamMediaJoinChannel) NetStreamMediaJoinChannel(void *pConnInfo, void *pParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = gStreamMediaInterfacePtr->pfJoinChannel(pConnInfo, pParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", func_01E9E988);

int MEDIUS_DME_SECTION(NetStreamMediaGetChannelInfo) NetStreamMediaGetChannelInfo(void *pConnInfo, unsigned int ChannelNum, void *pChannelInfo)
{
    int result;
    int err = NetMapRtError(NetMutexLock());
    if (err != 0) return err;
    result = gStreamMediaInterfacePtr->pfGetChannelInfo(pConnInfo, ChannelNum, pChannelInfo);
    err = NetMapRtError(NetMutexUnlock());
    if (err != 0) return err;
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", func_01E9EA10);

int MEDIUS_DME_SECTION(NetStreamMediaEndRecording) NetStreamMediaEndRecording(void *pConnInfo, void *pParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = gStreamMediaInterfacePtr->pfEndRecording(pConnInfo, pParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

int MEDIUS_DME_SECTION(NetStreamMediaGetCurrentChannelState) NetStreamMediaGetCurrentChannelState(void *pConnInfo, void *pState)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = gStreamMediaInterfacePtr->pfGetCurrentChannelState(pConnInfo, pState);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", func_01E9EAF8);

int MEDIUS_DME_SECTION(NetJoin) NetJoin(void *pInParams, void *pOutParams)
{
    int err = NetMapRtError(NetMutexLock());
    if (err == 0) {
        int result = gObjectInterfacePtr->pfJoin(pInParams, pOutParams);
        err = NetMapRtError(NetMutexUnlock());
        if (err == 0) err = result;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/Dme", func_01E9EB78);

int MEDIUS_DME_SECTION(NetSetDefaultNetUsePeerToPeerInParams) NetSetDefaultNetUsePeerToPeerInParams(NetUsePeerToPeerInParams *pInParams)
{
    int result = 0x17;
    if (pInParams) {
        memset(pInParams, 0, 0x10);
        pInParams->GlobalBufferPoolSize = 0x10000;
        result = 0;
    }
    return result;
}
