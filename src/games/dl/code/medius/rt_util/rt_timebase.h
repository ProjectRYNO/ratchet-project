#ifndef RT_TIMEBASE_H
#define RT_TIMEBASE_H

#include "rt_time.h"

#define RT_TIMEBASE_HISTORY 100

// Round-trip delay history; retail rt_timebase_* index 100 words, then count (0x190) and index (0x194).
typedef struct { // 0x198
    /* 0x000 */ RT_TIME_VAL delay[RT_TIMEBASE_HISTORY];
    /* 0x190 */ unsigned int count;
    /* 0x194 */ int index;
} RT_TIMEBASE_DELAYS;

#ifdef __cplusplus
extern "C" {
#endif

// Static storage in the prototype (no dlglobals entry); names describe retail use.
extern RT_TIME_VAL rtTimebaseLastLocalTime;
extern RT_TIME_VAL rtTimebaseGlobalTime;
extern int rtTimebaseStarted;
extern RT_TIME_VAL rtTimebaseQueryInterval;
extern RT_TIMEBASE_DELAYS rtTimebaseDelays;
extern RT_TIME_STAMP rtTimebaseQueryTimer;

int rt_timebase_get_globaltime(RT_TIME_VAL *time);
int rt_timebase_get_localtime(RT_TIME_VAL *time);
int rt_timebase_restart(void);
void rt_timebase_reset_globaltime(RT_TIME_VAL time);
int rt_timebase_update_globaltime(RT_TIME_VAL roundTrip, RT_TIME_VAL serverTime);
int rt_timebase_get_percentiledelay(RT_TIME_VAL *delay);
void rt_timebase_is_query_ready(int *ready);
int rt_timebase_start(void);

#ifdef __cplusplus
}
#endif

#endif
