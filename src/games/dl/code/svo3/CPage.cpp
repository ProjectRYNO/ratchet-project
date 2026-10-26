#include "CPage.h"
#include "SVBrowser.h"
#include "CHttp.h"
#include "HttpUtils.h"
#include "CQueryParams.h"
#include "SVOString.h"
#include "string.h"
#include "stdio.h"
extern "C" {
extern char svoPageSource[];
extern char svoPageGetCommand[];
extern char svoPageSvmlExtension[];
extern char svoPageJspExtension[];
extern char svoPageDemoXmlName[];
extern char svoPageAmxExtension[];
extern char svoPageTm2Extension[];
extern char svoPageAccountFormat[];
extern const unsigned int svoDownloadBinaryVtable[];
void DownloadBinary(DownloadBinaryState *);
void _DownloadBinary(DownloadBinaryState *, int);
char *GetPath(DownloadBinaryState *);
int GetFormMethodType(DownloadBinaryState *);
int DestroyOnRequestSend(DownloadBinaryState *);
DownloadCallback GetDownloadCallback(DownloadBinaryState *);
char *GetUserNameParameter(DownloadBinaryState *);
char *GetAccountIDParameter(DownloadBinaryState *);
void GetLoginInfo(SVBrowserPrefix *, char **, char **, int *, char **);
}

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
int pathIsStatic(CPage *, char *);
int pathIsFullyQualified(CPage *, char *);
int resolveRelativePath(CPage *, char *, char *);
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
void DownloadBinary(DownloadBinaryState *);
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
int pathIsFullyQualified(CPage *, char *);
int resolveRelativePath(CPage *, char *, char *);
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
void DownloadBinary(DownloadBinaryState *);
void PageRequestListener(PageRequestListenerState *, CMemoryContextBaseState *, unsigned int);
int doRequest(CPage *, char *, CQueryParamListState *, int, int, char *);
extern char svoPageGetCommand[];
iksparser_struct *iks_dom_new(iks **);
}
extern "C" void CPageConstruct(CPage *page, char *firstPage, int popup, int listenPort) __asm__("CPage");


extern "C" {
void shutdown(CPage *);
void _PageRequestListener(PageRequestListenerState *, int);
void PageDelete(void *) __asm__("operator.delete___dupe2");
}

extern "C" {
char *getTopOfHistory(CPage *);
int ClosePopup(CPage *);
int okToNavigate___dupe2(CPage *);
SVTag *GetTagAtIndex(CPage *, int);
void HandleInputForPluginEvents(SVTag *);
char *GetPageName(SVBrowserPrefix *);
int autoRefreshPage(CPage *);
int handleTextEntryDefaultInput(CPage *);
int handleTextScrollDefaultInput(CPage *);
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
int DefaultHandleInput(SVTag *tag, CPage *page);
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
void ParseSVMLAddObjects(ParseXMLState *);
void _ParseSVMLAddObjects(ParseXMLState *, int);
void ParseSVMLForDownloads(ParseXMLState *);
void _ParseSVMLForDownloads(ParseXMLState *, int);
void ParseXMLInfo(ParseXMLState *);
void _ParseXMLInfo(ParseXMLState *, int);

}
extern "C" {
void FreeFrontDisplayBuffer(CPage *);
void setPageState(CPage *, int);
SVTag *GetTagAtIndex(CPage *, int);
void LeaveCurrentPage(CPage *);
void RemovePluginMgrMessages();
int SSL_Cleanup();
int GetVisible(SVTag *);
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
unsigned int iks_nr_bytes(iksparser_struct *);
unsigned int iks_nr_lines(iksparser_struct *);
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
// Functions are kept in retail address order: g++ 2.96's delay-slot filling depends on which
// callees are already defined earlier in the file.
// g++ 2.x object view of DownloadBinary: vptr after the data, so the implicit operator= saves and restores it.
struct DownloadBinaryObj { char data[0x264]; DownloadBinaryObj() __asm__("DownloadBinary"); virtual void destroy(int); };
struct InTransitArray { DownloadBinaryObj data[2]; int count; char used[32]; int GetCount() { return count; } };
struct PostTransitArray { DownloadBinaryObj data[11]; int count; char used[32]; int GetCount() { return count; } };




}






static inline void InTransitPop(InTransitArray *array, DownloadBinaryObj *out)
{
    for (int i = 0; i < 2; i++) {
        if (array->used[i]) {
            *out = array->data[i];
            memset(&array->data[i], 0, sizeof(DownloadBinaryObj));
            array->used[i] = 0;
            int *count = &array->count;
            (*count)--;
            return;
        }
    }
}







extern "C" char svoPagePostCommand[];

struct SVPathCtor : SVPath { SVPathCtor(char *scheme, char *server, unsigned short *port, char *path, unsigned int length) { m_scheme = scheme; m_server = server; m_port = port; m_path = path; m_pathMaxLength = length; } };

static inline int PreTransitionPending(CPage *page) { return page->preTransitionCount != 0; }






















extern "C" SECTION(operator.delete___dupe2) void CPageoperator_delete___dupe2(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

extern "C" SECTION(operator.new___dupe3) void * CPageoperator_new___dupe3(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x8E, svoPageSource);
}








static inline void TransitPop(PostTransitArray *array, DownloadBinaryObj *out)
{
    for (int i = 0; i < 11; i++) {
        if (array->used[i]) {
            *out = array->data[i];
            memset(&array->data[i], 0, sizeof(DownloadBinaryObj));
            array->used[i] = 0;
            int *count = &array->count;
            (*count)--;
            return;
        }
    }
}
static inline void CopyBytes(char *dst, int n, const char *src)
{
    do {
        *dst++ = *src++;
    } while (--n != -1);
}















extern "C" SECTION(_CPage) void _CPage(CPage *page, unsigned int flags)
{
    shutdown(page);
    _PageRequestListener(&page->m_requestListener, 2);
    _SVChronograph(&page->m_pageRefreshTimer, 2);
    {
        DownloadBinaryState *a = page->inTransition;
        if ((unsigned int)a) {
            DownloadBinaryState *item = a + 2;
            while (a != item) {
                --item;
                ((const PageDownloadVtable *)item->vtable)->destroy(item, 2);
            }
        }
    }
    {
        DownloadBinaryState *b = page->postTransition;
        if ((unsigned int)b) {
            DownloadBinaryState *item = b + 11;
            while (b != item) {
                --item;
                ((const PageDownloadVtable *)item->vtable)->destroy(item, 2);
            }
        }
    }
    {
        DownloadBinaryState *c = page->preTransition;
        if ((unsigned int)c) {
            DownloadBinaryState *item = c + 11;
            while (c != item) {
                --item;
                ((const PageDownloadVtable *)item->vtable)->destroy(item, 2);
            }
        }
    }
    if (flags & 1) { PageDelete(page); return; }
}
struct DownloadBinaryMember { char data[0x264]; void *vtable; DownloadBinaryMember() __asm__("DownloadBinary"); }; struct CPageShell { char pre[11 * 0x268]; int preCount; char preUsed[32]; char post[11 * 0x268]; int postCount; char postUsed[32]; char in[2 * 0x268]; int inCount; char inUsed[32]; char rest[0x637C - 0x3A2C]; CPageShell(char *firstPage, int popup, int listenPort) __asm__("CPage"); }; SECTION(CPage) CPageShell::CPageShell(char *firstPage, int popup, int listenPort)
{
    CPage *page = (CPage *)this;
    char *element = (char *)page->preTransition;
    int n = 10;
    do {
        DownloadBinary((DownloadBinaryState *)element);
        element += sizeof(DownloadBinaryMember);
    } while (--n != -1);
    char *postArray = (char *)page->postTransition;
    char *element2 = postArray;
    n = 10;
    do {
        DownloadBinary((DownloadBinaryState *)element2);
        element2 += sizeof(DownloadBinaryMember);
    } while (--n != -1);
    char *inArray = (char *)page->inTransition;
    char *element3 = inArray;
    n = 1;
    do {
        DownloadBinary((DownloadBinaryState *)element3);
        element3 += sizeof(DownloadBinaryMember);
    } while (--n != -1);
    PageHistory(&page->m_history);
    SVChronographState *timer = &page->m_pageRefreshTimer;
    SVChronograph(timer, 0);
    PageRequestListener(&page->m_requestListener, GetMemoryContext(), 0xA000);
    page->m_pRequestProvider = 0;
    page->m_bIsPopup = popup;
    setPageContextData(page);
    page->m_state = 0;
    setPageState(page, 0);
    page->m_bIsActive = 0;
    page->m_pBackDisplayBuffer = &page->m_displayBuffers[0];
    page->m_pFrontDisplayBuffer = &page->m_displayBuffers[1];
    memset(page->m_displayBuffers[0].tagList, 0, 0x400);
    memset(page->m_pFrontDisplayBuffer->tagList, 0, 0x400);
    SVDisplayBufferState *back = page->m_pBackDisplayBuffer;
    SVDisplayBufferState *front = page->m_pFrontDisplayBuffer;
    back->xml = 0;
    page->m_defTextEntryTag = 0;
    front->xml = 0;
    page->m_defTextScrollTag = 0;
    if (!(page->m_pBackDisplayBuffer->parser = iks_dom_new(&page->m_pBackDisplayBuffer->xml))) __SVO_Assert_Handler(svoPageSource, 0xCD);
    if (!(page->m_pFrontDisplayBuffer->parser = iks_dom_new(&page->m_pFrontDisplayBuffer->xml))) __SVO_Assert_Handler(svoPageSource, 0xD1);
    if (!(page->m_parser = iks_dom_new(&page->m_XML))) __SVO_Assert_Handler(svoPageSource, 0xD5);
    // Retail patch: each clearing loop's `i++` was overwritten with a branch to the loop's
    // closing delay slot, so the element memsets never run (they would wipe the vtables just
    // set by the DownloadBinary constructors). The asm statements reproduce those branches; the
    // target is relative (`2f+20` is the bnez delay slot) so no label asm splits the schedule.
    for (int i = 0; i < 11;) {
        register int fill __asm__("$5") = 0;
        int offset = i * (int)sizeof(DownloadBinaryMember);
        __asm__ __volatile__(".set noreorder
	b 2f+20
2:
	.set reorder" : "+r"(i) : "r"(offset), "r"(fill));
        memset((char *)page->preTransition + offset, fill, sizeof(DownloadBinaryMember));
    }
    page->preTransitionCount = 0;
    memset(page->preTransitionUsed, 0, 32);
    for (int i = 0; i < 11;) {
        register int fill __asm__("$5") = 0;
        int offset = i * (int)sizeof(DownloadBinaryMember);
        __asm__ __volatile__(".set noreorder
	b 2f+20
2:
	.set reorder" : "+r"(i) : "r"(offset), "r"(fill));
        memset(postArray + offset, fill, sizeof(DownloadBinaryMember));
    }
    *(int *)(postArray + 11 * 0x268) = 0;
    memset(postArray + 11 * 0x268 + 4, 0, 32);
    for (int i = 0; i < 2;) {
        register int fill __asm__("$5") = 0;
        int offset = i * (int)sizeof(DownloadBinaryMember);
        __asm__ __volatile__(".set noreorder
	b 2f+20
2:
	.set reorder" : "+r"(i) : "r"(offset), "r"(fill));
        memset(inArray + offset, fill, sizeof(DownloadBinaryMember));
    }
    *(int *)(inArray + 2 * 0x268) = 0;
    memset(inArray + 2 * 0x268 + 4, 0, 32);
    if (!firstPage || doRequest(page, firstPage, 0, 0, 1, svoPageGetCommand)) {
        Reset___dupe5(timer);
        page->m_pageRefreshSeconds = 0;
    }
}
extern "C" SECTION(PushPostTransitionArray) void PushPostTransitionArray(CPage *page, DownloadBinaryState *item, DownloadBinaryState **out)
{
    PostTransitArray *array = (PostTransitArray *)page->postTransition;
    for (int i = 0; i < 11; i++) {
        if (!array->used[i]) {
            array->data[i] = *(DownloadBinaryObj *)item;
            *out = (DownloadBinaryState *)&array->data[i];
            array->used[i] = 1;
            int *count = &array->count;
            (*count)++;
            return;
        }
    }
}
extern "C" SECTION(PopInTransitArray) void PopInTransitArray(CPage *page, DownloadBinaryState *out)
{
    InTransitArray *array = (InTransitArray *)page->inTransition;
    for (int i = 0; i < 2; i++) {
        if (array->used[i]) {
            *(DownloadBinaryObj *)out = array->data[i];
            memset(&array->data[i], 0, sizeof(DownloadBinaryObj));
            array->used[i] = 0;
            int *count = &array->count;
            (*count)--;
            return;
        }
    }
}
extern "C" SECTION(DestroyPreTransitionArray) void DestroyPreTransitionArray(CPage *page)
{
    // Retail patch: the first instruction of this clearing loop was overwritten with a branch
    // to the loop's closing delay slot, so the memset never runs (it would wipe the elements'
    // vtables). The asm reproduces that branch; `fill` is deliberately never set, as in retail.
    PostTransitArray *array = (PostTransitArray *)page->preTransition;
    char *elements = (char *)array->data;
    for (int i = 0; i < 11; i++) {
        int stride = sizeof(DownloadBinaryObj);
        register int fill __asm__("$5");
        __asm__ __volatile__(".set noreorder
	b 1f-4
	.set reorder" : "=r"(fill));
        memset(elements + i * stride, fill, sizeof(DownloadBinaryObj));
    }
    __asm__ __volatile__("1:");
    array->count = 0;
}
extern "C" SECTION(DestroyPostTransitionArray) void DestroyPostTransitionArray(CPage *page)
{
    // Retail patch: the first instruction of this clearing loop was overwritten with a branch
    // to the loop's closing delay slot, so the memset never runs (it would wipe the elements'
    // vtables). The asm reproduces that branch; `fill` is deliberately never set, as in retail.
    PostTransitArray *array = (PostTransitArray *)page->postTransition;
    char *elements = (char *)array->data;
    for (int i = 0; i < 11; i++) {
        int stride = sizeof(DownloadBinaryObj);
        register int fill __asm__("$5");
        __asm__ __volatile__(".set noreorder
	b 1f-4
	.set reorder" : "=r"(fill));
        memset(elements + i * stride, fill, sizeof(DownloadBinaryObj));
    }
    __asm__ __volatile__("1:");
    array->count = 0;
}
extern "C" SECTION(DestroyInTransitionArray) void DestroyInTransitionArray(CPage *page)
{
    // Retail patch: the first instruction of this clearing loop was overwritten with a branch
    // to the loop's closing delay slot, so the memset never runs (it would wipe the elements'
    // vtables). The asm reproduces that branch; `fill` is deliberately never set, as in retail.
    InTransitArray *array = (InTransitArray *)page->inTransition;
    char *elements = (char *)array->data;
    for (int i = 0; i < 2; i++) {
        int stride = sizeof(DownloadBinaryObj);
        register int fill __asm__("$5");
        __asm__ __volatile__(".set noreorder
	b 1f-4
	.set reorder" : "=r"(fill));
        memset(elements + i * stride, fill, sizeof(DownloadBinaryObj));
    }
    __asm__ __volatile__("1:");
    array->count = 0;
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
    char *data;
    int length;
    switch (state) {
    case 1:
        freeResources(page, 1);
        if (!page->m_pRequestProvider) __SVO_Assert_Handler(svoPageSource, 0x169);
        provider = page->m_pRequestProvider;
        if (!provider->vtable->IsBusy(provider)) {
            callGenericDownloadCallback(page, &page->m_pCURIContent, &page->m_iCURIContentLength);
            if (GetTagAtIndex(page, 0)) {
                if (!((InTransitArray *)page->inTransition)->GetCount() && page->preTransitionCount && requestBinary(page, 1) != 1) setPageState(page, 9);
            } else if (!((InTransitArray *)page->inTransition)->GetCount() && PreTransitionPending(page)) {
                if (requestBinary(page, 1) != 1) setPageState(page, 8);
            } else if (!page->m_pCURIContent) setPageState(page, 0);
        }
        break;
    case 10:
        provider = page->m_pRequestProvider;
        if (!provider->vtable->IsBusy(provider)) {
            callGenericDownloadCallback(page, &data, &length);
            if (!page->inTransitionCount && page->postTransitionCount) {
                if (requestBinary(page, 2) == 1) setPageState(page, 1);
            } else setPageState(page, 0);
        }
        break;
    case 6:
        provider = page->m_pRequestProvider;
        if (!provider->vtable->IsBusy(provider)) {
            callGenericDownloadCallback(page, &data, &length);
            if (!page->inTransitionCount && page->postTransitionCount) {
                if (requestBinary(page, 2) == 1) setPageState(page, 1);
            } else setPageState(page, 3);
        }
        break;
    case 9:
        provider = page->m_pRequestProvider;
        if (!provider->vtable->IsBusy(provider)) {
            callGenericDownloadCallback(page, &data, &length);
            if (!page->inTransitionCount && page->preTransitionCount) {
                if (requestBinary(page, 1) == 1) setPageState(page, 1);
            } else setPageState(page, 2);
        }
        break;
    case 8:
        provider = page->m_pRequestProvider;
        if (!provider->vtable->IsBusy(provider)) {
            callGenericDownloadCallback(page, &data, &length);
            if (state == page->m_state) {
                if (!page->inTransitionCount && page->preTransitionCount) {
                    if (requestBinary(page, 1) == 1) setPageState(page, 1);
                } else setPageState(page, 11);
            } else if (requestBinary(page, 1) == 1) setPageState(page, 1);
        }
        break;
    case -1:
    case 0:
    case 2:
    case 3:
    case 4:
    case 11:
    case 12:
        break;
    default:
        __SVO_Assert_Handler(svoPageSource, 0x212);
        break;
    }
    if (GetErrorCode()) setPageState(page, -1);
    return page->m_state;
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
extern "C" SECTION(shutdown) void shutdown(CPage *page)
{
    freeResources(page, 0);
    FreeDisplayBuffers(page);
    if (page->m_parser) { iks_parser_delete(page->m_parser); page->m_parser = 0; }
    IURISchemeProviderState *provider = page->m_pRequestProvider;
    if (provider) { provider->vtable->freeResources(provider, 0); page->m_pRequestProvider = 0; }
    SSL_Cleanup();
}
extern "C" SECTION(resolveRelativePath) int resolveRelativePath(CPage *page, char *current, char *relative)
{
    if (!*current || !relative) __SVO_Assert_Handler(svoPageSource, 0x291);
    char *path = relative;
    int parents = 0;
    for (;;) {
        if (!strncmp(svoPageParentPath, path, 3)) { path += 3; parents++; }
        else if (!strncmp(svoPageCurrentPath, path, 2)) path += 2;
        else break;
    }
    char *slash;
    for (int i = 0; i < parents; i++) {
        slash = strrchr(current, '/');
        if (!slash) __SVO_Assert_Handler(svoPageSource, 0x2AB);
        *slash = '-';
    }
    slash = strrchr(current, '/');
    slash++;
    svstrncpy(slash, path, 0x101 - (slash - current));
    return 1;
}
extern "C" SECTION(followLink) int followLink(CPage *page, char *filePath, int option)
{
    char path[257];
    if (!filePath) __SVO_Assert_Handler(svoPageSource, 0x2BF);
    int history = 1;
    for (int i = 0; i < 257; i++) path[i] = 0;
    char *requestPath = filePath;
    CPage *target = page;
    switch (option) {
    case 3:
        target = GetInstance()->m_pPopupPage;
        break;
    case 2:
        if (pathIsFullyQualified(page, filePath)) requestPath = filePath;
        else {
            svstrncpy(path, getTopOfHistory(GetInstance()->m_pMainPage), 257);
            resolveRelativePath(page, path, filePath);
            requestPath = path;
        }
        target = GetInstance()->m_pPopupPage;
        target->m_bIsActive = 1;
        break;
    case 5:
        svstrncpy(path, top(&GetInstance()->m_pMainPage->m_history), 257);
        requestPath = path;
        goto closeAndLoadMain;
    case 6:
        svstrncpy(path, top(&GetInstance()->m_pPopupPage->m_history), 257);
        if (pathIsFullyQualified(page, filePath)) requestPath = filePath;
        else {
            resolveRelativePath(page, path, filePath);
            requestPath = path;
        }
    closeAndLoadMain:
        target = GetInstance()->m_pMainPage;
        ClosePopup(page);
        break;
    case 4:
        ClosePopup(page);
        return 1;
    case 7:
    case 8:
        history = 0;
        break;
    case 0:
    case 1:
        break;
    default:
        __SVO_Assert_Handler(svoPageSource, 0x301);
        break;
    }
    return doRequest(target, requestPath, 0, 0, history, svoPageGetCommand);
}
extern "C" SECTION(addToHistory) int addToHistory(CPage *page, char *path)
{
    if (!path) __SVO_Assert_Handler(svoPageSource, 0x30D);
    push(&page->m_history, path);
    return 1;
}
extern "C" SECTION(getTopOfHistory) char *getTopOfHistory(CPage *page) { return top(&page->m_history); }
extern "C" SECTION(doPost) int doPost(CPage *page, char *path, CQueryParamListState *params, int method, int storeHistory)
{
    return doRequest(page, path, params, method, storeHistory, svoPagePostCommand);
}
extern "C" SECTION(doRequest) int doRequest(CPage *page, char *path, CQueryParamListState *params, int method, int storeHistory, char *command)
{
    char newPath[272];
    char oldPath[272];
    char fullPath[272];
    char *histPath;
    if (!path) __SVO_Assert_Handler(svoPageSource, 0x327);
    svstrncpy(oldPath, path, 257);
    if (pathIsStatic(page, path)) {
        char *screen = strstr(path, svoPageDownloadHostSeparator) + 2;
        CSystemContextBase *system = GetSystemContext();
        ((const PageStaticScreenVtable *)system->vtable)->EnterStaticScreen(system, screen);
        return 1;
    }
    if (pathIsFullyQualified(page, path)) {
        SVPathCtor split(page->m_scheme, page->m_serverName, &page->m_port, newPath, 257);
        parseFullyQualifiedPath(path, &split);
        histPath = path;
    } else if (*path != '/') {
        memset(fullPath, 0, 257);
        svstrncpy(fullPath, top(&page->m_history), 257);
        if (!resolveRelativePath(page, fullPath, oldPath)) {
            __SVO_Assert_Handler(svoPageSource, 0x34B);
            return 0;
        }
        SVPathCtor split(page->m_scheme, page->m_serverName, &page->m_port, newPath, 257);
        parseFullyQualifiedPath(fullPath, &split);
        histPath = fullPath;
    } else {
        memset(newPath, 0, 257);
        char *src = top(&page->m_history);
        char *base;
        if (src) base = src;
        else base = page->m_serverName ? page->m_serverName : 0;
        strncpy(newPath, base, 257);
        char *replace = strstr(newPath, svoPageDownloadHostSeparator);
        replace = strstr(replace + 2, svoPageDownloadPathSeparator);
        if (!replace) __SVO_Assert_Handler(svoPageSource, 0x372);
        strncpy(replace, oldPath, strlen(oldPath) + 1);
        histPath = newPath;
        if (strlen(newPath) >= 257) __SVO_Assert_Handler(svoPageSource, 0x375);
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
    if (storeHistory) push(&page->m_history, histPath);
    page->m_pfSVMLPreTagCreateScanCB = (DownloadCallback)scanForDownloadablesCB;
    page->m_pfSVMLTagCreateCB = (DownloadCallback)parseTagsCB;
    page->m_pfXMLScanCB = (DownloadCallback)scanXMLCB;
    page->m_pfBinaryDownloadCB = 0;
    page->m_pCURIContent = 0;
    page->m_iCURIContentLength = 0;
    page->m_lastCURIContentType = 0;
    setPageState(page, 1);
    return 1;
}
extern "C" SECTION(parseTagsCB) void parseTagsCB(unsigned int status, char *buffer, int size, CPage *page, int swap)
{
    if (!page) __SVO_Assert_Handler(svoPageSource, 0x3ab);
    ParseXMLState parser;
    ParseSVMLAddObjects(&parser);
    SVMLparseCB(page, status, buffer, size, &parser, swap);
    _ParseSVMLAddObjects(&parser, 2);
}
extern "C" SECTION(scanForDownloadablesCB) void scanForDownloadablesCB(unsigned int status, char *buffer, int size, CPage *page, int swap)
{
    if (!page) __SVO_Assert_Handler(svoPageSource, 0x3b8);
    ParseXMLState parser;
    ParseSVMLForDownloads(&parser);
    SVMLparseCB(page, status, buffer, size, &parser, swap);
    _ParseSVMLForDownloads(&parser, 2);
}
extern "C" SECTION(scanXMLCB) void scanXMLCB(unsigned int status, char *buffer, int size, CPage *page, int swap)
{
    if (!page) __SVO_Assert_Handler(svoPageSource, 0x3cb);
    ParseXMLState parser;
    ParseXMLInfo(&parser);
    XMLparseCB(page, status, buffer, size, &parser);
    _ParseXMLInfo(&parser, 2);
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
extern "C" SECTION(parseCBHelper) void parseCBHelper(CPage *page, iks *xml, ParseXMLState *parser, int depth)
{
    for (iks *child = iks_child(xml); child; child = iks_next(child)) {
        switch (iks_type(child)) {
        case 0:
            __SVO_Assert_Handler(svoPageSource, 0x45B);
            break;
        case 1:
            ((const ParseXMLVtablePrefix *)parser->vtable)->CallFunction(parser, child, page);
            break;
        case 2:
        case 3:
            break;
        default:
            __SVO_Assert_Handler(svoPageSource, 0x465);
            break;
        }
        if (iks_has_children(child)) parseCBHelper(page, child, parser, ++depth);
    }
}
extern "C" SECTION(handleDefaultSelection) void handleDefaultSelection(CPage *page)
{
    SVTag *first = 0;
    int selected = 0;
    for (int i = 0; i < 256 && GetTagAtIndex(page, i); i++) {
        SVTag *a = GetTagAtIndex(page, i);
        if (a->vtable->IsSelected(a)) {
            selected = 1;
        } else {
            SVTag *b = GetTagAtIndex(page, i);
            if (b->vtable->IsSelectable(b) && !first) {
                first = GetTagAtIndex(page, i);
            } else if (selected) {
                SVTag *c = GetTagAtIndex(page, i);
                if (c->vtable->IsSelected(c)) __SVO_Assert_Handler(svoPageSource, 0x488);
            }
        }
    }
    if (first && !selected) first->vtable->SetSelectedState(first, 1);
}
extern "C" SECTION(frameUpdate) void frameUpdate(CPage *page)
{
    do switch (page->m_state) {
    case 12: {
        ((PageAnimationVtable *)svoPageContextData.drawContext->vtable)->AnimateOut(svoPageContextData.drawContext);
        break;
    }
    case 6: {
        if (((PageAnimationVtable *)svoPageContextData.drawContext->vtable)->AnimateIn(svoPageContextData.drawContext) == 1) setPageState(page, 10);
        break;
    }
    case 3: {
        if (((PageAnimationVtable *)svoPageContextData.drawContext->vtable)->AnimateIn(svoPageContextData.drawContext) == 1) setPageState(page, 0);
        break;
    }
    case 2: {
        if (((PageAnimationVtable *)svoPageContextData.drawContext->vtable)->AnimateOut(svoPageContextData.drawContext) == 1) setPageState(page, 11);
        break;
    }
    case 11:
        switch ((unsigned int)page->m_lastCURIContentType) {
        case 0:
        case 1:
            page->m_pfSVMLTagCreateCB(page->m_lastHttpStatus, page->m_pCURIContent, page->m_iCURIContentLength, page, 1);
            Reset___dupe6(&page->m_requestListener);
            doAfterParseTags(page);
            if (!page->inTransitionCount && page->postTransitionCount) {
                if (requestBinary(page, 2) == 1) setPageState(page, 1);
                else setPageState(page, 6);
            } else setPageState(page, 3);
            break;
        case 2:
            break;
        case 4:
            page->m_lastCURIContentType = 1;
            break;
        case 8:
            __SVO_Assert_Handler(svoPageSource, 0x519);
            break;
        case 0xFFFFFFFF:
            __SVO_Assert_Handler(svoPageSource, 0x51C);
            break;
        default:
            __SVO_Assert_Handler(svoPageSource, 0x51F);
            break;
        }
        break;
    } while (0);
}
extern "C" SECTION(draw) void draw(CPage *page, int active)
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
extern "C" SECTION(getIndexOfNextAvailEntryInTagList) int getIndexOfNextAvailEntryInTagList(CPage *page)
{
    SVTag **entries = page->m_pBackDisplayBuffer->tagList;
    for (int i = 0; i < 256; ++i) {
        if (!entries[i]) return i;
    }
    __SVO_Assert_Handler(svoPageSource, 0x5D5);
    return -1;
}
extern "C" SECTION(addObject) void addObject(CPage *page, iks *xml)
{
    SVTagModuleState **modules = getInstance___dupe3()->m_modules;
    for (int i = 0; i < 128 && modules[i]; i++) {
        SVTagModuleState *module = modules[i];
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
SECTION(okToNavigate___dupe2) int okToNavigate___dupe2(CPage *page)
{
    if (page->m_bIsActive && page->m_state == 0) return 1;
    return 0;
}
extern "C" SECTION(handleUpdate) void handleUpdate(CPage *page)
{
    for (int i = 0; i < 256 && GetTagAtIndex(page, i); i++) {
        SVTag *tag = GetTagAtIndex(page, i);
        if (!tag) __SVO_Assert_Handler(svoPageSource, 0x638);
        tag->vtable->Update(tag, page);
    }
}
extern "C" SECTION(handleInput) int handleInput(CPage *page)
{
    int bContinue = 1;
    if (okToNavigate___dupe2(page)) {
        SVTag *tag;
        for (int i = 0; i < 256 && GetTagAtIndex(page, i) && bContinue; i++) {
            tag = GetTagAtIndex(page, i);
            HandleInputForPluginEvents(tag);
            bContinue = ((const PageTagInputVtable *)tag->vtable)->HandleInput(tag, page);
        }
        if (bContinue) {
            CInputContextBaseState *input;
            if (!page->m_bIsPopup) input = GetInputContext();
            else input = GetAltInputContext();
            if (((const PageInputQueryVtable *)input->vtable)->QueryBackInput(input) && !GetInstance()->m_bShowVKB && !GetInstance()->m_bIsXMPPActive) {
                PageHistoryState *history = &page->m_history;
                char *previous = top(history);
                if (!pop(history) && page->m_bIsPopup) {
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
        }
    }
    return bContinue;
}
extern "C" SECTION(setPageContextData) void setPageContextData(CPage *page)
{
    if (page->m_bIsPopup) {
        svoPageContextData.audioContext = GetAudioContext();
        svoPageContextData.drawContext = GetDrawContext();
        svoPageContextData.memoryContext = GetMemoryContext();
        svoPageContextData.systemContext = GetSystemContext();
        svoPageContextData.inputContext = GetInputContext();
    } else {
        svoPageContextData.audioContext = GetAltAudioContext();
        svoPageContextData.drawContext = GetAltDrawContext();
        svoPageContextData.memoryContext = GetAltMemoryContext();
        svoPageContextData.systemContext = GetAltSystemContext();
        svoPageContextData.inputContext = GetAltInputContext();
    }
}
struct ServerNameBlock { char text[128]; }; extern "C" SECTION(LoadStatePostGameFromPersistentData) int LoadStatePostGameFromPersistentData(CPage *page, SVPersistentData *persist)
{
    LoadStatePostGameFromPersistentData___dupe4(Get(), persist);
    *(ServerNameBlock *)page->m_serverName = *(ServerNameBlock *)persist->serverName;
    page->m_port = persist->port;
    return 1;
}
extern "C" SECTION(handleTextEntryDefaultInput) int handleTextEntryDefaultInput(CPage *page)
{
    if (!page->m_defTextEntryTag) return 1;
    return DefaultHandleInput(page->m_defTextEntryTag, page);
}
extern "C" SECTION(handleTextScrollDefaultInput) int handleTextScrollDefaultInput(CPage *page)
{
    if (!page->m_defTextScrollTag) return 1;
    return DefaultHandleInput(page->m_defTextScrollTag, page);
}
extern "C" SECTION(SetDefaultTextScrollTag) void SetDefaultTextScrollTag(CPage *page, SVTag *tag)
{
    if (page->m_defTextScrollTag) __SVO_Assert_Handler(svoPageSource, 0x731);
    page->m_defTextScrollTag = tag;
}
extern "C" SECTION(pathIsFullyQualified) int pathIsFullyQualified(CPage *page, char *path)
{
    int result = 0;
    char *colon = strstr(path, svoPageSchemeSeparator);
    if (colon) {
        int length = colon - path;
        if (length > 14) __SVO_Assert_Handler(svoPageSource, 0x74d);
        char scheme[15];
        memcpy(scheme, path, 15);
        scheme[length] = 0;
        result = HasProvider(Get(), scheme);
        if (!result) SetErrorCode(32);
    }
    return result;
}
extern "C" SECTION(pathIsStatic) int pathIsStatic(CPage *page, char *path)
{
    int result = 0;
    char *colon = strstr(path, svoPageSchemeSeparator);
    if (colon) {
        int length = colon - path;
        if (length > 14) __SVO_Assert_Handler(svoPageSource, 0x777);
        char scheme[15];
        memcpy(scheme, path, 15);
        scheme[length] = 0;
        result = strcmp(scheme, svoPageStaticScheme) == 0;
    }
    return result;
}
extern "C" SECTION(adjustPathBinaryDownload) void adjustPathBinaryDownload(CPage *page, DownloadBinaryState *download)
{
    char path[272];
    char resolved[272];
    if (!download) __SVO_Assert_Handler(svoPageSource, 0x78C);
    char *source = GetPath(download);
    int length = strlen(GetPath(download));
    svstrncpy(path, source, length + 1);
    if (pathIsFullyQualified(page, path)) {
        strncpy(resolved, path, 257);
    } else if (path[0] != '/') {
        memset(resolved, 0, 257);
        strncpy(resolved, top(&page->m_history), 257);
        if (!resolveRelativePath(page, resolved, path)) {
            __SVO_Assert_Handler(svoPageSource, 0x7A1);
            return;
        }
    } else {
        memset(resolved, 0, 257);
        strncpy(resolved, top(&page->m_history), 257);
        char *replace = strstr(resolved, svoPageDownloadHostSeparator);
        replace = strstr(replace + 2, svoPageDownloadPathSeparator);
        if (!replace) __SVO_Assert_Handler(svoPageSource, 0x7AD);
        strncpy(replace, path, strlen(path));
    }
    if (page->m_state != 1) __SVO_Assert_Handler(svoPageSource, 0x7B3);
    SetPath(download, resolved);
}
extern "C" SECTION(requestBinary) int requestBinary(CPage *page, int queue)
{
    char unused[1024];
    CQueryParamListState params;
    CQueryParamList(&params);
    DownloadBinaryObj recordObj;
    DownloadBinaryState &record = *(DownloadBinaryState *)&recordObj;
    switch (queue) {
    case 0:
        __SVO_Assert_Handler(svoPageSource, 0x7C7);
        break;
    case 1:
        TransitPop((PostTransitArray *)page->preTransition, &recordObj);
        break;
    case 2:
        TransitPop((PostTransitArray *)page->postTransition, &recordObj);
        break;
    case 3:
        __SVO_Assert_Handler(svoPageSource, 0x7D0);
        break;
    case 0x7FFFFFFF:
        __SVO_Assert_Handler(svoPageSource, 0x7D3);
        break;
    }
    char path[272];
    SVPathCtor split(page->m_scheme, page->m_serverName, &page->m_port, path, 257);
    parseFullyQualifiedPath(GetPath(&record), &split);
    int type = 1;
    if (!strstr(GetPath(&record), svoPageSvmlExtension)) {
        if (strstr(GetPath(&record), svoPageJspExtension) || strstr(svoPageDemoXmlName, GetPath(&record))) type = 2;
        else {
            type = 4;
            if (!strstr(GetPath(&record), svoPageAmxExtension)) type = strstr(GetPath(&record), svoPageTm2Extension) ? 5 : 0;
        }
    }
    if (GetFormMethodType(&record) == 1) {
        char *user;
        char *password;
        int account;
        char number[16];
        char *ip;
        GetLoginInfo(GetInstance(), &user, &password, &account, &ip);
        sprintf(number, svoPageAccountFormat, account);
        Set(&params, GetUserNameParameter(&record), user, 0);
        Set(&params, GetAccountIDParameter(&record), number, 0);
    } else memset(unused, 0, sizeof(unused));
    URIRequest request;
    request.scheme = page->m_scheme;
    request.host = page->m_serverName;
    request.port = page->m_port;
    request.filePath = path;
    request.params = &params;
    request.methodType = GetFormMethodType(&record);
    request.httpCommand = svoPageGetCommand;
    request.context = 0;
    if (page->m_pRequestProvider) __SVO_Assert_Handler(svoPageSource, 0x811);
    IURISchemeProviderState *provider = doRequest___dupe3(Get(), (URIRequestPrefix *)&request, (IRequestListener *)&page->m_requestListener, page);
    page->m_pRequestProvider = provider;
    if (provider) {
        DownloadCallback callback = GetDownloadCallback(&record);
        page->m_pfBinaryDownloadCB = callback;
        page->m_pfXMLScanCB = callback;
        if (!DestroyOnRequestSend(&record)) {
            DownloadBinaryState copyObj;
            DownloadBinaryState &copy = copyObj;
            InTransitArray *inArr = (InTransitArray *)page->inTransition;
            copy.vtable = svoDownloadBinaryVtable;
            CopyBytes(copy.szPath, 0x100, record.szPath);
            copy.bRequested = record.bRequested;
            copy.eMethod = record.eMethod;
            copy.bDestroyWhenRequestSent = record.bDestroyWhenRequestSent;
            copy.iID = record.iID;
            copy.usWidth = record.usWidth;
            copy.usHeight = record.usHeight;
            copy.eMethodType = record.eMethodType;
            copy.pDownloadCallback = record.pDownloadCallback;
            copy.m_iUserNameMaxLength = record.m_iUserNameMaxLength;
            CopyBytes(copy.m_szActionStringParameter, 0xFF, record.m_szActionStringParameter);
            CopyBytes(copy.m_szUserNameParameter, 0x1F, record.m_szUserNameParameter);
            CopyBytes(copy.m_szAccountIDParameter, 0x1F, record.m_szAccountIDParameter);
            for (int k = 0; k < 2; k++) {
                if (!inArr->used[k]) {
                    inArr->data[k] = *(DownloadBinaryObj *)&copyObj;
                    inArr->used[k] = 1;
                    int *count = &inArr->count;
                    (*count)++;
                    break;
                }
            }
            _DownloadBinary(&copyObj, 2);
        }
    }
    _DownloadBinary(&record, 2);
    _CQueryParamList(&params, 2);
    return type;
}
extern "C" SECTION(scanObject) void scanObject(CPage *page, iks *xml)
{
    SVTagModuleState **modules = getInstance___dupe3()->m_modules;
    for (int i = 0; i < 128 && modules[i]; i++) {
        SVTagModuleState *module = modules[i];
        if (!module->vtable->IsMyTag(module, xml)) continue;
        SVTagScanResult results[2];
        for (int k = 0; k < 2; k++) {
            SVTagScanResult *r = &results[k];
            r->action = 0;
            r->download = 0;
        }
        svoPageContextData.pMain = page;
        module->vtable->ScanTag(module, xml, page->m_pFrontDisplayBuffer->tagList, &svoPageContextData, results);
        for (int j = 0; j < 2; ++j) {
            switch ((unsigned int)results[j].action) {
            case 1: adjustPathBinaryDownload(page, results[j].download); break;
            case 0: break;
            case 2: adjustPathBinaryDownload(page, results[j].download); break;
            case 3: setPageState(page, 1); break;
            default: __SVO_Assert_Handler(svoPageSource, 0x84E); break;
            }
        }
        return;
    }
}
extern "C" SECTION(callGenericDownloadCallback) int callGenericDownloadCallback(CPage *page, char **data, int *length)
{
    if (!GetResponse(&page->m_requestListener, data, length)) {
        SetErrorCode(0x1D);
        return 0;
    }
    page->m_lastHttpStatus = GetLastStatus(&page->m_requestListener);
    unsigned int type = GetLastContentType(&page->m_requestListener);
    page->m_lastCURIContentType = type;
    switch (type) {
    case 3: {
        int state = page->m_state;
        if (state == 1) {
            int size = substituteErrorPage(page, page->m_lastHttpStatus, *data, *length);
            page->m_lastCURIContentType = state;
            *length = size;
            goto scanSVML;
        }
        if ((unsigned int)(state - 8) < 3 || state == 6) {
            DownloadBinaryObj item;
            InTransitPop((InTransitArray *)page->inTransition, &item);
            _DownloadBinary((DownloadBinaryState *)&item, 2);
        }
        break;
    }
    case 1:
    scanSVML:
        if (!page->m_pfSVMLPreTagCreateScanCB) __SVO_Assert_Handler(svoPageSource, 0x88A);
        page->m_pfSVMLPreTagCreateScanCB(page->m_lastHttpStatus, *data, *length, page, 0);
        setPageState(page, 2);
        break;
    case 2:
        if (!page->m_pfXMLScanCB) __SVO_Assert_Handler(svoPageSource, 0x8A3);
        page->m_pfXMLScanCB(page->m_lastHttpStatus, *data, *length, page, 0);
        Reset___dupe6(&page->m_requestListener);
        setPageState(page, 0);
        break;
    case 4:
    case 5:
        if (!page->m_pfBinaryDownloadCB) __SVO_Assert_Handler(svoPageSource, 0x8BA);
        page->m_pfBinaryDownloadCB(page->m_lastHttpStatus, *data, *length, page, 0);
        break;
    case 8:
        __SVO_Assert_Handler(svoPageSource, 0x8C5);
        break;
    case 0xFFFFFFFF:
        __SVO_Assert_Handler(svoPageSource, 0x8C9);
        break;
    case 0:
        break;
    default:
        __SVO_Assert_Handler(svoPageSource, 0x8CD);
        break;
    }
    if (!page->m_pRequestProvider) __SVO_Assert_Handler(svoPageSource, 0x8D2);
    if (page->m_pRequestProvider) {
        page->m_pRequestProvider->vtable->freeResources(page->m_pRequestProvider, 0);
        page->m_pRequestProvider = 0;
    }
    return page->m_lastCURIContentType;
}
extern "C" SECTION(LeaveCurrentPage) void LeaveCurrentPage(CPage *page)
{
    SVTagModuleListState *instance = getInstance___dupe3();
    int i = 1;
    while (instance->m_modules[i]) { instance->m_modules[i]->vtable->LeaveCurrentPage(instance->m_modules[i]); i++; }
    char *name = GetPageName(GetInstance());
    if (name) {
        if (!strcmp(name, svoTournamentHomeName)) svoTournamentSelectedTagName = GetSelectedTagName(page);
    }
}
extern "C" SECTION(EnterNewPage___dupe30) void EnterNewPage___dupe30(CPage *page)
{
    SVTagModuleListState *instance = getInstance___dupe3();
    int i = 1;
    while (instance->m_modules[i]) { instance->m_modules[i]->vtable->EnterNewPage(instance->m_modules[i]); i++; }
}
extern "C" SECTION(GetSelectedTagName) char *GetSelectedTagName(CPage *page)
{
    SVTag **entries = page->m_pFrontDisplayBuffer->tagList;
    for (int i = 0; i < 256 && entries[i]; ++i) {
        if (entries[i]->vtable->IsSelected(entries[i]))
            return entries[i]->vtable->GetTagName(entries[i]);
    }
    return 0;
}
extern "C" SECTION(doAfterParseTags) void doAfterParseTags(CPage *page)
{
    SVTag **tags = page->m_pFrontDisplayBuffer->tagList;
    if (!tags) __SVO_Assert_Handler(svoPageSource, 0x933);
    int i = 0;
    SVTag *tag;
next:
    if (i < 256) {
        i++;
        tag = *tags++;
        if (tag) {
            if (!page->m_defTextScrollTag && tag->m_isDefTextScroll) SetDefaultTextScrollTag(page, tag);
            goto next;
        }
    }
    char *name = GetPageName(GetInstance());
    CInputContextBaseState *input = GetInputContext();
    if (!input->vtable->SetButtonMapForPage(input, name)) SetDefaultButtonMap(GetInputContext());
    FindAndSetDefualtTextAreaScroll(page);
    EnterNewPage___dupe30(page);
}
extern "C" SECTION(FindAndSetDefualtTextAreaScroll) void FindAndSetDefualtTextAreaScroll(CPage *page)
{
    SVTag **tags = page->m_pFrontDisplayBuffer->tagList;
    int multiple = 0;
    int found = -1;
    SVTag **entry = tags;
    for (int i = 0; i < 256; i++) {
        SVTag *tag = *entry++;
        if (!tag) break;
        if (!strcmp(svoPageTextAreaTagName, GetTagTypeName(tag))) {
            if (found == -1) { found = i; continue; }
            multiple = 1;
            break;
        }
    }
    if (!multiple && found != -1) {
        tags[found]->m_isDefTextScroll = 1;
        SetDefaultTextScrollTag(page, tags[found]);
    }
}
extern "C" SECTION(autoRefreshPage) int autoRefreshPage(CPage *page)
{
    SVChronographState *timer = &page->m_pageRefreshTimer;
    if (IsRunning(timer) && Elapsed(timer) >= page->m_pageRefreshSeconds) {
        Reset___dupe5(timer);
        return 1;
    }
    return 0;
}
extern "C" SECTION(SetPageRefreshSeconds) void SetPageRefreshSeconds(CPage *page, int seconds)
{
    page->m_pageRefreshSeconds = seconds;
    SVChronographState *timer = &page->m_pageRefreshTimer;
    if (IsStopped(timer)) {
        Reset___dupe5(timer);
        Start___dupe3(timer);
    }
}
extern "C" SECTION(ClosePopup) int ClosePopup(CPage *page)
{
    if (page != GetInstance()->m_pPopupPage) __SVO_Assert_Handler(svoPageSource, 0x9AB);
    page->m_bIsActive = 0;
    clear(&page->m_history);
    FreeDisplayBuffers(page);
    freeResources(page, 0);
    return 1;
}
extern "C" SECTION(setPageState) void setPageState(CPage *page, int nextState)
{
    char message[128];
    char oldText[64];
    char newText[64];
    memset(message, 0, 120);
    switch (page->m_state) {
    case -1: sprintf(oldText, svoPageStateError); break;
    case 0: sprintf(oldText, svoPageStateIdle); break;
    case 1: sprintf(oldText, svoPageStateDlPage); break;
    case 11: sprintf(oldText, svoPageStateCreatePage); break;
    case 2: sprintf(oldText, svoPageStateAniOut); break;
    case 3: sprintf(oldText, svoPageStateAniIn); break;
    case 4: sprintf(oldText, svoPageStateSubmit); break;
    case 5: sprintf(oldText, svoPageStateSubmitFail); break;
    case 6: sprintf(oldText, svoPageStateDlObjWhileAniIn); break;
    case 8: sprintf(oldText, svoPageStateDlObjThenAniIn); break;
    case 9: sprintf(oldText, svoPageStateDlObjThenAniOut); break;
    case 10: sprintf(oldText, svoPageStateDlObj); break;
    case 12: sprintf(oldText, svoPageStateShuttingDown); break;
    default: __SVO_Assert_Handler(svoPageSource, 0x9ec); break;
    }
    strcpy(message, oldText);
    strcat(message, svoPageStateTransition);
    switch (nextState) {
    case -1: sprintf(newText, svoPageStateError); break;
    case 0: sprintf(newText, svoPageStateIdle); break;
    case 11: sprintf(newText, svoPageStateCreatePage); break;
    case 1: sprintf(newText, svoPageStateDlPage); break;
    case 2: sprintf(newText, svoPageStateAniOut); break;
    case 3: sprintf(newText, svoPageStateAniIn); break;
    case 4: sprintf(newText, svoPageStateSubmit); break;
    case 5: sprintf(newText, svoPageStateSubmitFail); break;
    case 6: sprintf(newText, svoPageStateDlObjWhileAniIn); break;
    case 8: sprintf(newText, svoPageStateDlObjThenAniIn); break;
    case 9: sprintf(newText, svoPageStateDlObjThenAniOut); break;
    case 10: sprintf(newText, svoPageStateDlObj); break;
    case 12: sprintf(newText, svoPageStateShuttingDown); break;
    default: __SVO_Assert_Handler(svoPageSource, 0xa1c); break;
    }
    strcat(message, newText);
    page->m_state = nextState;
}
extern "C" SECTION(SwapDisplayBuffers) void SwapDisplayBuffers(CPage *page)
{
    SVDisplayBufferState *first = &page->m_displayBuffers[0];
    if (page->m_pBackDisplayBuffer == first) {
        page->m_pBackDisplayBuffer = &page->m_displayBuffers[1];
        page->m_pFrontDisplayBuffer = first;
    } else {
        page->m_pBackDisplayBuffer = first;
        page->m_pFrontDisplayBuffer = &page->m_displayBuffers[1];
    }
}
SECTION(GetTagAtIndex) SVTag *GetTagAtIndex(CPage *page, int index)
{
    return page->m_pFrontDisplayBuffer->tagList[index];
}
SECTION(SetTagAtIndex) void SetTagAtIndex(CPage *page, int index, SVTag *tag)
{
    page->m_pBackDisplayBuffer->tagList[index] = tag;
}
extern "C" SECTION(ResetBackDisplayBuffer) void ResetBackDisplayBuffer(CPage *page)
{
    FreeBackDisplayBuffer(page);
    ReAllocBackDisplayBufferParser(page);
}
extern "C" SECTION(ReAllocBackDisplayBufferParser) void ReAllocBackDisplayBufferParser(CPage *page)
{
    if (page->m_pBackDisplayBuffer->parser) __SVO_Assert_Handler(svoPageSource, 0xA4E);
    iksparser_struct *parser = iks_dom_new(&page->m_pBackDisplayBuffer->xml);
    page->m_pBackDisplayBuffer->parser = parser;
    if (!parser) __SVO_Assert_Handler(svoPageSource, 0xA52);
    iks_parser_reset(page->m_pBackDisplayBuffer->parser);
}
extern "C" SECTION(FreeBackDisplayBuffer) void FreeBackDisplayBuffer(CPage *page)
{
    SVTag **list = page->m_pBackDisplayBuffer->tagList;
    int i = 0;
    SVTag **next;
    // fake match: permuter (register allocation)
    while (i < 256 && *(next = &list[i])) {
        SVTag *tag = page->m_pBackDisplayBuffer->tagList[i];
        tag->vtable->destroy(tag, 3);
        list = page->m_pBackDisplayBuffer->tagList;
        SVTag **slot = &list[i];
        ++i;
        *slot = 0;
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
extern "C" SECTION(FreeFrontDisplayBuffer) void FreeFrontDisplayBuffer(CPage *page)
{
    SVTag **list = page->m_pFrontDisplayBuffer->tagList;
    int i = 0;
    SVTag **next;
    // fake match: permuter (register allocation)
    while (i < 256 && *(next = &list[i])) {
        SVTag *tag = page->m_pFrontDisplayBuffer->tagList[i];
        tag->vtable->destroy(tag, 3);
        list = page->m_pFrontDisplayBuffer->tagList;
        SVTag **slot = &list[i];
        ++i;
        *slot = 0;
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
extern "C" SECTION(FreeDisplayBuffers) void FreeDisplayBuffers(CPage *page) { FreeBackDisplayBuffer(page); FreeFrontDisplayBuffer(page); }
extern "C" SECTION(GenerateLagListInfo) void GenerateLagListInfo(CPage *page)
{
    CMemoryContextBaseState *memory = GetMemoryContext();
    if (!memory) __SVO_Assert_Handler(svoPageSource, 0xAA3);
    SVTag **tags = page->m_pFrontDisplayBuffer->tagList;
    if (!tags) __SVO_Assert_Handler(svoPageSource, 0xAA5);
    int count;
    for (count = 0; count < 256 && tags[count]; count++) {
    }
    SVTagInfo *info = (SVTagInfo *)svAllocSafe(memory, count * sizeof(SVTagInfo), 0, 0xAB7, svoPageSource);
    if (!info) return;
    memset(info, 0, count * sizeof(SVTagInfo));
    for (int i = 0; i < count; ++i) {
        if (!tags[i]) __SVO_Assert_Handler(svoPageSource, 0xAC2);
        info[i].tag = tags[i];
        info[i].tagID = tags[i]->vtable->GetTagID(tags[i]);
        info[i].name = tags[i]->vtable->GetTagName(tags[i]);
        info[i].typeName = GetTagTypeName(tags[i]);
        info[i].tagClass = tags[i]->m_tagClass;
    }
    SignalPluginEvent(GetInstance(), 11, 0);
    CSystemContextBase *system = GetSystemContext();
    system->vtable->HandleNewPageTagInfo(system, info, count);
    svFreeSafe(memory, info);
}
