#ifndef RT_MUTEX_H
#define RT_MUTEX_H

#define RT_MUTEX_NOT_OWNED 901
#define RT_MUTEX_NOT_LOCKED 902

// Offsets from retail rt_mutex_* and rt_mutex_platform_* accesses; the prototype names no type.
typedef struct { // 0x10
    /* 0x00 */ unsigned char created;
    /* 0x04 */ int lockCount;
    /* 0x08 */ int ownerThread;
    /* 0x0C */ int semaphore;
} RT_MUTEX;

#ifdef __cplusplus
extern "C" {
#endif

int rt_mutex_create(RT_MUTEX *mutex);
int rt_mutex_destroy(RT_MUTEX *mutex);
int rt_mutex_lock(RT_MUTEX *mutex, int *count);
int rt_mutex_unlock(RT_MUTEX *mutex, int *count);
int rt_mutex_platform_create(RT_MUTEX *mutex);
int rt_mutex_platform_destroy(RT_MUTEX *mutex);
int rt_mutex_platform_lock(RT_MUTEX *mutex);
int rt_mutex_platform_unlock(RT_MUTEX *mutex);
int rt_mutex_platform_get_thread_id(int *thread);

#ifdef __cplusplus
}
#endif

#endif
