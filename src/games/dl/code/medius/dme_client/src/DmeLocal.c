#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSetHeartbeatInterval);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetUseDme);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", GetSoftwareID);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetMyIntIP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetMyExtIP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", SendMyClientStatus);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", RtMsgToDmeConnectionIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetAverageDelayToClient);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetISetSendAggregationInterval);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetMyClientIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSetPeerToPeerHostChangeCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetResetTime);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", DMEmalloc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", DmeFree);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIRegisterMemoryCallbacks);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetMyIpAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetMyNetAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", RemoteClientConnects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", RemoteClientDisconnects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetCurrentUDPSourceBinaryIP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetLocalTime);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetTime);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetConnectStatus);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetValidClientCount);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetISendTo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetBitMaskToSendMask);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSendMessageByUDP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSendMessageByTCP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetFragSendCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetISendMessage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", ParseMessageList);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetISetNATServiceAddr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetISetDefaultResolveAddrParams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIResolveAddr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSetIncomingClient);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetISetMyClientReceiveBroadcast);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetUpdateAll);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIGetNetUpdateErrors);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIDisconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIClose);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetMapRtError);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetGetClientPingInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCleanupClientPingInfoArray);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetGetConnInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCleanupConnInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCreateConnInfoBare);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSetConnInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCreateConnInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetDestroyConnInfoBare);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetDestroyConnInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetGetClientInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCreateClientInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetDestroyClientInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetGetServerIpAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetSetServerIpAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetCheckForPingTimeouts);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetIsPeerToPeerHost);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetProcessEchoRequests);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetDisablePingIPs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetProcessP2PDisconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetClientIndexToClientIndexPacket);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetGetNatService);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetConvertTransportFlags);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_connect_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_disconnect_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_system_change_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_host_change_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", udp_resolve_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_peer_update_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_incoming_data_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetGetMyWorldID);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", udp_unconnected_data_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", udp_event_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", udp_data_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", p2p_broadcast_update_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", MsgClientSystemMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetMutexLock);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeLocal", NetMutexUnlock);
