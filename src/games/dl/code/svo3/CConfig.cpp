#include "CConfig.h"
#include "SVOString.h"
#include "../iksemel/src/iks.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct iksparser;
extern "C" {
extern const char svoConfigPathFormat[];
extern const char svoConfigSource[];
extern const char svoConfigIpKey[];
extern const char svoConfigPathKey[];
extern const char svoConfigPortKey[];
void __SVO_Assert_Handler(const char *file, int line);
int sceOpen(const char *filename, int mode);
int sceLseek(int descriptor, int offset, int origin);
int sceRead(int descriptor, void *buffer, int count);
int sceClose(int descriptor);
iksparser *iks_dom_new(iks **node);
int iks_parse(iksparser *parser, const char *text, unsigned int count, int finish);
char *iks_find_cdata(iks *node, const char *name);
void iks_parser_delete(iksparser *parser);
void iks_delete(iks *node);
}
#define SVO_CONFIG_SECTION(name) __attribute__((section(".svo_config_" #name)))

SVO_CONFIG_SECTION(CConfig) void *CConfig(CConfigState *config)
{
    config->m_port = -1;
    config->m_bFileRead = 0;
    // Reuse memset's returned pointer to stay within the original constructor slot.
    char *firstPage = (char *)memset(config->m_firstPage, 0, sizeof(config->m_firstPage));
    config = (CConfigState *)(firstPage - offsetof(CConfigState, m_firstPage));
    return memset(config->m_ip, 0, sizeof(config->m_ip));
}

int SVO_CONFIG_SECTION(loadConfigurationFile) loadConfigurationFile(CConfigState *config, char *filename)
{
    char data[4096];
    char path[256];
    memset(data, 0, sizeof(data));
    sprintf(path, svoConfigPathFormat, SVO_CONFIG_PREFIX, filename);
    int descriptor = sceOpen(path, 1);
    if (descriptor < 0) return 0;
    int length = sceLseek(descriptor, 0, 2);
    sceLseek(descriptor, 0, 0);
    if (length <= 0) __SVO_Assert_Handler(svoConfigSource, 0x48);
    if (length >= 4096) __SVO_Assert_Handler(svoConfigSource, 0x4B);
    sceRead(descriptor, data, length);
    // Retail repeats the length assertion; it does not inspect sceRead's result.
    if (length >= 4096) __SVO_Assert_Handler(svoConfigSource, 0x4F);
    sceClose(descriptor);
    iks *node = 0;
    iksparser *parser = iks_dom_new(&node);
    iks_parse(parser, data, 0, 1);
    if (!node) __SVO_Assert_Handler(svoConfigSource, 0x7E);
    char *value = iks_find_cdata(node, svoConfigIpKey);
    if (!value) __SVO_Assert_Handler(svoConfigSource, 0x84);
    svstrncpy(config->m_ip, value, sizeof(config->m_ip));
    value = iks_find_cdata(node, svoConfigPathKey);
    // Preserve the retail check of the destination address, rather than the XML value.
    if ((unsigned int)config == 0xFFFFFFBCU) __SVO_Assert_Handler(svoConfigSource, 0x88);
    svstrncpy(config->m_firstPage, value, sizeof(config->m_firstPage));
    value = iks_find_cdata(node, svoConfigPortKey);
    if (!value || !svisdigit((signed char)*value)) __SVO_Assert_Handler(svoConfigSource, 0x8C);
    config->m_port = atoi(value);
    iks_parser_delete(parser);
    iks_delete(node);
    config->m_bFileRead = 1;
    return 1;
}
