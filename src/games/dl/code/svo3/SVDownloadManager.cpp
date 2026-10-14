#include "SVTag.h"
#include "CInputContextBase.h"
#include "SVDownloadManager.h"
#include "CSystemContextBase.h"
#include "CMemoryContextBase.h"
#include "SVTagModule.h"

extern "C" {
extern const IRequestListenerVtablePrefix svoDownloadManagerVtable;
extern char svoSVDownloadManagerSource[];
CMemoryContextBaseState *GetMemoryContext();
void Http(HttpState *, CMemoryContextBaseState *, int);
void _Http(HttpState *, int);
void shutdown___dupe3(SVDownloadManagerState *);
void setState(SVDownloadManagerState *, int);
void DownloadManagerDelete(void *) __asm__("operator.delete___dupe12");
void NotifySystemContextOfChunk(SVDownloadManagerState *, DLBuffer *);
}

extern "C" void DownloadManagerConstruct(SVDownloadManagerState *, char *, char *, char *, int, CPage *, CMemoryContextBaseState *, unsigned int) __asm__("SVDownloadManager");




#include "CError.h"
#include "CSystemContextBase.h"
#include "CMemoryContextBase.h"
#include "SVTagModule.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SVDownloadManager_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVDownloadManager.h"

extern "C" {

CMemoryContextBaseState *GetMemoryContext(void);
extern char svoSVDownloadManagerSource[];
void * SVDownloadManageroperator_new___dupe13(unsigned int size) __asm__("operator.new___dupe13");


extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
void SVDownloadManageroperator_delete___dupe12(void *memory) __asm__("operator.delete___dupe12");

}
extern "C" {
void setState(SVDownloadManagerState *, int);
void NotifySystemContextOfChunk(SVDownloadManagerState *, DLBuffer *);
void NotifySystemContextOfFailure(SVDownloadManagerState *);
void freeResources___dupe2(HttpState *, int);
void freeResources___dupe4(SVDownloadManagerState *, int);
void UpdateFileDownload(SVDownloadManagerState *);
int IsSystemFinishedWithBuffers(SVDownloadManagerState *);
void download___dupe2(HttpState *);
}
#include "HttpUtils.h"
#include "SVOString.h"
#include "string.h"
#include "stdio.h"
extern "C" {
extern char svoDownloadHttpScheme[];
extern char svoDownloadGetCommand[];
extern char svoDownloadStatusToken[];
extern char svoDownloadStatusFormat[];
int doRequest___dupe2(HttpState *, URIRequest *, IRequestListenerState *, void *);
}
#define SECTION(name) __attribute__((section(".svo_SVDownloadManager_" #name)))

static inline void ResetDLBuffer(DLBuffer *buffer)
{
    buffer->bytesReceived = 0;
    buffer->bWaitingForSystemOk = 0;
    buffer->bBeingUsedForDownload = 0;
    buffer->startPos = 0xFFFFFFFF;
}

SECTION(setState) void setState(SVDownloadManagerState *manager, int state)
{
    manager->m_state = state;
}

SECTION(OnURIRequestRedirectReceived) void OnURIRequestRedirectReceived(SVDownloadManagerState *manager, void *context, char *url)
{
    // Retail does not handle redirects in this listener callback.
}

}

extern "C" SECTION(_SVDownloadManager) void _SVDownloadManager(SVDownloadManagerState *manager, int flags)
{
    manager->base.vtable = &svoDownloadManagerVtable;
    shutdown___dupe3(manager);
    int index = 0;
    int count = 1;
    do {
        if (manager->m_buffers[index].pData) {
            svFreeSafe(GetMemoryContext(), manager->m_buffers[index].pData);
            manager->m_buffers[index].pData = 0;
            manager->m_buffers[index].dataSizeBytes = 0;
        }
        index++;
    } while (--count >= 0);
    _SVChronograph(&manager->m_timer, 2);
    _Http(&manager->m_http, 2);
    if (flags & 1) { DownloadManagerDelete(manager); return; }
}

extern "C" SECTION(doRequest___dupe4) int doRequest___dupe4(SVDownloadManagerState *manager, char *path, CQueryParamListState *params, int method, char *id)
{
    char requestPath[272];
    char originalPath[272];
    SVPath split;
    URIRequest request;
    char filename[32];
    if (!path) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x146);
    if (manager->m_bRequestInProgress) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x147);
    svstrncpy(manager->m_fileID, id, 257);
    Reset___dupe5(&manager->m_timer);
    Start___dupe3(&manager->m_timer);
    svstrncpy(originalPath, path, strlen(path) + 1);
    if (pathIsFullyQualified___dupe2(path)) {
        SVPath *target = &split;
        target->m_scheme = manager->m_scheme;
        target->m_server = manager->m_serverName;
        target->m_port = &manager->m_port;
        target->m_path = requestPath;
        target->m_pathMaxLength = 257;
        parseFullyQualifiedPath(path, target);
    } else {
        __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x161);
        return 0;
    }
    if (manager->m_state) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x16B);
    for (int index = 0; index < 2; index++) {
        if (manager->m_buffers[index].pData) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x170);
        manager->m_buffers[index].pData = (char *)svAllocSafe(GetMemoryContext(), manager->m_buffers[index].dataSizeBytes, 4, 0x171, svoSVDownloadManagerSource);
        if (!manager->m_buffers[index].pData) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x172);
    }
    request.scheme = svoDownloadHttpScheme;
    request.host = manager->m_serverName;
    request.port = manager->m_port;
    request.filePath = requestPath;
    request.params = params;
    request.methodType = method;
    request.httpCommand = svoDownloadGetCommand;
    request.context = 0;
    if (!doRequest___dupe2(&manager->m_http, &request, &manager->base, manager)) {
        __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x185);
        return 0;
    }
    int length = strlen(path);
    int position = length;
    for (int i = 0; i < length; i++) {
        if (path[position] == '/' || !position) {
            svstrncpy(filename, &path[position] + 1, 32);
            break;
        }
        position--;
    }
    svstrncpy(manager->m_fileName, filename, 32);
    setState(manager, 1);
    manager->m_bRequestInProgress = 1;
    return 1;
}

extern "C" SECTION(download___dupe3) void download___dupe3(SVDownloadManagerState *manager)
{
    int state = manager->m_state;
    if (GetErrorCode()) setState(manager, -1);
    if (manager->m_bRequestInProgress) UpdateFileDownload(manager);
    switch (state) {
    case 1:
        freeResources___dupe4(manager, 1);
        download___dupe2(&manager->m_http);
        break;
    case 3:
        if (IsSystemFinishedWithBuffers(manager)) {
            manager->m_bRequestInProgress = 0;
            freeResources___dupe4(manager, 0);
            setState(manager, 0);
        }
        break;
    case -1:
    case 0:
    case 2:
        break;
    default:
        __SVO_Assert_Handler(svoSVDownloadManagerSource, 0xCA);
        break;
    }
    if (GetErrorCode()) setState(manager, -1);
}

#include "CDrawContextBase.h"
#include "TextTag.h"
extern "C" SVTag *getTagByName(char *name, CPage *page);
extern "C" CAllContextData svoPageContextData;
extern "C" char svoDownloadProgressRectName[], svoDownloadProgressTextName[], svoDownloadProgressPercentName[];
extern "C" char svoDownloadOutlineRectClass[], svoDownloadFillRectClass[], svoDownloadRateFormat[];
extern "C" const long long svoDownloadBlockedText[];
extern "C" char svoDownloadRateClass[], svoDownloadBytesFormat[], svoDownloadNotSetClass[];
extern "C" void formatDownloadStatusText(SVDownloadManagerState *manager, char *dst, char *src, char *id, int percent);
static inline int DLBufferIsFull(DLBuffer *buffer)
{
    return buffer->bytesReceived >= buffer->dataSizeBytes;
}

extern "C" SECTION(draw___dupe2) void draw___dupe2(SVDownloadManagerState *manager)
{
    if (manager->m_state == 1 || manager->m_state == 3) {
        CAllContextData contexts;
        CDrawContextBase *draw;
        int x;
        int progW;
        int y;
        int w;
        int h;
        unsigned int outlineColor;
        unsigned int fillColor;
        float percentComplete;
        SVTag *back;
        TextTagState *text;
        SVTag *pct;
        char dstr[128];
        unsigned int tagID;
        float kBytesPerSecond;
        w = 200;
        contexts = svoPageContextData;
        draw = contexts.drawContext;
        h = 30;
        percentComplete = (float)manager->m_fileBytesReceived / (float)manager->m_fileContentLength;
        back = getTagByName(svoDownloadProgressRectName, manager->m_page);
        text = (TextTagState *)getTagByName(svoDownloadProgressTextName, manager->m_page);
        pct = getTagByName(svoDownloadProgressPercentName, manager->m_page);
        if (back) {
            tagID = back->vtable->GetTagID(back);
            x = (int)back->m_x;
            y = (int)back->m_y;
            w = (int)back->m_width;
            h = (int)back->m_height;
            back->vtable->SetVisible(back, 0);
            outlineColor = back->m_lineColor;
            fillColor = back->m_fillColor;
            draw->vtable->DrawRectangle(draw, tagID, (float)x, (float)y, (float)w, (float)h, outlineColor, outlineColor, 1, 0, 100000.0f, 0, svoDownloadOutlineRectClass);
            if (pct) {
                tagID = pct->vtable->GetTagID(pct);
                x = (int)pct->m_x;
                y = (int)pct->m_y;
                w = (int)pct->m_width;
                h = (int)pct->m_height;
                pct->vtable->SetVisible(pct, 0);
                outlineColor = pct->m_lineColor;
                fillColor = pct->m_fillColor;
            }
            progW = (int)((float)w * percentComplete);
            draw->vtable->DrawRectangle(draw, tagID, (float)x, (float)y, (float)progW, (float)h, outlineColor, fillColor, 1, 0, 100000.0f, 0, svoDownloadFillRectClass);
        }
        memset(dstr, 0, 128);
        if (text) {
            x = (int)text->base.m_x;
            y = (int)text->base.m_y;
            kBytesPerSecond = (float)manager->m_fileBytesReceived / (float)Elapsed(&manager->m_timer);
            sprintf(dstr, svoDownloadRateFormat, Elapsed(&manager->m_timer), (double)kBytesPerSecond);
            draw->vtable->SVDrawText(draw, 0, (float)x + (float)(w / 2), (float)y - (float)(h * 2 + h), 0xFFFFFFFF, dstr, strlen(dstr), 12, 1, svoDownloadRateClass);
            sprintf(dstr, svoDownloadBytesFormat, manager->m_fileBytesReceived, manager->m_fileContentLength);
            draw->vtable->SVDrawText(draw, 0, (float)x, (float)y - (float)(h * 2), 0xFFFFFF77, dstr, strlen(dstr), 12, 0, svoDownloadNotSetClass);
            DLBuffer *buffer0 = &manager->m_buffers[0];
            DLBuffer *buffer1;
            if (DLBufferIsFull(buffer0) && DLBufferIsFull(buffer1 = &manager->m_buffers[1])
                && (buffer0->bWaitingForSystemOk || buffer1->bWaitingForSystemOk)) {
                memcpy(dstr, svoDownloadBlockedText, 41);
                draw->vtable->SVDrawText(draw, 0, (float)x, (float)y - (float)h, 0xFFFFFF77, dstr, strlen(dstr), 12, 0, svoDownloadNotSetClass);
            }
            int percent = (int)((double)percentComplete * 100.0);
            formatDownloadStatusText(manager, dstr, text->m_text, manager->m_fileID, percent);
            text->base.vtable->SetVisible(&text->base, 0);
            float tx = text->base.m_x;
            float ty = text->base.m_y;
            unsigned int color = text->m_textColor;
            draw->vtable->SVDrawText(draw, 0, tx, ty, color, dstr, strlen(dstr), text->m_fontSize, text->m_align, text->base.m_tagClass);
        }
    }
}

extern "C" SECTION(formatDownloadStatusText) void formatDownloadStatusText(SVDownloadManagerState *manager, char *dst, char *src, char *id, int percent)
{
    char text[128];
    if (strlen(src) > 127) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x262);
    int position = my_strcspn(src, svoDownloadStatusToken);
    int next = position + 6;
    if (position < 1) svstrncpy(dst, src, 128);
    else {
        memcpy(dst, src, position);
        dst[position - 1] = 0;
        sprintf(text, svoDownloadStatusFormat, manager->m_fileID, percent);
        strcat(dst, text);
        svstrncpy(text, src + next, strlen(src));
        strcat(dst, text);
    }
}

extern "C" SECTION(freeResources___dupe4) void freeResources___dupe4(SVDownloadManagerState *manager, int keep)
{
    if (!keep) {
        freeResources___dupe2(&manager->m_http, keep);
        setState(manager, 0);
        for (int i = 0; i < 2; ++i) {
            if (manager->m_buffers[i].pData) {
                CMemoryContextBaseState *memory = GetMemoryContext();
                svFreeSafe(memory, manager->m_buffers[i].pData);
                manager->m_buffers[i].pData = 0;
            }
        }
    }
}

extern "C" SECTION(IsSystemFinishedWithBuffers) int IsSystemFinishedWithBuffers(SVDownloadManagerState *manager)
{
    DLBuffer *first = &manager->m_buffers[0];
    int finished = 0;
    DLBuffer *second;
    if (!first->bWaitingForSystemOk && !(second = &manager->m_buffers[1])->bWaitingForSystemOk) {
        if (first->bytesReceived || second->bytesReceived) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x398);
        finished = 1;
    }
    return finished;
}

extern "C" SECTION(NotifySystemContextOfChunk) void NotifySystemContextOfChunk(SVDownloadManagerState *manager, DLBuffer *buffer)
{
    if (!buffer->bBeingUsedForDownload) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x296);
    if (buffer->bWaitingForSystemOk) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x297);
    CFileDownloadInfo info;
    info.name = manager->m_fileName;
    info.fileID = manager->m_fileID;
    info.pData = buffer->pData;
    info.dataLen = buffer->bytesReceived;
    info.partialDownloadInfo = manager->m_fileBytesReceived < manager->m_fileContentLength;
    info.curTotalDataLen = buffer->startPos + buffer->bytesReceived;
    info.entireDataLen = manager->m_fileContentLength;
    CSystemContextBase *system = GetSystemContext();
    system->vtable->FileDownloadCallback(system, &info);
    buffer->bBeingUsedForDownload = 0;
    buffer->bWaitingForSystemOk = 1;
}

extern "C" SECTION(NotifySystemContextOfFailure) void NotifySystemContextOfFailure(SVDownloadManagerState *manager)
{
    CFileDownloadInfo info;
    info.name = manager->m_fileName;
    info.fileID = manager->m_fileID;
    info.pData = 0;
    info.dataLen = 0;
    info.curTotalDataLen = manager->m_fileBytesReceived;
    info.partialDownloadInfo = 2;
    info.entireDataLen = manager->m_fileContentLength;
    CSystemContextBase *system = GetSystemContext();
    system->vtable->FileDownloadCallback(system, &info);
}

extern "C" SVTag *getTagByName(char *name, CPage *page);
extern "C" CAllContextData svoPageContextData;
extern "C" SECTION(okToNavigate___dupe4) int okToNavigate___dupe4(SVDownloadManagerState *manager)
{
    if (!manager->m_state) return 1;
    SVTag *tag = getTagByName(manager->m_fileID, manager->m_page);
    if (!tag) return 1;
    if (!tag->vtable->okToNavigate(tag)) {
        CAllContextData contexts = svoPageContextData;
        HasActionOccurred(contexts.inputContext, 0x11, SV_ACTION_BACK);
    }
    return tag->vtable->okToNavigate(tag);
}

extern "C" SECTION(OnURIRequestChunkReceived) void OnURIRequestChunkReceived(SVDownloadManagerState *manager, void *context, DLBuffer *buffer, char *data, int length)
{
    if (buffer != &manager->m_buffers[0] && buffer != &manager->m_buffers[1]) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x322);
    if (data != buffer->pData + buffer->bytesReceived) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x323);
    manager->m_fileBytesReceived += length;
    buffer->bytesReceived += length;
    if (buffer->dataSizeBytes < buffer->bytesReceived) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x329);
    if (DLBufferIsFull(buffer) && !manager->m_buffers[0].bWaitingForSystemOk && !manager->m_buffers[1].bWaitingForSystemOk)
        NotifySystemContextOfChunk(manager, buffer);
}

extern "C" SECTION(OnURIRequestCompletion) void OnURIRequestCompletion(SVDownloadManagerState *manager, void *context, int status)
{
    if (!status || manager->m_fileBytesReceived != manager->m_fileContentLength) {
        SetErrorCode(29);
        NotifySystemContextOfFailure(manager);
    }
    Stop___dupe3(&manager->m_timer);
    setState(manager, 3);
}

extern "C" SECTION(OnURIRequestHeaderReceived) int OnURIRequestHeaderReceived(SVDownloadManagerState *manager, void *context, int type, int status, unsigned int length)
{
    manager->m_fileStatus = status;
    manager->m_fileContentLength = length;
    manager->m_fileBytesReceived = 0;
    ResetDLBuffer(&manager->m_buffers[0]);
    ResetDLBuffer(&manager->m_buffers[1]);
    if (!length) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x309);
    return 1;
}

static inline int DLBufferHasRoom(DLBuffer *buffer)
{
    return buffer->bytesReceived < buffer->dataSizeBytes;
}

extern "C" SECTION(OnURIRequestIsOkContinueDownload) int OnURIRequestIsOkContinueDownload(SVDownloadManagerState *manager, void *context, URIReceiveBuffer *result)
{
    DLBuffer *buffer = 0;
    int ok = 0;
    DLBuffer *first = &manager->m_buffers[0];
    DLBuffer *second;
    if (!first->bWaitingForSystemOk && !(second = &manager->m_buffers[1])->bWaitingForSystemOk) {
        if (!first->bytesReceived) {
            buffer = !second->bytesReceived ? first : second;
        } else if (!second->bytesReceived) {
            buffer = first;
        } else {
            __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x356);
        }
    } else {
        if (manager->m_buffers[0].bWaitingForSystemOk && !DLBufferIsFull(&manager->m_buffers[1])) {
            buffer = &manager->m_buffers[1];
        } else if (manager->m_buffers[1].bWaitingForSystemOk) {
            if (DLBufferHasRoom(&manager->m_buffers[0])) buffer = &manager->m_buffers[0];
        }
    }
    if (buffer) {
        if (!buffer->pData) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x368);
        ok = 1;
        unsigned int received = buffer->bytesReceived;
        result->context = buffer;
        result->size = buffer->dataSizeBytes - received;
        result->data = buffer->pData + received;
        buffer->bBeingUsedForDownload = ok;
        if (!buffer->bytesReceived) buffer->startPos = manager->m_fileBytesReceived;
    }
    return ok;
}

extern "C" SECTION(OnURIRequestStart) void OnURIRequestStart(SVDownloadManagerState *manager, void *context)
{
    manager->m_fileContentLength = 0;
    manager->m_fileStatus = 500;
    manager->m_fileBytesReceived = 0;
    ResetDLBuffer(&manager->m_buffers[0]);
    ResetDLBuffer(&manager->m_buffers[1]);
}

extern "C" SECTION(operator.delete___dupe12) void SVDownloadManageroperator_delete___dupe12(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

extern "C" SECTION(operator.new___dupe13) void * SVDownloadManageroperator_new___dupe13(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0, 0x31, svoSVDownloadManagerSource);
}

extern "C" SECTION(shutdown___dupe3) void shutdown___dupe3(SVDownloadManagerState *manager)
{
    freeResources___dupe4(manager, 0);
    freeResources___dupe2(&manager->m_http, 1);
}

extern "C" SECTION(SVDownloadManager) void DownloadManagerConstruct(SVDownloadManagerState *manager, char *firstPage, char *user, char *password, int account, CPage *page, CMemoryContextBaseState *memory, unsigned int bufferSize)
{
    manager->base.vtable = &svoDownloadManagerVtable;
    Http(&manager->m_http, memory, 2);
    DLBuffer *buffer = manager->m_buffers;
    int count = 1;
    do {
        buffer->dataSizeBytes = 0;
        buffer->bytesReceived = 0;
        buffer->pData = 0;
        buffer->bWaitingForSystemOk = 0;
        buffer->bBeingUsedForDownload = 0;
        buffer->startPos = 0xFFFFFFFFu;
        ++buffer;
    } while (--count != -1);
    SVChronograph(&manager->m_timer, 0);
    if (!page) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x5E);
    manager->m_page = page;
    manager->m_state = 0;
    setState(manager, 0);
    manager->m_bRequestInProgress = 0;
    if (bufferSize < 2) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x67);
    if (!(bufferSize >> 1)) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x6A);
    for (int index = 0; index < 2; index++) {
        manager->m_buffers[index].pData = 0;
        manager->m_buffers[index].dataSizeBytes = bufferSize >> 1;
    }
}

static inline int DLBufferHasData(DLBuffer *b) { return b->bytesReceived != 0; }

extern "C" SECTION(UpdateFileDownload) void UpdateFileDownload(SVDownloadManagerState *manager)
{
    DLBuffer *first = &manager->m_buffers[0];
    if (first->bWaitingForSystemOk) {
        DLBuffer *second = &manager->m_buffers[1];
        if (second->bWaitingForSystemOk) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x2C2);
        CSystemContextBase *system = GetSystemContext();
        if (((const DownloadSystemVtable *)system->vtable)->OkToFreeFileDownloadBuffer(system, manager->m_buffers[0].pData)) {
            ResetDLBuffer(first);
            if (DLBufferIsFull(second) || (manager->m_state == 3 && DLBufferHasData(second))) {
                NotifySystemContextOfChunk(manager, second);
                return;
            }
        }
    } else {
        DLBuffer *second = &manager->m_buffers[1];
        if (second->bWaitingForSystemOk) {
            CSystemContextBase *system = GetSystemContext();
            if (((const DownloadSystemVtable *)system->vtable)->OkToFreeFileDownloadBuffer(system, manager->m_buffers[1].pData)) {
                ResetDLBuffer(second);
                if (DLBufferIsFull(first) || (manager->m_state == 3 && DLBufferHasData(first))) {
                    NotifySystemContextOfChunk(manager, first);
                    return;
                }
            }
        } else if (manager->m_state == 3) {
            if (first->bBeingUsedForDownload) {
                if (second->bBeingUsedForDownload) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x2E3);
                NotifySystemContextOfChunk(manager, first);
                return;
            }
            if (second->bBeingUsedForDownload) NotifySystemContextOfChunk(manager, second);
        }
    }
}
