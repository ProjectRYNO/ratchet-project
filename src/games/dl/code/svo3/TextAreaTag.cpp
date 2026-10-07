#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_TextAreaTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "TextAreaTag.h"

extern "C" {
void Scroll(TextAreaTagState *tag, signed char amount, int speed);

#define SECTION(name) __attribute__((section(".svo_TextAreaTag_" #name)))

SECTION(scroll___dupe2) void scroll___dupe2(TextAreaTagState *tag, signed char amount)
{
    Scroll(tag, amount, 0);
}

SECTION(GetMaxLengthUTF8Chars) long GetMaxLengthUTF8Chars(TextAreaTagState *tag)
{
    return tag->m_maxTextSize;
}

SECTION(GetMaxLengthBytes) long GetMaxLengthBytes(TextAreaTagState *tag)
{
    return tag->m_maxTextSize;
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", _TextAreaTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", changeColorForAllLines);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", CheckForLongWord);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", DefaultInit___dupe12);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", Draw___dupe16);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", DrawCursor);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", FindParentForm___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", FreeResources___dupe21);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", GetLineNumberAtOffset);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", GetNextWord);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", GetSubstringPixelWidth);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", HandleInput___dupe43);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", handleKeyboardInput);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", handleSpecialKeys);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", ParseText);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", PrintText);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", ProcessDownArrow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", ProcessLeftArrow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", ProcessNewLine);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", ProcessRightArrow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", ProcessUpArrow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", PutBackWord);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", RegisterWithForm___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", ResetParser);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", resetTextArea);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", ResetVariables);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", Scroll);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", SetArrowOffsets);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", SetScrollBarPercentage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", SetText___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", TextAreaTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", TrimLongWord);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", UpdateAfterTextEntry);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", UpdateCursorPosition);
