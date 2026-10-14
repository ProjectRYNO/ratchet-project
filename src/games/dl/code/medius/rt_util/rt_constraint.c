#include "common.h"
#include "rt_constraint.h"
#include "rt_string.h"

#define MEDIUS_CONSTRAINT_SECTION(name) __attribute__((section(".medius_constraint_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_constraint_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

int MEDIUS_CONSTRAINT_SECTION(rt_constraint_check_RT_U1BYTE) rt_constraint_check_RT_U1BYTE(
    unsigned char *value, RT_U1BYTE_CONSTRAINT *constraint)
{
    return *value >= constraint->lowVal && *value <= constraint->highVal;
}

int MEDIUS_CONSTRAINT_SECTION(rt_constraint_check_RT_4BYTE) rt_constraint_check_RT_4BYTE(
    int *value, RT_4BYTE_CONSTRAINT *constraint)
{
    return *value >= constraint->lowVal && *value <= constraint->highVal;
}

int MEDIUS_CONSTRAINT_SECTION(rt_constraint_check_RT_U4BYTE) rt_constraint_check_RT_U4BYTE(
    unsigned int *value, RT_U4BYTE_CONSTRAINT *constraint)
{
    return *value >= constraint->lowVal && *value <= constraint->highVal;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_constraint", func_01EA8E68);

int MEDIUS_CONSTRAINT_SECTION(rt_constraint_check_RT_CSTRING) rt_constraint_check_RT_CSTRING(
    char *value, RT_CSTRING_CONSTRAINT *constraint)
{
    unsigned int length;

    length = rt_strnlen(value, constraint->maxSize);
    return length >= constraint->minSize && length < constraint->maxSize;
}
