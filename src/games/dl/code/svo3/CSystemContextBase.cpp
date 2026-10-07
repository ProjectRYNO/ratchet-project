#include "CSystemContextBase.h"

extern "C" {
extern const char svoSystemContextSource[];
void __SVO_Assert_Handler(const char *file, int line);
}
#define SVO_SYSTEM_SECTION(name) __attribute__((section(".svo_system_" #name)))

void SVO_SYSTEM_SECTION(FileDownloadCallback) FileDownloadCallback(
    CSystemContextBase *context, CFileDownloadInfo *info)
{
    // Retail's base implementation deliberately does nothing.
}

void SVO_SYSTEM_SECTION(EnterStaticScreen) EnterStaticScreen(
    CSystemContextBase *context, char *screenName)
{
    __SVO_Assert_Handler(svoSystemContextSource, 0xE0);
}

long SVO_SYSTEM_SECTION(GetElapsedMS) GetElapsedMS(CSystemContextBase *context)
{
    __SVO_Assert_Handler(svoSystemContextSource, 0xE7);
    return 0;
}

int SVO_SYSTEM_SECTION(OkToFreeFileDownloadBuffer) OkToFreeFileDownloadBuffer(
    CSystemContextBase *context, void *data)
{
    __SVO_Assert_Handler(svoSystemContextSource, 0xF8);
    return 1;
}
