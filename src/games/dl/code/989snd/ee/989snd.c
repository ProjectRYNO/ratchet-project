#include "common.h"

// Recovered from Deadlocked's own EE instructions; see DOCS/989SND_REUSE.md.
// Deadlocked EE ABI: wire words and bank handles are 32 bits; callback data is 64 bits.
typedef unsigned long long SndUserData;
typedef void (*SndCompleteProc)(unsigned int result, SndUserData user_data);
unsigned int snd_SendIOPCommandAndWait(int command, int size, char *data);
void snd_SendIOPCommandNoWait(int command, int size, char *data, SndCompleteProc cb, SndUserData user_data);
void snd_SetSoundParams_CB(unsigned int handle, unsigned int mask, int vol, int pan, int pitch_mod, int bend, SndCompleteProc cb, SndUserData user_data);

#define SND_SECTION(name) __attribute__((section(".snd_" #name)))

// Keep each remaining assembly function in its original address slot as C replaces its neighbors.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) __asm__( \
    ".section .snd_" #NAME ",\"ax\",@progbits\n" \
    ".set noat\n.set noreorder\n" \
    ".include \"" FOLDER "/" #NAME ".s\"\n" \
    ".set reorder\n.set at\n.section .text\n")
#endif


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StartSoundSystemEx);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_FlushSoundCommands);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_00158188);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_GotReturns);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_PrepareReturnBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_001582A0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_BankLoadByLoc_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_BankLoadFromEE);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_00158550);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SetMasterVolumeDucker);

void SND_SECTION(snd_SetPlaybackMode) snd_SetPlaybackMode(int mode)
{
    unsigned int data[1] = {mode};
    snd_SendIOPCommandNoWait(0x0B, 4, (char *)data, 0, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_001586D8);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_00158760);

void SND_SECTION(snd_PlaySoundVolPanPMPB_CB) snd_PlaySoundVolPanPMPB_CB(unsigned int bank, int sound, int vol, int pan, int pitch_mod, int bend, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[6] = {bank, sound, vol, pan, pitch_mod, bend};
    snd_SendIOPCommandNoWait(0x11, 24, (char *)data, cb, user_data);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_001587C8);

void SND_SECTION(snd_StopSound) snd_StopSound(unsigned int handle)
{
    unsigned int data[1] = {handle};
    snd_SendIOPCommandNoWait(0x15, 4, (char *)data, 0, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_00158810);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_00158950);

void SND_SECTION(snd_SetSoundParams_A) snd_SetSoundParams_A(unsigned int handle, unsigned int mask, int vol, int pan, int pitch_mod, int bend)
{
    snd_SetSoundParams_CB(handle, mask, vol, pan, pitch_mod, bend, 0, 0);
}

void SND_SECTION(snd_SetSoundParams_CB) snd_SetSoundParams_CB(unsigned int handle, unsigned int mask, int vol, int pan, int pitch_mod, int bend, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[6] = {handle, mask, vol, pan, pitch_mod, bend};
    snd_SendIOPCommandNoWait(0x21, 24, (char *)data, cb, user_data);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_001589F0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SendIOPCommandAndWait);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SendIOPCommandNoWait);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_PostMessage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SendCurrentBatch);

void SND_SECTION(snd_StartCaching) snd_StartCaching(void)
{
    // These entry points are no-ops in Deadlocked.
}

void SND_SECTION(snd_SendCache) snd_SendCache(void)
{
    // These entry points are no-ops in Deadlocked.
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_InitVAGStreamingEx);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_001591D8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_CloseVAGStreaming);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_00159250);

void SND_SECTION(snd_PlayVAGStreamByLocEx_CB) snd_PlayVAGStreamByLocEx_CB(int loc1, int loc2, int offset1, int offset2, int vol, int pan, int vol_group, unsigned int queue, int sub_group, unsigned int flags, SndCompleteProc cb, SndUserData user_data)
{
    unsigned int data[8] = {loc1, loc2, ((unsigned int)vol << 16) | ((unsigned int)offset1 & 0xFFFF), ((unsigned int)pan << 16) | ((unsigned int)offset2 & 0xFFFF), vol_group, queue, sub_group, flags};
    snd_SendIOPCommandNoWait(0x2C, 32, (char *)data, cb, user_data);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_001592C8);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StreamSafeCdRead);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StreamSafeCdSync);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StreamSafeCdBreak);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StreamSafeCdGetError);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_001595A8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StreamSafeCdCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_001595E8);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_001596B0);

int SND_SECTION(snd_SRAMGetFreeMem) snd_SRAMGetFreeMem(void)
{
    return snd_SendIOPCommandAndWait(0x4A, 0, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_00159700);

int SND_SECTION(snd_InitMovieSoundEx) snd_InitMovieSoundEx(int sizeOfIOPBuffer, int sizeOfSPUBuffer, int volumeLevel, int panCenter, int volumeGroup, int type)
{
    unsigned int data[6] = {sizeOfIOPBuffer, sizeOfSPUBuffer, volumeLevel, panCenter, volumeGroup, type};
    return snd_SendIOPCommandAndWait(0x3B, 24, (char *)data);
}

void SND_SECTION(snd_ResetMovieSound) snd_ResetMovieSound(void)
{
    snd_SendIOPCommandAndWait(0x3D, 0, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_00159780);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", func_00159980);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_GetDopplerPitchMod);
