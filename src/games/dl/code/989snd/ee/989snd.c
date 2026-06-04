#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StartSoundSystemEx);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_FlushSoundCommands);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_GotReturns);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_PrepareReturnBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_BankLoadByLoc_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_BankLoadFromEE);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_ResolveBankXREFS);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_UnloadBank);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_UnloadBank_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SetMasterVolume);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SetMasterVolumeDucker);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SetPlaybackMode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SetGroupVoiceRange);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SetReverbMode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_PlaySoundVolPanPMPB_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StopSound);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StopAllSounds);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_PauseAllSoundsInGroup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_ContinueAllSoundsInGroup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StopAllSoundsInGroup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SoundIsStillPlaying);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SoundIsStillPlaying_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SetSoundParams_A);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SetSoundParams_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SendIOPCommandAndWait);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SendIOPCommandNoWait);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_PostMessage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SendCurrentBatch);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_InitVAGStreamingEx);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_CloseVAGStreaming);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_PlayVAGStreamByLocEx_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_PauseVAGStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_ContinueVAGStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_GetVAGStreamQueueCount_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_GetVAGStreamTimeRemaining_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_IsVAGStreamBuffered_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StreamSafeCdRead);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StreamSafeCdSync);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StreamSafeCdBreak);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StreamSafeCdGetError);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StreamSafeCdCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SetReverbEx);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_PreAllocReverbWorkArea);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_AutoReverb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_SRAMGetFreeMem);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_InitMovieSoundEx);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_ResetMovieSound);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_CloseMovieSound);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_StartMovieSoundEx);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_GetTransStatus);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_UpdateMovieADPCM);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_GetMovieNAX);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_DoExternCall);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_DoExternCall_A);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_DoExternCall_CB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_DoExternCallWithData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/989snd/ee/989snd", snd_GetDopplerPitchMod);
