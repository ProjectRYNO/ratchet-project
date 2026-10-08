#include "string.h"
#include "SVOString.h"
#include "TagUtils.h"
#include "QuickLinkTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_QuickLinkTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern char svoQuickLinkTagName[];
extern char gTagNotSetStr[];

extern "C" {
void decodeEntityText(char *text);
extern const SVTagVtablePrefix svoQuickLinkVtable;
extern char svoQuickLinkButtonAttribute[];
extern char svoQuickLinkOptionAttribute[];
extern char svoQuickLinkLinkAttribute[];
void DefaultInit___dupe8(QuickLinkTagState *);
long getPadLinkButtonAttrib(QuickLinkTagState *, iks *, char *, int *);

}
extern "C" {
extern char svoPadLinkButtonNames[25][14];
extern int svoPadLinkButtonValues[25];
}
#define SECTION(name) __attribute__((section(".svo_QuickLinkTag_" #name)))

SECTION(IsSelectable___dupe9) long IsSelectable___dupe9(void *self)
{
    return 0;
}

SECTION(FreeResources___dupe13) void FreeResources___dupe13(SVTag *tag)
{
    FreeContexts(tag);
}

}

extern "C" SECTION(DefaultInit___dupe8) void DefaultInit___dupe8(QuickLinkTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoQuickLinkTagName, 64);
    tag->m_padLinkButton = -1;
    tag->m_link = 0;
}

extern "C" SECTION(getPadLinkButtonAttrib) long getPadLinkButtonAttrib(QuickLinkTagState *tag, iks *xml, char *name, int *value)
{
    char *text = iks_find_attrib(xml, name);
    if (text) {
        for (int i = 0; i < 25; ++i) {
            if (!strcmp(text, svoPadLinkButtonNames[i])) {
                *value = svoPadLinkButtonValues[i];
                return 1;
            }
        }
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/QuickLinkTag", HandleInput___dupe39);

extern "C" SECTION(QuickLinkTag) void QuickLinkTag(QuickLinkTagState *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoQuickLinkVtable;
    DefaultInit___dupe8(tag);
    getPadLinkButtonAttrib(tag, tag->base.m_xml, svoQuickLinkButtonAttribute, &tag->m_padLinkButton);
    tag->m_linkOption = 0;
    getLinkOptionAttrib(tag->base.m_xml, svoQuickLinkOptionAttribute, &tag->m_linkOption);
    tag->m_link = iks_find_attrib(tag->base.m_xml, svoQuickLinkLinkAttribute);
    if (tag->m_link) decodeEntityText(tag->m_link);
}
