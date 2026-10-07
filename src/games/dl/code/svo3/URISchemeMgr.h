#ifndef URISCHEMEMGR_H
#define URISCHEMEMGR_H
#include "CMemoryContextBase.h"

struct IURISchemeProviderState;
struct IRequestListener;
struct SVPersistentData;
typedef struct { // 0x04 (request prefix only)
    /* 0x00 */ char *scheme;
} URIRequestPrefix;

typedef struct { // 0x20 (vtable prefix)
    /* 0x00 */ void *unknown00;
    /* 0x04 */ void *unknown04;
    /* 0x08 */ void *unknown08;
    /* 0x0C */ long (*doRequest)(IURISchemeProviderState *provider, URIRequestPrefix *request, IRequestListener *listener, void *context);
    /* 0x10 */ void *unknown10;
    /* 0x14 */ long (*IsBusy)(IURISchemeProviderState *provider);
    /* 0x18 */ void (*freeResources)(IURISchemeProviderState *provider, int flags);
    /* 0x1C */ long (*LoadStatePostGameFromPersistentData)(IURISchemeProviderState *provider, SVPersistentData *persist);
} IURISchemeProviderVtablePrefix;

struct IURISchemeProviderState { // 0x04
    /* 0x00 */ const IURISchemeProviderVtablePrefix *vtable;
};

typedef struct { // 0x08
    /* 0x00 */ IURISchemeProviderState *provider;
    /* 0x04 */ char *scheme;
} sProviderEntry;

typedef struct { // 0x40
    /* 0x00 */ sProviderEntry m_providers[8];
} CURISchemeMgrState;

extern "C" {
const IURISchemeProviderVtablePrefix *IURISchemeProvider(IURISchemeProviderState *provider);
void _IURISchemeProvider(IURISchemeProviderState *provider, unsigned int flags);
int Register(IURISchemeProviderState *provider, char **schemes);
void DeRegister(IURISchemeProviderState *provider);
CURISchemeMgrState *Get();
void *CURISchemeMgr(CURISchemeMgrState *manager);
void _CURISchemeMgr(CURISchemeMgrState *manager, unsigned int flags);
int Register___dupe2(CURISchemeMgrState *manager, IURISchemeProviderState *provider, char **schemes);
void DeRegister___dupe2(CURISchemeMgrState *manager, IURISchemeProviderState *provider);
int HasProvider(CURISchemeMgrState *manager, char *scheme);
IURISchemeProviderState *GetProvider(CURISchemeMgrState *manager, char *scheme);
IURISchemeProviderState *GetFreeProvider(CURISchemeMgrState *manager, char *scheme);
IURISchemeProviderState *doRequest___dupe3(CURISchemeMgrState *manager, URIRequestPrefix *request, IRequestListener *listener, void *context);
sProviderEntry *init___dupe2(CURISchemeMgrState *manager, CMemoryContextBaseState *memory);
void shutdown___dupe2(CURISchemeMgrState *manager);
long LoadStatePostGameFromPersistentData___dupe4(CURISchemeMgrState *manager, SVPersistentData *persist);
void __tcf_0();
}
#endif
