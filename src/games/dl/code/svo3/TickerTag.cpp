#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_TickerTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern "C" {
extern const SVTagVtablePrefix svoTickerTagVtable;
void FreeResources___dupe59(void *tag);
}
#define SECTION(name) __attribute__((section(".svo_TickerTag_" #name)))

SECTION(FreeResources___dupe59) void FreeResources___dupe59(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(HandleInput___dupe55) long HandleInput___dupe55(void *self, void *context)
{
    return 1;
}

SECTION(IsSelectable___dupe17) long IsSelectable___dupe17(void *self)
{
    return 0;
}

}

extern "C" SECTION(_TickerTag) void _TickerTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoTickerTagVtable;
    FreeResources___dupe59((void *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TickerTag", DefaultInit___dupe24);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TickerTag", Draw___dupe27);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TickerTag", getTickerTypeAttrib);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TickerTag", TickerTag);
