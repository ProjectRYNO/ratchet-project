#include "ButtonTagModule.h"
#include <string.h>

extern "C" {
extern char svoButtonTagModuleSource[];
extern char svoButtonTagModuleTagName[];
extern SVTagModuleState *svoButtonTagModuleInstance;
extern const SVTagModuleVtablePrefix svoButtonTagModuleVtable;
void ButtonTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_ButtonTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe2) int IsMyTag___dupe2(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoButtonTagModuleSource, 0x15);
    return strcmp(iks_name(xml), svoButtonTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe3) void BuildTag___dupe3(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    void *memory = SVTagNew(0x15C);
    ButtonTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe4) SVTagModuleState *getInstance___dupe4(void)
{
    if (!svoButtonTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoButtonTagModuleVtable;
        svoButtonTagModuleInstance = module;
    }
    return svoButtonTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe6) void FreeResources___dupe6(SVTagModuleState *module)
{
    if (svoButtonTagModuleInstance) {
        svoButtonTagModuleInstance->vtable->destroy(svoButtonTagModuleInstance, 3);
        svoButtonTagModuleInstance = 0;
    }
}
