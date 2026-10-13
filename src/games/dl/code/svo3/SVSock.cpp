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

__attribute__((section(".svo_sock_SVSock"))) SVSockState::SVSockState(CMemoryContextBaseState *memory)
{
    m_pMemoryContext = memory;
    vtable = svoSockVtable;
    m_errNo = 0;
}

extern "C" char svoSockSource[];

__attribute__((section(".svo_sock_operator.new___dupe9"))) void *SVSockoperator_new___dupe9(unsigned int size, CMemoryContextBaseState *memory)
{
    return svAllocSafe(memory, size, 0, 0x18, svoSockSource);
}

__attribute__((section(".svo_sock_SVSockDelete"))) void SVSockDelete(SVSockState *socket)
{
    svFreeSafe(socket->m_pMemoryContext, socket);
}
