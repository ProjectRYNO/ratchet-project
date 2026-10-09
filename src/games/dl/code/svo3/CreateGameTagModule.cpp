#include "TagUtils.h"
#include "CAllContextData.h"
#include "CSystemContextBase.h"
#include "SVOString.h"
#include "stdlib.h"
#include "CMemoryContextBase.h"
#include <string.h>
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_CreateGameTagModule_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "CreateGameTagModule.h"

extern "C" {
extern CreateGameTagModuleState *svoCreateGameTagModuleInstance;
extern char svoCreateGameTagModuleSource[];
CMemoryContextBaseState *GetMemoryContext(void);
void *CreateGameTagModuleNew(unsigned int size) __asm__("operator.new___dupe15");
void CreateGameTagModuleDelete13(void *memory) __asm__("operator.delete___dupe13");

extern const SVTagModuleVtablePrefix svoCreateGameTagModuleVtable;
extern char svoCreateGameTagModuleSource[];

extern "C" {
extern char svoCreateGameName[];
extern char svoGamePlayerName[];
extern char svoCreateGameStatusName[];
extern char svoCreateGameIDName[];
extern char svoCreateGameStatusIDName[];
extern char svoCreateGameMessageName[];
extern char svoCreateGameActionAttribute[];
extern char svoCreateGameParamNameAttribute[];
extern char svoCreateGameSeparator[];
extern char svoCreateGameAllocationSource[];
extern char *svoCreateGameResultNames[23];
extern const SVTagModuleVtablePrefix svoBaseTagModuleVtable;
int GetCreateGameSubmitResponse(CreateGameTagModuleState *, iks *);
int ParseCreateGameParamsXML(CreateGameTagModuleState *, iks *);
}
#define SECTION(name) __attribute__((section(".svo_CreateGameTagModule_" #name)))

SECTION(CreateGameTagModule) const SVTagModuleVtablePrefix *CreateGameTagModule(CreateGameTagModuleState *module)
{
    module->m_SVOGameID = 0;
    module->base.vtable = &svoCreateGameTagModuleVtable;
    module->m_createGameParamStrPtrs = 0;
    module->m_createGameNumOfParams = 0;
    return &svoCreateGameTagModuleVtable;
}

SECTION(BuildTag___dupe26) void BuildTag___dupe26(CreateGameTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0x3D);
}

}

extern "C" SECTION(_CreateGameTagModule) void _CreateGameTagModule(CreateGameTagModuleState *module, int flags)
{
    module->base.vtable = &svoCreateGameTagModuleVtable;
    if (module->m_createGameParamStrPtrs) svFreeSafe(GetMemoryContext(), module->m_createGameParamStrPtrs);
    module->base.vtable = &svoBaseTagModuleVtable;
    if (flags & 1) CreateGameTagModuleDelete13(module);
}

extern "C" SECTION(FreeResources___dupe55) void FreeResources___dupe55(CreateGameTagModuleState *module)
{
    if (svoCreateGameTagModuleInstance) {
        svoCreateGameTagModuleInstance->base.vtable->destroy(&svoCreateGameTagModuleInstance->base, 3);
        svoCreateGameTagModuleInstance = 0;
    }
}

extern "C" SECTION(GetCreateGameSubmitResponse) int GetCreateGameSubmitResponse(CreateGameTagModuleState *module, iks *xml)
{
    if (!xml || strcmp(svoCreateGameStatusName, iks_name(xml))) __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0xD3);
    iks *message = iks_child(xml);
    while (message) {
        if (iks_name(message) && !strcmp(svoCreateGameMessageName, iks_name(message))) break;
        message = iks_next(message);
    }
    if (!message || strcmp(svoCreateGameMessageName, iks_name(message))) __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0xDF);
    if (message) {
        char *text = iks_cdata(iks_child(message));
        for (int i = 0; i < 23; ++i) if (text && !strcmp(text, svoCreateGameResultNames[i])) return i;
    }
    return 1;
}

extern "C" SECTION(getInstance___dupe28) CreateGameTagModuleState *getInstance___dupe28(void)
{
    if (!svoCreateGameTagModuleInstance) {
        CreateGameTagModuleState *module = (CreateGameTagModuleState *)CreateGameTagModuleNew(0x214);
        CreateGameTagModule(module);
        svoCreateGameTagModuleInstance = module;
    }
    return svoCreateGameTagModuleInstance;
}

extern "C" SECTION(IsMyTag___dupe26) int IsMyTag___dupe26(CreateGameTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG) __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0x2F);
    if (!strcmp(iks_name(xml), svoCreateGameName)) return 1;
    return strcmp(iks_name(xml), svoGamePlayerName) == 0;
}

extern "C" SECTION(operator.delete___dupe13) void CreateGameTagModuleDelete13(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

extern "C" SECTION(operator.new___dupe15) void *CreateGameTagModuleNew(unsigned int size)
{
    void *memory = svAllocSafe(GetMemoryContext(), size, 0, 0xB6, svoCreateGameTagModuleSource);
    if (!memory) __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0xB9);
    return memory;
}

extern "C" SECTION(ParseCreateGameParamsXML) int ParseCreateGameParamsXML(CreateGameTagModuleState *module, iks *xml)
{
    iks *child = iks_child(xml);
    char *name = 0;
    memset(module->m_createGameParamNames, 0, 257);
    memset(module->m_createGameSubmitBaseURL, 0, 257);
    svstrncpy(module->m_createGameSubmitBaseURL, iks_find_attrib(xml, svoCreateGameActionAttribute), 257);
    if (!module->m_createGameSubmitBaseURL[0]) __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0x105);
    int count = 0;
    while (child) {
        if (iks_name(child)) {
            ++count;
            getStringAttrib(child, svoCreateGameParamNameAttribute, &name);
            if (!name) __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0x10F);
            strcat(module->m_createGameParamNames, name);
            strcat(module->m_createGameParamNames, svoCreateGameSeparator);
            name = 0;
        }
        child = iks_next(child);
    }
    if (!count) __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0x116);
    module->m_createGameNumOfParams = count;
    if (module->m_createGameParamStrPtrs) svFreeSafe(GetMemoryContext(), module->m_createGameParamStrPtrs);
    module->m_createGameParamStrPtrs = (char **)svAllocSafe(GetMemoryContext(), module->m_createGameNumOfParams << 2, 0, 0, svoCreateGameAllocationSource);
    char *text = module->m_createGameParamNames;
    for (int i = 0; i < module->m_createGameNumOfParams; ++i) {
        module->m_createGameParamStrPtrs[i] = text;
        text = strstr(text, svoCreateGameSeparator);
        *text++ = 0;
    }
    return 1;
}

extern "C" SECTION(ScanTags___dupe7) void ScanTags___dupe7(CreateGameTagModuleState *module, iks *xml, SVTag **tags, CAllContextData *contexts, CTagModuleActions *actions)
{
    if (!strcmp(iks_name(xml), svoCreateGameName)) {
        iks *status = getChildIksStruct(xml, svoCreateGameStatusName);
        if (!status) {
            if (!ParseCreateGameParamsXML(module, xml)) __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0x7B);
        } else {
            int result = GetCreateGameSubmitResponse(module, status);
            iks *id = getChildIksStruct(xml, svoCreateGameIDName);
            if (id) module->m_SVOGameID = atoi(iks_cdata(iks_child(id)));
            CSystemContextBase *system = contexts->systemContext;
            system->vtable->HandleCreateGameResponse(system, result);
        }
    } else if (!strcmp(iks_name(xml), svoGamePlayerName)) {
        int result = 1;
        iks *status = getChildIksStruct(xml, svoCreateGameStatusName);
        if (status) {
            iks *id = getChildIksStruct(status, svoCreateGameStatusIDName);
            if (id) result = atoi(iks_cdata(iks_child(id))) != 0x4FC6;
        }
        CSystemContextBase *system = contexts->systemContext;
        system->vtable->HandleJoinGameResponse(system, result);
    } else __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0xA1);
}
