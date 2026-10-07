#include "CQueryParams.h"
#include "CMemoryContextBase.h"
#include "SVOString.h"
#include "HttpUtils.h"
#include <string.h>

extern "C" {
extern char svoQueryParamsSource[];
CMemoryContextBaseState *GetMemoryContext(void);
void __SVO_Assert_Handler(const char *file, int line);
void __builtin_delete(void *memory);
}
#define SVO_QUERY_SECTION(name) __attribute__((section(".svo_query_" #name)))

SVO_QUERY_SECTION(CQueryParamList) void *CQueryParamList(CQueryParamListState *list)
{
    return memset(list, 0, sizeof(*list));
}

void SVO_QUERY_SECTION(_CQueryParamList) _CQueryParamList(
    CQueryParamListState *list, unsigned int flags)
{
    // Retail does not implicitly free the parameter strings here.
    if (flags & 1) __builtin_delete(list);
}

int SVO_QUERY_SECTION(toString) toString(CQueryParamListState *list, char *text, int capacity)
{
    memset(text, 0, capacity);
    char *cursor = text;
    for (unsigned int i = 0; i < 128; ++i) {
        CQueryParam *param = &list->m_params[i];
        if (!param->key || !param->value) break;
        if (cursor != text) *cursor++ = '&';
        cursor += escapeString(param->key, cursor, capacity - (cursor - text));
        *cursor++ = '=';
        cursor += escapeString(param->value, cursor, capacity - (cursor - text));
        if (cursor - text > capacity) {
            __SVO_Assert_Handler(svoQueryParamsSource, 0x4F);
            return 0;
        }
    }
    // Successful serialization consumes the list, using the current memory context.
    FreeAll(list, 0);
    return 1;
}

void SVO_QUERY_SECTION(Set) Set(CQueryParamListState *list, char *key, char *value,
                               CMemoryContextBaseState *memory)
{
    unsigned int keySize = svstrlen(key);
    unsigned int valueSize = svstrlen(value);
    if (!memory) memory = GetMemoryContext();
    if (list->m_params[list->m_iIndex].key) __SVO_Assert_Handler(svoQueryParamsSource, 0x70);
    if (list->m_params[list->m_iIndex].value) __SVO_Assert_Handler(svoQueryParamsSource, 0x71);

    // Re-read the index after each allocation, as in retail's callback-aware stores.
    char *allocated = (char *)svAllocSafe(memory, keySize, 0, 0x74, svoQueryParamsSource);
    list->m_params[list->m_iIndex].key = allocated;
    allocated = (char *)svAllocSafe(memory, valueSize, 0, 0x75, svoQueryParamsSource);
    list->m_params[list->m_iIndex].value = allocated;
    svstrncpy(list->m_params[list->m_iIndex].key, key, keySize);
    svstrncpy(list->m_params[list->m_iIndex].value, value, valueSize);
    list->m_iIndex = (int)((unsigned int)list->m_iIndex + 1);
}

void SVO_QUERY_SECTION(FreeAll) FreeAll(CQueryParamListState *list, CMemoryContextBaseState *memory)
{
    if (!memory) memory = GetMemoryContext();
    for (int i = 0; i < list->m_iIndex; ++i) {
        CQueryParam *param = &list->m_params[i];
        svFreeSafe(memory, param->key);
        param->key = 0;
        svFreeSafe(memory, param->value);
        param->value = 0;
        // A free callback may have modified the key again.
        param->key = 0;
    }
    list->m_iIndex = 0;
}

void SVO_QUERY_SECTION(SetFromParamList) SetFromParamList(CQueryParamListState *list,
    CQueryParamListState *source, CMemoryContextBaseState *memory)
{
    int count = GetParamCount(source);
    for (int i = 0; i < count; ++i) {
        Set(list, source->m_params[i].key, source->m_params[i].value, memory);
    }
}

int SVO_QUERY_SECTION(NotEmpty) NotEmpty(CQueryParamListState *list)
{
    return list->m_iIndex > 0;
}

int SVO_QUERY_SECTION(GetParamCount) GetParamCount(CQueryParamListState *list)
{
    return list->m_iIndex;
}
