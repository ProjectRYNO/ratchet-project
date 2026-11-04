#include "common.h"

#define MEDIUS_LIBNET_SECTION(name) __attribute__((section(".medius_libnet_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_libnet_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct LibnetClient {
    char pad[0x30];
    int size;
} LibnetClient;

int strlen(const char *);
char *strcpy(char *, const char *);
int CallRpc(LibnetClient *cd, int fno, void *buf, int ssize, int rsize);
int MemcpyD(LibnetClient *cd, unsigned int *net_buf, int offset, void *src, int size);
int MemcpyS(LibnetClient *cd, void *dst, unsigned int *net_buf, int offset, int size);
int GetInterfaceID(LibnetClient *cd, unsigned int *net_buf, int *if_id, int n);

int scePrintf(const char *, ...);
int sceSifMCallRpc(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void *end_func, void *end_para);

int MEDIUS_LIBNET_SECTION(CallRpc) CallRpc(LibnetClient *cd, int fno, void *buf, int ssize, int rsize)
{
    int bs;
    ssize = (ssize + 63) & ~63;
    rsize = (rsize + 63) & ~63;
    bs = cd->size;
    if (bs < ssize || bs < rsize) {
        scePrintf("[fatal error] insufficient buffer size in Libnet
");
        scePrintf("(fno=%d, ssize=%d, rsize=%d, buffer=%d)
", fno, ssize, rsize, bs);
        return -0x21F;
    }
    return sceSifMCallRpc(cd, fno, 0, buf, ssize, buf, rsize, 0, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", MemcpyD);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", MemcpyS);

int MEDIUS_LIBNET_SECTION(StrcpyD) StrcpyD(LibnetClient *cd, unsigned int *net_buf, int offset, char *src)
{
    int avail = cd->size - offset * 4;
    int len;
    if (src == 0)
        return 0;
    len = strlen(src) + 1;
    if (len < 0)
        return -0x21F;
    if (avail < len)
        return -0x21F;
    strcpy((char *)net_buf + offset * 4, src);
    return len;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", sceInetName2Address);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", func_01E9BA60);

int MEDIUS_LIBNET_SECTION(sceInetCreate) sceInetCreate(LibnetClient *cd, unsigned int *net_buf, void *param)
{
    int ret;
    if ((ret = MemcpyD(cd, net_buf, 1, param, 0x40)) < 0)
        return ret;
    if (CallRpc(cd, 1, net_buf, 0x44, 4) < 0)
        return -0x21E;
    return net_buf[0] ? net_buf[0] : -0x21C;
}

int MEDIUS_LIBNET_SECTION(sceInetOpen) sceInetOpen(LibnetClient *cd, unsigned int *net_buf, int cid, int ms)
{
    net_buf[0] = cid;
    net_buf[1] = ms;
    if (CallRpc(cd, 2, net_buf, 8, 4) < 0)
        return -0x21E;
    return net_buf[0];
}

int MEDIUS_LIBNET_SECTION(sceInetClose) sceInetClose(LibnetClient *cd, unsigned int *net_buf, int cid, int ms)
{
    net_buf[0] = cid;
    net_buf[1] = ms;
    if (CallRpc(cd, 3, net_buf, 8, 4) < 0)
        return -0x21E;
    return net_buf[0];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", sceInetRecv);

int MEDIUS_LIBNET_SECTION(sceInetSend) sceInetSend(LibnetClient *cd, unsigned int *net_buf, int cid, void *ptr, int count, int *pflags, int ms)
{
    int ret;
    net_buf[0] = cid;
    if (pflags)
        net_buf[1] = *pflags;
    else
        net_buf[1] = 0;
    net_buf[3] = ms;
    net_buf[2] = count;
    if ((ret = MemcpyD(cd, net_buf, 4, ptr, count)) < 0)
        return ret;
    if (CallRpc(cd, 5, net_buf, count + 16, 8) < 0)
        return -0x21E;
    if (pflags)
        *pflags = net_buf[1];
    return net_buf[0];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", func_01E9BCE0);

int MEDIUS_LIBNET_SECTION(sceInetAbort) sceInetAbort(LibnetClient *cd, unsigned int *net_buf, int cid, int flags)
{
    net_buf[0] = cid;
    net_buf[1] = flags;
    if (CallRpc(cd, 15, net_buf, 8, 4) < 0)
        return -0x21E;
    return net_buf[0];
}

int MEDIUS_LIBNET_SECTION(sceInetControl) sceInetControl(LibnetClient *cd, unsigned int *net_buf, int cid, int code, void *ptr, int len)
{
    int ret;
    net_buf[0] = cid;
    net_buf[1] = code;
    net_buf[2] = len;
    if ((ret = MemcpyD(cd, net_buf, 3, ptr, len)) < 0)
        return ret;
    if (CallRpc(cd, 19, net_buf, len + 12, len + 12) < 0)
        return -0x21E;
    if ((ret = MemcpyS(cd, ptr, net_buf, 3, len)) < 0)
        return ret;
    return net_buf[0];
}

int MEDIUS_LIBNET_SECTION(sceInetGetInterfaceList) sceInetGetInterfaceList(LibnetClient *cd, unsigned int *net_buf, int *interface_id_list, int n)
{
    int ret;
    net_buf[0] = n;
    if (CallRpc(cd, 8, net_buf, 4, n * 4 + 4) < 0)
        return -0x21E;
    if ((ret = net_buf[0]) < 0)
        return ret;
    if ((ret = MemcpyS(cd, interface_id_list, net_buf, 1, ret * 4)) < 0)
        return ret;
    return net_buf[0];
}

int MEDIUS_LIBNET_SECTION(sceInetInterfaceControl) sceInetInterfaceControl(LibnetClient *cd, unsigned int *net_buf, int interface_id, int code, void *ptr, int len)
{
    int ret;
    net_buf[0] = interface_id;
    net_buf[1] = code;
    net_buf[2] = len;
    if ((ret = MemcpyD(cd, net_buf, 3, ptr, len)) < 0)
        return ret;
    if (CallRpc(cd, 9, net_buf, len + 12, len + 12) < 0)
        return -0x21E;
    if ((ret = MemcpyS(cd, ptr, net_buf, 3, len)) < 0)
        return ret;
    return net_buf[0];
}

int MEDIUS_LIBNET_SECTION(sceInetGetNameServers) sceInetGetNameServers(LibnetClient *cd, unsigned int *net_buf, void *addr, int n)
{
    int ret;
    net_buf[0] = n;
    if (CallRpc(cd, 11, net_buf, 4, n * 16 + 4) < 0)
        return -0x21E;
    if ((ret = net_buf[0]) < 0)
        return ret;
    if ((ret = MemcpyS(cd, addr, net_buf, 1, ret * 16)) < 0)
        return ret;
    return net_buf[0];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", func_01E9BFB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", sceLibnetInitialize);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", sceLibnetTerminate);

int MEDIUS_LIBNET_SECTION(sceLibnetRegisterHandler) sceLibnetRegisterHandler(LibnetClient *cd, unsigned int *net_buf)
{
    if (CallRpc(cd, 30, net_buf, 0, 4) < 0)
        return -0x21E;
    return net_buf[0];
}

int MEDIUS_LIBNET_SECTION(sceLibnetUnregisterHandler) sceLibnetUnregisterHandler(LibnetClient *cd, unsigned int *net_buf)
{
    if (CallRpc(cd, 31, net_buf, 0, 4) < 0)
        return -0x21E;
    return net_buf[0];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", func_01E9C1B0);

int MEDIUS_LIBNET_SECTION(WaitInterface) WaitInterface(LibnetClient *cd, unsigned int *net_buf, int *if_id, int n, int fno)
{
    int i;
    if (CallRpc(cd, fno, net_buf, 0, n * 4 + 4) < 0)
        return -0x21E;
    for (i = 0; i < n; i++)
        if_id[i] = net_buf[i + 1];
    return net_buf[0];
}

int MEDIUS_LIBNET_SECTION(WaitInterfaceStarted) WaitInterfaceStarted(LibnetClient *cd, unsigned int *net_buf, int *if_id, int n)
{
    return WaitInterface(cd, net_buf, if_id, n, 0x22);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", GetInterfaceID);

int MEDIUS_LIBNET_SECTION(GetMyAddress) GetMyAddress(LibnetClient *cd, unsigned int *net_buf, int if_id, void *addr)
{
    return sceInetInterfaceControl(cd, net_buf, if_id, 9, addr, 16);
}

int MEDIUS_LIBNET_SECTION(WaitGetAddressAutoUpIf) WaitGetAddressAutoUpIf(LibnetClient *cd, unsigned int *net_buf, int *if_id, int n, void *addr)
{
    int ret;
    if (GetInterfaceID(cd, net_buf, if_id, n) < 0) {
        if ((ret = WaitInterfaceStarted(cd, net_buf, if_id, n)) < 0)
            return ret;
    }
    if ((ret = GetMyAddress(cd, net_buf, *if_id, addr)) < 0)
        return ret;
    return 0;
}

int MEDIUS_LIBNET_SECTION(WaitGetAddressNoAutoUpIf) WaitGetAddressNoAutoUpIf(LibnetClient *cd, unsigned int *net_buf, int *if_id, int n, void *addr)
{
    int ret;
    if ((ret = WaitInterfaceStarted(cd, net_buf, if_id, n)) < 0)
        return ret;
    if ((ret = GetMyAddress(cd, net_buf, *if_id, addr)) < 0)
        return ret;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", func_01E9C458);

int MEDIUS_LIBNET_SECTION(sceLibnetWaitGetAddress) sceLibnetWaitGetAddress(LibnetClient *cd, unsigned int *net_buf, int *if_id, int n, void *addr, unsigned int flags)
{
    int ret;
    if (flags & 2)
        ret = WaitGetAddressAutoUpIf(cd, net_buf, if_id, n, addr);
    else
        ret = WaitGetAddressNoAutoUpIf(cd, net_buf, if_id, n, addr);
    return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnet", func_01E9C498);
