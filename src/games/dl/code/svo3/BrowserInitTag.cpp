#include "common.h"
// Retain the unresolved wrapper at its original address.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_BrowserInitTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "BrowserInitTag.h"
#include "SVBrowser.h"
#include "SVOString.h"
#include "CSystemContextBase.h"

extern "C" {
extern char svoBrowserInitTagName[];
extern const SVTagVtablePrefix svoBrowserInitTagVtable;
extern int svoBrowserInitAlreadyHappened;
#define TAG_SECTION(name) __attribute__((section(".svo_BrowserInitTag_" #name)))

TAG_SECTION(DefaultInit___dupe25) void DefaultInit___dupe25(SVTag *tag)
{
    svstrncpy(tag->m_tagTypeName, svoBrowserInitTagName, 64);
}

TAG_SECTION(_BrowserInitTag) void _BrowserInitTag(SVTag *tag, int flags)
{
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/BrowserInitTag", BrowserInitTag);

TAG_SECTION(Update___dupe113) void Update___dupe113(SVTag *tag, CPage *page)
{
    if (!svoBrowserInitAlreadyHappened && BrowserIsIdle(GetInstance())) {
        CSystemContextBase *system = GetSystemContext();
        system->vtable->HandleOnlineInitComplete(system);
        svoBrowserInitAlreadyHappened = 1;
    }
}

TAG_SECTION(FreeResources___dupe60) void FreeResources___dupe60(SVTag *tag)
{
    FreeContexts(tag);
}
}
