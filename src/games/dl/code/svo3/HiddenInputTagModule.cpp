#include "HiddenInputTagModule.h"
#include <string.h>

extern "C" {
extern char svoHiddenInputTagModuleSource[];
extern char svoHiddenInputTagModuleTypeAttribute[];
extern char svoHiddenInputTagModuleTagName[];
extern char svoHiddenInputTagModuleInputType[];
extern SVTagModuleState *svoHiddenInputTagModuleInstance;
extern const SVTagModuleVtablePrefix svoHiddenInputTagModuleVtable;
void HiddenInputTag(void *memory, iks *xml, SVTag **tagList, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_HiddenInputTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe20) int IsMyTag___dupe20(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoHiddenInputTagModuleSource, 0x14);
    char *type = iks_find_attrib(xml, svoHiddenInputTagModuleTypeAttribute);
    if (strcmp(iks_name(xml), svoHiddenInputTagModuleTagName)) return 0;
    return strcmp(type, svoHiddenInputTagModuleInputType) == 0;
}

MODULE_SECTION(BuildTag___dupe21) void BuildTag___dupe21(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoHiddenInputTagModuleSource, 0x1F);
    void *memory = SVTagNew(0x1BC);
    HiddenInputTag(memory, xml, tagList, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe22) SVTagModuleState *getInstance___dupe22(void)
{
    if (!svoHiddenInputTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoHiddenInputTagModuleVtable;
        svoHiddenInputTagModuleInstance = module;
    }
    return svoHiddenInputTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe41) void FreeResources___dupe41(SVTagModuleState *module)
{
    if (svoHiddenInputTagModuleInstance) {
        svoHiddenInputTagModuleInstance->vtable->destroy(svoHiddenInputTagModuleInstance, 3);
        svoHiddenInputTagModuleInstance = 0;
    }
}
