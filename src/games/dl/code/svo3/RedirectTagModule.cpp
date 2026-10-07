#include "RedirectTagModule.h"
#include <string.h>

extern "C" {
extern char svoRedirectTagModuleSource[];
extern char svoRedirectTagModuleTagName[];
extern SVTagModuleState *svoRedirectTagModuleInstance;
extern const SVTagModuleVtablePrefix svoRedirectTagModuleVtable;
void RedirectTag(void *memory, iks *xml, CAllContextData *contexts);
}
#define MODULE_SECTION(name) __attribute__((section(".svo_RedirectTagModule_" #name)))

MODULE_SECTION(IsMyTag___dupe21) int IsMyTag___dupe21(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG)
        __SVO_Assert_Handler(svoRedirectTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoRedirectTagModuleTagName) == 0;
}

MODULE_SECTION(BuildTag___dupe22) void BuildTag___dupe22(
    SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList)
        __SVO_Assert_Handler(svoRedirectTagModuleSource, 0x1A);
    void *memory = SVTagNew(0xBC);
    RedirectTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

MODULE_SECTION(getInstance___dupe23) SVTagModuleState *getInstance___dupe23(void)
{
    if (!svoRedirectTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoRedirectTagModuleVtable;
        svoRedirectTagModuleInstance = module;
    }
    return svoRedirectTagModuleInstance;
}
