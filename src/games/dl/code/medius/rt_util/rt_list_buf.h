#ifndef RT_LIST_BUF_H
#define RT_LIST_BUF_H

#define RT_LIST_BUF_ERROR 300
#define RT_LIST_BUF_FULL 301
#define RT_DATA_VECTOR_MAX 8

// Names and layouts from the retail ELF debug information (rt_util/rt_list_buf.c).
typedef struct { // 0x18
    /* 0x00 */ unsigned int nBufRefCnt;
    /* 0x04 */ unsigned int nBufSize;
    /* 0x08 */ unsigned int nBlkSize;
    /* 0x0C */ unsigned int nBlks;
    /* 0x10 */ unsigned char *pBuf;
    /* 0x14 */ unsigned char *pTbl;
} RT_LIST_BUF_POOL;

// Node payload follows the header directly.
typedef struct RT_LIST_NODE { // 0x8
    /* 0x00 */ unsigned int nDataSize;
    /* 0x04 */ struct RT_LIST_NODE *next;
} RT_LIST_NODE;

typedef struct { // 0x10
    /* 0x00 */ unsigned int nBufSize;
    /* 0x04 */ unsigned int nBufUsed;
    /* 0x08 */ RT_LIST_BUF_POOL *pBuf;
    /* 0x0C */ RT_LIST_NODE *pHead;
} RT_LIST_BUF;

typedef struct { // 0x8
    /* 0x00 */ void *pData;
    /* 0x04 */ unsigned int nSize;
} RT_DATA_INFO;

typedef struct { // 0x48
    /* 0x00 */ RT_DATA_INFO aData[RT_DATA_VECTOR_MAX];
    /* 0x40 */ unsigned int nTotalSize;
    /* 0x44 */ int nLength;
} RT_DATA_VECTOR;

#ifdef __cplusplus
extern "C" {
#endif

int rt_list_buf_create_pool(RT_LIST_BUF_POOL *pBufPool, unsigned int nPoolSize, unsigned int nBlockSize);
int rt_list_buf_destroy_pool(RT_LIST_BUF_POOL *pBufPool);
int rt_list_buf_get_pool_used(RT_LIST_BUF_POOL *pBufPool, unsigned int *pnPoolUsed);
int rt_list_buf_create(RT_LIST_BUF *pListBuf, RT_LIST_BUF_POOL *pBufPool, unsigned int nSize);
void rt_list_buf_destroy(RT_LIST_BUF *pListBuf);
void rt_list_buf_clear(RT_LIST_BUF *pListBuf);
int rt_list_buf_insert(RT_LIST_BUF *pListBuf, RT_LIST_NODE *pListNode, RT_DATA_VECTOR *pVector);
int rt_list_buf_set_new_head(RT_LIST_BUF *pListBuf, RT_DATA_VECTOR *pVector);
int rt_list_buf_remove(RT_LIST_BUF *pListBuf, RT_LIST_NODE *pListNode);
int rt_list_buf_append_data(RT_LIST_BUF *pListBuf, RT_LIST_NODE **ppListNode, RT_DATA_VECTOR *pVector, unsigned int offset);
RT_LIST_NODE *rt_list_buf_get_tail(RT_LIST_BUF *pListBuf);
int rt_list_buf_resize_buffer(RT_LIST_BUF *pListBuf, unsigned int nSize);

#ifdef __cplusplus
}
#endif

#endif
