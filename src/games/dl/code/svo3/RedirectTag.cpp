#include "RedirectTag.h"
#include "SVOString.h"
#include "HttpUtils.h"

extern "C" {
extern char svoRedirectTagName[];
extern char svoRedirectTagSource[];
extern char svoRedirectLinkAttribute[];
extern const SVTagVtablePrefix svoRedirectTagVtable;
#define TAG_SECTION(name) __attribute__((section(".svo_RedirectTag_" #name)))

TAG_SECTION(DefaultInit___dupe20) void DefaultInit___dupe20(RedirectTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoRedirectTagName, 64);
    tag->m_link = 0;
    tag->m_alreadyRedirected = 0;
}

TAG_SECTION(RedirectTag) void RedirectTag(RedirectTagState *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoRedirectTagVtable;
    DefaultInit___dupe20(tag);
    tag->m_link = iks_find_attrib(tag->base.m_xml, svoRedirectLinkAttribute);
    if (tag->m_link) {
        tag->base.m_bSelectable = 1;
        decodeEntityText(tag->m_link);
    } else {
        tag->base.m_bSelectable = 0;
    }
}

TAG_SECTION(FreeResources___dupe42) void FreeResources___dupe42(SVTag *tag)
{
    FreeContexts(tag);
}

TAG_SECTION(HandleInput___dupe52) int HandleInput___dupe52(SVTag *tag, CPage *page)
{
    return 1;
}

TAG_SECTION(Update___dupe111) void Update___dupe111(RedirectTagState *tag, CPage *page)
{
    if (!page) __SVO_Assert_Handler(svoRedirectTagSource, 0x40);
    if (page->m_state == 0 && !tag->m_alreadyRedirected) {
        followLink(page, tag->m_link, 0);
        tag->m_alreadyRedirected = 1;
    }
}
}
