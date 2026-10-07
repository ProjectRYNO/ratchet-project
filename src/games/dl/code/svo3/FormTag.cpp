#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_FormTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_FormTag_" #name)))

SECTION(IsSelectable___dupe13) long IsSelectable___dupe13(void *self)
{
    return 0;
}

SECTION(FreeResources___dupe30) void FreeResources___dupe30(SVTag *tag)
{
    FreeContexts(tag);
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", AddCheckboxElement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", AddHiddenElement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", AddPasswordElement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", AddRadioElement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", AddSelectElement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", AddSubmitElement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", AddTextAreaElement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", AddTextElement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", CheckCheckboxElement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", CheckRadioElement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", DataCanBeEncryped);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", DefaultInit___dupe15);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", Draw___dupe21);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", FormTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", HandleInput___dupe47);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", InitRadioGroups);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", Submit);
