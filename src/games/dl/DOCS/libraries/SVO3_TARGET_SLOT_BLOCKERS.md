# SVO3 next-batch slot blockers

Retail/Ghidra/prototype-derived candidates. Behavior tests deferred. Do not widen slots.

## HttpSecure::HTTPS_Malloc

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(HTTPS_Malloc) void * HTTPS_Malloc(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0x8, 0x4F, svoHttpSecureSource);
}
```

## HttpSecure::HttpsDownloadHello

Candidate `0xB0`; retail `0xA8`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(HttpsDownloadHello) long HttpsDownloadHello(HttpSecureState *http, char *data, int length, char **output, int *outputLength, int *state)
{
    SSLCallbackParams params;
    memset(&params, 0, sizeof(params));
    params.received = data;
    params.receivedLength = length;
    ((const HttpSecureVtablePrefix *)http->base.vtable)->HttpsCallEngine(http, &params);
    *outputLength = params.sendBackLength;
    *output = params.sendBack;
    *state = params.state;
    return params.state == 10;
}
```

## CPage::operator.new___dupe3

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe3) void * CPageoperator_new___dupe3(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x8E, svoPageSource);
}
```

## CPage::ReAllocBackDisplayBufferParser

Candidate `0x80`; retail `0x74`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(ReAllocBackDisplayBufferParser) void ReAllocBackDisplayBufferParser(CPage *page)
{
    if (page->m_pBackDisplayBuffer->parser) __SVO_Assert_Handler(svoPageSource, 0xA4E);
    page->m_pBackDisplayBuffer->parser = iks_dom_new(&page->m_pBackDisplayBuffer->xml);
    if (!page->m_pBackDisplayBuffer->parser) __SVO_Assert_Handler(svoPageSource, 0xA52);
    iks_parser_reset(page->m_pBackDisplayBuffer->parser);
}
```

## CPage::setPageContextData

Candidate `0x90`; retail `0x8C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(setPageContextData) void setPageContextData(CPage *page)
{
    if (page->m_bIsPopup) {
        svoPageContextData.audioContext = GetAudioContext();
        svoPageContextData.drawContext = GetDrawContext();
        svoPageContextData.memoryContext = GetMemoryContext();
        svoPageContextData.systemContext = GetSystemContext();
        svoPageContextData.inputContext = GetInputContext();
    } else {
        svoPageContextData.audioContext = GetAltAudioContext();
        svoPageContextData.drawContext = GetAltDrawContext();
        svoPageContextData.memoryContext = GetAltMemoryContext();
        svoPageContextData.systemContext = GetAltSystemContext();
        svoPageContextData.inputContext = GetAltInputContext();
    }
}
```

## CHttp::operator.new___dupe4

Candidate `0x34`; retail `0x30`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe4) void * CHttpoperator_new___dupe4(unsigned int size, CMemoryContextBaseState *memory)
{
    return svAllocSafe(memory, size, 0x4, 0x32, svoHttpSource);
}
```

## CHttp::downloadHeaders

Candidate `0x1CC`; retail `0x1C0`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(downloadHeaders) long downloadHeaders(HttpState *http)
{
    if (!http->m_sock) __SVO_Assert_Handler(svoHttpSource, 0x26B);
    int received = 0;
    int finished = 0;
    SVSockState *socket = http->m_sock;
    if (!((const SVSockVtablePrefix *)socket->vtable)->Recv(socket, http->m_headerBuf + http->m_headerBytesReceived, 0x8000 - http->m_headerBytesReceived, &received, &finished)) {
        SetErrorCode(0x15);
        return 0;
    }
    if (http->m_headerBytesReceived > 0x8000) __SVO_Assert_Handler(svoHttpSource, 0x27C);
    char *response = 0;
    char *sendBack = 0;
    int responseLength = 0;
    int sendLength = 0;
    if (http->vtable->IsSecure(http) && finished &&
        http->vtable->HttpsDownload(http, http->m_headerBuf, http->m_headerBytesReceived, &response, &responseLength, &sendBack, &sendLength) && sendLength > 0) {
        unsigned long sent = 0;
        socket = http->m_sock;
        ((const SVSockVtablePrefix *)socket->vtable)->Send(socket, sendBack, sendLength, &sent);
        if ((int)sent < sendLength) __SVO_Assert_Handler(svoHttpSource, 0x28C);
        memcpy(http->m_headerBuf, response, responseLength);
        http->m_headerBytesReceived = 0;
        received = responseLength;
    }
    if (received) {
        http->m_timeoutFrameCounter = 0;
        http->m_headerBytesReceived += received;
        if (strstr(http->m_headerBuf, svoHttpHeaderEnd)) OnHeaderParsed(http, parseHeaderBuf(http));
    }
    return finished;
}
```

## CHttp::parseHttpStatusLine

Candidate `0xA4`; retail `0xA0`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(parseHttpStatusLine) char *parseHttpStatusLine(HttpState *http, char *cursor)
{
    if (strncmp(cursor, svoHttpVersionPrefix, 7)) return 0;
    cursor += 9;
    if (!svisdigit((signed char)*cursor)) { http->m_status = 600; return 0; }
    http->m_status = atoi(cursor);
    char *end = strchr(cursor, 10);
    return end ? end + 1 : 0;
}
```

## CHttp::md5request

Candidate `0x108`; retail `0xFC`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(md5request) char *md5request(HttpState *http, char *path, char *cookies, char *post, char *output)
{
    md5_context context;
    unsigned char digest[16];
    md5_starts(&context);
    md5_update(&context, (unsigned char *)path, (unsigned int)strlen(path));
    if (*cookies) md5_update(&context, (unsigned char *)cookies + 8, (unsigned int)(strlen(cookies + 8) - 2));
    if (post) md5_update(&context, (unsigned char *)post, (unsigned int)strlen(post));
    md5_update(&context, (unsigned char *)svoHttpMD5Suffix, (unsigned int)strlen(svoHttpMD5Suffix));
    md5_finish(&context, digest);
    return md5_hex(digest, output);
}
```

## CHttp::md5requestLogin

Candidate `0x188`; retail `0x174`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(md5requestLogin) char *md5requestLogin(HttpState *http, char *username, char *password, char *ip, char *output)
{
    md5_context context;
    unsigned char digest[16];
    char user[257];
    char pass[257];
    md5_starts(&context);
    char initial = svoHttpEmptyString[0];
    user[0] = initial;
    memset(user + 1, 0, 256);
    pass[0] = initial;
    memset(pass + 1, 0, 256);
    if (strlen(username) > 256) __SVO_Assert_Handler(svoHttpSource, 0x1D6);
    strcat(user, username);
    if (strlen(password) > 256) __SVO_Assert_Handler(svoHttpSource, 0x1D8);
    strcat(pass, password);
    char *lowerUser = strlwr(user);
    char *lowerPass = strlwr(pass);
    md5_update(&context, (unsigned char *)lowerUser, (unsigned int)strlen(lowerUser));
    md5_update(&context, (unsigned char *)lowerPass, (unsigned int)strlen(lowerPass));
    md5_update(&context, (unsigned char *)ip, (unsigned int)strlen(ip));
    md5_finish(&context, digest);
    return md5_hex(digest, output);
}
```

## SVBrowser::SV_IKS_Malloc

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(SV_IKS_Malloc) void * SV_IKS_Malloc(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0x4, 0xC0, svoBrowserSource);
}
```

## SVBrowser::UpdateDownloadManager

Candidate `0xCC`; retail `0xC8`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(UpdateDownloadManager) long UpdateDownloadManager(SVBrowserPrefix *browser)
{
    if (!browser->m_bUseDownloadManger) {
        SetErrorCode(31);
        if (!browser->m_bUseDownloadManger) __SVO_Assert_Handler(svoBrowserSource, 0x753);
        return 0;
    }
    if (browser->m_pDownloadManager) {
        download___dupe3(browser->m_pDownloadManager);
        if (((SVDownloadManagerState *)browser->m_pDownloadManager)->m_state) return 1;
        if (HasEntries(browser->m_pFileDownloadQueue)) {
            char lookup[257];
            char value[257];
            GetNextEntry(browser->m_pFileDownloadQueue, lookup, 257, value, 257);
            DownloadFile(browser, lookup, value);
        }
    }
    return 1;
}
```

## SVChronograph::operator.new___dupe5

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe5) void * SVChronographoperator_new___dupe5(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x5D, svoChronographSource);
}
```

## SVTagModuleList::operator.new___dupe6

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe6) void * SVTagModuleListoperator_new___dupe6(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x51, svoTagModuleListSource);
}
```

## SVTagModule::operator.new___dupe7

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe7) void * SVTagModuleoperator_new___dupe7(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0xC, svoSVTagModuleSource);
}
```

## SVTag::operator.new___dupe8

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe8) void * SVTagoperator_new___dupe8(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x1E, svoTagSource);
}
```

## SVSock::operator.new___dupe9

Candidate `0x34`; retail `0x30`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe9) void * SVSockoperator_new___dupe9(unsigned int size, CMemoryContextBaseState *memory)
{
    return svAllocSafe(memory, size, 0, 0x18, svoSockSource);
}
```

## SVURIStore::operator.new___dupe10

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe10) void * SVURIStoreoperator_new___dupe10(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x4A, svoURIStoreSource);
}
```

## CPluginManager::operator.new___dupe11

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe11) void * CPluginManageroperator_new___dupe11(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0xDD, svoPluginManagerSource);
}
```

## SVDownloadManager::operator.new___dupe13

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe13) void * SVDownloadManageroperator_new___dupe13(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x31, svoSVDownloadManagerSource);
}
```

## SVFileDownloadQueue::operator.new___dupe14

Candidate `0x40`; retail `0x3C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(operator.new___dupe14) void * SVFileDownloadQueueoperator_new___dupe14(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x6E, svoFileDownloadQueueSource);
}
```

## SVFileDownloadQueue::find___dupe2

Candidate `0x80`; retail `0x7C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(find___dupe2) char *find___dupe2(FileDownloadQueueState *queue, char *lookup)
{
    if (!lookup) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xAC);
    for (int i = 0; i < 5; ++i) {
        if (matchesMyLookup___dupe2(&queue->m_entries[i], lookup)) return GetValueStr___dupe2(&queue->m_entries[i]);
    }
    return 0;
}
```

## SVFileDownloadQueue::setFileDownloadProps

Candidate `0xF4`; retail `0xF0`. Retained assembly; not counted as compiled.

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

## SVFileDownloadQueue::GetNextEntry

Candidate `0x144`; retail `0x134`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(GetNextEntry) void GetNextEntry(FileDownloadQueueState *queue, char *path, int pathSize, char *id, int idSize)
{
    int selected = 0;
    for (int i = 0; i < 5; ++i) {
        if (strlen(GetValueStr___dupe2(&queue->m_entries[i]))) { selected = i; break; }
    }
    FileDownloadEntryState *entry = &queue->m_entries[selected];
    char *value = GetValueStr___dupe2(entry);
    if ((long)pathSize < (long)strlen(value)) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xD5);
    svstrncpy(path, value, pathSize);
    char *name = GetNameStr(entry);
    if ((long)idSize < (long)strlen(name)) __SVO_Assert_Handler(svoFileDownloadQueueSource, 0xDC);
    svstrncpy(id, name, idSize);
    reset___dupe3(entry);
}
```

## RTCommSock::sDNSLookupCB

Candidate `0xD4`; retail `0xCC`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(sDNSLookupCB) void sDNSLookupCB(const void *response)
{
    memcpy(m_DNSLookupResponse, response, 136);
    svoDNSLookupFinished = 1;
}
```

## RTCommSock::dnsLookupNonBlockingQuery

Candidate `0xA8`; retail `0x98`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(dnsLookupNonBlockingQuery) long dnsLookupNonBlockingQuery(RTCommSockState *socket, SVAddr **output)
{
    SVAddr *address = *output;
    if (rt_comm_update() != 0) return 0;
    if (svoDNSLookupFinished != 1) return 0;
    if (svoDNSLookupResult) { SetErrorCode(36); return 0; }
    void *ip = (char *)address + 8;
    memcpy(ip, m_DNSLookupResponse, 8);
    CacheStore2(Get___dupe2(), socket->m_szHostnameBeingLookedUp, ip);
    return 1;
}
```

## GridTag::CalculateGridHeight

Candidate `0xB0`; retail `0xA8`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(CalculateGridHeight) void CalculateGridHeight(GridTagState *tag)
{
    float y = tag->base.m_y + tag->m_headerHeight;
    tag->base.m_height = tag->m_headerHeight;
    for (int i = 0; i < tag->m_origNumVisRows; ++i) {
        SVGridRow *row = &tag->m_rows[i];
        row->row_y = y;
        tag->base.m_height += row->height;
        y += row->height;
        if (y != tag->base.m_height + tag->base.m_y)
            __SVO_Assert_Handler(svoGridTagSource, 0x423);
    }
}
```

## GridTag::HandleColumnShuffling

Candidate `0x130`; retail `0x12C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(HandleColumnShuffling) void HandleColumnShuffling(GridTagState *tag, int leftmost)
{
    if (leftmost < 0) __SVO_Assert_Handler(svoGridTagSource, 0x6CB);
    if (leftmost > tag->m_numTotalColumns - tag->m_numVisColumns + tag->m_numLockedColumns)
        __SVO_Assert_Handler(svoGridTagSource, 0x6CC);
    for (int i = 0; i < tag->m_numLockedColumns; ++i)
        if (tag->m_columnIndexes[i] != i) __SVO_Assert_Handler(svoGridTagSource, 0x6D2);
    for (int i = tag->m_numLockedColumns; i < tag->m_numVisColumns; ++i) {
        if (i + leftmost - tag->m_numLockedColumns >= tag->m_numTotalColumns)
            __SVO_Assert_Handler(svoGridTagSource, 0x6D8);
        tag->m_columnIndexes[i] = i + leftmost - tag->m_numLockedColumns;
    }
}
```

## GridTag::ParseSingleCell

Candidate `0x138`; retail `0x134`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(ParseSingleCell) long ParseSingleCell(GridTagState *tag, iks *xml, SVGridCell *cell)
{
    if (!xml || !cell) { __SVO_Assert_Handler(svoGridTagSource, 0x549); return 0; }
    unsigned int id = svoNextTagId;
    svoNextTagId = id + 1;
    cell->cell_tagID = id;
    cell->cellClass = iks_find_attrib(xml, svoGridClassAttribute);
    if (!iks_has_children(xml)) return 1;
    cell->cell_text = iks_has_children(xml) ? iks_cdata(iks_child(xml)) : 0;
    cell->cell_link = iks_find_attrib(xml, svoGridLinkAttribute);
    if (tag->base.m_toolTipTagName) cell->cell_tooltip = iks_find_attrib(xml, svoGridTooltipAttribute);
    if (cell->cell_link) decodeEntityText(cell->cell_link);
    cell->cellClass = iks_find_attrib(xml, svoGridClassAttribute);
    cell->linkOption = 0;
    getLinkOptionAttrib(xml, svoGridLinkOptionAttribute, (unsigned int *)&cell->linkOption);
    return 1;
}
```

## ImageTag::getImageTypeAttrib

Candidate `0x94`; retail `0x8C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getImageTypeAttrib) long getImageTypeAttrib(void *tag, iks *xml, char *name, unsigned int *value)
{
    char *text = iks_find_attrib(xml, name);
    if (!text) return 0;
    char **entry = svoImageTypeStrings;
    for (int i = 0; i < 4; ++i) {
        if (strcmp(text, *entry++) == 0) {
            *value = i;
            return 1;
        }
    }
    return 0;
}
```

## StaticImageTag::DefaultInit___dupe11

Candidate `0x78`; retail `0x74`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(DefaultInit___dupe11) char * DefaultInit___dupe11(StaticImageTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoStaticImageTagName, 64);
    memset(tag->m_link, 0, 128);
    tag->m_index = -1;
    tag->base.m_fillColor = 0xFFFFFFFF;
    tag->base.m_lineColor = 0xFF000000;
    tag->m_imageWidth = 0;
    tag->m_imageHeight = 0;
    return svstrncpy(tag->m_imageName, svoStaticImageUnsetName, 32);
}
```

## LineTag::LineTag

Candidate `0x9C`; retail `0x98`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(LineTag) void LineTag(LineTagState *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoLineTagVtable;
    DefaultInit___dupe7(tag);
    getFloatAttrib(tag->base.m_xml, svoLineEndXAttribute, &tag->m_endX);
    getFloatAttrib(tag->base.m_xml, svoLineEndYAttribute, &tag->m_endY);
    getFloatAttrib(tag->base.m_xml, svoLineThicknessAttribute, &tag->m_thickness);
    getColorAttrib(tag->base.m_xml, svoLineColorAttribute, &tag->base.m_lineColor);
    getStringAttrib(tag->base.m_xml, svoLineClassAttribute, &tag->base.m_tagClass);
}
```

## SetVariableTag::handleDownloadThrobber

Candidate `0x104`; retail `0xFC`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(handleDownloadThrobber) void handleDownloadThrobber(SetVariableTagState *tag)
{
    SVBrowserPrefix *browser = GetInstance();
    if (!browser) __SVO_Assert_Handler(svoSetVariableSource, 0x82);
    float x = 0;
    if (getFloatAttrib(tag->base.m_xml, svoThrobberXAttribute, &x)) browser->m_downloadThrobberInfo.x = x;
    float y = 0;
    if (getFloatAttrib(tag->base.m_xml, svoThrobberYAttribute, &y)) browser->m_downloadThrobberInfo.y = y;
    float width = 0;
    if (getFloatAttrib(tag->base.m_xml, svoThrobberWAttribute, &width)) browser->m_downloadThrobberInfo.width = width;
    float height = 0;
    if (getFloatAttrib(tag->base.m_xml, svoThrobberHAttribute, &height)) browser->m_downloadThrobberInfo.height = height;
    char *name = 0;
    if (getStringAttrib(tag->base.m_xml, svoThrobberClassAttribute, &name)) browser->m_downloadThrobberInfo.tagClass = name;
}
```

## md5::md5_update

Candidate `0x128`; retail `0x124`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(md5_update) void md5_update(md5_context *ctx, unsigned char *input, unsigned long length)
{
    if (!length) return;
    unsigned long left = (ctx->total[0] >> 3) & 63;
    unsigned long low = (ctx->total[0] + (length << 3)) & 0xFFFFFFFFUL;
    ctx->total[1] += (length >> 29) + (low < (length << 3));
    ctx->total[0] = low;
    unsigned long fill = 64 - left;
    if (left && length >= fill) {
        memcpy(ctx->buffer + (int)left, input, (int)fill);
        length -= fill;
        md5_process(ctx, ctx->buffer);
        input += (int)fill;
        left = 0;
    }
    while (length >= 64) {
        md5_process(ctx, input);
        input += 64;
        length -= 64;
    }
    if (length) memcpy(ctx->buffer + (int)left, input, (int)length);
}
```

## TextAreaTag::UpdateCursorPosition

Candidate `0xDC`; retail `0xD4`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(UpdateCursorPosition) void UpdateCursorPosition(TextAreaTagState *tag, CDrawContextBase *draw)
{
    tag->m_cursorY = tag->base.m_y + (float)(tag->m_curLine - tag->m_minDisplayLine) * tag->m_lineSpacing - 2.0f;
    if (tag->m_curEditOffset > tag->m_maxTextSize) {
        if (tag->m_curLine < 0) tag->m_curLine = 0;
        tag->m_curEditOffset = tag->m_textLines[tag->m_curLine].lineEndIndex;
    }
    float width = GetSubstringPixelWidth(tag, draw, tag->m_text, tag->m_textLines[tag->m_curLine].lineStartIndex, tag->m_curEditOffset);
    tag->m_cursorX = tag->base.m_x + width + 7.0f;
    SetArrowOffsets(tag);
}
```

## TextAreaTag::DrawCursor

Candidate `0x74`; retail `0x6C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(DrawCursor) void DrawCursor(TextAreaTagState *tag, CDrawContextBase *draw, int visible)
{
    if (visible) {
        unsigned int color = tag->base.m_bSelected ? tag->m_highlightTextColor : tag->m_textColor;
        float y = tag->m_cursorY + tag->m_yAxisPadValue;
        draw->vtable->DrawLine(draw, tag->base.m_tagid, tag->m_cursorX, y, tag->m_cursorX, y + tag->m_lineSpacing, tag->base.m_x, 2.0f, color, 0);
    }
}
```

## TickerTag::getTickerTypeAttrib

Candidate `0x98`; retail `0x90`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getTickerTypeAttrib) long getTickerTypeAttrib(TickerTagState *tag, iks *xml, unsigned int *value)
{
    char *text = iks_find_attrib(xml, svoTickerTypeAttribute);
    if (!text) return 0;
    char **entry = svoTickerTypeStrings;
    for (int i = 0; i < 2; ++i) {
        if (strcasecmp(text, *entry++) == 0) {
            *value = i;
            return 1;
        }
    }
    return 0;
}
```

## DataTag::getDataTypeAttrib

Candidate `0x94`; retail `0x8C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getDataTypeAttrib) long getDataTypeAttrib(void *tag, iks *xml, char *name, unsigned int *value)
{
    char *text = iks_find_attrib(xml, name);
    if (!text) return 0;
    char **entry = _data_type_strings;
    for (int i = 0; i < 3; ++i) {
        if (strcmp(text, *entry++) == 0) {
            *value = i;
            return 1;
        }
    }
    return 0;
}
```

## DataTagModule::getDataTypeAttrib___dupe2

Candidate `0x94`; retail `0x8C`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getDataTypeAttrib___dupe2) long getDataTypeAttrib___dupe2(void *tag, iks *xml, char *name, unsigned int *value)
{
    char *text = iks_find_attrib(xml, name);
    if (!text) return 0;
    char **entry = _data_type_strings;
    for (int i = 0; i < 3; ++i) {
        if (strcmp(text, *entry++) == 0) {
            *value = i;
            return 1;
        }
    }
    return 0;
}
```

## TagUtils::getLinkOptionAttrib

Candidate `0x8C`; retail `0x84`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getLinkOptionAttrib) long getLinkOptionAttrib(iks *xml, char *name, unsigned int *value)
{
    char *text = iks_find_attrib(xml, name);
    if (!text) return 0;
    char **entry = svoTagLinkOptions;
    for (int i = 0; i < 9; ++i) {
        if (strcmp(text, *entry++) == 0) {
            *value = i;
            return 1;
        }
    }
    return 0;
}
```

## TagUtils::getChildIksStruct

Candidate `0xB4`; retail `0xB0`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getChildIksStruct) iks *getChildIksStruct(iks *xml, char *name)
{
    if (!xml) __SVO_Assert_Handler(svoTagUtilsSource, 0x149);
    iks *child = 0;
    if (iks_has_children(xml)) child = iks_child(xml);
    while (child) {
        if (iks_name(child) && strcmp(name, iks_name(child)) == 0) return child;
        child = iks_next(child);
    }
    return 0;
}
```

## TextInputTag::setText

Candidate `0xC8`; retail `0xBC`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(setText) void setText(TextInputTagState *tag, char *text, unsigned int offset)
{
    resetTextInput(tag);
    strncpy(tag->m_text, text, 512);
    tag->m_curEditOffset = offset;
    tag->m_curRightOffset = offset;
    float width = ((const TextInputTagVtablePrefix *)tag->base.vtable)->getSubstringPixelWidth(tag, 0, offset);
    if (tag->m_curEditOffset > 0 && tag->m_maxWrap < width) {
        tag->m_curLeftOffset = tag->m_curEditOffset;
        do {
            --tag->m_curLeftOffset;
            width = ((const TextInputTagVtablePrefix *)tag->base.vtable)->getSubstringPixelWidth(tag, tag->m_curLeftOffset, tag->m_curEditOffset);
        } while (width < tag->m_maxWrap);
    }
}
```

## LoginTagModule::ScanTags___dupe6

Candidate `0x88`; retail `0x84`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(ScanTags___dupe6) void ScanTags___dupe6(LoginTagModuleState *module, iks *xml, SVTag **tags, CAllContextData *contexts, CTagModuleActions *actions)
{
    char *dtd = iks_find_attrib(xml, svoLoginDTDAttribute);
    if (dtd) ScanTagsHandleLoginDTD(module, xml, contexts, dtd, actions);
    else ScanTagsHandleLoginSubmitResponse(module, xml, contexts, actions);
}
```

## ListBoxTag::isIndexSelected

Candidate `0xC4`; retail `0xC0`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(isIndexSelected) long isIndexSelected(ListBoxTagState *tag, int index)
{
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x290);
    if (tag->m_maxNumItems < tag->m_numItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x291);
    if (index >= tag->m_numItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x292);
    if (!tag->m_items[index]) __SVO_Assert_Handler(svoListBoxTagSource, 0x293);
    return index == tag->m_selectedIndex;
}
```

## ListBoxTag::getSelectedItem

Candidate `0xD4`; retail `0xD0`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getSelectedItem) ListBoxItem *getSelectedItem(ListBoxTagState *tag)
{
    if (!tag->m_numItems) return 0;
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x190);
    if (tag->m_maxNumItems < tag->m_numItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x191);
    if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoListBoxTagSource, 0x192);
    if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x193);
    return tag->m_items[tag->m_selectedIndex];
}
```

## ListBoxTag::calculateScrollBarPercentage

Candidate `0x80`; retail `0x78`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(calculateScrollBarPercentage) float calculateScrollBarPercentage(ListBoxTagState *tag)
{
    int visible = tag->m_numItems;
    if (tag->m_maxVisibleItems < visible) visible = tag->m_maxVisibleItems;
    if (tag->m_topVisibleIndex < 0) __SVO_Assert_Handler(svoListBoxTagSource, 0x2C5);
    if (tag->m_topVisibleIndex > 0) return (float)tag->m_topVisibleIndex / (float)visible;
    return 0;
}
```

## GenericListBoxTag::getIndexOfHandle

Candidate `0xAC`; retail `0xA8`. Retained assembly; not counted as compiled.

```cpp
extern "C" SECTION(getIndexOfHandle) long getIndexOfHandle(GenericListBoxTagState *tag, svo_listbox_handle handle)
{
    if (tag->m_maxNumItems < tag->m_numItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x180);
    if (tag->m_maxNumItems < tag->m_maxVisibleItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x181);
    for (int i = 0; i < tag->m_maxNumItems; ++i) if (tag->m_handles[i] == handle) return i;
    return -1;
}
```
