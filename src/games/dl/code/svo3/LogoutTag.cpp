#include "common.h"
// Retain the unresolved wrapper at its original address.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_LogoutTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "LogoutTag.h"
#include "SVBrowser.h"
#include "SVOString.h"

extern "C" {
extern char svoLogoutTagName[];
extern char svoLogoutTagSource[];
extern const SVTagVtablePrefix svoLogoutTagVtable;
#define TAG_SECTION(name) __attribute__((section(".svo_LogoutTag_" #name)))

TAG_SECTION(DefaultInit___dupe17) void DefaultInit___dupe17(SVTag *tag)
{
    svstrncpy(tag->m_tagTypeName, svoLogoutTagName, 64);
    tag->m_bSelected = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/LogoutTag", LogoutTag);

TAG_SECTION(FreeResources___dupe34) void FreeResources___dupe34(SVTag *tag)
{
    FreeContexts(tag);
}

TAG_SECTION(HandleInput___dupe49) int HandleInput___dupe49(SVTag *tag, CPage *page)
{
    return 1;
}

TAG_SECTION(Update___dupe110) void Update___dupe110(SVTag *tag, CPage *page)
{
    if (!page) __SVO_Assert_Handler(svoLogoutTagSource, 0x36);
    if (page->m_state == 0) {
        SVBrowserPrefix *browser = GetInstance();
        if (!browser) __SVO_Assert_Handler(svoLogoutTagSource, 0x3B);
        SetLogout(browser);
    }
}
}
