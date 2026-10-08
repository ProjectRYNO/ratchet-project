#include "SVTagModuleList.h"
#include "SVTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_CPage_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "CPage.h"

extern "C" {

extern "C" {
extern char svoPageSource[];
long DefaultHandleInput(SVTag *tag, CPage *page);
void FreeBackDisplayBuffer(CPage *page);
void ReAllocBackDisplayBufferParser(CPage *page);
}
#define SECTION(name) __attribute__((section(".svo_CPage_" #name)))

SECTION(okToNavigate___dupe2) long okToNavigate___dupe2(CPage *page)
{
    return page->m_bIsActive && page->m_state == 0;
}

SECTION(GetTagAtIndex) SVTag *GetTagAtIndex(CPage *page, int index)
{
    return page->m_pFrontDisplayBuffer->tagList[index];
}

SECTION(SetTagAtIndex) void SetTagAtIndex(CPage *page, int index, SVTag *tag)
{
    page->m_pBackDisplayBuffer->tagList[index] = tag;
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", _CPage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", addObject);

extern "C" SECTION(addToHistory) long addToHistory(CPage *page, char *path)
{
    if (!path) __SVO_Assert_Handler(svoPageSource, 0x30D);
    push(&page->m_history, path);
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", adjustPathBinaryDownload);

extern "C" SECTION(autoRefreshPage) long autoRefreshPage(CPage *page)
{
    SVChronographState *timer = &page->m_pageRefreshTimer;
    if (!IsRunning(timer) || Elapsed(timer) < page->m_pageRefreshSeconds) return 0;
    Reset___dupe5(timer);
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", callGenericDownloadCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", ClosePopup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", CPage);

extern "C" SECTION(DestroyInTransitionArray) void DestroyInTransitionArray(CPage *page)
{
    // Retail branches over the element-clearing loop.
    page->inTransitionCount = 0;
}

extern "C" SECTION(DestroyPostTransitionArray) void DestroyPostTransitionArray(CPage *page)
{
    // Retail branches over the element-clearing loop.
    page->postTransitionCount = 0;
}

extern "C" SECTION(DestroyPreTransitionArray) void DestroyPreTransitionArray(CPage *page)
{
    // Retail branches over the element-clearing loop.
    page->preTransitionCount = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", doAfterParseTags);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", doPost);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", doRequest);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", download);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", draw);

extern "C" SECTION(EnterNewPage___dupe30) void EnterNewPage___dupe30(CPage *page)
{
    SVTagModuleState **entry = getInstance___dupe3()->m_modules + 1;
    while (*entry) {
        SVTagModuleState *module = *entry++;
        module->vtable->EnterNewPage(module);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", FindAndSetDefualtTextAreaScroll);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", followLink);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", frameUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", FreeBackDisplayBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", FreeDisplayBuffers);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", FreeFrontDisplayBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", freeResources);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", GenerateLagListInfo);

extern "C" SECTION(getIndexOfNextAvailEntryInTagList) long getIndexOfNextAvailEntryInTagList(CPage *page)
{
    SVTag **entries = page->m_pBackDisplayBuffer->tagList;
    for (int i = 0; i < 256; ++i) {
        if (!entries[i]) return i;
    }
    __SVO_Assert_Handler(svoPageSource, 0x5D5);
    return -1;
}

extern "C" SECTION(GetSelectedTagName) char *GetSelectedTagName(CPage *page)
{
    SVTag **entries = page->m_pFrontDisplayBuffer->tagList;
    for (int i = 0; i < 256 && entries[i]; ++i) {
        SVTag *tag = entries[i];
        if (tag->vtable->IsSelected(tag)) {
            tag = entries[i];
            return tag->vtable->GetTagName(tag);
        }
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", getTopOfHistory);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", handleDefaultSelection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", handleInput);

extern "C" SECTION(handleTextEntryDefaultInput) long handleTextEntryDefaultInput(CPage *page)
{
    if (page->m_defTextEntryTag) return DefaultHandleInput(page->m_defTextEntryTag, page);
    return 1;
}

extern "C" SECTION(handleTextScrollDefaultInput) long handleTextScrollDefaultInput(CPage *page)
{
    if (page->m_defTextScrollTag) return DefaultHandleInput(page->m_defTextScrollTag, page);
    return 1;
}

extern "C" SECTION(handleUpdate) void handleUpdate(CPage *page)
{
    for (int i = 0; i < 256 && GetTagAtIndex(page, i); ++i) {
        SVTag *tag = GetTagAtIndex(page, i);
        if (!tag) __SVO_Assert_Handler(svoPageSource, 0x638);
        tag->vtable->Update(tag, page);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", LeaveCurrentPage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", LoadStatePostGameFromPersistentData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", operator.delete___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", operator.new___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", parseCBHelper);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", parseTagsCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", pathIsFullyQualified);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", pathIsStatic);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", PopInTransitArray);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", PushPostTransitionArray);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", ReAllocBackDisplayBufferParser);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", requestBinary);

extern "C" SECTION(ResetBackDisplayBuffer) void ResetBackDisplayBuffer(CPage *page)
{
    FreeBackDisplayBuffer(page);
    ReAllocBackDisplayBufferParser(page);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", resolveRelativePath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", scanForDownloadablesCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", scanObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", scanXMLCB);

extern "C" SECTION(SetDefaultTextScrollTag) void SetDefaultTextScrollTag(CPage *page, SVTag *tag)
{
    if (page->m_defTextScrollTag) __SVO_Assert_Handler(svoPageSource, 0x731);
    page->m_defTextScrollTag = tag;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", setPageContextData);

extern "C" SECTION(SetPageRefreshSeconds) void SetPageRefreshSeconds(CPage *page, int seconds)
{
    page->m_pageRefreshSeconds = seconds;
    SVChronographState *timer = &page->m_pageRefreshTimer;
    if (IsStopped(timer)) {
        Reset___dupe5(timer);
        Start___dupe3(timer);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", setPageState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", shutdown);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", substituteErrorPage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", SVMLparseCB);

extern "C" SECTION(SwapDisplayBuffers) void SwapDisplayBuffers(CPage *page)
{
    if (page->m_pBackDisplayBuffer == &page->m_displayBuffers[0]) {
        page->m_pFrontDisplayBuffer = &page->m_displayBuffers[0];
        page->m_pBackDisplayBuffer = &page->m_displayBuffers[1];
    } else {
        page->m_pFrontDisplayBuffer = &page->m_displayBuffers[1];
        page->m_pBackDisplayBuffer = &page->m_displayBuffers[0];
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", XMLparseCB);
