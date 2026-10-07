#include "ListBoxTagModule.h"
#include <string.h>

extern "C" {
extern char svoListBoxTagModuleSource[];
extern char svoListBoxTagModuleTagName[];
extern SVTagModuleState *svoListBoxTagModuleInstance;
extern const SVTagModuleVtablePrefix svoListBoxTagModuleVtable;
void ListBoxTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_ListBoxTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe23) int IsMyTag___dupe23(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoListBoxTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoListBoxTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe24) void BuildTag___dupe24(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoListBoxTagModuleSource, 0x1A);
    void *memory = SVTagNew(0x288);
    ListBoxTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe25) SVTagModuleState *getInstance___dupe25(void)
{
    if (!svoListBoxTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoListBoxTagModuleVtable;
        svoListBoxTagModuleInstance = module;
    }
    return svoListBoxTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe49) void FreeResources___dupe49(SVTagModuleState *module)
{
    if (svoListBoxTagModuleInstance) {
        svoListBoxTagModuleInstance->vtable->destroy(svoListBoxTagModuleInstance, 3);
        svoListBoxTagModuleInstance = 0;
    }
}
