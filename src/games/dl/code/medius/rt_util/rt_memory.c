#include "common.h"

#define MEDIUS_MEMORY_SECTION(name) __attribute__((section(".medius_memory_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_memory_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void free(void *pointer);
extern void *(*gpfMallocCallback)(int size);
extern void (*gpfFreeCallback)(void *pointer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_memory", rt_memory_allocate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_memory", func_01EA9548);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_memory", rt_memory_allocate_init_zero);

int MEDIUS_MEMORY_SECTION(rt_memory_free) rt_memory_free(void **pointer)
{
    if (*pointer) {
        if (!gpfFreeCallback) {
            free(*pointer);
            *pointer = 0;
        } else {
            gpfFreeCallback(*pointer);
            *pointer = 0;
        }
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_memory", rt_memory_align_alloc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_memory", rt_memory_align_alloc_init_zero);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_memory", rt_memory_align_free);

int MEDIUS_MEMORY_SECTION(rt_memory_register_callbacks) rt_memory_register_callbacks(
    void *(*allocate_callback)(int), void (*free_callback)(void *))
{
    gpfMallocCallback = allocate_callback;
    gpfFreeCallback = free_callback;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_memory", rt_memory_register_another_callback);

int MEDIUS_MEMORY_SECTION(rt_memory_get_aligned_address) rt_memory_get_aligned_address(
    void **result, void *pointer, unsigned short alignment)
{
    unsigned int remainder;

    if (!result || !pointer)
        return 100;
    *result = pointer;
    if (alignment > 1) {
        remainder = (unsigned int)pointer % alignment;
        if (remainder)
            *result = (void *)((unsigned int)pointer + (alignment - remainder));
    }
    return 0;
}
