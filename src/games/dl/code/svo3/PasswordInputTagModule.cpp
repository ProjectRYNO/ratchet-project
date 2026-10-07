#include "PasswordInputTagModule.h"
#include <string.h>

extern "C" {
extern char svoPasswordInputTagModuleSource[];
extern char svoPasswordInputTagModuleTypeAttribute[];
extern char svoPasswordInputTagModuleTagName[];
extern char svoPasswordInputTagModuleInputType[];
extern SVTagModuleState *svoPasswordInputTagModuleInstance;
extern const SVTagModuleVtablePrefix svoPasswordInputTagModuleVtable;
void PasswordInputTag(void *memory, iks *xml, SVTag **tagList, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_PasswordInputTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe12) int IsMyTag___dupe12(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoPasswordInputTagModuleSource, 0x14);
    char *type = iks_find_attrib(xml, svoPasswordInputTagModuleTypeAttribute);
    if (strcmp(iks_name(xml), svoPasswordInputTagModuleTagName)) return 0;
    return strcmp(type, svoPasswordInputTagModuleInputType) == 0;
}

MODULE_SECTION(BuildTag___dupe13) void BuildTag___dupe13(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoPasswordInputTagModuleSource, 0x1F);
    void *memory = SVTagNew(0x514);
    PasswordInputTag(memory, xml, tagList, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe14) SVTagModuleState *getInstance___dupe14(void)
{
    if (!svoPasswordInputTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoPasswordInputTagModuleVtable;
        svoPasswordInputTagModuleInstance = module;
    }
    return svoPasswordInputTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe25) void FreeResources___dupe25(SVTagModuleState *module)
{
    if (svoPasswordInputTagModuleInstance) {
        svoPasswordInputTagModuleInstance->vtable->destroy(svoPasswordInputTagModuleInstance, 3);
        svoPasswordInputTagModuleInstance = 0;
    }
}
