#include "CInputContextBase.h"
#include "SVTagModule.h"
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

extern char svoNavigationSource[];
unsigned long dpmul(unsigned long, unsigned long);
long dptoli(unsigned long);
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

extern "C" SECTION(CNavInfo) void CNavInfo(CNavInfoState *nav)
{
    nav->right = 0;
    nav->up = 0;
    nav->down = 0;
    nav->left = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/Navigation", getDistanceAutoNav);

extern "C" SECTION(lt_double) int lt_double(unsigned long a, unsigned long b)
{
    const unsigned long scale = 0x4020000000000000UL;
    long left = dptoli(dpmul(a, scale));
    long right = dptoli(dpmul(b, scale));
    return left < right;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/Navigation", Navigate);

extern "C" SECTION(setWrapDimensions) void setWrapDimensions(int direction, float *x, float *y, float *width, float *height, CInputContextBaseState *input)
{
    float screenX;
    float screenY;
    input->vtable->GetScreenDimensions(input, &screenX, &screenY, width, height);
    if (direction == 0) *y = screenY + 1000.0f;
    else if (direction == 1) *y = -1000.0f;
    else if (direction == 2) *x = screenX + 1000.0f;
    else if (direction == 3) *x = -1000.0f;
    else __SVO_Assert_Handler(svoNavigationSource, 0x27B);
}
