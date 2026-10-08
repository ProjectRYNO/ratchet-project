#ifndef SVSOCK_H
#define SVSOCK_H

struct CMemoryContextBaseState;
struct SVSockState { // 0x0C
    /* 0x00 */ int m_errNo;
    /* 0x04 */ CMemoryContextBaseState *m_pMemoryContext;
    /* 0x08 */ const void *vtable;
};

struct SVAddr;
typedef struct { // 0x44 (vtable prefix)
    /* 0x00 */ unsigned char unrecovered00[8];
    /* 0x08 */ void (*destroy)(SVSockState *, unsigned int);
    /* 0x0C */ SVAddr *(*dnsLookup)(SVSockState *socket, char *hostname, CMemoryContextBaseState *memory, int *complete);
    /* 0x10 */ SVAddr *(*dnsLookupBlocking)(SVSockState *, char *, CMemoryContextBaseState *, int *);
    /* 0x14 */ SVAddr *(*dnsLookupNonBlocking)(SVSockState *, char *, CMemoryContextBaseState *, int *);
    /* 0x18 */ long (*dnsLookupUpdate)(SVSockState *socket, SVAddr **address);
    /* 0x1C */ unsigned char unrecovered1C[8];
    /* 0x24 */ long (*Connect)(SVSockState *, SVAddr *, int);
    /* 0x28 */ long (*isConnected)(SVSockState *socket);
    /* 0x2C */ long (*Send)(SVSockState *, char *, int, unsigned long *);
    /* 0x30 */ long (*Recv)(SVSockState *, char *, int, int *, int *);
    /* 0x34 */ long (*Close)(SVSockState *socket, int force);
    /* 0x38 */ void (*SetNonBlocking)(SVSockState *, int);
    /* 0x3C */ long (*GetNonBlocking)(SVSockState *);
    /* 0x40 */ void (*setSynchronous)(SVSockState *, int);
} SVSockVtablePrefix;

extern "C" const void *SVSock(SVSockState *socket, CMemoryContextBaseState *memory);
extern "C" {
void *SVSockNew(unsigned int size, CMemoryContextBaseState *memory) __asm__("operator.new___dupe9");
void SVSockDelete(SVSockState *socket) __asm__("operator.delete___dupe8");
}
#endif
