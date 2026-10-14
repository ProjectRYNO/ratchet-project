#include "RectangleTag.h"
#include "TagUtils.h"
#include "SVOString.h"
#include "CDrawContextBase.h"

extern "C" {
extern char svoRectangleTagName[];
extern char svoRectangleTagSource[];
extern char svoRectangleThicknessAttribute[];
extern char svoRectangleRadiusAttribute[];
extern char svoRectangleZAttribute[];
extern char svoRectangleClassAttribute[];
extern char *svoRectangleGradientAttributes[4];
extern const SVTagVtablePrefix svoRectangleTagVtable;
#define TAG_SECTION(name) __attribute__((section(".svo_RectangleTag_" #name)))

TAG_SECTION(DefaultInit___dupe5) void DefaultInit___dupe5(RectangleTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoRectangleTagName, 64);
    tag->m_zVal = 100000.0f;
    tag->m_lineThickness = 2;
    tag->m_cornerRadius = 0;
    tag->base.m_tagClass = 0;
    tag->m_gradientColor[0] = 0;
    tag->m_gradientColor[1] = 0;
    tag->m_gradientColor[2] = 0;
    tag->m_gradientColor[3] = 0;
}

struct RectangleTagCtor {
    RectangleTagState state;
    RectangleTagCtor(iks *xml, CAllContextData *contexts) __asm__("RectangleTag");
};
TAG_SECTION(RectangleTag) RectangleTagCtor::RectangleTagCtor(iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&state.base, xml, contexts);
    state.base.vtable = &svoRectangleTagVtable;
    DefaultInit___dupe5(&state);
    getIntAttrib(state.base.m_xml, svoRectangleThicknessAttribute, &state.m_lineThickness);
    getIntAttrib(state.base.m_xml, svoRectangleRadiusAttribute, &state.m_cornerRadius);
    getFloatAttrib(state.base.m_xml, svoRectangleZAttribute, &state.m_zVal);
    state.base.m_tagClass = iks_find_attrib(state.base.m_xml, svoRectangleClassAttribute);
    for (int i = 0; i < 4; ++i) {
        if (!getColorAttrib(state.base.m_xml, svoRectangleGradientAttributes[i], &state.m_gradientColor[i]))
            break;
    }
}

TAG_SECTION(FreeResources___dupe7) void FreeResources___dupe7(SVTag *tag)
{
    FreeContexts(tag);
}

TAG_SECTION(HandleInput___dupe36) int HandleInput___dupe36(SVTag *tag, CPage *page)
{
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!tag->m_xml) __SVO_Assert_Handler(svoRectangleTagSource, 0x59);
    if (!input) __SVO_Assert_Handler(svoRectangleTagSource, 0x5A);
    if (!page) __SVO_Assert_Handler(svoRectangleTagSource, 0x5B);
    return 1;
}

TAG_SECTION(Draw___dupe10) void Draw___dupe10(RectangleTagState *tag)
{
    CDrawContextBase *draw = tag->base.m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoRectangleTagSource, 0x63);
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoRectangleTagSource, 0x64);
    if (tag->m_gradientColor[0] || tag->m_gradientColor[1] ||
        tag->m_gradientColor[2] || tag->m_gradientColor[3])
        draw->vtable->DrawRectangle(draw, tag->base.m_tagid, tag->base.m_x, tag->base.m_y,
                                    tag->base.m_width, tag->base.m_height,
                                    tag->base.m_lineColor, tag->base.m_fillColor,
                                    tag->m_lineThickness, tag->m_cornerRadius, tag->m_zVal,
                                    tag->m_gradientColor, tag->base.m_tagClass);
    else
        draw->vtable->DrawRectangle(draw, tag->base.m_tagid, tag->base.m_x, tag->base.m_y,
                                    tag->base.m_width, tag->base.m_height,
                                    tag->base.m_lineColor, tag->base.m_fillColor,
                                    tag->m_lineThickness, tag->m_cornerRadius, tag->m_zVal,
                                    0, tag->base.m_tagClass);
}
}
