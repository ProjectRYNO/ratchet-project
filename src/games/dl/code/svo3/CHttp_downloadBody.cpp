// CHttp downloadBody, built with -fno-gcse (DECISIONS D14). Retail has none of the -Os code
// hoisting that GCSE applies to the identical Recv arms below; the rest of CHttp.cpp needs GCSE.
#include "CHttp.h"
#include "SVTagModule.h"
#include "CError.h"
#include "common.h"

extern "C" {
extern char svoHttpSource[];
void OnBodyChunkReceived(HttpState *, void *, char *, int);
int downloadBody(HttpState *);
}
#define SECTION(name) __attribute__((section(".svo_CHttp_" #name)))

extern "C" SECTION(downloadBody) int downloadBody(HttpState *http)
{
    int finished = 0;
    if (!http->m_sock) __SVO_Assert_Handler(svoHttpSource, 0x228);
    IRequestListenerState *listener = http->m_pListener;
    if (!listener) __SVO_Assert_Handler(svoHttpSource, 0x22C);
    else {
        URIReceiveBuffer buffer;
        buffer.data = 0;
        buffer.size = 0;
        if (listener->vtable->OnURIRequestIsOkContinueDownload(listener, http->m_pListenerContext, &buffer)) {
            int received = 0;
            if (!buffer.size) finished = 1;
            else {
                // Both arms are identical; retail keeps the m_contentLength load after they merge.
                if (!(http->m_contentLength ? ((const SVSockVtablePrefix *)http->m_sock->vtable)->Recv(http->m_sock, buffer.data, buffer.size, &received, &finished) : ((const SVSockVtablePrefix *)http->m_sock->vtable)->Recv(http->m_sock, buffer.data, buffer.size, &received, &finished))) SetErrorCode(0x15);
                else if (received) OnBodyChunkReceived(http, buffer.context, buffer.data, received);
            }
        }
    }
    return finished;
}
