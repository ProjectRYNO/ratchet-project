#include "common.h"
// Retain the unresolved wrapper at its original address.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_history_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "PageHistory.h"
#include "SVBrowser.h"
#include "SVOString.h"
#include <string.h>

extern "C" {
extern char svoPageHistorySource[];
extern char svoHistoryHomePage[];
void __SVO_Assert_Handler(const char *file, int line);
int pathIsFullyQualified(CPage *page, char *path);
char *URIStoreFind(char *name);
}
#define HISTORY_SECTION(name) __attribute__((section(".svo_history_" #name)))

// Recovered C currently emits 0x1C bytes for this 0x14-byte slot.
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/PageHistory", PageHistory);

void HISTORY_SECTION(clear) clear(PageHistoryState *history)
{
    init(history);
}

HISTORY_SECTION(init) void * init(PageHistoryState *history)
{
    void *result = memset(history->m_history, 0, sizeof(history->m_history));
    history->m_next_index = 0;
    return result;
}

int HISTORY_SECTION(PathMatchesHistoryTop) PathMatchesHistoryTop(PageHistoryState *history, char *path)
{
    char incoming[257];
    char current[257];
    svstrncpy(incoming, path, sizeof(incoming));
    svstrncpy(current, top(history), sizeof(current));
    char *query = strchr(incoming, '?');
    if (query) *query = 0;
    query = strchr(current, '?');
    if (query) *query = 0;
    return strcmp(incoming, current) == 0;
}

void HISTORY_SECTION(push) push(PageHistoryState *history, char *path)
{
    if (!path || strlen(path) > 256)
        __SVO_Assert_Handler(svoPageHistorySource, 0x3A);
    if (history->m_next_index && PathMatchesHistoryTop(history, path)) return;
    if (!pathIsFullyQualified(GetInstance()->m_pMainPage, path))
        __SVO_Assert_Handler(svoPageHistorySource, 0x57);
    if (history->m_next_index >= 32) {
        if (history->m_next_index != 32)
            __SVO_Assert_Handler(svoPageHistorySource, 0x5D);
        history->m_next_index = (unsigned int)history->m_next_index - 1;
        for (int i = 0; i < 31; ++i)
            svstrncpy(history->m_history[i], history->m_history[i + 1], 257);
    }
    svstrncpy(history->m_history[history->m_next_index], path, 257);
    history->m_next_index = (unsigned int)history->m_next_index + 1;
}

HISTORY_SECTION(pop) char * pop(PageHistoryState *history)
{
    if (history->m_next_index < 1) {
        __SVO_Assert_Handler(svoPageHistorySource, 0x6E);
    } else if (history->m_next_index == 1) {
        char *home = URIStoreFind(svoHistoryHomePage);
        if (home) svstrncpy(history->m_history[0], home, 257);
        return 0;
    } else {
        --history->m_next_index;
    }
    return history->m_history[history->m_next_index];
}

HISTORY_SECTION(top) char * top(PageHistoryState *history)
{
    if (history->m_next_index < 1)
        __SVO_Assert_Handler(svoPageHistorySource, 0x97);
    if (!history->m_history[history->m_next_index - 1][0])
        __SVO_Assert_Handler(svoPageHistorySource, 0x98);
    return history->m_history[history->m_next_index - 1];
}
