#include "CError.h"
#include "CSystemContextBase.h"

struct SVBrowser;
extern "C" SVBrowser *GetInstance(void);
#define SVO_ERROR_SECTION(name) __attribute__((section(".svo_error_" #name)))

void SVO_ERROR_SECTION(SetErrorCode) SetErrorCode(int code)
{
    // The first nonzero error is latched before notifying the browser.
    if (svoErrorCode == 0 && code != 0) {
        svoErrorCode = code;
        if (GetInstance()) {
            CSystemContextBase *context = GetSystemContext();
            if (context) {
                context->vtable->ErrorCallback(context, code);
            }
        }
    }
}

int SVO_ERROR_SECTION(GetErrorCode) GetErrorCode(void)
{
    return svoErrorCode;
}
