#include "TextAreaTagModule.h"
#include <string.h>

extern "C" {
extern char svoTextAreaTagModuleSource[];
extern char svoTextAreaTagModuleTagName[];
extern SVTagModuleState *svoTextAreaTagModuleInstance;
extern const SVTagModuleVtablePrefix svoTextAreaTagModuleVtable;
void TextAreaTag(void *memory, iks *xml, SVTag **tagList, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_TextAreaTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe10) int IsMyTag___dupe10(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoTextAreaTagModuleSource, 0x15);
    return strcmp(iks_name(xml), svoTextAreaTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe11) void BuildTag___dupe11(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoTextAreaTagModuleSource, 0x1B);
    void *memory = SVTagNew(0x194);
    TextAreaTag(memory, xml, tagList, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe12) SVTagModuleState *getInstance___dupe12(void)
{
    if (!svoTextAreaTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoTextAreaTagModuleVtable;
        svoTextAreaTagModuleInstance = module;
    }
    return svoTextAreaTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe22) void FreeResources___dupe22(SVTagModuleState *module)
{
    if (svoTextAreaTagModuleInstance) {
        svoTextAreaTagModuleInstance->vtable->destroy(svoTextAreaTagModuleInstance, 3);
        svoTextAreaTagModuleInstance = 0;
    }
}
