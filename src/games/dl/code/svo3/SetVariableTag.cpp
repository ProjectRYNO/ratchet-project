#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SetVariableTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern "C" {
extern const SVTagVtablePrefix svoSetVariableTagVtable;
void FreeResources___dupe9(void *tag);
}
#define SECTION(name) __attribute__((section(".svo_SetVariableTag_" #name)))

SECTION(FreeResources___dupe9) void FreeResources___dupe9(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(IsSelectable___dupe7) long IsSelectable___dupe7(void *self)
{
    return 0;
}

}

extern "C" SECTION(_SetVariableTag) void _SetVariableTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoSetVariableTagVtable;
    FreeResources___dupe9((void *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SetVariableTag", DefaultInit___dupe6);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SetVariableTag", Draw___dupe11);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SetVariableTag", handleDownloadThrobber);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SetVariableTag", handleHTTPSBuffers);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SetVariableTag", handleHTTPSendBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SetVariableTag", HandleInput___dupe37);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SetVariableTag", handleTTYDebugServerSetup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SetVariableTag", SetVariableTag);
