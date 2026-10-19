#include "common.h"
#include "rt_circ_buf.h"
#include "rt_memory.h"

#define MEDIUS_CIRC_SECTION(name) __attribute__((section(".medius_circ_" #name)))
#define RT_INVALID_PARAM 2

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_circ_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void *memset(void *pointer, int value, unsigned int size);

int MEDIUS_CIRC_SECTION(rt_circ_buf_create) rt_circ_buf_create(RT_CIRC_BUF *buffer, unsigned int size, unsigned char *scratch)
{
    int result;

    if (!buffer) return RT_INVALID_PARAM;
    if (!size) return RT_INVALID_PARAM;
    memset(buffer, 0, sizeof(RT_CIRC_BUF));
    result = rt_memory_allocate_init_zero((void **)&buffer->pBuf, size);
    if (result) return RT_MEMORY_ALLOC_ERROR;
    if (!buffer->pBuf) return RT_MEMORY_ALLOC_ERROR;
    buffer->pScratchBuf = scratch;
    buffer->nSize = size;
    buffer->nEndPos = 0;
    buffer->nUsed = 0;
    buffer->nStartPos = 0;
    return result;
}

int MEDIUS_CIRC_SECTION(rt_circ_buf_destroy) rt_circ_buf_destroy(RT_CIRC_BUF *buffer)
{
    if (!buffer) return RT_INVALID_PARAM;
    if (buffer->pBuf) rt_memory_free((void **)&buffer->pBuf);
    buffer->nStartPos = 0;
    buffer->nEndPos = 0;
    buffer->nSize = 0;
    buffer->nUsed = 0;
    return 0;
}

int MEDIUS_CIRC_SECTION(rt_circ_buf_clear) rt_circ_buf_clear(RT_CIRC_BUF *buffer)
{
    if (!buffer) return RT_INVALID_PARAM;
    buffer->nStartPos = 0;
    buffer->nEndPos = 0;
    buffer->nUsed = 0;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_circ_buf", rt_circ_buf_free);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_circ_buf", rt_circ_buf_use);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_circ_buf", rt_circ_buf_store);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_circ_buf", rt_circ_buf_copy);

int MEDIUS_CIRC_SECTION(rt_circ_buf_normalize) rt_circ_buf_normalize(RT_CIRC_BUF *buffer, int force)
{
    if (!buffer) return RT_INVALID_PARAM;
    if (force && !buffer->pScratchBuf) return RT_CIRC_BUF_NO_SCRATCH_BUF;
    return rt_circ_buf_normalize_with_buf(buffer, force, buffer->pScratchBuf);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_circ_buf", rt_circ_buf_normalize_with_buf);

int MEDIUS_CIRC_SECTION(rt_circ_buf_get_used) rt_circ_buf_get_used(RT_CIRC_BUF *buffer, unsigned int *used)
{
    if (!buffer) return RT_INVALID_PARAM;
    if (!used) return RT_INVALID_PARAM;
    *used = buffer->nUsed;
    return 0;
}

int MEDIUS_CIRC_SECTION(rt_circ_buf_get_used_nowrap) rt_circ_buf_get_used_nowrap(RT_CIRC_BUF *buffer, unsigned int *used)
{
    if (!buffer) return RT_INVALID_PARAM;
    if (!used) return RT_INVALID_PARAM;
    if (buffer->nUsed) {
        if (buffer->nStartPos < buffer->nEndPos)
            *used = buffer->nEndPos - buffer->nStartPos;
        else
            *used = buffer->nSize - buffer->nStartPos;
    } else {
        *used = 0;
    }
    return 0;
}

int MEDIUS_CIRC_SECTION(rt_circ_buf_get_avail) rt_circ_buf_get_avail(RT_CIRC_BUF *buffer, unsigned int *avail)
{
    if (!buffer) return RT_INVALID_PARAM;
    if (!avail) return RT_INVALID_PARAM;
    *avail = buffer->nSize - buffer->nUsed;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_circ_buf", rt_circ_buf_get_avail_nowrap);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_circ_buf", rt_circ_buf_get_start_used_ptr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_circ_buf", rt_circ_buf_get_start_avail_ptr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_circ_buf", rt_circ_buf_is_wrapped);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_circ_buf", func_01EA73F8);
