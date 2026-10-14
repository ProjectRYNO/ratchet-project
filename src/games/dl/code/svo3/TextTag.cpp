#include "TagUtils.h"
#include "HttpUtils.h"
#include "CDrawContextBase.h"
#include "CInputContextBase.h"
#include "CPage.h"
#include "string.h"
#include "SVOString.h"
#include "SVTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_TextTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "TextTag.h"

extern "C" {

extern const SVTagVtablePrefix svoTextTagVtable;
void FreeResources___dupe2(void *tag);

extern "C" {
extern char svoTextTagName[];
extern char gTagNotSetStr[];
}
extern "C" {
extern char svoTextFontSizeAttribute[];
extern char svoTextDisplayLengthAttribute[];
extern char svoTextAlignAttribute[];
extern char svoTextHighlightColorAttribute[];
extern char svoTextColorAttribute[];
extern char svoTextFontColorAttribute[];
extern char svoTextLinkAttribute[];
extern char svoTextLinkOptionAttribute[];
extern char svoTextClassAttribute[];
extern char svoTextTagSource[];
void DefaultInit___dupe2(TextTagState *);
int TrimToFitDisplaySize(CDrawContextBase *, char *, float, int);
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
}
#define SECTION(name) __attribute__((section(".svo_TextTag_" #name)))

SECTION(FreeResources___dupe2) void FreeResources___dupe2(void *self)
{
    // Retail implements this callback as a no-op.
}

int IsSelectable___dupe6(TextTagState *tag);
extern "C" SECTION(IsSelectable___dupe6) int IsSelectable___dupe6(TextTagState *tag)
{
    unsigned int selectable = 0;
    if (tag->base.m_bSelectable) selectable = tag->m_link != 0;
    return selectable;
}

}

extern "C" SECTION(_TextTag) void _TextTag(SVTag *tag, int flags)
{
    tag->vtable = &svoTextTagVtable;
    FreeResources___dupe2((void *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) { SVTagDelete(tag); return; }
}

extern "C" SECTION(DefaultInit___dupe2) void DefaultInit___dupe2(TextTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoTextTagName, 64);
    tag->m_fontSize = 14;
    tag->m_align = 0;
    tag->m_displayLength = 0.0f;
    memset(tag->m_text, 0, 128);
    tag->m_link = 0;
    tag->base.m_fillColor = 0xFFFFFF00;
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->m_textColor = 0xFFFFFFFF;
}

extern "C" SECTION(Draw___dupe8) void Draw___dupe8(TextTagState *tag)
{
    CDrawContextBase *draw = tag->base.m_contexts->drawContext;
    char *text = tag->m_text;
    if (!draw) __SVO_Assert_Handler(svoTextTagSource, 0x99);
    if (!tag->base.m_xml || (unsigned int)tag == 0xFFFFFF3C) __SVO_Assert_Handler(svoTextTagSource, 0x9A);
    unsigned int color = tag->m_textColor;
    int length = strlen(text);
    if (tag->m_displayLength > 0.0f) length = TrimToFitDisplaySize(draw, text, tag->m_displayLength, tag->m_fontSize);
    draw->vtable->SVDrawText(draw, tag->base.m_tagid, tag->base.m_x, tag->base.m_y, color,
        text, length, tag->m_fontSize, tag->m_align, tag->base.m_tagClass);
}

extern "C" SECTION(HandleInput___dupe34) int HandleInput___dupe34(TextTagState *tag, CPage *page)
{
    CInputContextBaseState *input = tag->base.m_contexts->inputContext;
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoTextTagSource, 0x71);
    if (!input) __SVO_Assert_Handler(svoTextTagSource, 0x72);
    if (!page) __SVO_Assert_Handler(svoTextTagSource, 0x73);
    if (!tag->base.vtable->IsSelected(&tag->base)) return 1;
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE) && !page->m_state && tag->m_link && *tag->m_link) {
        followLink(page, tag->m_link, tag->m_linkOption);
        return 0;
    }
    if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT)) {
        CDrawContextBase *draw = tag->base.m_contexts->drawContext;
        if (!draw) __SVO_Assert_Handler(svoTextTagSource, 0x8B);
        return !Navigate(&tag->base, input, draw, tag->base.m_xml, page);
    }
    return 1;
}

extern "C" SECTION(TextTag) void TextTag(TextTagState *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoTextTagVtable;
    DefaultInit___dupe2(tag);
    getIntAttrib(tag->base.m_xml, svoTextFontSizeAttribute, &tag->m_fontSize);
    getFloatAttrib(tag->base.m_xml, svoTextDisplayLengthAttribute, &tag->m_displayLength);
    getAlignAttrib(tag->base.m_xml, svoTextAlignAttribute, &tag->m_align);
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->base.m_fillColor = 0xFFFFFF00;
    getColorAttrib(tag->base.m_xml, svoTextHighlightColorAttribute, &tag->base.m_fillColor);
    getColorAttrib(tag->base.m_xml, svoTextColorAttribute, &tag->m_textColor);
    unsigned int color;
    if (getColorAttrib(tag->base.m_xml, svoTextFontColorAttribute, &color)) tag->m_textColor = color;
    tag->m_link = iks_find_attrib(tag->base.m_xml, svoTextLinkAttribute);
    if (tag->m_link) decodeEntityText(tag->m_link);
    tag->m_linkOption = 0;
    getLinkOptionAttrib(tag->base.m_xml, svoTextLinkOptionAttribute, &tag->m_linkOption);
    tag->base.m_bSelectable = tag->m_link != 0;
    getStringAttrib(tag->base.m_xml, svoTextClassAttribute, &tag->base.m_tagClass);
    memset(tag->m_text, 0, 128);
    if (iks_has_children(tag->base.m_xml)) {
        char *text = iks_cdata(iks_child(tag->base.m_xml));
        if (!text) __SVO_Assert_Handler(svoTextTagSource, 0x61);
        svstrncpy(tag->m_text, text, 128);
    }
    decodeEntityText(tag->m_text);
}
