#include "TagUtils.h"
#include "SVOString.h"
#include "buttonTag.h"
#include "CInputContextBase.h"
#include "CDrawContextBase.h"
#include "CPage.h"
#include "string.h"
#include "CMemoryContextBase.h"
#include "SVTagModule.h"
#include "string.h"
#include "SVOString.h"
#include "buttonTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_buttonTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern const SVTagVtablePrefix svoButtonTagVtable;
void FreeResources___dupe5(void *tag);

extern "C" {
extern char svoButtonTagName[];
extern char gTagNotSetStr[];
}
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoSockSource[];
void buttonTagoperator_delete___dupe9(void *memory) __asm__("operator.delete___dupe9");

}
extern "C" {
extern char svoButtonSource[];
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
int TrimToFitDisplaySize(CDrawContextBase *, char *, float, int);
CAudioContextBaseState *GetAudioContext();
extern char svoButtonAudioClass[];
extern char svoSubmitAudioClass[];
}
extern "C" {
extern char svoButtonTagAttrFontSize[];
extern char svoButtonTagAttrDisplayLength[];
extern char svoButtonTagAttrAlign[];
extern char svoButtonTagAttrBorder[];
extern char svoButtonTagAttrFalse[];
extern char svoButtonTagAttrFillColor[];
extern char svoButtonTagAttrLineColor[];
extern char svoButtonTagAttrTextColor[];
extern char svoButtonTagAttrHighlightFillColor[];
extern char svoButtonTagAttrHighlightLineColor[];
extern char svoButtonTagAttrHighlightTextColor[];
extern char svoButtonTagAttrClass[];
extern char svoButtonTagAttrHref[];
extern char svoButtonTagAttrSelectable[];
extern char svoButtonTagAttrTrue[];
extern char svoButtonTagAttrDefault[];
extern char svoButtonTagAttrLinkOption[];
extern const SVTagVtablePrefix svoButtonTagVtable;
void DefaultInit___dupe4(ButtonTagState *);
void decodeEntityText(char *);
}
#define SECTION(name) __attribute__((section(".svo_buttonTag_" #name)))

SECTION(FreeResources___dupe5) void FreeResources___dupe5(void *self)
{
    // Retail implements this callback as a no-op.
}

}

extern "C" SECTION(_ButtonTag) void _ButtonTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoButtonTagVtable;
    FreeResources___dupe5((void *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

extern "C" SECTION(ButtonTag) void ButtonTag(ButtonTagState *self, iks *xml, CAllContextData *contexts)
{
    SVTag *tag = &self->base;
    SVTagConstruct(tag, xml, contexts);
    tag->vtable = &svoButtonTagVtable;
    DefaultInit___dupe4(self);
    getIntAttrib(tag->m_xml, svoButtonTagAttrFontSize, &self->m_fontSize);
    getFloatAttrib(tag->m_xml, svoButtonTagAttrDisplayLength, &self->m_displayLength);
    getAlignAttrib(tag->m_xml, svoButtonTagAttrAlign, &self->m_align);
    char *border = iks_find_attrib(tag->m_xml, svoButtonTagAttrBorder);
    if (border && !strcmp(border, svoButtonTagAttrFalse)) self->m_drawBorder = 0;
    getColorAttrib(tag->m_xml, svoButtonTagAttrFillColor, &tag->m_fillColor);
    getColorAttrib(tag->m_xml, svoButtonTagAttrLineColor, &tag->m_lineColor);
    getColorAttrib(tag->m_xml, svoButtonTagAttrTextColor, &self->m_textColor);
    getColorAttrib(tag->m_xml, svoButtonTagAttrHighlightFillColor, &self->m_highlightFillColor);
    getColorAttrib(tag->m_xml, svoButtonTagAttrHighlightLineColor, &self->m_highlightLineColor);
    getColorAttrib(tag->m_xml, svoButtonTagAttrHighlightTextColor, &self->m_highlightTextColor);
    getStringAttrib(tag->m_xml, svoButtonTagAttrClass, &tag->m_tagClass);
    self->m_link = iks_find_attrib(tag->m_xml, svoButtonTagAttrHref);
    if (self->m_link) { tag->m_bSelectable = 1; decodeEntityText(self->m_link); }
    else tag->m_bSelectable = 0;
    char *selectable = 0;
    if (getStringAttrib(tag->m_xml, svoButtonTagAttrSelectable, &selectable))
        tag->m_bSelectable = !strcmp(selectable, svoButtonTagAttrTrue) || !strcmp(selectable, svoButtonTagAttrDefault);
    self->m_linkOption = 0;
    getLinkOptionAttrib(tag->m_xml, svoButtonTagAttrLinkOption, &self->m_linkOption);
    char *text = 0;
    if (iks_has_children(tag->m_xml)) text = iks_cdata(iks_child(tag->m_xml));
    if (!text) __SVO_Assert_Handler(svoButtonSource, 0x7A);
    svstrncpy(self->m_text, text, 128);
    decodeEntityText(self->m_text);
}

extern "C" SECTION(DefaultInit___dupe4) void DefaultInit___dupe4(ButtonTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoButtonTagName, 64);
    tag->m_highlightTextColor = 0xFF000000;
    tag->m_fontSize = 14;
    tag->m_drawBorder = 1;
    tag->m_textColor = 0xFFFFFFFF;
    tag->m_highlightFillColor = 0xFFFFFF00;
    tag->m_align = 1;
    tag->m_displayLength = 0.0f;
    tag->m_link = 0;
    tag->base.m_fillColor = 0xFF000000;
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->m_highlightLineColor = 0xFF000000;
}

extern "C" SECTION(Draw___dupe9) void Draw___dupe9(ButtonTagState *self)
{
    SVTag *tag = &self->base;
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoButtonSource, 0xDC);
    if (!tag->m_xml || !self->m_text) __SVO_Assert_Handler(svoButtonSource, 0xDD);
    int length = strlen(self->m_text);
    if (self->m_displayLength > 0.0f && self->m_drawBorder)
        length = TrimToFitDisplaySize(draw, self->m_text, self->m_displayLength, self->m_fontSize);
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
        line, fill, text, tag->m_bSelected, self->m_text, length, self->m_fontSize, self->m_align,
        tag->m_tagClass, self->m_drawBorder);
}

extern "C" SECTION(HandleInput___dupe35) int HandleInput___dupe35(ButtonTagState *self, CPage *page)
{
    SVTag *tag = &self->base;
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!tag->m_xml) __SVO_Assert_Handler(svoButtonSource, 0xA2);
    if (!input) __SVO_Assert_Handler(svoButtonSource, 0xA3);
    if (!page) __SVO_Assert_Handler(svoButtonSource, 0xA4);
    if (!tag->vtable->IsSelected(tag)) return 1;
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE) && !tag->vtable->IgnoreInput(tag)) {
        if (page->m_state == 0 && self->m_link && *self->m_link) {
            followLink(page, self->m_link, self->m_linkOption);
            CAudioContextBaseState *audio = GetAudioContext();
            ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 1, svoButtonAudioClass);
            return 0;
        }
        CAudioContextBaseState *audio = GetAudioContext();
        ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 6, svoButtonAudioClass);
    }
    for (int action = 0; action < 4; ++action) {
        if (HasActionOccurred(input, 0x11, (PadAction)action)) {
            CDrawContextBase *draw = tag->m_contexts->drawContext;
            if (!draw) __SVO_Assert_Handler(svoButtonSource, 0xCE);
            return Navigate(tag, input, draw, tag->m_xml, page) == 0;
        }
    }
    return 1;
}

extern "C" SECTION(operator.delete___dupe9) void buttonTagoperator_delete___dupe9(void *memory)
{
    __SVO_Assert_Handler(svoSockSource, 0x34);
}
