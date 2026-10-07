#include "CheckboxInputTagModule.h"
#include <string.h>

extern "C" {
extern char svoCheckboxInputTagModuleSource[];
extern char svoCheckboxInputTagModuleTypeAttribute[];
extern char svoCheckboxInputTagModuleTagName[];
extern char svoCheckboxInputTagModuleInputType[];
extern SVTagModuleState *svoCheckboxInputTagModuleInstance;
extern const SVTagModuleVtablePrefix svoCheckboxInputTagModuleVtable;
void CheckboxInputTag(void *memory, iks *xml, SVTag **tagList, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_CheckboxInputTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe14) int IsMyTag___dupe14(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoCheckboxInputTagModuleSource, 0x14);
    char *type = iks_find_attrib(xml, svoCheckboxInputTagModuleTypeAttribute);
    if (strcmp(iks_name(xml), svoCheckboxInputTagModuleTagName)) return 0;
    return strcmp(type, svoCheckboxInputTagModuleInputType) == 0;
}

MODULE_SECTION(BuildTag___dupe15) void BuildTag___dupe15(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoCheckboxInputTagModuleSource, 0x1F);
    void *memory = SVTagNew(0x194);
    CheckboxInputTag(memory, xml, tagList, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe16) SVTagModuleState *getInstance___dupe16(void)
{
    if (!svoCheckboxInputTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoCheckboxInputTagModuleVtable;
        svoCheckboxInputTagModuleInstance = module;
    }
    return svoCheckboxInputTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe29) void FreeResources___dupe29(SVTagModuleState *module)
{
    if (svoCheckboxInputTagModuleInstance) {
        svoCheckboxInputTagModuleInstance->vtable->destroy(svoCheckboxInputTagModuleInstance, 3);
        svoCheckboxInputTagModuleInstance = 0;
    }
}
