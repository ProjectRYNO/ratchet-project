#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_ImageTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_ImageTag_" #name)))

SECTION(FreeResources___dupe18) void FreeResources___dupe18(SVTag *tag)
{
    FreeContexts(tag);
}

long IsSelectable___dupe11(SVTag *tag);
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", IsSelectable___dupe11);

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", _ImageTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", DefaultInit___dupe10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", Draw___dupe14);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", getImageTypeAttrib);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", HandleInput___dupe41);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", ImageTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", InitImage___dupe2);
