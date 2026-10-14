#include "CMemoryContextBase.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SVFileDownloadQueue_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVFileDownloadQueue.h"
#include "SVTagModule.h"
#include "SVOString.h"
#include "CError.h"
#include <string.h>

extern "C" {
extern char svoFileDownloadQueueSource[];
CMemoryContextBaseState *GetMemoryContext(void);
void allocateMemoryForEntries(FileDownloadQueueState *queue);
void *FileDownloadQueueNew(unsigned int size) __asm__("operator.new___dupe14");
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoFileDownloadQueueSource[];
void * SVFileDownloadQueueoperator_new___dupe14(unsigned int size) __asm__("operator.new___dupe14");

}
extern "C" {
void reset___dupe3(FileDownloadEntryState *);
}
#define SECTION(name) __attribute__((section(".svo_SVFileDownloadQueue_" #name)))

SECTION(FileDownloadEntry) void FileDownloadEntry(FileDownloadEntryState *entry)
{
    entry->m_lookupStr = 0;
    entry->m_valueStr = 0;
}

SECTION(FreeResources___dupe53) void FreeResources___dupe53(FileDownloadEntryState *entry)
{
    CMemoryContextBaseState *memory = GetMemoryContext();
    if (entry->m_lookupStr) {
        svFreeSafe(memory, entry->m_lookupStr);
        entry->m_lookupStr = 0;
    }
    if (entry->m_valueStr) {
        svFreeSafe(memory, entry->m_valueStr);
        // Retail clears lookup twice and leaves the freed value pointer intact.
        entry->m_lookupStr = 0;
    }
}

SECTION(GetValueStr___dupe2) char *GetValueStr___dupe2(FileDownloadEntryState *entry)
{
    if (!entry->m_valueStr) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x2A);
    return entry->m_valueStr;
}

SECTION(GetNameStr) char *GetNameStr(FileDownloadEntryState *entry)
{
    if (!entry->m_lookupStr) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x30);
    return entry->m_lookupStr;
}

SECTION(matchesMyLookup___dupe2) int matchesMyLookup___dupe2(FileDownloadEntryState *entry, char *lookup)
{
    if (!lookup) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x36);
    return strcmp(lookup, entry->m_lookupStr) == 0;
}

void setFileDownloadProps(FileDownloadEntryState *entry, char *lookup, char *value);
extern "C" SECTION(setFileDownloadProps) void setFileDownloadProps(FileDownloadEntryState *entry, char *lookup, char *value)
{
    if (!entry->m_lookupStr || !entry->m_valueStr) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x3D);
    if (strlen(lookup) > 31 || strlen(value) > 256) {
        SetErrorCode(30);
        __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x44);
    }
    if (!lookup || !value) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x48);
    svstrncpy(entry->m_lookupStr, lookup, strlen(lookup) + 1);
    svstrncpy(entry->m_valueStr, value, strlen(value) + 1);
}

SECTION(allocateMemory) void allocateMemory(FileDownloadEntryState *entry)
{
    if (entry->m_lookupStr || entry->m_valueStr) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x50);
    CMemoryContextBaseState *memory = GetMemoryContext();
    entry->m_lookupStr = (char *)svAllocSafe(memory, 0x20, 0, 0x52, svoFileDownloadQueueSource);
    entry->m_valueStr = (char *)svAllocSafe(memory, 0x101, 0, 0x53, svoFileDownloadQueueSource);
}

SECTION(reset___dupe3) void reset___dupe3(FileDownloadEntryState *entry)
{
    if (!entry->m_lookupStr || !entry->m_valueStr) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x58);
    memset(entry->m_lookupStr, 0, 0x20);
    memset(entry->m_valueStr, 0, 0x101);
}

SECTION(isEmpty) int isEmpty(FileDownloadEntryState *entry)
{
    return entry->m_valueStr[0] == '\0';
}

void *FileDownloadQueueNew(unsigned int size);
extern "C" SECTION(operator.new___dupe14) void * SVFileDownloadQueueoperator_new___dupe14(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x6E, svoFileDownloadQueueSource);
}

SECTION(FileDownloadQueue) void FileDownloadQueue(FileDownloadQueueState *queue)
{
    FileDownloadEntryState *entry = queue->m_entries;
    int i = 4;
    do {
        FileDownloadEntry(entry);
        entry++;
    } while (--i != -1);
    memset(queue->m_entries, 0, 0x28);
    allocateMemoryForEntries(queue);
    return;
}

SECTION(allocateMemoryForEntries) void allocateMemoryForEntries(FileDownloadQueueState *queue)
{
    for (int i = 0; i < 5; ++i) {
        allocateMemory(&queue->m_entries[i]);
        reset___dupe3(&queue->m_entries[i]);
    }
}

SECTION(add___dupe2) void add___dupe2(FileDownloadQueueState *queue, char *lookup, char *value)
{
    if (!lookup || !value) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x8F);
    for (int i = 0; i < 5; ++i) {
        FileDownloadEntryState *entry = &queue->m_entries[i];
        matchesMyLookup___dupe2(entry, lookup); // Retail ignores the result.
        if (isEmpty(entry)) {
            setFileDownloadProps(entry, lookup, value);
            return;
        }
    }
    __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xA5);
}

char *find___dupe2(FileDownloadQueueState *queue, char *lookup);
extern "C" SECTION(find___dupe2) char *find___dupe2(FileDownloadQueueState *queue, char *lookup)
{
    if (!lookup) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xAC);
    FileDownloadEntryState *entry = queue->m_entries;
    for (int i = 0; i < 5; i++, entry++) {
        if (matchesMyLookup___dupe2(entry, lookup)) return GetValueStr___dupe2(entry);
    }
    return 0;
}

SECTION(FreeResources___dupe54) void FreeResources___dupe54(FileDownloadQueueState *queue)
{
    for (int i = 0; i < 5; ++i) FreeResources___dupe53(&queue->m_entries[i]);
}

void GetNextEntry(FileDownloadQueueState *queue, char *path, int pathSize, char *id, int idSize);
extern "C" SECTION(GetNextEntry) void GetNextEntry(FileDownloadQueueState *queue, char *path, int pathSize, char *id, int idSize)
{
    int index = 0;
    for (int i = 0; i < 5; ++i) {
        if (strlen(GetValueStr___dupe2(&queue->m_entries[i]))) { index = i; break; }
    }
    FileDownloadEntryState *entry = &queue->m_entries[index];
    char *value = GetValueStr___dupe2(entry);
    if (pathSize < (int)strlen(value)) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xD5);
    svstrncpy(path, value, pathSize);
    char *name = GetNameStr(entry);
    if (idSize < (int)strlen(name)) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xDC);
    svstrncpy(id, name, idSize);
    reset___dupe3(entry);
}

SECTION(HasEntries) int HasEntries(FileDownloadQueueState *queue)
{
    for (int i = 0; i < 5; ++i)
        if (strlen(GetValueStr___dupe2(&queue->m_entries[i]))) return 1;
    return 0;
}

}
