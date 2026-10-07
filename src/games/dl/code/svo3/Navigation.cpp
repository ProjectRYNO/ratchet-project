#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_Navigation_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "Navigation.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_Navigation_" #name)))

SECTION(reset___dupe2) void reset___dupe2(CNavInfoState *navigation)
{
    navigation->right = 0;
    navigation->up = 0;
    navigation->down = 0;
    navigation->left = 0;
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/Navigation", autoNavigate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/Navigation", CNavInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/Navigation", getDistanceAutoNav);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/Navigation", lt_double);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/Navigation", Navigate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/Navigation", setWrapDimensions);
