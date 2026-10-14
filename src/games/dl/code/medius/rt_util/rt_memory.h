#ifndef RT_MEMORY_H
#define RT_MEMORY_H

#define RT_MEMORY_ALLOC_ERROR 100

// Prototype dltypes.txt layout; retail rt_memory_align_* access pAlloc at 0x0 and pUse at 0x4.
typedef struct { // 0x08
    /* 0x00 */ void *pAlloc;
    /* 0x04 */ void *pUse;
} RT_MEMORY_ALIGNED;

#ifdef __cplusplus
extern "C" {
#endif

// Retail widens the size of rt_memory_allocate(_init_zero) to 64 bits (dsrl32/dsra32 at callers).
int rt_memory_allocate(void **pointer, unsigned long size);
int rt_memory_allocate_init_zero(void **pointer, unsigned long size);
int rt_memory_free(void **pointer);
int rt_memory_align_alloc(RT_MEMORY_ALIGNED *memory, unsigned int size, unsigned short alignment);
int rt_memory_align_alloc_init_zero(RT_MEMORY_ALIGNED *memory, unsigned int size, unsigned short alignment);
int rt_memory_align_free(RT_MEMORY_ALIGNED *memory);
int rt_memory_register_callbacks(void *(*allocate_callback)(int), void (*free_callback)(void *));
int rt_memory_register_another_callback(void *(*realloc_callback)(void *, int));
int rt_memory_get_aligned_address(void **result, void *pointer, unsigned short alignment);

#ifdef __cplusplus
}
#endif

#endif
