#include "TagUtils.h"
#include "SVOString.h"
#include "string.h"
#include "HiddenInputTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_HiddenInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

SVTagModuleState *getInstance___dupe17(void);
extern char svoHiddenInputTagFormNameAttribute[];
void AddHiddenElement(FormTag *form, HiddenInputTagState *tag);
extern char svoHiddenInputTagSource[];


extern "C" {
extern char svoHiddenInputTagName[];
}
extern "C" {
extern const SVTagVtablePrefix svoHiddenInputTagVtable;
extern char svoHiddenValueAttribute[];
extern char svoHiddenEncryptedAttribute[];
void *DefaultInit___dupe19(HiddenInputTagState *);
void SetValue(HiddenInputTagState *, char *);
void RegisterWithForm___dupe6(HiddenInputTagState *, iks *, SVTag **);
}
#define SECTION(name) __attribute__((section(".svo_HiddenInputTag_" #name)))

SECTION(HandleInput___dupe51) long HandleInput___dupe51(void *self, void *context)
{
    return 1;
}

SECTION(IsSelectable___dupe16) long IsSelectable___dupe16(void *self)
{
    return 0;
}

SECTION(FreeResources___dupe40) void FreeResources___dupe40(SVTag *tag)
{
    FreeContexts(tag);
}

}

extern "C" SECTION(DefaultInit___dupe19) void *DefaultInit___dupe19(HiddenInputTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoHiddenInputTagName, 64);
    void *result = memset(tag->m_value, 0, 256);
    tag->m_bSubmitAsEncryped = 0;
    return result;
}

extern "C" SECTION(FindParentForm___dupe6) FormTag *FindParentForm___dupe6(HiddenInputTagState *tag, iks *parent, SVTag **tagList)
{
    if (!parent) __SVO_Assert_Handler(svoHiddenInputTagSource, 0x60);
    if (!tagList) __SVO_Assert_Handler(svoHiddenInputTagSource, 0x61);
    SVTagModuleState *module = getInstance___dupe17();
    while (!module->vtable->IsMyTag(module, parent)) {
        parent = iks_parent(parent);
        if (!parent) __SVO_Assert_Handler(svoHiddenInputTagSource, 0x6E);
    }
    char *formName = iks_find_attrib(parent, svoHiddenInputTagFormNameAttribute);
    if (!formName) __SVO_Assert_Handler(svoHiddenInputTagSource, 0x74);
    for (int i = 0; i < 256; ++i) {
        SVTag *candidate = tagList[i];
        if (candidate) {
            char *name = candidate->vtable->GetTagName(candidate);
            if (!name) __SVO_Assert_Handler(svoHiddenInputTagSource, 0x7B);
            if (!strcmp(name, formName)) return (FormTag *)tagList[i];
        }
    }
    return 0;
}

extern "C" SECTION(HiddenInputTag) void HiddenInputTag(HiddenInputTagState *tag, iks *xml, SVTag **tags, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoHiddenInputTagVtable;
    DefaultInit___dupe19(tag);
    char *value = iks_find_attrib(tag->base.m_xml, svoHiddenValueAttribute);
    if (value) SetValue(tag, value);
    else __SVO_Assert_Handler(svoHiddenInputTagSource, 0x2F);
    if (!getBoolAttrib(tag->base.m_xml, svoHiddenEncryptedAttribute, &tag->m_bSubmitAsEncryped)) tag->m_bSubmitAsEncryped = 0;
    RegisterWithForm___dupe6(tag, iks_parent(tag->base.m_xml), tags);
}

extern "C" SECTION(RegisterWithForm___dupe6) void RegisterWithForm___dupe6(HiddenInputTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm___dupe6(tag, parent, tagList);
    if (!tag->m_parentForm) __SVO_Assert_Handler(svoHiddenInputTagSource, 0x8D);
    AddHiddenElement(tag->m_parentForm, tag);
}

extern "C" SECTION(SetValue) void SetValue(HiddenInputTagState *tag, char *value)
{
    if (strlen(value) < 256) {
        svstrncpy(tag->m_value, value, 256);
        return;
    }
    __SVO_Assert_Handler(svoHiddenInputTagSource, 0x5A);
}
