#include "common.h"
#include "rt_timebase.h"

#define MEDIUS_TIMEBASE_SECTION(name) __attribute__((section(".medius_timebase_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_timebase_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void *memset(void *pointer, int value, unsigned int size);

int MEDIUS_TIMEBASE_SECTION(rt_timebase_get_globaltime) rt_timebase_get_globaltime(RT_TIME_VAL *time)
{
    int result;
    RT_TIME_VAL now;
    RT_TIME_VAL delta;

    result = rt_time_get_local(&now);
    delta = now - rtTimebaseLastLocalTime;
    rtTimebaseLastLocalTime = now;
    rtTimebaseGlobalTime += delta;
    *time = rtTimebaseGlobalTime;
    return result;
}

int MEDIUS_TIMEBASE_SECTION(rt_timebase_get_localtime) rt_timebase_get_localtime(RT_TIME_VAL *time)
{
    return rt_time_get_local(time);
}

int MEDIUS_TIMEBASE_SECTION(rt_timebase_restart) rt_timebase_restart(void)
{
    memset(&rtTimebaseDelays, 0, sizeof(rtTimebaseDelays));
    memset(&rtTimebaseQueryTimer, 0, sizeof(rtTimebaseQueryTimer));
    rtTimebaseLastLocalTime = 0;
    rtTimebaseGlobalTime = 0;
    return 0;
}

void MEDIUS_TIMEBASE_SECTION(rt_timebase_reset_globaltime) rt_timebase_reset_globaltime(RT_TIME_VAL time)
{
    rtTimebaseGlobalTime = time;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_timebase", rt_timebase_update_globaltime);

// Bubble-sorts a copy of the history and returns the 5th-percentile delay (at least entry 1).
int MEDIUS_TIMEBASE_SECTION(rt_timebase_get_percentiledelay) rt_timebase_get_percentiledelay(RT_TIME_VAL *delay)
{
    RT_TIME_VAL sorted[RT_TIMEBASE_HISTORY];
    RT_TIME_VAL swap;
    int i;
    int j;
    int index;

    for (i = 0; i < RT_TIMEBASE_HISTORY; i++) sorted[i] = rtTimebaseDelays.delay[i];
    for (i = rtTimebaseDelays.count - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (sorted[j] > sorted[j + 1]) {
                swap = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = swap;
            }
        }
    }
    index = rtTimebaseDelays.count / 20;
    if (index <= 0) index = 1;
    *delay = sorted[index];
    return 0;
}

void MEDIUS_TIMEBASE_SECTION(rt_timebase_is_query_ready) rt_timebase_is_query_ready(int *ready)
{
    RT_TIME_VAL elapsed;

    *ready = 0;
    rt_time_platform_fast_elapsed_msecs(&rtTimebaseQueryTimer, &elapsed);
    if (elapsed >= rtTimebaseQueryInterval) {
        *ready = 1;
        rt_time_start(&rtTimebaseQueryTimer);
    }
}

int MEDIUS_TIMEBASE_SECTION(rt_timebase_start) rt_timebase_start(void)
{
    if (!rtTimebaseStarted) {
        memset(&rtTimebaseDelays, 0, sizeof(rtTimebaseDelays));
        rtTimebaseStarted = 1;
    }
    return rt_time_start(&rtTimebaseQueryTimer);
}
