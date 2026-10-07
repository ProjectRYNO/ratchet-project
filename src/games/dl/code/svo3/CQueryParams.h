#ifndef CQUERYPARAMS_H
#define CQUERYPARAMS_H

struct CMemoryContextBaseState;

typedef struct { // 0x08
    /* 0x00 */ char *key;
    /* 0x04 */ char *value;
} CQueryParam;

typedef struct { // 0x404
    /* 0x000 */ CQueryParam m_params[128];
    /* 0x400 */ int m_iIndex;
} CQueryParamListState;

extern "C" {
void *CQueryParamList(CQueryParamListState *list);
void _CQueryParamList(CQueryParamListState *list, unsigned int flags);
int toString(CQueryParamListState *list, char *text, int capacity);
void Set(CQueryParamListState *list, char *key, char *value, CMemoryContextBaseState *memory);
void FreeAll(CQueryParamListState *list, CMemoryContextBaseState *memory);
void SetFromParamList(CQueryParamListState *list, CQueryParamListState *source,
                      CMemoryContextBaseState *memory);
int NotEmpty(CQueryParamListState *list);
int GetParamCount(CQueryParamListState *list);
}

#endif
