#include "SVBrowser.h"
#include "SVPersistentData.h"
#include "SVDownloadManager.h"
#include "CMemoryContextBase.h"
#include "CConfig.h"
#include "CPage.h"
#include "CError.h"
#include "URISchemeMgr.h"
#include "string.h"
#include "stdio.h"
extern "C" {
extern SVBrowserPrefix *svoBrowserInstance;
extern char svoBrowserSource[];
extern char svoBrowserAllocationSource[];
extern char svoBrowserConfigFilename[];
extern char svoBrowserConfigHeader[];
extern char svoBrowserServerFormat[];
extern char svoBrowserPersistentFormat[];
void DefaultInit(SVBrowserPrefix *);
char *SV_CheckVersion(char *);
void RTCommInit(SVBrowserPrefix *);
void SetAlternateContexts(SVBrowserPrefix *, CAllContextData *);
void SetupTargetInfo(SVBrowserPrefix *, SVTargetInfo *);
void *SV_IKS_Malloc(unsigned int);
void SV_IKS_Free(void *);
void iks_set_malloc_func(void *(*)(unsigned int));
void iks_set_free_func(void (*)(void *));
void InitURISchemas(SVBrowserPrefix *);
void *FileDownloadQueueNew(unsigned int) __asm__("operator.new___dupe14");
void FileDownloadQueue(FileDownloadQueueState *);
void *PageNew(unsigned int) __asm__("operator.new___dupe3");
void PageConstruct(CPage *, char *, int, int) __asm__("CPage");
void *DownloadManagerNew(unsigned int) __asm__("operator.new___dupe13");
void BrowserDownloadManagerConstruct(SVDownloadManagerState *, char *, char *, char *, int, CPage *, CMemoryContextBaseState *, unsigned int) __asm__("SVDownloadManager");
void RegisterCommonTagModules();
void Activate(SVBrowserPrefix *);
void InitalizePluginManagerAndPlugins(SVBrowserPrefix *);
void *ChronographNew(unsigned int) __asm__("operator.new___dupe5");
int ReturnFromGame(SVBrowserPrefix *, SVPersistentData *);
void FreeResources(SVBrowserPrefix *);
}

#include "SVBrowser.h"
#include "RTCommSock.h"
#include "string.h"
extern "C" {
void rt_comm_startup();
void rt_comm_update();
void rt_comm_get_local_ip(RTLinkAddress *);
void rt_comm_linkaddress_tostr(char *, RTLinkAddress);
}



#include "SVBrowser.h"
#include "SVTag.h"
#include "SVDownloadManager.h"
#include "CPage.h"
#include "CMemoryContextBase.h"
#include "CDrawContextBase.h"
#include "CHttp.h"
#include "HttpSecure.h"
#include "URISchemeMgr.h"
#include "CError.h"
#include "string.h"


extern "C" {
extern SVBrowserPrefix *svoBrowserInstance;
extern char svoBrowserSource[];
extern HttpState *svoBrowserHttp;
extern HttpSecureState *svoBrowserHttps;
CMemoryContextBaseState *GetMemoryContext();
CDrawContextBase *GetDrawContext();
void *PluginManagerNew(unsigned int) __asm__("operator.new___dupe11");
void *BrowserHttpNew(unsigned int, CMemoryContextBaseState *) __asm__("operator.new___dupe4");
void *BrowserHttpsNew(unsigned int, CMemoryContextBaseState *) __asm__("operator.new___dupe2");
void Http(HttpState *, CMemoryContextBaseState *, int);
void HttpSecure(HttpSecureState *, CMemoryContextBaseState *, int);
char *find___dupe2(FileDownloadQueueState *, char *);
int doRequest___dupe4(SVDownloadManager *, char *, char *, int, char *);
void download___dupe3(SVDownloadManager *);
int HasEntries(FileDownloadQueueState *);
void GetNextEntry(FileDownloadQueueState *, char *, int, char *, int);
void draw(CPage *, int);
void draw___dupe2(SVDownloadManager *);
}

extern "C" { extern char gTagNotSetStr[]; }

#include "SVOString.h"


extern "C" CInputContextBaseState *GetInputContext();

#include "SVPersistentData.h"
extern "C" {
void setPageState(CPage *, int);
void CalculatePersistentDataMd5Sum(SVBrowserPrefix *, SVPersistentData *, char *, int);
int LoadStatePostGameFromPersistentData(CPage *, SVPersistentData *);
}

#include "CCookie.h"
#include "SVTagModuleList.h"

extern "C" {
void DestroyInTransitionArray(CPage *);
void DestroyPostTransitionArray(CPage *);
void DestroyPreTransitionArray(CPage *);
void shutdown(CPage *);
void _CPage(CPage *, unsigned int);
void FreeResources___dupe54(FileDownloadQueueState *);
void freeResources___dupe4(SVDownloadManager *, int);
void DeInitializePluginManagerAndPluggins(SVBrowserPrefix *);
}

#include "LoginTagModule.h"
#include "CSystemContextBase.h"


extern "C" {
int IsActive(SVBrowserPrefix *);
int download(CPage *);
LoginTagModuleState *getInstance___dupe27();
int UnhandledLoginResponseExists(LoginTagModuleState *, int *);
void DoFrameUpdates(SVBrowserPrefix *);
int okToNavigate___dupe4(SVDownloadManager *);
void HandleInputPages(SVBrowserPrefix *, CPage *);
void HandleUpdatePages(SVBrowserPrefix *, CPage *);
}

extern "C" { int UpdateDownloadManager(SVBrowserPrefix *); void DrawPages(SVBrowserPrefix *, CPage **, int); void DeInitURISchemas(SVBrowserPrefix *); }

#include "SVTag.h"
#include "md5.h"
#include "SVDownloadManager.h"
#include "SVTagModuleList.h"
#include "CMemoryContextBase.h"
#include "SVTagModule.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SVBrowser_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVBrowser.h"
#include "CPage.h"
#include "SVOString.h"
#include "CError.h"
#include <string.h>

extern "C" {
extern SVBrowserPrefix *svoBrowserInstance;
extern char svoBrowserSource[];
extern char gTagNotSetStr[];
void reset(DownloadThrobberInfo *info);
void FreeResources(SVBrowserPrefix *browser);
void RTCommDestroy(SVBrowserPrefix *browser);
void frameUpdate(CPage *page);
void handleUpdate(CPage *page);
void *PluginManagerNew(unsigned int size) __asm__("operator.new___dupe11");
void add___dupe2(FileDownloadQueueState *queue, char *lookup, char *value);
void rt_comm_update(void);
void rt_comm_shutdown(void);

extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoBrowserSource[];

}
extern "C" {
int handleInput(CPage *);
char *GetTagTypeName(SVTag *);
extern char svoBrowserPageIDTagName[];
void download___dupe3(SVDownloadManager *);
int HasEntries(FileDownloadQueueState *);
void GetNextEntry(FileDownloadQueueState *, char *, int, char *, int);
int DownloadFile(SVBrowserPrefix *, char *, char *);

}
#define SECTION(name) __attribute__((section(".svo_SVBrowser_" #name)))

SECTION(DefaultInit) void DefaultInit(SVBrowserPrefix *browser)
{
    browser->m_bUseDownloadManger = 1;
    browser->m_pPopupPage = 0;
    browser->m_pMainPage = 0;
    browser->m_pDownloadManager = 0;
    browser->m_bCreateGameRequested = 0;
    browser->m_pTimer = 0;
    browser->m_pFileDownloadQueue = 0;
    reset(&browser->m_downloadThrobberInfo);
    browser->m_bUseDownloadManger = 1;
    memset(&browser->m_targetInfo, 0, 0x4C);
    browser->m_severity = 0xFF;
    browser->m_category = 0xFFFF;
}

SECTION(GetInstance) SVBrowserPrefix *GetInstance(void)
{
    return svoBrowserInstance;
}

SECTION(GetMemoryContext) CMemoryContextBaseState *GetMemoryContext(void)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x6D);
    if (!svoBrowserInstance->m_pMemoryContext) __SVO_Assert_Handler(svoBrowserSource, 0x6E);
    return svoBrowserInstance->m_pMemoryContext;
}

SECTION(GetAltMemoryContext) CMemoryContextBaseState *GetAltMemoryContext(void)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x74);
    if (!svoBrowserInstance->m_pAltMemoryContext) __SVO_Assert_Handler(svoBrowserSource, 0x75);
    return svoBrowserInstance->m_pAltMemoryContext;
}

SECTION(GetAltDrawContext) CDrawContextBase *GetAltDrawContext(void)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x8F);
    if (!svoBrowserInstance->m_pAltDrawContext) __SVO_Assert_Handler(svoBrowserSource, 0x90);
    return svoBrowserInstance->m_pAltDrawContext;
}

SECTION(GetInputContext) CInputContextBaseState *GetInputContext(void)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x96);
    if (!svoBrowserInstance->m_pInputContext) __SVO_Assert_Handler(svoBrowserSource, 0x97);
    return svoBrowserInstance->m_pInputContext;
}

SECTION(GetAltInputContext) CInputContextBaseState *GetAltInputContext(void)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x9D);
    if (!svoBrowserInstance->m_pAltInputContext) __SVO_Assert_Handler(svoBrowserSource, 0x9E);
    return svoBrowserInstance->m_pAltInputContext;
}

SECTION(GetAudioContext) CAudioContextBaseState *GetAudioContext(void)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0xA4);
    if (!svoBrowserInstance->m_pAudioContext) __SVO_Assert_Handler(svoBrowserSource, 0xA5);
    return svoBrowserInstance->m_pAudioContext;
}

SECTION(GetAltAudioContext) CAudioContextBaseState *GetAltAudioContext(void)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0xAB);
    if (!svoBrowserInstance->m_pAltAudioContext) __SVO_Assert_Handler(svoBrowserSource, 0xAC);
    return svoBrowserInstance->m_pAltAudioContext;
}

SECTION(GetSystemContext) CSystemContextBase *GetSystemContext(void)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0xB2);
    if (!svoBrowserInstance->m_pSystemContext) __SVO_Assert_Handler(svoBrowserSource, 0xB3);
    return svoBrowserInstance->m_pSystemContext;
}

SECTION(GetAltSystemContext) CSystemContextBase *GetAltSystemContext(void)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0xB9);
    if (!svoBrowserInstance->m_pAltSystemContext) __SVO_Assert_Handler(svoBrowserSource, 0xBA);
    return svoBrowserInstance->m_pAltSystemContext;
}

SECTION(GetDrawContext) CDrawContextBase *GetDrawContext(void)
{
    if (!svoBrowserInstance) return 0;
    if (svoBrowserInstance->m_bShowVKB) {
        if (!svoBrowserInstance->m_pVKBDrawContext) __SVO_Assert_Handler(svoBrowserSource, 0x83);
        return svoBrowserInstance->m_pVKBDrawContext;
    }
    if (!svoBrowserInstance->m_pDrawContext) __SVO_Assert_Handler(svoBrowserSource, 0x88);
    return svoBrowserInstance->m_pDrawContext;
}

void *SV_IKS_Malloc(unsigned int size);
extern "C" SECTION(SV_IKS_Malloc) void * SV_IKS_Malloc(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0x4, 0xC0, svoBrowserSource);
}

SECTION(SV_IKS_Free) void SV_IKS_Free(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

SECTION(SetupTargetInfo) void SetupTargetInfo(SVBrowserPrefix *browser, SVTargetInfo *target)
{
    browser->m_targetInfo.targetType = target->targetType;
    unsigned int length = 64;
    if (browser->m_targetInfo.targetType == 1) length = 20;
    else __SVO_Assert_Handler(svoBrowserSource, 0x106);
    memcpy(browser->m_targetInfo.targetSpecialID, target->targetSpecialID, length);
    if (browser->m_targetInfo.targetSpecialID[length]) __SVO_Assert_Handler(svoBrowserSource, 0x10C);
    if (strlen(browser->m_targetInfo.targetSpecialID) > 64) __SVO_Assert_Handler(svoBrowserSource, 0x10D);
    browser->m_targetInfo.targetAppID = target->targetAppID;
}

SECTION(SetAlternateContexts) void SetAlternateContexts(SVBrowserPrefix *browser, CAllContextData *contexts)
{
    if (!contexts->drawContext || !contexts->inputContext || !contexts->memoryContext || !contexts->audioContext || !contexts->systemContext)
        __SVO_Assert_Handler(svoBrowserSource, 0x1FF);
    SVBrowserPrefix *instance = svoBrowserInstance;
    CDrawContextBase *draw = contexts->drawContext;
    CAudioContextBaseState *audio = contexts->audioContext;
    CMemoryContextBaseState *memory = contexts->memoryContext;
    CInputContextBaseState *input = contexts->inputContext;
    CSystemContextBase *system = contexts->systemContext;
    instance->m_pAltDrawContext = draw;
    instance->m_pAltAudioContext = audio;
    instance->m_pAltMemoryContext = memory;
    instance->m_pAltInputContext = input;
    instance->m_pAltSystemContext = system;
}

int BrowserIsIdle(SVBrowserPrefix *browser);
extern "C" SECTION(BrowserIsIdle) int BrowserIsIdle(SVBrowserPrefix *browser)
{
    int idle = 0;
    if (!browser->m_pMainPage->m_state) idle = !browser->m_pPopupPage->m_state;
    return idle;
}

SECTION(SetExternalIPAddress) void SetExternalIPAddress(SVBrowserPrefix *browser, char *ip)
{
    if (!ip) __SVO_Assert_Handler(svoBrowserSource, 0x250);
    svstrncpy(browser->m_loginInfo.ExternalIP, ip, 16);
}

SECTION(GetLoginInfo) void GetLoginInfo(SVBrowserPrefix *browser, char **user, char **password, int *account, char **ip)
{
    *user = browser->m_loginInfo.MediusUserName;
    *password = browser->m_loginInfo.MediusPassWord;
    *ip = browser->m_loginInfo.ExternalIP;
    *account = browser->m_loginInfo.MediusAccountID;
}

SECTION(SetLogout) void SetLogout(SVBrowserPrefix *browser)
{
    browser->m_bLogout = 1;
}

SECTION(ExitOnline) void ExitOnline(SVBrowserPrefix *browser, int force)
{
    if (svoBrowserInstance) {
        FreeResources(browser);
        if (force) RTCommDestroy(browser);
    }
}

SECTION(IsActive) int IsActive(SVBrowserPrefix *browser)
{
    return browser->m_bIsActive;
}

SECTION(Activate) void Activate(SVBrowserPrefix *browser)
{
    browser->m_bIsActive = 1;
}

SECTION(DoFrameUpdates) void DoFrameUpdates(SVBrowserPrefix *browser)
{
    frameUpdate(browser->m_pMainPage);
    frameUpdate(browser->m_pPopupPage);
}

SECTION(HandleUpdatePages) void HandleUpdatePages(SVBrowserPrefix *browser, CPage *page)
{
    handleUpdate(page);
}

void InitServerInfo(SVServerInfo *info);
extern "C" SECTION(InitServerInfo) void InitServerInfo(SVServerInfo *info)
{
    info->port = -1;
    memset(info->serverName, 0, 257);
    memset(info->firstPage, 0, 257);
}

SECTION(InitInitializeParams) void InitInitializeParams(SVInitializeParams *params)
{
    params->downloadBufferSize = 0x80000;
    params->mainContextData = 0;
    params->altContextData = 0;
    params->eURL = 0;
    params->serverInfo = 0;
    params->a_pPersistentData = 0;
    params->headerVersion = 0;
    params->defaultButtonMap = 0;
    params->targetInfo = 0;
    params->iShouldListenForAuthoringToolPort = 0;
}

SECTION(SignalPluginEvent) void SignalPluginEvent(SVBrowserPrefix *browser, int event, SVTag *sender)
{
    AddMessage(browser->m_pPluginManager, sender, event);
}

void InitalizePluginManagerAndPlugins(SVBrowserPrefix *browser);
SECTION(InitalizePluginManagerAndPlugins) void InitalizePluginManagerAndPlugins(SVBrowserPrefix *browser)
{
    SVBrowserPrefix *instance = svoBrowserInstance;
    CPluginManagerState *manager = (CPluginManagerState *)PluginManagerNew(0x58);
    CPluginManager(manager);
    instance->m_pPluginManager = manager;
    if (!svoBrowserInstance->m_pPluginManager) __SVO_Assert_Handler(svoBrowserSource, 0x5DE);
}

SECTION(DeInitializePluginManagerAndPluggins) void DeInitializePluginManagerAndPluggins(SVBrowserPrefix *browser)
{
    if (svoBrowserInstance->m_pPluginManager) {
        CMemoryContextBaseState *memory = GetMemoryContext();
        svFreeSafe(memory, svoBrowserInstance->m_pPluginManager);
        svoBrowserInstance->m_pPluginManager = 0;
    }
}

SECTION(RemovePluginMgrMessages) void RemovePluginMgrMessages(SVBrowserPrefix *browser)
{
    EmptyMessageQueue(svoBrowserInstance->m_pPluginManager);
}

SECTION(URIStoreAdd) void URIStoreAdd(char *lookup, char *value)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x6AD);
    if (!svoBrowserInstance->m_pURIStore) __SVO_Assert_Handler(svoBrowserSource, 0x6AE);
    add(svoBrowserInstance->m_pURIStore, lookup, value);
}

char *URIStoreFind(char *lookup);
SECTION(URIStoreFind) char *URIStoreFind(char *lookup)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x6B4);
    if (!svoBrowserInstance->m_pURIStore) __SVO_Assert_Handler(svoBrowserSource, 0x6B5);
    return find(svoBrowserInstance->m_pURIStore, lookup);
}

SECTION(FileDownloadQueueAdd) void FileDownloadQueueAdd(char *id, char *path)
{
    if (!svoBrowserInstance->m_bUseDownloadManger) {
        SetErrorCode(0x1F);
        if (!svoBrowserInstance->m_bUseDownloadManger) __SVO_Assert_Handler(svoBrowserSource, 0x6BE);
        return;
    }
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x6C2);
    if (!svoBrowserInstance->m_pFileDownloadQueue) __SVO_Assert_Handler(svoBrowserSource, 0x6C3);
    add___dupe2(svoBrowserInstance->m_pFileDownloadQueue, id, path);
}

void reset(DownloadThrobberInfo *info);
SECTION(reset) void reset(DownloadThrobberInfo *info)
{
    info->tagClass = gTagNotSetStr;
    info->width = 150.0f;
    info->x = 245.0f;
    info->y = 20.0f;
    info->height = 25.0f;
    info->tagid = 0;
}

SECTION(RTCommDestroy) void RTCommDestroy(SVBrowserPrefix *browser)
{
    rt_comm_update();
    rt_comm_shutdown();
}

}

extern "C" SECTION(CalculatePersistentDataMd5Sum) void CalculatePersistentDataMd5Sum(SVBrowserPrefix *browser, SVPersistentData *data, char *output, int size)
{
    if (size != 33) __SVO_Assert_Handler(svoBrowserSource, 0x3CE);
    md5_context context;
    unsigned char digest[16];
    memset(&context, 0, sizeof(context));
    memset(digest, 0, sizeof(digest));
    md5_starts(&context);
    md5_update(&context, (unsigned char *)data, 5000);
    md5_finish(&context, digest);
    md5_hex(digest, output);
}

extern "C" SECTION(DeInitURISchemas) void DeInitURISchemas(SVBrowserPrefix *browser)
{
    shutdown___dupe2(Get());
    if (svoBrowserHttp) {
        GetMemoryContext();
        if (svoBrowserHttp) ((const BrowserProviderVtable *)svoBrowserHttp->vtable)->destroy(svoBrowserHttp, 3);
        svoBrowserHttp = 0;
    }
    if (svoBrowserHttps) {
        GetMemoryContext();
        if (svoBrowserHttps) ((const BrowserProviderVtable *)svoBrowserHttps->base.vtable)->destroy(svoBrowserHttps, 3);
        svoBrowserHttps = 0;
    }
}

extern "C" SECTION(DownloadFile) int DownloadFile(SVBrowserPrefix *browser, char *path, char *id)
{
    if (!path) __SVO_Assert_Handler(svoBrowserSource, 0x427);
    if (!browser->m_bUseDownloadManger) {
        SetErrorCode(0x1F);
        if (!browser->m_bUseDownloadManger) __SVO_Assert_Handler(svoBrowserSource, 0x42B);
        return 0;
    }
    char *stored = find___dupe2(browser->m_pFileDownloadQueue, path);
    if (stored) return doRequest___dupe4(browser->m_pDownloadManager, stored, 0, 0, id);
    return doRequest___dupe4(browser->m_pDownloadManager, path, 0, 0, id);
}

extern "C" SECTION(DrawPages) void DrawPages(SVBrowserPrefix *browser, CPage **activePage, int drawTags)
{
    if (browser->m_pMainPage->m_bIsActive) {
        if (!*activePage) *activePage = browser->m_pMainPage;
        draw(browser->m_pMainPage, 1);
    }
    if (browser->m_pPopupPage->m_bIsActive) {
        *activePage = browser->m_pPopupPage;
        draw(browser->m_pPopupPage, 1);
    }
    if (browser->m_bUseDownloadManger && browser->m_pDownloadManager) draw___dupe2(browser->m_pDownloadManager);
    if (!BrowserIsIdle(browser)) {
        CDrawContextBase *drawContext = GetDrawContext();
        drawContext->vtable->DrawDownloadThrobber(drawContext, browser->m_downloadThrobberInfo.tagid,
            browser->m_downloadThrobberInfo.x, browser->m_downloadThrobberInfo.y,
            browser->m_downloadThrobberInfo.width, browser->m_downloadThrobberInfo.height,
            browser->m_downloadThrobberInfo.tagClass);
    }
}

extern "C" SECTION(FreeResources) void FreeResources(SVBrowserPrefix *browser)
{
    DestroyInTransitionArray(browser->m_pMainPage);
    DestroyPostTransitionArray(browser->m_pMainPage);
    DestroyPreTransitionArray(browser->m_pMainPage);
    if (browser->m_pMainPage) {
        shutdown(browser->m_pMainPage);
        if (browser->m_pMainPage) _CPage(browser->m_pMainPage, 3);
        browser->m_pMainPage = 0;
    }
    if (browser->m_pPopupPage) {
        shutdown(browser->m_pPopupPage);
        if (browser->m_pPopupPage) _CPage(browser->m_pPopupPage, 3);
        browser->m_pPopupPage = 0;
    }
    DeInitURISchemas(browser);
    FreeResources___dupe45(browser->m_pURIStore);
    CMemoryContextBaseState *memory = GetMemoryContext();
    svFreeSafe(memory, browser->m_pURIStore);
    if (browser->m_bUseDownloadManger) {
        if (browser->m_pFileDownloadQueue) {
            FreeResources___dupe54(browser->m_pFileDownloadQueue);
            memory = GetMemoryContext();
            svFreeSafe(memory, browser->m_pFileDownloadQueue);
            browser->m_pFileDownloadQueue = 0;
        }
        freeResources___dupe4(browser->m_pDownloadManager, 0);
        SVDownloadManager *manager = browser->m_pDownloadManager;
        if (manager) {
            const BrowserManagerVtable *table = (const BrowserManagerVtable *)((SVDownloadManagerState *)manager)->base.vtable;
            table->destroy(manager, 3);
        }
        browser->m_pDownloadManager = 0;
    }
    freeResources___dupe3(getInstance(browser->m_pMemoryContext));
    FreeResources___dupe4(getInstance___dupe3());
    DeInitializePluginManagerAndPluggins(browser);
    if (browser->m_pTimer) _SVChronograph(browser->m_pTimer, 3);
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x2C8);
    memory = GetMemoryContext();
    if (!memory) __SVO_Assert_Handler(svoBrowserSource, 0x2CA);
    svFreeSafe(memory, svoBrowserInstance);
    svoBrowserInstance = 0;
}

extern "C" SECTION(GetPageName) char *GetPageName(SVBrowserPrefix *browser)
{
    CPage *main = svoBrowserInstance->m_pMainPage;
    CPage *popup;
    if (main && (popup = svoBrowserInstance->m_pPopupPage)) {
    SVTag **tags;
    if (popup->m_bIsActive) tags = popup->m_pFrontDisplayBuffer->tagList;
    else tags = main->m_pFrontDisplayBuffer->tagList;
    for (int i = 0; i < 256 && tags[i]; ++i) {
        char *name = GetTagTypeName(tags[i]);
        if (!name) __SVO_Assert_Handler(svoBrowserSource, 0x71C);
        if (strncmp(name, svoBrowserPageIDTagName, 9) == 0)
            return tags[i]->vtable->GetTagName(tags[i]);
    }
    }
    return 0;
}

extern "C" SECTION(HandleInputPages) void HandleInputPages(SVBrowserPrefix *browser, CPage *page)
{
    int i = 0;
    int handled = handleInput(page);
    SVTagModuleState **modules = getInstance___dupe3()->m_modules;
    for (; i < 128 && handled && modules[i]; i++) {
        SVTagModuleState *module = modules[i];
        handled = module->vtable->HandleInput(module, page);
    }
}

static inline char *ConfigIP(CConfigState *c) { if (!c->m_bFileRead) __SVO_Assert_Handler(svoBrowserConfigHeader, 0x23); return c->m_ip; }
static inline int ConfigPort(CConfigState *c) { if (!c->m_bFileRead) __SVO_Assert_Handler(svoBrowserConfigHeader, 0x2D); return c->m_port; }
static inline char *ConfigFirstPage(CConfigState *c) { if (!c->m_bFileRead) __SVO_Assert_Handler(svoBrowserConfigHeader, 0x37); return c->m_firstPage; }
extern "C" SECTION(Initialize___dupe4) SVBrowserPrefix *Initialize___dupe4(SVInitializeParams *params)
{
    SetErrorCode(0);
    svoBrowserInstance = (SVBrowserPrefix *)svAllocSafe(params->mainContextData->memoryContext, 0x3140, 0, 0, svoBrowserAllocationSource);
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x134);
    if (!params->mainContextData || !params->mainContextData->drawContext || !params->mainContextData->inputContext || !params->mainContextData->memoryContext || !params->mainContextData->audioContext || !params->mainContextData->systemContext) __SVO_Assert_Handler(svoBrowserSource, 0x13B);
    DefaultInit(svoBrowserInstance);
    svoBrowserInstance->m_pDrawContext = params->mainContextData->drawContext;
    svoBrowserInstance->m_pAudioContext = params->mainContextData->audioContext;
    svoBrowserInstance->m_pMemoryContext = params->mainContextData->memoryContext;
    svoBrowserInstance->m_pInputContext = params->mainContextData->inputContext;
    svoBrowserInstance->m_pSystemContext = params->mainContextData->systemContext;
    svoBrowserInstance->m_pVKBDrawContext = params->mainContextData->drawContext;
    SV_CheckVersion(params->headerVersion);
    RTCommInit(svoBrowserInstance);
    if (params->altContextData->memoryContext != params->mainContextData->memoryContext) __SVO_Assert_Handler(svoBrowserSource, 0x153);
    params->altContextData->memoryContext = params->mainContextData->memoryContext;
    SetAlternateContexts(svoBrowserInstance, params->altContextData);
    svoBrowserInstance->m_pCurrentTextEditableTag = 0;
    svoBrowserInstance->m_textEditPosition = 0;
    memset(svoBrowserInstance->m_textBuffer, 0, 0x3000);
    svoBrowserInstance->m_textMaxBytes = 0;
    svoBrowserInstance->m_textMaxChars = 0;
    svoBrowserInstance->m_textIsPassword = 0;
    if (!params->targetInfo) __SVO_Assert_Handler(svoBrowserSource, 0x163);
    SetupTargetInfo(svoBrowserInstance, params->targetInfo);
    iks_set_malloc_func(SV_IKS_Malloc);
    iks_set_free_func(SV_IKS_Free);
    CConfigState config;
    char firstPage[272];
    CConfig(&config);
    switch (params->eURL) {
    case 1: {
        loadConfigurationFile(&config, svoBrowserConfigFilename);
        char *ip = ConfigIP(&config);
        int port = ConfigPort(&config);
        char *fp = ConfigFirstPage(&config);
        sprintf(firstPage, svoBrowserServerFormat, ip, port, fp);
        break;
    }
    case 2:
        if (!params->a_pPersistentData) __SVO_Assert_Handler(svoBrowserSource, 0x183);
        sprintf(firstPage, svoBrowserPersistentFormat, params->a_pPersistentData->homeURI);
        break;
    case 3:
        sprintf(firstPage, svoBrowserServerFormat, params->serverInfo->serverName, params->serverInfo->port, params->serverInfo->firstPage);
        break;
    default:
        __SVO_Assert_Handler(svoBrowserSource, 0x190);
    }
    init___dupe2(Get(), svoBrowserInstance->m_pMemoryContext);
    InitURISchemas(svoBrowserInstance);
    SVBrowserPrefix *inst = svoBrowserInstance;
    inst->m_pMainPage = 0;
    inst->m_pPopupPage = 0;
    inst->m_pDownloadManager = 0;
    URIStoreState *store = (URIStoreState *)URIStoreNew(0x204);
    URIStore(store);
    inst->m_pURIStore = store;
    SVBrowserPrefix *browser = svoBrowserInstance;
    if (browser->m_bUseDownloadManger) {
        FileDownloadQueueState *queue = (FileDownloadQueueState *)FileDownloadQueueNew(0x28);
        FileDownloadQueue(queue);
        browser->m_pFileDownloadQueue = queue;
        if (!svoBrowserInstance->m_pFileDownloadQueue) __SVO_Assert_Handler(svoBrowserSource, 0x1A0);
    }
    if (!svoBrowserInstance->m_pURIStore) __SVO_Assert_Handler(svoBrowserSource, 0x1AC);
    browser = svoBrowserInstance;
    CPage *page = (CPage *)PageNew(0x637C);
    PageConstruct(page, firstPage, 0, -1);
    browser->m_pMainPage = page;
    if (!svoBrowserInstance->m_pMainPage) __SVO_Assert_Handler(svoBrowserSource, 0x1B4);
    if (GetErrorCode()) return 0;
    browser = svoBrowserInstance;
    page = (CPage *)PageNew(0x637C);
    PageConstruct(page, 0, 1, -1);
    browser->m_pPopupPage = page;
    if (!svoBrowserInstance->m_pPopupPage) __SVO_Assert_Handler(svoBrowserSource, 0x1C4);
    browser = svoBrowserInstance;
    if (browser->m_bUseDownloadManger) {
        SVDownloadManagerState *manager = (SVDownloadManagerState *)DownloadManagerNew(0x8CD8);
        BrowserDownloadManagerConstruct(manager, firstPage, 0, 0, 0, svoBrowserInstance->m_pMainPage, svoBrowserInstance->m_pMemoryContext, params->downloadBufferSize);
        browser->m_pDownloadManager = (SVDownloadManager *)manager;
        if (!svoBrowserInstance->m_pDownloadManager) __SVO_Assert_Handler(svoBrowserSource, 0x1C9);
    }
    RegisterCommonTagModules();
    Activate(svoBrowserInstance);
    svoBrowserInstance->m_bOkToNavigate = 1;
    svoBrowserInstance->m_bLogout = 0;
    svoBrowserInstance->m_bShowVKB = 0;
    svoBrowserInstance->m_bIsXMPPActive = 0;
    InitalizePluginManagerAndPlugins(svoBrowserInstance);
    browser = svoBrowserInstance;
    SVChronographState *timer = (SVChronographState *)ChronographNew(0x10);
    SVChronograph(timer, 0);
    browser->m_pTimer = timer;
    DefineDefaultButtonMap(svoBrowserInstance->m_pInputContext, params->defaultButtonMap);
    SetDefaultButtonMap(svoBrowserInstance->m_pInputContext);
    switch (params->eURL) {
    case 2:
        if (!ReturnFromGame(GetInstance(), params->a_pPersistentData)) {
            FreeResources(GetInstance());
            svoBrowserInstance = 0;
        }
        break;
    case 1:
    case 3:
        break;
    default:
        __SVO_Assert_Handler(svoBrowserSource, 0x1F5);
    }
    return svoBrowserInstance;
}

extern "C" SECTION(InitURISchemas) void InitURISchemas(SVBrowserPrefix *browser)
{
    CMemoryContextBaseState *memory = GetMemoryContext();
    if (!svoBrowserHttp) {
        HttpState *http = (HttpState *)BrowserHttpNew(0x8AC4, memory);
        Http(http, memory, 1);
        svoBrowserHttp = http;
        ((const BrowserProviderVtable *)http->vtable)->registerSchemes(http);
    }
    if (!svoBrowserHttps) {
        HttpSecureState *https = (HttpSecureState *)BrowserHttpsNew(0x9B00, memory);
        HttpSecure(https, memory, 1);
        svoBrowserHttps = https;
        ((const BrowserProviderVtable *)https->base.vtable)->registerSchemes(https);
    }
}

extern "C" SECTION(LoadStatePostGameFromPersistentData___dupe3) int LoadStatePostGameFromPersistentData___dupe3(SVBrowserPrefix *browser, SVPersistentData *persist)
{
    if (!browser->m_pMainPage) __SVO_Assert_Handler(svoBrowserSource, 0x3E8);
    setPageState(browser->m_pMainPage, 1);
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x3EE);
    char hash[48];
    CalculatePersistentDataMd5Sum(browser, persist, hash, 33);
    if (strncmp(hash, persist->szMD5Hash, 33)) return 0;
    LoadInFromMemory(browser->m_pURIStore, persist->szURIStore, 0x1000);
    LoadStatePostGameFromPersistentData(browser->m_pMainPage, persist);
    LoadStatePostGameFromPersistentData___dupe4(Get(), persist);
    persist->SVOGameID = 0;
    return 1;
}

extern "C" SECTION(ReturnFromGame) int ReturnFromGame(SVBrowserPrefix *browser, SVPersistentData *persist)
{
    return LoadStatePostGameFromPersistentData___dupe3(browser, persist);
}

extern "C" SECTION(RTCommInit) void RTCommInit(SVBrowserPrefix *browser)
{
    RTLinkAddress address;
    char text[16];
    rt_comm_startup();
    rt_comm_update();
    rt_comm_get_local_ip(&address);
    rt_comm_linkaddress_tostr(text, address);
}

extern "C" SECTION(ShowVKB) void ShowVKB(SVBrowserPrefix *browser, SVTag *tag)
{
    browser->m_bShowVKB = 1;
    browser->m_pCurrentTextEditableTag = tag;
    char *text = ((const BrowserEditableVtable *)tag->vtable)->GetText(tag);
    if (!text) __SVO_Assert_Handler(svoBrowserSource, 0x57E);
    int password = ((const BrowserEditableVtable *)tag->vtable)->IsPassword(tag);
    svstrncpy(browser->m_textBuffer, text, strlen(text) + 1);
    browser->m_textMaxBytes = ((const BrowserEditableVtable *)tag->vtable)->GetMaxLengthBytes(tag);
    int chars = ((const BrowserEditableVtable *)tag->vtable)->GetMaxLengthUTF8Chars(tag);
    browser->m_textIsPassword = password;
    browser->m_textMaxChars = chars;
    browser->m_textEditPosition = ((const BrowserEditableVtable *)tag->vtable)->GetEditPosition(tag);
    CInputContextBaseState *input = GetInputContext();
    ((const BrowserInputVtable *)input->vtable)->SeedVKBBuffer(input, text);
}

extern "C" SECTION(Update___dupe109) int Update___dupe109(SVBrowserPrefix *browser, int updateType)
{
    int error = GetErrorCode();
    if (error) return error;
    if (!browser->m_pMainPage || !browser->m_pPopupPage) __SVO_Assert_Handler(svoBrowserSource, 0x4E6);
    EnsureCleanBlocks(GetMemoryContext());
    if (IsActive(browser)) {
        CPage *active = 0;
        int popupState = download(browser->m_pPopupPage);
        int mainState = download(browser->m_pMainPage);
        if (!popupState && !mainState) {
            int result = 1;
            if (UnhandledLoginResponseExists(getInstance___dupe27(), &result)) {
                if ((unsigned int)result > 1) __SVO_Assert_Handler(svoBrowserSource, 0x508);
                CSystemContextBase *system = GetSystemContext();
                ((BrowserSystemVtable *)system->vtable)->HandleLoginResponse(system, result);
            }
        }
        if (browser->m_bUseDownloadManger) UpdateDownloadManager(browser);
        DoFrameUpdates(browser);
        switch (updateType) {
        case 0:
            DrawPages(browser, &active, 1);
            if (browser->m_bOkToNavigate && active && (!browser->m_bUseDownloadManger || okToNavigate___dupe4(browser->m_pDownloadManager))) HandleInputPages(browser, active);
            Update___dupe112(browser->m_pPluginManager, 0);
            if (browser->m_bShowVKB) {
                CDrawContextBase *draw = browser->m_pVKBDrawContext;
                ((BrowserVKBVtable *)draw->vtable)->DrawVKB(draw);
            }
            break;
        case 1:
            DrawPages(browser, &active, 1);
            Update___dupe112(browser->m_pPluginManager, 1);
            if (browser->m_bShowVKB) {
                CDrawContextBase *draw = browser->m_pVKBDrawContext;
                ((BrowserVKBVtable *)draw->vtable)->DrawVKB(draw);
            }
            break;
        case 2:
            if (browser->m_pMainPage->m_bIsActive) active = browser->m_pMainPage;
            else if (browser->m_pPopupPage->m_bIsActive) active = browser->m_pPopupPage;
            if (browser->m_bOkToNavigate && active && (!browser->m_bUseDownloadManger || okToNavigate___dupe4(browser->m_pDownloadManager))) HandleInputPages(browser, active);
            Update___dupe112(browser->m_pPluginManager, 2);
            break;
        }
        if (browser->m_pMainPage) HandleUpdatePages(browser, browser->m_pMainPage);
        if (browser->m_pPopupPage) HandleUpdatePages(browser, browser->m_pPopupPage);
    }
    return EnsureCleanBlocks(GetMemoryContext());
}

extern "C" SECTION(UpdateDownloadManager) int UpdateDownloadManager(SVBrowserPrefix *browser)
{
    if (!browser->m_bUseDownloadManger) {
        SetErrorCode(31);
        if (!browser->m_bUseDownloadManger) __SVO_Assert_Handler(svoBrowserSource, 0x753);
        return 0;
    }
    if (browser->m_pDownloadManager) {
        download___dupe3(browser->m_pDownloadManager);
        if (!((SVDownloadManagerState *)browser->m_pDownloadManager)->m_state && HasEntries(browser->m_pFileDownloadQueue)) {
            char lookup[257];
            char value[257];
            GetNextEntry(browser->m_pFileDownloadQueue, lookup, 257, value, 257);
            DownloadFile(browser, lookup, value);
        }
    }
    return 1;
}
