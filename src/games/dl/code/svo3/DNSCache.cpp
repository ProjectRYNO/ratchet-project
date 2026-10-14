#include "DNSCache.h"
#include "SVOString.h"
#include <stdlib.h>
#include <string.h>

extern "C" {
extern DNSCacheState svoDNSCache;
extern int svoDNSCacheInitialized;
extern char svoDNSCacheSource[];
void __SVO_Assert_Handler(const char *file, int line);
char *strlwr(char *text);
}
#define DNS_SECTION(name) __attribute__((section(".svo_dns_" #name)))

DNS_SECTION(Get___dupe2) DNSCacheState *Get___dupe2()
{
    if (!svoDNSCacheInitialized) {
        DNSCache(&svoDNSCache);
        svoDNSCacheInitialized = 1;
        atexit(__tcf_0___dupe2);
    }
    return &svoDNSCache;
}

void DNS_SECTION(DNSCache) DNSCache(DNSCacheState *cache)
{
    DNSCacheEntry *entry = cache->m_entries;
    int i = 7;
    do {
        entry->name[0] = 0;
        memset(entry->rtIP, 0, 8);
        entry->age = -1;
        entry++;
    } while (--i != -1);
}

void DNS_SECTION(CacheStore) CacheStore(DNSCacheState *cache, char *name, const void *address)
{
    if (!name || strlen(name) > 127) __SVO_Assert_Handler(svoDNSCacheSource, 0x1E);
    // Preserve the retail 65-byte copy request into its 64-byte local buffer.
    // Long input can overrun this buffer; malformed-input matching is unfinished.
    char normalized[64];
    svstrncpy(normalized, name, 65);
    normalized[63] = 0;
    strlwr(normalized);
    DNSCacheEntry *available = 0;
    DNSCacheEntry *oldest = 0;
    DNSCacheEntry *found = 0;
    for (int i = 0; i < 8 && !found; i++) {
        if (cache->m_entries[i].age == -1) {
            if (!available) available = &cache->m_entries[i];
        } else if (!oldest || oldest->age < cache->m_entries[i].age) {
            oldest = &cache->m_entries[i];
        } else if (!strncmp(cache->m_entries[i].name, normalized, 64)) {
            // Retail skips this comparison when selecting a new oldest entry.
            found = &cache->m_entries[i];
        }
    }
    if (!found) {
        if (available) found = available;
        else found = oldest;
        svstrncpy(found->name, normalized, 129);
        memcpy(found->rtIP, address, 8);
    }
    // A hit resets age without replacing the stored address.
    found->age = 0;
}

void DNS_SECTION(CacheStore2) CacheStore2(DNSCacheState *cache, char *name, const void *address)
{
    if (!name || strlen(name) > 127) __SVO_Assert_Handler(svoDNSCacheSource, 0x57);
    // Preserve the retail 65-byte copy request into its 64-byte local buffer.
    // Long input can overrun this buffer; malformed-input matching is unfinished.
    char normalized[64];
    svstrncpy(normalized, name, 65);
    normalized[63] = 0;
    strlwr(normalized);
    DNSCacheEntry *available = 0;
    DNSCacheEntry *oldest = 0;
    DNSCacheEntry *found = 0;
    for (int i = 0; i < 8 && !found; i++) {
        if (cache->m_entries[i].age == -1) {
            if (!available) available = &cache->m_entries[i];
        } else if (!oldest || oldest->age < cache->m_entries[i].age) {
            oldest = &cache->m_entries[i];
        } else if (!strncmp(cache->m_entries[i].name, normalized, 64)) {
            // Retail skips this comparison when selecting a new oldest entry.
            found = &cache->m_entries[i];
        }
    }
    if (!found) {
        if (available) found = available;
        else found = oldest;
        svstrncpy(found->name, normalized, 129);
        memcpy(found->rtIP, address, 8);
    }
    // A hit resets age without replacing the stored address.
    found->age = 0;
}

int DNS_SECTION(CacheRetrieve) CacheRetrieve(DNSCacheState *cache, char *name, void *address)
{
    char normalized[64];
    int found = 0;
    svstrncpy(normalized, name, 65);
    normalized[63] = 0;
    strlwr(normalized);
    for (int i = 0; i < 8 && !found; i++) {
        if (cache->m_entries[i].age >= 0 && !strncmp(cache->m_entries[i].name, normalized, 128)) {
            memcpy(address, cache->m_entries[i].rtIP, 8);
            found = 1;
            cache->m_entries[i].age = 0;
        }
    }
    return found;
}

void DNS_SECTION(__tcf_0___dupe2) __tcf_0___dupe2()
{
    // Static array destructor for the eight cache entries; the element destructor is empty.
    if (svoDNSCache.m_entries) {
        DNSCacheEntry *entry = svoDNSCache.m_entries + 8;
        while (entry != svoDNSCache.m_entries) --entry;
    }
}
