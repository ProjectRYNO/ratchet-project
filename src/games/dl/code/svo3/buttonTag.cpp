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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/buttonTag", ButtonTag);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/buttonTag", Draw___dupe9);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/buttonTag", HandleInput___dupe35);

extern "C" SECTION(operator.delete___dupe9) void buttonTagoperator_delete___dupe9(void *memory)
{
    __SVO_Assert_Handler(svoSockSource, 0x34);
}
