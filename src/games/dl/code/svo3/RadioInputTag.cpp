#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_RadioInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "RadioInputTag.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_RadioInputTag_" #name)))

SECTION(FreeResources___dupe26) void FreeResources___dupe26(SVTag *tag)
{
    FreeContexts(tag);
}

SECTION(SetChecked) void SetChecked(RadioInputTagState *tag, int checked)
{
    if (tag->base.m_bSelectable) tag->m_isChecked = checked;
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RadioInputTag", DefaultInit___dupe13);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RadioInputTag", Draw___dupe19);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RadioInputTag", FindParentForm___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RadioInputTag", HandleInput___dupe45);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RadioInputTag", RadioInputTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RadioInputTag", RegisterWithForm___dupe3);
