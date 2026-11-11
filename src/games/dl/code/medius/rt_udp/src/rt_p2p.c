#include "common.h"

#define MEDIUS_P2P_SECTION(name) __attribute__((section(".medius_p2p_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_p2p_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef unsigned int RT_U4BYTE;
typedef unsigned short RT_U2BYTE;
typedef unsigned char RT_U1BYTE;
typedef int RT_RESULT;
typedef unsigned short RT_PEER_INDEX;
typedef unsigned short RT_UDP_PORT;

typedef struct {
    RT_U4BYTE Addr[2];
} RT_LINKADDRESS;

typedef struct {
    char pad0[0x4];
    void *pConnection;
    void *pAltConnection;
    char padc[0x14 - 0xC];
    RT_U4BYTE BroadcastIndex;
    RT_U4BYTE bSendBroadcasts;
    char pad1c[0x50 - 0x1C];
} RT_PEER_INFO;

typedef struct {
    char pad0[0x10];
    RT_U4BYTE nPeers;
    RT_U4BYTE Type;
} RT_OVERLAY_INFO;

typedef struct {
    RT_U1BYTE pad0[2];
    RT_U1BYTE Index;
    RT_U1BYTE pad3;
} RT_BROADCAST_MSG;

typedef void (*RT_P2P_BROADCAST_CB)(RT_PEER_INDEX peerIndex, RT_U4BYTE index, void *pUserData);

typedef struct {
    void *channel;
    char pad4[0x184 - 0x4];
    RT_PEER_INFO *PeerInfo;
    RT_OVERLAY_INFO *OverlayInfo;
    char pad18c[0x19C - 0x18C];
    RT_PEER_INDEX MaxPeers;
    char pad19e[0x1A2 - 0x19E];
    RT_PEER_INDEX HostPeerIndex;
    RT_PEER_INDEX MyPeerIndex;
    char pad1a6[0x1CC - 0x1A6];
    RT_U2BYTE nVirtualPort;
    char pad1ce[0x1D8 - 0x1CE];
    RT_U4BYTE nOverlays;
    char pad1dc[0x1E4 - 0x1DC];
    RT_U4BYTE bEnabDisconnectFwd;
    char pad1e8[0x204 - 0x1E8];
    RT_P2P_BROADCAST_CB pBroadcastCallback;
    char pad208[0x218 - 0x208];
    void *pBroadcastUserData;
} RT_IP2P;

typedef struct {
    RT_U4BYTE a;
    RT_U4BYTE b;
    RT_U4BYTE c;
    RT_U4BYTE d;
} RT_P2P_INTERFACE_PARAMS;

typedef struct {
    char pad0[0x84];
    RT_U4BYTE a;
    RT_U4BYTE b;
    RT_U4BYTE d;
    RT_U4BYTE c;
} RT_UDP_INTERFACE;

extern RT_UDP_INTERFACE *gUDPInterfacePtr;

typedef struct {
    char pad0[0x48];
    RT_U4BYTE bIgnore;
} RT_OVERLAY_PEER;

typedef struct {
    RT_OVERLAY_PEER **pPeers;
} RT_OVERLAY_PEERS_VIEW;

void rt_p2p_resolve_interface(void);
RT_RESULT NetUseUDP(void);
RT_RESULT rt_udp_get_local_address(void *channel, RT_LINKADDRESS *pIP, RT_U4BYTE *pPort);
RT_RESULT rt_udp_get_resolved_address(void *channel, RT_LINKADDRESS *pIP, RT_U4BYTE *pPort);
RT_RESULT rt_udp_get_latency_info(void *pConnection, void *pInfo);

typedef struct {
    int state;
    void *pConnection;
    void *pAltConnection;
    int bConn;
    int bAltConn;
    char pad14[0x34 - 0x14];
    unsigned short connId;
    char pad36[0x50 - 0x36];
} RT_P2P3_PEER;
typedef struct {
    void *channel;
    char pad4[0x184 - 0x4];
    RT_P2P3_PEER *PeerInfo;
    char pad188[0x198 - 0x188];
    void *grid;
    unsigned short MaxPeers;
} RT_P2P3;
typedef struct {
    char b[6];
} RT_P2P3_MSG6;
typedef union {
    RT_P2P3_MSG6 s;
    unsigned short h[3];
} RT_P2P3_MSG6U;
typedef struct {
    void *conn;
    unsigned int time[2];
} RT_P2P3_BACKLOG_ENTRY;
typedef struct {
    void *channel;
    RT_P2P3_BACKLOG_ENTRY e[32];
} RT_P2P3_BACKLOG;
extern int rt_udp_send(void *ch, void *conn, unsigned int a, void *b);
extern void *memset(void *, int, unsigned int);
extern int rt_p2p_generate_grid_add_peer(RT_P2P3 *p, char idx);
extern int rt_p2p_generic_disconnect(RT_P2P3 *p, void *conn, int a, int b);
extern int rt_time_start(void *t);
extern int rt_udp_deny(void *ch, void *conn);

RT_RESULT MEDIUS_P2P_SECTION(NetUsePeerToPeer) NetUsePeerToPeer(RT_P2P_INTERFACE_PARAMS *pParams)
{
    rt_p2p_resolve_interface();
    NetUseUDP();
    if (gUDPInterfacePtr != 0) {
        gUDPInterfacePtr->a = pParams->a;
        gUDPInterfacePtr->b = pParams->b;
        gUDPInterfacePtr->d = pParams->d;
        gUDPInterfacePtr->c = pParams->c;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_resolve_interface);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_create);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_destroy);

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_get_current_address_type) rt_p2p_get_current_address_type(RT_IP2P *ip2p, RT_PEER_INDEX peerIndex, int *pType)
{
    *pType = -1;
    if (ip2p == 0) {
        return 2;
    }
    if (peerIndex >= ip2p->MaxPeers) {
        return 0xD4E6;
    }
    if (ip2p->PeerInfo[peerIndex].pConnection != 0) {
        *pType = 0;
    } else if (ip2p->PeerInfo[peerIndex].pAltConnection != 0) {
        *pType = 1;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_peer_address);

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_get_my_address) rt_p2p_get_my_address(RT_IP2P *ip2p, RT_U4BYTE type, RT_LINKADDRESS *pIP, RT_U4BYTE *pPort)
{
    RT_RESULT result;
    if (ip2p == 0) {
        return 2;
    }
    if (type == 0) {
        result = rt_udp_get_local_address(ip2p->channel, pIP, pPort);
        if (result != 0) {
            return result;
        }
    } else if (type == 1) {
        result = rt_udp_get_resolved_address(ip2p->channel, pIP, pPort);
        if (result != 0) {
            return result;
        }
    } else {
        return 2;
    }
    return 0;
}

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_get_my_peer_index) rt_p2p_get_my_peer_index(RT_IP2P *ip2p, RT_PEER_INDEX *pMyIndex)
{
    if (pMyIndex == 0) {
        return 2;
    }
    if (ip2p == 0) {
        return 2;
    }
    *pMyIndex = ip2p->MyPeerIndex;
    return 0;
}

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_get_host_index) rt_p2p_get_host_index(RT_IP2P *ip2p, RT_PEER_INDEX *pPeerIndex)
{
    if (pPeerIndex == 0) {
        return 2;
    }
    if (ip2p == 0) {
        return 2;
    }
    *pPeerIndex = ip2p->HostPeerIndex;
    return 0;
}

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_get_virtual_port) rt_p2p_get_virtual_port(RT_IP2P *ip2p, RT_U2BYTE *pnVirtualPort)
{
    if (pnVirtualPort == 0) {
        return 2;
    }
    *pnVirtualPort = 0;
    if (ip2p == 0) {
        return 2;
    }
    *pnVirtualPort = ip2p->nVirtualPort;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_buffer_stats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_peer_buffer_stats);

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_set_send_aggregation) rt_p2p_set_send_aggregation(RT_IP2P *ip2p, RT_U4BYTE AggregateMsecs)
{
    RT_RESULT result = 2;
    if (ip2p != 0) {
        result = rt_udp_set_aggregation_interval(ip2p->channel, AggregateMsecs);
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_host);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_incoming_peer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_connect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_disconnect);

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_tick) rt_p2p_tick(RT_IP2P *ip2p)
{
    RT_RESULT result = 2;
    if (ip2p != 0) {
        result = 0;
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_list);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_receive_broadcasts);

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_send_to) rt_p2p_send_to(RT_IP2P *ip2p, RT_LINKADDRESS IPAddress, RT_U4BYTE Port, void *pVector)
{
    RT_RESULT result = 2;
    if (ip2p != 0) {
        result = rt_udp_send_unconnected(ip2p->channel, IPAddress, Port, pVector);
    }
    return result;
}

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_get_max_peers) rt_p2p_get_max_peers(RT_IP2P *ip2p, RT_U4BYTE *pMaxPeers)
{
    if (pMaxPeers == 0) {
        return 2;
    }
    *pMaxPeers = 0;
    if (ip2p == 0) {
        return 2;
    }
    *pMaxPeers = ip2p->MaxPeers;
    return 0;
}

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_set_max_peers) rt_p2p_set_max_peers(RT_IP2P *ip2p, RT_U4BYTE nMaxPeers)
{
    RT_RESULT result = 2;
    if (ip2p != 0) {
        ip2p->MaxPeers = nMaxPeers;
        result = 0;
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_set_overlay_type);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_join_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_quit_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_quit_all_overlays);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_ignore_peer_in_overlay);

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_get_overlay_peer_count) rt_p2p_get_overlay_peer_count(RT_IP2P *ip2p, RT_U1BYTE overlayIndex, RT_U4BYTE *pCount)
{
    if (pCount == 0) {
        return 2;
    }
    *pCount = 0;
    if (ip2p == 0) {
        return 2;
    }
    if (overlayIndex >= ip2p->nOverlays) {
        return 2;
    }
    if (ip2p->OverlayInfo == 0) {
        return 3;
    }
    *pCount = ip2p->OverlayInfo[overlayIndex].nPeers;
    return 0;
}

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_is_peer_in_overlay) rt_p2p_is_peer_in_overlay(RT_IP2P *ip2p, RT_U1BYTE overlayIndex, RT_PEER_INDEX peerIndex, RT_U4BYTE *pResult)
{
    if (pResult == 0) {
        return 2;
    }
    *pResult = 0;
    if (ip2p == 0) {
        return 2;
    }
    if (overlayIndex >= ip2p->nOverlays) {
        return 2;
    }
    if (ip2p->OverlayInfo == 0) {
        return 3;
    }
    if (peerIndex >= ip2p->MaxPeers) {
        return 2;
    }
    if (((RT_OVERLAY_PEERS_VIEW *)&ip2p->OverlayInfo[overlayIndex])->pPeers[peerIndex] != 0) {
        *pResult = 1;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_overlay);

RT_U2BYTE MEDIUS_P2P_SECTION(rt_p2p_pack_type) rt_p2p_pack_type(int type, RT_U2BYTE size)
{
    return (size & 0x7FF) | ((type & 0x1F) << 11);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_unpack_type);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_udp_event_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_udp_data_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_peer_info);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_connect_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_connected_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_timeout_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_closed_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_reset_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_error_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_peer_by_address);

RT_PEER_INDEX MEDIUS_P2P_SECTION(rt_p2p_get_peer_by_connection) rt_p2p_get_peer_by_connection(RT_IP2P *ip2p, void *pConnection)
{
    RT_PEER_INDEX i;
    for (i = 0; i < ip2p->MaxPeers; i++) {
        if (pConnection == ip2p->PeerInfo[i].pConnection) {
            return i;
        }
        if (pConnection == ip2p->PeerInfo[i].pAltConnection) {
            return i;
        }
    }
    return 0xFFFE;
}

void MEDIUS_P2P_SECTION(rt_p2p_get_my_peer_status) rt_p2p_get_my_peer_status(RT_P2P3 *p, int *status, short *idx)
{
    int i;
    int s = 0;
    *idx = -2;
    *status = 0;
    i = p->MaxPeers;
    while (i-- > 0) {
        s = p->PeerInfo[i].state;
        if ((unsigned int)(s - 7) < 3)
            break;
        if (s == 1) {
            *status = 7;
            return;
        }
    }
    if (i >= 0) {
        *status = s;
        *idx = i;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_find_free_peer_index);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_fill_new_peer_struct);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_internal_message);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_new_peer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_coordinate_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_connect_complete);

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_process_broadcast_update) rt_p2p_process_broadcast_update(RT_IP2P *ip2p, RT_PEER_INDEX peerIndex, RT_U1BYTE *pData)
{
    RT_BROADCAST_MSG msg;
    msg = *(RT_BROADCAST_MSG *)pData;
    ip2p->PeerInfo[peerIndex].BroadcastIndex = msg.Index;
    ip2p->pBroadcastCallback(peerIndex, msg.Index, ip2p->pBroadcastUserData);
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_connection_detached);

int MEDIUS_P2P_SECTION(rt_p2p_process_broadcast_disconnect) rt_p2p_process_broadcast_disconnect(RT_P2P3 *p, void *a1, RT_P2P3_MSG6 *msg)
{
    RT_P2P3_MSG6U m;
    m.s = *msg;
    if (p->PeerInfo[m.h[1]].connId != m.h[2])
        return 0;
    if (p->PeerInfo[m.h[1]].pConnection) {
        rt_p2p_generic_disconnect(p, p->PeerInfo[m.h[1]].pConnection, 1, 0xD2F3);
        return 0;
    }
    if (p->PeerInfo[m.h[1]].pAltConnection)
        rt_p2p_generic_disconnect(p, p->PeerInfo[m.h[1]].pAltConnection, 1, 0xD2F3);
    return 0;
}

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_process_local_broadcast_test) rt_p2p_process_local_broadcast_test(RT_IP2P *ip2p, RT_PEER_INDEX peerIndex, RT_U1BYTE *pData)
{
    if (ip2p->PeerInfo[peerIndex].bSendBroadcasts != 1) {
        ip2p->PeerInfo[peerIndex].bSendBroadcasts = 1;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_overlay_type);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_join_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_join_response);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_quit_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_ignore_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_grid_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_complete_connection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_local_broadcast_tests);

int MEDIUS_P2P_SECTION(rt_p2p_isend) rt_p2p_isend(RT_P2P3 *p, RT_P2P3_PEER *peer, unsigned short len, void *buf)
{
    int r = 0xD2F3;
    if (peer->pConnection && peer->bConn) {
        r = rt_udp_send(p->channel, peer->pConnection, len, buf);
        if (r)
            return r;
    } else if (peer->pAltConnection && peer->bAltConn) {
        r = rt_udp_send(p->channel, peer->pAltConnection, len, buf);
        if (r)
            return r;
    }
    return r;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_isend_list);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_my_broadcast_flag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_generic_disconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_determine_new_host);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_connection_detached_to_host);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_broadcast_disconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_notify_peers_disconnect_forwarding);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_notify_peers_disconnect);

int MEDIUS_P2P_SECTION(rt_p2p_save_backlog_connection) rt_p2p_save_backlog_connection(RT_P2P3_BACKLOG *b, void *conn)
{
    unsigned int i;
    unsigned int freeIdx = 32;
    for (i = 0; i < 32; i++) {
        if (b->e[i].conn == conn)
            return 0;
        if (b->e[i].conn == 0 && freeIdx == 32)
            freeIdx = i;
    }
    if (freeIdx != 32) {
        b->e[freeIdx].conn = conn;
        rt_time_start(b->e[freeIdx].time);
        return 0;
    }
    rt_udp_deny(b->channel, conn);
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_find_backlog_connection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_timeout_backlog_connection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_generate_grid_fill_empties);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_generate_grid_add_peer);

int MEDIUS_P2P_SECTION(rt_p2p_generate_grid) rt_p2p_generate_grid(RT_P2P3 *p, unsigned int n)
{
    unsigned int i;
    int r;
    memset(p->grid, -1, p->MaxPeers * 3);
    for (i = 0; i < n; i++) {
        r = rt_p2p_generate_grid_add_peer(p, i);
        if (r)
            return r;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_peer_grid_edges);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_update_grid);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_token_msg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_token_list_msg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_token_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", FUN_01ebc970);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_timebase_query);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_timebase_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_game_session_key);

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_get_latency_info) rt_p2p_get_latency_info(RT_IP2P *ip2p, RT_PEER_INDEX peerIndex, void *pInfo)
{
    RT_RESULT result;
    if (ip2p == 0) {
        return 2;
    }
    if (ip2p->PeerInfo[peerIndex].pConnection != 0) {
        result = rt_udp_get_latency_info(ip2p->PeerInfo[peerIndex].pConnection, pInfo);
        if (result != 0) {
            return result;
        }
    } else if (ip2p->PeerInfo[peerIndex].pAltConnection != 0) {
        result = rt_udp_get_latency_info(ip2p->PeerInfo[peerIndex].pAltConnection, pInfo);
        if (result != 0) {
            return result;
        }
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_set_host_invactivity_timeout_session);

RT_RESULT MEDIUS_P2P_SECTION(rt_p2p_set_host_inactivity_timeout_connection) rt_p2p_set_host_inactivity_timeout_connection(RT_IP2P *ip2p, void *pConnection)
{
    RT_U4BYTE timeout;
    if (ip2p->bEnabDisconnectFwd != 0) {
        rt_udp_get_inactivity_timeout(&timeout);
        timeout = timeout >> 2;
        rt_udp_set_connection_inactivity_timeout(pConnection, timeout);
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_set_peer_update_bit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_new_peer_info);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_peer_updates);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_reset_peer_info);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_peer_host_query);
