#ifndef SDK_EZNET_RPC_H
#define SDK_EZNET_RPC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i18n.h"

extern void scePrintf(const char *, ...);
extern int sceSifSearchModuleByName(const char *);
extern int sceSifBindRpc(void *, unsigned int, int);
extern int sceSifStopModule(int, int, void *, int *);
extern int sceSifUnloadModule(int);
extern int DelayThread(unsigned int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern void InvalidDCache(void *, void *);
extern void SyncDCache(void *, void *);
extern char *strncpy(char *, const char *, unsigned int);
extern int sdkCnfRunning;
extern int sdkCnfModuleId;
extern int sdkCtlRunning;
extern int sdkCtlModuleId;
extern char sdkCnfModuleName[];
extern char sdkCnfLog[];
extern char sdkCnfInitName[];
extern char sdkCnfModuleMissing[];
extern char sdkCnfBindFailed[];
extern char sdkCnfNotRunning[];
extern char sdkCnfListName[];
extern char sdkCnfAlignError[];
extern char sdkCnfResult[];
extern char sdkCnfCombinationName[];
extern char sdkCnfEmpty[];
extern char sdkCnfBadIndex[];
extern char sdkCnfPropertiesName[];
extern char sdkCtlModuleName[];
extern char sdkCtlLog[];
extern char sdkCtlInitName[];
extern char sdkCtlModuleMissing[];
extern char sdkCtlBindFailed[];
extern char sdkCtlNotRunning[];
extern char sdkCtlSetName[];
extern char sdkCtlAlignError[];
extern char sdkCtlResult[];
extern char sdkCtlUpName[];
extern char sdkCtlDownName[];
extern char sdkCtlStatusName[];
extern char sdkCtlWaitName[];
extern char sdkCnfClient[];
extern char sdkCtlClient[];
extern char sdkCnfBuffer[];
extern char sdkCtlBuffer[];
extern EzNetCtlInfo sdkCtlIfInfo;
extern void ezNetCtlRecreateIfstat(const char *, ezNetCtlStatus *, EzNetCtlInfo *);

int ezNetCtlWaitEventTO(int);


#ifdef __cplusplus
}
#endif
#endif
