#ifndef PAGEHISTORY_H
#define PAGEHISTORY_H

typedef struct { // 0x2024
    /* 0x0000 */ char m_history[32][257];
    /* 0x2020 */ int m_next_index;
} PageHistoryState;

extern "C" {
void *PageHistory(PageHistoryState *history);
void clear(PageHistoryState *history);
void *init(PageHistoryState *history);
int PathMatchesHistoryTop(PageHistoryState *history, char *path);
void push(PageHistoryState *history, char *path);
char *pop(PageHistoryState *history);
char *top(PageHistoryState *history);
}
#endif
