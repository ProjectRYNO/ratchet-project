#include "DnsCache.h"
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
extern int svoRTCommSockSendBufferSize;

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
extern unsigned char m_DNSLookupResponse[136];
extern int svoDNSLookupFinished;
extern int svoDNSLookupResult;
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", addrAsString);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", Connect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", createSVSock);

extern "C" SECTION(dnsLookup) SVAddr *dnsLookup(RTCommSockState *socket, char *hostname, CMemoryContextBaseState *memory, int *success)
{
    const SVSockVtablePrefix *vtable = (const SVSockVtablePrefix *)socket->base.vtable;
    long nonblocking = vtable->GetNonBlocking(&socket->base);
    vtable = (const SVSockVtablePrefix *)socket->base.vtable;
    if (nonblocking) return vtable->dnsLookupNonBlocking(&socket->base, hostname, memory, success);
    return vtable->dnsLookupBlocking(&socket->base, hostname, memory, success);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", dnsLookupBlocking);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", dnsLookupNonBlocking);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", dnsLookupNonBlockingQuery);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", sDNSLookupCB);

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
