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
#include "SVBrowser.h"
#include "CPage.h"
#include "CInputContextBase.h"
#include "CAudioContextBase.h"

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
int getPadLinkButtonAttrib(QuickLinkTagState *, iks *, char *, int *);

}
extern "C" {
extern char svoPadLinkButtonNames[25][14];
extern int svoPadLinkButtonValues[25];
}
#define SECTION(name) __attribute__((section(".svo_QuickLinkTag_" #name)))

SECTION(IsSelectable___dupe9) int IsSelectable___dupe9(void *self)
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

extern "C" SECTION(getPadLinkButtonAttrib) int getPadLinkButtonAttrib(QuickLinkTagState *tag, iks *xml, char *name, int *value)
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

extern "C" {
extern char svoQuickLinkTagSource[];
extern char svoQuickLinkSoundClass[];
void SignalPluginEvent(SVBrowserPrefix *browser, int event, SVTag *sender);
CAudioContextBaseState *GetAudioContext(void);
}
extern "C" SECTION(HandleInput___dupe39) int HandleInput___dupe39(QuickLinkTagState *tag, CPage *page)
{
    CInputContextBaseState *input = tag->base.m_contexts->inputContext;
    SVBrowserPrefix *browser = GetInstance();
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoQuickLinkTagSource, 0x7B);
    if (!input) __SVO_Assert_Handler(svoQuickLinkTagSource, 0x7C);
    if (!page) __SVO_Assert_Handler(svoQuickLinkTagSource, 0x7D);
    if (tag->m_padLinkButton == -1) __SVO_Assert_Handler(svoQuickLinkTagSource, 0x82);
    if (!tag->m_link) __SVO_Assert_Handler(svoQuickLinkTagSource, 0x88);
    if (browser->m_bShowVKB) return 1;
    if (!input->vtable->IsButtonDown(input, 0x11, tag->m_padLinkButton)) return 1;
    switch (tag->m_padLinkButton) {
    case 0x40: SignalPluginEvent(browser, 0, &tag->base); break;
    case 0x10: SignalPluginEvent(browser, 1, &tag->base); break;
    case 0x80: SignalPluginEvent(browser, 2, &tag->base); break;
    case 0x20: SignalPluginEvent(browser, 3, &tag->base); break;
    case 0x08: SignalPluginEvent(browser, 4, &tag->base); break;
    case 0x02: SignalPluginEvent(browser, 5, &tag->base); break;
    case 0x04: SignalPluginEvent(browser, 6, &tag->base); break;
    case 0x01: SignalPluginEvent(browser, 7, &tag->base); break;
    // The retail compare tree also balances two buttons that raise no plugin event.
    case 0x100:
    case 0x200:
        break;
    }
    if (page->m_state) return 1;
    if (strlen(tag->m_link)) {
        followLink(page, tag->m_link, tag->m_linkOption);
        CAudioContextBaseState *audio = GetAudioContext();
        ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 1, svoQuickLinkSoundClass);
    }
    return 0;
}

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
