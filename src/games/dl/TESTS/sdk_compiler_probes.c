extern int snprintf(char *, unsigned int, const char *, ...);
extern int strncmp(const char *, const char *, unsigned int);
extern int scePrintf(const char *, ...);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern void *sdkErrorMessages, *sdkPhaseMessages, *sdkStateMessages;
extern char sdkErrorEnglish[], sdkPhaseEnglish[], sdkStateEnglish[];
extern char sdkPPPprefix[], sdkMessageLog[], sdkMessageFunction[], sdkMessageMissing[];
extern char sdkCnfLog[], sdkCnfFunction[], sdkCnfEmpty[], sdkCnfBadIndex[];
extern char sdkCtlLog[], sdkCtlFunction[], sdkCtlNotRunning[];
extern int sdkCtlRunning;
extern char sdkCtlClient[];
extern int sdkCtlBuffer[];

typedef struct {
    int first;
    int last;
    const char *message;
    void *formatter;
} SDKMessageEntry;

void ezNetCtlSwapMessageTables(void *errors, void *phases, void *states)
{
    sdkErrorMessages = errors ? errors : sdkErrorEnglish;
    sdkPhaseMessages = phases ? phases : sdkPhaseEnglish;
    sdkStateMessages = states ? states : sdkStateEnglish;
}

SDKMessageEntry *getMsgEntry(int id, SDKMessageEntry *entry)
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

void cbFormatAuthMessage(char *out, unsigned int size, const char *format,
                         const char *status, const char *info)
{
    if (*(const int *)(status + 0x28) == 3)
        snprintf(out, size, format, info + 0x17c);
    else if (*(const int *)(status + 0x28) == 4)
        snprintf(out, size, format, info + 8);
}

void cbFormatPPPStatus(char *out, unsigned int size, const char *format,
                       const char *status, const char *info)
{
    const char *text = info + 0x10c;
    if (strncmp(text, sdkPPPprefix, 5) == 0)
        text = info + 0x112;
    snprintf(out, size, format, text);
}

void cbFormatPhoneNumber(char *out, unsigned int size, const char *format,
                         const char *status, const char *info)
{
    snprintf(out, size, format, info + 12);
}

void *ezNetCnfGetCombination(int *list, int index)
{
    if (!list || !*list) {
        scePrintf(sdkCnfLog, sdkCnfFunction);
        scePrintf(sdkCnfEmpty);
        return 0;
    }
    if (index <= 0 || index > *list) {
        scePrintf(sdkCnfLog, sdkCnfFunction);
        scePrintf(sdkCnfBadIndex, index);
        return 0;
    }
    return (char *)list + index * 200 - 152;
}

int ezNetCtlDownInterface(void)
{
    int *result = sdkCtlBuffer;
    if (!sdkCtlRunning) {
        scePrintf(sdkCtlLog, sdkCtlFunction);
        scePrintf(sdkCtlNotRunning);
        return -1;
    }
    sceSifCallRpc(sdkCtlClient, 6, 0, 0, 0, result, 4, 0, 0);
    return result[0];
}
