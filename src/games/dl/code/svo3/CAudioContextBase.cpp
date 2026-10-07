#include "CAudioContextBase.h"

extern "C" const char svoAudioContextVtable[];

extern "C" __attribute__((section(".svo_audio_CAudioContextBase")))
const void *CAudioContextBase(CAudioContextBaseState *context)
{
    // Preserve retail's v0 value as well as its vtable store.
    return context->vtable = svoAudioContextVtable;
}
