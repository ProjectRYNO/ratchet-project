#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SubmitInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_SubmitInputTag_" #name)))

SECTION(IsSelectable___dupe14) long IsSelectable___dupe14(void *self)
{
    return 1;
}

SECTION(FreeResources___dupe32) void FreeResources___dupe32(SVTag *tag)
{
    FreeContexts(tag);
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", DefaultInit___dupe16);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", Draw___dupe22);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", FindParentForm___dupe5);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", HandleInput___dupe48);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", RegisterWithForm___dupe5);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", SubmitInputTag);
