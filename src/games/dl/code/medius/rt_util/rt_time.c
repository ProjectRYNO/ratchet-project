#include "common.h"
#include "rt_time.h"

#define MEDIUS_TIME_SECTION(name) __attribute__((section(".medius_time_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_time_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#define RT_INVALID_PARAM 2

void rt_time_platform_init(void);

int MEDIUS_TIME_SECTION(rt_time_get_local) rt_time_get_local(RT_TIME_VAL *pMSecs)
{
    return rt_time_get_msecs(pMSecs);
}

int MEDIUS_TIME_SECTION(rt_time_get_msecs) rt_time_get_msecs(RT_TIME_VAL *pMSecs)
{
    int result;
    RT_TIME_STAMP diff;

    if (!pMSecs) return RT_INVALID_PARAM;
    result = rt_time_get_base_diff(&diff);
    if (result) return result;
    return rt_time_timestamp_to_msecs(&diff, pMSecs);
}

int MEDIUS_TIME_SECTION(rt_time_start) rt_time_start(RT_TIME_STAMP *pStartTimeStamp)
{
    return rt_time_get_time_stamp(pStartTimeStamp);
}

int MEDIUS_TIME_SECTION(rt_time_get_time_stamp) rt_time_get_time_stamp(RT_TIME_STAMP *pTimeStamp)
{
    return rt_time_platform_get_time_stamp(pTimeStamp);
}

int MEDIUS_TIME_SECTION(rt_time_elapsed) rt_time_elapsed(RT_TIME_STAMP *pStartTimeStamp, RT_TIME_VAL *pMSecs)
{
    return rt_time_elapsed_msecs(pStartTimeStamp, pMSecs);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_time", func_01EAB2B8);

int MEDIUS_TIME_SECTION(rt_time_elapsed_msecs) rt_time_elapsed_msecs(RT_TIME_STAMP *pStartTimeStamp, RT_TIME_VAL *pMSecs)
{
    int result = RT_INVALID_PARAM;
    RT_TIME_STAMP elapsed;

    if (pStartTimeStamp && pMSecs) {
        result = rt_time_elapsed_timestamp(pStartTimeStamp, &elapsed);
        if (result == 0) result = rt_time_timestamp_to_msecs(&elapsed, pMSecs);
    }
    return result;
}

int MEDIUS_TIME_SECTION(rt_time_elapsed_usecs) rt_time_elapsed_usecs(RT_TIME_STAMP *pStartTimeStamp, RT_TIME_VAL *pUSecs)
{
    int result = RT_INVALID_PARAM;
    RT_TIME_STAMP elapsed;

    if (pStartTimeStamp && pUSecs) {
        result = rt_time_elapsed_timestamp(pStartTimeStamp, &elapsed);
        if (result == 0) result = rt_time_timestamp_to_usecs(&elapsed, pUSecs);
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_time", rt_time_delay);

int MEDIUS_TIME_SECTION(rt_time_initialize) rt_time_initialize(void)
{
    int result;

    if (rtTimeInitialized == 1) return RT_TIME_ERROR;
    rt_time_platform_init();
    result = rt_time_get_time_stamp(&rtTimeBaseStamp);
    if (result == 0) rtTimeInitialized = 1;
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_time", func_01EAB418);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_time", rt_time_calc_diff);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_time", rt_time_timestamp_to_msecs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_time", rt_time_timestamp_to_usecs);

int MEDIUS_TIME_SECTION(rt_time_get_base_diff) rt_time_get_base_diff(RT_TIME_STAMP *pDiffTimeStamp)
{
    int result = RT_INVALID_PARAM;

    if (pDiffTimeStamp) {
        if (rtTimeInitialized || (result = rt_time_initialize()) == 0) {
            result = rt_time_elapsed_timestamp(&rtTimeBaseStamp, pDiffTimeStamp);
        }
    }
    return result;
}

int MEDIUS_TIME_SECTION(rt_time_elapsed_timestamp) rt_time_elapsed_timestamp(RT_TIME_STAMP *pStartTimeStamp, RT_TIME_STAMP *pElapsedTimeStamp)
{
    int result = RT_INVALID_PARAM;
    RT_TIME_STAMP now;

    if (pStartTimeStamp && pElapsedTimeStamp) {
        result = rt_time_get_time_stamp(&now);
        if (result == 0) result = rt_time_calc_diff(pStartTimeStamp, &now, pElapsedTimeStamp);
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_time", func_01EAB670);

int MEDIUS_TIME_SECTION(rt_time_get_gmtime) rt_time_get_gmtime(RT_TIME_DATE *gmTime)
{
    return rt_time_platform_get_gmtime(gmTime);
}
