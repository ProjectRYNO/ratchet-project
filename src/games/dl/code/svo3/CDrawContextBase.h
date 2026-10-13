#ifndef CDRAWCONTEXTBASE_H
#define CDRAWCONTEXTBASE_H

struct CDrawContextBase;
typedef struct { // 0x9C (vtable prefix)
    /* 0x00 */ void *unknown00;
    /* 0x04 */ void *unknown04;
    /* 0x08 */ void *unknown08;
    /* 0x0C */ void (*DrawLine)(CDrawContextBase *draw, unsigned int id,
                                  float x, float y, float endX, float endY,
                                  float z, float thickness, unsigned int color, char *tagClass);
    /* 0x10 */ void (*SVDrawText)(CDrawContextBase *draw, unsigned int id, float x, float y,
                                    unsigned int color, char *text, int length, int fontSize,
                                    int alignment, char *tagClass);
    /* 0x14 */ float (*GetStringWidth)(CDrawContextBase *draw, int fontSize, char *text, int length);
    /* 0x18 */ void (*DrawInputBox)(CDrawContextBase *, unsigned int, float, float, float, float, float, unsigned int, unsigned int, unsigned int, int, char *, int, int, char *);
    /* 0x1C */ void (*DrawButton)(CDrawContextBase *, unsigned int, float, float, float, float, float, unsigned int, unsigned int, unsigned int, int, char *, int, int, int, char *, int);
    /* 0x20 */ void (*DrawSelect)(CDrawContextBase *, unsigned int, float, float, float, float, float, unsigned int, unsigned int, unsigned int, int, char *, int, int, int, char *);
    /* 0x24 */ void (*DrawRadioButton)(CDrawContextBase *, unsigned int, float, float, float, float, float, unsigned int, unsigned int, unsigned int, int, int, char *, int, int, int, char *);
    /* 0x28 */ void (*DrawCheckbox)(CDrawContextBase *, unsigned int, float, float, float, float, float, unsigned int, unsigned int, unsigned int, int, int, char *, int, int, int, char *);
    /* 0x2C */ void (*DrawTicker)(CDrawContextBase *, unsigned int, float, float, float, float, int, char *, int, unsigned int, int, char *);
    /* 0x30 */ void (*DrawGridBorder)(CDrawContextBase *, unsigned int, float, float, float, float, float, unsigned int, unsigned int, char *);
    /* 0x34 */ void (*DrawGridHeader)(CDrawContextBase *, unsigned int, float, float, float, float, float, float, float, unsigned int, unsigned int, char *, int);
    /* 0x38 */ void (*DrawGridRow)(CDrawContextBase *, unsigned int, float, float, float, float, float, int, int, char *);
    /* 0x3C */ void (*DrawGridCell)(CDrawContextBase *, unsigned int, float, float, float, float, float, unsigned int, unsigned int, unsigned int, int, char *, int, int, int, char *);
    /* 0x40 */ void (*DrawGridScrollbars)(CDrawContextBase *, unsigned int, char *, float, float, float, float, float, float, float, float, float, float, float, float, float);
    /* 0x44 */ void (*DrawRectangle)(CDrawContextBase *draw, unsigned int id,
                                       float x, float y, float width, float height,
                                       unsigned int lineColor, unsigned int fillColor,
                                       int lineThickness, int cornerRadius, float z,
                                       unsigned int *gradient, char *tagClass);
    /* 0x48 */ void (*DrawTextArea)(CDrawContextBase *, unsigned int, float, float, float, float, float, unsigned int, unsigned int, unsigned int, int, float, float, float, char *, int, int);
    /* 0x4C */ void (*DrawListBox)(CDrawContextBase *, unsigned int, float, float, float, float, float, unsigned int, unsigned int, float, float, int, char *);
    /* 0x50 */ void *unknown50;
    /* 0x54 */ void (*StoreDownloadedImage)(CDrawContextBase *, int, char *, unsigned short, unsigned short);
    /* 0x58 */ void (*DrawPopupBackground)(CDrawContextBase *draw, float x, float y,
                                           float width, float height, unsigned int lineColor,
                                           unsigned int fillColor, char *tagClass);
    /* 0x5C */ void (*DrawGenericListboxFrame)(CDrawContextBase *, unsigned int, float, float, float, float, unsigned int, unsigned int, int, float, char *);
    /* 0x60 */ void (*DrawGenericListboxEntry)(CDrawContextBase *, unsigned int, char *, unsigned int, int, int, unsigned int, unsigned int, char *);
    /* 0x64 */ unsigned char unrecovered64[0x14];
    /* 0x78 */ void (*AnimateHighlight)(CDrawContextBase *, int fromTagID, int toTagID);
    /* 0x7C */ unsigned char unrecovered7C[0x04];
    /* 0x80 */ int (*RenderAssert)(CDrawContextBase *, char *message);
    /* 0x84 */ void (*DrawImage)(CDrawContextBase *, unsigned int, char *, int, int, int, int, float, float, int, unsigned int);
    /* 0x88 */ void (*DrawStaticImage)(CDrawContextBase *, unsigned int, char *, int, int, int, int, int, float, float, int, unsigned int);
    /* 0x8C */ void (*InitImage)(CDrawContextBase *, unsigned int, char *, int, int, int, int, float, float);
    /* 0x90 */ void (*InitStaticImage)(CDrawContextBase *, unsigned int, int, int, int, int, float, float);
    /* 0x94 */ void (*DestroyImage)(CDrawContextBase *, int);
    /* 0x98 */ void (*DrawDownloadThrobber)(CDrawContextBase *, unsigned int tagid, float x, float y, float width, float height, char *tagClass);
} CDrawContextVtablePrefix;

struct CDrawContextBase { // 0x04 (verified prefix)
    /* 0x00 */ CDrawContextVtablePrefix *vtable;
};
#endif
