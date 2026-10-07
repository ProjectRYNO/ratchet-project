#ifndef SVSOCK_H
#define SVSOCK_H

struct CMemoryContextBaseState;
typedef struct { // 0x0C
    /* 0x00 */ int m_errNo;
    /* 0x04 */ CMemoryContextBaseState *m_pMemoryContext;
    /* 0x08 */ const void *vtable;
} SVSockState;

extern "C" const void *SVSock(SVSockState *socket, CMemoryContextBaseState *memory);
extern "C" {
void *SVSockNew(unsigned int size, CMemoryContextBaseState *memory) __asm__("operator.new___dupe9");
void SVSockDelete(SVSockState *socket) __asm__("operator.delete___dupe8");
}
#endif
