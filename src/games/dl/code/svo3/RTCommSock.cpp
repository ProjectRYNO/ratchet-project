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

#include "RTCommSock.h"

extern "C" {
extern int svoRTCommSockSendBufferSize;

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", BufferHasEndSVMLTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", Close);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", Connect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", createSVSock);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", dnsLookup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", dnsLookupBlocking);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", dnsLookupNonBlocking);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", dnsLookupNonBlockingQuery);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", Recv);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", RTCommSock);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", sDNSLookupCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", Send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RTCommSock", WaitForConnect);
