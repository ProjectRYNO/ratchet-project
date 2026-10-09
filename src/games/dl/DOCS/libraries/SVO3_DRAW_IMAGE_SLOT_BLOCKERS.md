# Drawing and image slot blockers (2026-10-08)

Retail Ghidra and split evidence; original slots retained. No matching or gameplay claim.

## CDrawContextBase::TrimToFitDisplaySize

Candidate `0x28`; retail `0x24`. Retained assembly.

```cpp
extern "C" SECTION(TrimToFitDisplaySize) int TrimToFitDisplaySize(CDrawContextBase *draw, char *text, float length, int fontSize)
{
    return UTF8_TrimStringToFitLength(text, length, fontSize, draw);
}
```

## CDrawContextBase::DrawPopupBackground

Candidate `0x4C`; retail `0x48`. Retained assembly.

```cpp
extern "C" SECTION(DrawPopupBackground) void DrawPopupBackground(CDrawContextBase *draw, float x, float y, float width, float height, unsigned int lineColor, unsigned int fillColor, char *tagClass)
{
    draw->vtable->DrawRectangle(draw, 0, x, y, width, height, lineColor, fillColor, 1, 0, 200000.0f, 0, 0);
}
```

## CDrawContextBase::DrawGridHeader

Candidate `0x114`; retail `0x110`. Retained assembly.

```cpp
extern "C" SECTION(DrawGridHeader) void DrawGridHeader(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, char *tagClass, int selected, int selectedCol, float selectedX, float selectedWidth)
{
    float h = height - 1.0f;
    draw->vtable->DrawRectangle(draw, id, x, y, width, h, lineColor, fillColor, 1, 0, 100000.0f, 0, 0);
    if (selected) draw->vtable->DrawRectangle(draw, id, selectedX, y, selectedWidth, h, fillColor, lineColor, 1, 0, z + 1.0f, 0, 0);
}
```

## CDrawContextBase::DrawGridScrollbars

Candidate `0x328`; retail `0x318`. Retained assembly.

```cpp
extern "C" SECTION(DrawGridScrollbars) void DrawGridScrollbars(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, float vw, float vh, float vp, float vs, float hw, float hh, float hp, float hs, char *tagClass)
{
    float right = x + width + 1.0f;
    if (vp >= 0.0f) {
        draw->vtable->DrawRectangle(draw, id, right, y, vw, vh, 0xFF0000FF, 0xFFFFFFFF, 1, 0, 100000.0f, 0, 0);
        unsigned int up = 0xFF7F7F7F;
        unsigned int down = 0xFF7F7F7F;
        if (vs < 1.0f) {
            if (vp > 0.0f) up = 0xFFFF0000;
            if (vp + vs < 0.98999995f) down = 0xFFFF0000;
        }
        draw->vtable->DrawRectangle(draw, id, right, y, vw, vw, 0xFFFFFFFF, up, 1, 0, 100000.0f, 0, 0);
        draw->vtable->DrawRectangle(draw, id, right, y + vh - vw, vw, vw, 0xFFFFFFFF, down, 1, 0, 100000.0f, 0, 0);
    }
    float bottom = y + height + 1.0f;
    if (hp >= 0.0f) {
        draw->vtable->DrawRectangle(draw, id, x, bottom, hw, hh, 0xFF0000FF, 0xFFFFFFFF, 1, 0, 100000.0f, 0, 0);
        unsigned int left = 0xFF7F7F7F;
        unsigned int rightColor = 0xFF7F7F7F;
        if (hs < 1.0f) {
            if (hp > 0.0f) left = 0xFFFF0000;
            if (hp + hs < 0.98999995f) rightColor = 0xFFFF0000;
        }
        draw->vtable->DrawRectangle(draw, id, x, bottom, hh, hh, 0xFFFFFFFF, left, 1, 0, 100000.0f, 0, 0);
        draw->vtable->DrawRectangle(draw, id, x + hw - hh, bottom, hh, hh, 0xFFFFFFFF, rightColor, 1, 0, 100000.0f, 0, 0);
    }
}
```

## CDrawContextBase::DrawListBox

Candidate `0x250`; retail `0x240`. Retained assembly.

```cpp
extern "C" SECTION(DrawListBox) void DrawListBox(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, int selected, float percent, float sizePercent, char *tagClass)
{
    float right = x + width;
    float bottom = y + height;
    draw->vtable->DrawRectangle(draw, 0, x, y, width, height, lineColor, fillColor, 2, 0, 100000.0f, 0, 0);
    draw->vtable->DrawLine(draw, 0, x, y, right, bottom, 10000.0f, 2.0f, lineColor, tagClass);
    draw->vtable->DrawRectangle(draw, 0, right, y, 15.0f, height, lineColor, fillColor, 2, 0, 100000.0f, 0, 0);
    unsigned int up = 0xFF7F7F7F;
    unsigned int down = 0xFF7F7F7F;
    if (sizePercent < 1.0f) {
        if (percent > 0.0f) up = 0xFFFF0000;
        if (percent + sizePercent < 0.98999995f) down = 0xFFFF0000;
    }
    draw->vtable->DrawRectangle(draw, id, right, y, 15.0f, 15.0f, 0xFFFFFFFF, up, 1, 0, 100000.0f, 0, 0);
    draw->vtable->DrawRectangle(draw, id, right, bottom - 15.0f, 15.0f, 15.0f, 0xFFFFFFFF, down, 1, 0, 100000.0f, 0, 0);
}
```

## CDrawContextBase::DrawImage

Candidate `0x1BC`; retail `0x1AC`. Retained assembly.

```cpp
extern "C" SECTION(DrawImage) void DrawImage(CDrawContextBase *draw, unsigned int id, char *buffer, int x, int y, int w, int h, float u0, float v0, int selected, unsigned int alpha)
{
    float fx = (float)x;
    float fy = (float)y;
    float fw = (float)w;
    float fh = (float)h;
    draw->vtable->DrawRectangle(draw, id, fx, fy, fw, fh, 0xFFFFFF00, 0xFF000000, 1, 0, 100000.0f, 0, 0);
    draw->vtable->DrawLine(draw, id, fx, fy, fx + fw, fy + fh, 100000.0f, 2.0f, 0xFFFFFF00, svoDrawImageLineClass);
    char text[32] __attribute__((aligned(8)));
    memcpy(text, svoDrawImageText, 24);
    draw->vtable->SVDrawText(draw, id, fx + (float)(w / 2), fy + (float)(h / 2), 0xFFFFFFFF, text, strlen(text), 12, 1, svoDrawImageTextClass);
}
```

## CDrawContextBase::DrawStaticImage

Candidate `0x1DC`; retail `0x1B4`. Retained assembly.

```cpp
extern "C" SECTION(DrawStaticImage) void DrawStaticImage(CDrawContextBase *draw, unsigned int id, char *imageName, int index, int x, int y, int w, int h, float u0, float v0, int selected, unsigned int alpha)
{
    float fx = (float)x;
    float fy = (float)y;
    float fw = (float)w;
    float fh = (float)h;
    draw->vtable->DrawRectangle(draw, id, fx, fy, fw, fh, 0xFFFFFF00, 0xFF000000, 1, 0, 100000.0f, 0, 0);
    draw->vtable->DrawLine(draw, id, fx, fy, fx + fw, fy + fh, 100000.0f, 2.0f, 0xFFFFFF00, svoDrawImageLineClass);
    char text[64];
    memset(text, 0, sizeof(text));
    sprintf(text, svoDrawStaticImageFormat, index, imageName);
    draw->vtable->SVDrawText(draw, id, fx + (float)(w / 2), fy + (float)(h / 2), 0xFFFFFFFF, text, strlen(text), 12, 1, svoDrawImageTextClass);
}
```

## ImageTag::getImageTypeAttrib

Candidate `0x9C`; retail `0x8C`. Retained assembly.

```cpp
extern "C" SECTION(getImageTypeAttrib) int getImageTypeAttrib(ImageTagState *self, iks *xml, char *name, unsigned int *type)
{
    char *value = iks_find_attrib(xml, name);
    if (!value) return 0;
    int i = 0;
    char **entry = svoImageTypeStrings;
    do {
        char *candidate = *entry++;
        if (!strcmp(value, candidate)) break;
    } while (++i < 4);
    if (i == 4) return 0;
    *type = i;
    return 1;
}
```

## StaticImageTag::DefaultInit___dupe11

Candidate `0x78`; retail `0x74`. Retained assembly.

```cpp
extern "C" SECTION(DefaultInit___dupe11) char *DefaultInit___dupe11(StaticImageTagState *self)
{
    svstrncpy(self->base.m_tagTypeName, svoStaticImageTagName, 64);
    memset(self->m_link, 0, 128);
    self->m_index = -1;
    self->base.m_fillColor = 0xFFFFFFFF;
    self->base.m_lineColor = 0xFF000000;
    self->m_imageWidth = 0;
    self->m_imageHeight = 0;
    return svstrncpy(self->m_imageName, svoStaticImageUnsetName, 32);
}
```
