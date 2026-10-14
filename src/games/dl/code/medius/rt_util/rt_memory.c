#include "common.h"
#include "rt_memory.h"

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

extern void *malloc(unsigned int size);
extern void free(void *pointer);
extern void *memset(void *pointer, int value, unsigned int size);
extern void *(*gpfMallocCallback)(int size);
extern void *(*gpfReallocCallback)(void *pointer, int size);
extern void (*gpfFreeCallback)(void *pointer);

int MEDIUS_MEMORY_SECTION(rt_memory_allocate) rt_memory_allocate(void **pointer, unsigned long size)
{
    if (!gpfMallocCallback) {
        *pointer = malloc(size);
        if (!*pointer) return RT_MEMORY_ALLOC_ERROR;
    } else {
        *pointer = gpfMallocCallback(size);
        if (!*pointer) return RT_MEMORY_ALLOC_ERROR;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_memory", func_01EA9548);

int MEDIUS_MEMORY_SECTION(rt_memory_allocate_init_zero) rt_memory_allocate_init_zero(void **pointer, unsigned long size)
{
    int result;

    if (!pointer) return RT_MEMORY_ALLOC_ERROR;
    *pointer = 0;
    result = rt_memory_allocate(pointer, size);
    if (result) return result;
    if (*pointer) {
        memset(*pointer, 0, size);
        return 0;
    }
    return RT_MEMORY_ALLOC_ERROR;
}

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

int MEDIUS_MEMORY_SECTION(rt_memory_align_alloc) rt_memory_align_alloc(RT_MEMORY_ALIGNED *memory, unsigned int size,
    unsigned short alignment)
{
    int result;

    if (!memory || !size) return RT_MEMORY_ALLOC_ERROR;
    memory->pAlloc = 0;
    memory->pUse = 0;
    if (alignment > 1) {
        size += alignment - 1;
        size += alignment - size % alignment;
    }
    result = rt_memory_allocate(&memory->pAlloc, size);
    if (!result)
        result = rt_memory_get_aligned_address(&memory->pUse, memory->pAlloc, alignment);
    return result;
}

int MEDIUS_MEMORY_SECTION(rt_memory_align_alloc_init_zero) rt_memory_align_alloc_init_zero(RT_MEMORY_ALIGNED *memory,
    unsigned int size, unsigned short alignment)
{
    int result = RT_MEMORY_ALLOC_ERROR;

    if (memory && size) {
        memory->pAlloc = 0;
        memory->pUse = 0;
        result = rt_memory_align_alloc(memory, size, alignment);
        if (result) return result;
        if (memory->pUse) {
            memset(memory->pUse, 0, size);
            return 0;
        }
        result = RT_MEMORY_ALLOC_ERROR;
    }
    return result;
}

int MEDIUS_MEMORY_SECTION(rt_memory_align_free) rt_memory_align_free(RT_MEMORY_ALIGNED *memory)
{
    int result;

    if (!memory) return RT_MEMORY_ALLOC_ERROR;
    if (memory->pAlloc) {
        result = rt_memory_free(&memory->pAlloc);
        if (result) return result;
        memory->pAlloc = 0;
    }
    memory->pUse = 0;
    return 0;
}

int MEDIUS_MEMORY_SECTION(rt_memory_register_callbacks) rt_memory_register_callbacks(
    void *(*allocate_callback)(int), void (*free_callback)(void *))
{
    gpfMallocCallback = allocate_callback;
    gpfFreeCallback = free_callback;
    return 0;
}

int MEDIUS_MEMORY_SECTION(rt_memory_register_another_callback) rt_memory_register_another_callback(
    void *(*realloc_callback)(void *, int))
{
    gpfReallocCallback = realloc_callback;
    return 0;
}

int MEDIUS_MEMORY_SECTION(rt_memory_get_aligned_address) rt_memory_get_aligned_address(
    void **result, void *pointer, unsigned short alignment)
{
    unsigned int remainder;

    if (!result || !pointer)
        return RT_MEMORY_ALLOC_ERROR;
    *result = pointer;
    if (alignment > 1) {
        remainder = (unsigned int)pointer % alignment;
        if (remainder)
            *result = (void *)((unsigned int)pointer + (alignment - remainder));
    }
    return 0;
}
