#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SVTagModule_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTagModule.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_SVTagModule_" #name)))

SECTION(ScanTags___dupe3) void ScanTags___dupe3(SVTagModuleState *module, iks *xml, SVTag **tagList, CAllContextData *contexts)
{
    // Retail default callback has no tag scanning behavior.
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVTagModule", operator.delete___dupe6);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVTagModule", operator.new___dupe7);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVTagModule", ScanTags___dupe2);
