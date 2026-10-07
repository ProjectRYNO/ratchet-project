#include "RadioInputTagModule.h"
#include <string.h>

extern "C" {
extern char svoRadioInputTagModuleSource[];
extern char svoRadioInputTagModuleTypeAttribute[];
extern char svoRadioInputTagModuleTagName[];
extern char svoRadioInputTagModuleInputType[];
extern SVTagModuleState *svoRadioInputTagModuleInstance;
extern const SVTagModuleVtablePrefix svoRadioInputTagModuleVtable;
void RadioInputTag(void *memory, iks *xml, SVTag **tagList, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_RadioInputTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe13) int IsMyTag___dupe13(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoRadioInputTagModuleSource, 0x14);
    char *type = iks_find_attrib(xml, svoRadioInputTagModuleTypeAttribute);
    if (strcmp(iks_name(xml), svoRadioInputTagModuleTagName)) return 0;
    return strcmp(type, svoRadioInputTagModuleInputType) == 0;
}

MODULE_SECTION(BuildTag___dupe14) void BuildTag___dupe14(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoRadioInputTagModuleSource, 0x1F);
    void *memory = SVTagNew(0x198);
    RadioInputTag(memory, xml, tagList, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe15) SVTagModuleState *getInstance___dupe15(void)
{
    if (!svoRadioInputTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoRadioInputTagModuleVtable;
        svoRadioInputTagModuleInstance = module;
    }
    return svoRadioInputTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe27) void FreeResources___dupe27(SVTagModuleState *module)
{
    if (svoRadioInputTagModuleInstance) {
        svoRadioInputTagModuleInstance->vtable->destroy(svoRadioInputTagModuleInstance, 3);
        svoRadioInputTagModuleInstance = 0;
    }
}
