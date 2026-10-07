#include "SVOString.h"
#include "CDrawContextBase.h"
#include "SVTag.h"

extern "C" {
extern char svoPopupTagName[];
extern char svoPopupTagSource[];
extern char svoPopupClassAttribute[];
extern const SVTagVtablePrefix svoPopupTagVtable;


#define SECTION(name) __attribute__((section(".svo_PopupTag_" #name)))

SECTION(IsSelectable___dupe15) long IsSelectable___dupe15(void *self)
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


extern "C" SECTION(PopupTag) void PopupTag(SVTag *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(tag, xml, contexts);
    tag->vtable = &svoPopupTagVtable;
    svstrncpy(tag->m_tagTypeName, svoPopupTagName, 64);
    tag->m_tagClass = iks_find_attrib(tag->m_xml, svoPopupClassAttribute);
}
