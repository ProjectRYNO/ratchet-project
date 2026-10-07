#include "GridTagModule.h"
#include <string.h>

extern "C" {
extern char svoGridTagModuleSource[];
extern char svoGridTagModuleTagName[];
extern SVTagModuleState *svoGridTagModuleInstance;
extern const SVTagModuleVtablePrefix svoGridTagModuleVtable;
void GridTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_GridTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe18) int IsMyTag___dupe18(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoGridTagModuleSource, 0x15);
    return strcmp(iks_name(xml), svoGridTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe19) void BuildTag___dupe19(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList || !contexts)
        __SVO_Assert_Handler(svoGridTagModuleSource, 0x1B);
    void *memory = SVTagNew(0x184);
    GridTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe20) SVTagModuleState *getInstance___dupe20(void)
{
    if (!svoGridTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoGridTagModuleVtable;
        svoGridTagModuleInstance = module;
    }
    return svoGridTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe37) void FreeResources___dupe37(SVTagModuleState *module)
{
    if (svoGridTagModuleInstance) {
        svoGridTagModuleInstance->vtable->destroy(svoGridTagModuleInstance, 3);
        svoGridTagModuleInstance = 0;
    }
}
