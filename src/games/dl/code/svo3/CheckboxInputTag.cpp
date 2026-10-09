#include "TagUtils.h"
#include "SVOString.h"
#include "CheckboxInputTag.h"
#include "CInputContextBase.h"
#include "CDrawContextBase.h"
#include "CPage.h"
#include "string.h"
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

SVTagModuleState *getInstance___dupe17(void);
extern char svoCheckboxInputTagFormNameAttribute[];
void AddCheckboxElement(FormTag *form, CheckboxInputTagState *tag);
extern char svoCheckboxInputTagSource[];


extern "C" {
extern const SVTagVtablePrefix svoCheckboxInputTagVtable;
void FreeResources___dupe28(void *tag);
}
extern "C" {
extern char svoCheckboxInputTagName[];
}
extern "C" {
CAudioContextBaseState *GetAudioContext();
extern char svoCheckboxSoundClass[];
}
extern "C" {
extern char svoCheckboxInputTagSource[];
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
int TrimToFitDisplaySize(CDrawContextBase *, char *, float, int);
CAudioContextBaseState *GetAudioContext();
extern char svoButtonAudioClass[];
extern char svoSubmitAudioClass[];
void CheckCheckboxElement(FormTag *, CheckboxInputTagState *);
}
extern "C" {
extern char svoCheckboxInputTagAttrFontSize[];
extern char svoCheckboxInputTagAttrTextColor[];
extern char svoCheckboxInputTagAttrHighlightColor[];
extern char svoCheckboxInputTagAttrValue[];
extern char svoCheckboxInputTagAttrChecked[];
extern char svoCheckboxInputTagAttrSelectable[];
extern char svoCheckboxInputTagAttrClass[];
extern char svoCheckboxInputTagAttrSubmitAsEncrypted[];
extern const SVTagVtablePrefix svoCheckboxInputTagVtable;
void DefaultInit___dupe14(CheckboxInputTagState *);
void decodeEntityText(char *);
void RegisterWithForm___dupe4(CheckboxInputTagState *, iks *, SVTag **);
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

extern "C" SECTION(CheckboxInputTag) void CheckboxInputTag(CheckboxInputTagState *self, iks *xml, SVTag **tagList, CAllContextData *contexts)
{
    SVTag *tag = &self->base;
    SVTagConstruct(tag, xml, contexts);
    tag->vtable = &svoCheckboxInputTagVtable;
    DefaultInit___dupe14(self);
    getIntAttrib(tag->m_xml, svoCheckboxInputTagAttrFontSize, &self->m_fontSize);
    getColorAttrib(tag->m_xml, svoCheckboxInputTagAttrTextColor, &self->m_textColor);
    getColorAttrib(tag->m_xml, svoCheckboxInputTagAttrHighlightColor, &self->m_highlightColor);
    char *value = iks_find_attrib(tag->m_xml, svoCheckboxInputTagAttrValue);
    if (value) strcpy(self->m_value, value);
    else __SVO_Assert_Handler(svoCheckboxInputTagSource, 0x48);
    if (iks_find_attrib(tag->m_xml, svoCheckboxInputTagAttrChecked)) self->m_isChecked = 1;
    if (!getBoolAttrib(tag->m_xml, svoCheckboxInputTagAttrSelectable, &tag->m_bSelectable)) tag->m_bSelectable = 1;
    getStringAttrib(tag->m_xml, svoCheckboxInputTagAttrClass, &tag->m_tagClass);
    if (iks_has_children(tag->m_xml)) strcpy(self->m_text, iks_cdata(iks_child(tag->m_xml)));
    if (!getBoolAttrib(tag->m_xml, svoCheckboxInputTagAttrSubmitAsEncrypted, &self->m_bSubmitAsEncryped)) self->m_bSubmitAsEncryped = 0;
    if (!self->m_text) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0x69);
    decodeEntityText(self->m_text);
    RegisterWithForm___dupe4(self, iks_parent(tag->m_xml), tagList);
}

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

extern "C" SECTION(Draw___dupe20) void Draw___dupe20(CheckboxInputTagState *self)
{
    SVTag *tag = &self->base;
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0x9C);
    if (!tag->m_xml) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0x9D);
    unsigned int color = tag->m_bSelected ? self->m_highlightColor : self->m_textColor;
    int length = strlen(self->m_text);
    draw->vtable->DrawCheckbox(draw, tag->m_tagid, tag->m_x, tag->m_y, tag->m_z, tag->m_width, tag->m_height,
        color, tag->m_lineColor, tag->m_fillColor, tag->m_bSelected, self->m_isChecked,
        self->m_text, length, self->m_fontSize, 0, tag->m_tagClass);
}

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

extern "C" SECTION(HandleInput___dupe46) int HandleInput___dupe46(CheckboxInputTagState *self, CPage *page)
{
    SVTag *tag = &self->base;
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!tag->m_xml) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0x7B);
    if (!input) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0x7C);
    if (!page) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0x7D);
    if (!tag->vtable->IsSelected(tag)) return 1;
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE)) {
        if (!self->m_parentForm) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0x83);
        CheckCheckboxElement(self->m_parentForm, self);
    }
    for (int action = 0; action < 4; ++action) {
        if (HasActionOccurred(input, 0x11, (PadAction)action)) {
            CDrawContextBase *draw = tag->m_contexts->drawContext;
            if (!draw) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0x8D);
            return Navigate(tag, input, draw, tag->m_xml, page) == 0;
        }
    }
    return 1;
}

extern "C" SECTION(RegisterWithForm___dupe4) void RegisterWithForm___dupe4(CheckboxInputTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm___dupe4(tag, parent, tagList);
    if (!tag->m_parentForm) __SVO_Assert_Handler(svoCheckboxInputTagSource, 0xDD);
    AddCheckboxElement(tag->m_parentForm, tag);
}

extern "C" SECTION(ToggleChecked) void ToggleChecked(CheckboxInputTagState *tag)
{
    if (tag->base.m_bSelectable) {
        int sound = tag->m_isChecked ? 3 : 2;
        CAudioContextBaseState *audio = GetAudioContext();
        ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, sound, svoCheckboxSoundClass);
        tag->m_isChecked = !tag->m_isChecked;
    }
}
