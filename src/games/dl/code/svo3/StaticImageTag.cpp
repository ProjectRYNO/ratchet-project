#include "string.h"
#include "SVOString.h"
#include "StaticImageTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_StaticImageTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern char svoStaticImageTagName[];
extern char gTagNotSetStr[];
extern char svoStaticImageUnsetName[];


#define SECTION(name) __attribute__((section(".svo_StaticImageTag_" #name)))

SECTION(FreeResources___dupe20) void FreeResources___dupe20(SVTag *tag)
{
    FreeContexts(tag);
}

long IsSelectable___dupe12(SVTag *tag);
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/StaticImageTag", IsSelectable___dupe12);

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/StaticImageTag", DefaultInit___dupe11);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/StaticImageTag", Draw___dupe15);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/StaticImageTag", HandleInput___dupe42);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/StaticImageTag", StaticImageTag);
