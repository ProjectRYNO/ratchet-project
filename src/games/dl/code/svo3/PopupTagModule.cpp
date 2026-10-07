#include "PopupTagModule.h"
#include <string.h>

extern "C" {
extern char svoPopupTagModuleSource[];
extern char svoPopupTagModuleTagName[];
extern SVTagModuleState *svoPopupTagModuleInstance;
extern const SVTagModuleVtablePrefix svoPopupTagModuleVtable;
void PopupTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_PopupTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe19) int IsMyTag___dupe19(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoPopupTagModuleSource, 0x15);
    return strcmp(iks_name(xml), svoPopupTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe20) void BuildTag___dupe20(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoPopupTagModuleSource, 0x1B);
    void *memory = SVTagNew(0xB4);
    PopupTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe21) SVTagModuleState *getInstance___dupe21(void)
{
    if (!svoPopupTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoPopupTagModuleVtable;
        svoPopupTagModuleInstance = module;
    }
    return svoPopupTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe39) void FreeResources___dupe39(SVTagModuleState *module)
{
    if (svoPopupTagModuleInstance) {
        svoPopupTagModuleInstance->vtable->destroy(svoPopupTagModuleInstance, 3);
        svoPopupTagModuleInstance = 0;
    }
}
