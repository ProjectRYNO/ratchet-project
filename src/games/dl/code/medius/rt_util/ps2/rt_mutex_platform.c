#include "common.h"
#include <kernel.h>
#include "../rt_mutex.h"

#define MEDIUS_MUTEXP_SECTION(name) __attribute__((section(".medius_mutexp_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_mutexp_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#define RT_INVALID_PARAM 2

int MEDIUS_MUTEXP_SECTION(rt_mutex_platform_create) rt_mutex_platform_create(RT_MUTEX_DATA *pMutexData)
{
    ee_sema_t sema;
    int id;

    if (!pMutexData) return RT_INVALID_PARAM;
    pMutexData->pPlatformData = 0;
    sema.max_count = 1;
    sema.init_count = 1;
    id = CreateSema(&sema);
    if (id == -1) return RT_MUTEX_ERROR;
    pMutexData->PlatformVal = id;
    return 0;
}

int MEDIUS_MUTEXP_SECTION(rt_mutex_platform_destroy) rt_mutex_platform_destroy(RT_MUTEX_DATA *pMutexData)
{
    if (!pMutexData) return RT_INVALID_PARAM;
    if (DeleteSema(pMutexData->PlatformVal) == -1) return RT_MUTEX_ERROR;
    return 0;
}

int MEDIUS_MUTEXP_SECTION(rt_mutex_platform_lock) rt_mutex_platform_lock(RT_MUTEX_DATA *pMutexData)
{
    if (!pMutexData) return RT_INVALID_PARAM;
    if (WaitSema(pMutexData->PlatformVal) == -1) return RT_MUTEX_ERROR;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/ps2/rt_mutex_platform", func_01EAA058);

int MEDIUS_MUTEXP_SECTION(rt_mutex_platform_unlock) rt_mutex_platform_unlock(RT_MUTEX_DATA *pMutexData)
{
    if (!pMutexData) return RT_INVALID_PARAM;
    if (SignalSema(pMutexData->PlatformVal) == -1) return RT_MUTEX_ERROR;
    return 0;
}

int MEDIUS_MUTEXP_SECTION(rt_mutex_platform_get_thread_id) rt_mutex_platform_get_thread_id(int *pThreadID)
{
    if (!pThreadID) return RT_INVALID_PARAM;
    *pThreadID = GetThreadId();
    return 0;
}
