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
#define SECTION(name) __attribute__((section(".svo_TextTag_" #name)))

SECTION(FreeResources___dupe2) void FreeResources___dupe2(void *self)
{
    // Retail implements this callback as a no-op.
}

long IsSelectable___dupe6(TextTagState *tag);
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextTag", IsSelectable___dupe6);

}

extern "C" SECTION(_TextTag) void _TextTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoTextTagVtable;
    FreeResources___dupe2((void *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

extern "C" SECTION(DefaultInit___dupe2) void DefaultInit___dupe2(TextTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoTextTagName, 64);
    tag->m_align = 0;
    tag->m_fontSize = 14;
    tag->m_displayLength = 0.0f;
    memset(tag->m_text, 0, 128);
    tag->m_link = 0;
    tag->m_textColor = 0xFFFFFFFF;
    tag->base.m_fillColor = 0xFFFFFF00;
    tag->base.m_lineColor = 0xFFFFFFFF;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextTag", Draw___dupe8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextTag", HandleInput___dupe34);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextTag", TextTag);
