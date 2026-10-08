#include "CError.h"
#include "URISchemeMgr.h"
#include "ParseXML.h"
#include "string.h"
#include "SVBrowser.h"
#include "CMemoryContextBase.h"
#include "SVTagModule.h"
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

extern char svoPageSource[];
long DefaultHandleInput(SVTag *tag, CPage *page);
void FreeBackDisplayBuffer(CPage *page);
void ReAllocBackDisplayBufferParser(CPage *page);

extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoPageSource[];
void * CPageoperator_new___dupe3(unsigned int size) __asm__("operator.new___dupe3");

}
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
void CPageoperator_delete___dupe2(void *memory) __asm__("operator.delete___dupe2");

}
extern "C" {
iksparser_struct *iks_dom_new(iks **);
void iks_parser_reset(iksparser_struct *);
void FreeDisplayBuffers(CPage *);
void freeResources(CPage *, int);
char *GetPageName(SVBrowserPrefix *);
char *GetSelectedTagName(CPage *);
extern char svoTournamentHomeName[];
extern char *svoTournamentSelectedTagName;
extern CAllContextData svoPageContextData;
CAudioContextBaseState *GetAudioContext();
CAudioContextBaseState *GetAltAudioContext();
CDrawContextBase *GetDrawContext();
CDrawContextBase *GetAltDrawContext();
CMemoryContextBaseState *GetMemoryContext();
CMemoryContextBaseState *GetAltMemoryContext();
CSystemContextBase *GetSystemContext();
CSystemContextBase *GetAltSystemContext();
CInputContextBaseState *GetInputContext();
CInputContextBaseState *GetAltInputContext();

}
extern "C" {
void SVMLparseCB(CPage *, unsigned int, char *, int, ParseXMLState *, int);
void XMLparseCB(CPage *, unsigned int, char *, int, ParseXMLState *);
void iks_delete(iks *);
void iks_parser_delete(iksparser_struct *);
char *GetTagTypeName(SVTag *);
void SetDefaultTextScrollTag(CPage *, SVTag *);
extern char svoPageSchemeSeparator[];
extern char svoPageStaticScheme[];
extern char svoPageTextAreaTagName[];
const void *ParseSVMLAddObjects(ParseXMLState *);
void _ParseSVMLAddObjects(ParseXMLState *, int);
const void *ParseSVMLForDownloads(ParseXMLState *);
void _ParseSVMLForDownloads(ParseXMLState *, int);
const void *ParseXMLInfo(ParseXMLState *);
void _ParseXMLInfo(ParseXMLState *, int);

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

extern "C" SECTION(ClosePopup) long ClosePopup(CPage *page)
{
    if (page != GetInstance()->m_pPopupPage) __SVO_Assert_Handler(svoPageSource, 0x9AB);
    page->m_bIsActive = 0;
    clear(&page->m_history);
    FreeDisplayBuffers(page);
    freeResources(page, 0);
    return 1;
}

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

extern "C" SECTION(FindAndSetDefualtTextAreaScroll) void FindAndSetDefualtTextAreaScroll(CPage *page)
{
    SVTag **tags = page->m_pFrontDisplayBuffer->tagList;
    int found = -1;
    for (int i = 0; i < 256 && tags[i]; ++i) {
        if (!strcmp(svoPageTextAreaTagName, GetTagTypeName(tags[i]))) {
            if (found != -1) return;
            found = i;
        }
    }
    if (found != -1) {
        tags[found]->m_isDefTextScroll = 1;
        SetDefaultTextScrollTag(page, tags[found]);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", followLink);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", frameUpdate);

extern "C" SECTION(FreeBackDisplayBuffer) void FreeBackDisplayBuffer(CPage *page)
{
    for (int i = 0; i < 256 && page->m_pBackDisplayBuffer->tagList[i]; ++i) {
        SVTag *tag = page->m_pBackDisplayBuffer->tagList[i];
        tag->vtable->destroy(tag, 3);
        page->m_pBackDisplayBuffer->tagList[i] = 0;
    }
    if (page->m_pBackDisplayBuffer->xml) {
        iks_delete(page->m_pBackDisplayBuffer->xml);
        page->m_pBackDisplayBuffer->xml = 0;
    }
    if (page->m_pBackDisplayBuffer->parser) {
        iks_parser_delete(page->m_pBackDisplayBuffer->parser);
        page->m_pBackDisplayBuffer->parser = 0;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", FreeDisplayBuffers);

extern "C" SECTION(FreeFrontDisplayBuffer) void FreeFrontDisplayBuffer(CPage *page)
{
    for (int i = 0; i < 256 && page->m_pFrontDisplayBuffer->tagList[i]; ++i) {
        SVTag *tag = page->m_pFrontDisplayBuffer->tagList[i];
        tag->vtable->destroy(tag, 3);
        page->m_pFrontDisplayBuffer->tagList[i] = 0;
    }
    if (page->m_pFrontDisplayBuffer->xml) {
        iks_delete(page->m_pFrontDisplayBuffer->xml);
        page->m_pFrontDisplayBuffer->xml = 0;
    }
    if (page->m_pFrontDisplayBuffer->parser) {
        iks_parser_delete(page->m_pFrontDisplayBuffer->parser);
        page->m_pFrontDisplayBuffer->parser = 0;
    }
}

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

extern "C" SECTION(LeaveCurrentPage) void LeaveCurrentPage(CPage *page)
{
    SVTagModuleState **entry = getInstance___dupe3()->m_modules + 1;
    while (*entry) {
        SVTagModuleState *module = *entry++;
        module->vtable->LeaveCurrentPage(module);
    }
    char *name = GetPageName(GetInstance());
    if (name && strcmp(name, svoTournamentHomeName) == 0)
        svoTournamentSelectedTagName = GetSelectedTagName(page);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", LoadStatePostGameFromPersistentData);

extern "C" SECTION(operator.delete___dupe2) void CPageoperator_delete___dupe2(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", operator.new___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", parseCBHelper);

extern "C" SECTION(parseTagsCB) void parseTagsCB(unsigned int status, char *buffer, int size, CPage *page, int swap)
{
    if (!page) __SVO_Assert_Handler(svoPageSource, 0x3ab);
    ParseXMLState parser;
    ParseSVMLAddObjects(&parser);
    SVMLparseCB(page, status, buffer, size, &parser, swap);
    _ParseSVMLAddObjects(&parser, 2);
}

extern "C" SECTION(pathIsFullyQualified) long pathIsFullyQualified(CPage *page, char *path)
{
    char *colon = strstr(path, svoPageSchemeSeparator);
    if (!colon) return 0;
    int length = colon - path;
    if (length > 14) __SVO_Assert_Handler(svoPageSource, 0x74d);
    char scheme[15];
    memcpy(scheme, path, 15);
    scheme[length] = 0;
    long result = HasProvider(Get(), scheme);
    if (!result) SetErrorCode(32);
    return result;
}

extern "C" SECTION(pathIsStatic) long pathIsStatic(CPage *page, char *path)
{
    char *colon = strstr(path, svoPageSchemeSeparator);
    if (!colon) return 0;
    int length = colon - path;
    if (length > 14) __SVO_Assert_Handler(svoPageSource, 0x777);
    char scheme[15];
    memcpy(scheme, path, 15);
    scheme[length] = 0;
    return strcmp(scheme, svoPageStaticScheme) == 0;
}

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

extern "C" SECTION(scanForDownloadablesCB) void scanForDownloadablesCB(unsigned int status, char *buffer, int size, CPage *page, int swap)
{
    if (!page) __SVO_Assert_Handler(svoPageSource, 0x3b8);
    ParseXMLState parser;
    ParseSVMLForDownloads(&parser);
    SVMLparseCB(page, status, buffer, size, &parser, swap);
    _ParseSVMLForDownloads(&parser, 2);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", scanObject);

extern "C" SECTION(scanXMLCB) void scanXMLCB(unsigned int status, char *buffer, int size, CPage *page, int swap)
{
    if (!page) __SVO_Assert_Handler(svoPageSource, 0x3cb);
    ParseXMLState parser;
    ParseXMLInfo(&parser);
    XMLparseCB(page, status, buffer, size, &parser);
    _ParseXMLInfo(&parser, 2);
}

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
