#include "DownloadBinary.h"
#include "SVOString.h"

extern "C" {
extern const unsigned char svoDownloadBinaryVtable[];
void DownloadBinaryDelete(void *memory) __asm__("operator.delete___dupe10");
#define SECTION(name) __attribute__((section(".svo_DownloadBinary_" #name)))

SECTION(DownloadBinary) const void *DownloadBinary(DownloadBinaryState *record)
{
    record->bDestroyWhenRequestSent = 0;
    record->vtable = svoDownloadBinaryVtable;
    record->eMethod = 0;
    return svoDownloadBinaryVtable;
}

SECTION(_DownloadBinary) void _DownloadBinary(DownloadBinaryState *record, int flags)
{
    record->vtable = svoDownloadBinaryVtable;
    if (flags & 1) DownloadBinaryDelete(record);
}

SECTION(GetPath) char * GetPath(DownloadBinaryState *record)
{
    return record->szPath;
}

SECTION(GetDownloadCallback) DownloadCallback GetDownloadCallback(DownloadBinaryState *record)
{
    return record->pDownloadCallback;
}

SECTION(GetFormMethodType) int GetFormMethodType(DownloadBinaryState *record)
{
    return record->eMethod;
}

SECTION(GetWidth) unsigned short GetWidth(DownloadBinaryState *record)
{
    return record->usWidth;
}

SECTION(GetHeight) unsigned short GetHeight(DownloadBinaryState *record)
{
    return record->usHeight;
}

SECTION(GetID) int GetID(DownloadBinaryState *record)
{
    return record->iID;
}

SECTION(DestroyOnRequestSend) int DestroyOnRequestSend(DownloadBinaryState *record)
{
    return record->bDestroyWhenRequestSent;
}

SECTION(GetUserNameParameter) char * GetUserNameParameter(DownloadBinaryState *record)
{
    return record->m_szUserNameParameter;
}

SECTION(GetAccountIDParameter) char * GetAccountIDParameter(DownloadBinaryState *record)
{
    return record->m_szAccountIDParameter;
}

SECTION(SetPath) void SetPath(DownloadBinaryState *record, char *text)
{
    svstrncpy(record->szPath, text, 0x101);
}

SECTION(SetUserNameParameter) void SetUserNameParameter(DownloadBinaryState *record, char *text)
{
    svstrncpy(record->m_szUserNameParameter, text, 0x20);
}

SECTION(SetAccountIDParameter) void SetAccountIDParameter(DownloadBinaryState *record, char *text)
{
    svstrncpy(record->m_szAccountIDParameter, text, 0x20);
}

SECTION(SetFormMethodType) void SetFormMethodType(DownloadBinaryState *record, int value)
{
    record->eMethod = value;
}

SECTION(SetID___dupe2) void SetID___dupe2(DownloadBinaryState *record, int value)
{
    record->iID = value;
}

SECTION(SetUserNameMaxLength) void SetUserNameMaxLength(DownloadBinaryState *record, int value)
{
    record->m_iUserNameMaxLength = value;
}

SECTION(SetDownloadCallback) void SetDownloadCallback(DownloadBinaryState *record, DownloadCallback callback)
{
    record->pDownloadCallback = callback;
    record->bRequested = 0;
}

SECTION(SetDimensions___dupe2) void SetDimensions___dupe2(DownloadBinaryState *record, unsigned short width, unsigned short height)
{
    record->usHeight = height;
    record->usWidth = width;
}

SECTION(SetToDestroyOnRequestSend) void SetToDestroyOnRequestSend(DownloadBinaryState *record)
{
    record->bDestroyWhenRequestSent = 1;
}

}
