#ifndef SVOSTRING_H
#define SVOSTRING_H

// C linkage preserves the retail labels used by the split assembly.
#ifdef __cplusplus
extern "C" {
#endif

char *svstrncpy(char *dst, char *src, unsigned int size);
char *svsubstrncpy(char *dst, char *src, unsigned int size);
int svsnprintf(char *dst, unsigned int size, char *format, ...);
int my_strcspn(char *text, char *substring);

// Includes the terminating NUL, unlike strlen. Input must be a valid string.
int svstrlen(char *text);
int svisalpha(int c);
int svisxdigit(int c);
int svisdigit(int c);
int svisspace(int c);

#ifdef __cplusplus
}
#endif

#endif
