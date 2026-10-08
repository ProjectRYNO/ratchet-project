#include "TagUtils.h"
#include "LineTag.h"
#include "common.h"
// Retain the unresolved wrapper at its original address.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_LineTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVOString.h"
#include "CDrawContextBase.h"

extern "C" {
extern char svoLineTagName[];
extern char svoLineTagSource[];
extern char svoLineEndXAttribute[];
extern char svoLineEndYAttribute[];
extern char svoLineThicknessAttribute[];
extern char svoLineColorAttribute[];
extern char svoLineClassAttribute[];
extern const SVTagVtablePrefix svoLineTagVtable;
extern "C" {
void DefaultInit___dupe7(LineTagState *);
}
#define SECTION(name) TAG_SECTION(name)
#define TAG_SECTION(name) __attribute__((section(".svo_LineTag_" #name)))

TAG_SECTION(DefaultInit___dupe7) void DefaultInit___dupe7(LineTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoLineTagName, 64);
    tag->m_thickness = 2.0f;
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->m_endX = tag->base.m_x;
    tag->m_endY = tag->base.m_y;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/LineTag", LineTag);

TAG_SECTION(FreeResources___dupe12) void FreeResources___dupe12(SVTag *tag)
{
    FreeContexts(tag);
}

TAG_SECTION(HandleInput___dupe38) int HandleInput___dupe38(SVTag *tag, CPage *page)
{
    return 1;
}

TAG_SECTION(Draw___dupe12) void Draw___dupe12(LineTagState *tag)
{
    CDrawContextBase *draw = tag->base.m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoLineTagSource, 0x41);
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoLineTagSource, 0x42);
    draw->vtable->DrawLine(draw, tag->base.m_tagid, tag->base.m_x, tag->base.m_y,
                           tag->m_endX, tag->m_endY, tag->base.m_z, tag->m_thickness,
                           tag->base.m_lineColor, tag->base.m_tagClass);
}

TAG_SECTION(IsSelectable___dupe8) int IsSelectable___dupe8(SVTag *tag)
{
    return 0;
}
}
