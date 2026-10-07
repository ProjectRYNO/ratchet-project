#include "LogoutTagModule.h"
#include <string.h>

extern "C" {
extern char svoLogoutTagModuleSource[];
extern char svoLogoutTagModuleTagName[];
extern SVTagModuleState *svoLogoutTagModuleInstance;
extern const SVTagModuleVtablePrefix svoLogoutTagModuleVtable;
void LogoutTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_LogoutTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe17) int IsMyTag___dupe17(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoLogoutTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoLogoutTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe18) void BuildTag___dupe18(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoLogoutTagModuleSource, 0x1A);
    void *memory = SVTagNew(0xB4);
    LogoutTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe19) SVTagModuleState *getInstance___dupe19(void)
{
    if (!svoLogoutTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoLogoutTagModuleVtable;
        svoLogoutTagModuleInstance = module;
    }
    return svoLogoutTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe35) void FreeResources___dupe35(SVTagModuleState *module)
{
    if (svoLogoutTagModuleInstance) {
        svoLogoutTagModuleInstance->vtable->destroy(svoLogoutTagModuleInstance, 3);
        svoLogoutTagModuleInstance = 0;
    }
}
