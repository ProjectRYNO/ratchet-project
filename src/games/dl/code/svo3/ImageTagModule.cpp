#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_ImageTagModule_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTagModule.h"
#include <string.h>

extern "C" {
extern SVTagModuleState *svoImageTagModuleInstance;
extern const SVTagModuleVtablePrefix svoImageTagModuleVtable;
extern char svoImageTagModuleSource[];
extern char svoImageTagModuleName[];
void ImageTag(void *memory, iks *xml, CAllContextData *contexts);

#define SECTION(name) __attribute__((section(".svo_ImageTagModule_" #name)))

SECTION(IsMyTag___dupe8) int IsMyTag___dupe8(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG) __SVO_Assert_Handler(svoImageTagModuleSource, 0x1A);
    return strcmp(iks_name(xml), svoImageTagModuleName) == 0;
}

SECTION(BuildTag___dupe9) void BuildTag___dupe9(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList) __SVO_Assert_Handler(svoImageTagModuleSource, 0x20);
    void *memory = SVTagNew(0x170);
    ImageTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

SECTION(getInstance___dupe10) SVTagModuleState *getInstance___dupe10(void)
{
    if (!svoImageTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoImageTagModuleVtable;
        svoImageTagModuleInstance = module;
    }
    return svoImageTagModuleInstance;
}

SECTION(FreeResources___dupe17) void FreeResources___dupe17(SVTagModuleState *module)
{
    if (svoImageTagModuleInstance) {
        svoImageTagModuleInstance->vtable->destroy(svoImageTagModuleInstance, 3);
        svoImageTagModuleInstance = 0;
    }
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTagModule", processImageCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTagModule", ScanTags___dupe4);
