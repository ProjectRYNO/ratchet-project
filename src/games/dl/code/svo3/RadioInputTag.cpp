#include "SVOString.h"
#include "string.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_RadioInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "RadioInputTag.h"

extern "C" {

extern "C" {
SVTagModuleState *getInstance___dupe17(void);
extern char svoRadioInputTagFormNameAttribute[];
void AddRadioElement(FormTag *form, RadioInputTagState *tag);
extern char svoRadioInputTagSource[];

}
extern "C" {
extern char svoRadioInputTagName[];
}
#define SECTION(name) __attribute__((section(".svo_RadioInputTag_" #name)))

SECTION(FreeResources___dupe26) void FreeResources___dupe26(SVTag *tag)
{
    FreeContexts(tag);
}

SECTION(SetChecked) void SetChecked(RadioInputTagState *tag, int checked)
{
    if (tag->base.m_bSelectable) tag->m_isChecked = checked;
}

}

extern "C" SECTION(DefaultInit___dupe13) void DefaultInit___dupe13(RadioInputTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoRadioInputTagName, 64);
    memset(tag->m_text, 0, 100);
    memset(tag->m_value, 0, 100);
    tag->m_fontSize = 14;
    tag->m_textColor = 0xFFFFFFFF;
    tag->m_highlightColor = 0xFFFFFF00;
    tag->m_bRequiredForSubmit = 0;
    tag->m_isChecked = 0;
    tag->m_parentForm = 0;
    tag->m_bSubmitAsEncryped = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RadioInputTag", Draw___dupe19);

extern "C" SECTION(FindParentForm___dupe3) FormTag *FindParentForm___dupe3(RadioInputTagState *tag, iks *parent, SVTag **tagList)
{
    if (!parent) __SVO_Assert_Handler(svoRadioInputTagSource, 0xB0);
    if (!tagList) __SVO_Assert_Handler(svoRadioInputTagSource, 0xB1);
    SVTagModuleState *module = getInstance___dupe17();
    while (!module->vtable->IsMyTag(module, parent)) {
        parent = iks_parent(parent);
        if (!parent) __SVO_Assert_Handler(svoRadioInputTagSource, 0xBE);
    }
    char *formName = iks_find_attrib(parent, svoRadioInputTagFormNameAttribute);
    if (!formName) __SVO_Assert_Handler(svoRadioInputTagSource, 0xC4);
    for (int i = 0; i < 256; ++i) {
        SVTag *candidate = tagList[i];
        if (candidate) {
            char *name = candidate->vtable->GetTagName(candidate);
            if (!name) __SVO_Assert_Handler(svoRadioInputTagSource, 0xCB);
            if (!strcmp(name, formName)) return (FormTag *)tagList[i];
        }
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RadioInputTag", HandleInput___dupe45);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/RadioInputTag", RadioInputTag);

extern "C" SECTION(RegisterWithForm___dupe3) void RegisterWithForm___dupe3(RadioInputTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm___dupe3(tag, parent, tagList);
    if (!tag->m_parentForm) __SVO_Assert_Handler(svoRadioInputTagSource, 0xDD);
    AddRadioElement(tag->m_parentForm, tag);
}
