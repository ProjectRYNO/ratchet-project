#ifndef SVFILEDOWNLOADQUEUE_H
#define SVFILEDOWNLOADQUEUE_H

typedef struct { // 0x08
    /* 0x00 */ char *m_lookupStr;
    /* 0x04 */ char *m_valueStr;
} FileDownloadEntryState;
typedef struct { // 0x28
    /* 0x00 */ FileDownloadEntryState m_entries[5];
} FileDownloadQueueState;
#endif
