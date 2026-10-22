#include "common.h"
#include "rt_mutex.h"

#define MEDIUS_MUTEX_SECTION(name) __attribute__((section(".medius_mutex_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)     __asm__(".section .medius_mutex_" #NAME ",\"ax\",@progbits
"             ".set noat
.set noreorder
"             ".include \"" FOLDER "/" #NAME ".s\"
"             ".set reorder
.set at
.text
")
#endif

#define RT_INVALID_PARAM 2

int MEDIUS_MUTEX_SECTION(rt_mutex_create) rt_mutex_create(RT_MUTEX_DATA *mutex)
{
    int result;

    if (!mutex) return RT_INVALID_PARAM;
    mutex->bInitialized = 0;
    mutex->nLockCount = 0;
    mutex->ThreadID = 0;
    result = rt_mutex_platform_create(mutex);
    if (result) return result;
    mutex->bInitialized = 1;
    return result;
}

int MEDIUS_MUTEX_SECTION(rt_mutex_destroy) rt_mutex_destroy(RT_MUTEX_DATA *mutex)
{
    int result;

    if (!mutex) return RT_INVALID_PARAM;
    if (mutex->bInitialized != 1) return RT_INVALID_PARAM;
    result = rt_mutex_platform_destroy(mutex);
    if (!result) mutex->bInitialized = 0;
    return result;
}

int MEDIUS_MUTEX_SECTION(rt_mutex_lock) rt_mutex_lock(RT_MUTEX_DATA *mutex, int *count)
{
    int result;
    int thread;

    if (!mutex) return RT_INVALID_PARAM;
    if (mutex->bInitialized != 1) return RT_INVALID_PARAM;
    result = rt_mutex_platform_get_thread_id(&thread);
    if (result) return result;
    if (mutex->nLockCount && thread == mutex->ThreadID) {
        mutex->nLockCount++;
    } else {
        result = rt_mutex_platform_lock(mutex);
        if (result) return result;
        result = rt_mutex_platform_get_thread_id(&mutex->ThreadID);
        if (result) return result;
        mutex->nLockCount++;
    }
    if (count) *count = mutex->nLockCount;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_mutex", func_01EA9ED0);

int MEDIUS_MUTEX_SECTION(rt_mutex_unlock) rt_mutex_unlock(RT_MUTEX_DATA *mutex, int *count)
{
    int result;
    int thread;

    if (!mutex) return RT_INVALID_PARAM;
    if (mutex->bInitialized != 1) return RT_INVALID_PARAM;
    result = rt_mutex_platform_get_thread_id(&thread);
    if (result) return result;
    if (thread != mutex->ThreadID) return RT_MUTEX_NOT_OWNED;
    if (!mutex->nLockCount) return RT_MUTEX_NOT_LOCKED;
    mutex->nLockCount--;
    if (count) *count = mutex->nLockCount;
    if (!mutex->nLockCount) {
        mutex->ThreadID = 0;
        result = rt_mutex_platform_unlock(mutex);
        if (result) return result;
    }
    return 0;
}
