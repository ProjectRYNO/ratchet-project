#include "TagUtils.h"
#include "CAllContextData.h"
#include "stdlib.h"
struct CTagModuleActions;
#include "CMemoryContextBase.h"
#include <string.h>
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_LoginTagModule_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "LoginTagModule.h"

extern "C" {
extern LoginTagModuleState *svoLoginTagModuleInstance;
extern char svoLoginTagModuleSource[];
CMemoryContextBaseState *GetMemoryContext(void);
void *LoginTagModuleNew(unsigned int size) __asm__("operator.new___dupe12");
void LoginTagModuleDelete10(void *memory) __asm__("operator.delete___dupe10");
void LoginTagModuleDelete11(void *memory) __asm__("operator.delete___dupe11");
extern const SVTagModuleVtablePrefix svoBaseTagModuleVtable;
extern char svoLoginTagModuleName[];

extern const SVTagModuleVtablePrefix svoLoginTagModuleVtable;

extern "C" {
extern int m_loginResult;
void ScanTagsHandleLoginDTD(LoginTagModuleState *, iks *, CAllContextData *, char *, CTagModuleActions *);
void ScanTagsHandleLoginSubmitResponse(LoginTagModuleState *, iks *, CAllContextData *, CTagModuleActions *);
extern char svoLoginDTDAttribute[];
}
extern "C" {
extern char svoLoginStatusName[];
extern char svoLoginMessageName[];
extern char svoLoginIPAddressAttribute[];
extern char svoLoginUserName[];
extern char svoLoginMaxLengthAttribute[];
extern char svoLoginNameAttribute[];
extern char svoLoginAccountIDName[];
extern char *svoLoginResultNames[2];
const void *DownloadBinary(DownloadBinaryState *);
void _DownloadBinary(DownloadBinaryState *, int);
void SetPath(DownloadBinaryState *, char *);
void SetFormMethodType(DownloadBinaryState *, int);
void SetToDestroyOnRequestSend(DownloadBinaryState *);
void SetDownloadCallback(DownloadBinaryState *, DownloadCallback);
void scanXMLCB(unsigned int, char *, int, void *, int);
void URIStoreAdd(char *, char *);
void SetUserNameMaxLength(DownloadBinaryState *, int);
void SetUserNameParameter(DownloadBinaryState *, char *);
void SetAccountIDParameter(DownloadBinaryState *, char *);
void PushPostTransitionArray(CPage *, DownloadBinaryState *, DownloadBinaryState **);
}
#define SECTION(name) __attribute__((section(".svo_LoginTagModule_" #name)))

SECTION(LoginTagModule) const SVTagModuleVtablePrefix *LoginTagModule(LoginTagModuleState *module)
{
    module->m_bHaveUnhandledLoginResponse = 0;
    module->base.vtable = &svoLoginTagModuleVtable;
    return &svoLoginTagModuleVtable;
}

}

extern "C" SECTION(_LoginTagModule) void _LoginTagModule(LoginTagModuleState *module, int flags)
{
    module->base.vtable = &svoBaseTagModuleVtable;
    if (flags & 1) LoginTagModuleDelete11(module);
}

extern "C" SECTION(FreeResources___dupe52) void FreeResources___dupe52(LoginTagModuleState *module)
{
    if (svoLoginTagModuleInstance) {
        svoLoginTagModuleInstance->base.vtable->destroy(&svoLoginTagModuleInstance->base, 3);
        svoLoginTagModuleInstance = 0;
    }
}

extern "C" SECTION(getInstance___dupe27) LoginTagModuleState *getInstance___dupe27(void)
{
    if (!svoLoginTagModuleInstance) {
        LoginTagModuleState *module = (LoginTagModuleState *)LoginTagModuleNew(0x8);
        LoginTagModule(module);
        svoLoginTagModuleInstance = module;
    }
    return svoLoginTagModuleInstance;
}

extern "C" SECTION(IsMyTag___dupe25) int IsMyTag___dupe25(LoginTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG) __SVO_Assert_Handler(svoLoginTagModuleSource, 0x2A);
    return strcmp(iks_name(xml), svoLoginTagModuleName) == 0;
}

extern "C" SECTION(operator.delete___dupe10) void LoginTagModuleDelete10(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

extern "C" SECTION(operator.delete___dupe11) void LoginTagModuleDelete11(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

extern "C" SECTION(operator.new___dupe12) void *LoginTagModuleNew(unsigned int size)
{
    void *memory = svAllocSafe(GetMemoryContext(), size, 0, 0xCA, svoLoginTagModuleSource);
    if (!memory) __SVO_Assert_Handler(svoLoginTagModuleSource, 0xCD);
    return memory;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/LoginTagModule", ScanTags___dupe6);

extern "C" SECTION(ScanTagsHandleLoginDTD) void ScanTagsHandleLoginDTD(LoginTagModuleState *module, iks *xml, CAllContextData *contexts, char *action, CTagModuleActions *actions)
{
    DownloadBinaryState download;
    DownloadBinaryState *queued;
    DownloadBinary(&download);
    memset(&download, 0, sizeof(download));
    SetPath(&download, action);
    SetFormMethodType(&download, 1);
    SetToDestroyOnRequestSend(&download);
    SetDownloadCallback(&download, scanXMLCB);
    char *ip = iks_find_attrib(xml, svoLoginIPAddressAttribute);
    if (!ip) __SVO_Assert_Handler(svoLoginTagModuleSource, 0x77);
    else URIStoreAdd(svoLoginIPAddressAttribute, ip);
    if (iks_has_children(xml)) xml = iks_next(iks_child(xml));
    while (iks_name(xml)) {
        if (!strcmp(svoLoginUserName, iks_name(xml))) {
            char *length = iks_find_attrib(xml, svoLoginMaxLengthAttribute);
            if (!length) __SVO_Assert_Handler(svoLoginTagModuleSource, 0x87);
            SetUserNameMaxLength(&download, atoi(length));
            char *name = iks_find_attrib(xml, svoLoginNameAttribute);
            if (!name) __SVO_Assert_Handler(svoLoginTagModuleSource, 0x8A);
            SetUserNameParameter(&download, name);
        } else if (!strcmp(svoLoginAccountIDName, iks_name(xml))) SetAccountIDParameter(&download, iks_find_attrib(xml, svoLoginNameAttribute));
        xml = iks_next_tag(xml);
    }
    PushPostTransitionArray(contexts->pMain, &download, &queued);
    actions->action[0].type = 3;
    actions->action[1].ptr = queued;
    actions->action[1].type = 1;
    _DownloadBinary(&download, 2);
}

extern "C" SECTION(ScanTagsHandleLoginSubmitResponse) void ScanTagsHandleLoginSubmitResponse(LoginTagModuleState *module, iks *xml, CAllContextData *contexts, CTagModuleActions *actions)
{
    if (strcmp(iks_name(xml), svoLoginTagModuleName)) __SVO_Assert_Handler(svoLoginTagModuleSource, 0x39);
    iks *status = getChildIksStruct(xml, svoLoginStatusName);
    if (!status) __SVO_Assert_Handler(svoLoginTagModuleSource, 0x40);
    else {
        iks *message = getChildIksStruct(status, svoLoginMessageName);
        if (!message) __SVO_Assert_Handler(svoLoginTagModuleSource, 0x49);
        else {
            char *text = iks_cdata(iks_child(message));
            for (int i = 0; i < 2; ++i) {
                if (text && !strcmp(text, svoLoginResultNames[i])) {
                    module->m_bHaveUnhandledLoginResponse = 1;
                    m_loginResult = i;
                    return;
                }
            }
        }
    }
}

extern "C" SECTION(UnhandledLoginResponseExists) long UnhandledLoginResponseExists(LoginTagModuleState *module, int *result)
{
    if (!result) __SVO_Assert_Handler(svoLoginTagModuleSource, 0xB1);
    if (!module->m_bHaveUnhandledLoginResponse) return 0;
    int value = m_loginResult;
    module->m_bHaveUnhandledLoginResponse = 0;
    *result = value;
    return 1;
}
