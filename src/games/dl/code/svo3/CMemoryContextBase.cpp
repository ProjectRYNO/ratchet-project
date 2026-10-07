#include "CMemoryContextBase.h"
#include "SVOString.h"
#include <string.h>

extern "C" {
extern const CMemoryContextVtablePrefix svoMemoryContextVtable;
extern const char svoMemoryContextSource[];
extern char svoMemoryUnused[];
extern const char svoMemoryNotSet[];
extern const char svoMemoryFreed[];
extern unsigned int svoMemChunkIdCount;
void __SVO_Assert_Handler(const char *file, int line);
void __builtin_delete(void *memory);
}
#define SVO_MEMORY_SECTION(name) __attribute__((section(".svo_memory_" #name)))

void SVO_MEMORY_SECTION(_CMemoryContextBase) _CMemoryContextBase(
    CMemoryContextBaseState *context, unsigned int flags)
{
    context->vtable = &svoMemoryContextVtable;
    Cleanup(context);
    if (flags & 1) __builtin_delete(context);
}

void SVO_MEMORY_SECTION(CMemoryContextBase) CMemoryContextBase(CMemoryContextBaseState *context)
{
    context->vtable = &svoMemoryContextVtable;
    context->pageBeginHighWaterMark = 0;
    context->m_TotalBytes = 0;
    context->m_MaxAllocated = 0;
    context->m_AllocCounter = 0;
    context->m_FreeCounter = 0;
    context->buCnt = 0;
    InitMemChunks(context);
}

SVO_MEMORY_SECTION(svAllocSafe) void *svAllocSafe(CMemoryContextBaseState *context,
    unsigned int size, unsigned int align, int line, char *file)
{
    if (align >= 256) __SVO_Assert_Handler(svoMemoryContextSource, 0x52);
    unsigned int padding = align > 4 ? align : 4;
    void *memory = context->vtable->svAlloc(context, size + padding * 2, align);
    // Retail counts every attempt, including an allocator returning NULL.
    ++context->m_AllocCounter;
    return memory;
}

void SVO_MEMORY_SECTION(svFreeSafe) svFreeSafe(CMemoryContextBaseState *context, void *memory)
{
    context->vtable->svFree(context, memory);
    ++context->m_FreeCounter;
}

void SVO_MEMORY_SECTION(InitMemChunks) InitMemChunks(CMemoryContextBaseState *context)
{
    context->m_curMemChunk = 0;
    CMemChunk *chunk = context->m_memChunks;
    int remaining = 640;
    do {
        Init___dupe39(chunk++, 0, 0, svoMemoryUnused);
    } while (--remaining);
}

void SVO_MEMORY_SECTION(Cleanup) Cleanup(CMemoryContextBaseState *context)
{
    context->m_MaxAllocated = 0;
}

void SVO_MEMORY_SECTION(Init___dupe39) Init___dupe39(
    CMemChunk *chunk, int size, void *memory, char *file)
{
    char shortName[32];
    chunk->memPtr = memory;
    chunk->size = size;
    chunk->FreeCnt = 0;
    memset(shortName, 0, sizeof(shortName));
    // Retail unconditionally starts 30 bytes before the end, even for short names.
    svstrncpy(shortName, file + strlen(file) - 30, sizeof(shortName));
    if ((int)strlen(shortName) >= 32) __SVO_Assert_Handler(svoMemoryContextSource, 0x1DA);
    memset(chunk->idStr, 0, sizeof(chunk->idStr));
    strncpy(chunk->idStr, shortName, 31);
    if (strcmp(chunk->idStr, svoMemoryNotSet) == 0) {
        __SVO_Assert_Handler(svoMemoryContextSource, 0x1E2);
    }
    if (strcmp(shortName, svoMemoryFreed) == 0) {
        chunk->id = ~0U;
    } else {
        chunk->id = svoMemChunkIdCount++;
    }
}

int SVO_MEMORY_SECTION(EnsureCleanBlocks) EnsureCleanBlocks(CMemoryContextBaseState *context)
{
    return 1;
}
