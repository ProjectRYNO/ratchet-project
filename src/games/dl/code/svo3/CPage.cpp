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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", addToHistory);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", adjustPathBinaryDownload);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", autoRefreshPage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", callGenericDownloadCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", ClosePopup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", CPage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", DestroyInTransitionArray);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", DestroyPostTransitionArray);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", DestroyPreTransitionArray);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", doAfterParseTags);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", doPost);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", doRequest);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", download);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", draw);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", EnterNewPage___dupe30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", FindAndSetDefualtTextAreaScroll);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", followLink);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", frameUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", FreeBackDisplayBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", FreeDisplayBuffers);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", FreeFrontDisplayBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", freeResources);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", GenerateLagListInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", getIndexOfNextAvailEntryInTagList);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", GetSelectedTagName);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", getTopOfHistory);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", handleDefaultSelection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", handleInput);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", handleTextEntryDefaultInput);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", handleTextScrollDefaultInput);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", handleUpdate);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", ResetBackDisplayBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", resolveRelativePath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", scanForDownloadablesCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", scanObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", scanXMLCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", SetDefaultTextScrollTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", setPageContextData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", SetPageRefreshSeconds);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", setPageState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", shutdown);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", substituteErrorPage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", SVMLparseCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", SwapDisplayBuffers);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", XMLparseCB);
