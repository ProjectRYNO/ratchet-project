# Remaining HTTP slot blockers (2026-10-09)

Production retains assembly for these three routines. Candidates below are
recovered C/C++, not completed replacements. Sizes use EE GCC 3.2.3 with the
existing -Os flags. No changed ABI, widened slot or handwritten instructions
were integrated to force a fit. Retail Ghidra, split instructions and prototype
CHttp/HttpSecure sources supplied the recovery evidence. No behavior tests run.

The five fitting HTTP functions from this batch are integrated; see SVO3_HANDOFF.md.

## downloadHeaders

Compiled 0x1CC; original allocation 0x1C0.

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

## HTTPS_Malloc

Compiled 0x40; original allocation 0x3C.

```cpp
extern "C" SECTION(HTTPS_Malloc) void * HTTPS_Malloc(unsigned int size)
{
    return svAllocSafe(GetMemoryContext(), size, 0x8, 0x4F, svoHttpSecureSource);
}
```

## operator.new___dupe4

Compiled 0x34; original allocation 0x30.

```cpp
extern "C" SECTION(operator.new___dupe4) void * CHttpoperator_new___dupe4(unsigned int size, CMemoryContextBaseState *memory)
{
    return svAllocSafe(memory, size, 0x4, 0x32, svoHttpSource);
}
```

The downloadHeaders candidate with a cached header pointer is 0x1D0;
removing that cache or grouping locals reduces it to 0x1CC. A scratch experiment
declaring parseHeaderBuf as returning int produced 0x1C4, but differs from the
current long-return declaration and still overruns; it was not integrated.
Revisit verified caller/callee ABI and scheduling, not just measured size.
