# SVO3 next-batch slot blockers

Retail/Ghidra/prototype-derived candidates. Behavior tests deferred. Do not widen slots.

## TextInputTag::GetEditPosition___dupe2

Candidate `0x1C`; retail `0x18`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(GetEditPosition___dupe2) unsigned int GetEditPosition___dupe2(TextInputTagState *tag)
{
    return strlen(tag->m_text);
}
```

## TextInputTag::getSubstringPixelWidth

Candidate `0x2C`; retail `0x24`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getSubstringPixelWidth) float getSubstringPixelWidth(TextInputTagState *tag, int left, int right)
{
    return getSubstringPixelWidthImpl(tag, tag->m_text, left, right);
}
```

## TextAreaTag::changeColorForAllLines

Candidate `0x44`; retail `0x40`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(changeColorForAllLines) void changeColorForAllLines(TextAreaTagState *tag, unsigned int color)
{
    LineInfo *lines = tag->m_textLines;
    for (int i = 0; i < tag->m_maxTextLines + 1; ++i) lines[i].color = color;
}
```

## PasswordInputTag::defaultInit___dupe2

Candidate `0x3C`; retail `0x38`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(defaultInit___dupe2) char *defaultInit___dupe2(TextInputTagState *tag)
{
    defaultInit(tag);
    return svstrncpy(tag->base.m_tagTypeName, svoPasswordInputTagName, 64);
}
```

## PasswordInputTag::PasswordInputTag

Candidate `0x78`; retail `0x74`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(PasswordInputTag) long PasswordInputTag(TextInputTagState *tag, iks *xml, SVTag **tagList, CAllContextData *contexts)
{
    TextInputTag(tag, xml, tagList, contexts, 1);
    tag->base.vtable = &svoPasswordInputTagVtable;
    InitialiseFromXml(tag, xml, tagList, contexts);
    tag->m_bEditable = 1;
    return 1;
}
```

## GenericListBoxTag::getIndexOfHandle

Candidate `0xAC`; retail `0xA8`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getIndexOfHandle) long getIndexOfHandle(GenericListBoxTagState *tag, svo_listbox_handle handle)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x180);
    if (tag->m_maxVisibleItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x181);
    int count = tag->m_maxNumItems;
    for (int i = 0; i < count; ++i) {
        if (tag->m_handles[i] == handle) return i;
    }
    return -1;
}
```

## ListBoxTag::getSelectedItem

Candidate `0xD4`; retail `0xD0`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getSelectedItem) ListBoxItem * getSelectedItem(ListBoxTagState *tag)
{
    if (!tag->m_numItems) return 0;
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x190);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x191);
    if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoListBoxTagSource, 0x192);
    if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x193);
    return tag->m_items[tag->m_selectedIndex];
}
```

## ListBoxTag::isIndexSelected

Candidate `0xC4`; retail `0xC0`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(isIndexSelected) long isIndexSelected(ListBoxTagState *tag, int index)
{
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x290);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x291);
    if (index >= tag->m_numItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x292);
    if (!tag->m_items[index]) __SVO_Assert_Handler(svoListBoxTagSource, 0x293);
    return index == tag->m_selectedIndex;
}
```

## ListBoxTag::calculateScrollBarPercentage

Candidate `0x80`; retail `0x78`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(calculateScrollBarPercentage) float calculateScrollBarPercentage(ListBoxTagState *tag)
{
    int visible = tag->m_numItems;
    if (tag->m_maxVisibleItems < visible) visible = tag->m_maxVisibleItems;
    if (tag->m_topVisibleIndex < 0) __SVO_Assert_Handler(svoListBoxTagSource, 0x2c5);
    if (tag->m_topVisibleIndex > 0) return (float)tag->m_topVisibleIndex / (float)visible;
    return 0.0f;
}
```

## CPage::getTopOfHistory

Candidate `0x1C`; retail `0x18`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getTopOfHistory) char *getTopOfHistory(CPage *page)
{
    return top(&page->m_history);
}
```
