#ifndef CCOOKIE_H
#define CCOOKIE_H
#include "CMemoryContextBase.h"

typedef struct { // 0x7F4
    /* 0x000 */ char m_cookies[16][127];
    /* 0x7F0 */ CMemoryContextBaseState *m_memory;
} CCookieJar;

extern "C" {
CCookieJar *getInstance(CMemoryContextBaseState *memory);
int setCookie(CCookieJar *jar, char *name, char *value);
int asHeaderString(CCookieJar *jar, char *header, unsigned int size);
int parseSetCookieHeader(CCookieJar *jar, char *header);
void freeResources___dupe3(CCookieJar *jar);
}
#endif
