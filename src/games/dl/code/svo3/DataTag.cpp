#include "SVOString.h"
#include <string.h>
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_DataTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "DataTag.h"

extern "C" {
extern char svoDataTagName[];
extern char svoDataTagSource[];
extern char svoDataIDAttribute[];
extern char svoDataURIAttribute[];
extern char svoDataSrcAttribute[];
extern char svoDataAllowNavAttribute[];
extern char svoDataFalse[];
extern char svoDataTrue[];
void URIStoreAdd(char *lookup, char *value);
void FileDownloadQueueAdd(char *id, char *path);
int strcasecmp(const char *, const char *);


#define SECTION(name) __attribute__((section(".svo_DataTag_" #name)))

SECTION(FreeResources___dupe46) void FreeResources___dupe46(SVTag *tag)
{
    FreeContexts(tag);
}

SECTION(okToNavigate___dupe3) long okToNavigate___dupe3(DataTagState *tag)
{
    return tag->m_bAllowNavigationDuringDownload;
}

}

extern "C" SECTION(_DataTag) void _DataTag(DataTagState *tag, int flags)
{
    tag->base.vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(&tag->base);
}


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/DataTag", DataTag);

extern "C" SECTION(DefaultInit___dupe21) void DefaultInit___dupe21(DataTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoDataTagName, 64);
    tag->m_bAllowNavigationDuringDownload = 1;
}


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/DataTag", getDataTypeAttrib);

extern "C" SECTION(ParseFileTag) long ParseFileTag(DataTagState *tag, iks *xml)
{
    char *id = iks_find_attrib(xml, svoDataIDAttribute);
    char *src = iks_find_attrib(xml, svoDataSrcAttribute);
    if (!id || !src) {
        __SVO_Assert_Handler(svoDataTagSource, 0x6C);
        return 0;
    }
    FileDownloadQueueAdd(id, src);
    char *allow = iks_find_attrib(xml, svoDataAllowNavAttribute);
    if (!allow) return 1;
    if (!strcasecmp(allow, svoDataFalse)) tag->m_bAllowNavigationDuringDownload = 0;
    else if (!strcasecmp(allow, svoDataTrue)) tag->m_bAllowNavigationDuringDownload = 1;
    else {
        __SVO_Assert_Handler(svoDataTagSource, 0x7F);
        return 0;
    }
    return 1;
}


extern "C" SECTION(ParseURITag) long ParseURITag(DataTagState *tag, iks *xml)
{
    char *id = iks_find_attrib(xml, svoDataIDAttribute);
    char *uri = iks_find_attrib(xml, svoDataURIAttribute);
    if (!id || !uri) __SVO_Assert_Handler(svoDataTagSource, 0x4B);
    else URIStoreAdd(id, uri);
    return 1;
}
