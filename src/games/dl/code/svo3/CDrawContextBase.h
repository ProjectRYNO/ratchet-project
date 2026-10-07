#ifndef CDRAWCONTEXTBASE_H
#define CDRAWCONTEXTBASE_H

struct CDrawContextBase;
typedef struct { // 0x48 (vtable prefix)
    /* 0x00 */ void *unknown00;
    /* 0x04 */ void *unknown04;
    /* 0x08 */ void *unknown08;
    /* 0x0C */ void (*DrawLine)(CDrawContextBase *draw, unsigned int id,
                                  float x, float y, float endX, float endY,
                                  float z, float thickness, unsigned int color, char *tagClass);
    /* 0x10 */ void *unknown10;
    /* 0x14 */ float (*GetStringWidth)(CDrawContextBase *draw, int fontSize, char *text, int length);
    /* 0x18 */ unsigned char unrecovered18[0x2C];
    /* 0x44 */ void (*DrawRectangle)(CDrawContextBase *draw, unsigned int id,
                                       float x, float y, float width, float height,
                                       unsigned int lineColor, unsigned int fillColor,
                                       int lineThickness, int cornerRadius, float z,
                                       unsigned int *gradient, char *tagClass);
} CDrawContextVtablePrefix;

struct CDrawContextBase { // 0x04 (verified prefix)
    /* 0x00 */ CDrawContextVtablePrefix *vtable;
};
#endif
