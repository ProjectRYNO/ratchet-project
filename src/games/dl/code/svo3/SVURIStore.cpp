#include "common.h"
// Retain the unresolved wrapper at its original address.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_uri_store_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVURIStore.h"
#include "CMemoryContextBase.h"
#include "SVOString.h"
#include <string.h>

extern "C" {
extern char svoURIStoreSource[];
extern char svoURIStoreDelimiter[];
extern SVTagModuleState *svoRedirectTagModuleInstance;
CMemoryContextBaseState *GetMemoryContext();
}
#define STORE_SECTION(name) __attribute__((section(".svo_uri_store_" #name)))

void STORE_SECTION(FreeResources___dupe43) FreeResources___dupe43(SVTagModuleState *module)
{
    if (svoRedirectTagModuleInstance) {
        svoRedirectTagModuleInstance->vtable->destroy(svoRedirectTagModuleInstance, 3);
        svoRedirectTagModuleInstance = 0;
    }
}

void STORE_SECTION(URIEntry) URIEntry(URIEntryState *entry)
{
    entry->m_valueStr = 0;
    entry->m_lookupStr = 0;
}

void STORE_SECTION(FreeResources___dupe44) FreeResources___dupe44(URIEntryState *entry)
{
    CMemoryContextBaseState *memory = GetMemoryContext();
    if (entry->m_lookupStr) svFreeSafe(memory, entry->m_lookupStr);
    if (entry->m_valueStr) svFreeSafe(memory, entry->m_valueStr);
    // Retail does not clear these pointers after freeing them.
}

STORE_SECTION(GetValueStr) char *GetValueStr(URIEntryState *entry)
{
    if (!entry->m_valueStr) __SVO_Assert_Handler(svoURIStoreSource, 0x24);
    return entry->m_valueStr;
}

int STORE_SECTION(matchesMyLookup) matchesMyLookup(URIEntryState *entry, char *lookup)
{
    if (!lookup) __SVO_Assert_Handler(svoURIStoreSource, 0x31);
    return strcmp(lookup, entry->m_lookupStr) == 0;
}

void STORE_SECTION(setURIProps) setURIProps(URIEntryState *entry, char *lookup, char *value)
{
    char *sourceFile = svoURIStoreSource;
    // Inspect both pointer words together to keep this body in its retail slot.
    if ((unsigned int)entry->m_lookupStr | (unsigned int)entry->m_valueStr) __SVO_Assert_Handler(sourceFile, 0x38);
    CMemoryContextBaseState *memory = GetMemoryContext();
    entry->m_lookupStr = (char *)svAllocSafe(memory, (unsigned int)strlen(lookup) + 1, 0, 0x3A, sourceFile);
    entry->m_valueStr = (char *)svAllocSafe(memory, (unsigned int)strlen(value) + 1, 0, 0x3B, sourceFile);
    // The input assertion comes after allocation in retail.
    if (!lookup || !value) __SVO_Assert_Handler(sourceFile, 0x3E);
    svstrncpy(entry->m_lookupStr, lookup, (unsigned int)strlen(lookup) + 1);
    svstrncpy(entry->m_valueStr, value, (unsigned int)strlen(value) + 1);
}

// Retail tail-jump allocator awaits compact compiler output.
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVURIStore", operator.new___dupe10);

STORE_SECTION(URIStore) void *URIStore(URIStoreState *store)
{
    URIEntryState *entry = store->m_entries;
    for (int i = 63; i >= 0; --i, ++entry) URIEntry(entry);
    void *result = memset(store->m_entries, 0, 0x200);
    store->m_next_URI_index = 0;
    return result;
}

void STORE_SECTION(add) add(URIStoreState *store, char *lookup, char *value)
{
    if (!lookup || !value) __SVO_Assert_Handler(svoURIStoreSource, 0x5A);
    for (int i = 0; i < store->m_next_URI_index; ++i)
        if (matchesMyLookup(&store->m_entries[i], lookup)) return;
    if (store->m_next_URI_index < 64) {
        setURIProps(&store->m_entries[store->m_next_URI_index], lookup, value);
        store->m_next_URI_index = (unsigned int)store->m_next_URI_index + 1;
    } else {
        __SVO_Assert_Handler(svoURIStoreSource, 0x75);
    }
}

STORE_SECTION(find) char *find(URIStoreState *store, char *lookup)
{
    if (store->m_next_URI_index > 64) __SVO_Assert_Handler(svoURIStoreSource, 0x7D);
    if (!lookup) __SVO_Assert_Handler(svoURIStoreSource, 0x7E);
    for (int i = 0; i < store->m_next_URI_index; ++i)
        if (matchesMyLookup(&store->m_entries[i], lookup)) return GetValueStr(&store->m_entries[i]);
    return 0;
}

void STORE_SECTION(FreeResources___dupe45) FreeResources___dupe45(URIStoreState *store)
{
    URIEntryState *entry = store->m_entries;
    for (int i = 63; i >= 0; --i, ++entry) FreeResources___dupe44(entry);
}

int STORE_SECTION(LoadInFromMemory) LoadInFromMemory(URIStoreState *store, char *memory, int size)
{
    // Retail ignores size, consumes at most 64 pairs and mutates the input.
    if (strstr(memory, svoURIStoreDelimiter)) {
        for (int remaining = 64; remaining; --remaining) {
            char *separator = strstr(memory, svoURIStoreDelimiter);
            if (!separator) break;
            *separator = 0;
            char *value = separator + 14;
            char *end = strstr(value, svoURIStoreDelimiter);
            *end = 0;
            char *lookup = memory;
            memory = end + 14;
            add(store, lookup, value);
        }
    }
    return 1;
}
