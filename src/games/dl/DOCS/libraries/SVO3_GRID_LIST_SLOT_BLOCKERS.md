# Grid/list/login slot blockers (2026-10-09)

Retail Ghidra and split evidence; original slots retained. No matching or gameplay claim.

## LoginTagModule::ScanTags___dupe6

Candidate `0x88`; retail `0x84`. Retained assembly.

```cpp
extern "C" SECTION(ScanTags___dupe6) void ScanTags___dupe6(LoginTagModuleState *module, iks *xml, SVTag **tags, CAllContextData *contexts, CTagModuleActions *actions)
{
    char *action = iks_find_attrib(xml, svoLoginDTDAttribute);
    if (action) ScanTagsHandleLoginDTD(module, xml, contexts, action, actions);
    else ScanTagsHandleLoginSubmitResponse(module, xml, contexts, actions);
}
```

## ListBoxTag::getSelectedItem

Candidate `0xD4`; retail `0xD0`. Retained assembly.

```cpp
extern "C" SECTION(getSelectedItem) ListBoxItem *getSelectedItem(ListBoxTagState *tag)
{
    ListBoxItem *selected = 0;
    if (tag->m_numItems) {
        if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x190);
        if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x191);
        if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoListBoxTagSource, 0x192);
        if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x193);
        selected = tag->m_items[tag->m_selectedIndex];
    }
    return selected;
}
```

## ListBoxTag::populateListboxItems

Candidate `0x1CC`; retail `0x1C4`. Retained assembly.

```cpp
extern "C" SECTION(populateListboxItems) void populateListboxItems(ListBoxTagState *tag)
{
    iks *nodes[100];
    if (!iks_has_children(tag->base.m_xml)) __SVO_Assert_Handler(svoListBoxTagSource, 0x208);
    iks_child(tag->base.m_xml);
    int count = getChildIksStructList(tag->base.m_xml, svoListBoxItemName, nodes, 100);
    for (int i = 0; i < count; ++i) {
        iks *xml = nodes[i];
        tag->m_items[i] = (ListBoxItem *)svAllocSafe(tag->base.m_contexts->memoryContext, sizeof(ListBoxItem), 0, 0x214, svoListBoxTagSource);
        initListboxItem(tag, tag->m_items[i]);
        tag->m_items[i]->displayStr = iks_cdata(iks_child(xml));
        tag->m_items[i]->h_ref = iks_find_attrib(xml, svoListBoxHrefAttribute);
        tag->m_items[i]->tagClass = iks_find_attrib(xml, svoListBoxClassAttribute);
        if (!tag->m_items[i]->tagClass) tag->m_items[i]->tagClass = svoListBoxDefaultItemClass;
        tag->m_items[i]->name = iks_find_attrib(xml, svoListBoxNameAttribute);
        if (!tag->m_items[i]->name) __SVO_Assert_Handler(svoListBoxTagSource, 0x227);
        tag->m_items[i]->tagid = svoNextTagId++;
        if (tag->m_items[i]->h_ref) {
            decodeEntityText(tag->m_items[i]->h_ref);
            getLinkOptionAttrib(xml, svoListBoxLinkOptionAttribute, &tag->m_items[i]->linkOption);
        }
    }
    tag->m_numItems = count;
}
```

## GridTag::CalculateGridHeight

Candidate `0xB0`; retail `0xA8`. Retained assembly.

```cpp
extern "C" SECTION(CalculateGridHeight) void CalculateGridHeight(GridTagState *tag)
{
    float y = tag->base.m_y + tag->m_headerHeight;
    tag->base.m_height = tag->m_headerHeight;
    int i = 0;
    if (tag->m_origNumVisRows > 0) do {
        SVGridRow *row = &tag->m_rows[i];
        row->row_y = y;
        tag->base.m_height += row->height;
        y += row->height;
        if (y != tag->base.m_height + tag->base.m_y) __SVO_Assert_Handler(svoGridTagSource, 0x423);
    } while (++i < tag->m_origNumVisRows);
}
```

## GridTag::HandleColumnShuffling

Candidate `0x130`; retail `0x12C`. Retained assembly.

```cpp
extern "C" SECTION(HandleColumnShuffling) void HandleColumnShuffling(GridTagState *tag, int leftmostCol)
{
    if (leftmostCol < 0) __SVO_Assert_Handler(svoGridTagSource, 0x6CB);
    if (leftmostCol > tag->m_numTotalColumns - tag->m_numVisColumns + tag->m_numLockedColumns)
        __SVO_Assert_Handler(svoGridTagSource, 0x6CC);
    for (int i = 0; i < tag->m_numLockedColumns; ++i) {
        if (tag->m_columnIndexes[i] != i) __SVO_Assert_Handler(svoGridTagSource, 0x6D2);
    }
    for (int i = tag->m_numLockedColumns; i < tag->m_numVisColumns; ++i) {
        if (i + leftmostCol - tag->m_numLockedColumns >= tag->m_numTotalColumns)
            __SVO_Assert_Handler(svoGridTagSource, 0x6D8);
        tag->m_columnIndexes[i] = i + leftmostCol - tag->m_numLockedColumns;
    }
}
```
