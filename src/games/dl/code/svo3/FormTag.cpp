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
extern char svoFormDefaultEncoding[34] __attribute__((aligned(8)));
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
}
#define SECTION(name) __attribute__((section(".svo_FormTag_" #name)))

SECTION(IsSelectable___dupe13) int IsSelectable___dupe13(void *self)
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
    for (int i = 0; i < 64; i++) {
        if (!strcmp(name, form->m_radioElementGroups[i].name)) {
            for (int j = 0; j < 64; j++) {
                if (!form->m_radioElementGroups[i].elements[j]) {
                    form->m_radioElementGroups[i].elements[j] = tag;
                    form->m_radioElementGroups[i].numElementsInGroup++;
                    return;
                }
            }
            __SVO_Assert_Handler(svoFormTagSource, 0xDE);
        } else if (!strcmp(form->m_radioElementGroups[i].name, svoFormUnsetGroup)) {
            strcpy(form->m_radioElementGroups[i].name, name);
            form->m_radioElementGroups[i].elements[0] = tag;
            form->m_radioElementGroups[i].numElementsInGroup++;
            form->m_numRadioElementGroups++;
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
    for (int i = 0; i < 64; i++) {
        if (!strcmp(form->m_radioElementGroups[i].name, svoFormUnsetGroup)) return;
        if (!strcmp(form->m_radioElementGroups[i].name, name)) {
            int count = form->m_radioElementGroups[i].numElementsInGroup;
            for (int j = 0; j < count; j++) {
                RadioInputTagState *element = form->m_radioElementGroups[i].elements[j];
                if (!element) __SVO_Assert_Handler(svoFormTagSource, 0x17A);
                if (element == tag) {
                    if (!element->m_isChecked) {
                        SetChecked(element, 1);
                        CAudioContextBaseState *audio = GetAudioContext();
                        ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 2, svoFormAudioClass);
                    } else {
                        CAudioContextBaseState *audio = GetAudioContext();
                        ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 6, svoFormAudioClass);
                    }
                } else if (element->m_isChecked) SetChecked(element, 0);
            }
            return;
        }
    }
}

extern "C" SECTION(DataCanBeEncryped) int DataCanBeEncryped(FormTag *form)
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

SECTION(FormTag) FormTag::FormTag(iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&base, xml, contexts);
    base.vtable = &svoFormTagVtable;
    DefaultInit___dupe15(this);
    char *action = iks_find_attrib(base.m_xml, svoFormActionAttribute);
    if (action) strcpy(m_url, action);
    else __SVO_Assert_Handler(svoFormTagSource, 0x63);
    char *encoding = iks_find_attrib(base.m_xml, svoFormEncodingAttribute);
    if (encoding) strcpy(m_encType, encoding);
    else memcpy(m_encType, svoFormDefaultEncoding, 34);
    char *method = iks_find_attrib(base.m_xml, svoFormMethodAttribute);
    if (method) {
        if (!strcmp(method, svoFormPost) || !strcmp(method, svoFormGet)) {
            if (!strcmp(method, svoFormPost)) m_method = 0;
            else m_method = 1;
            m_methodType = 0;
        } else if (!strcmp(method, svoFormLogin)) {
            m_methodType = 1;
        } else {
            __SVO_Assert_Handler(svoFormTagSource, 0x8A);
        }
    } else {
        __SVO_Assert_Handler(svoFormTagSource, 0x90);
    }
}

extern "C" SECTION(HandleInput___dupe47) int HandleInput___dupe47(FormTag *form, CPage *page)
{
    CInputContextBaseState *input = form->base.m_contexts->inputContext;
    if (!form->base.m_xml) __SVO_Assert_Handler(svoFormTagSource, 0xA4);
    if (!input) __SVO_Assert_Handler(svoFormTagSource, 0xA5);
    if (!page) __SVO_Assert_Handler(svoFormTagSource, 0xA6);
    return 1;
}

extern "C" SECTION(InitRadioGroups) void InitRadioGroups(FormTag *form)
{
    for (int i = 0; i < 64; i++) {
        memset(form->m_radioElementGroups[i].elements, 0, sizeof(form->m_radioElementGroups[i].elements));
        strcpy(form->m_radioElementGroups[i].name, svoFormUnsetGroup);
        form->m_radioElementGroups[i].numElementsInGroup = 0;
    }
}

#include "CheckboxInputTag.h"
#include "TextInputTag.h"
#include "HiddenInputTag.h"
#include "SelectTag.h"
#include "TextAreaTag.h"
#include "CQueryParams.h"
struct FormValueVtable { // slot 0x50 of the text-entry tag vtables
    /* 0x00 */ unsigned char prefix[0x50];
    /* 0x50 */ char *(*GetValue)(SVTag *tag);
};
extern "C" {
char *GetValue(SelectTagState *tag);
int doPost(CPage *page, char *path, CQueryParamListState *params, int method, int storeHistory);
int DataCanBeEncrypedTag(FormTag *form, SVTag *tag) __asm__("DataCanBeEncryped");
}
#define FORM_VALUE(tag) (((const FormValueVtable *)(tag)->base.vtable)->GetValue(&(tag)->base))
extern "C" SECTION(Submit) void Submit(FormTag *form, CPage *page)
{
    int i = 0;
    CQueryParamListState QueryParams;
    CQueryParamListState EncryptedQueryParams;
    CQueryParamList(&QueryParams);
    CQueryParamList(&EncryptedQueryParams);
    if (!form->m_bValidationSucceeded) {
        _CQueryParamList(&EncryptedQueryParams, 2);
        _CQueryParamList(&QueryParams, 2);
        return;
    }
    if (i < form->m_numRadioElementGroups) {
        do {
            if (!strcmp(form->m_radioElementGroups[i].name, svoFormUnsetGroup)) break;
            int numElements = form->m_radioElementGroups[i].numElementsInGroup;
            for (int j = 0; j < numElements; j++) {
                RadioInputTagState *element = form->m_radioElementGroups[i].elements[j];
                if (!element) __SVO_Assert_Handler(svoFormTagSource, 0x218);
                if (element->m_isChecked) {
                    char *name = element->base.vtable->GetTagName(&element->base);
                    if (element->m_bSubmitAsEncryped && DataCanBeEncrypedTag(form, &element->base))
                        Set(&EncryptedQueryParams, name, element->m_value, 0);
                    else
                        Set(&QueryParams, name, element->m_value, 0);
                    break;
                }
            }
            i++;
        } while (i < form->m_numRadioElementGroups);
    }
    for (i = 0; i < form->m_numCheckboxElements; i++) {
        CheckboxInputTagState *element = form->m_checkboxElements[i];
        if (!element) __SVO_Assert_Handler(svoFormTagSource, 0x23E);
        if (element->m_isChecked) {
            char *name = element->base.vtable->GetTagName(&element->base);
            if (element->m_bSubmitAsEncryped && DataCanBeEncrypedTag(form, &element->base))
                Set(&EncryptedQueryParams, name, element->m_value, 0);
            else
                Set(&QueryParams, name, element->m_value, 0);
        }
    }
    for (i = 0; i < form->m_numTextElements; i++) {
        TextInputTagState *element = form->m_textElements[i];
        if (!element) __SVO_Assert_Handler(svoFormTagSource, 0x255);
        char *name = element->base.vtable->GetTagName(&element->base);
        char *value = FORM_VALUE(element);
        if (element->m_bSubmitAsEncryped && DataCanBeEncrypedTag(form, &element->base))
            Set(&EncryptedQueryParams, name, value, 0);
        else
            Set(&QueryParams, name, value, 0);
    }
    for (i = 0; i < form->m_numPasswordElements; i++) {
        TextInputTagState *element = form->m_passwordElements[i];
        char *name = element->base.vtable->GetTagName(&element->base);
        char *value = FORM_VALUE(element);
        if (element->m_bSubmitAsEncryped && DataCanBeEncrypedTag(form, &element->base))
            Set(&EncryptedQueryParams, name, value, 0);
        else
            Set(&QueryParams, name, value, 0);
    }
    for (i = 0; i < form->m_numHiddenElements; i++) {
        HiddenInputTagState *element = form->m_hiddenElements[i];
        Set(&QueryParams, element->base.vtable->GetTagName(&element->base), element->m_value, 0);
    }
    for (i = 0; i < form->m_numSelectElements; i++) {
        SelectTagState *element = form->m_selectElements[i];
        char *name = element->base.vtable->GetTagName(&element->base);
        char *value = GetValue(element);
        if (element->m_bSubmitAsEncryped && DataCanBeEncrypedTag(form, &element->base))
            Set(&EncryptedQueryParams, name, value, 0);
        else
            Set(&QueryParams, name, value, 0);
    }
    for (i = 0; i < form->m_numTextAreaElements; i++) {
        TextAreaTagState *element = form->m_textAreaElements[i];
        char *name = element->base.vtable->GetTagName(&element->base);
        char *value = FORM_VALUE(element);
        if (element->m_bSubmitAsEncryped && DataCanBeEncrypedTag(form, &element->base))
            Set(&EncryptedQueryParams, name, value, 0);
        else
            Set(&QueryParams, name, value, 0);
    }
    for (i = 0; i < GetParamCount(&QueryParams); i++) {
    }
    int bStoreInHistory = form->m_method != 0;
    if (!form->m_bEncryptionErrorOccurred)
        doPost(page, form->m_url, &QueryParams, form->m_methodType, bStoreInHistory);
    _CQueryParamList(&EncryptedQueryParams, 2);
    _CQueryParamList(&QueryParams, 2);
}
