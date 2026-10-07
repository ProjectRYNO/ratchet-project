#ifndef SVURISTORE_H
#define SVURISTORE_H
#include "SVTagModule.h"

typedef struct { // 0x08
    /* 0x00 */ char *m_lookupStr;
    /* 0x04 */ char *m_valueStr;
} URIEntryState;

typedef struct { // 0x204
    /* 0x000 */ URIEntryState m_entries[64];
    /* 0x200 */ int m_next_URI_index;
} URIStoreState;

extern "C" {
// Redirect module cleanup is grouped in this retail translation unit.
void FreeResources___dupe43(SVTagModuleState *module);
void URIEntry(URIEntryState *entry);
void FreeResources___dupe44(URIEntryState *entry);
char *GetValueStr(URIEntryState *entry);
int matchesMyLookup(URIEntryState *entry, char *lookup);
void setURIProps(URIEntryState *entry, char *lookup, char *value);
void *URIStoreNew(unsigned int size) __asm__("operator.new___dupe10");
void *URIStore(URIStoreState *store);
void add(URIStoreState *store, char *lookup, char *value);
char *find(URIStoreState *store, char *lookup);
void FreeResources___dupe45(URIStoreState *store);
int LoadInFromMemory(URIStoreState *store, char *memory, int size);
}
#endif
