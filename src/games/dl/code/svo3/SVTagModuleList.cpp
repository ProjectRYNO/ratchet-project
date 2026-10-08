#include "CMemoryContextBase.h"
#include "SVTagModule.h"
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoTagModuleListSource[];
void * SVTagModuleListoperator_new___dupe6(unsigned int size) __asm__("operator.new___dupe6");

}
#define SECTION(name) __attribute__((section(".svo_module_list_" #name)))
#include "common.h"
// Keep unreplaced assembly in its original function slots.

// Retain the unresolved wrapper at its original address.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_module_list_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTagModuleList.h"
#include <string.h>

extern "C" {
extern SVTagModuleListState *svoTagModuleListInstance;
void SVTagModuleListDelete(void *memory) __asm__("operator.delete___dupe5");
}
#define MODULE_LIST_SECTION(name) __attribute__((section(".svo_module_list_" #name)))

MODULE_LIST_SECTION(SVTagModuleList) void *SVTagModuleList(SVTagModuleListState *list)
{
    void *result = memset(list->m_modules, 0, 0x200);
    list->m_nextTagUID = 0;
    return result;
}

MODULE_LIST_SECTION(getInstance___dupe3) SVTagModuleListState *getInstance___dupe3()
{
    if (!svoTagModuleListInstance) {
        SVTagModuleListState *list = (SVTagModuleListState *)SVTagModuleListNew(0x204);
        SVTagModuleList(list);
        svoTagModuleListInstance = list;
    }
    return svoTagModuleListInstance;
}

void MODULE_LIST_SECTION(FreeResources___dupe4) FreeResources___dupe4(SVTagModuleListState *list)
{
    SVTagModuleState **entry = list->m_modules;
    for (int i = 127; i >= 0; --i, ++entry) {
        if (*entry) {
            (*entry)->vtable->freeResources(*entry);
            *entry = 0;
        }
    }
    if (svoTagModuleListInstance) {
        SVTagModuleListDelete(svoTagModuleListInstance);
        svoTagModuleListInstance = 0;
    }
}

int MODULE_LIST_SECTION(AddTagModule) AddTagModule(SVTagModuleListState *list, SVTagModuleState *module)
{
    SVTagModuleState **entry = list->m_modules;
    for (int i = 0; i < 128; ++i, ++entry) {
        if (!*entry) {
            *entry = module;
            return 1;
        }
    }
    return 0;
}

// Same retail tail-jump allocator as SVChronograph; matching compiler work remains.
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVTagModuleList", operator.new___dupe6);
