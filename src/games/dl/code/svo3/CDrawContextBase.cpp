#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_CDrawContextBase_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "CDrawContextBase.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_CDrawContextBase_" #name)))

SECTION(RenderAssert) long RenderAssert(void *self, void *context)
{
    return 0;
}

SECTION(TransitionPageOff) long TransitionPageOff(void *self)
{
    return 1;
}

SECTION(TransitionPageOn) long TransitionPageOn(void *self)
{
    return 1;
}

SECTION(TransitionPopupPageOff) long TransitionPopupPageOff(void *self)
{
    return 1;
}

SECTION(TransitionPopupPageOn) long TransitionPopupPageOn(void *self)
{
    return 1;
}

SECTION(DrawVKB) void DrawVKB(CDrawContextBase *draw)
{
    // Retail has no default virtual keyboard renderer.
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawButton);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawDownloadThrobber);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawGenericListboxFrame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawGridBorder);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawGridCell);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawGridHeader);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawGridScrollbars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawInputBox);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawListBox);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawPopupBackground);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawSelect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawStaticImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawTextArea);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", drawTicker);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", TrimToFitDisplaySize);
