#include "SVBrowser.h"
#include "TagUtils.h"
#include "SetVariableTag.h"
#include "string.h"
#include "SVOString.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SetVariableTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern const SVTagVtablePrefix svoSetVariableTagVtable;
void FreeResources___dupe9(void *tag);

extern "C" {
extern char svoSetVariableTagName[];
extern char gTagNotSetStr[];
}
extern "C" {
extern char svoSetVariableSource[];
extern char svoSendBufferAttribute[];
extern char svoDecryptBufferAttribute[];
extern char svoEncryptBufferAttribute[];
extern int guiServerMessageSize;
extern int guiAppoutMessageSize;
void SetSockSendBufferSize(int);

}
extern "C" {
void handleDownloadThrobber(SetVariableTagState *);
void handleTTYDebugServerSetup(SetVariableTagState *);
void handleHTTPSendBuffer(SetVariableTagState *);
void handleHTTPSBuffers(SetVariableTagState *);
char *DefaultInit___dupe6(SetVariableTagState *);
void SetExternalIPAddress(SVBrowserPrefix *, char *);
void SetPageRefreshSeconds(CPage *, int);
CMemoryContextBaseState *GetMemoryContext();
void sv_connect_to_log_server(CMemoryContextBaseState *, char *, int);
extern char svoAutoRefreshAttribute[];
extern char svoIPAddressAttribute[];
extern char svoTTYServerNameAttribute[];
extern char svoTTYServerPortAttribute[];
extern char svoThrobberXAttribute[];
extern char svoThrobberYAttribute[];
extern char svoThrobberWAttribute[];
extern char svoThrobberHAttribute[];
extern char svoThrobberClassAttribute[];

}
#define SECTION(name) __attribute__((section(".svo_SetVariableTag_" #name)))

SECTION(FreeResources___dupe9) void FreeResources___dupe9(void *self)
{
    // Retail implements this callback as a no-op.
}

SECTION(IsSelectable___dupe7) long IsSelectable___dupe7(void *self)
{
    return 0;
}

}

extern "C" SECTION(_SetVariableTag) void _SetVariableTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoSetVariableTagVtable;
    FreeResources___dupe9((void *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

extern "C" SECTION(DefaultInit___dupe6) char * DefaultInit___dupe6(SetVariableTagState *tag)
{
    char *result = svstrncpy(tag->base.m_tagTypeName, svoSetVariableTagName, 64);
    tag->m_pageRefreshSeconds = 0;
    tag->m_myExternalIP = 0;
    return result;
}

extern "C" SECTION(Draw___dupe11) void Draw___dupe11(SetVariableTagState *tag)
{
    if (!tag->base.m_contexts->drawContext) __SVO_Assert_Handler(svoSetVariableSource, 0x6C);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SetVariableTag", handleDownloadThrobber);

extern "C" SECTION(handleHTTPSBuffers) void handleHTTPSBuffers(SetVariableTagState *tag)
{
    int decrypt = -1;
    getIntAttrib(tag->base.m_xml, svoDecryptBufferAttribute, &decrypt);
    int encrypt = -1;
    guiServerMessageSize = decrypt == -1 ? guiServerMessageSize : decrypt;
    getIntAttrib(tag->base.m_xml, svoEncryptBufferAttribute, &encrypt);
    guiAppoutMessageSize = encrypt == -1 ? guiAppoutMessageSize : encrypt;
}

extern "C" SECTION(handleHTTPSendBuffer) void handleHTTPSendBuffer(SetVariableTagState *tag)
{
    int size = -1;
    getIntAttrib(tag->base.m_xml, svoSendBufferAttribute, &size);
    if (size != -1) SetSockSendBufferSize(size);
}

extern "C" SECTION(HandleInput___dupe37) long HandleInput___dupe37(SetVariableTagState *tag, CPage *page)
{
    CInputContextBaseState *input = tag->base.m_contexts->inputContext;
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoSetVariableSource, 0x5D);
    if (!input) __SVO_Assert_Handler(svoSetVariableSource, 0x5E);
    if (!page) __SVO_Assert_Handler(svoSetVariableSource, 0x5F);
    if (tag->m_pageRefreshSeconds > 0) SetPageRefreshSeconds(page, tag->m_pageRefreshSeconds);
    return 1;
}

extern "C" SECTION(handleTTYDebugServerSetup) void handleTTYDebugServerSetup(SetVariableTagState *tag)
{
    if (!GetInstance()) __SVO_Assert_Handler(svoSetVariableSource, 0xB5);
    char *name = 0;
    int port = -1;
    long found = getStringAttrib(tag->base.m_xml, svoTTYServerNameAttribute, &name);
    getIntAttrib(tag->base.m_xml, svoTTYServerPortAttribute, &port);
    if (found && port != -1) {
        if (!GetInstance()) __SVO_Assert_Handler(svoSetVariableSource, 0xCB);
        sv_connect_to_log_server(GetMemoryContext(), name, port);
    }
}

extern "C" SECTION(SetVariableTag) void SetVariableTag(SetVariableTagState *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoSetVariableTagVtable;
    DefaultInit___dupe6(tag);
    getIntAttrib(tag->base.m_xml, svoAutoRefreshAttribute, &tag->m_pageRefreshSeconds);
    getStringAttrib(tag->base.m_xml, svoIPAddressAttribute, &tag->m_myExternalIP);
    if (tag->m_myExternalIP) SetExternalIPAddress(GetInstance(), tag->m_myExternalIP);
    handleHTTPSendBuffer(tag);
    handleHTTPSBuffers(tag);
    handleDownloadThrobber(tag);
    handleTTYDebugServerSetup(tag);
}
