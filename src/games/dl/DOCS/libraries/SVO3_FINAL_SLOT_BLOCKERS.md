# SVO3 continuation slot blockers (2026-10-08)

Recovered from retail Ghidra, split instructions and prototype. These candidates
remain explicit assembly and are not counted as compiled. Do not widen slots.

## CPage::getTopOfHistory

Candidate `0x1C`; original slot `0x18`. Assembly retained.

```cpp
extern "C" SECTION(getTopOfHistory) char *getTopOfHistory(CPage *page) { return top(&page->m_history); }
```

## TagUtils::getLinkOptionAttrib

Candidate `0x88`; original slot `0x84`. Assembly retained.

```cpp
extern "C" SECTION(getLinkOptionAttrib) int getLinkOptionAttrib(iks *xml, char *name, unsigned int *option)
{
    char *value = iks_find_attrib(xml, name);
    if (!value) return 0;
    char **entry = svoTagLinkOptions;
    for (int i = 0; i < 9; ++i, ++entry) {
        if (!strcmp(value, *entry)) { *option = i; return 1; }
    }
    return 0;
}
```

## SVFileDownloadQueue::setFileDownloadProps

Candidate `0xF4`; original slot `0xF0`. Assembly retained.

```cpp
extern "C" SECTION(setFileDownloadProps) void setFileDownloadProps(FileDownloadEntryState *entry, char *lookup, char *value)
{
    if (!entry->m_lookupStr || !entry->m_valueStr) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x3D);
    if (strlen(lookup) > 31 || strlen(value) > 256) {
        SetErrorCode(30);
        __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x44);
    }
    if (!lookup || !value) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x48);
    svstrncpy(entry->m_lookupStr, lookup, strlen(lookup) + 1);
    svstrncpy(entry->m_valueStr, value, strlen(value) + 1);
}
```

## SVFileDownloadQueue::find___dupe2

Candidate `0x84`; original slot `0x7C`. Assembly retained.

```cpp
extern "C" SECTION(find___dupe2) char *find___dupe2(FileDownloadQueueState *queue, char *lookup)
{
    if (!lookup) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xAC);
    FileDownloadEntryState *entry = queue->m_entries;
    FileDownloadEntryState *end = entry + 5;
    while (entry != end) {
        if (matchesMyLookup___dupe2(entry, lookup)) return GetValueStr___dupe2(entry);
        ++entry;
    }
    return 0;
}
```

## SubmitInputTag::SubmitInputTag

Candidate `0x188`; original slot `0x184`. Assembly retained.

```cpp
extern "C" SECTION(SubmitInputTag) void SubmitInputTag(SubmitInputTagState *self, iks *xml, SVTag **tagList, CAllContextData *contexts)
{
    SVTag *tag = &self->base;
    SVTagConstruct(tag, xml, contexts);
    tag->vtable = &svoSubmitInputTagVtable;
    DefaultInit___dupe16(self);
    // SVTagConstruct stores xml unchanged; DefaultInit does not modify it.
    if (!tagList || !tag->m_xml) __SVO_Assert_Handler(svoSubmitInputTagSource, 0x35);
    getIntAttrib(tag->m_xml, svoSubmitInputTagAttrFontSize, &self->m_fontSize);
    getFloatAttrib(tag->m_xml, svoSubmitInputTagAttrDisplayLength, &self->m_displayLength);
    getAlignAttrib(tag->m_xml, svoSubmitInputTagAttrAlign, &self->m_align);
    getColorAttrib(tag->m_xml, svoSubmitInputTagAttrFillColor, &tag->m_fillColor);
    getColorAttrib(tag->m_xml, svoSubmitInputTagAttrLineColor, &tag->m_lineColor);
    getColorAttrib(tag->m_xml, svoSubmitInputTagAttrTextColor, &self->m_textColor);
    getColorAttrib(tag->m_xml, svoSubmitInputTagAttrHighlightFillColor, &self->m_highlightFillColor);
    getColorAttrib(tag->m_xml, svoSubmitInputTagAttrHighlightLineColor, &self->m_highlightLineColor);
    getColorAttrib(tag->m_xml, svoSubmitInputTagAttrHighlightTextColor, &self->m_highlightTextColor);
    getStringAttrib(tag->m_xml, svoSubmitInputTagAttrClass, &tag->m_tagClass);
    char *value = iks_find_attrib(tag->m_xml, svoSubmitInputTagAttrValue);
    if (value) svstrncpy(self->m_value, value, strlen(value) + 1);
    RegisterWithForm___dupe5(self, iks_parent(tag->m_xml), tagList);
}
```
