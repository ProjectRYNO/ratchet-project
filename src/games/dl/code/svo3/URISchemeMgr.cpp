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

SCHEME_SECTION(IURISchemeProvider) void IURISchemeProvider(IURISchemeProviderState *provider)
{
    provider->vtable = &svoURISchemeProviderVtable;
}

void SCHEME_SECTION(_IURISchemeProvider) _IURISchemeProvider(IURISchemeProviderState *provider, unsigned int flags)
{
    provider->vtable = &svoURISchemeProviderVtable;
    if (flags & 1) { __builtin_delete(provider); return; }
}

// Recovered C exceeds the retail tail-call slot; see SVO3.md.
SCHEME_SECTION(Register) int Register(IURISchemeProviderState *provider, char **schemes)
{
    return Register___dupe2(Get(), provider, schemes);
}

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
SCHEME_SECTION(CURISchemeMgr) void *CURISchemeMgr(CURISchemeMgrState *manager)
{
    return memset(manager, 0, 0x40);
}

void SCHEME_SECTION(_CURISchemeMgr) _CURISchemeMgr(CURISchemeMgrState *manager, unsigned int flags)
{
    if (flags & 1) { __builtin_delete(manager); return; }
}

int SCHEME_SECTION(Register___dupe2) Register___dupe2(CURISchemeMgrState *manager, IURISchemeProviderState *provider, char **schemes)
{
    int result = 1;
    if (*schemes) {
        char **list = schemes;
        while (1) {
            char *scheme = *list;
            sProviderEntry *available = 0;
            sProviderEntry *duplicate = 0;
            // A goto loop keeps retail's unreduced entry indexing.
            int i = 0;
        next:
            if (!manager->m_providers[i].provider) {
                available = &manager->m_providers[i]; // Retail deliberately keeps the last vacant slot.
            } else if (manager->m_providers[i].scheme && !strcmp(manager->m_providers[i].scheme, scheme)
                       && manager->m_providers[i].provider == provider) {
                duplicate = &manager->m_providers[i];
            }
            i++;
            if (i < 8) goto next;
            if (duplicate) {
                __SVO_Assert_Handler(svoURISchemeSource, 0x6E);
                result = 0;
            } else if (available) {
                available->scheme = scheme;
                available->provider = provider;
            } else {
                __SVO_Assert_Handler(svoURISchemeSource, 0x79);
                result = 0;
            }
            ++list;
            if (!*list || !result) break;
        }
    }
    return result;
}

void SCHEME_SECTION(DeRegister___dupe2) DeRegister___dupe2(CURISchemeMgrState *manager, IURISchemeProviderState *provider)
{
    int i = 0;
next:
    if (manager->m_providers[i].provider == provider) {
        manager->m_providers[i].provider = 0;
        manager->m_providers[i].scheme = 0;
    }
    i++;
    if (i < 8) goto next;
}

int SCHEME_SECTION(HasProvider) HasProvider(CURISchemeMgrState *manager, char *scheme)
{
    return GetProvider(manager, scheme) != 0;
}

SCHEME_SECTION(GetProvider) IURISchemeProviderState *GetProvider(CURISchemeMgrState *manager, char *scheme)
{
    IURISchemeProviderState *result = 0;
    int i = 0;
next:
    if (manager->m_providers[i].provider && !strcmp(manager->m_providers[i].scheme, scheme))
        result = manager->m_providers[i].provider;
    i++;
    if (i < 8 && !result) goto next;
    return result;
}

SCHEME_SECTION(GetFreeProvider) IURISchemeProviderState *GetFreeProvider(CURISchemeMgrState *manager, char *scheme)
{
    IURISchemeProviderState *result = 0;
    int i = 0;
next:
    if (manager->m_providers[i].provider && !strcmp(manager->m_providers[i].scheme, scheme)) {
        IURISchemeProviderState *provider = manager->m_providers[i].provider;
        if (!provider->vtable->IsBusy(provider)) result = manager->m_providers[i].provider;
    }
    i++;
    if (i < 8 && !result) goto next;
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
    int i = 0;
next:
    manager->m_providers[i].provider = 0;
    manager->m_providers[i].scheme = 0;
    i++;
    if (i < 8) goto next;
    // Retail falls off the end, leaving the last entry address in $2.
}

void SCHEME_SECTION(shutdown___dupe2) shutdown___dupe2(CURISchemeMgrState *manager)
{
    sProviderEntry *entry = manager->m_providers;
    for (int i = 7; i >= 0; --i, ++entry) {
        IURISchemeProviderState *provider = entry->provider;
        if (provider) provider->vtable->freeResources(provider, 1);
    }
}

int SCHEME_SECTION(LoadStatePostGameFromPersistentData___dupe4) LoadStatePostGameFromPersistentData___dupe4(CURISchemeMgrState *manager, SVPersistentData *persist)
{
    int result = 1;
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
