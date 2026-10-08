#include "string.h"
#include "TagUtils.h"
#include "HttpUtils.h"
#include "SVOString.h"
#include "TickerTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_TickerTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern const SVTagVtablePrefix svoTickerTagVtable;
void FreeResources___dupe59(void *tag);

extern "C" {
extern char *svoTickerTypeStrings[];
extern char svoTickerTypeAttribute[];
int strcasecmp(const char *, const char *);
}
extern "C" {
extern char svoTickerTagName[];
extern char gTagNotSetStr[];
}
extern "C" {
void DefaultInit___dupe24(TickerTagState *);
long getTickerTypeAttrib(TickerTagState *, iks *, unsigned int *);
extern char svoTickerFontSizeAttribute[];
extern char svoTickerDisplayLengthAttribute[];
extern char svoTickerAlignAttribute[];
extern char svoTickerHighlightAttribute[];
extern char svoTickerTextColorAttribute[];
extern char svoTickerClassAttribute[];

}
extern "C" {
extern char *svoTickerTypeStrings[];
}
#define SECTION(name) __attribute__((section(".svo_TickerTag_" #name)))

SECTION(FreeResources___dupe59) void FreeResources___dupe59(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(HandleInput___dupe55) long HandleInput___dupe55(void *self, void *context)
{
    return 1;
}

SECTION(IsSelectable___dupe17) long IsSelectable___dupe17(void *self)
{
    return 0;
}

}

extern "C" SECTION(_TickerTag) void _TickerTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoTickerTagVtable;
    FreeResources___dupe59((void *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

extern "C" SECTION(DefaultInit___dupe24) void DefaultInit___dupe24(TickerTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoTickerTagName, 64);
    tag->m_fontSize = 14;
    tag->base.m_fillColor = 0xFFFFFF00;
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->base.m_tagClass = gTagNotSetStr;
    tag->m_text = 0;
    tag->m_align = 0;
    tag->m_displayLength = 0.0f;
    tag->base.m_bSelectable = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TickerTag", Draw___dupe27);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TickerTag", getTickerTypeAttrib);

extern "C" SECTION(TickerTag) void TickerTag(TickerTagState *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoTickerTagVtable;
    DefaultInit___dupe24(tag);
    getIntAttrib(tag->base.m_xml, svoTickerFontSizeAttribute, &tag->m_fontSize);
    getFloatAttrib(tag->base.m_xml, svoTickerDisplayLengthAttribute, &tag->m_displayLength);
    getAlignAttrib(tag->base.m_xml, svoTickerAlignAttribute, &tag->m_align);
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->base.m_fillColor = 0xFFFFFF00;
    getColorAttrib(tag->base.m_xml, svoTickerHighlightAttribute, &tag->base.m_fillColor);
    getColorAttrib(tag->base.m_xml, svoTickerTextColorAttribute, &tag->base.m_lineColor);
    getStringAttrib(tag->base.m_xml, svoTickerClassAttribute, &tag->base.m_tagClass);
    getTickerTypeAttrib(tag, tag->base.m_xml, &tag->m_type);
    if (iks_has_children(tag->base.m_xml)) {
        tag->m_text = iks_cdata(iks_child(tag->base.m_xml));
        if (tag->m_text) decodeEntityText(tag->m_text);
    }
}
