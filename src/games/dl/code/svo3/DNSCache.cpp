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
    DNSCacheEntry *end = entry + 8;
    do {
        entry->name[0] = 0;
        memset(entry->rtIP, 0, 8);
        entry->age = -1;
    } while (++entry != end);
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
    DNSCacheEntry *entry = cache->m_entries;
    DNSCacheEntry *end = entry + 8;
    do {
        if (entry->age == -1) {
            if (!available) available = entry;
        } else if (!oldest || oldest->age < entry->age) {
            oldest = entry;
        } else if (!strncmp(entry->name, normalized, 64)) {
            // Retail skips this comparison when selecting a new oldest entry.
            found = entry;
        }
    } while (++entry != end && !found);
    if (!found) {
        found = available ? available : oldest;
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
    DNSCacheEntry *entry = cache->m_entries;
    DNSCacheEntry *end = entry + 8;
    do {
        if (entry->age == -1) {
            if (!available) available = entry;
        } else if (!oldest || oldest->age < entry->age) {
            oldest = entry;
        } else if (!strncmp(entry->name, normalized, 64)) {
            // Retail skips this comparison when selecting a new oldest entry.
            found = entry;
        }
    } while (++entry != end && !found);
    if (!found) {
        found = available ? available : oldest;
        svstrncpy(found->name, normalized, 129);
        memcpy(found->rtIP, address, 8);
    }
    // A hit resets age without replacing the stored address.
    found->age = 0;
}

int DNS_SECTION(CacheRetrieve) CacheRetrieve(DNSCacheState *cache, char *name, void *address)
{
    char normalized[64];
    svstrncpy(normalized, name, 65);
    normalized[63] = 0;
    strlwr(normalized);
    for (int i = 0; i < 8; ++i) {
        DNSCacheEntry *entry = &cache->m_entries[i];
        if (entry->age >= 0 && !strncmp(entry->name, normalized, 128)) {
            memcpy(address, entry->rtIP, 8);
            entry->age = 0;
            return 1;
        }
    }
    return 0;
}

void DNS_SECTION(__tcf_0___dupe2) __tcf_0___dupe2()
{
    // Retail only walks eight entries backwards: no calls or observable stores.
}
