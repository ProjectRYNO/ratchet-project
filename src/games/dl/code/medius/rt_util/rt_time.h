#ifndef RT_TIME_H
#define RT_TIME_H

typedef unsigned int RT_TIME_VAL;

// Prototype dltypes.txt layout; rt_timebase_restart clears 8 bytes of its query timer.
typedef struct { // 0x08
    /* 0x00 */ unsigned int Secs;
    /* 0x04 */ unsigned int USecs;
} RT_TIME_STAMP;

#ifdef __cplusplus
extern "C" {
#endif

int rt_time_get_local(RT_TIME_VAL *time);
int rt_time_start(RT_TIME_STAMP *timer);
int rt_time_platform_fast_elapsed_msecs(RT_TIME_STAMP *timer, RT_TIME_VAL *elapsed);

#ifdef __cplusplus
}
#endif

#endif
