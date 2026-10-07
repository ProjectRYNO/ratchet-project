# SVO3 50% batch: retained slot blockers

These 16 trial bodies are **not integrated or counted as compiled**. Retail Ghidra, split instructions and prototype data informed them, but GCC 3.2.3 with the current object flags exceeds the original slot. Keep INCLUDE_ASM until a fitting implementation is established. No behavior test or matching claim is attached to these candidates.

Names and types are declared in their owning source/header. The candidate sizes below are the last measured probes. Do not widen slots to accommodate them.


## SVFileDownloadQueue::find___dupe2

Candidate `0x80` bytes; retail `0x7C` bytes.

```cpp
SECTION(find___dupe2) char *find___dupe2(FileDownloadQueueState *queue, char *lookup)
{
    if (!lookup) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xAC);
    for (int i = 0; i < 5; ++i)
        if (matchesMyLookup___dupe2(&queue->m_entries[i], lookup))
            return GetValueStr___dupe2(&queue->m_entries[i]);
    return 0;
}
```


## SVFileDownloadQueue::GetNextEntry

Candidate `0x144` bytes; retail `0x134` bytes.

```cpp
SECTION(GetNextEntry) void GetNextEntry(FileDownloadQueueState *queue, char *path, int pathSize, char *id, int idSize)
{
    int index = 0;
    for (int i = 0; i < 5; ++i) {
        if (strlen(GetValueStr___dupe2(&queue->m_entries[i]))) {
            index = i;
            break;
        }
    }
    // With no populated entry, retail still consumes slot zero.
    FileDownloadEntryState *entry = &queue->m_entries[index];
    char *text = GetValueStr___dupe2(entry);
    if ((long)pathSize < (long)strlen(text)) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xD5);
    svstrncpy(path, text, pathSize);
    text = GetNameStr(entry);
    if ((long)idSize < (long)strlen(text)) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xDC);
    svstrncpy(id, text, idSize);
    reset___dupe3(entry);
}
```


## SVFileDownloadQueue::operator.new___dupe14

Candidate `0x40` bytes; retail `0x3C` bytes.

```cpp
SECTION(operator.new___dupe14) void *FileDownloadQueueNew(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x6E, svoFileDownloadQueueSource);
}
```


## SVFileDownloadQueue::setFileDownloadProps

Candidate `0xF4` bytes; retail `0xF0` bytes.

```cpp
SECTION(setFileDownloadProps) void setFileDownloadProps(FileDownloadEntryState *entry, char *lookup, char *value)
{
    if (!entry->m_lookupStr || !entry->m_valueStr) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x3D);
    if (strlen(lookup) > 31 || strlen(value) > 256) {
        SetErrorCode(0x1E);
        __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x44);
    }
    if (!lookup || !value) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0x48);
    svstrncpy(entry->m_lookupStr, lookup, strlen(lookup) + 1);
    svstrncpy(entry->m_valueStr, value, strlen(value) + 1);
}
```


## TagUtils::getChildIksStruct

Candidate `0xB4` bytes; retail `0xB0` bytes.

```cpp
SECTION(getChildIksStruct) iks *getChildIksStruct(iks *xml, char *name)
{
    if (!xml) __SVO_Assert_Handler(svoTagUtilsSource, 0x149);
    iks *child = 0;
    if (iks_has_children(xml)) child = iks_child(xml);
    while (child) {
        if (iks_name(child) && !strcmp(name, iks_name(child))) return child;
        child = iks_next(child);
    }
    return 0;
}
```


## TagUtils::getLinkOptionAttrib

Candidate `0x88` bytes; retail `0x84` bytes.

```cpp
SECTION(getLinkOptionAttrib) long getLinkOptionAttrib(iks *xml, char *name, unsigned int *option)
{
    char *text = iks_find_attrib(xml, name);
    if (!text) return 0;
    for (int i = 0; i < 9; ++i) {
        if (!strcmp(text, svoTagLinkOptions[i])) {
            *option = i;
            return 1;
        }
    }
    return 0;
}
```


## SVBrowser::BrowserIsIdle

Candidate `0x2C` bytes; retail `0x24` bytes.

```cpp
SECTION(BrowserIsIdle) long BrowserIsIdle(SVBrowserPrefix *browser)
{
    if (browser->m_pMainPage->m_state) return 0;
    return browser->m_pPopupPage->m_state == 0;
}
```


## SVBrowser::InitalizePluginManagerAndPlugins

Candidate `0x6C` bytes; retail `0x68` bytes.

```cpp
SECTION(InitalizePluginManagerAndPlugins) void InitalizePluginManagerAndPlugins(SVBrowserPrefix *browser)
{
    SVBrowserPrefix *instance = svoBrowserInstance;
    CPluginManagerState *manager = (CPluginManagerState *)PluginManagerNew(0x58);
    CPluginManager(manager);
    instance->m_pPluginManager = manager;
    if (!svoBrowserInstance->m_pPluginManager) __SVO_Assert_Handler(svoBrowserSource, 0x5DE);
}
```


## SVBrowser::InitServerInfo

Candidate `0x48` bytes; retail `0x44` bytes.

```cpp
SECTION(InitServerInfo) void InitServerInfo(SVServerInfo *info)
{
    info->port = -1;
    memset(info->serverName, 0, 257);
    memset(info->firstPage, 0, 257);
}
```


## SVBrowser::reset

Candidate `0x48` bytes; retail `0x44` bytes.

```cpp
SECTION(reset) void reset(DownloadThrobberInfo *info)
{
    info->tagClass = gTagNotSetStr;
    info->width = 150.0f;
    info->x = 245.0f;
    info->y = 20.0f;
    info->height = 25.0f;
    info->tagid = 0;
}
```


## SVBrowser::SV_IKS_Malloc

Candidate `0x40` bytes; retail `0x3C` bytes.

```cpp
SECTION(SV_IKS_Malloc) void *SV_IKS_Malloc(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 4, 0xC0, svoBrowserSource);
}
```


## SVBrowser::URIStoreFind

Candidate `0x74` bytes; retail `0x70` bytes.

```cpp
SECTION(URIStoreFind) char *URIStoreFind(char *lookup)
{
    if (!svoBrowserInstance) __SVO_Assert_Handler(svoBrowserSource, 0x6B4);
    if (!svoBrowserInstance->m_pURIStore) __SVO_Assert_Handler(svoBrowserSource, 0x6B5);
    return find(svoBrowserInstance->m_pURIStore, lookup);
}
```


## TextTag::IsSelectable___dupe6

Candidate `0x24` bytes; retail `0x1C` bytes.

```cpp
SECTION(IsSelectable___dupe6) long IsSelectable___dupe6(TextTagState *tag)
{
    if (!tag->base.m_bSelectable) return 0;
    return tag->m_link != 0;
}
```


## ImageTag::IsSelectable___dupe11

Candidate `0x28` bytes; retail `0x20` bytes.

```cpp
SECTION(IsSelectable___dupe11) long IsSelectable___dupe11(SVTag *tag)
{
    // Retail compares the address of an embedded field against null.
    if (!tag->m_bSelectable) return 0;
    return (unsigned int)tag != (unsigned int)-0xBC;
}
```


## SelectTag::IsSelectable___dupe10

Candidate `0x24` bytes; retail `0x1C` bytes.

```cpp
SECTION(IsSelectable___dupe10) long IsSelectable___dupe10(SelectTagState *tag)
{
    if (!tag->base.m_bSelectable) return 0;
    return tag->m_numOptions > 0;
}
```


## StaticImageTag::IsSelectable___dupe12

Candidate `0x28` bytes; retail `0x20` bytes.

```cpp
SECTION(IsSelectable___dupe12) long IsSelectable___dupe12(SVTag *tag)
{
    // Retail compares the address of an embedded field against null.
    if (!tag->m_bSelectable) return 0;
    return (unsigned int)tag != (unsigned int)-0xB4;
}
```
