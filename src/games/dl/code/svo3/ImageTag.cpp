#include "string.h"
#include "TagUtils.h"
#include "SVOString.h"
#include "ImageTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_ImageTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern char *svoImageTypeStrings[];

extern "C" {
extern char svoImageTagName[];
extern char gTagNotSetStr[];

}
extern "C" {
extern char *svoImageTypeStrings[];
}
#define SECTION(name) __attribute__((section(".svo_ImageTag_" #name)))

SECTION(FreeResources___dupe18) void FreeResources___dupe18(SVTag *tag)
{
    FreeContexts(tag);
}

long IsSelectable___dupe11(SVTag *tag);
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", IsSelectable___dupe11);

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", _ImageTag);

extern "C" SECTION(DefaultInit___dupe10) void DefaultInit___dupe10(ImageTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoImageTagName, 64);
    tag->m_align = 1;
    tag->m_displayLength = 0;
    memset(tag->m_link, 0, 128);
    tag->m_imageType = 1;
    tag->base.m_fillColor = 0xFFFFFFFF;
    tag->base.m_lineColor = 0xFF000000;
    tag->base.m_tagClass = gTagNotSetStr;
    tag->Height = 0;
    tag->m_iID = 0;
    tag->ImageBuf = 0;
    tag->Width = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", Draw___dupe14);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", getImageTypeAttrib);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", HandleInput___dupe41);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", ImageTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", InitImage___dupe2);
