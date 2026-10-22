#include "common.h"
#include "rt_list_buf.h"

#define MEDIUS_LIST_BUF_SECTION(name) __attribute__((section(".medius_list_buf_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_list_buf_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#define RT_INVALID_PARAM 2

#ifndef NULL
#define NULL ((void *)0)
#endif

extern void *memset(void *pointer, int value, unsigned int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);
extern int rt_memory_allocate(void **pointer, unsigned long size);
extern int rt_memory_free(void **pointer);

unsigned char *pool_alloc(RT_LIST_BUF_POOL *pPool, unsigned int nBytes);
void pool_free(RT_LIST_BUF_POOL *pPool, unsigned char *pBuf);

int MEDIUS_LIST_BUF_SECTION(rt_list_buf_create_pool) rt_list_buf_create_pool(RT_LIST_BUF_POOL *pBufPool, unsigned int nPoolSize, unsigned int nBlockSize)
{
    int result;

    if (!pBufPool) return RT_INVALID_PARAM;
    if (nPoolSize & 3) return RT_INVALID_PARAM;
    if (nBlockSize & 3) return RT_INVALID_PARAM;
    if (nBlockSize >= nPoolSize) return RT_INVALID_PARAM;
    memset(pBufPool, 0, sizeof(*pBufPool));
    result = rt_memory_allocate((void **)&pBufPool->pBuf, nPoolSize);
    if (result) return result;
    pBufPool->nBufSize = nPoolSize;
    pBufPool->nBlkSize = nBlockSize;
    pBufPool->nBufRefCnt = 0;
    pBufPool->nBlks = nPoolSize / nBlockSize;
    if (nPoolSize % nBlockSize < pBufPool->nBlks) pBufPool->nBlks -= (pBufPool->nBlks - nPoolSize % nBlockSize) / nBlockSize;
    pBufPool->pTbl = pBufPool->pBuf + pBufPool->nBlks * pBufPool->nBlkSize;
    memset(pBufPool->pTbl, 0, pBufPool->nBlks);
    return 0;
}

int MEDIUS_LIST_BUF_SECTION(rt_list_buf_destroy_pool) rt_list_buf_destroy_pool(RT_LIST_BUF_POOL *pBufPool)
{
    if (!pBufPool) return RT_INVALID_PARAM;
    rt_memory_free((void **)&pBufPool->pBuf);
    memset(pBufPool, 0, sizeof(*pBufPool));
    return 0;
}

int MEDIUS_LIST_BUF_SECTION(rt_list_buf_get_pool_used) rt_list_buf_get_pool_used(RT_LIST_BUF_POOL *pBufPool, unsigned int *pnPoolUsed)
{
    unsigned int i;
    unsigned int count = 0;

    if (!pBufPool) return RT_INVALID_PARAM;
    if (!pnPoolUsed) return RT_INVALID_PARAM;
    *pnPoolUsed = 0;
    for (i = 0; i < pBufPool->nBlks; i++) {
        if (pBufPool->pTbl[i]) count++;
    }
    *pnPoolUsed = count * pBufPool->nBlkSize;
    return 0;
}

int MEDIUS_LIST_BUF_SECTION(rt_list_buf_create) rt_list_buf_create(RT_LIST_BUF *pListBuf, RT_LIST_BUF_POOL *pBufPool, unsigned int nSize)
{
    if (!pListBuf) return RT_INVALID_PARAM;
    if (!pBufPool) return RT_INVALID_PARAM;
    if (nSize <= sizeof(RT_LIST_NODE)) return RT_INVALID_PARAM;
    memset(pListBuf, 0, sizeof(*pListBuf));
    pListBuf->pBuf = pBufPool;
    pListBuf->nBufSize = nSize;
    pBufPool->nBufRefCnt++;
    return 0;
}

void MEDIUS_LIST_BUF_SECTION(rt_list_buf_destroy) rt_list_buf_destroy(RT_LIST_BUF *pListBuf)
{
    if (!pListBuf || !pListBuf->pBuf || !pListBuf->nBufSize) return;
    rt_list_buf_clear(pListBuf);
    pListBuf->pBuf->nBufRefCnt--;
    memset(pListBuf, 0, sizeof(*pListBuf));
}

void MEDIUS_LIST_BUF_SECTION(rt_list_buf_clear) rt_list_buf_clear(RT_LIST_BUF *pListBuf)
{
    RT_LIST_NODE *pNode;

    if (!pListBuf || !pListBuf->pBuf || !pListBuf->nBufSize) return;
    for (pNode = pListBuf->pHead; pNode; pNode = pNode->next) {
        rt_list_buf_remove(pListBuf, pNode);
    }
}

int MEDIUS_LIST_BUF_SECTION(rt_list_buf_insert) rt_list_buf_insert(RT_LIST_BUF *pListBuf, RT_LIST_NODE *pListNode, RT_DATA_VECTOR *pVector)
{
    RT_LIST_NODE *pNewNode;
    unsigned char *cursor;
    unsigned int nodeSize;
    int i;

    if (!pListBuf || !pListBuf->pBuf || !pListBuf->nBufSize) return RT_INVALID_PARAM;
    if (!pVector) return RT_INVALID_PARAM;
    if (!pVector->nTotalSize) return RT_INVALID_PARAM;
    nodeSize = pVector->nTotalSize + sizeof(RT_LIST_NODE);
    if (pListBuf->nBufSize - pListBuf->nBufUsed < nodeSize) return RT_LIST_BUF_FULL;
    cursor = pool_alloc(pListBuf->pBuf, nodeSize);
    if (!cursor) return RT_LIST_BUF_FULL;
    pNewNode = (RT_LIST_NODE *)cursor;
    pNewNode->nDataSize = pVector->nTotalSize;
    cursor = (unsigned char *)(pNewNode + 1);
    for (i = pVector->nLength - 1; i >= 0; i--) {
        if (pVector->aData[i].pData && pVector->aData[i].nSize) {
            memcpy(cursor, pVector->aData[i].pData, pVector->aData[i].nSize);
            cursor += pVector->aData[i].nSize;
        }
    }
    if (!pListNode) {
        pNewNode->next = pListBuf->pHead;
        pListBuf->pHead = pNewNode;
    } else {
        pNewNode->next = pListNode->next;
        pListNode->next = pNewNode;
    }
    pListBuf->nBufUsed += nodeSize;
    return 0;
}

int MEDIUS_LIST_BUF_SECTION(rt_list_buf_set_new_head) rt_list_buf_set_new_head(RT_LIST_BUF *pListBuf, RT_DATA_VECTOR *pVector)
{
    return rt_list_buf_insert(pListBuf, NULL, pVector);
}

int MEDIUS_LIST_BUF_SECTION(rt_list_buf_remove) rt_list_buf_remove(RT_LIST_BUF *pListBuf, RT_LIST_NODE *pListNode)
{
    RT_LIST_NODE *pPrev;

    if (!pListBuf || !pListBuf->pBuf || !pListBuf->nBufSize) return RT_INVALID_PARAM;
    if (!pListNode) return RT_INVALID_PARAM;
    if (pListNode == pListBuf->pHead) {
        pListBuf->pHead = pListNode->next;
        pListBuf->nBufUsed -= pListNode->nDataSize + sizeof(RT_LIST_NODE);
        pool_free(pListBuf->pBuf, pListNode);
        return 0;
    }
    for (pPrev = pListBuf->pHead; pPrev; pPrev = pPrev->next) {
        if (pPrev->next == pListNode) {
            pPrev->next = pListNode->next;
            pListBuf->nBufUsed -= pListNode->nDataSize + sizeof(RT_LIST_NODE);
            pool_free(pListBuf->pBuf, pListNode);
            return 0;
        }
    }
    return RT_LIST_BUF_ERROR;
}

int MEDIUS_LIST_BUF_SECTION(rt_list_buf_append_data) rt_list_buf_append_data(RT_LIST_BUF *pListBuf, RT_LIST_NODE **ppListNode, RT_DATA_VECTOR *pVector, unsigned int offset)
{
    RT_LIST_NODE *pNewNode;
    RT_LIST_NODE *pPrev;
    unsigned char *pDest;
    int i;

    if (!pListBuf || !pListBuf->pBuf || !pListBuf->nBufSize) return RT_INVALID_PARAM;
    if (!*ppListNode) return RT_INVALID_PARAM;
    if (!pVector) return RT_INVALID_PARAM;
    if (!pVector->nTotalSize) return RT_INVALID_PARAM;
    if (pListBuf->nBufSize - pListBuf->nBufUsed < pVector->nTotalSize + (*ppListNode)->nDataSize + sizeof(RT_LIST_NODE))
        return RT_LIST_BUF_FULL;
    pDest = pool_alloc(pListBuf->pBuf, pVector->nTotalSize + (*ppListNode)->nDataSize + sizeof(RT_LIST_NODE));
    if (!pDest) return RT_LIST_BUF_FULL;
    pNewNode = (RT_LIST_NODE *)pDest;
    pDest = (unsigned char *)(pNewNode + 1);
    pNewNode->nDataSize = pVector->nTotalSize + (*ppListNode)->nDataSize;
    memcpy(pDest, *ppListNode + 1, offset);
    pDest += offset;
    for (i = pVector->nLength - 1; i >= 0; i--) {
        if (pVector->aData[i].pData && pVector->aData[i].nSize) {
            memcpy(pDest, pVector->aData[i].pData, pVector->aData[i].nSize);
            pDest += pVector->aData[i].nSize;
        }
    }
    if (pListBuf->pHead == *ppListNode) {
        pNewNode->next = (*ppListNode)->next;
        pListBuf->pHead = pNewNode;
        pool_free(pListBuf->pBuf, (unsigned char *)*ppListNode);
        *ppListNode = pNewNode;
        pListBuf->nBufUsed += pVector->nTotalSize;
        return 0;
    }
    for (pPrev = pListBuf->pHead; pPrev; pPrev = pPrev->next) {
        if (*ppListNode == pPrev->next) {
            pNewNode->next = (*ppListNode)->next;
            pPrev->next = pNewNode;
        pool_free(pListBuf->pBuf, (unsigned char *)*ppListNode);
        *ppListNode = pNewNode;
        pListBuf->nBufUsed += pVector->nTotalSize;
        return 0;
        }
    }
    return RT_LIST_BUF_ERROR;
}

RT_LIST_NODE *MEDIUS_LIST_BUF_SECTION(rt_list_buf_get_tail) rt_list_buf_get_tail(RT_LIST_BUF *pListBuf)
{
    RT_LIST_NODE *pNode = NULL;
    RT_LIST_NODE *pNext;

    if (pListBuf && pListBuf->pBuf && pListBuf->nBufSize && pListBuf->pHead) {
        pNode = pListBuf->pHead;
        while ((pNext = pNode ? pNode->next : NULL)) pNode = pNext;
    }
    return pNode;
}

int MEDIUS_LIST_BUF_SECTION(rt_list_buf_resize_buffer) rt_list_buf_resize_buffer(RT_LIST_BUF *pListBuf, unsigned int nSize)
{
    if (!pListBuf || !pListBuf->pBuf || !pListBuf->nBufSize) return RT_INVALID_PARAM;
    if (nSize <= sizeof(RT_LIST_NODE)) return RT_INVALID_PARAM;
    pListBuf->nBufSize = nSize;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_list_buf", pool_alloc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_list_buf", pool_free);
