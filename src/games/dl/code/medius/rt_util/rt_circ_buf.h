#ifndef RT_CIRC_BUF_H
#define RT_CIRC_BUF_H

#define RT_CIRC_BUF_ERROR 200
#define RT_CIRC_BUF_NO_SCRATCH_BUF 201

// Prototype dltypes.txt layout; retail rt_circ_buf_* access every field at these offsets.
typedef struct { // 0x18
    /* 0x00 */ unsigned int nStartPos;
    /* 0x04 */ unsigned int nEndPos;
    /* 0x08 */ unsigned int nSize;
    /* 0x0C */ unsigned int nUsed;
    /* 0x10 */ unsigned char *pBuf;
    /* 0x14 */ unsigned char *pScratchBuf;
} RT_CIRC_BUF;

#ifdef __cplusplus
extern "C" {
#endif

int rt_circ_buf_create(RT_CIRC_BUF *buffer, unsigned int size, unsigned char *scratch);
int rt_circ_buf_destroy(RT_CIRC_BUF *buffer);
int rt_circ_buf_clear(RT_CIRC_BUF *buffer);
int rt_circ_buf_free(RT_CIRC_BUF *buffer, unsigned int size);
int rt_circ_buf_use(RT_CIRC_BUF *buffer, unsigned int size);
int rt_circ_buf_store(RT_CIRC_BUF *buffer, unsigned char *source, unsigned int size);
int rt_circ_buf_copy(unsigned char *destination, RT_CIRC_BUF *buffer, unsigned int size);
int rt_circ_buf_normalize(RT_CIRC_BUF *buffer, int force);
int rt_circ_buf_normalize_with_buf(RT_CIRC_BUF *buffer, int force, unsigned char *scratch);
int rt_circ_buf_get_used(RT_CIRC_BUF *buffer, unsigned int *used);
int rt_circ_buf_get_used_nowrap(RT_CIRC_BUF *buffer, unsigned int *used);
int rt_circ_buf_get_avail(RT_CIRC_BUF *buffer, unsigned int *avail);
int rt_circ_buf_get_avail_nowrap(RT_CIRC_BUF *buffer, unsigned int *avail);
int rt_circ_buf_get_start_used_ptr(RT_CIRC_BUF *buffer, unsigned char **pointer);
int rt_circ_buf_get_start_avail_ptr(RT_CIRC_BUF *buffer, unsigned char **pointer);
int rt_circ_buf_is_wrapped(RT_CIRC_BUF *buffer, int *wrapped);

#ifdef __cplusplus
}
#endif

#endif
