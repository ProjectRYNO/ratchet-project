#include "CPage.h"
#include "CError.h"
#include "CHttp.h"
#include "HttpUtils.h"
#include "CSystemContextBase.h"
#include "SVOString.h"
#include "string.h"

extern "C" {
extern char svoPageSource[];

extern char svoPageDownloadHostSeparator[];
extern char svoPageDownloadPathSeparator[];
long pathIsStatic(CPage *, char *);
long pathIsFullyQualified(CPage *, char *);
long resolveRelativePath(CPage *, char *, char *);
void setPageState(CPage *, int);
void scanForDownloadablesCB(unsigned int, char *, int, CPage *, int);
void scanXMLCB(unsigned int, char *, int, CPage *, int);
void parseTagsCB(unsigned int, char *, int, CPage *, int);
}

#include "CPage.h"
#include "SVBrowser.h"
#include "CError.h"
#include "string.h"

extern "C" {
extern char svoPageSource[];
void rt_comm_update();
CMemoryContextBaseState *GetMemoryContext();
void setPageState(CPage *, int);
void freeResources(CPage *, int);
SVTag *GetTagAtIndex(CPage *, int);
int requestBinary(CPage *, int);
int callGenericDownloadCallback(CPage *, char **, int *);
int GetResponse(PageRequestListenerState *, char **, int *);
int GetLastStatus(PageRequestListenerState *);
int GetLastContentType(PageRequestListenerState *);
int substituteErrorPage(CPage *, unsigned int, char *, int);
const void *DownloadBinary(DownloadBinaryState *);
void _DownloadBinary(DownloadBinaryState *, int);
void Reset___dupe6(PageRequestListenerState *);
}




#include "CPage.h"
#include "SVTag.h"
#include "CQueryParams.h"
#include "SVBrowser.h"
#include "CMemoryContextBase.h"
#include "SVTagModule.h"
#include "SVOString.h"
#include "string.h"
#include "stdio.h"
extern "C" {
extern char svoPageSource[];
extern CAllContextData svoPageContextData;
extern char svoPageDownloadHostSeparator[];
extern char svoPageDownloadPathSeparator[];
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
char *GetPath(DownloadBinaryState *);
void SetPath(DownloadBinaryState *, char *);
long pathIsFullyQualified(CPage *, char *);
long resolveRelativePath(CPage *, char *, char *);
}

extern "C" {
extern char svoPageStateError[];
extern char svoPageStateIdle[];
extern char svoPageStateDlPage[];
extern char svoPageStateCreatePage[];
extern char svoPageStateAniOut[];
extern char svoPageStateAniIn[];
extern char svoPageStateSubmit[];
extern char svoPageStateSubmitFail[];
extern char svoPageStateDlObjWhileAniIn[];
extern char svoPageStateDlObjThenAniIn[];
extern char svoPageStateDlObjThenAniOut[];
extern char svoPageStateDlObj[];
extern char svoPageStateShuttingDown[];
extern char svoPageStateTransition[];
}

#include "CDrawContextBase.h"

extern "C" {
void Reset___dupe6(PageRequestListenerState *);
void doAfterParseTags(CPage *);
int requestBinary(CPage *, int);
}

extern "C" {
const void *DownloadBinary(DownloadBinaryState *);
void PageRequestListener(PageRequestListenerState *, CMemoryContextBaseState *, unsigned int);
long doRequest(CPage *, char *, CQueryParamListState *, int, long, char *);
extern char svoPageGetCommand[];
iksparser_struct *iks_dom_new(iks **);
}
extern "C" void CPageConstruct(CPage *page, char *firstPage, int popup, int listenPort) __asm__("CPage");


extern "C" {
long shutdown(CPage *);
void _PageRequestListener(PageRequestListenerState *, int);
void PageDelete(void *) __asm__("operator.delete___dupe2");
}

extern "C" {
char *getTopOfHistory(CPage *);
long ClosePopup(CPage *);
long okToNavigate___dupe2(CPage *);
SVTag *GetTagAtIndex(CPage *, int);
void HandleInputForPluginEvents(SVTag *);
char *GetPageName(SVBrowserPrefix *);
long autoRefreshPage(CPage *);
long handleTextEntryDefaultInput(CPage *);
long handleTextScrollDefaultInput(CPage *);
extern char svoPageHomePageID[];
}




extern "C" { void setPageContextData(CPage *); void setPageState(CPage *, int); }

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

extern "C" SECTION(_CPage) void _CPage(CPage *page, unsigned int flags)
{
    shutdown(page);
    _PageRequestListener(&page->m_requestListener, 2);
    _SVChronograph(&page->m_pageRefreshTimer, 2);
    DownloadBinaryState *begin = page->inTransition;
    if ((unsigned int)begin) {
        DownloadBinaryState *item = begin + 2;
        do {
            --item;
            ((const PageDownloadVtable *)item->vtable)->destroy(item, 2);
        } while (item != begin);
    }
    begin = page->postTransition;
    if ((unsigned int)begin) {
        DownloadBinaryState *item = begin + 11;
        do {
            --item;
            ((const PageDownloadVtable *)item->vtable)->destroy(item, 2);
        } while (item != begin);
    }
    begin = page->preTransition;
    if ((unsigned int)begin) {
        DownloadBinaryState *item = begin + 11;
        do {
            --item;
            ((const PageDownloadVtable *)item->vtable)->destroy(item, 2);
        } while (item != begin);
    }
    if (flags & 1) PageDelete(page);
}

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

extern "C" SECTION(adjustPathBinaryDownload) void adjustPathBinaryDownload(CPage *page, DownloadBinaryState *download)
{
    char path[272];
    char resolved[272];
    if (!download) __SVO_Assert_Handler(svoPageSource, 0x78C);
    char *source = GetPath(download);
    int length = strlen(GetPath(download));
    svstrncpy(path, source, length + 1);
    if (!pathIsFullyQualified(page, path)) {
        if (path[0] == '/') {
            memset(resolved, 0, 257);
            strncpy(resolved, top(&page->m_history), 257);
            char *replace = strstr(resolved, svoPageDownloadHostSeparator);
            replace = strstr(replace + 2, svoPageDownloadPathSeparator);
            if (!replace) __SVO_Assert_Handler(svoPageSource, 0x7AD);
            strncpy(replace, path, strlen(path));
        } else {
            memset(resolved, 0, 257);
            strncpy(resolved, top(&page->m_history), 257);
            if (!resolveRelativePath(page, resolved, path)) {
                __SVO_Assert_Handler(svoPageSource, 0x7A1);
                return;
            }
        }
    } else strncpy(resolved, path, 257);
    if (page->m_state != 1) __SVO_Assert_Handler(svoPageSource, 0x7B3);
    SetPath(download, resolved);
}

extern "C" SECTION(autoRefreshPage) long autoRefreshPage(CPage *page)
{
    SVChronographState *timer = &page->m_pageRefreshTimer;
    if (!IsRunning(timer) || Elapsed(timer) < page->m_pageRefreshSeconds) return 0;
    Reset___dupe5(timer);
    return 1;
}

extern "C" SECTION(callGenericDownloadCallback) int callGenericDownloadCallback(CPage *page, char **data, int *length)
{
    if (!GetResponse(&page->m_requestListener, data, length)) {
        SetErrorCode(0x1D);
        return 0;
    }
    page->m_lastHttpStatus = GetLastStatus(&page->m_requestListener);
    int type = GetLastContentType(&page->m_requestListener);
    page->m_lastCURIContentType = type;
    if (type == 3) {
        int state = page->m_state;
        if (state == 1) {
            int size = substituteErrorPage(page, page->m_lastHttpStatus, *data, *length);
            page->m_lastCURIContentType = 1;
            *length = size;
            goto scanSVML;
        }
        if ((unsigned int)(state - 8) < 3 || state == 6) {
            DownloadBinaryState item;
            DownloadBinary(&item);
            for (int i = 0; i < 2; ++i) {
                if (page->inTransitionUsed[i]) {
                    const void *vtable = item.vtable;
                    item = page->inTransition[i];
                    item.vtable = vtable;
                    memset(&page->inTransition[i], 0, sizeof(item));
                    page->inTransitionUsed[i] = 0;
                    --page->inTransitionCount;
                    break;
                }
            }
            _DownloadBinary(&item, 2);
        }
    } else if (type == 1) {
scanSVML:
        if (!page->m_pfSVMLPreTagCreateScanCB) __SVO_Assert_Handler(svoPageSource, 0x88A);
        page->m_pfSVMLPreTagCreateScanCB(page->m_lastHttpStatus, *data, *length, page, 0);
        setPageState(page, 2);
    } else if (type == 2) {
        if (!page->m_pfXMLScanCB) __SVO_Assert_Handler(svoPageSource, 0x8A3);
        page->m_pfXMLScanCB(page->m_lastHttpStatus, *data, *length, page, 0);
        Reset___dupe6(&page->m_requestListener);
        setPageState(page, 0);
    } else if (type == 4 || type == 5) {
        if (!page->m_pfBinaryDownloadCB) __SVO_Assert_Handler(svoPageSource, 0x8BA);
        page->m_pfBinaryDownloadCB(page->m_lastHttpStatus, *data, *length, page, 0);
    } else if (type == 8) __SVO_Assert_Handler(svoPageSource, 0x8C5);
    else if (type == -1) __SVO_Assert_Handler(svoPageSource, 0x8C9);
    else if (type != 0) __SVO_Assert_Handler(svoPageSource, 0x8CD);
    if (!page->m_pRequestProvider) __SVO_Assert_Handler(svoPageSource, 0x8D2);
    IURISchemeProviderState *provider = page->m_pRequestProvider;
    if (provider) {
        provider->vtable->freeResources(provider, 0);
        page->m_pRequestProvider = 0;
    }
    return page->m_lastCURIContentType;
}

extern "C" SECTION(ClosePopup) long ClosePopup(CPage *page)
{
    if (page != GetInstance()->m_pPopupPage) __SVO_Assert_Handler(svoPageSource, 0x9AB);
    page->m_bIsActive = 0;
    clear(&page->m_history);
    FreeDisplayBuffers(page);
    freeResources(page, 0);
    return 1;
}

extern "C" SECTION(CPage) void CPageConstruct(CPage *page, char *firstPage, int popup, int listenPort)
{
    for (int i = 0; i < 11; ++i) DownloadBinary(&page->preTransition[i]);
    for (int i = 0; i < 11; ++i) DownloadBinary(&page->postTransition[i]);
    for (int i = 0; i < 2; ++i) DownloadBinary(&page->inTransition[i]);
    PageHistory(&page->m_history);
    SVChronograph(&page->m_pageRefreshTimer, 0);
    PageRequestListener(&page->m_requestListener, GetMemoryContext(), 0xA000);
    page->m_pRequestProvider = 0;
    page->m_bIsPopup = popup;
    setPageContextData(page);
    page->m_state = 0;
    setPageState(page, 0);
    page->m_bIsActive = 0;
    page->m_pFrontDisplayBuffer = &page->m_displayBuffers[1];
    page->m_pBackDisplayBuffer = &page->m_displayBuffers[0];
    memset(page->m_displayBuffers[0].tagList, 0, 0x400);
    memset(page->m_pFrontDisplayBuffer->tagList, 0, 0x400);
    SVDisplayBufferState *front = page->m_pFrontDisplayBuffer;
    page->m_pBackDisplayBuffer->xml = 0;
    page->m_defTextEntryTag = 0;
    front->xml = 0;
    page->m_defTextScrollTag = 0;
    iksparser_struct *parser = iks_dom_new(&page->m_pBackDisplayBuffer->xml);
    page->m_pBackDisplayBuffer->parser = parser;
    if (!parser) __SVO_Assert_Handler(svoPageSource, 0xCD);
    parser = iks_dom_new(&page->m_pFrontDisplayBuffer->xml);
    page->m_pFrontDisplayBuffer->parser = parser;
    if (!parser) __SVO_Assert_Handler(svoPageSource, 0xD1);
    parser = iks_dom_new(&page->m_XML);
    page->m_parser = parser;
    if (!parser) __SVO_Assert_Handler(svoPageSource, 0xD5);
    page->preTransitionCount = 0;
    memset(page->preTransitionUsed, 0, 32);
    page->postTransitionCount = 0;
    memset(page->postTransitionUsed, 0, 32);
    page->inTransitionCount = 0;
    memset(page->inTransitionUsed, 0, 32);
    if (!firstPage || doRequest(page, firstPage, 0, 0, 1, svoPageGetCommand)) {
        Reset___dupe5(&page->m_pageRefreshTimer);
        page->m_pageRefreshSeconds = 0;
    }
}

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

extern "C" SECTION(doRequest) long doRequest(CPage *page, char *path, CQueryParamListState *params, int method, long storeHistory, char *command)
{
    char newPath[272];
    char oldPath[272];
    char fullPath[272];
    char *historyPath = newPath;
    if (!path) __SVO_Assert_Handler(svoPageSource, 0x327);
    svstrncpy(oldPath, path, 257);
    if (pathIsStatic(page, path)) {
        char *screen = strstr(path, svoPageDownloadHostSeparator) + 2;
        CSystemContextBase *system = GetSystemContext();
        ((const PageStaticScreenVtable *)system->vtable)->EnterStaticScreen(system, screen);
        return 1;
    }
    if (pathIsFullyQualified(page, path)) {
        SVPath split;
        split.m_scheme = page->m_scheme;
        split.m_server = page->m_serverName;
        split.m_port = &page->m_port;
        split.m_path = newPath;
        split.m_pathMaxLength = 257;
        parseFullyQualifiedPath(path, &split);
        historyPath = path;
    } else if (*path == '/') {
        memset(newPath, 0, 257);
        char *base = top(&page->m_history);
        if (!base) base = page->m_serverName;
        strncpy(newPath, base, 257);
        char *replace = strstr(newPath, svoPageDownloadHostSeparator);
        replace = strstr(replace + 2, svoPageDownloadPathSeparator);
        if (!replace) __SVO_Assert_Handler(svoPageSource, 0x372);
        strncpy(replace, oldPath, strlen(oldPath) + 1);
        if (strlen(newPath) >= 257) __SVO_Assert_Handler(svoPageSource, 0x375);
    } else {
        memset(fullPath, 0, 257);
        svstrncpy(fullPath, top(&page->m_history), 257);
        if (!resolveRelativePath(page, fullPath, oldPath)) {
            __SVO_Assert_Handler(svoPageSource, 0x34B);
            return 0;
        }
        SVPath split;
        split.m_scheme = page->m_scheme;
        split.m_server = page->m_serverName;
        split.m_port = &page->m_port;
        split.m_path = newPath;
        split.m_pathMaxLength = 257;
        parseFullyQualifiedPath(fullPath, &split);
        historyPath = fullPath;
    }
    if (page->m_state) __SVO_Assert_Handler(svoPageSource, 0x37E);
    URIRequest request;
    request.scheme = page->m_scheme;
    request.host = page->m_serverName;
    request.port = page->m_port;
    request.filePath = newPath;
    request.params = params;
    request.methodType = method;
    request.httpCommand = command;
    request.context = 0;
    if (page->m_pRequestProvider) __SVO_Assert_Handler(svoPageSource, 0x38B);
    IURISchemeProviderState *provider = doRequest___dupe3(Get(), (URIRequestPrefix *)&request, (IRequestListener *)&page->m_requestListener, page);
    page->m_pRequestProvider = provider;
    if (!provider) return 0;
    if (storeHistory) push(&page->m_history, historyPath);
    page->m_pfSVMLPreTagCreateScanCB = (DownloadCallback)scanForDownloadablesCB;
    page->m_pfXMLScanCB = (DownloadCallback)scanXMLCB;
    page->m_pfSVMLTagCreateCB = (DownloadCallback)parseTagsCB;
    page->m_pfBinaryDownloadCB = 0;
    page->m_pCURIContent = 0;
    page->m_iCURIContentLength = 0;
    page->m_lastCURIContentType = 0;
    setPageState(page, 1);
    return 1;
}

extern "C" SECTION(download) int download(CPage *page)
{
    rt_comm_update();
    int state = page->m_state;
    if (GetErrorCode()) {
        setPageState(page, -1);
        return -1;
    }
    EnsureCleanBlocks(GetMemoryContext());
    IURISchemeProviderState *provider = page->m_pRequestProvider;
    if (provider) ((const PageProviderDownloadVtable *)provider->vtable)->download(provider);
    EnsureCleanBlocks(GetMemoryContext());
    if (state == 1) {
        freeResources(page, 1);
        if (!page->m_pRequestProvider) __SVO_Assert_Handler(svoPageSource, 0x169);
        provider = page->m_pRequestProvider;
        if (!provider->vtable->IsBusy(provider)) {
            callGenericDownloadCallback(page, &page->m_pCURIContent, &page->m_iCURIContentLength);
            if (GetTagAtIndex(page, 0)) {
                if (!page->inTransitionCount && page->preTransitionCount && requestBinary(page, 1) != 1) setPageState(page, 9);
            } else if (!page->inTransitionCount && page->preTransitionCount) {
                if (requestBinary(page, 1) != 1) setPageState(page, 8);
            } else if (!page->m_pCURIContent) setPageState(page, 0);
        }
    } else if (state == 6 || state == 8 || state == 9 || state == 10) {
        provider = page->m_pRequestProvider;
        if (!provider->vtable->IsBusy(provider)) {
            char *data;
            int length;
            callGenericDownloadCallback(page, &data, &length);
            int queue = -1;
            if (state == 6) {
                if (page->inTransitionCount || !page->postTransitionCount) setPageState(page, 3);
                else queue = 2;
            } else if (state == 8) {
                if (state == page->m_state && (page->inTransitionCount || !page->preTransitionCount)) setPageState(page, 11);
                else queue = 1;
            } else if (state == 9) {
                if (page->inTransitionCount || !page->preTransitionCount) setPageState(page, 2);
                else queue = 1;
            } else {
                if (!page->inTransitionCount && page->postTransitionCount) queue = 2;
                else setPageState(page, 0);
            }
            if (queue != -1 && requestBinary(page, queue) == 1) setPageState(page, 1);
        }
    } else if (state != -1 && state != 0 && state != 2 && state != 3 && state != 4 && state != 11 && state != 12) __SVO_Assert_Handler(svoPageSource, 0x212);
    if (GetErrorCode()) setPageState(page, -1);
    return page->m_state;
}

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

extern "C" SECTION(followLink) long followLink(CPage *page, char *filePath, int option)
{
    char path[257];
    if (!filePath) __SVO_Assert_Handler(svoPageSource, 0x2BF);
    memset(path, 0, sizeof(path));
    long history = 1;
    CPage *target = page;
    char *requestPath = filePath;
    if (option == 2) {
        if (!pathIsFullyQualified(page, filePath)) {
            svstrncpy(path, getTopOfHistory(GetInstance()->m_pMainPage), 257);
            resolveRelativePath(page, path, filePath);
            requestPath = path;
        }
        target = GetInstance()->m_pPopupPage;
        target->m_bIsActive = 1;
    } else if (option == 3) target = GetInstance()->m_pPopupPage;
    else if (option == 4) {
        ClosePopup(page);
        return 1;
    } else if (option == 5) {
        svstrncpy(path, top(&GetInstance()->m_pMainPage->m_history), 257);
        requestPath = path;
        goto closeAndLoadMain;
    } else if (option == 6) {
        svstrncpy(path, top(&GetInstance()->m_pPopupPage->m_history), 257);
        if (!pathIsFullyQualified(page, filePath)) {
            resolveRelativePath(page, path, filePath);
            requestPath = path;
        }
closeAndLoadMain:
        target = GetInstance()->m_pMainPage;
        ClosePopup(page);
    } else if (option == 7 || option == 8) history = 0;
    else if (option != 0 && option != 1) __SVO_Assert_Handler(svoPageSource, 0x301);
    return doRequest(target, requestPath, 0, 0, history, svoPageGetCommand);
}

extern "C" SECTION(frameUpdate) void frameUpdate(CPage *page)
{
    int state = page->m_state;
    if (state == 2 || state == 12) {
        CDrawContextBase *draw = svoPageContextData.drawContext;
        long done = ((PageAnimationVtable *)draw->vtable)->AnimateOut(draw);
        if (state == 2 && done == 1) setPageState(page, 11);
    } else if (state == 3 || state == 6) {
        CDrawContextBase *draw = svoPageContextData.drawContext;
        if (((PageAnimationVtable *)draw->vtable)->AnimateIn(draw) == 1) setPageState(page, state == 3 ? 0 : 10);
    } else if (state == 11) {
        unsigned int type = page->m_lastCURIContentType;
        if (type == 2) return;
        if (type < 2) {
            page->m_pfSVMLTagCreateCB(page->m_lastHttpStatus, page->m_pCURIContent, page->m_iCURIContentLength, page, 1);
            Reset___dupe6(&page->m_requestListener);
            doAfterParseTags(page);
            if (!page->inTransitionCount && page->postTransitionCount) {
                int result = requestBinary(page, 2);
                setPageState(page, result == 1 ? 1 : 6);
            } else setPageState(page, 3);
        } else if (type == 4) page->m_lastCURIContentType = 1;
        else if (type == 8) __SVO_Assert_Handler(svoPageSource, 0x519);
        else if (type == 0xFFFFFFFF) __SVO_Assert_Handler(svoPageSource, 0x51C);
        else __SVO_Assert_Handler(svoPageSource, 0x51F);
    }
}

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

extern "C" SECTION(handleInput) long handleInput(CPage *page)
{
    long unhandled = 1;
    if (!okToNavigate___dupe2(page)) return unhandled;
    for (int index = 0; index < 256; ++index) {
        SVTag *tag = GetTagAtIndex(page, index);
        if (!tag || !unhandled) break;
        tag = GetTagAtIndex(page, index);
        HandleInputForPluginEvents(tag);
        unhandled = ((const PageTagInputVtable *)tag->vtable)->HandleInput(tag, page);
    }
    if (!unhandled) return unhandled;
    CInputContextBaseState *input = page->m_bIsPopup ? GetAltInputContext() : GetInputContext();
    if (((const PageInputQueryVtable *)input->vtable)->QueryBackInput(input) && !GetInstance()->m_bShowVKB && !GetInstance()->m_bIsXMPPActive) {
        PageHistoryState *history = &page->m_history;
        char *previous = top(history);
        char *entry = pop(history);
        if (!entry && page->m_bIsPopup) {
            ClosePopup(page);
            return 0;
        }
        char *name = GetPageName(GetInstance());
        if (!name || strcmp(name, svoPageHomePageID)) {
            if (!doRequest(page, top(history), 0, 0, 0, svoPageGetCommand)) push(history, previous);
        }
    } else if (((const PageInputQueryVtable *)input->vtable)->QueryRefreshInput(input) || autoRefreshPage(page)) {
        doRequest(page, top(&page->m_history), 0, 0, 0, svoPageGetCommand);
    }
    handleTextEntryDefaultInput(page);
    handleTextScrollDefaultInput(page);
    return unhandled;
}

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

extern "C" SECTION(setPageState) void setPageState(CPage *page, int nextState)
{
    char message[128];
    char oldText[64];
    char newText[64];
    memset(message, 0, 120);
    int state = page->m_state;
    if (state == -1) sprintf(oldText, svoPageStateError);
    else if (state == 0) sprintf(oldText, svoPageStateIdle);
    else if (state == 1) sprintf(oldText, svoPageStateDlPage);
    else if (state == 11) sprintf(oldText, svoPageStateCreatePage);
    else if (state == 2) sprintf(oldText, svoPageStateAniOut);
    else if (state == 3) sprintf(oldText, svoPageStateAniIn);
    else if (state == 4) sprintf(oldText, svoPageStateSubmit);
    else if (state == 5) sprintf(oldText, svoPageStateSubmitFail);
    else if (state == 6) sprintf(oldText, svoPageStateDlObjWhileAniIn);
    else if (state == 8) sprintf(oldText, svoPageStateDlObjThenAniIn);
    else if (state == 9) sprintf(oldText, svoPageStateDlObjThenAniOut);
    else if (state == 10) sprintf(oldText, svoPageStateDlObj);
    else if (state == 12) sprintf(oldText, svoPageStateShuttingDown);
    else __SVO_Assert_Handler(svoPageSource, 0x9ec);
    strcpy(message, oldText);
    strcat(message, svoPageStateTransition);
    state = nextState;
    if (state == -1) sprintf(newText, svoPageStateError);
    else if (state == 0) sprintf(newText, svoPageStateIdle);
    else if (state == 1) sprintf(newText, svoPageStateDlPage);
    else if (state == 11) sprintf(newText, svoPageStateCreatePage);
    else if (state == 2) sprintf(newText, svoPageStateAniOut);
    else if (state == 3) sprintf(newText, svoPageStateAniIn);
    else if (state == 4) sprintf(newText, svoPageStateSubmit);
    else if (state == 5) sprintf(newText, svoPageStateSubmitFail);
    else if (state == 6) sprintf(newText, svoPageStateDlObjWhileAniIn);
    else if (state == 8) sprintf(newText, svoPageStateDlObjThenAniIn);
    else if (state == 9) sprintf(newText, svoPageStateDlObjThenAniOut);
    else if (state == 10) sprintf(newText, svoPageStateDlObj);
    else if (state == 12) sprintf(newText, svoPageStateShuttingDown);
    else __SVO_Assert_Handler(svoPageSource, 0xa1c);
    strcat(message, newText);
    page->m_state = nextState;
}

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
