#include "common.h"

#define MEDIUS_DMEADDR_SECTION(name) __attribute__((section(".medius_dmeaddr_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dmeaddr_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef unsigned short RT_U2BYTE;
typedef unsigned int RT_U4BYTE;

typedef enum { NetErrorNone = 0, NetErrorInvalidArg = 23 } NetErrorCode;

typedef enum {
    NetAddressNone = 0,
    NetAddressTypeExternal = 1,
    NetAddressTypeInternal = 2,
    NetAddressTypeNATService = 3,
    NetAddressTypeBinaryExternal = 4,
    NetAddressTypeBinaryInternal = 5,
    NetAddressTypeBinaryExternalVport = 6,
    NetAddressTypeBinaryInternalVport = 7,
    NetAddressTypeBinaryNATServices = 8,
    ExtraNetAddressType = -1
} NetAddressType;

typedef struct {
    NetAddressType AddressType;
    char Address[16];
    unsigned int Port;
} NetAddress;

typedef struct {
    RT_U4BYTE Addr[2];
} RT_LINKADDRESS;

extern int rt_comm_linkaddress_toint(RT_LINKADDRESS *pAddr, char *pString);
typedef unsigned char RT_U1BYTE;

typedef struct {
    char Data[16];
} NetAddressBuf;

extern void *memset(void *, int, unsigned int);
extern int rt_comm_linkaddress_toext(char *pString, RT_LINKADDRESS addr);

NetErrorCode MEDIUS_DMEADDR_SECTION(BinaryAddressToNetAddress) BinaryAddressToNetAddress(NetAddress *pNetAddr, NetAddressType Type, RT_U1BYTE *pAddress, RT_U2BYTE Port,
                                       RT_U2BYTE VirtualPort)
{
    NetErrorCode result;
    NetErrorCode err = NetErrorInvalidArg;
    RT_LINKADDRESS addr;

    result = NetErrorNone;
    if (pNetAddr && pAddress) {
        memset(pNetAddr, 0, sizeof(NetAddress));
        pNetAddr->AddressType = Type;
        pNetAddr->Port = Port;
        switch (Type) {
        case NetAddressTypeExternal:
        case NetAddressTypeInternal:
        case NetAddressTypeNATService:
            addr = *(RT_LINKADDRESS *)pAddress;
            rt_comm_linkaddress_toext(pNetAddr->Address, addr);
            break;
        case NetAddressTypeBinaryExternal:
        case NetAddressTypeBinaryInternal:
            *(NetAddressBuf *)pNetAddr->Address = *(NetAddressBuf *)pAddress;
            break;
        case NetAddressTypeBinaryExternalVport:
        case NetAddressTypeBinaryInternalVport:
            *(NetAddressBuf *)pNetAddr->Address = *(NetAddressBuf *)pAddress;
            pNetAddr->Port = (VirtualPort << 16) | Port;
            break;
        case NetAddressNone:
        case NetAddressTypeBinaryNATServices:
        default:
            result = NetErrorInvalidArg;
            break;
        }
        err = result;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeAddress", StringAddressToNetAddress);

NetErrorCode MEDIUS_DMEADDR_SECTION(NetAddressToBinaryAddress) NetAddressToBinaryAddress(NetAddress *pNetAddr, NetAddressType *pType, RT_LINKADDRESS *pBuf,
                                       RT_U2BYTE *pPort, RT_U2BYTE *pVirtualPort)
{
    NetErrorCode result;
    NetErrorCode err = NetErrorInvalidArg;
    NetAddressType type;
    RT_LINKADDRESS addr;

    result = NetErrorNone;
    if (pNetAddr && pType && pBuf && pPort && pVirtualPort) {
        type = pNetAddr->AddressType;
        *pType = type;
        *pPort = pNetAddr->Port;
        *pVirtualPort = 0;
        switch (type) {
        case NetAddressTypeExternal:
        case NetAddressTypeInternal:
        case NetAddressTypeNATService:
            rt_comm_linkaddress_toint(&addr, pNetAddr->Address);
            *pBuf = addr;
            break;
        case NetAddressTypeBinaryExternal:
        case NetAddressTypeBinaryInternal:
            *pBuf = *(RT_LINKADDRESS *)pNetAddr->Address;
            break;
        case NetAddressTypeBinaryExternalVport:
        case NetAddressTypeBinaryInternalVport:
            *pBuf = *(RT_LINKADDRESS *)pNetAddr->Address;
            *pVirtualPort = pNetAddr->Port >> 16;
            break;
        case NetAddressNone:
        case NetAddressTypeBinaryNATServices:
        default:
            result = NetErrorInvalidArg;
            break;
        }
        err = result;
    }
    return err;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeAddress", NetIAddressToStringAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/dme_client/src/DmeAddress", func_01E9F038);
