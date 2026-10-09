#include "TagUtils.h"
#include "SVOString.h"
#include "SubmitInputTag.h"
#include "CInputContextBase.h"
#include "CDrawContextBase.h"
#include "CPage.h"
#include "string.h"
#include "string.h"
#include "SubmitInputTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SubmitInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

SVTagModuleState *getInstance___dupe17(void);
extern char svoSubmitInputTagFormNameAttribute[];
void AddSubmitElement(FormTag *form, SubmitInputTagState *tag);
extern char svoSubmitInputTagSource[];


extern "C" {
extern char svoSubmitInputTagSource[];
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
int TrimToFitDisplaySize(CDrawContextBase *, char *, float, int);
CAudioContextBaseState *GetAudioContext();
extern char svoButtonAudioClass[];
extern char svoSubmitAudioClass[];
void Submit(FormTag *, CPage *);
}
extern "C" {
extern char svoSubmitInputTagAttrFontSize[];
extern char svoSubmitInputTagAttrDisplayLength[];
extern char svoSubmitInputTagAttrAlign[];
extern char svoSubmitInputTagAttrFillColor[];
extern char svoSubmitInputTagAttrLineColor[];
extern char svoSubmitInputTagAttrTextColor[];
extern char svoSubmitInputTagAttrHighlightFillColor[];
extern char svoSubmitInputTagAttrHighlightLineColor[];
extern char svoSubmitInputTagAttrHighlightTextColor[];
extern char svoSubmitInputTagAttrClass[];
extern char svoSubmitInputTagAttrValue[];
extern const SVTagVtablePrefix svoSubmitInputTagVtable;
void DefaultInit___dupe16(SubmitInputTagState *);
void decodeEntityText(char *);
void RegisterWithForm___dupe5(SubmitInputTagState *, iks *, SVTag **);
}
extern "C" {
extern char svoSubmitTagName[];
extern char svoSubmitDefaultText[] __attribute__((aligned(4)));
}
#define SECTION(name) __attribute__((section(".svo_SubmitInputTag_" #name)))

SECTION(IsSelectable___dupe14) long IsSelectable___dupe14(void *self)
{
    return 1;
}

SECTION(FreeResources___dupe32) void FreeResources___dupe32(SVTag *tag)
{
    FreeContexts(tag);
}

}

extern "C" SECTION(DefaultInit___dupe16) void DefaultInit___dupe16(SubmitInputTagState *self)
{
    svstrncpy(self->base.m_tagTypeName, svoSubmitTagName, 64);
    memset(self->m_value, 0, 128);
    memcpy(self->m_value, svoSubmitDefaultText, 7);
    self->base.m_bSelectable = 1;
    self->m_fontSize = 14;
    self->m_textColor = 0xFFFFFFFF;
    self->m_highlightFillColor = 0xFFFFFF00;
    self->m_highlightTextColor = 0xFF000000;
    self->m_align = 1;
    self->m_displayLength = 0;
    self->base.m_fillColor = 0xFF000000;
    self->base.m_lineColor = 0xFFFFFFFF;
    self->m_highlightLineColor = 0xFF000000;
}

extern "C" SECTION(Draw___dupe22) void Draw___dupe22(SubmitInputTagState *self)
{
    SVTag *tag = &self->base;
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoSubmitInputTagSource, 0x80);
    if (!tag->m_xml) __SVO_Assert_Handler(svoSubmitInputTagSource, 0x81);
    int length = strlen(self->m_value);
    if (self->m_displayLength > 0.0f)
        length = TrimToFitDisplaySize(draw, self->m_value, self->m_displayLength, self->m_fontSize);
    unsigned int fill;
    unsigned int line;
    unsigned int text;
    if (tag->vtable->IsSelected(tag)) {
        fill = self->m_highlightFillColor;
        line = self->m_highlightLineColor;
        text = self->m_highlightTextColor;
    } else {
        fill = tag->m_fillColor;
        line = tag->m_lineColor;
        text = self->m_textColor;
    }
    draw->vtable->DrawButton(draw, tag->m_tagid, tag->m_x, tag->m_y, tag->m_z, tag->m_width, tag->m_height,
        line, fill, text, tag->m_bSelected, self->m_value, length, self->m_fontSize, self->m_align,
        tag->m_tagClass, 1);
}

extern "C" SECTION(FindParentForm___dupe5) FormTag *FindParentForm___dupe5(SubmitInputTagState *tag, iks *parent, SVTag **tagList)
{
    if (!parent) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xA9);
    if (!tagList) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xAA);
    SVTagModuleState *module = getInstance___dupe17();
    if (!module->vtable->IsMyTag(module, parent)) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xB2);
    char *formName = iks_find_attrib(parent, svoSubmitInputTagFormNameAttribute);
    if (!formName) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xB8);
    for (int i = 0; i < 256; ++i) {
        SVTag *candidate = tagList[i];
        if (candidate) {
            char *name = candidate->vtable->GetTagName(candidate);
            if (!name) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xBF);
            if (!strcmp(name, formName)) return (FormTag *)tagList[i];
        }
    }
    return 0;
}

extern "C" SECTION(HandleInput___dupe48) int HandleInput___dupe48(SubmitInputTagState *self, CPage *page)
{
    SVTag *tag = &self->base;
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!tag->m_xml) __SVO_Assert_Handler(svoSubmitInputTagSource, 0x5D);
    if (!input) __SVO_Assert_Handler(svoSubmitInputTagSource, 0x5E);
    if (!page) __SVO_Assert_Handler(svoSubmitInputTagSource, 0x5F);
    if (!tag->vtable->IsSelected(tag)) return 1;
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE)) {
        if (!self->m_parentForm) __SVO_Assert_Handler(svoSubmitInputTagSource, 0x65);
        Submit(self->m_parentForm, page);
        CAudioContextBaseState *audio = GetAudioContext();
        ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 1, svoSubmitAudioClass);
    }
    for (int action = 0; action < 4; ++action) {
        if (HasActionOccurred(input, 0x11, (PadAction)action)) {
            CDrawContextBase *draw = tag->m_contexts->drawContext;
            if (!draw) __SVO_Assert_Handler(svoSubmitInputTagSource, 0x71);
            return Navigate(tag, input, draw, tag->m_xml, page) == 0;
        }
    }
    return 1;
}

extern "C" SECTION(RegisterWithForm___dupe5) void RegisterWithForm___dupe5(SubmitInputTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm___dupe5(tag, parent, tagList);
    if (!tag->m_parentForm) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xD1);
    AddSubmitElement(tag->m_parentForm, tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", SubmitInputTag);
