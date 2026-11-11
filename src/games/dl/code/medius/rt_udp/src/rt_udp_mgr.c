#include "common.h"

#define MEDIUS_UDPMGR_SECTION(name) __attribute__((section(".medius_udpmgr_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_udpmgr_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct {
    unsigned short id;
    unsigned short pad2;
    int a;
    int b;
    int c;
} RT_UDP_MGR_REF;

typedef struct {
    int hChannel;
    RT_UDP_MGR_REF refs[16];
    unsigned int count;
} RT_UDP_MGR;

// rt_udp channel manager state: shared channel and its channel references.
extern RT_UDP_MGR mediusUdpMgr;

void *memset(void *, int, unsigned int);
int rt_udp_create(void *pChannel, void *pParams);

int MEDIUS_UDPMGR_SECTION(rt_udp_mgr_create) rt_udp_mgr_create(int *pParams, int *pOut)
{
    int result;

    if (pParams == 0) {
        return 2;
    }
    memset(&mediusUdpMgr, 0, sizeof(RT_UDP_MGR));
    pParams[9] = 1;
    result = rt_udp_create(&mediusUdpMgr, pParams);
    if (result == 0) {
        *pOut = mediusUdpMgr.hChannel;
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp_mgr", rt_udp_mgr_destroy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp_mgr", rt_udp_mgr_get_channel_ref);

int MEDIUS_UDPMGR_SECTION(rt_udp_mgr_release_channel_ref) rt_udp_mgr_release_channel_ref(unsigned short id)
{
    unsigned int i;

    if (id == 0) {
        return 2;
    }
    for (i = 0; i < 16; i++) {
        if (id == mediusUdpMgr.refs[i].id) {
            memset(&mediusUdpMgr.refs[i], 0, sizeof(RT_UDP_MGR_REF));
            mediusUdpMgr.count--;
            return 0;
        }
    }
    return 2;
}

int MEDIUS_UDPMGR_SECTION(rt_udp_mgr_find_channel_ref) rt_udp_mgr_find_channel_ref(unsigned short id, RT_UDP_MGR_REF **pOut)
{
    unsigned int i;
    unsigned int slot;

    slot = 16;
    if (pOut == 0) {
        return 2;
    }
    *pOut = 0;
    for (i = 0; i < 16; i++) {
        if (id != 0 && id == mediusUdpMgr.refs[i].id) {
            *pOut = &mediusUdpMgr.refs[i];
            return 0;
        }
        if (mediusUdpMgr.refs[i].id != 0 && slot == 16) {
            slot = i;
        }
    }
    if (*pOut == 0 && slot != 16) {
        *pOut = &mediusUdpMgr.refs[slot];
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_udp/src/rt_udp_mgr", func_01EC2610);
