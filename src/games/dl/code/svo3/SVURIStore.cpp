#include "CMemoryContextBase.h"
#include "SVTagModule.h"
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoURIStoreSource[];
void * SVURIStoreoperator_new___dupe10(unsigned int size) __asm__("operator.new___dupe10");

}
#define SECTION(name) __attribute__((section(".svo_uri_store_" #name)))
#include "common.h"
// Keep unreplaced assembly in its original function slots.

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
    entry->m_lookupStr = 0;
    entry->m_valueStr = 0;
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
    if (entry->m_lookupStr || entry->m_valueStr) __SVO_Assert_Handler(svoURIStoreSource, 0x38);
    CMemoryContextBaseState *memory = GetMemoryContext();
    entry->m_lookupStr = (char *)svAllocSafe(memory, strlen(lookup) + 1, 0, 0x3A, svoURIStoreSource);
    entry->m_valueStr = (char *)svAllocSafe(memory, strlen(value) + 1, 0, 0x3B, svoURIStoreSource);
    // The input assertion comes after allocation in retail.
    if (!lookup || !value) __SVO_Assert_Handler(svoURIStoreSource, 0x3E);
    svstrncpy(entry->m_lookupStr, lookup, strlen(lookup) + 1);
    svstrncpy(entry->m_valueStr, value, strlen(value) + 1);
}

// Retail tail-jump allocator awaits compact compiler output.
extern "C" SECTION(operator.new___dupe10) void * SVURIStoreoperator_new___dupe10(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x4A, svoURIStoreSource);
}

STORE_SECTION(URIStore) void *URIStore(URIStoreState *store)
{
    URIEntryState *entry = store->m_entries;
    int i = 63;
    do {
        URIEntry(entry);
        entry++;
    } while (--i != -1);
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
        for (int i = 0; i < 64; i++) {
            char *separator = strstr(memory, svoURIStoreDelimiter);
            char *value = separator + 14;
            if (!separator) break;
            *separator = 0;
            char *end = strstr(value, svoURIStoreDelimiter);
            *end = 0;
            add(store, memory, value);
            memory = end + 14;
        }
    }
    return 1;
}
