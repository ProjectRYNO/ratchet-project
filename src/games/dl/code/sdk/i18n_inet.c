#include "i18n_inet.h"

extern void *memset(void *, int, unsigned int);
extern unsigned int strlen(const char *);
extern char *strchr(const char *, int);
extern char *strncpy(char *, const char *, unsigned int);
extern int strcmp(const char *, const char *);
extern int strncmp(const char *, const char *, unsigned int);

void __attribute__((section(".sdk_i18n_inet_ezNetCtlRecreateIfstat")))
ezNetCtlRecreateIfstat(const char *text, ezNetCtlStatus *status, EzNetCtlInfo *info)
{
    char *space;
    const char *value = 0;
    SdkPPPStatus *entry;

    memset(info, 0, 0x1fc);
    if (strlen(text) == 0) return;
    space = strchr(text, ' ');
    if (space) value = space + 1;
    if (status->iftype == 3) {
        strncpy(info->ppp.message, text, 0x50);
        strncpy(info->ppp.phone, text + 0x50, 0x20);
        strncpy(info->ppp.speed, text + 0x50, 0x20);
        strncpy(info->ppp.auth, text + 0x80, 0x80);
    } else if (status->iftype == 4) {
        strncpy(info->common.data, text + 0x80, 0x80);
    }
    if (strncmp(text, sdkInetAbort, 5) == 0) {
        if (strcmp(value, sdkInetBusy) == 0) status->error = -404;
        else if (strcmp(value, sdkInetLineInUse) == 0) status->error = -401;
        else if (strcmp(value, sdkInetNoDialtone) == 0) status->error = -401;
        else if (strcmp(value, sdkInetNoAnswer) == 0) status->error = -401;
        else if (strcmp(value, sdkInetNoCarrier) == 0) status->error = -402;
        else status->error = -499;

        info->common.phase = 301;
    } else if (strcmp(text, sdkInetAuthFailed) == 0) {
        status->error = -302;
    } else {
        for (entry = sdkPPPStatusList; entry->text; ++entry) {
            if (strcmp(value, entry->text) == 0) {
                if (strncmp(text, sdkInetPhase, 5) == 0) {
                    int phase;
                    // Preserve the retail interface dispatch before publishing detail.
                    if (status->iftype == 3) {
                        phase = entry->phase;
                        info->common.phase = phase;
                    } else {
                        phase = entry->phase;
                        info->common.phase = phase;
                    }
                    info->common.detail = phase;
                } else if (strncmp(text, sdkInetDisconnect, 10) == 0 ||
                           strncmp(text, sdkInetTimeout, 7) == 0) {
                    status->error = entry->error;
                }
                return;
            }
        }
    }
}
