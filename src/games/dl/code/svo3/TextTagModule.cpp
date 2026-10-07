#include "TextTagModule.h"
#include <string.h>

extern "C" {
extern char svoTextTagModuleSource[];
extern char svoTextTagModuleTagName[];
extern SVTagModuleState *svoTextTagModuleInstance;
extern const SVTagModuleVtablePrefix svoTextTagModuleVtable;
void TextTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_TextTagModule_" #name)))

MODULE_SECTION(IsMyTag) int IsMyTag(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoTextTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoTextTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe2) void BuildTag___dupe2(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!tagList)
        __SVO_Assert_Handler(svoTextTagModuleSource, 0x1B);
    void *memory = SVTagNew(0x14C);
    TextTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe2) SVTagModuleState *getInstance___dupe2(void)
{
    if (!svoTextTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoTextTagModuleVtable;
        svoTextTagModuleInstance = module;
    }
    return svoTextTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe3) void FreeResources___dupe3(SVTagModuleState *module)
{
    if (svoTextTagModuleInstance) {
        svoTextTagModuleInstance->vtable->destroy(svoTextTagModuleInstance, 3);
        svoTextTagModuleInstance = 0;
    }
}
