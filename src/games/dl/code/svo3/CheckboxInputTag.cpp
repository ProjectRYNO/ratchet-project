#include "SVOString.h"
#include "string.h"
#include "CheckboxInputTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_CheckboxInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern "C" {
SVTagModuleState *getInstance___dupe17(void);
extern char svoCheckboxInputTagFormNameAttribute[];
void AddCheckboxElement(FormTag *form, CheckboxInputTagState *tag);
extern char svoCheckboxInputTagSource[];

}
extern "C" {
extern const SVTagVtablePrefix svoCheckboxInputTagVtable;
void FreeResources___dupe28(void *tag);
}
extern "C" {
extern char svoCheckboxInputTagName[];
}
#define SECTION(name) __attribute__((section(".svo_CheckboxInputTag_" #name)))

SECTION(FreeResources___dupe28) void FreeResources___dupe28(void *self)
{
    // Retail implements this callback as a no-op.
}

}

extern "C" SECTION(_CheckboxInputTag) void _CheckboxInputTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoCheckboxInputTagVtable;
    FreeResources___dupe28((void *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", CheckboxInputTag);

extern "C" SECTION(DefaultInit___dupe14) void DefaultInit___dupe14(CheckboxInputTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoCheckboxInputTagName, 64);
    memset(tag->m_text, 0, 100);
    memset(tag->m_value, 0, 100);
    tag->m_fontSize = 14;
    tag->m_textColor = 0xFFFFFFFF;
    tag->m_highlightColor = 0xFFFFFF00;
    tag->m_bSubmitAsEncryped = 0;
    tag->m_isChecked = 0;
    tag->m_parentForm = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", Draw___dupe20);

extern "C" SECTION(FindParentForm___dupe4) FormTag *FindParentForm___dupe4(CheckboxInputTagState *tag, iks *parent, SVTag **tagList)
{
    if (!parent) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0xB0);
    if (!tagList) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0xB1);
    SVTagModuleState *module = getInstance___dupe17();
    while (!module->vtable->IsMyTag(module, parent)) {
        parent = iks_parent(parent);
        if (!parent) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0xBE);
    }
    char *formName = iks_find_attrib(parent, svoCheckboxInputTagFormNameAttribute);
    if (!formName) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0xC4);
    for (int i = 0; i < 256; ++i) {
        SVTag *candidate = tagList[i];
        if (candidate) {
            char *name = candidate->vtable->GetTagName(candidate);
            if (!name) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0xCB);
            if (!strcmp(name, formName)) return (FormTag *)tagList[i];
        }
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", HandleInput___dupe46);

extern "C" SECTION(RegisterWithForm___dupe4) void RegisterWithForm___dupe4(CheckboxInputTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm___dupe4(tag, parent, tagList);
    if (!tag->m_parentForm) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0xDD);
    AddCheckboxElement(tag->m_parentForm, tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CheckboxInputTag", ToggleChecked);
