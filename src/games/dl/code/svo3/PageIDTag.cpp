#include "SVBrowser.h"
#include "CPage.h"
#include "SVOString.h"
#include <string.h>
#include "SVTag.h"

extern "C" {
extern char svoPageIDTagName[];
extern char svoPageIDTagSource[];
extern char svoPageIDNameAttribute[];
extern const SVTagVtablePrefix svoPageIDTagVtable;
char *GetTagTypeName(SVTag *tag);

#define SECTION(name) __attribute__((section(".svo_PageIDTag_" #name)))

SECTION(FreeResources___dupe51) void FreeResources___dupe51(SVTag *tag)
{
    FreeContexts(tag);
}

}

extern "C" SECTION(_PageIDTag) void _PageIDTag(SVTag *tag, int flags)
{
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

extern "C" SECTION(PageIDTag) void PageIDTag(SVTag *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(tag, xml, contexts);
    tag->vtable = &svoPageIDTagVtable;
    svstrncpy(tag->m_tagTypeName, svoPageIDTagName, 64);
    SVTag **tags = GetInstance()->m_pMainPage->m_pBackDisplayBuffer->tagList;
    for (int i = 0; i < 256 && tags[i]; ++i)
        if (tags[i] != tag && !strcmp(GetTagTypeName(tags[i]), svoPageIDTagName))
            __SVO_Assert_Handler(svoPageIDTagSource, 0x24);
    tag->m_name = iks_find_attrib(xml, svoPageIDNameAttribute);
    if (!tag->m_name) __SVO_Assert_Handler(svoPageIDTagSource, 0x2A);
}
