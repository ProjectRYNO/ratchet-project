#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_QuickLinkTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_QuickLinkTag_" #name)))

SECTION(IsSelectable___dupe9) long IsSelectable___dupe9(void *self)
{
    return 0;
}

SECTION(FreeResources___dupe13) void FreeResources___dupe13(SVTag *tag)
{
    FreeContexts(tag);
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/QuickLinkTag", DefaultInit___dupe8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/QuickLinkTag", getPadLinkButtonAttrib);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/QuickLinkTag", HandleInput___dupe39);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/QuickLinkTag", QuickLinkTag);
