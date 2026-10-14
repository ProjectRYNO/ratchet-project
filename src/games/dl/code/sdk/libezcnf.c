#include "common.h"
#include "eznet_rpc.h"

#define SDK_SECTION(name) __attribute__((section(".sdk_libezcnf_" #name)))

// Preserve the original unused instruction fragment in its retail slot.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .sdk_libezcnf_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

int SDK_SECTION(ezNetCnfInit) ezNetCnfInit(void)
{
    int id;
    sdkCnfModuleId = id = sceSifSearchModuleByName(sdkCnfModuleName);
    if(id < 0)
    {
        scePrintf(sdkCnfLog,sdkCnfInitName);
        scePrintf(sdkCnfModuleMissing,sdkCnfModuleName);
        sdkCnfRunning=0;
    }
    else
    {
        for(;;)
        {
            if(sceSifBindRpc(sdkCnfClient,0x75499128,0)<0)
            {
                scePrintf(sdkCnfLog,sdkCnfInitName);
                scePrintf(sdkCnfBindFailed);
            }
            if(*(int*)(sdkCnfClient+36))break;
            DelayThread(10000);
        }
        sdkCnfRunning=1;
    }
    return id>0?0:id;
}

int SDK_SECTION(ezNetCnfExit) ezNetCnfExit(void)
{
    /* Retail leaves result unset when the module is not running. */
    int result;
    if(sdkCnfRunning)
    {
        if(sceSifStopModule(sdkCnfModuleId,0,0,&result)<0)goto end;
        if((result=sceSifUnloadModule(sdkCnfModuleId))<0)goto end;
        sdkCnfRunning=0;
        result=0;
    }
end:
    return result;
}

int SDK_SECTION(ezNetCnfGetCombinationList) ezNetCnfGetCombinationList(const char *path,int type,void *out)
{
    char *buf=sdkCnfBuffer;
    if(!sdkCnfRunning)
    {
        scePrintf(sdkCnfLog,sdkCnfListName);
        scePrintf(sdkCnfNotRunning);
        return -1;
    }
    if((unsigned int)out&63)
    {
        scePrintf(sdkCnfLog,sdkCnfListName);
        scePrintf(sdkCnfAlignError,out,64);
        return -22;
    }
    InvalidDCache(out,(char*)out+0x7ff);
    *(void**)buf=out;
    *(int*)(buf+4)=type;
    strncpy(buf+16,path,255);
    sceSifCallRpc(sdkCnfClient,1,0,buf,384,buf,4,0,0);
    scePrintf(sdkCnfLog,sdkCnfListName);
    scePrintf(sdkCnfResult,*(int*)buf);
    return *(int*)buf;
}

void *SDK_SECTION(ezNetCnfGetCombination) ezNetCnfGetCombination(int *list,int index)
{
    if(!list||!*list)
    {
        scePrintf(sdkCnfLog,sdkCnfCombinationName);
        scePrintf(sdkCnfEmpty);
        return 0;
    }
    if(index<=0||index>*list)
    {
        scePrintf(sdkCnfLog,sdkCnfCombinationName);
        scePrintf(sdkCnfBadIndex,index);
        return 0;
    }
    return (char*)list+index*200-152;
}

int SDK_SECTION(ezNetCnfGetProperties) ezNetCnfGetProperties(const char *path,const char *name,void *out)
{
    char *buf=sdkCnfBuffer;
    if(!sdkCnfRunning)
    {
        scePrintf(sdkCnfLog,sdkCnfPropertiesName);
        scePrintf(sdkCnfNotRunning);
        return -1;
    }
    if((unsigned int)out&63)
    {
        scePrintf(sdkCnfLog,sdkCnfPropertiesName);
        scePrintf(sdkCnfAlignError,out,64);
        return -22;
    }
    InvalidDCache(out,(char*)out+0x133f);
    *(void**)buf=out;
    strncpy(buf+16,path,255);
    strncpy(buf+272,name,111);
    sceSifCallRpc(sdkCnfClient,2,0,buf,384,buf,4,0,0);
    scePrintf(sdkCnfLog,sdkCnfPropertiesName);
    scePrintf(sdkCnfResult,*(int*)buf);
    return *(int*)buf;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/libezcnf", func_01E9A170);
