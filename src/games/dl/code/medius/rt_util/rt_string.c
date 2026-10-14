#include "common.h"
#include "rt_string.h"

#define MEDIUS_STRING_SECTION(name) __attribute__((section(".medius_string_" #name)))

unsigned int MEDIUS_STRING_SECTION(rt_strnlen) rt_strnlen(const char *s, unsigned int n)
{
    const char *p;
    const char *end = s + n;

    if (!s) return 0;
    for (p = s; p < end && *p; p++)
        ;
    return p - s;
}
