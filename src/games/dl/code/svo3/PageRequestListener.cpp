#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_PageRequestListener_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "PageRequestListener.h"
#include "SVTagModule.h"
#include "SVBrowser.h"
#include "CPage.h"
#include "HttpUtils.h"
#include <string.h>

extern "C" {
extern char svoPageRequestListenerSource[];
extern const unsigned char svoPageRequestListenerVtable[];
extern DownloadBuffer svoPageRequestDownloadBuffer;
void PageRequestListenerDelete(PageRequestListenerState *listener) __asm__("operator.delete___dupe14");
void Reset___dupe6(PageRequestListenerState *listener);
void addToHistory(CPage *page, char *url);
#define SECTION(name) __attribute__((section(".svo_PageRequestListener_" #name)))

SECTION(PageRequestListener) void PageRequestListener(PageRequestListenerState *listener, CMemoryContextBaseState *memory, unsigned int length)
{
    listener->m_downloadBufferLength = length;
    listener->vtable = svoPageRequestListenerVtable;
    if (!memory) __SVO_Assert_Handler(svoPageRequestListenerSource, 0x61);
    listener->m_pMemoryContext = memory;
    listener->m_pBodyData = 0;
    Reset___dupe6(listener);
}

SECTION(_PageRequestListener) void _PageRequestListener(PageRequestListenerState *listener, int flags)
{
    listener->vtable = svoPageRequestListenerVtable;
    Reset___dupe6(listener);
    if (flags & 1) PageRequestListenerDelete(listener);
}

SECTION(operator.delete___dupe14) void PageRequestListenerDelete(PageRequestListenerState *listener)
{
    svFreeSafe(listener->m_pMemoryContext, listener);
}

SECTION(Reset___dupe6) void Reset___dupe6(PageRequestListenerState *listener)
{
    listener->m_completionStatus = 500;
    if (listener->m_pBodyData) {
        svFreeSafe(listener->m_pMemoryContext, listener->m_pBodyData);
        listener->m_pBodyData = 0;
    }
    listener->m_bFinished = 0;
    listener->m_bodyDataLength = 0;
    listener->m_bodyContentType = 0;
    listener->m_bodyDataAmountReceived = 0;
}

SECTION(OnURIRequestStart___dupe2) void OnURIRequestStart___dupe2(PageRequestListenerState *listener, void *context)
{
    Reset___dupe6(listener);
}

SECTION(OnURIRequestChunkReceived___dupe2) int OnURIRequestChunkReceived___dupe2(PageRequestListenerState *listener, void *context, void *bufferContext, char *data, unsigned int length)
{
    if (!listener->m_pBodyData) __SVO_Assert_Handler(svoPageRequestListenerSource, 0xAD);
    EnsureCleanBlocks(listener->m_pMemoryContext);
    if (data != listener->m_pBodyData + listener->m_bodyDataAmountReceived) {
        if (listener->m_bodyDataAmountReceived) __SVO_Assert_Handler(svoPageRequestListenerSource, 0xC2);
        memcpy(listener->m_pBodyData + listener->m_bodyDataAmountReceived, data, length);
    }
    listener->m_bodyDataAmountReceived += length;
    if (listener->m_bodyDataLength < listener->m_bodyDataAmountReceived)
        __SVO_Assert_Handler(svoPageRequestListenerSource, 0xC6);
    return EnsureCleanBlocks(listener->m_pMemoryContext);
}

SECTION(OnURIRequestIsOkContinueDownload___dupe2) int OnURIRequestIsOkContinueDownload___dupe2(PageRequestListenerState *listener, void *context, DownloadBuffer *buffer)
{
    buffer->length = listener->m_bodyDataLength - listener->m_bodyDataAmountReceived;
    buffer->data = listener->m_pBodyData + listener->m_bodyDataAmountReceived;
    svoPageRequestDownloadBuffer.data = buffer->data;
    svoPageRequestDownloadBuffer.length = buffer->length;
    svoPageRequestDownloadBuffer.context = buffer->context;
    return 1;
}

SECTION(OnURIRequestHeaderReceived___dupe2) int OnURIRequestHeaderReceived___dupe2(PageRequestListenerState *listener, void *context, int contentType, int status, unsigned int length)
{
    listener->m_bodyContentType = contentType;
    listener->m_completionStatus = status;
    if (status != 302) {
        if (listener->m_pBodyData) __SVO_Assert_Handler(svoPageRequestListenerSource, 0xF1);
        if (listener->m_bodyDataAmountReceived) __SVO_Assert_Handler(svoPageRequestListenerSource, 0xF2);
        if (!length) length = listener->m_downloadBufferLength;
        listener->m_bodyDataLength = length;
        listener->m_pBodyData = (char *)svAllocSafe(listener->m_pMemoryContext, length, 4, 0xFA, svoPageRequestListenerSource);
        memset(listener->m_pBodyData, 0, length);
    }
    listener->m_bodyDataAmountReceived = 0;
    return 0;
}

SECTION(OnURIRequestRedirectReceived___dupe2) void OnURIRequestRedirectReceived___dupe2(PageRequestListenerState *listener, void *context, char *url)
{
    SVBrowserPrefix *browser = GetInstance();
    CPage *page = browser->m_pPopupPage;
    if (!page || !page->m_bIsActive) {
        page = browser->m_pMainPage;
        if (page && !page->m_bIsActive) page = 0;
    }
    if (page) addToHistory(page, url);
}

SECTION(OnURIRequestCompletion___dupe2) void OnURIRequestCompletion___dupe2(PageRequestListenerState *listener, void *context)
{
    if ((unsigned int)(listener->m_bodyContentType - 1) < 3)
        printFormattedBody(listener->m_pBodyData, listener->m_bodyDataAmountReceived, listener->m_bodyContentType);
    listener->m_bFinished = 1;
}

SECTION(GetResponse) int GetResponse(PageRequestListenerState *listener, char **data, int *length)
{
    *data = listener->m_pBodyData;
    if (!listener->m_bFinished) __SVO_Assert_Handler(svoPageRequestListenerSource, 0x148);
    *length = listener->m_bodyDataAmountReceived;
    return listener->m_pBodyData != 0;
}

SECTION(GetLastStatus) int GetLastStatus(PageRequestListenerState *listener)
{
    return listener->m_completionStatus;
}

SECTION(GetLastContentType) int GetLastContentType(PageRequestListenerState *listener)
{
    return listener->m_bodyContentType;
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/PageRequestListener", func_01F27658);
