#include "common.h"
#include "../../../sdk/sce_missing.h"
#include "../rt_time.h"

#define MEDIUS_TIMEP_SECTION(name) __attribute__((section(".medius_timep_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_timep_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#define RT_INVALID_PARAM 2
#define RT_BCD(x) (((x) >> 4) * 10 + ((x) & 0xF))

extern char rtTimeCdromDevice[];

int MEDIUS_TIMEP_SECTION(rt_time_platform_get_time_stamp) rt_time_platform_get_time_stamp(RT_TIME_STAMP *pTimeStamp)
{
    if (!pTimeStamp) return RT_INVALID_PARAM;
    if (rt_time_platform_update_base()) return RT_TIME_ERROR;
    pTimeStamp->Secs = rtTimePlatformBase.Secs;
    pTimeStamp->USecs = rtTimePlatformBase.USecs;
    return 0;
}

int MEDIUS_TIMEP_SECTION(rt_time_platform_update_date_time) rt_time_platform_update_date_time(void)
{
    sceCdCLOCK clock;

    if (sceDevctl(rtTimeCdromDevice, 0x430C, 0, 0, &clock, 8) < 0) return RT_TIME_ERROR;
    sceScfGetLocalTimefromRTC(&clock);
    rtTimePlatformDate.MSec = 0;
    rtTimePlatformDate.Sec = RT_BCD(clock.second);
    rtTimePlatformDate.Min = RT_BCD(clock.minute);
    rtTimePlatformDate.Hour = RT_BCD(clock.hour);
    rtTimePlatformDate.Day = RT_BCD(clock.day);
    rtTimePlatformDate.Month = RT_BCD(clock.month);
    rtTimePlatformDate.Year = RT_BCD(clock.year);
    if (rt_time_get_msecs(&rtTimePlatformDate.MSecsWhenAquired)) return RT_TIME_ERROR;
    return 0;
}

int MEDIUS_TIMEP_SECTION(rt_time_platform_get_gmtime) rt_time_platform_get_gmtime(RT_TIME_DATE *gmTime)
{
    return rt_time_platform_get_date_time(gmTime);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/ps2/rt_time_platform", rt_time_platform_get_date_time);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/ps2/rt_time_platform", func_01EABA68);

int MEDIUS_TIMEP_SECTION(rt_time_platform_fast_elapsed_msecs) rt_time_platform_fast_elapsed_msecs(RT_TIME_STAMP *pStartTimeStamp, RT_TIME_VAL *pMSecs)
{
    return rt_time_elapsed_msecs(pStartTimeStamp, pMSecs);
}

int MEDIUS_TIMEP_SECTION(rt_time_platform_init) rt_time_platform_init(void)
{
    if (!rtTimePlatformInitialized) {
        rtTimePlatformBase.Secs = 0;
        rtTimePlatformBase.Ticks = 0;
        rtTimePlatformBase.USecs = 0;
        rtTimePlatformBase.LastCount = rt_time_platform_timer_getcount();
        rtTimePlatformInitialized = 1;
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/ps2/rt_time_platform", rt_time_platform_timer_getcount);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/ps2/rt_time_platform", rt_time_platform_update_base);
