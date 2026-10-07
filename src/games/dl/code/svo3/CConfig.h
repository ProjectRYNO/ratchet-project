#ifndef CCONFIG_H
#define CCONFIG_H

typedef struct { // 0x148
    /* 0x000 */ char m_ip[64];
    /* 0x040 */ int m_port;
    /* 0x044 */ char m_firstPage[256];
    /* 0x144 */ int m_bFileRead;
} CConfigState;

extern "C" {
extern char *SVO_CONFIG_PREFIX;
void *CConfig(CConfigState *config);
int loadConfigurationFile(CConfigState *config, char *filename);
}

#endif
