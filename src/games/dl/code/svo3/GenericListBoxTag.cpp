#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_GenericListBoxTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {
extern char svoGenericListBoxTagSource[];

#define SECTION(name) __attribute__((section(".svo_GenericListBoxTag_" #name)))

SECTION(FreeResources___dupe56) void FreeResources___dupe56(SVTag *tag)
{
    __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x70);
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", _GenericListBoxTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", addHandle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", changeSelectedItem___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", clearList);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", DefaultInit___dupe23);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", deleteHandle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", Draw___dupe26);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", GenericListBoxTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", getHandleByIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", getIndexOfHandle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", getNumVisibleRows___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", getSelectedHandle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", getSelectedIndex___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", getTopVisibleIndex___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", HandleInput___dupe54);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", selectIndex___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", size);
