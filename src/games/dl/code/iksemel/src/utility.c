#include "common.h"
#include "iksemel.h"
#include <string.h>

extern const char iksEscapeAmp[];
extern const char iksEscapeApos[];
extern const char iksEscapeQuot[];
extern const char iksEscapeLt[];
extern const char iksEscapeGt[];

void IKS_SECTION(iks_set_malloc_func) iks_set_malloc_func(void *(*func)(unsigned int size))
{
    my_malloc_func = func;
}

void IKS_SECTION(iks_set_free_func) iks_set_free_func(void (*func)(void *ptr))
{
    my_free_func = func;
}

char *IKS_SECTION(iks_escape) iks_escape(ikstack *s, char *src, unsigned int len)
{
    char *ret;
    unsigned int i, j, nlen;
    char c;

    if (!src || !s) return 0;
    if (len == (unsigned int)-1) len = strlen(src);

    // Retail dispatches both loops through .rodata jump tables; these if-chains need none and fit the slot.
    nlen = len;
    for (i = 0; i < len; i++) {
        c = src[i];
        if (c == '&') nlen += 4;
        else if (c == '<' || c == '>') nlen += 3;
        else if (c == '\'' || c == '"') nlen += 5;
    }
    if (len == nlen) return src;

    ret = iks_stack_alloc(s, nlen + 1);
    if (!ret) return 0;

    for (i = j = 0; i < len; i++) {
        c = src[i];
        if (c == '&') {
            memcpy(&ret[j], iksEscapeAmp, 5);
            j += 5;
        } else if (c == '\'') {
            memcpy(&ret[j], iksEscapeApos, 6);
            j += 6;
        } else if (c == '"') {
            memcpy(&ret[j], iksEscapeQuot, 6);
            j += 6;
        } else if (c == '<') {
            memcpy(&ret[j], iksEscapeLt, 4);
            j += 4;
        } else if (c == '>') {
            memcpy(&ret[j], iksEscapeGt, 4);
            j += 4;
        } else {
            ret[j++] = c;
        }
    }
    ret[j] = '\0';

    return ret;
}
