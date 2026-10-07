#include "TextInputTagModule.h"
#include <string.h>

extern "C" {
extern char svoTextInputTagModuleSource[];
extern char svoTextInputTagModuleTypeAttribute[];
extern char svoTextInputTagModuleTagName[];
extern char svoTextInputTagModuleInputType[];
extern SVTagModuleState *svoTextInputTagModuleInstance;
extern const SVTagModuleVtablePrefix svoTextInputTagModuleVtable;
void TextInputTag(void *memory, iks *xml, SVTag **tagList, CAllContextData *contexts, int password);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_TextInputTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe11) int IsMyTag___dupe11(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoTextInputTagModuleSource, 0x14);
    char *type = iks_find_attrib(xml, svoTextInputTagModuleTypeAttribute);
    if (strcmp(iks_name(xml), svoTextInputTagModuleTagName)) return 0;
    return strcmp(type, svoTextInputTagModuleInputType) == 0;
}

MODULE_SECTION(BuildTag___dupe12) void BuildTag___dupe12(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!tagList)
        __SVO_Assert_Handler(svoTextInputTagModuleSource, 0x1F);
    void *memory = SVTagNew(0x514);
    TextInputTag(memory, xml, tagList, contexts, 0);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe13) SVTagModuleState *getInstance___dupe13(void)
{
    if (!svoTextInputTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoTextInputTagModuleVtable;
        svoTextInputTagModuleInstance = module;
    }
    return svoTextInputTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe24) void FreeResources___dupe24(SVTagModuleState *module)
{
    if (svoTextInputTagModuleInstance) {
        svoTextInputTagModuleInstance->vtable->destroy(svoTextInputTagModuleInstance, 3);
        svoTextInputTagModuleInstance = 0;
    }
}
