#include "RectangleTagModule.h"
#include <string.h>

extern "C" {
extern char svoRectangleTagModuleSource[];
extern char svoRectangleTagModuleTagName[];
extern SVTagModuleState *svoRectangleTagModuleInstance;
extern const SVTagModuleVtablePrefix svoRectangleTagModuleVtable;
void RectangleTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_RectangleTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe5) int IsMyTag___dupe5(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoRectangleTagModuleSource, 0x15);
    return strcmp(iks_name(xml), svoRectangleTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe6) void BuildTag___dupe6(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoRectangleTagModuleSource, 0x1B);
    void *memory = SVTagNew(0xD0);
    RectangleTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe7) SVTagModuleState *getInstance___dupe7(void)
{
    if (!svoRectangleTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoRectangleTagModuleVtable;
        svoRectangleTagModuleInstance = module;
    }
    return svoRectangleTagModuleInstance;
}

MODULE_SECTION(FreeResources___dupe11) void FreeResources___dupe11(SVTagModuleState *module)
{
    if (svoRectangleTagModuleInstance) {
        svoRectangleTagModuleInstance->vtable->destroy(svoRectangleTagModuleInstance, 3);
        svoRectangleTagModuleInstance = 0;
    }
}
