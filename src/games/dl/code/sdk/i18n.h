#ifndef SDK_I18N_H
#define SDK_I18N_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct { // 0x38
    /* 0x00 */ int ifid;
    /* 0x04 */ int ifid2;
    /* 0x08 */ char ifname[16];
    /* 0x18 */ char ifname2[16];
    /* 0x28 */ int iftype;
    /* 0x2c */ int error;
    /* 0x30 */ int state;
    /* 0x34 */ int link;
} ezNetCtlStatus;

typedef union { // 0x1fc
    /* 0x00 */ char raw[0x1fc];
    /* 0x00 */ struct {
        /* 0x00 */ int phase;
        /* 0x04 */ int detail;
        /* 0x08 */ char data[0x1f4];
    } common;
    /* 0x00 */ struct {
        /* 0x00 */ char unknown00[0x0c];
        /* 0x0c */ char phone[0x20];
        /* 0x2c */ char unknown2c[0xe0];
        /* 0x10c */ char message[0x50];
        /* 0x15c */ char speed[0x20];
        /* 0x17c */ char auth[0x80];
    } ppp;
} EzNetCtlInfo;

typedef void (*EzNetCtlMessageFormatter)(char *, unsigned int, const char *,
                                        const ezNetCtlStatus *, EzNetCtlInfo *);
typedef struct { // 0x10
    /* 0x00 */ int first;
    /* 0x04 */ int last;
    /* 0x08 */ const char *message;
    /* 0x0c */ EzNetCtlMessageFormatter formatter;
} SDKMessageEntry;

void ezNetCtlSwapMessageTables(SDKMessageEntry *, SDKMessageEntry *, SDKMessageEntry *);
SDKMessageEntry *getMsgEntry(int, SDKMessageEntry *);
void ezNetCtlLocalizeMessage(char *, unsigned int, const ezNetCtlStatus *, EzNetCtlInfo *);
void cbFormatAuthMessage(char *, unsigned int, const char *, const ezNetCtlStatus *, EzNetCtlInfo *);
void cbFormatPPPStatus(char *, unsigned int, const char *, const ezNetCtlStatus *, EzNetCtlInfo *);
void cbFormatLineSpeed(char *, unsigned int, const char *, const ezNetCtlStatus *, EzNetCtlInfo *);
void cbFormatPhoneNumber(char *, unsigned int, const char *, const ezNetCtlStatus *, EzNetCtlInfo *);
#ifdef __cplusplus
}
#endif
#endif
