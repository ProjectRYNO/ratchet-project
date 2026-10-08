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
void freeResources___dupe2(HttpState *);
void freeResources___dupe4(SVDownloadManagerState *, int);
void UpdateFileDownload(SVDownloadManagerState *);
long IsSystemFinishedWithBuffers(SVDownloadManagerState *);
void download___dupe2(HttpState *);
}
#define SECTION(name) __attribute__((section(".svo_SVDownloadManager_" #name)))

SECTION(setState) void setState(SVDownloadManagerState *manager, int state)
{
    manager->m_state = state;
}

SECTION(OnURIRequestRedirectReceived) void OnURIRequestRedirectReceived(SVDownloadManagerState *manager, void *context, char *url)
{
    // Retail does not handle redirects in this listener callback.
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVDownloadManager", _SVDownloadManager);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVDownloadManager", doRequest___dupe4);

extern "C" SECTION(download___dupe3) void download___dupe3(SVDownloadManagerState *manager)
{
    int state = manager->m_state;
    if (GetErrorCode()) setState(manager, -1);
    if (manager->m_bRequestInProgress) UpdateFileDownload(manager);
    if (state == 1) {
        freeResources___dupe4(manager, 1);
        download___dupe2(&manager->m_http);
    } else if (state == 3) {
        if (IsSystemFinishedWithBuffers(manager)) {
            manager->m_bRequestInProgress = 0;
            freeResources___dupe4(manager, 0);
            setState(manager, 0);
        }
    } else if (state != -1 && state != 0 && state != 2) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0xCA);
    if (GetErrorCode()) setState(manager, -1);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVDownloadManager", draw___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVDownloadManager", formatDownloadStatusText);

extern "C" SECTION(freeResources___dupe4) void freeResources___dupe4(SVDownloadManagerState *manager, int keep)
{
    if (!keep) {
        freeResources___dupe2(&manager->m_http);
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

extern "C" SECTION(IsSystemFinishedWithBuffers) long IsSystemFinishedWithBuffers(SVDownloadManagerState *manager)
{
    if (manager->m_buffers[0].bWaitingForSystemOk || manager->m_buffers[1].bWaitingForSystemOk) return 0;
    if (manager->m_buffers[0].bytesReceived || manager->m_buffers[1].bytesReceived) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x398);
    return 1;
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
    info.entireDataLen = manager->m_fileContentLength;
    info.curTotalDataLen = buffer->startPos + buffer->bytesReceived;
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
    info.partialDownloadInfo = 2;
    info.entireDataLen = manager->m_fileContentLength;
    info.curTotalDataLen = manager->m_fileBytesReceived;
    CSystemContextBase *system = GetSystemContext();
    system->vtable->FileDownloadCallback(system, &info);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVDownloadManager", okToNavigate___dupe4);

extern "C" SECTION(OnURIRequestChunkReceived) void OnURIRequestChunkReceived(SVDownloadManagerState *manager, void *context, DLBuffer *buffer, char *data, int length)
{
    if (buffer != &manager->m_buffers[0] && buffer != &manager->m_buffers[1]) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x322);
    if (data != buffer->pData + buffer->bytesReceived) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x323);
    manager->m_fileBytesReceived += length;
    buffer->bytesReceived += length;
    if (buffer->dataSizeBytes < buffer->bytesReceived) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x329);
    if (buffer->dataSizeBytes <= buffer->bytesReceived && !manager->m_buffers[0].bWaitingForSystemOk && !manager->m_buffers[1].bWaitingForSystemOk)
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

extern "C" SECTION(OnURIRequestHeaderReceived) long OnURIRequestHeaderReceived(SVDownloadManagerState *manager, void *context, int type, int status, unsigned int length)
{
    manager->m_fileStatus = status;
    manager->m_fileContentLength = length;
    manager->m_fileBytesReceived = 0;
    manager->m_buffers[0].startPos = 0xFFFFFFFF;
    manager->m_buffers[0].bytesReceived = 0;
    manager->m_buffers[0].bWaitingForSystemOk = 0;
    manager->m_buffers[0].bBeingUsedForDownload = 0;
    manager->m_buffers[1].startPos = 0xFFFFFFFF;
    manager->m_buffers[1].bytesReceived = 0;
    manager->m_buffers[1].bWaitingForSystemOk = 0;
    manager->m_buffers[1].bBeingUsedForDownload = 0;
    if (!length) __SVO_Assert_Handler(svoSVDownloadManagerSource, 0x309);
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVDownloadManager", OnURIRequestIsOkContinueDownload);

extern "C" SECTION(OnURIRequestStart) void OnURIRequestStart(SVDownloadManagerState *manager, void *context)
{
    manager->m_fileContentLength = 0;
    manager->m_fileStatus = 500;
    manager->m_fileBytesReceived = 0;
    manager->m_buffers[0].startPos = 0xFFFFFFFF;
    manager->m_buffers[0].bytesReceived = 0;
    manager->m_buffers[0].bWaitingForSystemOk = 0;
    manager->m_buffers[0].bBeingUsedForDownload = 0;
    manager->m_buffers[1].startPos = 0xFFFFFFFF;
    manager->m_buffers[1].bytesReceived = 0;
    manager->m_buffers[1].bWaitingForSystemOk = 0;
    manager->m_buffers[1].bBeingUsedForDownload = 0;

}

extern "C" SECTION(operator.delete___dupe12) void SVDownloadManageroperator_delete___dupe12(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVDownloadManager", operator.new___dupe13);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVDownloadManager", shutdown___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVDownloadManager", SVDownloadManager);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVDownloadManager", UpdateFileDownload);
