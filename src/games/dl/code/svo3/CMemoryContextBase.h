#ifndef CMEMORYCONTEXTBASE_H
#define CMEMORYCONTEXTBASE_H

struct CMemoryContextBaseState;
typedef struct { // 0x14 (verified vtable prefix)
    /* 0x00 */ void *unknown00;
    /* 0x04 */ void *unknown04;
    /* 0x08 */ void *unknown08;
    /* 0x0C */ void *(*svAlloc)(CMemoryContextBaseState *, unsigned int, unsigned int);
    /* 0x10 */ void (*svFree)(CMemoryContextBaseState *, void *);
} CMemoryContextVtablePrefix;

typedef struct { // 0x34
    /* 0x00 */ int FreeCnt;
    /* 0x04 */ void *memPtr;
    /* 0x08 */ int size;
    /* 0x0C */ char idStr[32];
    /* 0x2C */ int alignSize;
    /* 0x30 */ unsigned int id;
} CMemChunk;

struct CMemoryContextBaseState { // 0x10420
    /* 0x00000 */ int m_TotalBytes;
    /* 0x00004 */ CMemChunk m_memChunks[640];
    /* 0x08204 */ CMemChunk bu_memChunk[640];
    /* 0x10404 */ int m_curMemChunk;
    /* 0x10408 */ int buCnt;
    /* 0x1040C */ int pageBeginHighWaterMark;
    /* 0x10410 */ int m_MaxAllocated;
    /* 0x10414 */ unsigned int m_AllocCounter;
    /* 0x10418 */ unsigned int m_FreeCounter;
    /* 0x1041C */ const CMemoryContextVtablePrefix *vtable;
};

extern "C" {
void _CMemoryContextBase(CMemoryContextBaseState *context, unsigned int flags);
void CMemoryContextBase(CMemoryContextBaseState *context);
void *svAllocSafe(CMemoryContextBaseState *context, unsigned int size,
                  unsigned int align, int line, char *file);
void svFreeSafe(CMemoryContextBaseState *context, void *memory);
void InitMemChunks(CMemoryContextBaseState *context);
void Cleanup(CMemoryContextBaseState *context);
void Init___dupe39(CMemChunk *chunk, int size, void *memory, char *file);
int EnsureCleanBlocks(CMemoryContextBaseState *context);
}

#endif
