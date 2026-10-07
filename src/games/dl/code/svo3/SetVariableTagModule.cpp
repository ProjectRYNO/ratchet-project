#include "SetVariableTagModule.h"
#include <string.h>

extern "C" {
extern char svoSetVariableTagModuleSource[];
extern char svoSetVariableTagModuleTagName[];
extern SVTagModuleState *svoSetVariableTagModuleInstance;
extern const SVTagModuleVtablePrefix svoSetVariableTagModuleVtable;
void SetVariableTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_SetVariableTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe4) int IsMyTag___dupe4(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoSetVariableTagModuleSource, 0x15);
    return strcmp(iks_name(xml), svoSetVariableTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe5) void BuildTag___dupe5(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    void *memory = SVTagNew(0xBC);
    SetVariableTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe6) SVTagModuleState *getInstance___dupe6(void)
{
    if (!svoSetVariableTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoSetVariableTagModuleVtable;
        svoSetVariableTagModuleInstance = module;
    }
    return svoSetVariableTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe10) void FreeResources___dupe10(SVTagModuleState *module)
{
    if (svoSetVariableTagModuleInstance) {
        svoSetVariableTagModuleInstance->vtable->destroy(svoSetVariableTagModuleInstance, 3);
        svoSetVariableTagModuleInstance = 0;
    }
}
