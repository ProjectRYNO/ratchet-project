#include "common.h"

#define MEDIUS_DMELOCAL_SECTION(name) __attribute__((section(".medius_dmelocal_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dmelocal_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef enum { NetErrorNone = 0, NetErrorBadPointer = 10, NetErrorInvalidArg = 23 } NetErrorCode;

typedef struct {
    unsigned char Addr[8];
} RT_LINKADDRESS;

typedef struct {
    /* 0x00 */ unsigned int SoftwareID;
    /* 0x04 */ char pad04[0xC];
    /* 0x10 */ int Time;
    /* 0x14 */ char pad14[0x4];
    /* 0x18 */ RT_LINKADDRESS CurrentUDPSource;
    /* 0x20 */ char pad20[0x4];
    /* 0x24 */ int bInitialized;
    /* 0x28 */ char Mutex[4];
} DmeGlobals;

typedef struct NetTypeClientInfo NetTypeClientInfo;

typedef struct {
    /* 0x000 */ NetTypeClientInfo *ppClientInfo[256];
    /* 0x400 */ char pad400[0x4];
    /* 0x404 */ int MyClientIndex;
    /* 0x408 */ char pad408[0x8];
    /* 0x410 */ char ServerIP[4];
} NetTypeConnectionInfo;

typedef struct {
    /* 0x000 */ char pad000[0x138];
    /* 0x138 */ NetTypeConnectionInfo *pConnInfo;
} medius_ObjectInterface;

typedef void (*NetTypePeerToPeerHostChangeCallback)(void);

extern DmeGlobals *gDmeGlobals;
extern medius_ObjectInterface *gObjectInterfacePtr;
extern NetTypePeerToPeerHostChangeCallback gpfHostChangeCallback;
extern void *gpHostChangeCallbackData;
/* 0x00167F54: heartbeat interval in milliseconds */
extern unsigned int mediusHeartbeatInterval;
/* 0x001AFD28: local NAT service address */
extern char mediusNatServiceAddr[];
/* 0x001AF918: connection info table indexed by connection ID */
extern NetTypeConnectionInfo *mediusConnInfoTable[4];
/* 0x001AFD80: accumulated NetUpdate connection errors */
extern char mediusNetUpdateErrors[];

void rt_memory_free(void **BlockPtr);
int rt_mutex_unlock(void *mutex, unsigned int *p);
void rt_time_get_local(unsigned int *t);
void *memcpy(void *, const void *, unsigned int);
void rt_comm_linkaddress_toint(void *dst, char *src);
void DmeFree(void **BlockPtr);
NetTypeClientInfo *NetGetClientInfo(NetTypeConnectionInfo *pConnInfo, int ClientIndex);
void *DMEmalloc(unsigned int size);
typedef void (*medius_UdpCb)();
typedef struct {
    /* 0x00 */ char pad00[0x3C];
    /* 0x3C */ medius_UdpCb pfData;
    /* 0x40 */ char pad40[0x1C];
    /* 0x5C */ medius_UdpCb pfConnect;
} medius_UDPInterface;
extern medius_UDPInterface *gUDPInterfacePtr;
typedef struct {
    void *pfMallocCallback;
    void *pfReallocCallback;
    void *pfFreeCallback;
} NetMemoryCallbackParams;
typedef struct {
    void *pUserData;
    unsigned char severity;
    int encoding_type;
    int language_type;
    unsigned char bEndOfMessage;
    unsigned short msg_len;
    unsigned char *p_msg;
    void *pUserCallbackData;
} medius_SystemMessage;
typedef struct {
    /* 0x00 */ int bDefaultSet;
    /* 0x04 */ char pad04[0x1C];
} NetResolveAddrInParams;
extern void (*gpfSystemMessageCallback)(medius_SystemMessage *);
extern void *gpSystemMessageCallbackData;
extern int gbTimebaseEnabled;
/* 0x001AF928: per-client ping info pointers */
extern void *mediusClientPingInfo[256];
/* 0x001B1E28: last parse result per DME connection */
extern int mediusParseResult[];
int rt_memory_allocate_init_zero(void **p, unsigned long size);
int printf(const char *, ...);
int rt_mutex_lock(void *mutex, unsigned int *p);
void *memset(void *, int, unsigned int);
void NetIGetMyExtIP(RT_LINKADDRESS *);
void rt_comm_linkaddress_toext(char *, RT_LINKADDRESS);
int rt_memory_register_callbacks(void *, void *);
int rt_memory_register_another_callback(void *);
int rt_parse_execute(void *, int, int, unsigned char *, unsigned int, void *);
void rt_timebase_get_globaltime(int *);

void MEDIUS_DMELOCAL_SECTION(NetSetHeartbeatInterval) NetSetHeartbeatInterval(unsigned int msecs)
{
    mediusHeartbeatInterval = msecs;
}

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetUseDme) NetUseDme(void)
{
    return NetErrorNone;
}

unsigned int MEDIUS_DMELOCAL_SECTION(GetSoftwareID) GetSoftwareID(void)
{
    return gDmeGlobals->SoftwareID;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetMyIntIP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetMyExtIP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", SendMyClientStatus);

int MEDIUS_DMELOCAL_SECTION(RtMsgToDmeConnectionIndex) RtMsgToDmeConnectionIndex(unsigned int RtMsgConnectionIndex)
{
    return (RtMsgConnectionIndex < 5) + RtMsgConnectionIndex;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetAverageDelayToClient);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetISetSendAggregationInterval);

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetIGetMyClientIndex) NetIGetMyClientIndex(int *ReturnedClientIndex, NetTypeConnectionInfo *pConnInfo)
{
    if (!ReturnedClientIndex) return NetErrorInvalidArg;
    *ReturnedClientIndex = 0x100;
    if (!pConnInfo) return NetErrorInvalidArg;
    *ReturnedClientIndex = pConnInfo->MyClientIndex;
    return NetErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", func_01EA0638);

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetSetPeerToPeerHostChangeCallback) NetSetPeerToPeerHostChangeCallback(NetTypePeerToPeerHostChangeCallback pfPeerToPeerHostChangeCallback, void *pHostChangeCallbackData)
{
    gpfHostChangeCallback = pfPeerToPeerHostChangeCallback;
    gpHostChangeCallbackData = pHostChangeCallbackData;
    return NetErrorNone;
}

void MEDIUS_DMELOCAL_SECTION(NetResetTime) NetResetTime(int NewTime)
{
    gDmeGlobals->Time = NewTime;
}

void *MEDIUS_DMELOCAL_SECTION(DMEmalloc) DMEmalloc(unsigned int size)
{
    void *p = 0;
    if (rt_memory_allocate_init_zero(&p, size)) {
        printf("rt_memory_allocate failed \n");
    }
    return p;
}

void MEDIUS_DMELOCAL_SECTION(DmeFree) DmeFree(void **BlockPtr)
{
    if (*BlockPtr) {
        rt_memory_free(BlockPtr);
    }
}

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetIRegisterMemoryCallbacks) NetIRegisterMemoryCallbacks(NetMemoryCallbackParams *pCallbackParams)
{
    if (!pCallbackParams) return NetErrorInvalidArg;
    if (rt_memory_register_callbacks(pCallbackParams->pfMallocCallback, pCallbackParams->pfFreeCallback)) return 0x16;
    return rt_memory_register_another_callback(pCallbackParams->pfReallocCallback) ? 0x16 : NetErrorNone;
}

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetIGetMyIpAddress) NetIGetMyIpAddress(char *IpAddress)
{
    RT_LINKADDRESS addr;
    if (!IpAddress) return NetErrorInvalidArg;
    NetIGetMyExtIP(&addr);
    rt_comm_linkaddress_toext(IpAddress, addr);
    return NetErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetMyNetAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", RemoteClientConnects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", RemoteClientDisconnects);

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetIGetCurrentUDPSourceBinaryIP) NetIGetCurrentUDPSourceBinaryIP(RT_LINKADDRESS *pLinkAddr)
{
    if (!pLinkAddr) return NetErrorInvalidArg;
    *pLinkAddr = gDmeGlobals->CurrentUDPSource;
    return NetErrorNone;
}

unsigned int MEDIUS_DMELOCAL_SECTION(NetIGetLocalTime) NetIGetLocalTime(void)
{
    unsigned int t;
    rt_time_get_local(&t);
    return t;
}

unsigned int MEDIUS_DMELOCAL_SECTION(NetIGetTime) NetIGetTime(NetTypeConnectionInfo *ConnectionHandle)
{
    if (!*(int *)((char *)ConnectionHandle + 0x4A4)) return 0x2F;
    if (gbTimebaseEnabled) {
        rt_timebase_get_globaltime(&gDmeGlobals->Time);
    }
    return gDmeGlobals->Time;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetConnectStatus);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetValidClientCount);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", func_01EA0D08);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetISendTo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetBitMaskToSendMask);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSendMessageByUDP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSendMessageByTCP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetFragSendCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetISendMessage);

void MEDIUS_DMELOCAL_SECTION(ParseMessageList) ParseMessageList(int WorldID, NetTypeConnectionInfo *pConnInfo, int SourceID, unsigned char *IncomingMessage, unsigned int MessageLength)
{
    int result = rt_parse_execute(pConnInfo, WorldID, SourceID, IncomingMessage, MessageLength, 0);
    if (pConnInfo) {
        mediusParseResult[*(int *)((char *)pConnInfo + 0x46C)] = result;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", RemoteClientDisconnectEvent);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", RemoteClientEvent);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIInitialize);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIEnableUDP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCreateP2PInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", IncomingMessageFunc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", MapMsgClientFailureReason);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", MyClientConnectsPeerToPeer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", MsgClientConnectCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", MsgClientDisconnectCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSetDefaultConnectParams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIConnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetConnect_ClientServerTCP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetConnect_PeerToPeerUDP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSetDefaultHostPeerToPeerParams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIHostPeerToPeer);

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetISetNATServiceAddr) NetISetNATServiceAddr(void *pAddress)
{
    NetErrorCode err = NetErrorInvalidArg;
    if (pAddress) {
        memcpy(mediusNatServiceAddr, pAddress, 0x18);
        err = NetErrorNone;
    }
    return err;
}

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetISetDefaultResolveAddrParams) NetISetDefaultResolveAddrParams(NetResolveAddrInParams *pParams)
{
    NetErrorCode err = NetErrorInvalidArg;
    if (pParams) {
        memset(pParams, 0, 0x20);
        pParams->bDefaultSet = 1;
        err = NetErrorNone;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIResolveAddr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSetIncomingClient);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetISetMyClientReceiveBroadcast);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", func_01EA3B88);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetUpdateAll);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", func_01EA3E00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIUpdate);

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetIGetNetUpdateErrors) NetIGetNetUpdateErrors(void *pNetUpdateErrorStruct)
{
    NetErrorCode err = NetErrorBadPointer;
    if (pNetUpdateErrorStruct) {
        memcpy(pNetUpdateErrorStruct, mediusNetUpdateErrors, 0x28);
        err = NetErrorNone;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIDisconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIClose);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetMapRtError);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetGetClientPingInfo);

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetCleanupClientPingInfoArray) NetCleanupClientPingInfoArray(void)
{
    int i;
    for (i = 0; i < 256; i++) {
        DmeFree(&mediusClientPingInfo[i]);
    }
    return NetErrorNone;
}

NetTypeConnectionInfo *MEDIUS_DMELOCAL_SECTION(NetGetConnInfo) NetGetConnInfo(unsigned int ConnectionID)
{
    if (ConnectionID < 4) {
        return mediusConnInfoTable[ConnectionID];
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCleanupConnInfo);

NetTypeConnectionInfo *MEDIUS_DMELOCAL_SECTION(NetCreateConnInfoBare) NetCreateConnInfoBare(void)
{
    return DMEmalloc(0x4AC);
}

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetSetConnInfo) NetSetConnInfo(unsigned int ConnectionID, NetTypeConnectionInfo *pConnInfo)
{
    if (mediusConnInfoTable[ConnectionID] == 0) {
        mediusConnInfoTable[ConnectionID] = pConnInfo;
        return NetErrorNone;
    }
    return NetErrorInvalidArg;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCreateConnInfo);

void MEDIUS_DMELOCAL_SECTION(NetDestroyConnInfoBare) NetDestroyConnInfoBare(NetTypeConnectionInfo *pConnInfo)
{
    DmeFree((void **)&pConnInfo);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetDestroyConnInfo);

NetTypeClientInfo *MEDIUS_DMELOCAL_SECTION(NetGetClientInfo) NetGetClientInfo(NetTypeConnectionInfo *pConnInfo, int ClientIndex)
{
    if (pConnInfo && (unsigned int)ClientIndex < 0x100) {
        return pConnInfo->ppClientInfo[ClientIndex];
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCreateClientInfo);

void MEDIUS_DMELOCAL_SECTION(NetDestroyClientInfo) NetDestroyClientInfo(NetTypeConnectionInfo *pConnInfo, int ClientIndex)
{
    if (pConnInfo) {
        DmeFree((void **)&pConnInfo->ppClientInfo[ClientIndex]);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetGetServerIpAddress);

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetSetServerIpAddress) NetSetServerIpAddress(NetTypeConnectionInfo *pConnInfo, char *ServerIpAddress)
{
    NetErrorCode err = NetErrorInvalidArg;
    if (ServerIpAddress && pConnInfo) {
        rt_comm_linkaddress_toint(pConnInfo->ServerIP, ServerIpAddress);
        err = NetErrorNone;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCheckForPingTimeouts);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIsPeerToPeerHost);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", func_01EA4B88);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetProcessEchoRequests);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetDisablePingIPs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetProcessP2PDisconnect);

unsigned char MEDIUS_DMELOCAL_SECTION(NetClientIndexToClientIndexPacket) NetClientIndexToClientIndexPacket(int ClientIndex)
{
    return ClientIndex;
}

NetErrorCode MEDIUS_DMELOCAL_SECTION(NetGetNatService) NetGetNatService(void **ppNatService)
{
    if (!ppNatService) return NetErrorInvalidArg;
    *ppNatService = mediusNatServiceAddr;
    return NetErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetConvertTransportFlags);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_connect_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_disconnect_cb);

void MEDIUS_DMELOCAL_SECTION(p2p_system_change_cb) p2p_system_change_cb(int SystemStatus, int bIsReady, void *pUserData)
{
    if (pUserData && *(int *)((char *)pUserData + 0x468) == 2) {
        if (bIsReady) {
            *(int *)((char *)pUserData + 0x450) |= SystemStatus;
        } else {
            *(int *)((char *)pUserData + 0x450) &= ~SystemStatus;
        }
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_host_change_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", udp_resolve_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_peer_update_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_incoming_data_cb);

int MEDIUS_DMELOCAL_SECTION(NetGetMyWorldID) NetGetMyWorldID(void)
{
    if (gObjectInterfacePtr && gObjectInterfacePtr->pConnInfo) {
        return *(int *)((char *)gObjectInterfacePtr->pConnInfo + 0x458);
    }
    return -1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", udp_unconnected_data_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", udp_event_cb);

void MEDIUS_DMELOCAL_SECTION(udp_data_cb) udp_data_cb(int Channel, int Connection, unsigned char *pData, unsigned int nDataSize, unsigned int UserIndex, int bBroadcastData, void *UserData)
{
    if (gUDPInterfacePtr) {
        gUDPInterfacePtr->pfData(Channel, Connection, pData, nDataSize, UserIndex, bBroadcastData, UserData);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_broadcast_update_cb);

void MEDIUS_DMELOCAL_SECTION(MsgClientSystemMessageCallback) MsgClientSystemMessageCallback(void *pUserData, unsigned char severity, int encoding_type, int language_type, int bEndOfMessage, unsigned int msg_len, unsigned char *p_msg)
{
    medius_SystemMessage msg;
    if (gpfSystemMessageCallback) {
        msg.pUserData = pUserData;
        msg.severity = severity;
        msg.encoding_type = encoding_type;
        msg.language_type = language_type;
        msg.bEndOfMessage = bEndOfMessage;
        msg.msg_len = msg_len;
        msg.p_msg = p_msg;
        msg.pUserCallbackData = gpSystemMessageCallbackData;
        gpfSystemMessageCallback(&msg);
    }
}

int MEDIUS_DMELOCAL_SECTION(NetMutexLock) NetMutexLock(void)
{
    if (!gDmeGlobals->bInitialized) return 5;
    return rt_mutex_lock(gDmeGlobals->Mutex, 0);
}

int MEDIUS_DMELOCAL_SECTION(NetMutexUnlock) NetMutexUnlock(void)
{
    return rt_mutex_unlock(gDmeGlobals->Mutex, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", func_01EA5820);
