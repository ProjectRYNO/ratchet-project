#include "SelectTagModule.h"
#include <string.h>

extern "C" {
extern char svoSelectTagModuleSource[];
extern char svoSelectTagModuleTagName[];
extern SVTagModuleState *svoSelectTagModuleInstance;
extern const SVTagModuleVtablePrefix svoSelectTagModuleVtable;
void SelectTag(void *memory, iks *xml, SVTag **tagList, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_SelectTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe7) int IsMyTag___dupe7(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoSelectTagModuleSource, 0x15);
    return strcmp(iks_name(xml), svoSelectTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe8) void BuildTag___dupe8(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoSelectTagModuleSource, 0x1B);
    void *memory = SVTagNew(0xF4);
    SelectTag(memory, xml, tagList, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe9) SVTagModuleState *getInstance___dupe9(void)
{
    if (!svoSelectTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoSelectTagModuleVtable;
        svoSelectTagModuleInstance = module;
    }
    return svoSelectTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe16) void FreeResources___dupe16(SVTagModuleState *module)
{
    if (svoSelectTagModuleInstance) {
        svoSelectTagModuleInstance->vtable->destroy(svoSelectTagModuleInstance, 3);
        svoSelectTagModuleInstance = 0;
    }
}
