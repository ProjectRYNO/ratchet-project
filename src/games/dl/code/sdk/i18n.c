#include "i18n.h"
#define SDK_I18N_SECTION(name) __attribute__((section(".sdk_i18n_" #name)))
extern int snprintf(char *, unsigned int, const char *, ...);
extern int strncmp(const char *, const char *, unsigned int);
extern unsigned int strlen(const char *);
extern void *memset(void *, int, unsigned int);
extern char *strncpy(char *, const char *, unsigned int);
extern int scePrintf(const char *, ...);
extern SDKMessageEntry *sdkErrorMessages;
extern SDKMessageEntry *sdkPhaseMessages;
extern SDKMessageEntry *sdkStateMessages;
extern SDKMessageEntry sdkErrorEnglish[];
extern SDKMessageEntry sdkPhaseEnglish[];
extern SDKMessageEntry sdkStateEnglish[];
extern const char sdkPPPprefix[];
extern const char sdkMessageLog[];
extern const char sdkMessageFunction[];
extern const char sdkMessageMissing[];
extern unsigned char _ctype_[];

void SDK_I18N_SECTION(ezNetCtlSwapMessageTables) ezNetCtlSwapMessageTables(
    SDKMessageEntry *errors, SDKMessageEntry *phases, SDKMessageEntry *states)
{
    sdkErrorMessages = errors ? errors : sdkErrorEnglish;
    sdkPhaseMessages = phases ? phases : sdkPhaseEnglish;
    sdkStateMessages = states ? states : sdkStateEnglish;
}

SDKMessageEntry *SDK_I18N_SECTION(getMsgEntry) getMsgEntry(int id, SDKMessageEntry *entry)
{
    while (entry->message) {
        if (entry->first <= id && id <= entry->last)
            return entry;
        ++entry;
    }
    scePrintf(sdkMessageLog, sdkMessageFunction);
    scePrintf(sdkMessageMissing, id);
    return 0;
}

void SDK_I18N_SECTION(ezNetCtlLocalizeMessage) ezNetCtlLocalizeMessage(
    char *out, unsigned int size, const ezNetCtlStatus *status, EzNetCtlInfo *info)
{
    SDKMessageEntry *entry = 0;
    int phase = 0;
    if (!out || !size)
        return;
    switch (status->iftype) {
    case 2:
        phase = info->common.phase;
        break;
    case 3:
        if (info->common.phase == 302)
            phase = info->common.detail;
        else
            phase = info->common.phase;
        break;
    case 4:
        if (info->common.phase == 302)
            phase = info->common.detail;
        else
            phase = info->common.phase;
        break;
    }
    if (phase && status->state > 0 && status->state < 4)
        entry = getMsgEntry(phase, sdkPhaseMessages);
    if (status->error)
        entry = getMsgEntry(status->error, sdkErrorMessages);
    if (!entry)
        entry = getMsgEntry(status->state, sdkStateMessages);
    memset(out, 0, size);
    if (entry) {
        if (entry->formatter)
            entry->formatter(out, size, entry->message, status, info);
        else
            strncpy(out, entry->message, size);
    }
}

void SDK_I18N_SECTION(cbFormatAuthMessage) cbFormatAuthMessage(
    char *out, unsigned int size, const char *format, const ezNetCtlStatus *status, EzNetCtlInfo *info)
{
    if (status->iftype == 3)
        snprintf(out, size, format, info->ppp.auth);
    else if (status->iftype == 4)
        snprintf(out, size, format, info->common.data);
}

void SDK_I18N_SECTION(cbFormatPPPStatus) cbFormatPPPStatus(
    char *out, unsigned int size, const char *format, const ezNetCtlStatus *status, EzNetCtlInfo *info)
{
    const char *text = info->ppp.message;
    if (strncmp(text, sdkPPPprefix, 5) == 0)
        text = info->ppp.message + 6;
    snprintf(out, size, format, text);
}

void SDK_I18N_SECTION(cbFormatLineSpeed) cbFormatLineSpeed(
    char *out, unsigned int size, const char *format, const ezNetCtlStatus *status, EzNetCtlInfo *info)
{
    char *text = info->ppp.speed;
    int length = strlen(text);
    while (length && ((_ctype_ + 1)[(int)text[length - 1]] & 8)) {
        text[--length] = 0;
    }
    snprintf(out, size, format, text);
}

void SDK_I18N_SECTION(cbFormatPhoneNumber) cbFormatPhoneNumber(
    char *out, unsigned int size, const char *format, const ezNetCtlStatus *status, EzNetCtlInfo *info)
{
    snprintf(out, size, format, info->ppp.phone);
}
