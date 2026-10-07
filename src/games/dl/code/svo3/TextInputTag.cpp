#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_TextInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "TextInputTag.h"

extern "C" {
void DrawImpl(TextInputTagState *tag, char *text);

#define SECTION(name) __attribute__((section(".svo_TextInputTag_" #name)))

SECTION(FreeResources___dupe23) void FreeResources___dupe23(SVTag *tag)
{
    FreeContexts(tag);
}

SECTION(Draw___dupe17) void Draw___dupe17(TextInputTagState *tag)
{
    DrawImpl(tag, tag->m_text);
}

SECTION(GetMaxLengthUTF8Chars___dupe2) long GetMaxLengthUTF8Chars___dupe2(TextInputTagState *tag)
{
    return tag->m_maxLengthUTF8Chars;
}

SECTION(GetMaxLengthBytes___dupe2) long GetMaxLengthBytes___dupe2(TextInputTagState *tag)
{
    return 0x200;
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", defaultInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", drawCursor);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", DrawImpl);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", DumpSubstring);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", findParentForm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", GetEditPosition___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", getSubstringPixelWidth);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", getSubstringPixelWidthImpl);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", GetText___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", HandleInput___dupe44);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", handleKeyboardInput___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", handleSpecialKeys___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", InitialiseFromXml);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", registerWithForm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", resetTextInput);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", scrollTextLeftToFillWindow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", scrollTextRightToFillWindow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", setText);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", SetText___dupe4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", TextInputTag);
