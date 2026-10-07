#include "LineTagModule.h"
#include <string.h>

extern "C" {
extern char svoLineTagModuleSource[];
extern char svoLineTagModuleTagName[];
extern SVTagModuleState *svoLineTagModuleInstance;
extern const SVTagModuleVtablePrefix svoLineTagModuleVtable;
void LineTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_LineTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe3) int IsMyTag___dupe3(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoLineTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoLineTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe4) void BuildTag___dupe4(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoLineTagModuleSource, 0x1A);
    void *memory = SVTagNew(0xC0);
    LineTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe5) SVTagModuleState *getInstance___dupe5(void)
{
    if (!svoLineTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoLineTagModuleVtable;
        svoLineTagModuleInstance = module;
    }
    return svoLineTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe8) void FreeResources___dupe8(SVTagModuleState *module)
{
    if (svoLineTagModuleInstance) {
        svoLineTagModuleInstance->vtable->destroy(svoLineTagModuleInstance, 3);
        svoLineTagModuleInstance = 0;
    }
}
