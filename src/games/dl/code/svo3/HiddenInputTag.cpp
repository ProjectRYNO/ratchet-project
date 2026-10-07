#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_HiddenInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_HiddenInputTag_" #name)))

SECTION(HandleInput___dupe51) long HandleInput___dupe51(void *self, void *context)
{
    return 1;
}

SECTION(IsSelectable___dupe16) long IsSelectable___dupe16(void *self)
{
    return 0;
}

SECTION(FreeResources___dupe40) void FreeResources___dupe40(SVTag *tag)
{
    FreeContexts(tag);
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HiddenInputTag", DefaultInit___dupe19);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HiddenInputTag", FindParentForm___dupe6);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HiddenInputTag", HiddenInputTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HiddenInputTag", RegisterWithForm___dupe6);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/HiddenInputTag", SetValue);
