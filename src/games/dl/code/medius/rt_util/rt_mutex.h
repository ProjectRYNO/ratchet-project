#ifndef RT_MUTEX_H
#define RT_MUTEX_H

#define RT_MUTEX_ERROR 900
#define RT_MUTEX_NOT_OWNED 901
#define RT_MUTEX_NOT_LOCKED 902

// Names and layout from the retail ELF debug information.
typedef struct { // 0x14
    /* 0x00 */ unsigned char bInitialized;
    /* 0x04 */ int nLockCount;
    /* 0x08 */ int ThreadID;
    /* 0x0C */ int PlatformVal;
    /* 0x10 */ void *pPlatformData;
} RT_MUTEX_DATA;

#ifdef __cplusplus
extern "C" {
#endif

int rt_mutex_create(RT_MUTEX_DATA *mutex);
int rt_mutex_destroy(RT_MUTEX_DATA *mutex);
int rt_mutex_lock(RT_MUTEX_DATA *mutex, int *count);
int rt_mutex_unlock(RT_MUTEX_DATA *mutex, int *count);
int rt_mutex_platform_create(RT_MUTEX_DATA *pMutexData);
int rt_mutex_platform_destroy(RT_MUTEX_DATA *pMutexData);
int rt_mutex_platform_lock(RT_MUTEX_DATA *pMutexData);
int rt_mutex_platform_unlock(RT_MUTEX_DATA *pMutexData);
int rt_mutex_platform_get_thread_id(int *pThreadID);

#ifdef __cplusplus
}
#endif

#endif
