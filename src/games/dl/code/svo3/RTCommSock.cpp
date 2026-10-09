#include "DnsCache.h"
#include "SVOString.h"
#include "CError.h"
#include "SVTagModule.h"
#include "RTCommSock.h"
#include "string.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_RTCommSock_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern "C" {
extern unsigned int svoRTCommSockSendBufferSize;

extern "C" {
extern char svoRTCommEndSVML[];
extern char svoRTCommEndXML[];
}
extern "C" {
extern char svoRTCommSockSource[];
extern char svoRTCommSockVtable[];
extern char svoRTCommAddrVtable[];
void SetNonBlocking(RTCommSockState *, int);
long rt_comm_update(void);
long rt_comm_is_connected(void *, int *);
long rt_comm_receive(void *, char *, unsigned int, unsigned int *);
long rt_comm_send(void *, char *, unsigned int, unsigned int *);
long rt_memory_free(void **);
long rt_circ_buf_destroy(void *);
long rt_comm_destroy(void *);
long rt_circ_buf_store(void *, char *, unsigned int);
long rt_circ_buf_get_used_nowrap(void *, unsigned int *);
long rt_circ_buf_get_start_used_ptr(void *, char **);
long rt_circ_buf_free(void *, unsigned int);
long rt_circ_buf_normalize(void *, int);
long BufferHasEndSVMLTag(RTCommSockState *, char *, int);

}
extern "C" {
// Retail storage at 0x0016E4D0 is eight-byte aligned.
extern unsigned char m_DNSLookupResponse[136] __attribute__((aligned(8)));
extern int svoDNSLookupFinished;
extern int svoDNSLookupResult;
}
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

SECTION(unSerializeAddr) void *unSerializeAddr(RTCommSockState *socket, void *data, void *memory)
{
    return 0;
}

SECTION(SetSockSendBufferSize) void SetSockSendBufferSize(int size)
{
    svoRTCommSockSendBufferSize = size;
}

SECTION(SetNonBlocking) void SetNonBlocking(RTCommSockState *socket, int nonBlocking)
{
    socket->m_bNonBlocking = nonBlocking;
}

SECTION(GetNonBlocking) long GetNonBlocking(RTCommSockState *socket)
{
    return socket->m_bNonBlocking;
}

SECTION(setSynchronous) void setSynchronous(RTCommSockState *socket, int synchronous)
{
    socket->m_eSynchronous = synchronous;
}

SECTION(getSynchronous) long getSynchronous(RTCommSockState *socket)
{
    return socket->m_eSynchronous;
}

}

extern "C" SECTION(addrAsString) int addrAsString(RTCommSockState *socket, SVAddr *address, char *text, int maxLength)
{
    if (rt_comm_linkaddress_toext(text, ((SVRTCommAddrState *)address)->address[0]))
        __SVO_Assert_Handler(svoRTCommSockSource, 0x137);
    return 1;
}

extern "C" SECTION(BufferHasEndSVMLTag) long BufferHasEndSVMLTag(RTCommSockState *socket, char *buffer, int length)
{
    int start = length > 1024 ? length - 1024 : 0;
    char *tail = buffer + start;
    if (strstr(tail, svoRTCommEndSVML)) return 1;
    return strstr(tail, svoRTCommEndXML) != 0;
}

extern "C" SECTION(Close) long Close(RTCommSockState *socket, int force)
{
    rt_memory_free(&socket->m_pScratchBuffer);
    rt_circ_buf_destroy(socket->m_OutBuffer);
    rt_comm_destroy(socket->m_rtCommCID);
    rt_comm_update();
    return 1;
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

extern "C" SECTION(createSVSock) SVSockState *createSVSock(CMemoryContextBaseState *memory)
{
    RTCommSockState *socket = (RTCommSockState *)SVSockNew(sizeof(RTCommSockState), memory);
    RTCommSock(socket, memory);
    if (!socket) __SVO_Assert_Handler(svoRTCommSockSource, 0x2F);
    if (((const RTCommSockVtablePrefix *)socket->base.vtable)->getErrNo(socket))
        __SVO_Assert_Handler(svoRTCommSockSource, 0x30);
    return &socket->base;
}

extern "C" SECTION(dnsLookup) SVAddr *dnsLookup(RTCommSockState *socket, char *hostname, CMemoryContextBaseState *memory, int *success)
{
    const SVSockVtablePrefix *vtable = (const SVSockVtablePrefix *)socket->base.vtable;
    long nonblocking = vtable->GetNonBlocking(&socket->base);
    vtable = (const SVSockVtablePrefix *)socket->base.vtable;
    if (nonblocking) return vtable->dnsLookupNonBlocking(&socket->base, hostname, memory, success);
    return vtable->dnsLookupBlocking(&socket->base, hostname, memory, success);
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

extern "C" SECTION(Recv) long Recv(RTCommSockState *socket, char *buffer, int size, int *length, int *finished)
{
    *finished = 0;
    if (rt_comm_update()) __SVO_Assert_Handler(svoRTCommSockSource, 0x225);
    unsigned int received;
    long result = rt_comm_receive(socket->m_rtCommCID, buffer, size, &received);
    *length = received;
    if (result == 0xC356 || BufferHasEndSVMLTag(socket, buffer, received)) {
        *finished = 1;
        return 1;
    }
    if (result) { SetErrorCode(0x15); return 0; }
    return 1;
}

extern "C" SECTION(RTCommSock) void RTCommSock(RTCommSockState *socket, CMemoryContextBaseState *memory)
{
    SVSock(&socket->base, memory);
    socket->base.vtable = svoRTCommSockVtable;
    socket->addressVtable = svoRTCommAddrVtable;
    SetNonBlocking(socket, 1);
    socket->m_rtCommCID = 0;
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

extern "C" SECTION(Send) long Send(RTCommSockState *socket, char *buffer, int length, unsigned long *sent)
{
    void *ring = socket->m_OutBuffer;
    if (rt_circ_buf_store(ring, buffer, length)) {
        *sent = 0;
        SetErrorCode(0x21);
        return 0;
    }
    *sent = (long)length;
    unsigned int used;
    if (rt_circ_buf_get_used_nowrap(ring, &used)) return 0;
    if (!used) {
        if (length > 0) __SVO_Assert_Handler(svoRTCommSockSource, 0x20D);
        return 1;
    }
    char *start = 0;
    if (rt_circ_buf_get_start_used_ptr(ring, &start)) return 1;
    unsigned int count = 0;
    long result = rt_comm_send(socket->m_rtCommCID, start, used, &count);
    *sent = count;
    if (result) return 0;
    rt_circ_buf_free(ring, (unsigned int)*sent);
    rt_circ_buf_normalize(ring, 1);
    if (rt_comm_update()) __SVO_Assert_Handler(svoRTCommSockSource, 0x207);
    return 1;
}

extern "C" SECTION(WaitForConnect) long WaitForConnect(RTCommSockState *socket)
{
    if (rt_comm_update()) return 0;
    int connected;
    long result = rt_comm_is_connected(socket->m_rtCommCID, &connected);
    if (connected == 1 && !result) return 1;
    if (connected || result) {
        SetErrorCode(0x26);
        if (!result) __SVO_Assert_Handler(svoRTCommSockSource, 0x1CA);
    }
    return 0;
}
