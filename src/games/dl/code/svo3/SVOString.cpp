#include "SVOString.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

extern "C" {
extern const char svoStringSource[];
void __SVO_Assert_Handler(const char *file, int line);
}
#define SVO_STRING_SECTION(name) __attribute__((section(".svo_string_" #name)))

SVO_STRING_SECTION(svstrncpy) char *svstrncpy(char *dst, char *src, unsigned int size)
{
    unsigned int i = 0;
    char *target;
    char *source;
    if (!src) __SVO_Assert_Handler(svoStringSource, 0x1E);
    if (!dst) __SVO_Assert_Handler(svoStringSource, 0x1F);
    if (size >= 0xA000) __SVO_Assert_Handler(svoStringSource, 0x20);
    goto test;
copy:
    *target = *source;
test:
    if (i >= size) {
        // Retail also writes dst[-1] when size is zero; callers must provide capacity.
        dst[i - 1] = 0;
        __SVO_Assert_Handler(svoStringSource, 0x28);
        return dst;
    }
    target = &dst[i];
    source = &src[i];
    i++;
    if (*source) goto copy;
    *target = 0;
    return dst;
}

SVO_STRING_SECTION(svsubstrncpy) char *svsubstrncpy(char *dst, char *src, unsigned int size)
{
    unsigned int i = 0;
    char *target;
    char *source;
    if (!src) __SVO_Assert_Handler(svoStringSource, 0x44);
    if (!dst) __SVO_Assert_Handler(svoStringSource, 0x45);
    if (!size) __SVO_Assert_Handler(svoStringSource, 0x48);
    goto test;
copy:
    *target = *source;
test:
    if (i >= size) {
        dst[i - 1] = 0;
        return dst;
    }
    target = &dst[i];
    source = &src[i];
    i++;
    if (*source) goto copy;
    *target = 0;
    return dst;
}

int SVO_STRING_SECTION(svsnprintf) svsnprintf(char *dst, unsigned int size, char *format, ...)
{
    va_list args;
    va_start(args, format);
    if (!dst) __SVO_Assert_Handler(svoStringSource, 0x71);
    // Retail uses vsprintf, then checks its result; size is not a formatting bound.
    memset(dst, 0, size);
    int count = vsprintf(dst, format, args);
    if (count == -1 || count >= (int)size) {
        __SVO_Assert_Handler(svoStringSource, 0x76);
    }
    va_end(args);
    return count;
}

int SVO_STRING_SECTION(my_strcspn) my_strcspn(char *text, char *substring)
{
    int i = 0;
    int textLength = strlen(text);
    int substringLength = strlen(substring);
    // Despite its name this searches for a substring, not a character set.
    for (; i < textLength; ++i) {
        if (strncmp(text + i, substring, substringLength) == 0) return i;
    }
    return -1;
}

int SVO_STRING_SECTION(svstrlen) svstrlen(char *text)
{
    return strlen(text) + 1;
}

int SVO_STRING_SECTION(svisalpha) svisalpha(int c)
{
    if ((unsigned int)c - 'A' < 26 || (unsigned int)c - 'a' < 26) return 1;
    return 0;
}

int SVO_STRING_SECTION(svisxdigit) svisxdigit(int c)
{
    if (svisdigit(c)) return 1;
    if ((unsigned int)c - 'A' < 6) return 1;
    return (unsigned int)c - 'a' < 6;
}

int SVO_STRING_SECTION(svisdigit) svisdigit(int c)
{
    return (unsigned int)c - '0' < 10;
}

int SVO_STRING_SECTION(svisspace) svisspace(int c)
{
    if (c == ' ') return 1;
    if (c == '\f') return 1;
    if (c == '\n') return 1;
    if (c == '\r') return 1;
    if (c == '\t') return 1;
    return c == '\v';
}
