#ifndef RYNO_989SND_EE_H
#define RYNO_989SND_EE_H

/* Names from the prototype decompilation; layout/addresses checked against retail. */
typedef unsigned int SndWord;
typedef unsigned long long SndUserData;
typedef void (*SndCompleteProc)(SndWord result, SndUserData user_data);
typedef void (*SndCdCallback)(int reason);
typedef struct { int num_commands; char buffer[4092]; } SndCommandBuffer;
typedef struct { SndCompleteProc done; SndUserData u_data; } SndCommandReturnDef;
typedef struct { unsigned short command, size; } SndCommandEntry;
typedef struct { char header[0x24]; SndWord server; } SndRpcClient;
typedef struct { int cd_busy; int pad_0, pad_1, pad_2; int cd_error; int pad_3, pad_4, pad_5; char pad_big[32]; } SndSystemStatus;
typedef struct { unsigned char trycount, spindlctrl, datapattern, pad; } SndCdRMode;
typedef struct {
    int source_group;
    unsigned int target_groups;
    int full_duck_mult, attack_time, release_time, current_duck_mult;
} DuckerDef;

/* Existing data allocations, never new copies of library state. */
extern SndWord *gCommBusy __asm__("D_0021DCA8");
extern int gAwaitingInts __asm__("D_0021DCAC");
extern int gLocalLoadError __asm__("D_0021DCB0");
extern int gStreamingInited __asm__("D_0021DCB4");
extern SndCdCallback gCdCallback __asm__("D_0021DCB8");
extern int gSSRead __asm__("D_0021DCBC");
extern int gSSReadDone __asm__("D_0021DCC0");
extern int gLoadingFromFS __asm__("D_0021DCC4");
extern SndCommandBuffer *gSndCommandBuffePtr[2] __asm__("D_0021DCC8");
extern int gCommandBuffeBytesAvail[2] __asm__("D_0021DCD0");
extern SndCommandReturnDef *gSndCommandReturnDefPtr[2] __asm__("D_0021DCD8");
extern SndWord *gReturnValuesPtr[2] __asm__("D_0021DCE0");
extern int gCommandFillBuffer __asm__("D_0021DCE8");
extern int gCaching __asm__("D_0021DCEC");
extern SndWord gLoadBusy __asm__("D_0021DCF0");
extern SndCommandReturnDef gLoadReturnDef __asm__("D_0021DCF8");
extern SndCompleteProc gLoadCB __asm__("D_0021DD0C");
extern SndUserData gLoadUserData __asm__("D_0021DD10");
extern int gPrefs_Silent __asm__("D_0021DD20");
extern SndRpcClient gSLClientData __asm__("D_001BD480");
extern SndWord gSyncBuffer[16] __asm__("D_001BD4C0");
extern char gSyncSendBuffer[512] __asm__("D_001BD500");
extern SndCommandBuffer gSndCommandBuffer1 __asm__("D_001BD700");
extern SndCommandBuffer gSndCommandBuffer2 __asm__("D_001BE700");
extern SndCommandReturnDef gSndCommandReturnDef1[256] __asm__("D_001BF700");
extern SndCommandReturnDef gSndCommandReturnDef2[256] __asm__("D_001C0700");
extern SndWord gActualReturnValues1[264] __asm__("D_001C1700");
extern SndWord gActualReturnValues2[264] __asm__("D_001C1B40");
extern SndSystemStatus gStats __asm__("D_001C1F80");
extern SndRpcClient gSLClientLoaderData __asm__("D_001C1FC0");
extern SndWord gLoadReturnValue __asm__("D_0021D9C0");
extern int gLoadParams[8] __asm__("D_001C2000");

extern const char sndBindError[] __asm__("D_001A4720");
extern const char sndSourceFile[] __asm__("D_001A4748");
extern const char sndMissingReturns[] __asm__("D_001A4768");
extern const char sndCollision[] __asm__("D_001A47F0");
extern const char sndLocBusy[] __asm__("D_001A4878");
extern const char sndCdBusy[] __asm__("D_001A48A8");
extern const char sndEeBusy[] __asm__("D_001A4900");
extern const char sndEeLoadError[] __asm__("D_001A4930");
extern const char sndExternalTooLarge[] __asm__("D_001A4BC8");
extern const char sndCommandTooLarge[] __asm__("D_001A4C10");
extern const char sndBufferFull[] __asm__("D_001A4C38");
extern const char sndContinuing[] __asm__("D_001A4C98");

int printf(const char *, ...);
void *memcpy(void *, const void *, unsigned int);
void sceSifInitRpc(int);
int sceSifBindRpc(SndRpcClient *, unsigned int, int);
int sceSifCheckStatRpc(SndRpcClient *);
int sceSifCallRpc(SndRpcClient *, int, int, void *, int, void *, int, void (*)(void *), void *);
void FlushCache(int);
void SyncDCache(void *, void *);
void InvalidDCache(void *, void *);
int sceCdRead(unsigned int, unsigned int, void *, SndCdRMode *);
int sceCdSync(int);
int sceCdBreak(void);
int sceCdGetError(void);
SndCdCallback sceCdCallback(SndCdCallback);

void snd_StartSoundSystemEx(unsigned int);
int snd_FlushSoundCommands(void);
int snd_GotReturns(void);
void snd_PrepareReturnBuffer(SndWord *, int);
unsigned int snd_SendIOPCommandAndWait(int, int, char *);
void snd_SendIOPCommandNoWait(int, int, char *, SndCompleteProc, SndUserData);
void snd_PostMessage(void);
void snd_SendCurrentBatch(void);
int snd_StreamSafeCdSync(int);
void snd_SetSoundParams_CB(unsigned int, unsigned int, int, int, int, int, SndCompleteProc, SndUserData);

#ifndef SND_HOST_TEST
typedef char snd_check_word[(sizeof(SndWord) == 4) ? 1 : -1];
typedef char snd_check_pointer[(sizeof(void *) == 4) ? 1 : -1];
typedef char snd_check_return_record[(sizeof(SndCommandReturnDef) == 16) ? 1 : -1];
typedef char snd_check_buffer[(sizeof(SndCommandBuffer) == 4096) ? 1 : -1];
typedef char snd_check_client[(sizeof(SndRpcClient) == 0x28) ? 1 : -1];
typedef char snd_check_status[(sizeof(SndSystemStatus) == 0x40) ? 1 : -1];
typedef char snd_check_ducker[(sizeof(DuckerDef) == 0x18) ? 1 : -1];
#endif
#endif
