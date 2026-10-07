#include "CCookie.h"
#include "SVOString.h"
#include <string.h>

extern "C" {
extern CCookieJar *svoCookieJarInstance;
extern char svoCookieSource[];
extern char svoCookieHeaderPrefix[];
extern char svoCookieSeparator[];
extern char svoCookiePairFormat[];
extern char svoCookieLineEnd[];
extern char svoCookieRequestHeader[];
void __SVO_Assert_Handler(const char *file, int line);
}
#define COOKIE_SECTION(name) __attribute__((section(".svo_cookie_" #name)))

COOKIE_SECTION(getInstance) CCookieJar *getInstance(CMemoryContextBaseState *memory)
{
    if (!svoCookieJarInstance) {
        svoCookieJarInstance = (CCookieJar *)svAllocSafe(memory, 0x7F4, 0, 0x18, svoCookieSource);
        if (!svoCookieJarInstance) __SVO_Assert_Handler(svoCookieSource, 0x19);
        memset(svoCookieJarInstance->m_cookies, 0, 0x7F0);
        svoCookieJarInstance->m_memory = memory;
    }
    return svoCookieJarInstance;
}

int COOKIE_SECTION(setCookie) setCookie(CCookieJar *jar, char *name, char *value)
{
    if (jar->m_cookies[15][126]) __SVO_Assert_Handler(svoCookieSource, 0x4C);
    unsigned int nameLength = strlen(name);
    unsigned int valueLength = strlen(value);
    if (nameLength + valueLength + 2 >= 128) {
        __SVO_Assert_Handler(svoCookieSource, 0x55);
        return 0;
    }
    char *available = 0;
    char *entry = jar->m_cookies[0];
    char *destination = entry + nameLength + 1;
    for (unsigned int i = 0; i < 16; ++i, entry += 127, destination += 127) {
        if (entry[126]) __SVO_Assert_Handler(svoCookieSource, 0x60);
        if (!entry[0] && !available) {
            available = entry;
        } else if (!strcmp(entry, name)) {
            if (!*value) {
                memset(entry, 0, 127);
            } else {
                memset(destination, 0, 126 - nameLength);
                svstrncpy(destination, value, 126 - nameLength);
            }
            return 1;
        }
    }
    if (available) {
        svstrncpy(available, name, 127);
        svstrncpy(available + nameLength + 1, value, 126 - nameLength);
        return 1;
    }
    __SVO_Assert_Handler(svoCookieSource, 0x88);
    return 0;
}

int COOKIE_SECTION(asHeaderString) asHeaderString(CCookieJar *jar, char *header, unsigned int size)
{
    if (jar->m_cookies[15][126]) __SVO_Assert_Handler(svoCookieSource, 0x9D);
    memset(header, 0, size);
    char *cursor = header;
    char *entry = jar->m_cookies[0];
    for (unsigned int i = 0; i < 16; ++i, entry += 127) {
        if (*entry) {
            char *value = strchr(entry, 0) + 1;
            if (!value || !*value) __SVO_Assert_Handler(svoCookieSource, 0xA9);
            char *end = strchr(value, 0);
            unsigned int remaining = size - (cursor - header);
            // Retail checks the pair here, before adding the header/separator.
            if (remaining < (unsigned int)(end - entry + 2)) {
                __SVO_Assert_Handler(svoCookieSource, 0xB0);
                return 0;
            }
            if (cursor == header) {
                svstrncpy(cursor, svoCookieHeaderPrefix, size);
                cursor += 8;
            } else {
                svstrncpy(cursor, svoCookieSeparator, remaining);
                cursor += 2;
            }
            cursor += svsnprintf(cursor, size - (cursor - header), svoCookiePairFormat, entry, value);
        }
    }
    if (cursor != header) svstrncpy(cursor, svoCookieLineEnd, size - (cursor - header));
    return 1;
}

int COOKIE_SECTION(parseSetCookieHeader) parseSetCookieHeader(CCookieJar *jar, char *header)
{
    if (!strncmp(header, svoCookieRequestHeader, 7)) {
        __SVO_Assert_Handler(svoCookieSource, 0xF8);
        return 0;
    }
    char *start = strchr(header, ':') + 1;
    while (svisspace(*start)) ++start;
    char text[127];
    strncpy(text, start, 127);
    text[126] = 0;
    char *value = strchr(text, '=');
    if (!value) {
        __SVO_Assert_Handler(svoCookieSource, 0x10F);
        return 0;
    }
    *value++ = 0;
    char *end = strchr(value, ';');
    if (!end) {
        __SVO_Assert_Handler(svoCookieSource, 0x117);
        return 0;
    }
    *end = 0;
    return setCookie(jar, text, value);
}

void COOKIE_SECTION(freeResources___dupe3) freeResources___dupe3(CCookieJar *jar)
{
    if (!svoCookieJarInstance) __SVO_Assert_Handler(svoCookieSource, 0x122);
    svFreeSafe(jar->m_memory, svoCookieJarInstance);
    svoCookieJarInstance = 0;
}
