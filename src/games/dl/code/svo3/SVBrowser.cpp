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
long handleInput(CPage *);
char *GetTagTypeName(SVTag *);
extern char svoBrowserPageIDTagName[];
void download___dupe3(SVDownloadManager *);
long HasEntries(FileDownloadQueueState *);
void GetNextEntry(FileDownloadQueueState *, char *, int, char *, int);
void DownloadFile(SVBrowserPrefix *, char *, char *);

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
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", SV_IKS_Malloc);

SECTION(SV_IKS_Free) void SV_IKS_Free(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

SECTION(SetupTargetInfo) void SetupTargetInfo(SVBrowserPrefix *browser, SVTargetInfo *target)
{
    browser->m_targetInfo.targetType = target->targetType;
    unsigned int length = 64;
    if (target->targetType == 1) length = 20;
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
    CSystemContextBase *system = contexts->systemContext;
    CDrawContextBase *draw = contexts->drawContext;
    CAudioContextBaseState *audio = contexts->audioContext;
    CMemoryContextBaseState *memory = contexts->memoryContext;
    CInputContextBaseState *input = contexts->inputContext;
    instance->m_pAltSystemContext = system;
    instance->m_pAltDrawContext = draw;
    instance->m_pAltAudioContext = audio;
    instance->m_pAltMemoryContext = memory;
    instance->m_pAltInputContext = input;
}

long BrowserIsIdle(SVBrowserPrefix *browser);
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", BrowserIsIdle);

SECTION(SetExternalIPAddress) void SetExternalIPAddress(SVBrowserPrefix *browser, char *ip)
{
    if (!ip) __SVO_Assert_Handler(svoBrowserSource, 0x250);
    svstrncpy(browser->m_loginInfo.ExternalIP, ip, 16);
}

SECTION(GetLoginInfo) void GetLoginInfo(SVBrowserPrefix *browser, char **user, char **password, int *account, char **ip)
{
    int id = browser->m_loginInfo.MediusAccountID;
    *user = browser->m_loginInfo.MediusUserName;
    *account = id;
    *password = browser->m_loginInfo.MediusPassWord;
    *ip = browser->m_loginInfo.ExternalIP;
}

SECTION(SetLogout) void SetLogout(SVBrowserPrefix *browser)
{
    browser->m_bLogout = 1;
}

SECTION(ExitOnline) void ExitOnline(SVBrowserPrefix *browser, long force)
{
    if (svoBrowserInstance) {
        FreeResources(browser);
        if (force) RTCommDestroy(browser);
    }
}

SECTION(IsActive) long IsActive(SVBrowserPrefix *browser)
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
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", InitServerInfo);

SECTION(InitInitializeParams) void InitInitializeParams(SVInitializeParams *params)
{
    params->iShouldListenForAuthoringToolPort = 0;
    params->downloadBufferSize = 0x80000;
    params->mainContextData = 0;
    params->altContextData = 0;
    params->eURL = 0;
    params->serverInfo = 0;
    params->a_pPersistentData = 0;
    params->headerVersion = 0;
    params->defaultButtonMap = 0;
    params->targetInfo = 0;
}

SECTION(SignalPluginEvent) void SignalPluginEvent(SVBrowserPrefix *browser, int event, SVTag *sender)
{
    AddMessage(browser->m_pPluginManager, sender, event);
}

void InitalizePluginManagerAndPlugins(SVBrowserPrefix *browser);
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", InitalizePluginManagerAndPlugins);

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
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", URIStoreFind);

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
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", reset);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", DeInitURISchemas);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", DownloadFile);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", DrawPages);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", FreeResources);

extern "C" SECTION(GetPageName) char *GetPageName(SVBrowserPrefix *browser)
{
    CPage *main = svoBrowserInstance->m_pMainPage;
    if (!main) return 0;
    CPage *popup = svoBrowserInstance->m_pPopupPage;
    if (!popup) return 0;
    SVTag **tags = (popup->m_bIsActive ? popup : main)->m_pFrontDisplayBuffer->tagList;
    for (int i = 0; i < 256 && tags[i]; ++i) {
        char *name = GetTagTypeName(tags[i]);
        if (!name) __SVO_Assert_Handler(svoBrowserSource, 0x71C);
        if (strncmp(name, svoBrowserPageIDTagName, 9) == 0)
            return tags[i]->vtable->GetTagName(tags[i]);
    }
    return 0;
}

extern "C" SECTION(HandleInputPages) void HandleInputPages(SVBrowserPrefix *browser, CPage *page)
{
    long handled = handleInput(page);
    SVTagModuleState **entry = getInstance___dupe3()->m_modules;
    if (handled && *entry) {
        int count = 0;
        do {
            SVTagModuleState *module = *entry++;
            ++count;
            handled = module->vtable->HandleInput(module, page);
            if (count >= 128 || !handled) break;
        } while (*entry);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", Initialize___dupe4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", InitURISchemas);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", LoadStatePostGameFromPersistentData___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", ReturnFromGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", RTCommInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", ShowVKB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", Update___dupe109);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVBrowser", UpdateDownloadManager);
