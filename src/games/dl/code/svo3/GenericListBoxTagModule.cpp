#include "GenericListBoxTagModule.h"
#include <string.h>

extern "C" {
extern char svoGenericListBoxTagModuleSource[];
extern char svoGenericListBoxTagModuleTagName[];
extern SVTagModuleState *svoGenericListBoxTagModuleInstance;
extern const SVTagModuleVtablePrefix svoGenericListBoxTagModuleVtable;
void GenericListBoxTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_GenericListBoxTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe27) int IsMyTag___dupe27(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoGenericListBoxTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoGenericListBoxTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe27) void BuildTag___dupe27(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoGenericListBoxTagModuleSource, 0x1A);
    void *memory = SVTagNew(0xE4);
    GenericListBoxTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe29) SVTagModuleState *getInstance___dupe29(void)
{
    if (!svoGenericListBoxTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoGenericListBoxTagModuleVtable;
        svoGenericListBoxTagModuleInstance = module;
    }
    return svoGenericListBoxTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe57) void FreeResources___dupe57(SVTagModuleState *module)
{
    if (svoGenericListBoxTagModuleInstance) {
        svoGenericListBoxTagModuleInstance->vtable->destroy(svoGenericListBoxTagModuleInstance, 3);
        svoGenericListBoxTagModuleInstance = 0;
    }
}
