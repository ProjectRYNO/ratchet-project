#ifndef DOWNLOADBINARY_H
#define DOWNLOADBINARY_H

typedef void (*DownloadCallback)(unsigned int id, char *data, int length, void *userData, int status);
typedef struct { // 0x268
    /* 0x000 */ char szPath[257];
    /* 0x101 */ unsigned char padding101[3];
    /* 0x104 */ int bRequested;
    /* 0x108 */ int eMethod;
    /* 0x10C */ int bDestroyWhenRequestSent;
    /* 0x110 */ int iID;
    /* 0x114 */ unsigned short usWidth;
    /* 0x116 */ unsigned short usHeight;
    /* 0x118 */ int eMethodType;
    /* 0x11C */ DownloadCallback pDownloadCallback;
    /* 0x120 */ int m_iUserNameMaxLength;
    /* 0x124 */ char m_szActionStringParameter[256];
    /* 0x224 */ char m_szUserNameParameter[32];
    /* 0x244 */ char m_szAccountIDParameter[32];
    /* 0x264 */ const void *vtable;
} DownloadBinaryState;
#endif
