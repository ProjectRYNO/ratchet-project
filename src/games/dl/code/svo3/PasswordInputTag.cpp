#include "string.h"
#include "SVOString.h"
#include "TextInputTag.h"
extern "C" {
FormTag *findParentForm(TextInputTagState *tag, iks *parent, SVTag **tagList);
void AddPasswordElement(FormTag *form, TextInputTagState *tag);
}
extern "C" {
void defaultInit(TextInputTagState *tag);
void DrawImpl(TextInputTagState *tag, char *text);
float getSubstringPixelWidthImpl(TextInputTagState *tag, char *text, int left, int right);
void TextInputTag(TextInputTagState *tag, iks *xml, SVTag **tagList, CAllContextData *contexts, int deferInit);
void InitialiseFromXml(TextInputTagState *tag, iks *xml, SVTag **tagList, CAllContextData *contexts);
extern char svoPasswordInputTagName[];
extern char svoPasswordInputTagSource[];
extern const SVTagVtablePrefix svoPasswordInputTagVtable;
}
#define SECTION(name) __attribute__((section(".svo_PasswordInputTag_" #name)))
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_PasswordInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/PasswordInputTag", defaultInit___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/PasswordInputTag", PasswordInputTag);

extern "C" SECTION(Draw___dupe18) void Draw___dupe18(TextInputTagState *tag)
{
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoPasswordInputTagSource, 0x2A);
    char masked[512];
    memset(masked, 0, 512);
    memset(masked, '*', strlen(tag->m_text));
    DrawImpl(tag, masked);
}

extern "C" SECTION(getSubstringPixelWidth___dupe2) float getSubstringPixelWidth___dupe2(TextInputTagState *tag, int left, int right)
{
    char masked[512];
    memset(masked, 0, 512);
    memset(masked, '*', strlen(tag->m_text));
    return getSubstringPixelWidthImpl(tag, masked, left, right);
}

extern "C" SECTION(registerWithForm___dupe2) void registerWithForm___dupe2(TextInputTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = findParentForm(tag, parent, tagList);
    if (tag->m_parentForm) AddPasswordElement(tag->m_parentForm, tag);
}
