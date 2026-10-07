#ifndef SVDISPLAYBUFFER_H
#define SVDISPLAYBUFFER_H
struct SVTag;
typedef struct { // 0x408
    /* 0x000 */ unsigned char unrecovered[8];
    /* 0x008 */ SVTag *tagList[256];
} SVDisplayBufferState;
#endif
