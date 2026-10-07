#include "PageIDTagModule.h"
#include <string.h>

extern "C" {
extern char svoPageIDTagModuleSource[];
extern char svoPageIDTagModuleTagName[];
extern SVTagModuleState *svoPageIDTagModuleInstance;
extern const SVTagModuleVtablePrefix svoPageIDTagModuleVtable;
void PageIDTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_PageIDTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe24) int IsMyTag___dupe24(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoPageIDTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoPageIDTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe25) void BuildTag___dupe25(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoPageIDTagModuleSource, 0x1A);
    void *memory = SVTagNew(0xB4);
    PageIDTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe26) SVTagModuleState *getInstance___dupe26(void)
{
    if (!svoPageIDTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoPageIDTagModuleVtable;
        svoPageIDTagModuleInstance = module;
    }
    return svoPageIDTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe50) void FreeResources___dupe50(SVTagModuleState *module)
{
    if (svoPageIDTagModuleInstance) {
        svoPageIDTagModuleInstance->vtable->destroy(svoPageIDTagModuleInstance, 3);
        svoPageIDTagModuleInstance = 0;
    }
}
