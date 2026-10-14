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

int MEDIUS_MUTEX_SECTION(rt_mutex_create) rt_mutex_create(RT_MUTEX *mutex)
{
    int result;

    if (!mutex) return RT_INVALID_PARAM;
    mutex->created = 0;
    mutex->lockCount = 0;
    mutex->ownerThread = 0;
    result = rt_mutex_platform_create(mutex);
    if (result) return result;
    mutex->created = 1;
    return result;
}

int MEDIUS_MUTEX_SECTION(rt_mutex_destroy) rt_mutex_destroy(RT_MUTEX *mutex)
{
    int result;

    if (!mutex) return RT_INVALID_PARAM;
    if (mutex->created != 1) return RT_INVALID_PARAM;
    result = rt_mutex_platform_destroy(mutex);
    if (!result) mutex->created = 0;
    return result;
}

int MEDIUS_MUTEX_SECTION(rt_mutex_lock) rt_mutex_lock(RT_MUTEX *mutex, int *count)
{
    int result;
    int thread;

    if (!mutex) return RT_INVALID_PARAM;
    if (mutex->created != 1) return RT_INVALID_PARAM;
    result = rt_mutex_platform_get_thread_id(&thread);
    if (result) return result;
    if (mutex->lockCount && thread == mutex->ownerThread) {
        mutex->lockCount++;
    } else {
        result = rt_mutex_platform_lock(mutex);
        if (result) return result;
        result = rt_mutex_platform_get_thread_id(&mutex->ownerThread);
        if (result) return result;
        mutex->lockCount++;
    }
    if (count) *count = mutex->lockCount;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_mutex", func_01EA9ED0);

int MEDIUS_MUTEX_SECTION(rt_mutex_unlock) rt_mutex_unlock(RT_MUTEX *mutex, int *count)
{
    int result;
    int thread;

    if (!mutex) return RT_INVALID_PARAM;
    if (mutex->created != 1) return RT_INVALID_PARAM;
    result = rt_mutex_platform_get_thread_id(&thread);
    if (result) return result;
    if (thread != mutex->ownerThread) return RT_MUTEX_NOT_OWNED;
    if (!mutex->lockCount) return RT_MUTEX_NOT_LOCKED;
    mutex->lockCount--;
    if (count) *count = mutex->lockCount;
    if (!mutex->lockCount) {
        mutex->ownerThread = 0;
        result = rt_mutex_platform_unlock(mutex);
        if (result) return result;
    }
    return 0;
}
