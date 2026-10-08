#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_buttonTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern "C" {
extern const SVTagVtablePrefix svoButtonTagVtable;
void FreeResources___dupe5(void *tag);
}
#define SECTION(name) __attribute__((section(".svo_buttonTag_" #name)))

SECTION(FreeResources___dupe5) void FreeResources___dupe5(void *self)
{
    // Retail implements this callback as a no-op.
}

}

extern "C" SECTION(_ButtonTag) void _ButtonTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoButtonTagVtable;
    FreeResources___dupe5((void *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/buttonTag", ButtonTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/buttonTag", DefaultInit___dupe4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/buttonTag", Draw___dupe9);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/buttonTag", HandleInput___dupe35);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/buttonTag", operator.delete___dupe9);
