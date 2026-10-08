#include "string.h"
#include "TagUtils.h"
#include "SVTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_DataTagModule_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTagModule.h"
#include <string.h>

extern "C" {
extern SVTagModuleState *svoDataTagModuleInstance;
extern const SVTagModuleVtablePrefix svoDataTagModuleVtable;
extern char svoDataTagModuleSource[];
extern char svoDataTagModuleName[];
void DataTag(void *memory, iks *xml, CAllContextData *contexts);

extern "C" {
extern char *_data_type_strings[];
}
extern "C" {
extern char *_data_type_strings[];
}
#define SECTION(name) __attribute__((section(".svo_DataTagModule_" #name)))

SECTION(IsMyTag___dupe22) int IsMyTag___dupe22(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG) __SVO_Assert_Handler(svoDataTagModuleSource, 0x14);
    return strcmp(iks_name(xml), svoDataTagModuleName) == 0;
}

SECTION(BuildTag___dupe23) void BuildTag___dupe23(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList || !contexts) __SVO_Assert_Handler(svoDataTagModuleSource, 0x60);
    void *memory = SVTagNew(0xBC);
    DataTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

SECTION(getInstance___dupe24) SVTagModuleState *getInstance___dupe24(void)
{
    if (!svoDataTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoDataTagModuleVtable;
        svoDataTagModuleInstance = module;
    }
    return svoDataTagModuleInstance;
}

SECTION(FreeResources___dupe47) void FreeResources___dupe47(SVTagModuleState *module)
{
    if (svoDataTagModuleInstance) {
        svoDataTagModuleInstance->vtable->destroy(svoDataTagModuleInstance, 3);
        svoDataTagModuleInstance = 0;
    }
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/DataTagModule", getDataTypeAttrib___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/DataTagModule", ScanTags___dupe5);
