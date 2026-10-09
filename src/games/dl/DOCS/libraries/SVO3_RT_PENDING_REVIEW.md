# RTCommSock candidates pending automatic approval review

Date: 2026-10-08. The user subsequently approved resuming this work. All seven
functions below are now integrated in `RTCommSock.cpp`, and the verified header
types are present. RTCommSock is assembly-free. See SVO3_HANDOFF.md for current
build/audit results; byte matching and gameplay validation remain unfinished.
The candidate measurements and automatic rejection below are historical evidence.

## Evidence and scope

Ghidra program: `/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf.moose`, with every address below explicitly selected. Pseudocode was checked against the retail split instructions and `deadlocked-proto-decomp/svo3/RTCommSock.cpp`. `dltypes.txt` provides the address, lookup-parameter, channel-options and returned-address layouts at lines 21890, 23692-23729 and 31996-32067. Prototype names are evidence; retail instructions determine behavior.

All seven candidates compiled with the existing object's EE GCC 3.2.3 options. The scratch object has only the seven named function sections, no replacement machine words and no slot changes. Equality with a slot size is a fit, not a byte-matching claim. These routines have not had behavior tests or a final linked-ELF audit.

| Function | Retail address | Slot bytes | Compiled bytes |
| --- | --- | --- | --- |
| `createSVSock` | `0x1ef4ddc` | `0x88` | `0x88` |
| `dnsLookupBlocking` | `0x1ef4f40` | `0x11c` | `0x110` |
| `sDNSLookupCB` | `0x1ef505c` | `0xcc` | `0x8c` |
| `dnsLookupNonBlockingQuery` | `0x1ef5128` | `0x98` | `0x90` |
| `dnsLookupNonBlocking` | `0x1ef51c0` | `0x168` | `0x168` |
| `addrAsString` | `0x1ef5330` | `0x58` | `0x3c` |
| `Connect` | `0x1ef5388` | `0x1c0` | `0x18c` |

## Validation actually run

From `/ProjectRYNO/dl` in the owned `projectryno-svo75` container:

```sh
/opt/ps2dev/ee/bin/ee-g++ -c -G0 -Os -ffast-math -fno-exceptions \
  -fno-schedule-insns -fno-reorder-blocks -falign-functions=4 \
  -Icode/include -Icode/svo3 -Wa,-EL -Wa,-no-pad-sections \
  build/svo-library-work/rt-final-candidates.cpp \
  -o build/svo-library-work/rt-final-candidates.o
mips-linux-gnu-nm -S build/svo-library-work/rt-final-candidates.o
```

Both commands passed. The final symbol-size output is the table above. Object disassembly was also inspected while reducing the two nonblocking routines. The callback copies four eight-byte words before storing them, matching the retail copy order while accepting unaligned input. The global response is at `0x0016E4D0`; its known alignment allows an aligned declaration without changing storage. The nonblocking lookup preserves the retail 65-byte copy into its 64-byte hostname field, its asynchronous success-output behavior, and the no-DNS-server update path. `Connect` preserves the address writeback after `rt_comm_create`, option values and allocation error `0x22`.

At the original candidate checkpoint no production source was changed. The
subsequent authorized integration updates source/header, manifest and type inventory;
no new RT global aliases are required. Current validation is in SVO3_HANDOFF.md.

## Automatic review rejection

The integration action was rejected and did not execute. The exact reason was:

> The proposed integration violates the no-slot-widening requirement: scratch symbols show addrAsString, dnsLookupBlocking, sDNSLookupCB, dnsLookupNonBlockingQuery, and Connect are smaller than retail slots but the other candidates are not proven to fit, and no post-integration compile or slot audit is performed before modifying tracked RTCommSock files.

The candidate measurements establish that `createSVSock` and `dnsLookupNonBlocking` also fit, exactly. A post-integration audit has not been performed because integration was rejected. No alternative integration path was attempted after rejection. The parent agent is handling the required user approval; this document preserves reviewable source and evidence rather than authorizing a retry.

Local detailed records, if still present: `build/svo-library-work/rt-final-results.json`, `rt-final-ghidra.json`, `rt-final-types.h`, `rt-final-candidates.cpp`, and `rt-final-candidates.o`. The source below is durable so these ignored build records are not required to resume review.

## Candidate types

These definitions supplement the existing `RTCommSock.h` for the scratch compilation. The scratch-only include guard and include are shown as used. They do not replace the production header.

```cpp
#ifndef RT_FINAL_TYPES_H
#define RT_FINAL_TYPES_H
#include "RTCommSock.h"
typedef struct { // 0x18
    /* 0x00 */ const void *vtable;
    /* 0x04 */ unsigned int padding04;
    /* 0x08 */ unsigned long address[2];
} SVRTCommAddrState;
typedef struct { // 0x08
    /* 0x00 */ unsigned int Addr[2];
} RTLinkAddress;
typedef struct { // 0x10C
    /* 0x000 */ char szHostName[256];
    /* 0x100 */ RTLinkAddress NSServerIP;
    /* 0x108 */ void (*pfCommLookupCB)(const void *);
} RTCommLookupParams;
typedef struct { // 0x10
    /* 0x00 */ int type;
    /* 0x04 */ int maxMsgLen;
    /* 0x08 */ unsigned int nonBlockingConnect;
    /* 0x0C */ unsigned int synchronousReceive;
} RTCommChannelOptions;
typedef struct { // 0x4C (vtable prefix)
    /* 0x00 */ SVSockVtablePrefix base;
    /* 0x44 */ long (*getSynchronous)(RTCommSockState *);
    /* 0x48 */ long (*getErrNo)(RTCommSockState *);
} RTCommSockVtablePrefix;
typedef struct __attribute__((packed)) { // 0x08
    /* 0x00 */ unsigned long value;
} RTUnalignedWord;
#endif
```

## Candidate functions

```cpp
#include "rt-final-types.h"
#include "DnsCache.h"
#include "CError.h"
#include "SVTagModule.h"
#include "SVOString.h"
#include "string.h"
extern "C" {
extern unsigned int svoRTCommSockSendBufferSize;
extern char svoRTCommSockSource[];
extern unsigned char m_DNSLookupResponse[136] __attribute__((aligned(8)));
extern int svoDNSLookupFinished;
extern int svoDNSLookupResult;
void RTCommSock(RTCommSockState *, CMemoryContextBaseState *);
long rt_comm_linkaddress_toext(char *, unsigned long);
long rt_comm_linkaddress_tostr(char *, unsigned long);
long rt_comm_linkaddress_toint(void *, char *);
long rt_comm_get_host_by_name(char *, void *);
long rt_comm_get_host_by_name_nb(RTCommLookupParams *);
long rt_comm_get_dns_servers(void *, unsigned int, int *);
long rt_comm_update();
long rt_comm_create(void **, unsigned long, int, RTCommChannelOptions *);
long rt_memory_allocate(void **, unsigned long);
long rt_circ_buf_create(void *, unsigned int, void *);
long rt_circ_buf_clear(void *);
void sDNSLookupCB(const void *);
}
#define SECTION(name) __attribute__((section(".svo_RTCommSock_" #name)))
extern "C" SECTION(addrAsString) int addrAsString(RTCommSockState *socket, SVAddr *address, char *text, int maxLength)
{
    if (rt_comm_linkaddress_toext(text, ((SVRTCommAddrState *)address)->address[0]))
        __SVO_Assert_Handler(svoRTCommSockSource, 0x137);
    return 1;
}
extern "C" SECTION(createSVSock) SVSockState *createSVSock(CMemoryContextBaseState *memory)
{
    RTCommSockState *socket = (RTCommSockState *)SVSockNew(sizeof(RTCommSockState), memory);
    RTCommSock(socket, memory);
    if (!socket) __SVO_Assert_Handler(svoRTCommSockSource, 0x2F);
    if (((const RTCommSockVtablePrefix *)socket->base.vtable)->getErrNo(socket))
        __SVO_Assert_Handler(svoRTCommSockSource, 0x30);
    return &socket->base;
}
extern "C" SECTION(dnsLookupBlocking) SVAddr *dnsLookupBlocking(RTCommSockState *socket, char *hostname, CMemoryContextBaseState *memory, int *success)
{
    *success = 0;
    if (!hostname || !memory) socket->base.m_errNo = 3;
    if (socket->base.m_errNo) return 0;
    unsigned long address;
    if (svisdigit((signed char)*hostname)) {
        if (rt_comm_linkaddress_toint(&address, hostname)) __SVO_Assert_Handler(svoRTCommSockSource, 0x74);
    } else if (!CacheRetrieve(Get___dupe2(), hostname, &address)) {
        long result = rt_comm_get_host_by_name(hostname, &address);
        char text[32];
        rt_comm_linkaddress_tostr(text, address);
        if (result) return 0;
        CacheStore(Get___dupe2(), hostname, &address);
    }
    *success = 1;
    socket->address = address;
    return (SVAddr *)&socket->addressVtable;
}
extern "C" SECTION(sDNSLookupCB) void sDNSLookupCB(const void *response)
{
    const RTUnalignedWord *source = (const RTUnalignedWord *)response;
    RTUnalignedWord *target = (RTUnalignedWord *)m_DNSLookupResponse;
    for (int i = 0; i < 16; i += 4) {
        unsigned long first = source[i].value;
        unsigned long second = source[i + 1].value;
        unsigned long third = source[i + 2].value;
        unsigned long fourth = source[i + 3].value;
        target[i].value = first;
        target[i + 1].value = second;
        target[i + 2].value = third;
        target[i + 3].value = fourth;
    }
    target[16].value = source[16].value;
    svoDNSLookupFinished = 1;
}
extern "C" SECTION(dnsLookupNonBlockingQuery) int dnsLookupNonBlockingQuery(RTCommSockState *socket, SVAddr **output)
{
    SVRTCommAddrState *address = (SVRTCommAddrState *)*output;
    if (!rt_comm_update() && svoDNSLookupFinished == 1) {
        if (!svoDNSLookupResult) {
            memcpy(address->address, m_DNSLookupResponse, 8);
            DNSCacheState *cache = Get___dupe2();
            CacheStore2(cache, socket->m_szHostnameBeingLookedUp, address->address);
            return 1;
        }
        SetErrorCode(36);
    }
    return 0;
}
extern "C" SECTION(dnsLookupNonBlocking) SVAddr *dnsLookupNonBlocking(RTCommSockState *socket, char *hostname, CMemoryContextBaseState *memory, int *success)
{
    if (!hostname || !memory) socket->base.m_errNo = 3;
    if (socket->base.m_errNo) return 0;
    unsigned long address = 0;
    if (!svisalpha((signed char)*hostname)) {
        if (rt_comm_linkaddress_toint(&address, hostname)) __SVO_Assert_Handler(svoRTCommSockSource, 0xE9);
    } else if (!CacheRetrieve(Get___dupe2(), hostname, &address)) goto lookup;
    *success = 1;
    socket->address = address;
    return (SVAddr *)&socket->addressVtable;
lookup:
    RTCommLookupParams params __attribute__((aligned(8)));
    svstrncpy(params.szHostName, hostname, 0x100);
    params.pfCommLookupCB = sDNSLookupCB;
    svoDNSLookupFinished = 0;
    memset(m_DNSLookupResponse, 0, 0x88);
    unsigned long server;
    int count = 0;
    if (rt_comm_get_dns_servers(&server, 1, &count)) __SVO_Assert_Handler(svoRTCommSockSource, 0x106);
    if (count) {
        memcpy(&params.NSServerIP, &server, 8);
        // Retail passes 65 despite the 64-byte hostname field; preserve its store behavior.
        svstrncpy(socket->m_szHostnameBeingLookedUp, hostname, 0x41);
        if (rt_comm_get_host_by_name_nb(&params)) return 0;
    }
    rt_comm_update();
    return (SVAddr *)&socket->addressVtable;
}
extern "C" SECTION(Connect) int Connect(RTCommSockState *socket, SVAddr *address, int port)
{
    unsigned int nonBlocking = ((const SVSockVtablePrefix *)socket->base.vtable)->GetNonBlocking(&socket->base);
    if (port <= 0) __SVO_Assert_Handler(svoRTCommSockSource, 0x142);
    if (!address) __SVO_Assert_Handler(svoRTCommSockSource, 0x143);
    RTCommChannelOptions options;
    memset(&options, 0, sizeof(options));
    options.maxMsgLen = 0x200;
    options.type = 0;
    options.nonBlockingConnect = nonBlocking;
    long sync = ((const RTCommSockVtablePrefix *)socket->base.vtable)->getSynchronous(socket);
    if (sync == 2) options.synchronousReceive = 1;
    else if (sync == 1) options.synchronousReceive = 0;
    else if (!sync) __SVO_Assert_Handler(svoRTCommSockSource, 0x151);
    else if (sync != 3) __SVO_Assert_Handler(svoRTCommSockSource, 0x160);
    unsigned long ip = ((SVRTCommAddrState *)address)->address[0];
    void *channel = 0;
    long result = rt_comm_create(&channel, ip, port, &options);
    socket->m_rtCommCID = channel;
    ((SVRTCommAddrState *)address)->address[0] = ip;
    if (result) return 0;
    rt_comm_update();
    socket->m_pScratchBuffer = 0;
    if (rt_memory_allocate(&socket->m_pScratchBuffer, svoRTCommSockSendBufferSize)) {
        SetErrorCode(0x22);
        return 0;
    }
    rt_circ_buf_create(socket->m_OutBuffer, svoRTCommSockSendBufferSize, socket->m_pScratchBuffer);
    rt_circ_buf_clear(socket->m_OutBuffer);
    return 1;
}
```
