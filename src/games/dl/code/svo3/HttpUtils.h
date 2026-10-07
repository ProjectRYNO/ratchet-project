#ifndef HTTPUTILS_H
#define HTTPUTILS_H

typedef struct { // 0x08
    /* 0x00 */ char *str;
    /* 0x04 */ char val;
    /* 0x05 */ char padding[3];
} HTTPEntity;

typedef struct { // 0x14
    /* 0x00 */ char *m_scheme;
    /* 0x04 */ char *m_server;
    /* 0x08 */ unsigned short *m_port; // Retail C++ reference storage.
    /* 0x0C */ char *m_path;
    /* 0x10 */ unsigned int m_pathMaxLength;
} SVPath;

extern "C" {
int escapeString(char *source, char *destination, unsigned int capacity);
void decodeEntityText(char *text);
char decodeEntityChar(char *text, unsigned int *position);
void decodeURLEntityText(char *text);
char decodeURLEntityChar(char *text, unsigned int *position);
int isURLDigit(char c);
void parseFullyQualifiedPath(char *source, SVPath *path);
int pathIsFullyQualified___dupe2(char *source);
void printFormattedBody(char *body, unsigned int length, int contentType);
}
#endif
