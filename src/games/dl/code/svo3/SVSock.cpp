#include "CMemoryContextBase.h"
#include "SVTagModule.h"
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoSockSource[];
void * SVSockoperator_new___dupe9(unsigned int size, CMemoryContextBaseState *memory) __asm__("operator.new___dupe9");

}
#define SECTION(name) __attribute__((section(".svo_SVSock_" #name)))
#include "common.h"
// Keep unreplaced assembly in its original function slots.

// Retain the unresolved wrapper at its original address.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_sock_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVSock.h"

extern "C" const unsigned int svoSockVtable[];

__attribute__((section(".svo_sock_SVSock"))) const void * SVSock(
    SVSockState *socket, CMemoryContextBaseState *memory)
{
    socket->m_pMemoryContext = memory;
    socket->vtable = svoSockVtable;
    socket->m_errNo = 0;
    return svoSockVtable;
}

extern "C" char svoSockSource[];

// Recovered C currently emits 0x34 bytes for this 0x30-byte slot.
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVSock", operator.new___dupe9);

__attribute__((section(".svo_sock_SVSockDelete"))) void SVSockDelete(SVSockState *socket)
{
    svFreeSafe(socket->m_pMemoryContext, socket);
}
