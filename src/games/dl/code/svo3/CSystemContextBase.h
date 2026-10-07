#ifndef CSYSTEMCONTEXTBASE_H
#define CSYSTEMCONTEXTBASE_H

struct CSystemContextBase;
struct CFileDownloadInfo;

// Verified prefix used by error and timer dispatch.
typedef struct { // 0x3C (vtable prefix, not the full table)
    /* 0x00 */ void *unknown00;
    /* 0x04 */ void *unknown04;
    /* 0x08 */ void *unknown08;
    /* 0x0C */ void (*ErrorCallback)(CSystemContextBase *context, int code);
    /* 0x10 */ void *unknown10;
    /* 0x14 */ void *unknown14;
    /* 0x18 */ void (*HandleOnlineInitComplete)(CSystemContextBase *context);
    /* 0x1C */ void *unknown1C;
    /* 0x20 */ void *unknown20;
    /* 0x24 */ void *unknown24;
    /* 0x28 */ void *unknown28;
    /* 0x2C */ void *unknown2C;
    /* 0x30 */ void *unknown30;
    /* 0x34 */ void *unknown34;
    /* 0x38 */ long (*GetElapsedMS)(CSystemContextBase *context);
} CSystemContextVtablePrefix;

struct CSystemContextBase { // 0x14
    /* 0x00 */ unsigned char unrecovered[0x10];
    /* 0x10 */ CSystemContextVtablePrefix *vtable;
};

extern "C" {
void FileDownloadCallback(CSystemContextBase *context, CFileDownloadInfo *info);
void EnterStaticScreen(CSystemContextBase *context, char *screenName);
long GetElapsedMS(CSystemContextBase *context);
int OkToFreeFileDownloadBuffer(CSystemContextBase *context, void *data);
CSystemContextBase *GetSystemContext(void);
}

#endif
