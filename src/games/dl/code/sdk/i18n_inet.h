#ifndef SDK_I18N_INET_H
#define SDK_I18N_INET_H

#include "i18n.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct { // 0x0c
    /* 0x00 */ const char *text;
    /* 0x04 */ int phase;
    /* 0x08 */ int error;
} SdkPPPStatus;

extern SdkPPPStatus sdkPPPStatusList[];
extern const char sdkInetAbort[];
extern const char sdkInetBusy[];
extern const char sdkInetLineInUse[];
extern const char sdkInetNoDialtone[];
extern const char sdkInetNoAnswer[];
extern const char sdkInetNoCarrier[];
extern const char sdkInetAuthFailed[];
extern const char sdkInetPhase[];
extern const char sdkInetDisconnect[];
extern const char sdkInetTimeout[];

void ezNetCtlRecreateIfstat(const char *, ezNetCtlStatus *, EzNetCtlInfo *);

#ifdef __cplusplus
}
#endif
#endif
