#include "common.h"
// Retain the unresolved wrapper at its original address.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_chrono_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVChronograph.h"
#include "SVBrowser.h"
#include "CSystemContextBase.h"
#include "CMemoryContextBase.h"

extern "C" {
extern int svoTimerMilliseconds;
extern char svoChronographSource[];
CMemoryContextBaseState *GetMemoryContext(void);
}
#define CHRONO_SECTION(name) __attribute__((section(".svo_chrono_" #name)))

int CHRONO_SECTION(SV_timerGetMilliseconds) SV_timerGetMilliseconds(CSystemContextBase *context)
{
    SVBrowserPrefix *browser = GetInstance();
    if (!context) {
        if (!browser) {
            svoTimerMilliseconds = 0;
            return svoTimerMilliseconds;
        }
        context = GetSystemContext();
    }
    svoTimerMilliseconds = context->vtable->GetElapsedMS(context);
    return svoTimerMilliseconds;
}

void CHRONO_SECTION(SVChronograph) SVChronograph(SVChronographState *timer, int startnow)
{
    timer->start = 1;
    timer->m_pSystemContext = 0;
    timer->stop = 1;
    timer->lastlap = 1;
    if (startnow) Start___dupe3(timer);
}

void CHRONO_SECTION(_SVChronograph) _SVChronograph(SVChronographState *timer, unsigned int flags)
{
    if (flags & 1) SVChronographDelete(timer);
}

// Recovered C currently emits 0x40 bytes for this 0x3C-byte slot.
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVChronograph", operator.new___dupe5);

void CHRONO_SECTION(SVChronographDelete) SVChronographDelete(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

void CHRONO_SECTION(Start___dupe3) Start___dupe3(SVChronographState *timer)
{
    int now = SV_timerGetMilliseconds(timer->m_pSystemContext);
    if (IsStopped(timer)) {
        unsigned int pause = (unsigned int)now - timer->stop;
        timer->stop = 0;
        timer->start = (unsigned int)timer->start + pause;
        timer->lastlap = (unsigned int)timer->lastlap + pause;
    } else {
        Reset___dupe5(timer);
    }
}

void CHRONO_SECTION(Stop___dupe3) Stop___dupe3(SVChronographState *timer)
{
    if (IsRunning(timer)) timer->stop = SV_timerGetMilliseconds(timer->m_pSystemContext);
}

void CHRONO_SECTION(Reset___dupe5) Reset___dupe5(SVChronographState *timer)
{
    int now = SV_timerGetMilliseconds(timer->m_pSystemContext);
    timer->start = now;
    timer->lastlap = now;
}

int CHRONO_SECTION(Elapsed) Elapsed(SVChronographState *timer)
{
    return ElapsedMS(timer) / 1000;
}

int CHRONO_SECTION(ElapsedMS) ElapsedMS(SVChronographState *timer)
{
    int now = IsStopped(timer) ? timer->stop : SV_timerGetMilliseconds(timer->m_pSystemContext);
    int elapsed = (unsigned int)now - timer->start;
    if (elapsed < 0) Reset___dupe5(timer);
    return elapsed;
}

int CHRONO_SECTION(IsRunning) IsRunning(SVChronographState *timer)
{
    return timer->stop == 0;
}

int CHRONO_SECTION(IsStopped) IsStopped(SVChronographState *timer)
{
    return !IsRunning(timer);
}
