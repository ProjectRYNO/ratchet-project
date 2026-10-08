#include "CMemoryContextBase.h"
#include "SVTag.h"
#include "string.h"
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

extern "C" {
SVTagModuleState *getInstance___dupe17(void);
extern char svoTextAreaTagFormNameAttribute[];
void AddTextAreaElement(FormTag *form, TextAreaTagState *tag);
extern char svoTextAreaTagSource[];

}
extern "C" {
extern const SVTagVtablePrefix svoTextAreaTagVtable;
void FreeResources___dupe21(TextAreaTagState *tag);
}
extern "C" {
float GetSubstringPixelWidth(TextAreaTagState *tag, CDrawContextBase *draw, char *text, int startOffset, int endOffset);
}
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

extern "C" SECTION(_TextAreaTag) void _TextAreaTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoTextAreaTagVtable;
    FreeResources___dupe21((TextAreaTagState *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", changeColorForAllLines);

extern "C" SECTION(CheckForLongWord) int CheckForLongWord(TextAreaTagState *tag, char *text, int startOffset, int endOffset, float maxLength)
{
    return maxLength < GetSubstringPixelWidth(tag, tag->base.m_contexts->drawContext, text, startOffset, endOffset);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", DefaultInit___dupe12);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", Draw___dupe16);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", DrawCursor);

extern "C" SECTION(FindParentForm___dupe2) FormTag *FindParentForm___dupe2(TextAreaTagState *tag, iks *parent, SVTag **tagList)
{
    if (!parent) __SVO_Assert_Handler(svoTextAreaTagSource, 0x3A8);
    if (!tagList) __SVO_Assert_Handler(svoTextAreaTagSource, 0x3A9);
    SVTagModuleState *module = getInstance___dupe17();
    while (!module->vtable->IsMyTag(module, parent)) {
        parent = iks_parent(parent);
        if (!parent) return 0;
    }
    char *formName = iks_find_attrib(parent, svoTextAreaTagFormNameAttribute);
    if (!formName) __SVO_Assert_Handler(svoTextAreaTagSource, 0x3BB);
    for (int i = 0; i < 256; ++i) {
        SVTag *candidate = tagList[i];
        if (candidate) {
            char *name = candidate->vtable->GetTagName(candidate);
            if (!name) __SVO_Assert_Handler(svoTextAreaTagSource, 0x3C2);
            if (!strcmp(name, formName)) return (FormTag *)tagList[i];
        }
    }
    return 0;
}

extern "C" SECTION(FreeResources___dupe21) void FreeResources___dupe21(TextAreaTagState *tag)
{
    if (tag->m_text) {
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_text);
        tag->m_text = 0;
    }
    if (tag->m_textLines) {
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_textLines);
        tag->m_textLines = 0;
    }
}

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

extern "C" SECTION(PutBackWord) void PutBackWord(TextAreaTagState *tag, int startIndex, int *parseOffset)
{
    if (startIndex < 0) startIndex = 0;
    int *offset = parseOffset ? parseOffset : &tag->m_curParseOffset;
    *offset = startIndex;
    tag->m_textLines[tag->m_curParseLine].lineEndIndex = (short)*offset;
}

extern "C" SECTION(RegisterWithForm___dupe2) void RegisterWithForm___dupe2(TextAreaTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm___dupe2(tag, parent, tagList);
    if (tag->m_parentForm) AddTextAreaElement(tag->m_parentForm, tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", ResetParser);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", resetTextArea);

extern "C" SECTION(ResetVariables) void ResetVariables(TextAreaTagState *tag)
{
    tag->m_firstAppendToChat = 1;
    tag->m_canScrollDown = 0;
    tag->m_scrollFrame = 0;
    tag->m_cursorX = tag->base.m_x + 7.0f;
    tag->m_curEditOffset = 0;
    tag->m_cursorY = tag->base.m_y - 2.0f;
    tag->m_textEndOffset = 0;
    tag->m_curParseOffset = 0;
    tag->m_curParseLine = 0;
    tag->m_curLine = 0;
    tag->m_textEndLine = 0;
    tag->m_minDisplayLine = 0;
    tag->m_numLinesInDisplay = 1;
    tag->m_overallLength = 0.0f;
    tag->m_upArrowOffset = 0;
    tag->m_downArrowOffset = 0;
    tag->m_leftArrowOffset = 0;
    tag->m_rightArrowOffset = 0;
    tag->m_numTotalLines = 0;
    tag->m_canScrollUp = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", Scroll);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", SetArrowOffsets);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", SetScrollBarPercentage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", SetText___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", TextAreaTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", TrimLongWord);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", UpdateAfterTextEntry);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", UpdateCursorPosition);
