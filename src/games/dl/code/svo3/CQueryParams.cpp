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
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_query_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

SVO_QUERY_SECTION(CQueryParamList) void *CQueryParamList(CQueryParamListState *list)
{
    list->m_iIndex = 0;
    return memset(list->m_params, 0, sizeof(list->m_params));
}

void SVO_QUERY_SECTION(_CQueryParamList) _CQueryParamList(
    CQueryParamListState *list, unsigned int flags)
{
    // Retail does not implicitly free the parameter strings here.
    if (flags & 1) { __builtin_delete(list); return; }
}

int SVO_QUERY_SECTION(toString) toString(CQueryParamListState *list, char *text, int capacity)
{
    unsigned int i = 0;
    char *cursor = text;
    memset(text, 0, capacity);
    do {
        if (!list->m_params[i].key) break;
        if (!list->m_params[i].value) break;
        if (cursor != text) *cursor++ = '&';
        cursor += escapeString(list->m_params[i].key, cursor, capacity - (cursor - text));
        *cursor++ = '=';
        cursor += escapeString(list->m_params[i].value, cursor, capacity - (cursor - text));
        if (cursor - text > capacity) {
            __SVO_Assert_Handler(svoQueryParamsSource, 0x4F);
            return 0;
        }
    } while (++i < 128);
    FreeAll(list, 0);
    return 1;
}

void SVO_QUERY_SECTION(Set) Set(CQueryParamListState *list, char *key, char *value,
                               CMemoryContextBaseState *memory)
{
    unsigned int keySize = svstrlen(key);
    unsigned int valueSize = svstrlen(value);
    CMemoryContextBaseState *context;
    if (!memory) context = GetMemoryContext(); else context = memory;
    if (list->m_params[list->m_iIndex].key) __SVO_Assert_Handler(svoQueryParamsSource, 0x70);
    if (list->m_params[list->m_iIndex].value) __SVO_Assert_Handler(svoQueryParamsSource, 0x71);

    // Re-read the index after each allocation, as in retail's callback-aware stores.
    char *allocated = (char *)svAllocSafe(context, keySize, 0, 0x74, svoQueryParamsSource);
    list->m_params[list->m_iIndex].key = allocated;
    allocated = (char *)svAllocSafe(context, valueSize, 0, 0x75, svoQueryParamsSource);
    list->m_params[list->m_iIndex].value = allocated;
    svstrncpy(list->m_params[list->m_iIndex].key, key, keySize);
    svstrncpy(list->m_params[list->m_iIndex].value, value, valueSize);
    list->m_iIndex = (int)((unsigned int)list->m_iIndex + 1);
}

void SVO_QUERY_SECTION(FreeAll) FreeAll(CQueryParamListState *list, CMemoryContextBaseState *memory)
{
    CMemoryContextBaseState *mem;
    if (!memory) mem = GetMemoryContext(); else mem = memory;
    for (int i = 0; i < list->m_iIndex; ++i) {
        svFreeSafe(mem, list->m_params[i].key);
        list->m_params[i].key = 0;
        svFreeSafe(mem, list->m_params[i].value);
        list->m_params[i].value = 0;
        list->m_params[i].key = 0;
        list->m_params[i].value = 0;
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
