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

    if (!src || !s) return 0;
    if (len == -1) len = strlen(src);

    nlen = len;
    for (i = 0; i < len; i++) {
        switch (src[i]) {
            case '&': nlen += 4; break;
            case '<': nlen += 3; break;
            case '>': nlen += 3; break;
            case '\'': nlen += 5; break;
            case '"': nlen += 5; break;
        }
    }
    if (len == nlen) return src;

    ret = iks_stack_alloc(s, nlen + 1);
    if (!ret) return 0;

    for (i = j = 0; i < len; i++) {
        switch (src[i]) {
            case '&': memcpy(&ret[j], iksEscapeAmp, 5); j += 5; break;
            case '\'': memcpy(&ret[j], iksEscapeApos, 6); j += 6; break;
            case '"': memcpy(&ret[j], iksEscapeQuot, 6); j += 6; break;
            case '<': memcpy(&ret[j], iksEscapeLt, 4); j += 4; break;
            case '>': memcpy(&ret[j], iksEscapeGt, 4); j += 4; break;
            default: ret[j++] = src[i];
        }
    }
    ret[j] = '\0';

    return ret;
}
