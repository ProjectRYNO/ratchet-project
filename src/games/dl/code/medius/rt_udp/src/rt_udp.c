#include "common.h"

#define MEDIUS_UDP_SECTION(name) __attribute__((section(".medius_udp_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_udp_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef unsigned int RT_U4BYTE;
typedef unsigned short RT_U2BYTE;
typedef unsigned char RT_U1BYTE;
typedef int RT_RESULT;

typedef struct {
    RT_U4BYTE Addr[2];
} RT_LINKADDRESS;

typedef struct {
    RT_U4BYTE nDataSize;
    char pad4[0x10 - 0x4];
} RT_LIST_BUF;

typedef struct RT_UDP_ICONNECTION {
    RT_U4BYTE State;
    char pad4[0x8 - 0x4];
    RT_LINKADDRESS DestAddress;
    RT_U4BYTE DestPort;
    RT_LIST_BUF SendBuf;
    RT_LIST_BUF RecvBuf;
    char pad34[0x44 - 0x34];
    RT_U4BYTE InactivityTimeout;
    RT_U4BYTE pad48;
    RT_U4BYTE LatencyC;
    RT_U4BYTE LatencyA;
    RT_U4BYTE LatencyB;
    char pad58[0x5C - 0x58];
    RT_U2BYTE VirtualPort;
    char pad5e[0x70 - 0x5E];
    RT_U4BYTE nPeerID;
    char pad74[0x8C - 0x74];
    struct RT_UDP_ICONNECTION *next;
} RT_UDP_ICONNECTION;

typedef void (*RT_UDP_RESOLVE_CB)(void *piChannel, RT_U4BYTE b, RT_LINKADDRESS addr, RT_U4BYTE port, void *pUserData);

typedef struct {
    char pad0[0xC];
    RT_UDP_ICONNECTION *pConnList;
    void *igd;
    char BufferPool[0x70 - 0x14];
    RT_U4BYTE AggregationInterval;
    char pad74[0x80 - 0x74];
    RT_U4BYTE bListening;
    RT_U4BYTE bResolving;
    char pad88[0x94 - 0x88];
    RT_LINKADDRESS LocalIP;
    RT_U4BYTE BindPort;
    char pad9c[0xB0 - 0xA0];
    RT_UDP_RESOLVE_CB pResolveCallback;
    void *pResolveUserData;
} RT_UDP_ICHANNEL;

typedef struct {
    RT_U2BYTE Flags;
    RT_U2BYTE Count;
} RT_UDP_HEADER;

typedef struct {
    RT_U1BYTE b[2];
} RT_UDP_SEQ;

typedef struct {
    RT_U2BYTE FlagsAndPayloadSize;
    RT_UDP_SEQ Seq;
} RT_UDP_SUB_HEADER;

typedef struct {
    RT_U4BYTE a;
    RT_U4BYTE b;
    RT_U4BYTE c;
} RT_UDP_LATENCY_INFO;

RT_U4BYTE randomMT(void);
RT_U2BYTE rt_udp_get_sequence_id(RT_UDP_SUB_HEADER *pSubHeader);
RT_RESULT rt_udp_buffer_ack(RT_UDP_ICHANNEL *piChannel, RT_UDP_ICONNECTION *pConnection, RT_U2BYTE seq);
void rt_list_buf_clear(RT_LIST_BUF *pBuf);
RT_RESULT rt_list_buf_resize_buffer(RT_LIST_BUF *pBuf, RT_U4BYTE size);

typedef struct {
    RT_U2BYTE v;
    RT_U2BYTE pad;
} RT_U2_BOX;
extern int mediusUdpUnexpectedPortEnabled;
extern char mediusUdpVersionString[];
extern RT_U4BYTE mediusUdpInactivityTimeout;

typedef struct {
    unsigned int Addr[2];
} RT_UDP3_LINKADDRESS;
typedef struct {
    void *comm;
    char pad4[0x8 - 0x4];
    RT_UDP3_LINKADDRESS addr;
    int port;
    char pad14[0x5E - 0x14];
    unsigned short id;
} RT_UDP3_CONN;
typedef struct {
    void *comm;
    char pad4[0x10 - 0x4];
    void *upnp;
    char pad14[0x58 - 0x14];
    void *m58;
    void *m5c;
} RT_UDP3_SHARED;
extern int rt_udp_send_version_exchange(void *a, int *conn);
extern int rt_comm_destroy(void *c);
extern int rt_memory_free(void *p);
extern int rt_upnp_destroy(void *p);
extern int rt_comm_shutdown(void);
extern int rt_comm_send_to(void *c, RT_UDP3_LINKADDRESS addr, int port, void *buf, int len, int *out);
extern void *memset(void *, int, unsigned int);
extern int rt_upnp_get_external_address(void *u);

void MEDIUS_UDP_SECTION(rt_udp_enable_unexpected_port) rt_udp_enable_unexpected_port(int b_setting)
{
    mediusUdpUnexpectedPortEnabled = b_setting;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_get_sequence_id);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_ack_list_flush);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_buffer_ack);

RT_UDP_SUB_HEADER *MEDIUS_UDP_SECTION(rt_udp_get_first_sub_header) rt_udp_get_first_sub_header(RT_UDP_HEADER *pHeader)
{
    RT_U2_BOX count;
    RT_U4BYTE offset;
    if (pHeader->Flags & 0x4000) {
        count.v = pHeader->Count;
        offset = sizeof(RT_UDP_HEADER) + count.v * sizeof(RT_U2BYTE);
        return (RT_UDP_SUB_HEADER *)((char *)pHeader + offset);
    }
    return (RT_UDP_SUB_HEADER *)((char *)pHeader + 2);
}

int MEDIUS_UDP_SECTION(FUN_01ebd750) FUN_01ebd750(void)
{
    return 2;
}

RT_U4BYTE MEDIUS_UDP_SECTION(randomNonZero) randomNonZero(RT_U4BYTE n)
{
    RT_U4BYTE r;
    do {
        r = randomMT() % n;
    } while (r == 0);
    return r;
}

RT_RESULT MEDIUS_UDP_SECTION(NetUseUDP) NetUseUDP(void)
{
    rt_udp_resolve_interface();
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_resolve_interface);

char *MEDIUS_UDP_SECTION(rt_udp_get_version_string) rt_udp_get_version_string(void)
{
    return mediusUdpVersionString;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_create);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_destroy);

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_set_buffer_size) rt_udp_set_buffer_size(RT_UDP_ICHANNEL *piChannel, RT_UDP_ICONNECTION *pConnection, RT_U4BYTE which, RT_U4BYTE size)
{
    if (piChannel == 0) {
        return 0xD2F2;
    }
    if (pConnection == 0) {
        return 0xD2F3;
    }
    if (pConnection->State == 0) {
        return 0xD2F3;
    }
    if (size == 0) {
        return 2;
    }
    if (which == 0) {
        return rt_list_buf_resize_buffer(&pConnection->SendBuf, size);
    }
    if (which == 1) {
        return rt_list_buf_resize_buffer(&pConnection->RecvBuf, size);
    }
    return 2;
}

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_set_aggregation_interval) rt_udp_set_aggregation_interval(RT_UDP_ICHANNEL *piChannel, RT_U4BYTE interval)
{
    RT_RESULT result = 0xD2F2;
    if (piChannel != 0) {
        piChannel->AggregationInterval = interval;
        result = 0;
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_get_buffer_size);

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_get_aggregation_interval) rt_udp_get_aggregation_interval(RT_UDP_ICHANNEL *piChannel, RT_U4BYTE *pInterval)
{
    *pInterval = 0;
    if (piChannel == 0) {
        return 0xD2F2;
    }
    *pInterval = piChannel->AggregationInterval;
    return 0;
}

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_get_virtual_port) rt_udp_get_virtual_port(RT_UDP_ICONNECTION *pConnection, RT_U2BYTE *pPort)
{
    *pPort = 0;
    if (pConnection == 0) {
        return 0xD2F3;
    }
    *pPort = pConnection->VirtualPort;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_get_buffer_stats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_resolve_address);

int MEDIUS_UDP_SECTION(rt_udp_get_resolved_address) rt_udp_get_resolved_address(RT_UDP3_SHARED *ch, void *a, void *b)
{
    int r;
    if (ch == 0)
        return 0xD2F2;
    if (ch->upnp) {
        r = rt_upnp_get_external_address(ch->upnp);
        if (r == 0)
            return r;
        return rt_udp_get_local_address(ch, a, b);
    }
    return rt_udp_get_local_address(ch, a, b);
}

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_get_local_address) rt_udp_get_local_address(RT_UDP_ICHANNEL *piChannel, RT_LINKADDRESS *pIP, RT_U4BYTE *pPort)
{
    if (piChannel == 0) {
        return 0xD2F2;
    }
    *pIP = piChannel->LocalIP;
    *pPort = piChannel->BindPort;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_get_address);

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_disable_nat_service_heartbeat) rt_udp_disable_nat_service_heartbeat(RT_UDP_ICHANNEL *piChannel)
{
    RT_RESULT result = 0xD2F2;
    if (piChannel != 0) {
        rt_upnp_disable_natservice_heartbeat(piChannel->igd);
        result = 0;
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_connect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_disconnect);

void MEDIUS_UDP_SECTION(rt_udp_set_peer_id) rt_udp_set_peer_id(RT_UDP_ICONNECTION *pConnection, RT_U4BYTE nPeerID)
{
    if (pConnection != 0) {
        pConnection->nPeerID = nPeerID;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_send_list);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_send_unconnected);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_broadcast);

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_listen) rt_udp_listen(RT_UDP_ICHANNEL *piChannel, RT_U4BYTE bListen)
{
    RT_RESULT result = 2;
    if (piChannel != 0) {
        piChannel->bListening = bListen;
        result = 0;
    }
    return result;
}

int MEDIUS_UDP_SECTION(rt_udp_accept) rt_udp_accept(void *a, int *conn)
{
    if (a == 0)
        return 2;
    if (conn == 0)
        return 0xD2F3;
    if (*conn != 8)
        return 0xD2F4;
    *conn = 9;
    if (rt_udp_send_version_exchange(a, conn) != 0) {
        *conn = 7;
        return 0xD2F7;
    }
    return 0;
}

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_deny) rt_udp_deny(RT_UDP_ICHANNEL *piChannel, RT_UDP_ICONNECTION *pConnection)
{
    if (piChannel == 0) {
        return 2;
    }
    if (pConnection == 0) {
        return 0xD2F3;
    }
    if (pConnection->State != 8) {
        return 0xD2F4;
    }
    pConnection->State = 5;
    rt_udp_send_reset(piChannel, pConnection);
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_pre_accept);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_event_process);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_event_check);

void MEDIUS_UDP_SECTION(rt_udp_add_conn_to_list) rt_udp_add_conn_to_list(RT_UDP_ICHANNEL *piChannel, RT_UDP_ICONNECTION *pConnection)
{
    pConnection->next = piChannel->pConnList;
    piChannel->pConnList = pConnection;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_del_conn_from_list);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_find_free_connection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_setup_packet_sub_header);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_buffer_data_for_send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_append_data_to_packet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_get_packet_seed);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_set_packet_seed);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_send_messages);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_remove_non_delivery_critical_packets);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_send_broadcasts);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_receive_messages);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_process_message);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_process_version_exchange);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_send_version_exchange);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", FUN_01ec0fa8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_process_disconnect);

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_process_reset) rt_udp_process_reset(RT_UDP_ICONNECTION *pConnection)
{
    if (pConnection == 0) {
        return 0xD2F3;
    }
    if (pConnection->State != 5) {
        pConnection->State = 2;
        rt_list_buf_clear(&pConnection->SendBuf);
        rt_list_buf_clear(&pConnection->RecvBuf);
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_process_heartbeat);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_process_acknowlege);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_process_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_process_unconnected_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_find_connection);

int MEDIUS_UDP_SECTION(rt_udp_send_reset) rt_udp_send_reset(void **ch, RT_UDP3_CONN *c)
{
    unsigned short buf[8];
    int out = 0;
    memset(buf, 0, 6);
    buf[0] = (c->id & 0x3FF) | 0x1000;
    rt_comm_send_to(*ch, c->addr, c->port, buf, 6, &out);
    return 0;
}

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_send_ack) rt_udp_send_ack(RT_UDP_ICHANNEL *piChannel, RT_UDP_ICONNECTION *pConnection, RT_UDP_SUB_HEADER *pSubHeader)
{
    return rt_udp_buffer_ack(piChannel, pConnection, rt_udp_get_sequence_id(pSubHeader));
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_is_duplicate_packet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_calculate_rto);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_create_shared_channel_data);

int MEDIUS_UDP_SECTION(rt_udp_destroy_shared_channel_data) rt_udp_destroy_shared_channel_data(RT_UDP3_SHARED *p)
{
    void *u;
    rt_comm_destroy(p->comm);
    rt_memory_free(&p->m58);
    rt_memory_free(&p->m5c);
    u = p->upnp;
    if (u) {
        rt_upnp_destroy(u);
        p->upnp = 0;
    }
    rt_comm_shutdown();
    return 0;
}

void MEDIUS_UDP_SECTION(rt_udp_uber_resolve_cb) rt_udp_uber_resolve_cb(RT_U4BYTE a, RT_U4BYTE b, RT_U4BYTE c, RT_LINKADDRESS addr, RT_U4BYTE port, RT_UDP_ICHANNEL *piChannel)
{
    if (piChannel != 0) {
        piChannel->bResolving = 0;
        piChannel->pResolveCallback(piChannel, b, addr, port, piChannel->pResolveUserData);
    }
}

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_get_inactivity_timeout) rt_udp_get_inactivity_timeout(RT_U4BYTE *pnmsecs)
{
    *pnmsecs = mediusUdpInactivityTimeout;
    return 0;
}

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_set_connection_inactivity_timeout) rt_udp_set_connection_inactivity_timeout(RT_UDP_ICONNECTION *pConnection, RT_U4BYTE msecs)
{
    RT_RESULT result = 2;
    if (msecs != 0) {
        pConnection->InactivityTimeout = msecs;
        result = 0;
    }
    return result;
}

RT_RESULT MEDIUS_UDP_SECTION(rt_udp_get_latency_info) rt_udp_get_latency_info(RT_UDP_ICONNECTION *pConnection, RT_UDP_LATENCY_INFO *pInfo)
{
    if (pConnection == 0) {
        return 0xD2F3;
    }
    if (pConnection->State != 0xD) {
        return 0xD2F3;
    }
    if (pInfo == 0) {
        return 2;
    }
    pInfo->a = pConnection->LatencyA;
    pInfo->b = pConnection->LatencyB;
    pInfo->c = pConnection->LatencyC;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp", rt_udp_get_pool_used);
