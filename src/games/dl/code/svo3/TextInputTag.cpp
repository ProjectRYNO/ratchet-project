#include "string.h"
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

extern "C" {
SVTagModuleState *getInstance___dupe17(void);
extern char svoTextInputTagFormNameAttribute[];
void AddTextElement(FormTag *form, TextInputTagState *tag);
extern char svoTextInputTagSource[];

}
extern "C" {
float getSubstringPixelWidthImpl(TextInputTagState *tag, char *text, int left, int right);
void setText(TextInputTagState *tag, char *text, unsigned int length);
}
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

extern "C" SECTION(findParentForm) FormTag *findParentForm(TextInputTagState *tag, iks *parent, SVTag **tagList)
{
    if (!parent) __SVO_Assert_Handler(svoTextInputTagSource, 0x311);
    if (!tagList) __SVO_Assert_Handler(svoTextInputTagSource, 0x312);
    SVTagModuleState *module = getInstance___dupe17();
    if (!module->vtable->IsMyTag(module, parent)) return 0;
    char *formName = iks_find_attrib(parent, svoTextInputTagFormNameAttribute);
    if (!formName) __SVO_Assert_Handler(svoTextInputTagSource, 0x31F);
    for (int i = 0; i < 256; ++i) {
        SVTag *candidate = tagList[i];
        if (candidate) {
            char *name = candidate->vtable->GetTagName(candidate);
            if (!name) __SVO_Assert_Handler(svoTextInputTagSource, 0x326);
            if (!strcmp(name, formName)) return (FormTag *)tagList[i];
        }
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", GetEditPosition___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", getSubstringPixelWidth);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", getSubstringPixelWidthImpl);

extern "C" SECTION(GetText___dupe2) char *GetText___dupe2(TextInputTagState *tag)
{
    if ((int)strlen(tag->m_text) >= 512) __SVO_Assert_Handler(svoTextInputTagSource, 0x247);
    return tag->m_text;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", HandleInput___dupe44);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", handleKeyboardInput___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", handleSpecialKeys___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", InitialiseFromXml);

extern "C" SECTION(registerWithForm) void registerWithForm(TextInputTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = findParentForm(tag, parent, tagList);
    if (tag->m_parentForm) AddTextElement(tag->m_parentForm, tag);
}

extern "C" SECTION(resetTextInput) void resetTextInput(TextInputTagState *tag)
{
    memset(tag->m_text, 0, 512);
    memset(tag->m_keyboardInput, 0, 512);
    tag->m_curEditOffset = 0;
    tag->m_curRightOffset = 0;
    tag->m_curLeftOffset = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", scrollTextLeftToFillWindow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", scrollTextRightToFillWindow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", setText);

extern "C" SECTION(SetText___dupe4) void SetText___dupe4(TextInputTagState *tag, char *text)
{
    if ((int)strlen(text) >= 512) __SVO_Assert_Handler(svoTextInputTagSource, 0x240);
    setText(tag, text, strlen(text));
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", TextInputTag);
