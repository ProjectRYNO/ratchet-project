#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SelectTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SelectTag.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_SelectTag_" #name)))

SECTION(FreeResources___dupe15) void FreeResources___dupe15(SVTag *tag)
{
    FreeContexts(tag);
}

long IsSelectable___dupe10(SelectTagState *tag);
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", IsSelectable___dupe10);

SECTION(GetValue) char *GetValue(SelectTagState *tag)
{
    return tag->m_values[tag->m_currOptionIdx];
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", _SelectTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", advanceCurrOption);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", changeCurOptionToNextLetterInAlphabet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", DefaultInit___dupe9);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", Draw___dupe13);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", FindParentForm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", getCurrOptionStrPtr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", HandleInput___dupe40);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", populateSelectOptions);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", RegisterWithForm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", SelectTag);
