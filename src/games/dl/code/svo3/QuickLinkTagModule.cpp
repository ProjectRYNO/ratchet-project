#include "QuickLinkTagModule.h"
#include <string.h>

extern "C" {
extern char svoQuickLinkTagModuleSource[];
extern char svoQuickLinkTagModuleTagName[];
extern SVTagModuleState *svoQuickLinkTagModuleInstance;
extern const SVTagModuleVtablePrefix svoQuickLinkTagModuleVtable;
void QuickLinkTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_QuickLinkTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe6) int IsMyTag___dupe6(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoQuickLinkTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoQuickLinkTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe7) void BuildTag___dupe7(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoQuickLinkTagModuleSource, 0x1A);
    void *memory = SVTagNew(0xC0);
    QuickLinkTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe8) SVTagModuleState *getInstance___dupe8(void)
{
    if (!svoQuickLinkTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoQuickLinkTagModuleVtable;
        svoQuickLinkTagModuleInstance = module;
    }
    return svoQuickLinkTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe14) void FreeResources___dupe14(SVTagModuleState *module)
{
    if (svoQuickLinkTagModuleInstance) {
        svoQuickLinkTagModuleInstance->vtable->destroy(svoQuickLinkTagModuleInstance, 3);
        svoQuickLinkTagModuleInstance = 0;
    }
}
