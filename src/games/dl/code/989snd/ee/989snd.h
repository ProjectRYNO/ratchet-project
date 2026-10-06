#ifndef SND_EE_H
#define SND_EE_H

/* Names from the prototype decompilation; layout/addresses checked against retail. */
typedef unsigned int SndWord;
typedef unsigned long long SndUserData;
typedef void (*SndCompleteProc)(SndWord result, SndUserData user_data);
typedef void (*SndCdCallback)(int reason);
typedef struct { // 0x1000
    /* 0x0000 */ int num_commands;
    /* 0x0004 */ char buffer[4092];
} SndCommandBuffer;

typedef struct { // 0x10
    /* 0x00 */ SndCompleteProc done;
    /* 0x08 */ SndUserData u_data;
} SndCommandReturnDef;

typedef struct { // 0x04
    /* 0x00 */ unsigned short command;
    /* 0x02 */ unsigned short size;
} SndCommandEntry;

typedef struct { // 0x28
    /* 0x00 */ char header[0x24];
    /* 0x24 */ SndWord server;
} SndRpcClient;

typedef struct { // 0x40
    /* 0x00 */ int cd_busy;
    /* 0x04 */ int pad_0;
    /* 0x08 */ int pad_1;
    /* 0x0C */ int pad_2;
    /* 0x10 */ int cd_error;
    /* 0x14 */ int pad_3;
    /* 0x18 */ int pad_4;
    /* 0x1C */ int pad_5;
    /* 0x20 */ char pad_big[32];
} SndSystemStatus;

typedef struct { // 0x04
    /* 0x00 */ unsigned char trycount;
    /* 0x01 */ unsigned char spindlctrl;
    /* 0x02 */ unsigned char datapattern;
    /* 0x03 */ unsigned char pad;
} SndCdRMode;

typedef struct { // 0x18
    /* 0x00 */ int source_group;
    /* 0x04 */ unsigned int target_groups;
    /* 0x08 */ int full_duck_mult;
    /* 0x0C */ int attack_time;
    /* 0x10 */ int release_time;
    /* 0x14 */ int current_duck_mult;
} DuckerDef;

/* Existing data allocations, never new copies of library state. */
extern SndWord *gCommBusy;
extern int gAwaitingInts;
extern int gLocalLoadError;
extern int gStreamingInited;
extern SndCdCallback gCdCallback;
extern int gSSRead;
extern int gSSReadDone;
extern int gLoadingFromFS;
extern SndCommandBuffer *gSndCommandBuffePtr[2];
extern int gCommandBuffeBytesAvail[2];
extern SndCommandReturnDef *gSndCommandReturnDefPtr[2];
extern SndWord *gReturnValuesPtr[2];
extern int gCommandFillBuffer;
extern int gCaching;
extern SndWord gLoadBusy;
extern SndCommandReturnDef gLoadReturnDef;
extern SndCompleteProc gLoadCB;
extern SndUserData gLoadUserData;
extern int gPrefs_Silent;
extern SndRpcClient gSLClientData;
extern SndWord gSyncBuffer[16];
extern char gSyncSendBuffer[512];
extern SndCommandBuffer gSndCommandBuffer1;
extern SndCommandBuffer gSndCommandBuffer2;
extern SndCommandReturnDef gSndCommandReturnDef1[256];
extern SndCommandReturnDef gSndCommandReturnDef2[256];
extern SndWord gActualReturnValues1[264];
extern SndWord gActualReturnValues2[264];
extern SndSystemStatus gStats;
extern SndRpcClient gSLClientLoaderData;
extern SndWord gLoadReturnValue;
extern int gLoadParams[8];

extern const char sndBindError[];
extern const char sndSourceFile[];
extern const char sndMissingReturns[];
extern const char sndCollision[];
extern const char sndLocBusy[];
extern const char sndCdBusy[];
extern const char sndEeBusy[];
extern const char sndEeLoadError[];
extern const char sndExternalTooLarge[];
extern const char sndCommandTooLarge[];
extern const char sndBufferFull[];
extern const char sndContinuing[];

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

#endif
