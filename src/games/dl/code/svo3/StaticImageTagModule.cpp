#include "StaticImageTagModule.h"
#include <string.h>

extern "C" {
extern char svoStaticImageTagModuleSource[];
extern char svoStaticImageTagModuleTagName[];
extern SVTagModuleState *svoStaticImageTagModuleInstance;
extern const SVTagModuleVtablePrefix svoStaticImageTagModuleVtable;
void StaticImageTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_StaticImageTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe9) int IsMyTag___dupe9(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoStaticImageTagModuleSource, 0x19);
    return strcmp(iks_name(xml), svoStaticImageTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe10) void BuildTag___dupe10(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoStaticImageTagModuleSource, 0x1F);
    void *memory = SVTagNew(0x170);
    StaticImageTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe11) SVTagModuleState *getInstance___dupe11(void)
{
    if (!svoStaticImageTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoStaticImageTagModuleVtable;
        svoStaticImageTagModuleInstance = module;
    }
    return svoStaticImageTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe19) void FreeResources___dupe19(SVTagModuleState *module)
{
    if (svoStaticImageTagModuleInstance) {
        svoStaticImageTagModuleInstance->vtable->destroy(svoStaticImageTagModuleInstance, 3);
        svoStaticImageTagModuleInstance = 0;
    }
}
