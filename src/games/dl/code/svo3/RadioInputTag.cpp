#include "TagUtils.h"
#include "SVOString.h"
#include "RadioInputTag.h"
#include "CInputContextBase.h"
#include "CDrawContextBase.h"
#include "CPage.h"
#include "string.h"
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

SVTagModuleState *getInstance___dupe17(void);
extern char svoRadioInputTagFormNameAttribute[];
void AddRadioElement(FormTag *form, RadioInputTagState *tag);
extern char svoRadioInputTagSource[];


extern "C" {
extern char svoRadioInputTagName[];
}
extern "C" {
extern char svoRadioInputTagSource[];
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
int TrimToFitDisplaySize(CDrawContextBase *, char *, float, int);
CAudioContextBaseState *GetAudioContext();
extern char svoButtonAudioClass[];
extern char svoSubmitAudioClass[];
void CheckRadioElement(FormTag *, RadioInputTagState *);
}
extern "C" {
extern char svoRadioInputTagAttrFontSize[];
extern char svoRadioInputTagAttrTextColor[];
extern char svoRadioInputTagAttrHighlightColor[];
extern char svoRadioInputTagAttrClass[];
extern char svoRadioInputTagAttrValue[];
extern char svoRadioInputTagAttrChecked[];
extern char svoRadioInputTagAttrSelectable[];
extern char svoRadioInputTagAttrSubmitAsEncrypted[];
extern char svoRadioInputTagAttrRequiredForPost[];
extern const SVTagVtablePrefix svoRadioInputTagVtable;
void DefaultInit___dupe13(RadioInputTagState *);
void decodeEntityText(char *);
void RegisterWithForm___dupe3(RadioInputTagState *, iks *, SVTag **);
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

extern "C" SECTION(Draw___dupe19) void Draw___dupe19(RadioInputTagState *self)
{
    SVTag *tag = &self->base;
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoRadioInputTagSource, 0x9B);
    if (!tag->m_xml) __SVO_Assert_Handler(svoRadioInputTagSource, 0x9C);
    unsigned int color = tag->m_bSelected ? self->m_highlightColor : self->m_textColor;
    int length = strlen(self->m_text);
    draw->vtable->DrawRadioButton(draw, tag->m_tagid, tag->m_x, tag->m_y, tag->m_z, tag->m_width, tag->m_height,
        color, tag->m_lineColor, tag->m_fillColor, tag->m_bSelected, self->m_isChecked,
        self->m_text, length, self->m_fontSize, 0, tag->m_tagClass);
}

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

extern "C" SECTION(HandleInput___dupe45) int HandleInput___dupe45(RadioInputTagState *self, CPage *page)
{
    SVTag *tag = &self->base;
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!tag->m_xml) __SVO_Assert_Handler(svoRadioInputTagSource, 0x79);
    if (!input) __SVO_Assert_Handler(svoRadioInputTagSource, 0x7A);
    if (!page) __SVO_Assert_Handler(svoRadioInputTagSource, 0x7B);
    if (!tag->vtable->IsSelected(tag)) return 1;
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE)) {
        if (!self->m_parentForm) __SVO_Assert_Handler(svoRadioInputTagSource, 0x81);
        CheckRadioElement(self->m_parentForm, self);
    }
    for (int action = 0; action < 4; ++action) {
        if (HasActionOccurred(input, 0x11, (PadAction)action)) {
            CDrawContextBase *draw = tag->m_contexts->drawContext;
            if (!draw) __SVO_Assert_Handler(svoRadioInputTagSource, 0x8B);
            return Navigate(tag, input, draw, tag->m_xml, page) == 0;
        }
    }
    return 1;
}

extern "C" SECTION(RadioInputTag) void RadioInputTag(RadioInputTagState *self, iks *xml, SVTag **tagList, CAllContextData *contexts)
{
    SVTag *tag = &self->base;
    SVTagConstruct(tag, xml, contexts);
    tag->vtable = &svoRadioInputTagVtable;
    DefaultInit___dupe13(self);
    getIntAttrib(tag->m_xml, svoRadioInputTagAttrFontSize, &self->m_fontSize);
    getColorAttrib(tag->m_xml, svoRadioInputTagAttrTextColor, &self->m_textColor);
    getColorAttrib(tag->m_xml, svoRadioInputTagAttrHighlightColor, &self->m_highlightColor);
    getStringAttrib(tag->m_xml, svoRadioInputTagAttrClass, &tag->m_tagClass);
    char *value = iks_find_attrib(tag->m_xml, svoRadioInputTagAttrValue);
    if (value) strcpy(self->m_value, value);
    else __SVO_Assert_Handler(svoRadioInputTagSource, 0x45);
    if (iks_find_attrib(tag->m_xml, svoRadioInputTagAttrChecked)) self->m_isChecked = 1;
    if (!getBoolAttrib(tag->m_xml, svoRadioInputTagAttrSelectable, &tag->m_bSelectable)) tag->m_bSelectable = 1;
    if (iks_has_children(tag->m_xml)) strcpy(self->m_text, iks_cdata(iks_child(tag->m_xml)));
    if (!self->m_text) __SVO_Assert_Handler(svoRadioInputTagSource, 0x5A);
    decodeEntityText(self->m_text);
    if (!getBoolAttrib(tag->m_xml, svoRadioInputTagAttrSubmitAsEncrypted, &self->m_bSubmitAsEncryped)) self->m_bSubmitAsEncryped = 0;
    if (!getBoolAttrib(tag->m_xml, svoRadioInputTagAttrRequiredForPost, &self->m_bRequiredForSubmit)) self->m_bRequiredForSubmit = 0;
    RegisterWithForm___dupe3(self, iks_parent(tag->m_xml), tagList);
}

extern "C" SECTION(RegisterWithForm___dupe3) void RegisterWithForm___dupe3(RadioInputTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm___dupe3(tag, parent, tagList);
    if (!tag->m_parentForm) __SVO_Assert_Handler(svoRadioInputTagSource, 0xDD);
    AddRadioElement(tag->m_parentForm, tag);
}
