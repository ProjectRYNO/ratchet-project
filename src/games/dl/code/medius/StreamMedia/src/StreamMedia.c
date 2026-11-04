#include "common.h"

#define MEDIUS_SMEDIA_SECTION(name) __attribute__((section(".medius_smedia_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_smedia_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct {
    unsigned int MaxClients;
    int bInUse;
    char pad8[8];
    unsigned int NumChannels;
    unsigned int MaxIncomingAudioStreams;
    char pad18[0x60];
    unsigned char CurrentChannel;
    char pad79[0xF];
    unsigned short *aChannelOwners;
    unsigned short *pPeerIndex;
} NetTypeStreamMediaInfo;

typedef struct {
    char pad0[0x404];
    int MyClientIndex;
    char pad408[0x6C];
    void *pP2P;
    char pad478[0x10];
    NetTypeStreamMediaInfo *pStreamMediaInfo;
} NetTypeConnectionInfo;

extern char *gP2PInterfacePtr;

extern int NetMapRtError(int);
extern void StreamMediaResolveInterface(void);
extern int NetStreamMediaDisconnect(NetTypeConnectionInfo *);
extern int StreamMediaSendHostQuery(NetTypeConnectionInfo *, int);
extern int NetIStreamMediaQuitChannel(NetTypeConnectionInfo *, unsigned int);
extern void NetStreamMediaDestroyInfo(NetTypeConnectionInfo *);
extern NetTypeStreamMediaInfo *NetStreamMediaGetValidInfo(NetTypeConnectionInfo *);

extern int NetStreamMediaSendMyIndexInfo(NetTypeConnectionInfo *, unsigned short, int);
typedef struct {
    NetTypeConnectionInfo *ConnectionHandle;
    unsigned int ChannelNum;
    unsigned int ClientCount;
} NetStreamMediaChannelInfo;

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetIStreamMediaJoinChannel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetIStreamMediaQuitChannel);

int MEDIUS_SMEDIA_SECTION(NetIStreamMediaGetChannelInfo) NetIStreamMediaGetChannelInfo(NetTypeConnectionInfo *pConnInfo, unsigned int ChannelNum, NetStreamMediaChannelInfo *pChannelInfo)
{
    unsigned int count[4];
    count[0] = 0;
    if (!pChannelInfo) return 0x17;
    pChannelInfo->ConnectionHandle = pConnInfo;
    pChannelInfo->ChannelNum = ChannelNum;
    pChannelInfo->ClientCount = 0;
    if (!pConnInfo) return 0x17;
    if (!NetStreamMediaGetValidInfo(pConnInfo)) return 0x17;
    {
        int err = NetMapRtError((*(int (**)(void *, unsigned char, unsigned int *))(gP2PInterfacePtr + 0x70))(pConnInfo->pP2P, ChannelNum, count));
        pChannelInfo->ClientCount = count[0];
        return err;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetIStreamMediaGetClientInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetIStreamMediaEndRecording);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetIStreamMediaGetCurrentChannelState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetIStreamMediaSetIgnoreState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaRecordAudio);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaRequestBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaAudioEncodeAndSend);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaGetChannelOwners);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaPlayAudio);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaRecordVideo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaPlayVideo);

void MEDIUS_SMEDIA_SECTION(NetStreamMediaResolveAddrCB) NetStreamMediaResolveAddrCB(void *pData)
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaEnableOnConnection);

int MEDIUS_SMEDIA_SECTION(NetStreamMediaDisableOnConnection) NetStreamMediaDisableOnConnection(NetTypeConnectionInfo *pConnInfo)
{
    NetTypeStreamMediaInfo *info = NetStreamMediaGetValidInfo(pConnInfo);
    if (!info) return 0x17;
    if (info->CurrentChannel != 0xFF) {
        NetIStreamMediaQuitChannel(pConnInfo, info->CurrentChannel);
    }
    info->bInUse = 0;
    NetStreamMediaDestroyInfo(pConnInfo);
    return 0;
}

int MEDIUS_SMEDIA_SECTION(NetStreamMediaHost) NetStreamMediaHost(NetTypeConnectionInfo *pConnInfo, int ClientIndex)
{
    NetTypeStreamMediaInfo *info = NetStreamMediaGetValidInfo(pConnInfo);
    int result = 0x17;
    if (info) {
        result = NetMapRtError((*(int (**)(void *, unsigned short *))(gP2PInterfacePtr + 0x2C))(pConnInfo->pP2P, info->pPeerIndex + ClientIndex));
    }
    return result;
}

int MEDIUS_SMEDIA_SECTION(NetStreamMediaIsEnabledOnConnection) NetStreamMediaIsEnabledOnConnection(NetTypeConnectionInfo *pConnInfo)
{
    return NetStreamMediaGetValidInfo(pConnInfo) != 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", StreamMediaClientInfoPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", StreamMediaHostInfoPacketHandler);

int MEDIUS_SMEDIA_SECTION(StreamMediaIndexInfoPacketHandler) StreamMediaIndexInfoPacketHandler(NetTypeConnectionInfo *pConnInfo, int WorldID, int SourceClientIndex, void *pVoid)
{
    NetTypeStreamMediaInfo *info;
    if (!pConnInfo) return -1;
    if (!pVoid) return -1;
    info = NetStreamMediaGetValidInfo(pConnInfo);
    if (!info) return -1;
    if (((unsigned int *)pVoid)[1] >= info->MaxClients) return -1;
    info->pPeerIndex[((unsigned int *)pVoid)[1]] = *(unsigned short *)pVoid;
    NetStreamMediaSendMyIndexInfo(pConnInfo, *(unsigned short *)pVoid, 1);
    return 8;
}

int MEDIUS_SMEDIA_SECTION(StreamMediaIndexInfoResponse) StreamMediaIndexInfoResponse(NetTypeConnectionInfo *pConnInfo, int WorldID, int SourceClientIndex, void *pVoid)
{
    NetTypeStreamMediaInfo *info;
    if (!pConnInfo) return -1;
    if (!pVoid) return -1;
    info = NetStreamMediaGetValidInfo(pConnInfo);
    if (!info) return -1;
    if (((unsigned int *)pVoid)[1] >= info->MaxClients) return -1;
    info->pPeerIndex[((unsigned int *)pVoid)[1]] = *(unsigned short *)pVoid;
    return 8;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", StreamMediaBufferRequestHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", StreamMediaBufferGrantedHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", StreamMediaBufferReleaseHandler);

int MEDIUS_SMEDIA_SECTION(NetStreamMediaDisconnect) NetStreamMediaDisconnect(NetTypeConnectionInfo *pConnInfo)
{
    NetTypeStreamMediaInfo *info = NetStreamMediaGetValidInfo(pConnInfo);
    if (!info) return 0x17;
    if (info->CurrentChannel != 0xFF) {
        (*(int (**)(void *, int))(gP2PInterfacePtr + 0x64))(pConnInfo->pP2P, info->CurrentChannel);
    }
    (*(int (**)(void *))(gP2PInterfacePtr + 0x38))(pConnInfo->pP2P);
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaCreateInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaDestroyInfo);

NetTypeStreamMediaInfo *MEDIUS_SMEDIA_SECTION(NetStreamMediaGetValidInfo) NetStreamMediaGetValidInfo(NetTypeConnectionInfo *pConnInfo)
{
    NetTypeStreamMediaInfo *info;
    if (!pConnInfo) return 0;
    info = pConnInfo->pStreamMediaInfo;
    if (info && info->bInUse) return info;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaRemoteClientConnects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaRemoteClientDisconnects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaSendMyIndexInfo);

int MEDIUS_SMEDIA_SECTION(NetStreamMediaSetMyPeerIndex) NetStreamMediaSetMyPeerIndex(NetTypeConnectionInfo *pConnInfo, unsigned short PeerIndex)
{
    NetTypeStreamMediaInfo *info;
    if (!pConnInfo) return 0x17;
    info = NetStreamMediaGetValidInfo(pConnInfo);
    if (!info) return 0x17;
    if ((unsigned int)pConnInfo->MyClientIndex >= info->MaxClients) return 0x17;
    info->pPeerIndex[pConnInfo->MyClientIndex] = PeerIndex;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaGetMyPeerIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", p2p_overlay_data_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", NetStreamMediaSendAddressInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", StreamMediaSendHostQuery);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", StreamMediaHostQueryHandler);

int MEDIUS_SMEDIA_SECTION(StreamMediaHostResponseHandler) StreamMediaHostResponseHandler(NetTypeConnectionInfo *pConnInfo, int WorldID, int SourceClientIndex, void *pThisPacket)
{
    NetStreamMediaDisconnect(pConnInfo);
    StreamMediaSendHostQuery(pConnInfo, 0xFFFE);
    return 1;
}

int MEDIUS_SMEDIA_SECTION(NetUseStreamMedia) NetUseStreamMedia(void)
{
    StreamMediaResolveInterface();
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/StreamMedia", StreamMediaResolveInterface);
