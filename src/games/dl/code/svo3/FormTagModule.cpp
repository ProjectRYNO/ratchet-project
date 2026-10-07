#include "FormTagModule.h"
#include <string.h>

extern "C" {
extern char svoFormTagModuleSource[];
extern char svoFormTagModuleTagName[];
extern SVTagModuleState *svoFormTagModuleInstance;
extern const SVTagModuleVtablePrefix svoFormTagModuleVtable;
void FormTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_FormTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe15) int IsMyTag___dupe15(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoFormTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoFormTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe16) void BuildTag___dupe16(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList || !contexts)
        __SVO_Assert_Handler(svoFormTagModuleSource, 0x1E);
    void *memory = SVTagNew(0x69EC);
    FormTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe17) SVTagModuleState *getInstance___dupe17(void)
{
    if (!svoFormTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(8);
        module->vtable = &svoFormTagModuleVtable;
        svoFormTagModuleInstance = module;
    }
    return svoFormTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe31) void FreeResources___dupe31(SVTagModuleState *module)
{
    if (svoFormTagModuleInstance) {
        svoFormTagModuleInstance->vtable->destroy(svoFormTagModuleInstance, 3);
        svoFormTagModuleInstance = 0;
    }
}
