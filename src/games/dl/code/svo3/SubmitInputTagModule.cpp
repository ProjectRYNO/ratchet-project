#include "SubmitInputTagModule.h"
#include <string.h>

extern "C" {
extern char svoSubmitInputTagModuleSource[];
extern char svoSubmitInputTagModuleTypeAttribute[];
extern char svoSubmitInputTagModuleTagName[];
extern char svoSubmitInputTagModuleInputType[];
extern SVTagModuleState *svoSubmitInputTagModuleInstance;
extern const SVTagModuleVtablePrefix svoSubmitInputTagModuleVtable;
void SubmitInputTag(void *memory, iks *xml, SVTag **tagList, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_SubmitInputTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe16) int IsMyTag___dupe16(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoSubmitInputTagModuleSource, 0x14);
    char *type = iks_find_attrib(xml, svoSubmitInputTagModuleTypeAttribute);
    if (strcmp(iks_name(xml), svoSubmitInputTagModuleTagName)) return 0;
    return strcmp(type, svoSubmitInputTagModuleInputType) == 0;
}

MODULE_SECTION(BuildTag___dupe17) void BuildTag___dupe17(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoSubmitInputTagModuleSource, 0x1F);
    void *memory = SVTagNew(0x158);
    SubmitInputTag(memory, xml, tagList, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe18) SVTagModuleState *getInstance___dupe18(void)
{
    if (!svoSubmitInputTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoSubmitInputTagModuleVtable;
        svoSubmitInputTagModuleInstance = module;
    }
    return svoSubmitInputTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe33) void FreeResources___dupe33(SVTagModuleState *module)
{
    if (svoSubmitInputTagModuleInstance) {
        svoSubmitInputTagModuleInstance->vtable->destroy(svoSubmitInputTagModuleInstance, 3);
        svoSubmitInputTagModuleInstance = 0;
    }
}
