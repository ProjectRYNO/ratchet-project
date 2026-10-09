#include "CSystemContextBase.h"
#include "stdio.h"
#include "SVPersistentData.h"
#include "SVOString.h"
#include "CInputContextBase.h"
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
extern "C" {
void FreeFrontDisplayBuffer(CPage *);
void setPageState(CPage *, int);
SVTag *GetTagAtIndex(CPage *, int);
void LeaveCurrentPage(CPage *);
void RemovePluginMgrMessages();
long SSL_Cleanup();
long GetVisible(SVTag *);
}
extern "C" {
extern char svoPageParentPath[];
extern char svoPageCurrentPath[];
void FindAndSetDefualtTextAreaScroll(CPage *);
void EnterNewPage___dupe30(CPage *);
}
extern "C" {
void SetTagAtIndex(CPage *, int, SVTag *);
int getIndexOfNextAvailEntryInTagList(CPage *);
}
extern "C" {
int substituteErrorPage(CPage *, unsigned int, char *, int);
void ResetBackDisplayBuffer(CPage *);
void SwapDisplayBuffers(CPage *);
void GenerateLagListInfo(CPage *);
void handleDefaultSelection(CPage *);
void parseCBHelper(CPage *, iks *, ParseXMLState *, int);
int iks_parse(iksparser_struct *, const char *, unsigned int, int);
unsigned long iks_nr_bytes(iksparser_struct *);
unsigned long iks_nr_lines(iksparser_struct *);
}
extern "C" {
void SignalPluginEvent(SVBrowserPrefix *, int, SVTag *);
void adjustPathBinaryDownload(CPage *, DownloadBinaryState *);
extern char svoPageErrorFormat[];
extern char svoPageXmlDeclaration[] __attribute__((aligned(8)));
extern char svoPageSvmlOpen[];
extern char svoPageErrorText1[];
extern char svoPageErrorTextStyle[];
extern char svoPageErrorText2[];
extern char svoPageErrorBackText[];
extern char svoPageSvmlClose[];
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

extern "C" SECTION(addObject) void addObject(CPage *page, iks *xml)
{
    SVTagModuleState **modules = getInstance___dupe3()->m_modules;
    for (int remaining = 128; remaining && *modules; --remaining) {
        SVTagModuleState *module = *modules++;
        if (module->vtable->IsMyTag(module, xml)) {
            SVTag *tag = 0;
            module->vtable->InitTag(module, xml, &tag, page->m_pBackDisplayBuffer->tagList, &svoPageContextData);
            if (tag) {
                int index = getIndexOfNextAvailEntryInTagList(page);
                SetTagAtIndex(page, index, tag);
            }
            return;
        }
    }
}

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

extern "C" SECTION(doAfterParseTags) void doAfterParseTags(CPage *page)
{
    SVTag **tags = page->m_pFrontDisplayBuffer->tagList;
    if (!tags) __SVO_Assert_Handler(svoPageSource, 0x933);
    for (int i = 0; i < 256; ++i) {
        SVTag *tag = *tags++;
        if (!tag) break;
        if (!page->m_defTextScrollTag && tag->m_isDefTextScroll) SetDefaultTextScrollTag(page, tag);
    }
    char *name = GetPageName(GetInstance());
    CInputContextBaseState *input = GetInputContext();
    if (!input->vtable->SetButtonMapForPage(input, name)) SetDefaultButtonMap(GetInputContext());
    FindAndSetDefualtTextAreaScroll(page);
    EnterNewPage___dupe30(page);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", doPost);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", doRequest);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", download);

extern "C" SECTION(draw) void draw(CPage *page, long active)
{
    if (page->m_bIsActive && active) {
        for (int i = 0; i < 256 && GetTagAtIndex(page, i); ++i) {
            if (GetVisible(GetTagAtIndex(page, i))) {
                SVTag *tag = GetTagAtIndex(page, i);
                tag->vtable->Draw(tag);
            }
        }
    }
}

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

extern "C" SECTION(FreeDisplayBuffers) void FreeDisplayBuffers(CPage *page) { FreeBackDisplayBuffer(page); FreeFrontDisplayBuffer(page); }

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

extern "C" SECTION(freeResources) void freeResources(CPage *page, int keepRequest)
{
    if (!keepRequest && page->m_state != 0) {
        IURISchemeProviderState *provider = page->m_pRequestProvider;
        if (provider) {
            provider->vtable->freeResources(provider, 0);
            page->m_pRequestProvider = 0;
        }
        setPageState(page, 0);
    }
    if (GetTagAtIndex(page, 0)) LeaveCurrentPage(page);
    if (page->m_XML) { iks_delete(page->m_XML); page->m_XML = 0; }
    page->m_defTextEntryTag = 0;
    page->m_defTextScrollTag = 0;
    Reset___dupe5(&page->m_pageRefreshTimer);
    Stop___dupe3(&page->m_pageRefreshTimer);
    page->m_pageRefreshSeconds = 0;
    RemovePluginMgrMessages();
}

extern "C" SECTION(GenerateLagListInfo) void GenerateLagListInfo(CPage *page)
{
    CMemoryContextBaseState *memory = GetMemoryContext();
    if (!memory) __SVO_Assert_Handler(svoPageSource, 0xAA3);
    SVTag **tags = page->m_pFrontDisplayBuffer->tagList;
    if (!tags) __SVO_Assert_Handler(svoPageSource, 0xAA5);
    int count = 0;
    while (count < 256 && tags[count]) ++count;
    SVTagInfo *info = (SVTagInfo *)svAllocSafe(memory, count * sizeof(SVTagInfo), 0, 0xAB7, svoPageSource);
    if (!info) return;
    memset(info, 0, count * sizeof(SVTagInfo));
    for (int i = 0; i < count; ++i, ++tags) {
        if (!*tags) __SVO_Assert_Handler(svoPageSource, 0xAC2);
        info[i].tag = *tags;
        info[i].tagID = (*tags)->vtable->GetTagID(*tags);
        info[i].name = (*tags)->vtable->GetTagName(*tags);
        info[i].typeName = GetTagTypeName(*tags);
        info[i].tagClass = (*tags)->m_tagClass;
    }
    SignalPluginEvent(GetInstance(), 11, 0);
    CSystemContextBase *system = GetSystemContext();
    system->vtable->HandleNewPageTagInfo(system, info, count);
    svFreeSafe(memory, info);
}

extern "C" SECTION(getIndexOfNextAvailEntryInTagList) int getIndexOfNextAvailEntryInTagList(CPage *page)
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

extern "C" SECTION(handleDefaultSelection) void handleDefaultSelection(CPage *page)
{
    SVTag *first = 0;
    bool selected = false;
    SVTag *tag;
    for (int i = 0; i < 256 && (tag = GetTagAtIndex(page, i)); ++i) {
        if (tag->vtable->IsSelected(tag)) { selected = true; continue; }
        tag = GetTagAtIndex(page, i);
        if (tag->vtable->IsSelectable(tag) && !first) { first = GetTagAtIndex(page, i); continue; }
        if (selected) {
            tag = GetTagAtIndex(page, i);
            if (tag->vtable->IsSelected(tag)) __SVO_Assert_Handler(svoPageSource, 0x488);
        }
    }
    if (first && !selected) first->vtable->SetSelectedState(first, 1);
}

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
    SVTag *tag;
    for (int i = 0; i < 256 && (tag = GetTagAtIndex(page, i)); ++i) {
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

extern "C" SECTION(LoadStatePostGameFromPersistentData) long LoadStatePostGameFromPersistentData(CPage *page, SVPersistentData *persist)
{
    LoadStatePostGameFromPersistentData___dupe4(Get(), persist);
    for (int i = 0; i < 128; ++i) page->m_serverName[i] = persist->serverName[i];
    page->m_port = persist->port;
    return 1;
}

extern "C" SECTION(operator.delete___dupe2) void CPageoperator_delete___dupe2(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", operator.new___dupe3);

extern "C" SECTION(parseCBHelper) void parseCBHelper(CPage *page, iks *xml, ParseXMLState *parser, int depth)
{
    for (iks *child = iks_child(xml); child; child = iks_next(child)) {
        int type = iks_type(child);
        if (type == 1) ((const ParseXMLVtablePrefix *)parser->vtable)->CallFunction(parser, child, page);
        else if (!type) __SVO_Assert_Handler(svoPageSource, 0x45B);
        else if (type != 2 && type != 3) __SVO_Assert_Handler(svoPageSource, 0x465);
        // Retail increments this local across siblings as well as recursion.
        if (iks_has_children(child)) parseCBHelper(page, child, parser, ++depth);
    }
}

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

extern "C" SECTION(PopInTransitArray) void PopInTransitArray(CPage *page, DownloadBinaryState *out)
{
    for (int i = 0; i < 2; ++i) if (page->inTransitionUsed[i]) {
        const void *vtable = out->vtable;
        *out = page->inTransition[i];
        out->vtable = vtable;
        memset(&page->inTransition[i], 0, sizeof(DownloadBinaryState));
        page->inTransitionUsed[i] = 0;
        --page->inTransitionCount;
        return;
    }
}

extern "C" SECTION(PushPostTransitionArray) void PushPostTransitionArray(CPage *page, DownloadBinaryState *item, DownloadBinaryState **out)
{
    for (int i = 0; i < 11; ++i) if (!page->postTransitionUsed[i]) {
        DownloadBinaryState *dest = &page->postTransition[i];
        const void *vtable = dest->vtable;
        *dest = *item;
        *out = dest;
        dest->vtable = vtable;
        page->postTransitionUsed[i] = 1;
        ++page->postTransitionCount;
        return;
    }
}

extern "C" SECTION(ReAllocBackDisplayBufferParser) void ReAllocBackDisplayBufferParser(CPage *page)
{
    if (page->m_pBackDisplayBuffer->parser) __SVO_Assert_Handler(svoPageSource, 0xA4E);
    iksparser_struct *parser = iks_dom_new(&page->m_pBackDisplayBuffer->xml);
    page->m_pBackDisplayBuffer->parser = parser;
    if (!parser) __SVO_Assert_Handler(svoPageSource, 0xA52);
    iks_parser_reset(page->m_pBackDisplayBuffer->parser);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPage", requestBinary);

extern "C" SECTION(ResetBackDisplayBuffer) void ResetBackDisplayBuffer(CPage *page)
{
    FreeBackDisplayBuffer(page);
    ReAllocBackDisplayBufferParser(page);
}

extern "C" SECTION(resolveRelativePath) long resolveRelativePath(CPage *page, char *current, char *relative)
{
    if (!*current || !relative) __SVO_Assert_Handler(svoPageSource, 0x291);
    int parents = 0;
    for (;;) {
        while (!strncmp(svoPageParentPath, relative, 3)) { relative += 3; ++parents; }
        if (strncmp(svoPageCurrentPath, relative, 2)) break;
        relative += 2;
    }
    while (parents > 0) {
        char *slash = strrchr(current, '/');
        if (!slash) __SVO_Assert_Handler(svoPageSource, 0x2AB);
        --parents;
        *slash = '-';
    }
    char *tail = strrchr(current, '/') + 1;
    svstrncpy(tail, relative, 0x101 - (tail - current));
    return 1;
}

extern "C" SECTION(scanForDownloadablesCB) void scanForDownloadablesCB(unsigned int status, char *buffer, int size, CPage *page, int swap)
{
    if (!page) __SVO_Assert_Handler(svoPageSource, 0x3b8);
    ParseXMLState parser;
    ParseSVMLForDownloads(&parser);
    SVMLparseCB(page, status, buffer, size, &parser, swap);
    _ParseSVMLForDownloads(&parser, 2);
}

extern "C" SECTION(scanObject) void scanObject(CPage *page, iks *xml)
{
    SVTagModuleState **modules = getInstance___dupe3()->m_modules;
    for (int i = 0; i < 128 && modules[i]; ++i) {
        SVTagModuleState *module = modules[i];
        if (!module->vtable->IsMyTag(module, xml)) continue;
        SVTagScanResult results[2];
        for (int j = 0; j < 2; ++j) { results[j].action = 0; results[j].download = 0; }
        svoPageContextData.pMain = page;
        module->vtable->ScanTag(module, xml, page->m_pFrontDisplayBuffer->tagList, &svoPageContextData, results);
        for (int j = 0; j < 2; ++j) {
            switch (results[j].action) {
            case 0: break;
            case 1:
            case 2: adjustPathBinaryDownload(page, results[j].download); break;
            case 3: setPageState(page, 1); break;
            default: __SVO_Assert_Handler(svoPageSource, 0x84E); break;
            }
        }
        return;
    }
}

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

extern "C" SECTION(shutdown) long shutdown(CPage *page)
{
    freeResources(page, 0);
    FreeDisplayBuffers(page);
    if (page->m_parser) { iks_parser_delete(page->m_parser); page->m_parser = 0; }
    IURISchemeProviderState *provider = page->m_pRequestProvider;
    if (provider) { provider->vtable->freeResources(provider, 0); page->m_pRequestProvider = 0; }
    return SSL_Cleanup();
}

extern "C" SECTION(substituteErrorPage) int substituteErrorPage(CPage *page, unsigned int status, char *buffer, int length)
{
    char message[128];
    char xml[512] __attribute__((aligned(8)));
    sprintf(message, svoPageErrorFormat, status, length);
    memcpy(xml, svoPageXmlDeclaration, 22);
    strcat(xml, svoPageSvmlOpen);
    strcat(xml, svoPageErrorText1);
    strcat(xml, svoPageErrorTextStyle);
    strcat(xml, message);
    strcat(xml, svoPageErrorText2);
    strcat(xml, svoPageErrorTextStyle);
    strcat(xml, svoPageErrorBackText);
    strcat(xml, svoPageSvmlClose);
    if (strlen(xml) > 511) __SVO_Assert_Handler(svoPageSource, 0x5BA);
    strcpy(buffer, xml);
    return strlen(buffer);
}

extern "C" SECTION(SVMLparseCB) void SVMLparseCB(CPage *page, unsigned int status, char *buffer, int length, ParseXMLState *parser, int swap)
{
    if (!buffer) __SVO_Assert_Handler(svoPageSource, 0x3DF);
    const ParseXMLVtablePrefix *vtable = (const ParseXMLVtablePrefix *)parser->vtable;
    if (vtable->ShouldFreeResources(parser)) freeResources(page, 1);
    page->m_bIsActive = 1;
    if (status != 200 && page->m_lastCURIContentType != 1)
        length = substituteErrorPage(page, status, buffer, length);
    ResetBackDisplayBuffer(page);
    if (iks_parse(page->m_pBackDisplayBuffer->parser, buffer, length, 1)) {
        iks_nr_bytes(page->m_pBackDisplayBuffer->parser);
        iks_nr_lines(page->m_pBackDisplayBuffer->parser);
        __SVO_Assert_Handler(svoPageSource, 0x3FD);
        return;
    }
    char *name = iks_name(page->m_pBackDisplayBuffer->xml);
    if (!name || strcmp(((const ParseXMLVtablePrefix *)parser->vtable)->GetCheckString(parser), name)) {
        __SVO_Assert_Handler(svoPageSource, 0x406);
        return;
    }
    parseCBHelper(page, page->m_pBackDisplayBuffer->xml, parser, 0);
    if (swap) { SwapDisplayBuffers(page); GenerateLagListInfo(page); }
    handleDefaultSelection(page);
}

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

extern "C" SECTION(XMLparseCB) void XMLparseCB(CPage *page, unsigned int status, char *buffer, int length, ParseXMLState *parser)
{
    if (!buffer) __SVO_Assert_Handler(svoPageSource, 0x423);
    if (page->m_XML) { iks_delete(page->m_XML); page->m_XML = 0; }
    if (status != 200 && page->m_lastCURIContentType != 2)
        length = substituteErrorPage(page, status, buffer, length);
    iks_parser_reset(page->m_parser);
    if (iks_parse(page->m_parser, buffer, length, 1)) {
        iks_nr_bytes(page->m_parser);
        iks_nr_lines(page->m_parser);
        __SVO_Assert_Handler(svoPageSource, 0x441);
        return;
    }
    char *name = iks_name(page->m_XML);
    if (!name || strcmp(((const ParseXMLVtablePrefix *)parser->vtable)->GetCheckString(parser), name)) {
        __SVO_Assert_Handler(svoPageSource, 0x44A);
        return;
    }
    parseCBHelper(page, page->m_XML, parser, 0);
}
