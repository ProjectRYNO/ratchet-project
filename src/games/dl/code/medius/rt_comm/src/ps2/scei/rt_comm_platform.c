#include "common.h"
#include "../../../../rt_util/rt_ip.h"

#define MEDIUS_COMMPLAT_SECTION(name) __attribute__((section(".medius_commplat_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_commplat_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef enum { RT_RESULT_OK = 0, RT_NOT_INITIALIZED = 5, RT_COMM_ERROR = 50000 } RT_RESULT;
typedef enum { NetErrorNone = 0 } NetErrorCode;
typedef int RT_BOOL;
typedef unsigned int RT_IP;
typedef int RT_COMM_INTERFACE_ID;

typedef struct { // 0x8
    /* 0x00 */ unsigned int Addr[2];
} RT_LINKADDRESS;

typedef struct { // 0x10
    /* 0x00 */ int reserved;
    /* 0x04 */ unsigned char data[12];
} sceInetAddress;

// Non-zero once rt_comm_platform has started the libnet interface.
extern int mediusCommPlatformInitialized;
// Local IP from the libnet stack (debug-info name).
extern RT_IP gLocalIP;
// Broadcast IP of the local network.
extern RT_IP mediusCommBroadcastIP;
// libnet SIF client passed to the sceBInet calls.
extern char mediusCommInetClient[];

extern void *memset(void *, int, unsigned int);
extern void rt_comm_platform_resolve_interface(void);
extern int sceBInetUpdate(void *);
extern int sceBInetDisplayLibnetbState(void *);
extern unsigned int mediusCommInetBuffer[];
extern int mediusCommPlatformInterfaceId;
extern int sceBLibnetTerminate(void *, unsigned int *);
extern int sceLibnetUnregisterHandler(void *, unsigned int *);
extern int sceLibnetTerminate(void *);
extern int sceBInetClose(void *, unsigned int *, int, int);

NetErrorCode MEDIUS_COMMPLAT_SECTION(NetUseCommInet) NetUseCommInet(void)
{
    rt_comm_platform_resolve_interface();
    return NetErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_resolve_interface);

void MEDIUS_COMMPLAT_SECTION(RTIP2Address) RTIP2Address(sceInetAddress *pAddr, RT_IP ip)
{
    memset(pAddr, 0, sizeof(sceInetAddress));
    pAddr->reserved = 0;
    pAddr->data[0] = ip >> 24;
    pAddr->data[1] = ip >> 16;
    pAddr->data[2] = ip >> 8;
    pAddr->data[3] = ip;
}

RT_IP MEDIUS_COMMPLAT_SECTION(Address2RTIP) Address2RTIP(sceInetAddress *pAddr)
{
    return (((pAddr->data[0] << 8) + pAddr->data[1] << 8) + pAddr->data[2] << 8) + pAddr->data[3];
}

void MEDIUS_COMMPLAT_SECTION(rt_comm_platform_linkaddress_setnull) rt_comm_platform_linkaddress_setnull(RT_LINKADDRESS *pAddr)
{
    memset(pAddr, 0, sizeof(RT_LINKADDRESS));
}

RT_BOOL MEDIUS_COMMPLAT_SECTION(rt_comm_platform_linkaddress_isnull) rt_comm_platform_linkaddress_isnull(RT_LINKADDRESS LinkAddr)
{
    return LinkAddr.Addr[0] == 0;
}

RT_BOOL MEDIUS_COMMPLAT_SECTION(rt_comm_platform_linkaddress_isequal) rt_comm_platform_linkaddress_isequal(RT_LINKADDRESS LinkAddr1, RT_LINKADDRESS LinkAddr2)
{
    return LinkAddr1.Addr[0] == LinkAddr2.Addr[0];
}

char *MEDIUS_COMMPLAT_SECTION(rt_comm_platform_linkaddress_tostr) rt_comm_platform_linkaddress_tostr(char *pszStr, RT_LINKADDRESS LinkAddr)
{
    rt_ip_ip2string(pszStr, LinkAddr.Addr[0]);
    return pszStr;
}

RT_RESULT MEDIUS_COMMPLAT_SECTION(rt_comm_platform_linkaddress_toext) rt_comm_platform_linkaddress_toext(unsigned char *pExt, RT_LINKADDRESS LinkAddr)
{
    rt_ip_ip2string((char *)pExt, LinkAddr.Addr[0]);
    return RT_RESULT_OK;
}

RT_RESULT MEDIUS_COMMPLAT_SECTION(rt_comm_platform_linkaddress_toint) rt_comm_platform_linkaddress_toint(RT_LINKADDRESS *pLinkAddr, unsigned char *pExt)
{
    pLinkAddr->Addr[0] = rt_ip_string2ip((char *)pExt);
    return RT_RESULT_OK;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_startup);

void MEDIUS_COMMPLAT_SECTION(rt_comm_platform_shutdown) rt_comm_platform_shutdown(void)
{
    sceBLibnetTerminate(mediusCommInetClient, mediusCommInetBuffer);
    if (sceLibnetUnregisterHandler(mediusCommInetClient, mediusCommInetBuffer) >= 0) {
        sceLibnetTerminate(mediusCommInetClient);
        mediusCommPlatformInterfaceId = -1;
        mediusCommPlatformInitialized = 0;
    }
}

RT_RESULT MEDIUS_COMMPLAT_SECTION(rt_comm_platform_update) rt_comm_platform_update(void)
{
    sceBInetUpdate(mediusCommInetClient);
    return RT_RESULT_OK;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_create);

int MEDIUS_COMMPLAT_SECTION(rt_comm_platform_destroy) rt_comm_platform_destroy(RT_COMM_INTERFACE_ID IID)
{
    if (mediusCommPlatformInitialized != 0 && IID >= 0) {
        sceBInetClose(mediusCommInetClient, mediusCommInetBuffer, IID, 500);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_send_to);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_vsend);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_vsend_to);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_send_echo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_receive);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_receive_from);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_receive_echo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_get_avail_bytes_to_read);

RT_RESULT MEDIUS_COMMPLAT_SECTION(rt_comm_platform_get_local_ip) rt_comm_platform_get_local_ip(RT_LINKADDRESS *pLinkAddr)
{
    if (!mediusCommPlatformInitialized) return RT_NOT_INITIALIZED;
    pLinkAddr->Addr[0] = gLocalIP;
    return RT_RESULT_OK;
}

RT_RESULT MEDIUS_COMMPLAT_SECTION(rt_comm_platform_get_broadcast_ip) rt_comm_platform_get_broadcast_ip(RT_LINKADDRESS *pLinkAddr)
{
    if (!mediusCommPlatformInitialized) return RT_NOT_INITIALIZED;
    pLinkAddr->Addr[0] = mediusCommBroadcastIP;
    return RT_RESULT_OK;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_get_host_by_name);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_get_remote_ip);

RT_RESULT MEDIUS_COMMPLAT_SECTION(rt_comm_platform_display_state) rt_comm_platform_display_state(void)
{
    if (!mediusCommPlatformInitialized) return RT_NOT_INITIALIZED;
    if (sceBInetDisplayLibnetbState(mediusCommInetClient) != 0) return RT_COMM_ERROR;
    return RT_RESULT_OK;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_is_connected);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_wait_for_interface_startup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_get_local_ip_from_stack);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_get_broadcast_ip_from_stack);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/ps2/scei/rt_comm_platform", rt_comm_platform_get_dns_servers);
