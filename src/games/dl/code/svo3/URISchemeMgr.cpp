#include "common.h"
// Retain the unresolved wrapper at its original address.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_uri_scheme_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "URISchemeMgr.h"
#include <stdlib.h>
#include <string.h>

extern "C" {
extern CURISchemeMgrState svoURISchemeManager;
extern int svoURISchemeManagerInitialized;
extern char svoURISchemeSource[];
extern const IURISchemeProviderVtablePrefix svoURISchemeProviderVtable;
void __builtin_delete(void *memory);
void __SVO_Assert_Handler(const char *file, int line);
}
#define SCHEME_SECTION(name) __attribute__((section(".svo_uri_scheme_" #name)))

SCHEME_SECTION(IURISchemeProvider) const IURISchemeProviderVtablePrefix *IURISchemeProvider(IURISchemeProviderState *provider)
{
    provider->vtable = &svoURISchemeProviderVtable;
    return &svoURISchemeProviderVtable;
}

void SCHEME_SECTION(_IURISchemeProvider) _IURISchemeProvider(IURISchemeProviderState *provider, unsigned int flags)
{
    provider->vtable = &svoURISchemeProviderVtable;
    if (flags & 1) __builtin_delete(provider);
}

// Recovered C exceeds the retail tail-call slot; see SVO3.md.
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/URISchemeMgr", Register);

void SCHEME_SECTION(DeRegister) DeRegister(IURISchemeProviderState *provider)
{
    DeRegister___dupe2(Get(), provider);
}

SCHEME_SECTION(Get) CURISchemeMgrState *Get()
{
    if (!svoURISchemeManagerInitialized) {
        CURISchemeMgr(&svoURISchemeManager);
        svoURISchemeManagerInitialized = 1;
        atexit(__tcf_0);
    }
    return &svoURISchemeManager;
}

// Recovered C exceeds the retail tail-call slot; see SVO3.md.
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/URISchemeMgr", CURISchemeMgr);

void SCHEME_SECTION(_CURISchemeMgr) _CURISchemeMgr(CURISchemeMgrState *manager, unsigned int flags)
{
    if (flags & 1) __builtin_delete(manager);
}

int SCHEME_SECTION(Register___dupe2) Register___dupe2(CURISchemeMgrState *manager, IURISchemeProviderState *provider, char **schemes)
{
    int result = 1;
    while (*schemes) {
        char *scheme = *schemes;
        sProviderEntry *available = 0;
        sProviderEntry *duplicate = 0;
        for (int i = 0; i < 8; ++i) {
            sProviderEntry *entry = &manager->m_providers[i];
            if (!entry->provider) {
                available = entry; // Retail deliberately keeps the last vacant slot.
            } else if (entry->scheme && !strcmp(entry->scheme, scheme) && entry->provider == provider) {
                duplicate = entry;
            }
        }
        if (duplicate) {
            result = 0;
            __SVO_Assert_Handler(svoURISchemeSource, 0x6E);
        } else if (available) {
            available->scheme = scheme;
            available->provider = provider;
        } else {
            result = 0;
            __SVO_Assert_Handler(svoURISchemeSource, 0x79);
        }
        ++schemes;
        if (!*schemes || !result) break;
    }
    return result;
}

void SCHEME_SECTION(DeRegister___dupe2) DeRegister___dupe2(CURISchemeMgrState *manager, IURISchemeProviderState *provider)
{
    for (int i = 0; i < 8; ++i) {
        sProviderEntry *entry = &manager->m_providers[i];
        if (entry->provider == provider) {
            entry->provider = 0;
            entry->scheme = 0;
        }
    }
}

int SCHEME_SECTION(HasProvider) HasProvider(CURISchemeMgrState *manager, char *scheme)
{
    return GetProvider(manager, scheme) != 0;
}

SCHEME_SECTION(GetProvider) IURISchemeProviderState *GetProvider(CURISchemeMgrState *manager, char *scheme)
{
    IURISchemeProviderState *result = 0;
    for (int i = 0; i < 8 && !result; ++i) {
        sProviderEntry *entry = &manager->m_providers[i];
        if (entry->provider && !strcmp(entry->scheme, scheme)) result = entry->provider;
    }
    return result;
}

SCHEME_SECTION(GetFreeProvider) IURISchemeProviderState *GetFreeProvider(CURISchemeMgrState *manager, char *scheme)
{
    IURISchemeProviderState *result = 0;
    for (int i = 0; i < 8 && !result; ++i) {
        sProviderEntry *entry = &manager->m_providers[i];
        if (entry->provider && !strcmp(entry->scheme, scheme)) {
            IURISchemeProviderState *provider = entry->provider;
            if (!provider->vtable->IsBusy(provider)) result = entry->provider;
        }
    }
    return result;
}

SCHEME_SECTION(doRequest___dupe3) IURISchemeProviderState *doRequest___dupe3(CURISchemeMgrState *manager, URIRequestPrefix *request, IRequestListener *listener, void *context)
{
    IURISchemeProviderState *provider = GetFreeProvider(manager, request->scheme);
    if (provider) provider->vtable->doRequest(provider, request, listener, context);
    return provider;
}

SCHEME_SECTION(init___dupe2) sProviderEntry *init___dupe2(CURISchemeMgrState *manager, CMemoryContextBaseState *memory)
{
    for (int i = 0; i < 8; ++i) {
        manager->m_providers[i].scheme = 0;
        manager->m_providers[i].provider = 0;
    }
    return &manager->m_providers[7];
}

void SCHEME_SECTION(shutdown___dupe2) shutdown___dupe2(CURISchemeMgrState *manager)
{
    sProviderEntry *entry = manager->m_providers;
    for (int i = 7; i >= 0; --i, ++entry) {
        IURISchemeProviderState *provider = entry->provider;
        if (provider) provider->vtable->freeResources(provider, 1);
    }
}

long SCHEME_SECTION(LoadStatePostGameFromPersistentData___dupe4) LoadStatePostGameFromPersistentData___dupe4(CURISchemeMgrState *manager, SVPersistentData *persist)
{
    long result = 1;
    sProviderEntry *entry = manager->m_providers;
    for (int i = 0; i < 8 && result; ++i, ++entry) {
        IURISchemeProviderState *provider = entry->provider;
        if (provider) result = provider->vtable->LoadStatePostGameFromPersistentData(provider, persist);
    }
    return result;
}

void SCHEME_SECTION(__tcf_0) __tcf_0()
{
    _CURISchemeMgr(&svoURISchemeManager, 2);
}
