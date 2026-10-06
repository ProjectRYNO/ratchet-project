#include "989snd.h"

// Recovered using retail Ghidra, prototype types, and original EE instructions.
#define SND_SECTION(name) __attribute__((section(".snd_" #name)))

void SND_SECTION(snd_StartSoundSystemEx) snd_StartSoundSystemEx(unsigned int flags)
{
    int data[2];
    volatile int delay;
    gSndCommandBuffePtr[0] = &gSndCommandBuffer1;
    gSndCommandBuffePtr[1] = &gSndCommandBuffer2;
    gReturnValuesPtr[0] = gActualReturnValues1;
    gReturnValuesPtr[1] = gActualReturnValues2;
    gSndCommandReturnDefPtr[0] = gSndCommandReturnDef1;
    gSndCommandReturnDefPtr[1] = gSndCommandReturnDef2;
    gPrefs_Silent = (flags & 2) != 0;
    sceSifInitRpc(0);
    do {
        if (sceSifBindRpc(&gSLClientData, 0x123456, 0) < 0) {
            printf(sndBindError, sndSourceFile, 0xB5);
            for (;;) {}
        }
        for (delay = 10000; delay; --delay) {}
    } while (!gSLClientData.server);
    gLoadBusy = 0;
    gLoadReturnDef.done = 0;
    gLoadReturnDef.u_data = 0;
    gLoadReturnValue = 0;
    do {
        if (sceSifBindRpc(&gSLClientLoaderData, 0x123457, 0) < 0) {
            printf(sndBindError, sndSourceFile, 0xCA);
            for (;;) {}
        }
        for (delay = 10000; delay; --delay) {}
    } while (!gSLClientLoaderData.server);
    gCommandBuffeBytesAvail[0] = gCommandBuffeBytesAvail[1] = 4092;
    gSndCommandBuffer1.num_commands = gSndCommandBuffer2.num_commands = 0;
    gStats.cd_busy = gStats.cd_error = 0;
    data[0] = (int)&gStats;
    data[1] = flags;
    snd_SendIOPCommandAndWait(0, 8, (char *)data);
}

/* Use spare room in the initialization slot for this completion helper. */
static void SND_SECTION(snd_StartSoundSystemEx) __attribute__((noinline)) snd_FinishFileLoad(void)
{
    if (gLoadCB) gLoadCB(gSyncBuffer[1], gLoadUserData);
    gLoadCB = 0;
    gLoadingFromFS = 0;
}

int SND_SECTION(snd_FlushSoundCommands) snd_FlushSoundCommands(void)
{
    int which, x;
    SndCompleteProc done;
    SndUserData user_data;
    if (gCommBusy && snd_GotReturns()) {
        if (gLoadingFromFS) {
            snd_FinishFileLoad();
        } else {
            which = gCommandFillBuffer != 1;
            for (x = 0; x < gSndCommandBuffePtr[which]->num_commands; ++x) {
                done = gSndCommandReturnDefPtr[which][x].done;
                if (done) done(gReturnValuesPtr[which][x + 1], gSndCommandReturnDefPtr[which][x].u_data);
            }
        }
    }
    if (gLoadBusy) {
        InvalidDCache(&gLoadReturnValue, &gLoadReturnValue + 1);
        if (gLoadReturnValue != ~0U) {
            done = gLoadReturnDef.done;
            user_data = gLoadReturnDef.u_data;
            if (done) {
                /* Retail clears this record BEFORE the callback. */
                gLoadReturnDef.done = 0;
                gLoadReturnDef.u_data = 0;
                done(gLoadReturnValue, user_data);
            }
            gLoadReturnValue = 0;
            gLoadBusy = 0;
        }
    }
    if (!gCommBusy && gSndCommandBuffePtr[gCommandFillBuffer]->num_commands && !gCaching)
        snd_SendCurrentBatch();
    if (gSSRead) {
        snd_StreamSafeCdSync(1);
        if (gSSReadDone) {
            gSSRead = gSSReadDone = 0;
            if (gCdCallback) gCdCallback(1);
        }
    }
    return gCommBusy != 0 || gLoadBusy != 0;
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_00158188[] SND_SECTION(func_00158188) = {
    0x27BD0010U, 0x00000000U, 0x27BD0010U, 0x00000000U
};

int SND_SECTION(snd_GotReturns) snd_GotReturns(void)
{
    if (!gCommBusy) return 1;
    if (sceSifCheckStatRpc(&gSLClientData)) return 0;
    InvalidDCache(gCommBusy, gCommBusy + gAwaitingInts + 2);
    if (gCommBusy[0] == ~0U && gCommBusy[gAwaitingInts + 1] == ~0U) {
        gCommBusy = 0;
        return 1;
    }
    if (!gPrefs_Silent) printf(sndMissingReturns);
    return 0;
}

void SND_SECTION(snd_PrepareReturnBuffer) snd_PrepareReturnBuffer(SndWord *buffer, int num_ints)
{
    gCommBusy = buffer;
    gAwaitingInts = num_ints;
    buffer[num_ints + 1] = 0;
    buffer[0] = 0;
    /* The original inclusive cache endpoints are byte offsets, not word offsets. */
    SyncDCache(buffer, (char *)buffer + 3);
    SyncDCache(buffer + num_ints + 1, (char *)(buffer + num_ints + 1) + 3);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_001582A0[] SND_SECTION(func_001582A0) = {
    0x27BD0040U, 0x00000000U
};

void SND_SECTION(snd_BankLoadByLoc_CB) snd_BankLoadByLoc_CB(int loc, int offset, SndCompleteProc cb, SndUserData user_data)
{
    gLocalLoadError = 0;
    if (gLoadBusy) {
        if (!gPrefs_Silent) printf(sndLocBusy);
        return;
    }
    if (snd_StreamSafeCdSync(1) == 1) {
        if (!gPrefs_Silent) printf(sndCdBusy);
        return;
    }
    gLoadReturnValue = ~0U;
    SyncDCache(&gLoadReturnValue, &gLoadReturnValue + 1);
    gLoadParams[0] = loc;
    gLoadParams[1] = offset;
    gLoadReturnDef.done = cb;
    gLoadReturnDef.u_data = user_data;
    while (sceSifCheckStatRpc(&gSLClientLoaderData)) {
        if (!gPrefs_Silent) printf(sndCollision);
        snd_FlushSoundCommands();
        FlushCache(0);
    }
    gLoadBusy = 1;
    sceSifCallRpc(&gSLClientLoaderData, 3, 1, gLoadParams, 8, &gLoadReturnValue, 4, 0, 0);
}

unsigned int SND_SECTION(snd_BankLoadFromEE) snd_BankLoadFromEE(void *ee_loc)
{
    gLocalLoadError = 0;
    if (gLoadBusy) {
        if (!gPrefs_Silent) printf(sndEeBusy);
        return 0;
    }
    gLoadReturnValue = ~0U;
    SyncDCache(&gLoadReturnValue, &gLoadReturnValue + 1);
    gLoadParams[0] = (int)ee_loc;
    while (sceSifCheckStatRpc(&gSLClientLoaderData)) {
        if (!gPrefs_Silent) printf(sndCollision);
        snd_FlushSoundCommands();
        FlushCache(0);
    }
    if (sceSifCallRpc(&gSLClientLoaderData, 0x57, 1, gLoadParams, 4, &gLoadReturnValue, 4, 0, 0) < 0) {
        if (!gPrefs_Silent) printf(sndEeLoadError);
        gLocalLoadError = 0x106;
        return 0;
    }
    while (gLoadReturnValue == ~0U) FlushCache(0);
    return gLoadReturnValue;
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_00158550[] SND_SECTION(func_00158550) = {
    0x27BD0040U, 0x00000000U, 0x27BD0040U, 0x00000000U, 0x27BD0040U, 0x00000000U
};

void SND_SECTION(snd_ResolveBankXREFS) snd_ResolveBankXREFS(void)
{
    snd_SendIOPCommandNoWait(0x08, 0, 0, 0, 0);
}

void SND_SECTION(snd_UnloadBank) snd_UnloadBank(unsigned int bank)
{
    unsigned int data[1] = {bank};
    snd_SendIOPCommandNoWait(0x06, 4, (char *)data, 0, 0);
}

void SND_SECTION(snd_UnloadBank_CB) snd_UnloadBank_CB(unsigned int bank, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[1] = {bank};
    snd_SendIOPCommandNoWait(0x06, 4, (char *)data, cb, user_data);
}

void SND_SECTION(snd_SetMasterVolume) snd_SetMasterVolume(int group, int volume)
{
    unsigned int data[2] = {group, volume};
    snd_SendIOPCommandNoWait(0x09, 8, (char *)data, 0, 0);
}

void SND_SECTION(snd_SetMasterVolumeDucker) snd_SetMasterVolumeDucker(int which, const DuckerDef *state)
{
    struct { int which; DuckerDef state; } data;
    data.which = which;
    if (state) data.state = *state;
    else data.state.source_group = -1;
    /* Remaining fields are ignored by the IOP when source_group is -1, as in retail. */
    snd_SendIOPCommandNoWait(0x60, sizeof(data), (char *)&data, 0, 0);
}

void SND_SECTION(snd_SetPlaybackMode) snd_SetPlaybackMode(int mode)
{
    unsigned int data[1] = {mode};
    snd_SendIOPCommandNoWait(0x0B, 4, (char *)data, 0, 0);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_001586D8[] SND_SECTION(func_001586D8) = {
    0x27BD0010U, 0x00000000U, 0x27BD0010U, 0x00000000U, 0x27BD0020U, 0x00000000U
};

void SND_SECTION(snd_SetGroupVoiceRange) snd_SetGroupVoiceRange(int group, int min, int max)
{
    unsigned int data[3] = {group, min, max};
    snd_SendIOPCommandNoWait(0x4E, 12, (char *)data, 0, 0);
}

void SND_SECTION(snd_SetReverbMode) snd_SetReverbMode(int mode)
{
    unsigned int data[1] = {mode};
    snd_SendIOPCommandNoWait(0x64, 4, (char *)data, 0, 0);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_00158760[] SND_SECTION(func_00158760) = {
    0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0030U, 0x00000000U, 0x27BD0030U, 0x00000000U
};

void SND_SECTION(snd_PlaySoundVolPanPMPB_CB) snd_PlaySoundVolPanPMPB_CB(unsigned int bank, int sound, int vol, int pan, int pitch_mod, int bend, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[6] = {bank, sound, vol, pan, pitch_mod, bend};
    snd_SendIOPCommandNoWait(0x11, 24, (char *)data, cb, user_data);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_001587C8[] SND_SECTION(func_001587C8) = {
    0x27BD0010U, 0x00000000U, 0x27BD0010U, 0x00000000U, 0x27BD0010U, 0x00000000U
};

void SND_SECTION(snd_StopSound) snd_StopSound(unsigned int handle)
{
    unsigned int data[1] = {handle};
    snd_SendIOPCommandNoWait(0x15, 4, (char *)data, 0, 0);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_00158810[] SND_SECTION(func_00158810) = {
    0x27BD0040U, 0x00000000U, 0x27BD0040U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0030U, 0x00000000U, 0x27BD0020U, 0x00000000U
};

void SND_SECTION(snd_StopAllSounds) snd_StopAllSounds(void)
{
    snd_SendIOPCommandNoWait(0x18, 0, 0, 0, 0);
}

void SND_SECTION(snd_PauseAllSoundsInGroup) snd_PauseAllSoundsInGroup(unsigned int groups)
{
    unsigned int data[1] = {groups};
    snd_SendIOPCommandNoWait(0x16, 4, (char *)data, 0, 0);
}

void SND_SECTION(snd_ContinueAllSoundsInGroup) snd_ContinueAllSoundsInGroup(unsigned int groups)
{
    unsigned int data[1] = {groups};
    snd_SendIOPCommandNoWait(0x17, 4, (char *)data, 0, 0);
}

void SND_SECTION(snd_StopAllSoundsInGroup) snd_StopAllSoundsInGroup(unsigned int groups)
{
    unsigned int data[1] = {groups};
    snd_SendIOPCommandNoWait(0x61, 4, (char *)data, 0, 0);
}

unsigned int SND_SECTION(snd_SoundIsStillPlaying) snd_SoundIsStillPlaying(unsigned int handle)
{
    unsigned int data[1] = {handle};
    return snd_SendIOPCommandAndWait(0x19, 4, (char *)data);
}

void SND_SECTION(snd_SoundIsStillPlaying_CB) snd_SoundIsStillPlaying_CB(unsigned int handle, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[1] = {handle};
    snd_SendIOPCommandNoWait(0x19, 4, (char *)data, cb, user_data);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_00158950[] SND_SECTION(func_00158950) = {
    0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0030U, 0x00000000U
};

void SND_SECTION(snd_SetSoundParams_A) snd_SetSoundParams_A(unsigned int handle, unsigned int mask, int vol, int pan, int pitch_mod, int bend)
{
    snd_SetSoundParams_CB(handle, mask, vol, pan, pitch_mod, bend, 0, 0);
}

void SND_SECTION(snd_SetSoundParams_CB) snd_SetSoundParams_CB(unsigned int handle, unsigned int mask, int vol, int pan, int pitch_mod, int bend, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[6] = {handle, mask, vol, pan, pitch_mod, bend};
    snd_SendIOPCommandNoWait(0x21, 24, (char *)data, cb, user_data);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_001589F0[] SND_SECTION(func_001589F0) = {
    0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0010U, 0x00000000U, 0x27BD0010U, 0x00000000U
};

unsigned int SND_SECTION(snd_SendIOPCommandAndWait) snd_SendIOPCommandAndWait(int command, int data_size, char *data)
{
    int i;
    unsigned int result;
    if (command == 0x68) {
        if ((unsigned int)((int *)data)[2] + 12 > 512) {
            printf(sndExternalTooLarge);
            for (;;) {}
        }
        for (i = 0; i < 12; ++i) gSyncSendBuffer[i] = data[i];
        memcpy(gSyncSendBuffer + 12, ((void **)data)[3], ((int *)data)[2]);
    } else {
        for (i = 0; i < data_size; ++i) gSyncSendBuffer[i] = data[i];
    }
    while (gCommBusy) {
        snd_FlushSoundCommands();
        FlushCache(0);
    }
    snd_PrepareReturnBuffer(gSyncBuffer, 1);
    while (sceSifCheckStatRpc(&gSLClientData)) {
        if (!gPrefs_Silent) printf(sndCollision);
        snd_FlushSoundCommands();
        FlushCache(0);
    }
    sceSifCallRpc(&gSLClientData, command, 1, data_size ? gSyncSendBuffer : 0, data_size, gSyncBuffer, 12, 0, 0);
    while (!snd_GotReturns()) {}
    result = gSyncBuffer[1];
    if (gSndCommandBuffePtr[gCommandFillBuffer]->num_commands && !gCaching) snd_SendCurrentBatch();
    return result;
}

void SND_SECTION(snd_SendIOPCommandNoWait) snd_SendIOPCommandNoWait(int command, int data_size, char *data, SndCompleteProc done, SndUserData user_data)
{
    int msg_size, waited = 0, was_caching = 0, i;
    SndCommandEntry *entry;
    char *payload;
    int index;
    if (!gCaching && !gCommBusy && !data_size && !done) {
        snd_PrepareReturnBuffer(gSyncBuffer, 1);
        while (sceSifCheckStatRpc(&gSLClientData)) {
            if (!gPrefs_Silent) printf(sndCollision);
            snd_FlushSoundCommands();
            FlushCache(0);
        }
        sceSifCallRpc(&gSLClientData, command, 1, 0, 0, gSyncBuffer, 12, 0, 0);
        return;
    }
    msg_size = data_size + 4;
    if (msg_size & 3) msg_size += 4 - msg_size % 4;
    if (msg_size > 512) {
        printf(sndCommandTooLarge);
        for (;;) {}
    }
    while (gSndCommandBuffePtr[gCommandFillBuffer]->num_commands == 256 ||
           gCommandBuffeBytesAvail[gCommandFillBuffer] < msg_size) {
        if (gCaching) { gCaching = 0; was_caching = 1; }
        snd_FlushSoundCommands();
        if (waited == 1 && !gPrefs_Silent)
            printf(sndBufferFull, gCommandFillBuffer, gSndCommandBuffePtr[gCommandFillBuffer]->num_commands);
        ++waited;
    }
    if (waited && !gPrefs_Silent) printf(sndContinuing, waited);
    if (was_caching) gCaching = 1;
    entry = (SndCommandEntry *)((char *)gSndCommandBuffePtr[gCommandFillBuffer] + 4096 - gCommandBuffeBytesAvail[gCommandFillBuffer]);
    entry->command = command;
    entry->size = data_size;
    payload = (char *)(entry + 1);
    if (command == 0x68) {
        for (i = 0; i < 12; ++i) payload[i] = data[i];
        memcpy(payload + 12, ((void **)data)[3], ((int *)data)[2]);
    } else {
        for (i = 0; i < data_size; ++i) payload[i] = data[i];
    }
    gCommandBuffeBytesAvail[gCommandFillBuffer] -= msg_size;
    index = gSndCommandBuffePtr[gCommandFillBuffer]->num_commands;
    gSndCommandReturnDefPtr[gCommandFillBuffer][index].done = done;
    gSndCommandReturnDefPtr[gCommandFillBuffer][index].u_data = user_data;
    snd_PostMessage();
}

void SND_SECTION(snd_PostMessage) snd_PostMessage(void)
{
    ++gSndCommandBuffePtr[gCommandFillBuffer]->num_commands;
    snd_FlushSoundCommands();
}

void SND_SECTION(snd_SendCurrentBatch) snd_SendCurrentBatch(void)
{
    snd_PrepareReturnBuffer(gReturnValuesPtr[gCommandFillBuffer], gSndCommandBuffePtr[gCommandFillBuffer]->num_commands);
    while (sceSifCheckStatRpc(&gSLClientData)) {
        if (!gPrefs_Silent) printf(sndCollision);
        FlushCache(0);
    }
    sceSifCallRpc(&gSLClientData, 0x4D, 1, gSndCommandBuffePtr[gCommandFillBuffer],
        4096 - gCommandBuffeBytesAvail[gCommandFillBuffer], gReturnValuesPtr[gCommandFillBuffer],
        4 * gSndCommandBuffePtr[gCommandFillBuffer]->num_commands + 8, 0, 0);
    gCommandFillBuffer = gCommandFillBuffer != 1;
    gSndCommandBuffePtr[gCommandFillBuffer]->num_commands = 0;
    gCommandBuffeBytesAvail[gCommandFillBuffer] = 4092;
}

void SND_SECTION(snd_StartCaching) snd_StartCaching(void)
{
    // These entry points are no-ops in Deadlocked.
}

void SND_SECTION(snd_SendCache) snd_SendCache(void)
{
    // These entry points are no-ops in Deadlocked.
}

int SND_SECTION(snd_InitVAGStreamingEx) snd_InitVAGStreamingEx(int channels, int buffer_size, unsigned int read_mode, int streamsafe)
{
    unsigned int data[4], result;
    int busy;
    if (gStreamingInited == 1) return 0;
    busy = gLoadBusy;
    while (busy) busy = snd_FlushSoundCommands();
    snd_StreamSafeCdSync(0);
    data[0] = channels; data[1] = buffer_size; data[2] = read_mode; data[3] = streamsafe;
    result = snd_SendIOPCommandAndWait(0x2A, 16, (char *)data);
    gStreamingInited = result;
    return result;
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_001591D8[] SND_SECTION(func_001591D8) = {
    0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0010U, 0x00000000U
};

void SND_SECTION(snd_CloseVAGStreaming) snd_CloseVAGStreaming(void)
{
    int busy = gLoadBusy;
    if (gStreamingInited) {
        while (busy) busy = snd_FlushSoundCommands();
        snd_StreamSafeCdSync(0);
        snd_SendIOPCommandAndWait(0x35, 0, 0);
        gStreamingInited = 0;
    }
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_00159250[] SND_SECTION(func_00159250) = {
    0x27BD0030U, 0x00000000U
};

void SND_SECTION(snd_PlayVAGStreamByLocEx_CB) snd_PlayVAGStreamByLocEx_CB(int loc1, int loc2, int offset1, int offset2, int vol, int pan, int vol_group, unsigned int queue, int sub_group, unsigned int flags, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[8] = {loc1, loc2, ((unsigned int)vol << 16) | ((unsigned int)offset1 & 0xFFFF), ((unsigned int)pan << 16) | ((unsigned int)offset2 & 0xFFFF), vol_group, queue, sub_group, flags};
    snd_SendIOPCommandNoWait(0x2C, 32, (char *)data, cb, user_data);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_001592C8[] SND_SECTION(func_001592C8) = {
    0x27BD0120U, 0x00000000U, 0x27BD0120U, 0x00000000U
};

void SND_SECTION(snd_PauseVAGStream) snd_PauseVAGStream(unsigned int stream)
{
    unsigned int data[1] = {stream};
    snd_SendIOPCommandNoWait(0x2D, 4, (char *)data, 0, 0);
}

void SND_SECTION(snd_ContinueVAGStream) snd_ContinueVAGStream(unsigned int stream)
{
    unsigned int data[1] = {stream};
    snd_SendIOPCommandNoWait(0x2E, 4, (char *)data, 0, 0);
}

void SND_SECTION(snd_GetVAGStreamQueueCount_CB) snd_GetVAGStreamQueueCount_CB(unsigned int stream, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[1] = {stream};
    snd_SendIOPCommandNoWait(0x30, 4, (char *)data, cb, user_data);
}

void SND_SECTION(snd_GetVAGStreamTimeRemaining_CB) snd_GetVAGStreamTimeRemaining_CB(unsigned int stream, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[1] = {stream};
    snd_SendIOPCommandNoWait(0x32, 4, (char *)data, cb, user_data);
}

void SND_SECTION(snd_IsVAGStreamBuffered_CB) snd_IsVAGStreamBuffered_CB(unsigned int stream, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[1] = {stream};
    snd_SendIOPCommandNoWait(0x4F, 4, (char *)data, cb, user_data);
}

int SND_SECTION(snd_StreamSafeCdRead) snd_StreamSafeCdRead(unsigned int lbn, unsigned int sectors, void *buf, SndCdRMode *mode)
{
    unsigned int data[3];
    if (!gStreamingInited) return sceCdRead(lbn, sectors, buf, mode);
    if (snd_StreamSafeCdSync(1) == 1) return 0;
    gStats.cd_busy = 1;
    gStats.cd_error = 0;
    FlushCache(0);
    gSSRead = 1; gSSReadDone = 0;
    data[0] = lbn; data[1] = sectors; data[2] = (unsigned int)buf;
    snd_SendIOPCommandNoWait(0x38, 12, (char *)data, 0, 0);
    return 1;
}

int SND_SECTION(snd_StreamSafeCdSync) snd_StreamSafeCdSync(int mode)
{
    if (!gStreamingInited) return sceCdSync(mode);
    FlushCache(0);
    gSSReadDone = gStats.cd_busy == 0;
    if (gSSReadDone) return 0;
    if (mode == 1) return 1;
    do {
        snd_FlushSoundCommands();
        FlushCache(0);
        gSSReadDone = gStats.cd_busy == 0;
    } while (!gSSReadDone);
    return 0;
}

int SND_SECTION(snd_StreamSafeCdBreak) snd_StreamSafeCdBreak(void)
{
    if (!gStreamingInited) return sceCdBreak();
    snd_SendIOPCommandNoWait(0x37, 0, 0, 0, 0);
    return 1;
}

int SND_SECTION(snd_StreamSafeCdGetError) snd_StreamSafeCdGetError(void)
{
    if (!gStreamingInited) return sceCdGetError();
    return gStats.cd_error;
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_001595A8[] SND_SECTION(func_001595A8) = {
    0x27BD0010U, 0x00000000U, 0x27BD0010U, 0x00000000U
};

/* GCC's shared epilogue exceeds the original entry slot by one instruction.
 * Keep the public entry fixed and place its C implementation in initialization
 * padding, alongside the file-load completion helper. */
static SndCdCallback SND_SECTION(snd_StartSoundSystemEx) __attribute__((noinline)) snd_ChangeCdCallback(SndCdCallback callback)
{
    SndCdCallback previous;
    if (!gStreamingInited) previous = sceCdCallback(callback);
    else {
        previous = gCdCallback;
        gCdCallback = callback;
    }
    return previous;
}

SndCdCallback SND_SECTION(snd_StreamSafeCdCallback) snd_StreamSafeCdCallback(SndCdCallback callback)
{
    return snd_ChangeCdCallback(callback);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_001595E8[] SND_SECTION(func_001595E8) = {
    0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U
};

void SND_SECTION(snd_SetReverbEx) snd_SetReverbEx(int core, int type, int depth, int delay, int feedback)
{
    unsigned int data[5] = {core, type, depth, delay, feedback};
    snd_SendIOPCommandNoWait(0x50, 20, (char *)data, 0, 0);
}

void SND_SECTION(snd_PreAllocReverbWorkArea) snd_PreAllocReverbWorkArea(int core, int type)
{
    unsigned int data[2] = {core, type};
    snd_SendIOPCommandNoWait(0x51, 8, (char *)data, 0, 0);
}

void SND_SECTION(snd_AutoReverb) snd_AutoReverb(int core, int depth, int delta_time, int channel_flags)
{
    unsigned int data[4] = {core, depth, delta_time, channel_flags};
    snd_SendIOPCommandNoWait(0x10, 16, (char *)data, 0, 0);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_001596B0[] SND_SECTION(func_001596B0) = {
    0x27BD0010U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0010U, 0x00000000U, 0x27BD0020U, 0x00000000U, 0x27BD0020U, 0x00000000U
};

int SND_SECTION(snd_SRAMGetFreeMem) snd_SRAMGetFreeMem(void)
{
    return snd_SendIOPCommandAndWait(0x4A, 0, 0);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_00159700[] SND_SECTION(func_00159700) = {
    0x27BD0010U, 0x00000000U, 0x27BD0010U, 0x00000000U, 0x27BD0010U, 0x00000000U
};

int SND_SECTION(snd_InitMovieSoundEx) snd_InitMovieSoundEx(int sizeOfIOPBuffer, int sizeOfSPUBuffer, int volumeLevel, int panCenter, int volumeGroup, int type)
{
    unsigned int data[6] = {sizeOfIOPBuffer, sizeOfSPUBuffer, volumeLevel, panCenter, volumeGroup, type};
    return snd_SendIOPCommandAndWait(0x3B, 24, (char *)data);
}

void SND_SECTION(snd_ResetMovieSound) snd_ResetMovieSound(void)
{
    snd_SendIOPCommandAndWait(0x3D, 0, 0);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_00159780[] SND_SECTION(func_00159780) = {
    0x27BD0010U, 0x00000000U, 0x27BD0020U, 0x00000000U
};

void SND_SECTION(snd_CloseMovieSound) snd_CloseMovieSound(void)
{
    snd_SendIOPCommandAndWait(0x3C, 0, 0);
}

void SND_SECTION(snd_StartMovieSoundEx) snd_StartMovieSoundEx(int iopBuffer, int iopBufferSize, int iopPausePosition, unsigned int sr, int ch)
{
    unsigned int data[5] = {iopBuffer, iopBufferSize, iopPausePosition, sr, ch};
    snd_SendIOPCommandAndWait(0x3E, 20, (char *)data);
}

int SND_SECTION(snd_GetTransStatus) snd_GetTransStatus(void)
{
    return snd_SendIOPCommandAndWait(0x40, 0, 0);
}

void SND_SECTION(snd_UpdateMovieADPCM) snd_UpdateMovieADPCM(int data_size, unsigned int offset)
{
    unsigned int data[2] = {data_size, offset};
    snd_SendIOPCommandAndWait(0x5A, 8, (char *)data);
}

unsigned int SND_SECTION(snd_GetMovieNAX) snd_GetMovieNAX(void)
{
    return snd_SendIOPCommandAndWait(0x5B, 0, 0);
}

int SND_SECTION(snd_DoExternCall) snd_DoExternCall(unsigned int proc_id, int func_index, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    unsigned int data[7] = {proc_id, func_index, arg1, arg2, arg3, arg4, arg5};
    return snd_SendIOPCommandAndWait(0x4C, 28, (char *)data);
}

void SND_SECTION(snd_DoExternCall_A) snd_DoExternCall_A(unsigned int proc_id, int func_index, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    unsigned int data[7] = {proc_id, func_index, arg1, arg2, arg3, arg4, arg5};
    snd_SendIOPCommandNoWait(0x4C, 28, (char *)data, 0, 0);
}

void SND_SECTION(snd_DoExternCall_CB) snd_DoExternCall_CB(unsigned int proc_id, int func_index, int arg1, int arg2, int arg3, int arg4, int arg5, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[7] = {proc_id, func_index, arg1, arg2, arg3, arg4, arg5};
    snd_SendIOPCommandNoWait(0x4C, 28, (char *)data, cb, user_data);
}

int SND_SECTION(snd_DoExternCallWithData) snd_DoExternCallWithData(unsigned int proc_id, int func_index, int data_size, void *data_ptr)
{
    // The transport copies this 12-byte header and then follows the EE pointer.
    unsigned int data[4] = {proc_id, func_index, data_size, (unsigned int)data_ptr};
    return snd_SendIOPCommandAndWait(0x68, data_size + 12, (char *)data);
}

/* Linker remnants, not callable functions; preserve original words. */
const unsigned int func_00159980[] SND_SECTION(func_00159980) = {
    0x27BD0020U, 0x00000000U
};

int SND_SECTION(snd_GetDopplerPitchMod) snd_GetDopplerPitchMod(int approaching_mph)
{
    /* EE MULT retains the low signed 32 bits before signed division. */
    return (int)((unsigned int)approaching_mph * 1524U) / 741;
}
