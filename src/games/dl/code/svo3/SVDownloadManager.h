#ifndef SVDOWNLOADMANAGER_H
#define SVDOWNLOADMANAGER_H

typedef struct { // 0x8B80 (verified prefix)
    /* 0x0000 */ unsigned char unrecovered00[0x8B7C];
    /* 0x8B7C */ int m_state;
} SVDownloadManagerState;

#endif
