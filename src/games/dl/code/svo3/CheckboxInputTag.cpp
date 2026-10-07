#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_CheckboxInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_CheckboxInputTag_" #name)))

SECTION(FreeResources___dupe28) void FreeResources___dupe28(void *self)
{
    // Retail implements this callback as a no-op.
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", _CheckboxInputTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", CheckboxInputTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", DefaultInit___dupe14);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", Draw___dupe20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", FindParentForm___dupe4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", HandleInput___dupe46);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", RegisterWithForm___dupe4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", ToggleChecked);
