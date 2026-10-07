#include "TickerTagModule.h"
#include <string.h>

extern "C" {
extern char svoTickerTagModuleSource[];
extern char svoTickerTagModuleTagName[];
extern SVTagModuleState *svoTickerTagModuleInstance;
extern const SVTagModuleVtablePrefix svoTickerTagModuleVtable;
void TickerTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_TickerTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe28) int IsMyTag___dupe28(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoTickerTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoTickerTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe28) void BuildTag___dupe28(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!tagList)
        __SVO_Assert_Handler(svoTickerTagModuleSource, 0x1B);
    void *memory = SVTagNew(0xC8);
    TickerTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe30) SVTagModuleState *getInstance___dupe30(void)
{
    if (!svoTickerTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoTickerTagModuleVtable;
        svoTickerTagModuleInstance = module;
    }
    return svoTickerTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe58) void FreeResources___dupe58(SVTagModuleState *module)
{
    if (svoTickerTagModuleInstance) {
        svoTickerTagModuleInstance->vtable->destroy(svoTickerTagModuleInstance, 3);
        svoTickerTagModuleInstance = 0;
    }
}
