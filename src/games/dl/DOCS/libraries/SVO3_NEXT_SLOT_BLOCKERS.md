# SVO3 next-batch slot blockers

Retail/Ghidra/prototype-derived candidates. Behavior tests deferred. Do not widen slots.

## DataTag::getDataTypeAttrib

Candidate `0x98`; retail `0x8C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getDataTypeAttrib) long getDataTypeAttrib(void *tag, iks *xml, char *name, unsigned int *result)
{
    char *value = iks_find_attrib(xml, name);
    if (!value) return 0;
    char **entry = _data_type_strings;
    do {
        if (!strcmp(value, *entry)) {
            *result = entry - _data_type_strings;
            return 1;
        }
    } while (++entry != _data_type_strings + 3);
    return 0;
}
```

## DataTagModule::getDataTypeAttrib___dupe2

Candidate `0x98`; retail `0x8C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getDataTypeAttrib___dupe2) long getDataTypeAttrib___dupe2(void *tag, iks *xml, char *name, unsigned int *result)
{
    char *value = iks_find_attrib(xml, name);
    if (!value) return 0;
    char **entry = _data_type_strings;
    do {
        if (!strcmp(value, *entry)) {
            *result = entry - _data_type_strings;
            return 1;
        }
    } while (++entry != _data_type_strings + 3);
    return 0;
}
```

## ImageTag::getImageTypeAttrib

Candidate `0x98`; retail `0x8C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getImageTypeAttrib) long getImageTypeAttrib(void *tag, iks *xml, char *name, unsigned int *result)
{
    char *value = iks_find_attrib(xml, name);
    if (!value) return 0;
    char **entry = svoImageTypeStrings;
    do {
        if (!strcmp(value, *entry)) {
            *result = entry - svoImageTypeStrings;
            return 1;
        }
    } while (++entry != svoImageTypeStrings + 4);
    return 0;
}
```

## TickerTag::getTickerTypeAttrib

Candidate `0x9C`; retail `0x90`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getTickerTypeAttrib) long getTickerTypeAttrib(void *tag, iks *xml, unsigned int *result)
{
    char *value = iks_find_attrib(xml, svoTickerTypeAttribute);
    if (!value) return 0;
    char **entry = svoTickerTypeStrings;
    do {
        if (!strcasecmp(value, *entry)) {
            *result = entry - svoTickerTypeStrings;
            return 1;
        }
    } while (++entry != svoTickerTypeStrings + 2);
    return 0;
}
```

## CHttp::parseHttpStatusLine

Candidate `0xA4`; retail `0xA0`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(parseHttpStatusLine) char *parseHttpStatusLine(HttpState *http, char *cursor)
{
    if (strncmp(cursor, svoHttpVersionPrefix, 7)) return 0;
    cursor += 9;
    if (!svisdigit((signed char)*cursor)) {
        http->m_status = 600;
        return 0;
    }
    http->m_status = atoi(cursor);
    char *newline = strchr(cursor, '\n');
    return newline ? newline + 1 : 0;
}
```

## CDrawContextBase::DrawPopupBackground

Candidate `0x4C`; retail `0x48`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(DrawPopupBackground) void DrawPopupBackground(CDrawContextBase *draw, float x, float y, float width, float height, unsigned int lineColor, unsigned int fillColor, char *tagClass)
{
    draw->vtable->DrawRectangle(draw, 0, x, y, width, height, lineColor, fillColor, 1, 0, 200000.0f, 0, 0);
}
```
