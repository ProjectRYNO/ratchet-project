#ifndef RT_TIME_H
#define RT_TIME_H

typedef unsigned int RT_TIME_VAL;

// Prototype dltypes.txt layout; rt_timebase_restart clears 8 bytes of its query timer.
typedef struct { // 0x08
    /* 0x00 */ unsigned int Secs;
    /* 0x04 */ unsigned int USecs;
} RT_TIME_STAMP;

#define RT_TIME_ERROR 1600
#define RT_TIME_OVERFLOW 1601

// Names and layout from the retail ELF debug information.
typedef struct RT_TIME_DATE { // 0x24
    /* 0x00 */ unsigned int MSec;
    /* 0x04 */ unsigned int Sec;
    /* 0x08 */ unsigned int Min;
    /* 0x0C */ unsigned int Hour;
    /* 0x10 */ unsigned int Day;
    /* 0x14 */ unsigned int Month;
    /* 0x18 */ unsigned int Year;
    /* 0x1C */ unsigned int WeekDay;
    /* 0x20 */ RT_TIME_VAL MSecsWhenAquired;
} RT_TIME_DATE;

// PS2 time base, counted in EE COP0 Count cycles (294,912,000 per second).
#define RT_TIME_PLATFORM_TICKS_PER_SEC 0x11940000

typedef struct { // 0x10
    /* 0x00 */ unsigned int Secs;
    /* 0x04 */ unsigned int Ticks;
    /* 0x08 */ unsigned int USecs;
    /* 0x0C */ unsigned int LastCount;
} RT_TIME_PLATFORM_BASE;

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char rtTimeInitialized;
extern RT_TIME_STAMP rtTimeBaseStamp;
extern unsigned char rtTimePlatformInitialized;
extern RT_TIME_PLATFORM_BASE rtTimePlatformBase;
extern RT_TIME_DATE rtTimePlatformDate;

int rt_time_get_local(RT_TIME_VAL *pMSecs);
int rt_time_get_msecs(RT_TIME_VAL *pMSecs);
int rt_time_start(RT_TIME_STAMP *pStartTimeStamp);
int rt_time_get_time_stamp(RT_TIME_STAMP *pTimeStamp);
int rt_time_elapsed(RT_TIME_STAMP *pStartTimeStamp, RT_TIME_VAL *pMSecs);
int rt_time_elapsed_msecs(RT_TIME_STAMP *pStartTimeStamp, RT_TIME_VAL *pMSecs);
int rt_time_elapsed_usecs(RT_TIME_STAMP *pStartTimeStamp, RT_TIME_VAL *pUSecs);
int rt_time_delay(RT_TIME_VAL MSecs);
int rt_time_initialize(void);
int rt_time_calc_diff(RT_TIME_STAMP *pStartTimeStamp, RT_TIME_STAMP *pEndTimeStamp, RT_TIME_STAMP *pDiffTimeStamp);
int rt_time_timestamp_to_msecs(RT_TIME_STAMP *pTimeStamp, RT_TIME_VAL *pMSecs);
int rt_time_timestamp_to_usecs(RT_TIME_STAMP *pTimeStamp, RT_TIME_VAL *pUSecs);
int rt_time_get_base_diff(RT_TIME_STAMP *pDiffTimeStamp);
int rt_time_elapsed_timestamp(RT_TIME_STAMP *pStartTimeStamp, RT_TIME_STAMP *pElapsedTimeStamp);
int rt_time_get_gmtime(RT_TIME_DATE *gmTime);
int rt_time_platform_get_time_stamp(RT_TIME_STAMP *pTimeStamp);
int rt_time_platform_get_gmtime(RT_TIME_DATE *gmTime);
int rt_time_platform_get_date_time(RT_TIME_DATE *DateTime);
int rt_time_platform_update_date_time(void);
int rt_time_platform_init(void);
unsigned int rt_time_platform_timer_getcount(void);
int rt_time_platform_update_base(void);
int rt_time_platform_fast_elapsed_msecs(RT_TIME_STAMP *timer, RT_TIME_VAL *elapsed);

#ifdef __cplusplus
}
#endif

#endif
