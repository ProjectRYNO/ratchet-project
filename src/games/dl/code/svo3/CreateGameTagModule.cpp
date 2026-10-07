#include "CMemoryContextBase.h"
#include <string.h>
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_CreateGameTagModule_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "CreateGameTagModule.h"

extern "C" {
extern CreateGameTagModuleState *svoCreateGameTagModuleInstance;
extern char svoCreateGameTagModuleSource[];
CMemoryContextBaseState *GetMemoryContext(void);
void *CreateGameTagModuleNew(unsigned int size) __asm__("operator.new___dupe15");
void CreateGameTagModuleDelete13(void *memory) __asm__("operator.delete___dupe13");

extern const SVTagModuleVtablePrefix svoCreateGameTagModuleVtable;
extern char svoCreateGameTagModuleSource[];

#define SECTION(name) __attribute__((section(".svo_CreateGameTagModule_" #name)))

SECTION(CreateGameTagModule) const SVTagModuleVtablePrefix *CreateGameTagModule(CreateGameTagModuleState *module)
{
    module->m_SVOGameID = 0;
    module->base.vtable = &svoCreateGameTagModuleVtable;
    module->m_createGameParamStrPtrs = 0;
    module->m_createGameNumOfParams = 0;
    return &svoCreateGameTagModuleVtable;
}

SECTION(BuildTag___dupe26) void BuildTag___dupe26(CreateGameTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0x3D);
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CreateGameTagModule", _CreateGameTagModule);

extern "C" SECTION(FreeResources___dupe55) void FreeResources___dupe55(CreateGameTagModuleState *module)
{
    if (svoCreateGameTagModuleInstance) {
        svoCreateGameTagModuleInstance->base.vtable->destroy(&svoCreateGameTagModuleInstance->base, 3);
        svoCreateGameTagModuleInstance = 0;
    }
}


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CreateGameTagModule", GetCreateGameSubmitResponse);

extern "C" SECTION(getInstance___dupe28) CreateGameTagModuleState *getInstance___dupe28(void)
{
    if (!svoCreateGameTagModuleInstance) {
        CreateGameTagModuleState *module = (CreateGameTagModuleState *)CreateGameTagModuleNew(0x214);
        CreateGameTagModule(module);
        svoCreateGameTagModuleInstance = module;
    }
    return svoCreateGameTagModuleInstance;
}


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CreateGameTagModule", IsMyTag___dupe26);

extern "C" SECTION(operator.delete___dupe13) void CreateGameTagModuleDelete13(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}


extern "C" SECTION(operator.new___dupe15) void *CreateGameTagModuleNew(unsigned int size)
{
    void *memory = svAllocSafe(GetMemoryContext(), size, 0, 0xB6, svoCreateGameTagModuleSource);
    if (!memory) __SVO_Assert_Handler(svoCreateGameTagModuleSource, 0xB9);
    return memory;
}


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CreateGameTagModule", ParseCreateGameParamsXML);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CreateGameTagModule", ScanTags___dupe7);
