#include "common.h"
#include "iks.h"

#define IKS_SECTION(name) __attribute__((section(".iks_" #name)))

// Keep the remaining assembly at its retail address alongside compiled slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .iks_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", iks_new_within);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", iks_insert);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", iks_insert_cdata);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", iks_insert_attrib);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", iks_delete);

iks *IKS_SECTION(iks_next) iks_next(iks *node)
{
    return node ? node->next : 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", iks_next_tag);

iks *IKS_SECTION(iks_parent) iks_parent(iks *node)
{
    return node ? node->parent : 0;
}

iks *IKS_SECTION(iks_child) iks_child(iks *node)
{
    return node ? node->children : 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", iks_find);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", iks_find_cdata);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", iks_find_attrib);

int IKS_SECTION(iks_type) iks_type(iks *node)
{
    return node ? node->type : 0;
}

char *IKS_SECTION(iks_name) iks_name(iks *node)
{
    return node ? node->name : 0;
}

char *IKS_SECTION(iks_cdata) iks_cdata(iks *node)
{
    return node ? node->cdata : 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", iks_has_children);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", escape_size);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", my_strcat);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/iksemel/src/iks", escape);
