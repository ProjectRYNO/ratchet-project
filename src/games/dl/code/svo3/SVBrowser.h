#ifndef SVBROWSER_H
#define SVBROWSER_H
#include "CAllContextData.h"
#include "SVURIStore.h"
#include "SVFileDownloadQueue.h"
#include "CPluginManager.h"

struct SVDownloadManager;
#include "SVChronograph.h"
typedef struct { // 0x18
    /* 0x00 */ unsigned int tagid;
    /* 0x04 */ float x;
    /* 0x08 */ float y;
    /* 0x0C */ float width;
    /* 0x10 */ float height;
    /* 0x14 */ char *tagClass;
} DownloadThrobberInfo;
typedef struct { // 0x4C
    /* 0x00 */ int targetType;
    /* 0x04 */ char targetSpecialID[65];
    /* 0x45 */ unsigned char padding45[3];
    /* 0x48 */ unsigned int targetAppID;
} SVTargetInfo;
typedef struct { // 0x54
    /* 0x00 */ char MediusUserName[32];
    /* 0x20 */ char MediusPassWord[32];
    /* 0x40 */ char ExternalIP[16];
    /* 0x50 */ int MediusAccountID;
} SVLoginInfo;
typedef struct { // 0x208
    /* 0x000 */ char serverName[257];
    /* 0x101 */ char firstPage[257];
    /* 0x202 */ unsigned char padding202[2];
    /* 0x204 */ int port;
} SVServerInfo;
struct SVPersistentData;
#include "CInputContextBase.h"
typedef struct { // 0x28
    /* 0x00 */ SVTargetInfo *targetInfo;
    /* 0x04 */ CAllContextData *mainContextData;
    /* 0x08 */ CAllContextData *altContextData;
    /* 0x0C */ int eURL;
    /* 0x10 */ SVServerInfo *serverInfo;
    /* 0x14 */ SVPersistentData *a_pPersistentData;
    /* 0x18 */ char *headerVersion;
    /* 0x1C */ SVButtonMap *defaultButtonMap;
    /* 0x20 */ unsigned int downloadBufferSize;
    /* 0x24 */ int iShouldListenForAuthoringToolPort;
} SVInitializeParams;
// Keep the established name while recovering fields beyond the old prefix.
typedef struct { // 0x3140
    /* 0x0000 */ DownloadThrobberInfo m_downloadThrobberInfo;
    /* 0x0018 */ int m_bOkToNavigate;
    /* 0x001C */ int m_bIsActive;
    /* 0x0020 */ int m_bLogout;
    /* 0x0024 */ int m_bShowVKB;
    /* 0x0028 */ int m_bIsXMPPActive;
    /* 0x002C */ SVTargetInfo m_targetInfo;
    /* 0x0078 */ CDrawContextBase *m_pDrawContext;
    /* 0x007C */ CDrawContextBase *m_pVKBDrawContext;
    /* 0x0080 */ CInputContextBaseState *m_pInputContext;
    /* 0x0084 */ CMemoryContextBaseState *m_pMemoryContext;
    /* 0x0088 */ CAudioContextBaseState *m_pAudioContext;
    /* 0x008C */ CSystemContextBase *m_pSystemContext;
    /* 0x0090 */ CDrawContextBase *m_pAltDrawContext;
    /* 0x0094 */ CInputContextBaseState *m_pAltInputContext;
    /* 0x0098 */ CMemoryContextBaseState *m_pAltMemoryContext;
    /* 0x009C */ CAudioContextBaseState *m_pAltAudioContext;
    /* 0x00A0 */ CSystemContextBase *m_pAltSystemContext;
    /* 0x00A4 */ CPage *m_pMainPage;
    /* 0x00A8 */ CPage *m_pPopupPage;
    /* 0x00AC */ SVDownloadManager *m_pDownloadManager;
    /* 0x00B0 */ int m_textMaxBytes;
    /* 0x00B4 */ int m_textMaxChars;
    /* 0x00B8 */ char m_textBuffer[0x3000];
    /* 0x30B8 */ int m_textEditPosition;
    /* 0x30BC */ int m_textIsPassword;
    /* 0x30C0 */ SVTag *m_pCurrentTextEditableTag;
    /* 0x30C4 */ URIStoreState *m_pURIStore;
    /* 0x30C8 */ FileDownloadQueueState *m_pFileDownloadQueue;
    /* 0x30CC */ int m_bUseDownloadManger;
    /* 0x30D0 */ CPluginManagerState *m_pPluginManager;
    /* 0x30D4 */ int m_bCreateGameRequested;
    /* 0x30D8 */ SVChronographState *m_pTimer;
    /* 0x30DC */ SVLoginInfo m_loginInfo;
    /* 0x3130 */ void *m_pXMPPClient;
    /* 0x3134 */ int m_tick;
    /* 0x3138 */ unsigned int m_severity;
    /* 0x313C */ unsigned int m_category;
} SVBrowserPrefix;
extern "C" {
SVBrowserPrefix *GetInstance(void);
int BrowserIsIdle(SVBrowserPrefix *browser);
void SetLogout(SVBrowserPrefix *browser);
}
struct SVTag;
struct CDrawContextBase;

struct BrowserProviderVtable { // 0x28
    /* 0x00 */ void *prefix[2];
    /* 0x08 */ void (*destroy)(void *, int);
    /* 0x0C */ unsigned char gap[0x18];
    /* 0x24 */ void (*registerSchemes)(void *);
};

struct BrowserEditableVtable { // 0x68
    /* 0x00 */ unsigned char prefix[0x50];
    /* 0x50 */ char *(*GetText)(SVTag *);
    /* 0x54 */ void *unknown54;
    /* 0x58 */ int (*IsPassword)(SVTag *);
    /* 0x5C */ int (*GetMaxLengthBytes)(SVTag *);
    /* 0x60 */ int (*GetMaxLengthUTF8Chars)(SVTag *);
    /* 0x64 */ int (*GetEditPosition)(SVTag *);
};

struct BrowserInputVtable { // 0x38
    /* 0x00 */ unsigned char prefix[0x34];
    /* 0x34 */ void (*SeedVKBBuffer)(CInputContextBaseState *, char *);
};

struct BrowserManagerVtable { // 0x24
    /* 0x00 */ unsigned char prefix[0x20];
    /* 0x20 */ void (*destroy)(SVDownloadManager *, int);
};

struct BrowserSystemVtable { // 0x20
    /* 0x00 */ unsigned char prefix[0x1C];
    /* 0x1C */ void (*HandleLoginResponse)(CSystemContextBase *, int);
};

struct BrowserVKBVtable { // 0x68
    /* 0x00 */ unsigned char prefix[0x64];
    /* 0x64 */ void (*DrawVKB)(CDrawContextBase *);
};
#endif
