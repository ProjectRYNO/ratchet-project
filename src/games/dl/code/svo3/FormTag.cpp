#include "CAudioContextBase.h"
#include "SVOString.h"
#include "string.h"
#include "RadioInputTag.h"
#include "FormTag.h"
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

extern char svoFormTagSource[];
extern char svoFormUnsetGroup[];
void ToggleChecked(CheckboxInputTagState *tag);

extern "C" {
extern char svoFormTagName[];
extern char svoFormActionAttribute[];
extern char svoFormEncodingAttribute[];
extern char svoFormDefaultEncoding[];
extern char svoFormMethodAttribute[];
extern char svoFormPost[];
extern char svoFormGet[];
extern char svoFormLogin[];
extern char svoFormAudioClass[];
void InitRadioGroups(FormTag *form);
void SetChecked(RadioInputTagState *tag, int checked);
CAudioContextBaseState *GetAudioContext();
}
extern "C" {
extern const SVTagVtablePrefix svoFormTagVtable;
void DefaultInit___dupe15(FormTag *form);
void FormTagConstruct(FormTag *form, iks *xml, CAllContextData *contexts) __asm__("FormTag");
}
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

extern "C" SECTION(AddCheckboxElement) void AddCheckboxElement(FormTag *form, CheckboxInputTagState *tag)
{
    if (!tag) __SVO_Assert_Handler(svoFormTagSource, 0xf4);
    int count = form->m_numCheckboxElements;
    if (count >= 64) {
        __SVO_Assert_Handler(svoFormTagSource, 0xf9);
        return;
    }
    form->m_checkboxElements[count] = tag;
    form->m_numCheckboxElements = count + 1;
}

extern "C" SECTION(AddHiddenElement) void AddHiddenElement(FormTag *form, HiddenInputTagState *tag)
{
    if (!tag) __SVO_Assert_Handler(svoFormTagSource, 0x137);
    int count = form->m_numHiddenElements;
    if (count >= 64) {
        __SVO_Assert_Handler(svoFormTagSource, 0x13c);
        return;
    }
    form->m_hiddenElements[count] = tag;
    form->m_numHiddenElements = count + 1;
}

extern "C" SECTION(AddPasswordElement) void AddPasswordElement(FormTag *form, TextInputTagState *tag)
{
    if (!tag) __SVO_Assert_Handler(svoFormTagSource, 0x114);
    int count = form->m_numPasswordElements;
    if (count >= 64) {
        __SVO_Assert_Handler(svoFormTagSource, 0x119);
        return;
    }
    form->m_passwordElements[count] = tag;
    form->m_numPasswordElements = count + 1;
}

extern "C" SECTION(AddRadioElement) void AddRadioElement(FormTag *form, RadioInputTagState *tag)
{
    if (!tag) __SVO_Assert_Handler(svoFormTagSource, 0xC7);
    char *name = tag->base.vtable->GetTagName(&tag->base);
    if (!name) __SVO_Assert_Handler(svoFormTagSource, 0xCA);
    for (int i = 0; i < 64; ++i) {
        RadioElementGroup *group = &form->m_radioElementGroups[i];
        if (!strcmp(name, group->name)) {
            for (int j = 0; j < 64; ++j) {
                if (!group->elements[j]) {
                    group->elements[j] = tag;
                    ++group->numElementsInGroup;
                    return;
                }
            }
            __SVO_Assert_Handler(svoFormTagSource, 0xDE);
        } else if (!strcmp(group->name, svoFormUnsetGroup)) {
            strcpy(group->name, name);
            group->elements[0] = tag;
            ++group->numElementsInGroup;
            ++form->m_numRadioElementGroups;
            return;
        }
    }
    __SVO_Assert_Handler(svoFormTagSource, 0xEE);
}

extern "C" SECTION(AddSelectElement) void AddSelectElement(FormTag *form, SelectTagState *tag)
{
    if (!tag) __SVO_Assert_Handler(svoFormTagSource, 0x148);
    int count = form->m_numSelectElements;
    if (count >= 64) {
        __SVO_Assert_Handler(svoFormTagSource, 0x14d);
        return;
    }
    form->m_selectElements[count] = tag;
    form->m_numSelectElements = count + 1;
}

extern "C" SECTION(AddSubmitElement) void AddSubmitElement(FormTag *form, SubmitInputTagState *tag)
{
    if (!tag) __SVO_Assert_Handler(svoFormTagSource, 0x125);
    if (form->m_submitElement) {
        __SVO_Assert_Handler(svoFormTagSource, 0x12C);
        return;
    }
    form->m_submitElement = tag;
}

extern "C" SECTION(AddTextAreaElement) void AddTextAreaElement(FormTag *form, TextAreaTagState *tag)
{
    if (!tag) __SVO_Assert_Handler(svoFormTagSource, 0x159);
    int count = form->m_numTextAreaElements;
    if (count >= 64) {
        __SVO_Assert_Handler(svoFormTagSource, 0x15e);
        return;
    }
    form->m_textAreaElements[count] = tag;
    form->m_numTextAreaElements = count + 1;
}

extern "C" SECTION(AddTextElement) void AddTextElement(FormTag *form, TextInputTagState *tag)
{
    if (!tag) __SVO_Assert_Handler(svoFormTagSource, 0x104);
    int count = form->m_numTextElements;
    if (count >= 64) {
        __SVO_Assert_Handler(svoFormTagSource, 0x109);
        return;
    }
    form->m_textElements[count] = tag;
    form->m_numTextElements = count + 1;
}

extern "C" SECTION(CheckCheckboxElement) void CheckCheckboxElement(FormTag *form, CheckboxInputTagState *tag)
{
    for (int i = 0; i < 64; ++i) {
        CheckboxInputTagState *element = form->m_checkboxElements[i];
        if (!element) __SVO_Assert_Handler(svoFormTagSource, 0x1A4);
        if (element == tag) {
            ToggleChecked(element);
            return;
        }
    }
}

extern "C" SECTION(CheckRadioElement) void CheckRadioElement(FormTag *form, RadioInputTagState *tag)
{
    char *name = tag->base.vtable->GetTagName(&tag->base);
    for (int i = 0; i < 64; ++i) {
        RadioElementGroup *group = &form->m_radioElementGroups[i];
        if (!strcmp(group->name, svoFormUnsetGroup)) return;
        if (strcmp(group->name, name)) continue;
        int count = group->numElementsInGroup;
        for (int j = 0; j < count; ++j) {
            RadioInputTagState *element = group->elements[j];
            if (!element) __SVO_Assert_Handler(svoFormTagSource, 0x17A);
            if (element == tag) {
                int sound = 6;
                if (!element->m_isChecked) {
                    SetChecked(element, 1);
                    sound = 2;
                }
                CAudioContextBaseState *audio = GetAudioContext();
                ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, sound, svoFormAudioClass);
            } else if (element->m_isChecked) SetChecked(element, 0);
        }
        return;
    }
}

extern "C" SECTION(DataCanBeEncryped) long DataCanBeEncryped(FormTag *form)
{
    form->m_bEncryptionErrorOccurred = 1;
    __SVO_Assert_Handler(svoFormTagSource, 0x1BD);
    return 0;
}

extern "C" SECTION(DefaultInit___dupe15) void DefaultInit___dupe15(FormTag *form)
{
    svstrncpy(form->base.m_tagTypeName, svoFormTagName, 64);
    memset(form->m_url, 0, sizeof(form->m_url));
    memset(form->m_encType, 0, sizeof(form->m_encType));
    memset(form->m_radioElementGroups, 0, sizeof(form->m_radioElementGroups));
    memset(form->m_checkboxElements, 0, sizeof(form->m_checkboxElements));
    memset(form->m_textElements, 0, sizeof(form->m_textElements));
    memset(form->m_passwordElements, 0, sizeof(form->m_passwordElements));
    memset(form->m_hiddenElements, 0, sizeof(form->m_hiddenElements));
    memset(form->m_selectElements, 0, sizeof(form->m_selectElements));
    memset(form->m_textAreaElements, 0, sizeof(form->m_textAreaElements));
    form->m_submitElement = 0;
    form->m_numRadioElementGroups = 0;
    form->m_bValidationSucceeded = 1;
    form->m_numCheckboxElements = 0;
    form->m_numTextElements = 0;
    form->m_numPasswordElements = 0;
    form->m_numHiddenElements = 0;
    form->m_numSelectElements = 0;
    form->m_numTextAreaElements = 0;
    form->base.m_bSelectable = 0;
    form->base.m_bSelected = 0;
    form->m_methodType = 0;
    form->m_method = 0;
    form->m_bEncryptionErrorOccurred = 0;
    form->m_tagThatFailedValidation = 0;
    form->m_pChildrenInfoList = 0;
    InitRadioGroups(form);
}

extern "C" SECTION(Draw___dupe21) void Draw___dupe21(FormTag *form)
{
    if (!form->base.m_contexts->drawContext) __SVO_Assert_Handler(svoFormTagSource, 0xB0);
    if (!form->base.m_xml) __SVO_Assert_Handler(svoFormTagSource, 0xB1);
}

extern "C" SECTION(FormTag) void FormTagConstruct(FormTag *form, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&form->base, xml, contexts);
    form->base.vtable = &svoFormTagVtable;
    DefaultInit___dupe15(form);
    char *value = iks_find_attrib(form->base.m_xml, svoFormActionAttribute);
    if (value) strcpy(form->m_url, value);
    else __SVO_Assert_Handler(svoFormTagSource, 0x63);
    value = iks_find_attrib(form->base.m_xml, svoFormEncodingAttribute);
    if (value) strcpy(form->m_encType, value);
    else memcpy(form->m_encType, svoFormDefaultEncoding, 34);
    value = iks_find_attrib(form->base.m_xml, svoFormMethodAttribute);
    if (!value) {
        __SVO_Assert_Handler(svoFormTagSource, 0x90);
    } else if (!strcmp(value, svoFormPost) || !strcmp(value, svoFormGet)) {
        form->m_method = strcmp(value, svoFormPost) != 0;
        form->m_methodType = 0;
    } else if (!strcmp(value, svoFormLogin)) {
        form->m_methodType = 1;
    } else {
        __SVO_Assert_Handler(svoFormTagSource, 0x8A);
    }
}

extern "C" SECTION(HandleInput___dupe47) long HandleInput___dupe47(FormTag *form, CPage *page)
{
    CInputContextBaseState *input = form->base.m_contexts->inputContext;
    if (!form->base.m_xml) __SVO_Assert_Handler(svoFormTagSource, 0xA4);
    if (!input) __SVO_Assert_Handler(svoFormTagSource, 0xA5);
    if (!page) __SVO_Assert_Handler(svoFormTagSource, 0xA6);
    return 1;
}

extern "C" SECTION(InitRadioGroups) void InitRadioGroups(FormTag *form)
{
    for (RadioElementGroup *group = form->m_radioElementGroups; group != form->m_radioElementGroups + 64; ++group) {
        memset(group->elements, 0, sizeof(group->elements));
        strcpy(group->name, svoFormUnsetGroup);
        group->numElementsInGroup = 0;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/FormTag", Submit);
