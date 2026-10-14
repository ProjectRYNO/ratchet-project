#include "common.h"
#include "eznet_rpc.h"

#define SDK_SECTION(name) __attribute__((section(".sdk_libezctl_" #name)))

// Preserve the original unused instruction fragment in its retail slot.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .sdk_libezctl_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

int SDK_SECTION(ezNetCtlInit) ezNetCtlInit(void)
{
    int id;
    sdkCtlModuleId = id = sceSifSearchModuleByName(sdkCtlModuleName);
    if(id < 0)
    {
        scePrintf(sdkCtlLog,sdkCtlInitName);
        scePrintf(sdkCtlModuleMissing,sdkCtlModuleName);
        sdkCtlRunning=0;
    }
    else
    {
        for(;;)
        {
            if(sceSifBindRpc(sdkCtlClient,0x75488909,0)<0)
            {
                scePrintf(sdkCtlLog,sdkCtlInitName);
                scePrintf(sdkCtlBindFailed);
            }
            if(*(int*)(sdkCtlClient+36))break;
            DelayThread(10000);
        }
        sdkCtlRunning=1;
    }
    return id>0?0:id;
}

int SDK_SECTION(ezNetCtlExit) ezNetCtlExit(int flags)
{
    int result=0;
    if(!(flags&2)&&sdkCtlRunning)
    {
        if(sceSifStopModule(sdkCtlModuleId,0,0,&result)<0)goto end;
        if((result=sceSifUnloadModule(sdkCtlModuleId))<0)goto end;
        sdkCtlRunning=0;
        result=0;
    }
    else result=0;
end:
    return result;
}

int SDK_SECTION(ezNetCtlSetProperties) ezNetCtlSetProperties(void *properties)
{
    char *buf=sdkCtlBuffer;
    int result;
    if(!sdkCtlRunning)
    {
        scePrintf(sdkCtlLog,sdkCtlSetName);
        scePrintf(sdkCtlNotRunning);
        return -1;
    }
    if((unsigned int)properties&63)
    {
        scePrintf(sdkCtlLog,sdkCtlSetName);
        scePrintf(sdkCtlAlignError,properties,64);
        return -22;
    }
    SyncDCache(properties,(char*)properties+0x133f);
    *(void**)buf=properties;
    sceSifCallRpc(sdkCtlClient,1,0,buf,4,buf,4,0,0);
    result=*(int*)buf;
    scePrintf(sdkCtlLog,sdkCtlSetName);
    scePrintf(sdkCtlResult,result);
    do
    {
        result=ezNetCtlWaitEventTO(2000);
    }
    while(result>1);
    return result;
}

int SDK_SECTION(ezNetCtlUpInterface) ezNetCtlUpInterface(void)
{
    int *result=(int*)sdkCtlBuffer;
    if(!sdkCtlRunning)
    {
        scePrintf(sdkCtlLog,sdkCtlUpName);
        scePrintf(sdkCtlNotRunning);
        return -1;
    }
    sceSifCallRpc(sdkCtlClient,5,0,0,0,result,4,0,0);
    return *result;
}

int SDK_SECTION(ezNetCtlDownInterface) ezNetCtlDownInterface(void)
{
    int *result=(int*)sdkCtlBuffer;
    if(!sdkCtlRunning)
    {
        scePrintf(sdkCtlLog,sdkCtlDownName);
        scePrintf(sdkCtlNotRunning);
        return -1;
    }
    sceSifCallRpc(sdkCtlClient,6,0,0,0,result,4,0,0);
    return *result;
}

int SDK_SECTION(ezNetCtlGetStatus) ezNetCtlGetStatus(ezNetCtlStatus *out,char *message,int size)
{
    char *buf=sdkCtlBuffer;
    if(!sdkCtlRunning)
    {
        scePrintf(sdkCtlLog,sdkCtlStatusName);
        scePrintf(sdkCtlNotRunning);
        return -1;
    }
    sceSifCallRpc(sdkCtlClient,3,0,0,0,buf,384,0,0);
    *out=*(ezNetCtlStatus*)(buf+272);
    ezNetCtlRecreateIfstat(buf+16,out,&sdkCtlIfInfo);
    ezNetCtlLocalizeMessage(message,size,out,&sdkCtlIfInfo);
    return *(int*)buf;
}

int SDK_SECTION(ezNetCtlWaitEventTO) ezNetCtlWaitEventTO(int timeout)
{
    int *buf=(int*)sdkCtlBuffer;
    if(!sdkCtlRunning)
    {
        scePrintf(sdkCtlLog,sdkCtlWaitName);
        scePrintf(sdkCtlNotRunning);
        return -1;
    }
    *buf=timeout;
    sceSifCallRpc(sdkCtlClient,4,0,buf,4,buf,4,0,0);
    if(*buf!=-1)
    {
        scePrintf(sdkCtlLog,sdkCtlWaitName);
        scePrintf(sdkCtlResult,*buf);
    }
    return *buf;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/libezctl", func_01E9A730);
