#include "BrowserInitTagModule.h"
#include <string.h>

extern "C" {
extern char svoBrowserInitTagModuleSource[];
extern char svoBrowserInitTagModuleTagName[];
extern SVTagModuleState *svoBrowserInitTagModuleInstance;
extern const SVTagModuleVtablePrefix svoBrowserInitTagModuleVtable;
void BrowserInitTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_BrowserInitTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe29) int IsMyTag___dupe29(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoBrowserInitTagModuleSource, 0x15);
    return strcmp(iks_name(xml), svoBrowserInitTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe29) void BuildTag___dupe29(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList || !contexts)
        __SVO_Assert_Handler(svoBrowserInitTagModuleSource, 0x1B);
    void *memory = SVTagNew(0xB4);
    BrowserInitTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe31) SVTagModuleState *getInstance___dupe31(void)
{
    if (!svoBrowserInitTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoBrowserInitTagModuleVtable;
        svoBrowserInitTagModuleInstance = module;
    }
    return svoBrowserInitTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe61) void FreeResources___dupe61(SVTagModuleState *module)
{
    if (svoBrowserInitTagModuleInstance) {
        svoBrowserInitTagModuleInstance->vtable->destroy(svoBrowserInitTagModuleInstance, 3);
        svoBrowserInitTagModuleInstance = 0;
    }
}
