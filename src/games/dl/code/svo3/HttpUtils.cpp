#include "HttpUtils.h"
#include "SVOString.h"
#include <stdlib.h>
#include <string.h>

extern "C" {
extern char svoHttpUtilsSource[];
extern char svoHttpEscapeFormat[];
extern char svoHttpDoubleSlash[];
extern char svoHttpColon[];
extern char svoHttpSlash[];
extern HTTPEntity svoHttpEntityMap[];
extern char *svoHttpInvalidChars;
void __SVO_Assert_Handler(const char *file, int line);
}
#define HTTP_SECTION(name) __attribute__((section(".svo_http_" #name)))

int HTTP_SECTION(escapeString) escapeString(char *source, char *destination, unsigned int capacity)
{
    if (!source || !destination) __SVO_Assert_Handler(svoHttpUtilsSource, 0x35);
    unsigned int length = strlen(source);
    unsigned int written = 0;
    unsigned int position = 0;
    if (capacity <= length) __SVO_Assert_Handler(svoHttpUtilsSource, 0x3B);
    for (; written < capacity && position < length && source[position]; position++) {
        char *current = source + position;
        if (strchr(svoHttpInvalidChars, *current))
            written += svsnprintf(destination + written, capacity - written, svoHttpEscapeFormat, *current);
        else
            destination[written++] = *current;
        if (written >= capacity) __SVO_Assert_Handler(svoHttpUtilsSource, 0x4A);
    }
    destination[written] = 0;
    return written;
}

void HTTP_SECTION(decodeEntityText) decodeEntityText(char *text)
{
    if (!text) __SVO_Assert_Handler(svoHttpUtilsSource, 0x5D);
    unsigned int read = 0;
    int written = 0;
    do {
        text[written++] = decodeEntityChar(text, &read);
    } while (text[read]);
    memset(text + written, 0, read - written);
}

char HTTP_SECTION(decodeEntityChar) decodeEntityChar(char *text, unsigned int *position)
{
    char *current = text + *position;
    if (*current == '&') {
        if (current[1] == '#') {
            if (svisdigit(current[2])) {
                char *end;
                long value = strtol(text + *position + 2, &end, 10);
                if (*end++ == ';' && value < 256) {
                    *position = end - text;
                    return (char)value;
                }
            }
        } else {
            for (int i = 0; svoHttpEntityMap[i].str; i++) {
                char *pattern = svoHttpEntityMap[i].str;
                if (!strncmp(pattern, text + *position, strlen(pattern))) {
                    *position += strlen(pattern);
                    return svoHttpEntityMap[i].val;
                }
            }
        }
    }
    char result = text[*position];
    ++*position;
    return result;
}

void HTTP_SECTION(decodeURLEntityText) decodeURLEntityText(char *text)
{
    if (!text) __SVO_Assert_Handler(svoHttpUtilsSource, 0xA5);
    unsigned int read = 0;
    int written = 0;
    do {
        text[written++] = decodeURLEntityChar(text, &read);
    } while (text[read]);
    memset(text + written, 0, read - written);
}

char HTTP_SECTION(decodeURLEntityChar) decodeURLEntityChar(char *text, unsigned int *position)
{
    char *current = text + *position;
    if (*current == '+') {
        ++*position;
        return ' ';
    }
    if (*current == '%') {
        // Retail advances by two, leaving the last '2' of %22 for the next call.
        if (current[1] == '2' && current[2] == '2') {
            *position += 2;
            return '"';
        }
        if (isURLDigit(text[*position + 1])) {
            char *end;
            long value = strtol(text + *position + 1, &end, 16);
            if (value < 256) {
                *position = end - text;
                return (char)value;
            }
        }
    }
    char result = text[*position];
    ++*position;
    return result;
}

int HTTP_SECTION(isURLDigit) isURLDigit(char c)
{
    if (c < 'G') { if (c >= 'A') return 1; } return svisdigit(c) != 0;
}

void HTTP_SECTION(parseFullyQualifiedPath) parseFullyQualifiedPath(char *source, SVPath *path)
{
    char portText[6];
    if (!strstr(source, svoHttpDoubleSlash)) __SVO_Assert_Handler(svoHttpUtilsSource, 0x100);
    char *server = strstr(source, svoHttpDoubleSlash) + 2;
    int schemeLength = strstr(source, svoHttpColon) - source;
    if (schemeLength > 14) __SVO_Assert_Handler(svoHttpUtilsSource, 0x105);
    memcpy(path->m_scheme, source, 15);
    path->m_scheme[schemeLength] = 0;
    char *colon = strstr(server, svoHttpColon);
    char *slash = strstr(server, svoHttpSlash);
    int serverLength = colon ? colon - server : slash - server;
    int portLength = slash - colon;
    strncpy(path->m_server, server, serverLength);
    char *portStart = server + serverLength + 1;
    path->m_server[serverLength] = 0;
    unsigned int port = 80;
    if (colon) {
        if (portLength > 6) __SVO_Assert_Handler(svoHttpUtilsSource, 0x11E);
        memset(portText, 0, sizeof(portText));
        // The retail length includes the slash after the port digits.
        strncpy(portText, portStart, portLength);
        port = atoi(portText);
        if (port > 65535) {
            __SVO_Assert_Handler(svoHttpUtilsSource, 0x128);
            port = 80;
        }
    }
    *path->m_port = port;
    memset(path->m_path, 0, path->m_pathMaxLength);
    strncpy(path->m_path, slash, strlen(slash) + 1);
}

int HTTP_SECTION(pathIsFullyQualified___dupe2) pathIsFullyQualified___dupe2(char *source)
{
    int result = 0;
    char *colon = strstr(source, svoHttpColon);
    int length = colon - source;
    if (colon) {
        if (length > 14) __SVO_Assert_Handler(svoHttpUtilsSource, 0x14E);
        char scheme[16];
        memcpy(scheme, source, 15);
        scheme[length] = 0;
        result = 1;
    }
    return result;
}

void HTTP_SECTION(printFormattedBody) printFormattedBody(char *body, unsigned int length, int contentType)
{
    // The retail diagnostic output is disabled; only these local copies remain.
    char line[36];
    line[35] = 0;
    for (unsigned int count = 0; count <= length / 35; count++) {
        memcpy(line, body, 35);
        body += 35;
    }
}
