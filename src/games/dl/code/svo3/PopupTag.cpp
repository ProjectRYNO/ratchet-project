#include "SVOString.h"
#include "CDrawContextBase.h"
#include "SVTag.h"

extern "C" {
extern char svoPopupTagName[];
extern char svoPopupTagSource[];
extern char svoPopupClassAttribute[];
extern const SVTagVtablePrefix svoPopupTagVtable;

#define SECTION(name) __attribute__((section(".svo_PopupTag_" #name)))

SECTION(IsSelectable___dupe15) int IsSelectable___dupe15(void *self)
{
    return 0;
}

SECTION(FreeResources___dupe38) void FreeResources___dupe38(SVTag *tag)
{
    FreeContexts(tag);
}

}

extern "C" SECTION(Draw___dupe24) void Draw___dupe24(SVTag *tag)
{
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoPopupTagSource, 0x27);
    if (!tag->m_xml) __SVO_Assert_Handler(svoPopupTagSource, 0x28);
    draw->vtable->DrawPopupBackground(draw, tag->m_x, tag->m_y, tag->m_width, tag->m_height,
                                      tag->m_lineColor, tag->m_fillColor, tag->m_tagClass);
}

struct PopupTagState { // 0xB4
    /* 0x00 */ SVTag base;
    PopupTagState(iks *xml, CAllContextData *contexts) __asm__("PopupTag");
};
SECTION(PopupTag) PopupTagState::PopupTagState(iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&base, xml, contexts);
    base.vtable = &svoPopupTagVtable;
    svstrncpy(base.m_tagTypeName, svoPopupTagName, 64);
    base.m_tagClass = iks_find_attrib(base.m_xml, svoPopupClassAttribute);
}
