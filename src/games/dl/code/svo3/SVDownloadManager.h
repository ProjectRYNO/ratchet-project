#ifndef SVDOWNLOADMANAGER_H
#define SVDOWNLOADMANAGER_H
#include "CHttp.h"
struct CPage;
typedef struct { // 0x18
    /* 0x00 */ unsigned int dataSizeBytes;
    /* 0x04 */ unsigned int bytesReceived;
    /* 0x08 */ char *pData;
    /* 0x0C */ int bWaitingForSystemOk;
    /* 0x10 */ int bBeingUsedForDownload;
    /* 0x14 */ unsigned int startPos;
} DLBuffer;
typedef struct { // 0x8CD8
    /* 0x0000 */ IRequestListenerState base;
    /* 0x0004 */ char m_fileName[32];
    /* 0x0024 */ char m_scheme[16];
    /* 0x0034 */ char m_serverName[128];
    /* 0x00B4 */ unsigned short m_port;
    /* 0x00B6 */ unsigned char paddingB6[2];
    /* 0x00B8 */ HttpState m_http;
    /* 0x8B7C */ int m_state;
    /* 0x8B80 */ int m_bRequestInProgress;
    /* 0x8B84 */ int m_fileStatus;
    /* 0x8B88 */ unsigned int m_fileContentLength;
    /* 0x8B8C */ unsigned int m_fileBytesReceived;
    /* 0x8B90 */ DLBuffer m_buffers[2];
    /* 0x8BC0 */ CPage *m_page;
    /* 0x8BC4 */ SVChronographState m_timer;
    /* 0x8BD4 */ char m_fileID[257];
    /* 0x8CD5 */ unsigned char padding8CD5[3];
} SVDownloadManagerState;
#endif
