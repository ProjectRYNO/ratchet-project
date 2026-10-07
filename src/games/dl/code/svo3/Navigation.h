#ifndef NAVIGATION_H
#define NAVIGATION_H

typedef struct { // 0x10
    /* 0x00 */ char *up;
    /* 0x04 */ char *down;
    /* 0x08 */ char *left;
    /* 0x0C */ char *right;
} CNavInfoState;
extern "C" void reset___dupe2(CNavInfoState *navigation);
#endif
