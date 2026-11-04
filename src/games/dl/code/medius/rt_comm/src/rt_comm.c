#include "common.h"

#define MEDIUS_COMM_SECTION(name) __attribute__((section(".medius_comm_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_comm_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef unsigned int RT_U4BYTE;
typedef int RT_4BYTE;
typedef RT_U4BYTE RT_BOOL;
typedef int RT_RESULT;

typedef struct {
    /* 0x0 */ RT_U4BYTE Addr[2];
} RT_LINKADDRESS;

typedef struct {
    /* 0x0 */ int Type;
    /* 0x4 */ RT_4BYTE MaxMsgLen;
    /* 0x8 */ RT_BOOL bNonBlockingConnect;
} RT_COMM_CHANNEL_INFO;

typedef struct {
    /* 0x0 */ RT_COMM_CHANNEL_INFO Info;
    /* 0xc */ RT_BOOL bSyncronousReceive;
} RT_COMM_CHANNEL_OPTIONS;

typedef struct {
    /* 0x00 */ RT_BOOL bValid;
    /* 0x04 */ RT_BOOL bInUse;
    /* 0x08 */ int InterfaceID;
    /* 0x0c */ RT_COMM_CHANNEL_OPTIONS Options;
    /* 0x1c */ int Port;
    /* 0x20 */ RT_BOOL bConnected;
} RT_COMM_CHANNEL_DATA;

typedef RT_COMM_CHANNEL_DATA *RT_COMM_CHANNEL_ID;

typedef struct {
    /* 0x00 */ void *pad00[13];
    /* 0x34 */ RT_RESULT (*GetLocalIP)(RT_LINKADDRESS *);
    /* 0x38 */ RT_RESULT (*GetBroadcastIP)(RT_LINKADDRESS *);
    /* 0x3c */ RT_RESULT (*GetHostByName)();
    /* 0x40 */ void *pad40;
    /* 0x44 */ RT_RESULT (*DisplayState)();
    /* 0x48 */ void *pad48[2];
    /* 0x50 */ void (*LinkAddressSetNull)(RT_LINKADDRESS *);
    /* 0x54 */ RT_BOOL (*LinkAddressIsNull)(RT_LINKADDRESS);
    /* 0x58 */ RT_BOOL (*LinkAddressIsEqual)(RT_LINKADDRESS, RT_LINKADDRESS);
    /* 0x5c */ char *(*LinkAddressToStr)(char *, RT_LINKADDRESS);
    /* 0x60 */ RT_RESULT (*LinkAddressToExt)(void *, RT_LINKADDRESS);
    /* 0x64 */ RT_RESULT (*LinkAddressToInt)();
    /* 0x68 */ RT_RESULT (*GetDnsServers)();
} RT_COMM_PLATFORM_INTERFACE;

typedef struct {
    unsigned char data[0x38];
} RT_COMM_METRICS;

extern RT_COMM_PLATFORM_INTERFACE *gCommPlatformInterfacePtr;
// rt_comm global metrics block copied out by rt_comm_get_metrics (0x001B2148).
extern RT_COMM_METRICS mediusCommMetrics;

void *memset(void *, int, unsigned int);
void *memcpy(void *, const void *, unsigned int);
RT_RESULT rt_memory_free(void *ppMemory);
RT_RESULT rt_memory_allocate_init_zero(void *ppMemory, unsigned int size);
void rt_comm_metric_update(RT_COMM_METRICS *pMetrics);


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_startup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_shutdown);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_update);

void MEDIUS_COMM_SECTION(rt_comm_set_default_options) rt_comm_set_default_options(RT_COMM_CHANNEL_OPTIONS *pOptions)
{
    memset(pOptions, 0, 0x10);
    pOptions->Info.Type = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_create);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_destroy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_send_to);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", func_01EA7918);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_vsend_to);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_send_echo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_receive);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_receive_from);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_receive_echo);

RT_RESULT MEDIUS_COMM_SECTION(rt_comm_get_local_ip) rt_comm_get_local_ip(RT_LINKADDRESS *pLinkAddr)
{
    return gCommPlatformInterfacePtr->GetLocalIP(pLinkAddr);
}

RT_RESULT MEDIUS_COMM_SECTION(rt_comm_get_broadcast_ip) rt_comm_get_broadcast_ip(RT_LINKADDRESS *pLinkAddr)
{
    return gCommPlatformInterfacePtr->GetBroadcastIP(pLinkAddr);
}

RT_RESULT MEDIUS_COMM_SECTION(rt_comm_get_host_by_name) rt_comm_get_host_by_name(char *pName, RT_LINKADDRESS *pLinkAddr)
{
    return gCommPlatformInterfacePtr->GetHostByName(pName, pLinkAddr);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", func_01EA7DC0);

RT_RESULT MEDIUS_COMM_SECTION(rt_comm_display_state) rt_comm_display_state(void)
{
    return gCommPlatformInterfacePtr->DisplayState();
}

void MEDIUS_COMM_SECTION(rt_comm_get_metrics) rt_comm_get_metrics(RT_COMM_METRICS *pMetrics)
{
    rt_comm_metric_update(pMetrics);
    memcpy(pMetrics, &mediusCommMetrics, 0x38);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_interface_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_local_port);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_is_connected);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_host_by_name_nb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_generate_lookup_query);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_resend_lookup_query);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_check_for_query_response);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_process_response_header);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_skip_query_section);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_process_rr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_isdigit);

RT_COMM_CHANNEL_ID MEDIUS_COMM_SECTION(rt_comm_get_new_channel_id) rt_comm_get_new_channel_id(void)
{
    RT_COMM_CHANNEL_ID pChannel = 0;
    rt_memory_allocate_init_zero(&pChannel, 0x24);
    if (pChannel == 0) {
        return 0;
    }
    pChannel->bValid = 1;
    return pChannel;
}

void MEDIUS_COMM_SECTION(rt_comm_release_channel_id) rt_comm_release_channel_id(RT_COMM_CHANNEL_ID CID)
{
    rt_memory_free(&CID);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_is_valid_channel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_metric_init);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_metric_add_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_metric_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_metric_update_single);

void MEDIUS_COMM_SECTION(rt_comm_linkaddress_setnull) rt_comm_linkaddress_setnull(RT_LINKADDRESS *pAddr)
{
    gCommPlatformInterfacePtr->LinkAddressSetNull(pAddr);
}

RT_BOOL MEDIUS_COMM_SECTION(rt_comm_linkaddress_isnull) rt_comm_linkaddress_isnull(RT_LINKADDRESS LinkAddr)
{
    return gCommPlatformInterfacePtr->LinkAddressIsNull(LinkAddr);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_linkaddress_isequal);

char * MEDIUS_COMM_SECTION(rt_comm_linkaddress_tostr) rt_comm_linkaddress_tostr(char *pszStr, RT_LINKADDRESS LinkAddr)
{
    return gCommPlatformInterfacePtr->LinkAddressToStr(pszStr, LinkAddr);
}

RT_RESULT MEDIUS_COMM_SECTION(rt_comm_linkaddress_toext) rt_comm_linkaddress_toext(void *pExt, RT_LINKADDRESS LinkAddr)
{
    return gCommPlatformInterfacePtr->LinkAddressToExt(pExt, LinkAddr);
}

RT_RESULT MEDIUS_COMM_SECTION(rt_comm_linkaddress_toint) rt_comm_linkaddress_toint(void *pExt, RT_LINKADDRESS *pAddr)
{
    return gCommPlatformInterfacePtr->LinkAddressToInt(pExt, pAddr);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", func_01EA8C90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_echo_send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_echo_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_echo_shutdown);

RT_RESULT MEDIUS_COMM_SECTION(rt_comm_get_dns_servers) rt_comm_get_dns_servers(void *pServers, int count)
{
    return gCommPlatformInterfacePtr->GetDnsServers(pServers, count);
}
