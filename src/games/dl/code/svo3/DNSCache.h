#ifndef DNSCACHE_H
#define DNSCACHE_H

typedef struct { // 0x8C
    /* 0x00 */ char name[128];
    /* 0x80 */ unsigned char rtIP[8]; // Unaligned eight-byte retail address.
    /* 0x88 */ int age;
} DNSCacheEntry;

typedef struct { // 0x460
    /* 0x000 */ DNSCacheEntry m_entries[8];
} DNSCacheState;

extern "C" {
DNSCacheState *Get___dupe2();
void DNSCache(DNSCacheState *cache);
void CacheStore(DNSCacheState *cache, char *name, const void *address);
void CacheStore2(DNSCacheState *cache, char *name, const void *address);
int CacheRetrieve(DNSCacheState *cache, char *name, void *address);
void __tcf_0___dupe2();
}
#endif
