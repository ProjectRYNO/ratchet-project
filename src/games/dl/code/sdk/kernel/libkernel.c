#include "common.h"
#include "libkernel.h"

/* Recovered directly from the retail boot instructions (libkernl 3000); no vendor source. */
#define KERNEL_SECTION(name) __attribute__((section(".kernel_" #name)))

/* Functions still in assembly (including the kernel syscall stubs, which were written in
   assembly), and original padding words, stay in their own slots. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
	__asm__(".section .kernel_" #NAME ",\"ax\",@progbits\n" \
			".set noat\n.set noreorder\n" \
			".include \"" FOLDER "/" #NAME ".s\"\n" \
			".set reorder\n.set at\n.text\n")
#endif

extern int sdkSifSreg[32];
extern int sdkSifRpcInitialized;
extern sifCmdData_t sdkSifCmd;
extern int sdkSifCmdHandlerId;
extern int sdkSifCmdInitialized;
extern int sdkFsInitialized;
extern int sdkFsResetFlags[1];
extern int sdkFsSema;
extern int sdkFsIobSema;
extern int sdkFsIobSema2;
extern fsIob_t sdkFsIob[32];
extern const char sdkFsSemaName[];
extern const char sdkFsIobSemaName[];
extern const char sdkFsIobSemaName2[];
extern int sdkIopHeapState;
extern sifRpcClient_t sdkIopHeapClient;
extern int sdkIopHeapSend[4];
extern int sdkIopHeapReceive[4];
extern int sdkLoadFileState;
extern int sdkLoadFileFlags[1];
extern int sdkLoadFileClient[10];
extern sifSearchBuffer_t sdkLoadFileBuffer;
extern sifNotifyHandler_t *sdkRebootNotifyHandlers;
extern unsigned int sdkRebootNotifyCount;
extern sifNotifyHandler_t sdkRebootNotifySystem[32];
extern char sdkDeci2Buffer[];
extern ttyQueue_t sdkTtyQueue;
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern void sceSifExitCmd(void);
extern unsigned int sceSifGetReg(int);
extern void sceResetttyinit(void);
extern void sceSifExecNotifyHandler(int, int);
extern int _sceSifSendCmd(int, int, void *, int, void *, void *, int);
extern int sceSifFreeSysMemory(void *);
extern int _sceSifLoadModuleBuffer(void *, int, const char *, int *);
extern int _lf_bind(void);
extern int _lf_version(void);
extern int Deci2Call(int, void *);
extern int CreateSema(kernelSemaParam_t *);
extern int WaitSema(int);
extern int SignalSema(int);
extern int DIntr(void);
extern int EIntr(void);
extern int iAllocTimerCounter(void);
extern int iFreeTimerCounter(int);
extern int iStartTimerCounter(int);
extern void *memset(void *, int, unsigned int);
extern char *strncpy(char *, const char *, unsigned int);
extern int sdkTtyInitialized;
extern timerData_t sdkTimer;
extern timerAlarm_t *sdkAlarmFree;
extern timerAlarm_t sdkAlarms[64];
extern int sceTtyInit(void);
extern int sceTtyWrite(const char *, int);
extern int sceTtyRead(void *, int);
extern int *__errno(void);
extern int iSetTimerHandler(int, unsigned long, void *, void *);
extern unsigned long iGetTimerSystemTime(void);
extern void SetNextComp(unsigned long);
timerCounter_t *UnlinkAlarm(timerCounter_t *counter);
extern int DelayThread(int);
extern int isceSifSendCmd(int, void *, int, void *, void *, int);
extern sifRpcPool_t sdkRpcPool;
extern const char sdkRpcBindSemaName[];
extern int sceSifSendCmd(int, void *, int, void *, void *, int);
extern int DeleteSema(int);
extern ttyData_t sdkTty;
extern const char sdkRpcDataSemaName[];
extern int sdkDeci2PutPos;
extern char sdkDeci2PutBuffer[0x80];
extern char **sdkExecArgv;
extern int InitTLB(void);
extern void _Exit(int);
extern void SetT2(volatile int *, int);
extern int kputchar(int);
extern char *SetArg(const char *, int, char **);
extern void _LoadExecPS2(const char *, int, char **);
extern void supplement_crt0(void);
extern void InitSystemCallTableAddress(void);
extern void InitAlarm(void);
extern int InitTimer(int);
extern int StartTimerSystemTime(void);
extern int InitThread(void);
extern void InitExecPS2(void);
extern void InitTLBFunctions(void);
extern void sceSifInitRebootNotify(void);
extern void SetT2_COMP(int);
extern void SetT2_MODE(int);
extern void TerminateLibrary(void);
extern void _sceFsSigSema(void);
extern char sdkTtySendHeader[];
extern char sdkTtyRecvBuffer[];
extern void FlushCache(int);
extern void sceTtyHandler(int, unsigned int, ttyData_t *);
extern int DisableDmac(int);
extern int RemoveDmacHandler(int, int);
extern int GetMemorySize(void);
extern int InitTLB32MB(void);
extern int _InitTLB(void);
extern void serialPutchar(int);
extern void deci2Putchar(int);
extern void InsertAlarm(timerCounter_t *);
extern int FreeTimerCounter(int);
extern void kprintf(const char *, ...);
extern int _sceSnprintf(kernelPrintfChar, void *, unsigned int, const char *, va_list);
extern int sdkLibcSema;
extern int sdkLibcEhSema;
extern const char sdkLibcSemaName[];
extern const char sdkLibcEhSemaName[];
extern kernelPatch_t sdkExecPatchTable[3];
extern char sdkExecPatchCode[];
extern kernelPatch_t sdkTlbPatchTable[8];
extern char sdkTlbPatchCode[];
extern kernelPatch_t sdkAlarmPatchTable[8];
extern char sdkAlarmPatchCode[];
extern char sdkAlarmPatchData[];
extern int sdkThreadSema;
extern int sdkThreadId;
extern threadQueue_t sdkThreadQueue;
extern char sdkThreadStack[0x400];
extern const char sdkThreadName[];
extern const char sdkThreadErrorMsg[];
extern char _gp[];
extern void GetOsdConfigParam(osdConfig_t *);
extern void SetOsdConfigParam(osdConfig_t *);
extern void setup(int, void *);
extern void Copy(void *, void *, int);
extern void *GetEntryAddress(int);
extern void setup___dupe3(int, void *);
extern void Copy___dupe2(void *, void *, int);
extern void *GetEntryAddress___dupe2(int);
extern void setup___dupe5(int, void *);
extern void Copy___dupe4(void *, void *, int);
extern void *GetEntryAddress___dupe3(int);
extern int CreateThread(kernelThreadParam_t *);
extern int StartThread(int, void *);
extern int GetThreadId(void);
extern int ChangeThreadPriority(int, int);
extern int WakeupThread(int);
extern int RotateThreadReadyQueue(int);
extern int SuspendThread(int);
extern int PatchIsNeeded(void);
void topThread(threadQueue_t *queue);
extern timerCounter_t sdkTimerCounters[128];
extern int AllocTimerCounter(void);
extern int StartTimerCounter(int);
extern int SetTimerHandler(int, unsigned long, void *, void *);
extern int AlarmHandler(int, int, int, timerAlarm_t *);
extern int _InitAlarm(void);
extern int cbTimerHandler(int);
extern int AddIntcHandler2(int, void *, int, void *);
extern int EnableIntc(int);
extern void SetT2_COUNT(int);
extern fsRequest_t sdkFsRequest;
extern int sdkFsClient[10];
extern int sdkFsReceive[4];
extern const char sdkFsOpenSemaName[];
extern const char sdkFsCloseSemaName[];
extern const char sdkFsDevctlSemaName[];
extern kernelVersion_t sdkKernelVersion;
extern kernelVersion_t *sdkFsVersion;
extern kernelVersion_t *sdkLoadFileVersion;
extern int memcmp(const void *, const void *, unsigned int);
extern int _sceFsWaitS(int);
extern int sceFsInit(void);
extern int _fs_version(void);
#define LOAD_BUFFER ((sifLoadModuleBuffer_t *)&sdkLoadFileBuffer)
extern sifResetPacket_t sdkSifResetPacket;
extern const char sdkSifRebootPrefix[];
extern const char sdkSifRebootTooLongMsg[];
extern unsigned int sceSifSetDma(sifDmaTransfer_t *, int);
extern void sceSifStopDma(void);
extern int sceSifSetReg(unsigned int, unsigned int);
extern void *memcpy(void *, const void *, unsigned int);
int sceSifResetIop(const char *, int);
extern const char sdkTtyMsgPacketSize[];
extern const char sdkTtyMsgRecvError[];
extern const char sdkTtyMsgSendError[];
extern const char sdkTtyMsgWlenError[];
extern kernelPatch_t sdkSyscallPatchTable[2];
extern unsigned int sdkSyscallTable;
extern kernelPatch_t sdkArgPatch;
extern void setup___dupe2(int, void *);
extern unsigned int FindAddress(unsigned int, unsigned int, unsigned int);
extern void setup___dupe4(int, void *);
extern int Copy___dupe3(void *, void *, int);
extern unsigned int strlen(const char *);
extern int ftoi(unsigned long);
char *_sceRpcGetFPacket(sifRpcData_t *rpc);
void _sceFsSemInit(void);
void _sceFsIobSemaMK(void);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetGsCrt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001267B0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _Exit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001267D0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _LoadExecPS2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001267F0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126800);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126810);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126820);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126830);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126840);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126850);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126860);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126870);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", AddIntcHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", AddIntcHandler2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", RemoveIntcHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", AddDmacHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", AddDmacHandler2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", RemoveDmacHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _EnableIntc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _DisableIntc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _EnableDmac);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _DisableDmac);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126920);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126930);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126940);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126950);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126960);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126970);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126980);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126990);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", CreateThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", DeleteThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _StartThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001269D0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001269E0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", TerminateThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", ChangeThreadPriority);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A40);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", RotateThreadReadyQueue);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A60);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetThreadId);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", ReferThreadStatus);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126AB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SleepThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", WakeupThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _iWakeupThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126AF0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SuspendThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", ResumeThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B40);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B60);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", EndOfHeap);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", CreateSema);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", DeleteSema);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SignalSema);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", iSignalSema);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", WaitSema);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", PollSema);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126C00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", ReferSemaStatus);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126C20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126C30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetOsdConfigParam);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetOsdConfigParam);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126C60);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126C70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126C80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126C90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126CA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126CB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126CC0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126CD0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126CE0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126CF0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126D00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126D10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126D20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126D30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126D40);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126D50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126D60);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126D70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126D80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126D90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126DA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126DB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126DC0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126DD0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126DE0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126DF0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", FlushCache);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E40);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E60);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifStopDma);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126EA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetOsdConfigParam2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GsGetIMR);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126ED0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GsPutIMR);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126EF0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126F00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetVSyncFlag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126F20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126F30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifDmaStat);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126F50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifSetDma);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", isceSifSetDma);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifSetDChain);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", isceSifSetDChain);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifSetReg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifGetReg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126FC0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", Deci2Call);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126FE0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126FF0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetMemorySize);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _InitTLB);

void KERNEL_SECTION(sceResetttyinit) sceResetttyinit(void)
{
	sdkTtyInitialized = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", VSync);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", VSync2);

int KERNEL_SECTION(write) write(int fd, const void *buffer, int size)
{
	if ((unsigned int)(fd - 1) < 2) {
		if (!sdkTtyInitialized) {
			if (!sceTtyInit()) return -1;
			sdkTtyInitialized = 1;
		}
		return sceTtyWrite(buffer, size);
	}
	return -1;
}

int KERNEL_SECTION(read) read(int fd, void *buffer, int size)
{
	if (fd == 0) {
		if (!sdkTtyInitialized) {
			if (!sceTtyInit()) return -1;
			sdkTtyInitialized = 1;
		}
		return sceTtyRead(buffer, size);
	}
	return -1;
}

int KERNEL_SECTION(open) open(const char *name, int flags, int mode)
{
	*__errno() = 5;
	return -1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", close);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", lseek);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sbrk);

int KERNEL_SECTION(fstat) fstat(int fd, kernelStat_t *st)
{
	st->mode = 0x2000;
	st->blocks = 0;
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", getpid);

int KERNEL_SECTION(stat) stat(const char *name, kernelStat_t *st)
{
	*__errno() = 5;
	return -1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceSDC);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SyncDCache);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001274B8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceIDC);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", InvalidDCache);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001275E8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", QueryIntrContext);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", DisableIntc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", EnableIntc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", DisableDmac);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", EnableDmac);

void KERNEL_SECTION(topThread) topThread(threadQueue_t *queue)
{
	int index;
	while (1) {
		WaitSema(sdkThreadSema);
		index = queue->index & 0x1ff;
		queue->index = index + 1;
		switch (queue->requests[index].command) {
		case 0:
			WakeupThread(queue->requests[index].threadId);
			break;
		case 1:
			RotateThreadReadyQueue(queue->requests[index].threadId);
			break;
		case 2:
			SuspendThread(queue->requests[index].threadId);
			break;
		default:
			kprintf(sdkThreadErrorMsg);
			break;
		}
	}
}

int KERNEL_SECTION(InitThread) InitThread(void)
{
	kernelThreadParam_t thread;
	kernelSemaParam_t sema;
	if (sdkThreadId > 0) return -1;
	sema.maxCount = 0xff;
	sema.initCount = 0;
	sema.option = sdkThreadName;
	sdkThreadSema = CreateSema(&sema);
	if (sdkThreadSema < 0) return -1;
	thread.func = topThread;
	thread.stack = sdkThreadStack;
	thread.stackSize = 0x400;
	thread.gpReg = _gp;
	thread.option = sdkThreadName;
	thread.initPriority = 0;
	sdkThreadId = CreateThread(&thread);
	if (sdkThreadId < 0) {
		DeleteSema(sdkThreadSema);
		return -1;
	}
	sdkThreadQueue.index = 0;
	sdkThreadQueue.unk04 = 0;
	StartThread(sdkThreadId, &sdkThreadQueue);
	ChangeThreadPriority(GetThreadId(), 1);
	return sdkThreadId;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", iWakeupThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00127A00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", DelayThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", StartThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _DelayThreadHandler);

int KERNEL_SECTION(sceDeci2Open) sceDeci2Open(unsigned short protocol, void *opt, void *handler)
{
	int param[4];
	param[0] = protocol;
	param[1] = (int)opt;
	param[2] = (int)handler;
	param[3] = (int)sdkDeci2Buffer | 0x20000000;
	return Deci2Call(1, param);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00127CB8);

int KERNEL_SECTION(sceDeci2ReqSend) sceDeci2ReqSend(int socket, char dest)
{
	int param[4];
	param[0] = socket;
	param[1] = dest;
	return Deci2Call(3, param);
}

void KERNEL_SECTION(sceDeci2Poll) sceDeci2Poll(int socket)
{
	int param[4];
	param[0] = socket;
	Deci2Call(4, param);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00127D18);

int KERNEL_SECTION(sceDeci2ExRecv) sceDeci2ExRecv(int socket, void *buffer, unsigned short size)
{
	int param[4];
	param[0] = socket;
	param[1] = (int)buffer;
	param[2] = size;
	return Deci2Call(-5, param);
}

int KERNEL_SECTION(sceDeci2ExSend) sceDeci2ExSend(int socket, void *buffer, unsigned short size)
{
	int param[4];
	param[0] = socket;
	param[1] = (int)buffer;
	param[2] = size;
	return Deci2Call(-6, param);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00127D90);

void KERNEL_SECTION(kputs) kputs(const char *text)
{
	const char *param[4];
	param[0] = text;
	Deci2Call(0x10, param);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00127DC4);

ttyQueue_t *KERNEL_SECTION(QueueInit) QueueInit(int size)
{
	sdkTtyQueue.size = size;
	sdkTtyQueue.count = 0;
	sdkTtyQueue.write = (char *)&sdkTtyQueue + 16;
	sdkTtyQueue.read = (char *)&sdkTtyQueue + 16;
	return &sdkTtyQueue;
}

void KERNEL_SECTION(QueuePeekWriteDone) QueuePeekWriteDone(ttyQueue_t *queue)
{
	queue->count++;
	queue->write++;
	if (queue->write == (char *)queue + (queue->size + 16)) queue->write = (char *)queue + 16;
}

void KERNEL_SECTION(QueuePeekReadDone) QueuePeekReadDone(ttyQueue_t *queue)
{
	queue->count--;
	queue->read++;
	if (queue->read == (char *)queue + (queue->size + 16)) queue->read = (char *)queue + 16;
}

void KERNEL_SECTION(sceTtyHandler) sceTtyHandler(int event, unsigned int param, ttyData_t *tty)
{
	int n, sent;
	char *buffer;
	switch (event) {
	case 1:
	case 2:
		if (param) {
			if (tty->rlen + param > 0x140) kprintf(sdkTtyMsgPacketSize);
			n = sceDeci2ExRecv(tty->socket, tty->recvBuffer + tty->rlen, param);
			if (n < 0) kprintf(sdkTtyMsgRecvError);
			tty->rlen += n;
		} else {
			buffer = tty->recvBuffer;
			for (n = 0xc; n < *(unsigned short *)buffer; n++) {
				*tty->queue->write = tty->recvBuffer[n];
				QueuePeekWriteDone(tty->queue);
			}
			tty->rlen = 0;
		}
		break;
	case 3:
		sent = sceDeci2ExSend(tty->socket, tty->sendHeader, tty->wlen);
		if (sent < 0) {
			kprintf(sdkTtyMsgSendError, sent);
			tty->busy = 0;
		} else {
			tty->sendHeader += sent;
			tty->wlen -= sent;
		}
		break;
	case 4:
		if (tty->wlen) kprintf(sdkTtyMsgWlenError, tty->wlen);
		tty->busy = 0;
		break;
	}
}

int KERNEL_SECTION(sceTtyWrite) sceTtyWrite(const char *buffer, int size)
{
	ttyData_t *tty = &sdkTty;
	int written = 0;
	int len = 0;
	int intr;
	char *header;
	char *p;
	if (tty->busy) return -1;
	intr = DIntr();
	tty->busy = 1;
	header = (char *)((unsigned int)sdkTtySendHeader | 0x20000000);
	tty->sendHeader = header;
	p = header + 0xc;
	while (size-- != 0) {
		if (*buffer == '\n') {
			*p++ = '\r';
			if (++len >= 0x100) break;
		}
		*p = *buffer;
		len++;
		buffer++;
		p++;
		written++;
		if (len >= 0x100) break;
	}
	sdkTty.wlen = len + 0xc;
	*(short *)header = sdkTty.wlen;
	if (sceDeci2ReqSend(sdkTty.socket, header[7]) < 0) {
		sdkTty.busy = 0;
		if (intr) EIntr();
		return -1;
	}
	while (sdkTty.busy) sceDeci2Poll(sdkTty.socket);
	if (intr) EIntr();
	return written;
}

int KERNEL_SECTION(sceTtyRead) sceTtyRead(void *buffer, int size)
{
	int i = 0;
	while (i < size) {
		char *dst = (char *)buffer + i;
		while (!((volatile ttyQueue_t *)sdkTty.queue)->count) {}
		*dst = *sdkTty.queue->read;
		QueuePeekReadDone(sdkTty.queue);
		if (*dst == '\n' || *dst == '\r') return i + 1;
		i++;
	}
	return i;
}

int KERNEL_SECTION(sceTtyInit) sceTtyInit(void)
{
	char *header;
	FlushCache(0);
	sdkTty.socket = sceDeci2Open(0x210, &sdkTty, sceTtyHandler);
	if (sdkTty.socket < 0) return 0;
	sdkTty.busy = 0;
	sdkTty.wlen = 0;
	sdkTty.rlen = 0;
	sdkTty.recvBuffer = (char *)((unsigned int)sdkTtyRecvBuffer | 0x20000000);
	header = (char *)((unsigned int)sdkTtySendHeader | 0x20000000);
	sdkTty.sendHeader = header;
	*(short *)(header + 4) = 0x210;
	header[6] = 0x45;
	header[7] = 0x48;
	*(short *)(header + 2) = 0;
	*(int *)(header + 8) = 0;
	sdkTty.queue = QueueInit(0x100);
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012830C);

int KERNEL_SECTION(kputchar) kputchar(int c)
{
	while (*(volatile unsigned int *)0x1000f130 & 0x8000) {}
	*(volatile char *)0x1000f180 = c;
	return c;
}

void KERNEL_SECTION(deci2Putchar) deci2Putchar(int c)
{
	if (sdkDeci2PutPos >= 0x7e) {
		sdkDeci2PutPos = 0;
		sdkDeci2PutBuffer[0x7f] = 0;
		kputs(sdkDeci2PutBuffer);
	}
	if (c == '\n') {
		int pos = sdkDeci2PutPos;
		sdkDeci2PutPos = 0;
		sdkDeci2PutBuffer[pos] = c;
		sdkDeci2PutBuffer[pos + 1] = 0;
		kputs(sdkDeci2PutBuffer);
	} else {
		sdkDeci2PutBuffer[sdkDeci2PutPos++] = c;
	}
}

void KERNEL_SECTION(serialPutchar) serialPutchar(int c)
{
	if (c == '\n') {
		kputchar('\r');
		kputchar('\n');
		return;
	}
	kputchar(c);
}

int KERNEL_SECTION(ftoi) ftoi(unsigned long value)
{
  int new_var;
  long exp = (value << 1) >> 53;
  int new_var2;
  exp -= 0x433;
  new_var = 0x35;
  if (exp < (-new_var))
  {
	return 0;
  }
  if (exp >= 0xd)
  {
	return 9999;
  }
  new_var2 = 12;
  value = (value << new_var2) >> new_var2;
  value = value | (((unsigned long) 1) << 52);
  if (exp < 0)
  {
	exp = -exp;
	value >>= (int) (exp - 2);
	if ((value & 3) == 3)
	{
	  value = (value >> 2) + 1;
	}
	else
	{
	  value >>= 2;
	}
  }
  else
  {
	value <<= (int) exp;
  }
  return (int) value;
}

int KERNEL_SECTION(printfloat) printfloat(kernelPrintfChar func, void *context, int *size, double value)
{
	int count = 0;
	int exp = 0;
	int frac;
	if (!*size) return 0;
	if (value < 0.0) {
		value = 0.0 - value;
		count = 1;
		func(context, size, '-');
		(*size)--;
	}
	if (value < 0.1) {
		while (value < 0.1) {
			value *= 10.0;
			exp--;
		}
	} else if (value >= 1.0) {
		while (value >= 1.0) {
			value /= 10.0;
			exp++;
		}
	}
	frac = ftoi(value * 1000000.0);
	count += _sceSnprintf_pf(func, context, size, "0.%d", frac);
	if (exp >= 0) count += _sceSnprintf_pf(func, context, size, "e+%d", exp);
	else count += _sceSnprintf_pf(func, context, size, "e%d", exp);
	return count;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceSnprintf);

int KERNEL_SECTION(snprintf_char) snprintf_char(char **buffer, int *size, int c)
{
	if (!*size) return 1;
	if (c < 0x100) {
		if (*size == 1) c = 0;
		*(*buffer)++ = c;
		(*size)--;
		return 1;
	}
	**buffer = 0;
	return 0;
}

int KERNEL_SECTION(printf_char) printf_char(void *context, int unused, int c)
{
	if (c) deci2Putchar(c);
	return 1;
}

int KERNEL_SECTION(kprintf_char) kprintf_char(void *context, int unused, int c)
{
	if (c) serialPutchar(c);
	return 1;
}

int KERNEL_SECTION(_sceSnprintf_pf) _sceSnprintf_pf(kernelPrintfChar func, void *context, int *size, const char *format, ...)
{
	int n;
	va_list args;
	va_start(args, format);
	n = _sceSnprintf(func, context, *size, format, args);
	*size -= n;
	return n;
}

int KERNEL_SECTION(sceSnprintf) sceSnprintf(char *buffer, int size, const char *format, ...)
{
	char *ptr = buffer;
	va_list args;
	va_start(args, format);
	return _sceSnprintf((kernelPrintfChar)snprintf_char, &ptr, size, format, args);
}

void KERNEL_SECTION(scePrintf) scePrintf(const char *format, ...)
{
	int context = 0;
	int intr;
	va_list args;
	intr = DIntr();
	va_start(args, format);
	_sceSnprintf((kernelPrintfChar)printf_char, &context, 0xffffffff, format, args);
	if (intr) EIntr();
	va_end(args);
}

void KERNEL_SECTION(kprintf) kprintf(const char *format, ...)
{
	int context = 0;
	int intr;
	va_list args;
	intr = DIntr();
	va_start(args, format);
	_sceSnprintf((kernelPrintfChar)kprintf_char, &context, 0xffffffff, format, args);
	if (intr) EIntr();
	va_end(args);
}

void KERNEL_SECTION(_set_sreg) _set_sreg(sifCmdSregPkt_t *request, sifCmdData_t *data)
{
	data->sregs[request->index] = request->value;
}

void KERNEL_SECTION(_change_addr) _change_addr(sifCmdChangeAddrPkt_t *request, sifCmdData_t *data)
{
	data->iopBuffer = request->addr;
}

int KERNEL_SECTION(sceSifGetSreg) sceSifGetSreg(int index)
{
	return sdkSifSreg[index];
}

int KERNEL_SECTION(sceSifSetSreg) sceSifSetSreg(int index, int value)
{
	return sdkSifSreg[index] = value;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00129658);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifInitCmd);

void KERNEL_SECTION(sceSifExitCmd) sceSifExitCmd(void)
{
	DisableDmac(5);
	RemoveDmacHandler(5, sdkSifCmdHandlerId);
	sdkSifCmdInitialized = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifAddCmdHandler);

void KERNEL_SECTION(sceSifRemoveCmdHandler) sceSifRemoveCmdHandler(int cid)
{
	if (cid < 0) sdkSifCmd.sysHandlers[cid & 0x7fffffff].func = 0;
	else sdkSifCmd.usrHandlers[cid].func = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceSifSendCmd);

int KERNEL_SECTION(sceSifSendCmd) sceSifSendCmd(int cid, void *packet, int size, void *src, void *dest, int length)
{
	return _sceSifSendCmd(cid, 0, packet, size, src, dest, length);
}

int KERNEL_SECTION(isceSifSendCmd) isceSifSendCmd(int cid, void *packet, int size, void *src, void *dest, int length)
{
	return _sceSifSendCmd(cid, 1, packet, size, src, dest, length);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceSifCmdIntrHdlr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifWriteBackDCache);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00129D8C);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifInitRpc);

void KERNEL_SECTION(sceSifExitRpc) sceSifExitRpc(void)
{
	sceSifExitCmd();
	sdkSifRpcInitialized = 0;
}

sifRpcPkt_t *KERNEL_SECTION(_sceRpcGetPacket) _sceRpcGetPacket(sifRpcPool_t *rpc)
{
	sifRpcPkt_t *packet;
	int i, count, id;
	DIntr();
	count = rpc->count;
	packet = rpc->packets;
	for (i = 0; i < count; i++, packet++) {
		if (!(packet->mode & 1)) {
			packet->mode = (i << 16) | 5;
			if (++rpc->pid == 1) {
				rpc->pid++;
				id = 1;
			} else id = rpc->pid;
			packet->paddr = packet;
			packet->pid = id;
			EIntr();
			return packet;
		}
	}
	EIntr();
	return 0;
}

void KERNEL_SECTION(_sceRpcFreePacket) _sceRpcFreePacket(sifRpcPacket_t *packet)
{
	packet->id = 0;
	packet->mode &= ~1;
}

char *KERNEL_SECTION(_sceRpcGetFPacket) _sceRpcGetFPacket(sifRpcData_t *rpc)
{
	int index = rpc->index % rpc->count;
	char *packet = rpc->packets + index * 64;
	rpc->index = index + 1;
	return packet;
}

char *KERNEL_SECTION(_sceRpcGetFPacket2) _sceRpcGetFPacket2(sifRpcData_t *rpc, int index)
{
	if (index < 0 || index >= rpc->fixedCount) return _sceRpcGetFPacket(rpc);
	return rpc->fixed + index * 64;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _request_end);

int KERNEL_SECTION(_alarm_rdata) _alarm_rdata(int id, int a1, int a2, sifRpcAlarm_t *data)
{
	return isceSifSendCmd(0x80000008, data, 0x40, data->src, data->dest, data->size) ? 0 : 0x800;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _request_rdata);

int KERNEL_SECTION(sceSifGetOtherData) sceSifGetOtherData(sifRpcReceiveData_t *rdata, void *src, void *dest, int size, int mode)
{
	kernelSemaParam_t param;
	sifRpcOtherPkt_t *packet = (sifRpcOtherPkt_t *)_sceRpcGetPacket(&sdkRpcPool);
	if (!packet) return -1;
	rdata->packet = packet;
	rdata->rpcId = packet->pid;
	packet->src = src;
	packet->dest = dest;
	packet->size = size;
	packet->paddr = packet;
	packet->client = rdata;
	if (!(mode & 1)) {
		param.maxCount = 1;
		param.option = sdkRpcDataSemaName;
		param.initCount = 0;
		rdata->sema = CreateSema(&param);
		if (rdata->sema < 0) {
			_sceRpcFreePacket((sifRpcPacket_t *)packet);
			return -3;
		}
		if (!sceSifSendCmd(0x8000000c, packet, 0x40, 0, 0, 0)) {
			_sceRpcFreePacket((sifRpcPacket_t *)packet);
			DeleteSema(rdata->sema);
			return -2;
		}
		WaitSema(rdata->sema);
		DeleteSema(rdata->sema);
		return 0;
	}
	rdata->sema = -1;
	if (!sceSifSendCmd(0x8000000c, packet, 0x40, 0, 0, 0)) {
		_sceRpcFreePacket((sifRpcPacket_t *)packet);
		return -2;
	}
	return 0;
}

sifRpcServer_t *KERNEL_SECTION(_search_svdata) _search_svdata(int sid, sifRpcInfo_t *info)
{
	sifRpcQueue_t *queue;
	sifRpcServer_t *server;
	for (queue = info->active; queue; queue = queue->next) {
		for (server = queue->link; server; server = server->next) {
			if (server->sid == sid) return server;
		}
	}
	return 0;
}

int KERNEL_SECTION(_alarm_bind) _alarm_bind(int id, int a1, int a2, void *data)
{
	return isceSifSendCmd(0x80000008, data, 0x40, 0, 0, 0) ? 0 : 0x800;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _request_bind);

int KERNEL_SECTION(sceSifBindRpc) sceSifBindRpc(sifRpcClient_t *client, int rpc, int mode)
{
	kernelSemaParam_t param;
	sifRpcMsg_t *packet;
	client->command = 0;
	client->server = 0;
	packet = (sifRpcMsg_t *)_sceRpcGetPacket(&sdkRpcPool);
	if (!packet) return -1;
	client->packet = packet;
	client->rpcId = packet->pid;
	packet->cid = rpc;
	packet->paddr = packet;
	packet->client = client;
	if (!(mode & 1)) {
		param.maxCount = 1;
		param.option = sdkRpcBindSemaName;
		param.initCount = 0;
		client->sema = CreateSema(&param);
		if (client->sema < 0) {
			_sceRpcFreePacket((sifRpcPacket_t *)packet);
			return -3;
		}
		if (!sceSifSendCmd(0x80000009, packet, 0x40, 0, 0, 0)) {
			_sceRpcFreePacket((sifRpcPacket_t *)packet);
			DeleteSema(client->sema);
			return -2;
		}
		WaitSema(client->sema);
		DeleteSema(client->sema);
		return 0;
	}
	client->sema = -1;
	if (!sceSifSendCmd(0x80000009, packet, 0x40, 0, 0, 0)) {
		_sceRpcFreePacket((sifRpcPacket_t *)packet);
		return -2;
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _request_call);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifCallRpc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifCheckStatRpc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012A958);

void KERNEL_SECTION(_sceFsIobSemaMK) _sceFsIobSemaMK(void)
{
	kernelSemaParam_t param;
	if (sdkFsIobSema == -1) {
		param.initCount = 1;
		param.maxCount = 1;
		param.option = sdkFsIobSemaName;
		sdkFsIobSema = CreateSema(&param);
		param.option = sdkFsIobSemaName2;
		sdkFsIobSema2 = CreateSema(&param);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012A9E0);

fsIob_t *KERNEL_SECTION(new_iob) new_iob(void)
{
	fsIob_t *iob;
	_sceFsIobSemaMK();
	WaitSema(sdkFsIobSema);
	for (iob = sdkFsIob; iob < sdkFsIob + 32; iob++) {
		if (!iob->mode) {
			iob->mode = 0x10000000;
			SignalSema(sdkFsIobSema);
			return iob;
		}
	}
	SignalSema(sdkFsIobSema);
	return 0;
}

int KERNEL_SECTION(sceFsSifCallRpc) sceFsSifCallRpc(void *client, int rpc, int mode, void *send, int ssize, void *recv, int rsize, void *end, void *endparam, int noRetry)
{
	int i = 0, failed;
	int delay = 1;
	do {
		failed = sceSifCallRpc(client, rpc, mode, send, ssize, recv, rsize, end, endparam) < 0;
		if (!failed || noRetry) break;
		DelayThread(delay * 1000);
		if (delay < 127) delay *= 2;
	} while (++i < 101);
	return failed;
}

fsIob_t *KERNEL_SECTION(get_iob) get_iob(unsigned int fd)
{
	fsIob_t *iob;
	_sceFsIobSemaMK();
	WaitSema(sdkFsIobSema);
	if (fd >= 32) {
		SignalSema(sdkFsIobSema);
		return 0;
	}
	iob = &sdkFsIob[fd];
	SignalSema(sdkFsIobSema);
	return iob;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceFs_Rcv_Intr);

void KERNEL_SECTION(_sceFsSemInit) _sceFsSemInit(void)
{
	kernelSemaParam_t param;
	if (sdkFsSema == -1) {
		param.initCount = 1;
		param.maxCount = 1;
		param.option = sdkFsSemaName;
		sdkFsSema = CreateSema(&param);
	}
}

int KERNEL_SECTION(_sceFsWaitS) _sceFsWaitS(int unused)
{
	_sceFsSemInit();
	WaitSema(sdkFsSema);
	return 0;
}

void KERNEL_SECTION(_sceFsSigSema) _sceFsSigSema(void)
{
	SignalSema(sdkFsSema);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceFs_Poff_Intr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceFsInit);

int KERNEL_SECTION(_fs_version) _fs_version(void)
{
	kernelVersion_t *kernel = &sdkKernelVersion;
	void *local = sdkFsResetFlags;
	int result = 0;
	if (memcmp(local, kernel, 4) && memcmp(local, sdkFsVersion, 4))
		result = memcmp(kernel, sdkFsVersion, 4) != 0;
	return result;
}

int KERNEL_SECTION(sceFsReset) sceFsReset(void)
{
	sdkFsInitialized = 0;
	memset(sdkFsResetFlags, 0, 4);
	return 0;
}

int KERNEL_SECTION(sceOpen) sceOpen(const char *name, int flags, ...)
{
	fsOpenRequest_t *request;
	kernelSemaParam_t param;
	int result;
	va_list args;
	fsIob_t *iob;
	int i, index, sema, ok, mode;
	_sceFsWaitS(0);
	request = &sdkFsRequest.open;
	if (!sdkFsInitialized) sceFsInit();
	if (_fs_version()) {
		_sceFsSigSema();
		return 0xfffefffc;
	}
	iob = new_iob();
	if (!iob) {
		_sceFsSigSema();
		return -19;
	}
	va_start(args, flags);
	mode = va_arg(args, int);
	for (i = 0; i < 0x400; i++) {
		if (!(request->name[i] = name[i])) break;
	}
	if (i == 0x400) request->name[0x3ff] = 0;
	index = iob - sdkFsIob;
	request->flags = flags & 0x7fffffff;
	request->mode = mode;
	param.maxCount = 1;
	param.option = sdkFsOpenSemaName;
	request->index = index;
	param.initCount = 0;
	sema = CreateSema(&param);
	request->result = &result;
	request->sema = sema;
	request->size = 4;
	if (sceFsSifCallRpc(sdkFsClient, 0, 0, &sdkFsRequest.open, 0x418, sdkFsReceive, 4, 0, 0, 0) < 0) {
		DeleteSema(sema);
		_sceFsSigSema();
		return -11;
	}
	ok = *(int *)((unsigned int)sdkFsReceive | 0x20000000);
	_sceFsSigSema();
	if (!ok) {
		DeleteSema(sema);
		return -11;
	}
	WaitSema(sema);
	DeleteSema(sema);
	if (result < 0) {
		WaitSema(sdkFsIobSema);
		iob->mode = 0;
		SignalSema(sdkFsIobSema);
		return result;
	}
	ok = index;
	WaitSema(sdkFsIobSema);
	iob->unk00 = result;
	iob->mode |= flags;
	SignalSema(sdkFsIobSema);
	return ok;
}

int KERNEL_SECTION(sceClose) sceClose(int fd)
{
	fsCloseRequest_t *request = &sdkFsRequest.close;
	kernelSemaParam_t param;
	int result;
	fsIob_t *iob = get_iob(fd);
	int sema, ok, ret;
	_sceFsWaitS(1);
	if (!sdkFsInitialized || !iob || !iob->mode) {
		_sceFsSigSema();
		return -9;
	}
	request->fd = iob->unk00;
	request->index = iob - sdkFsIob;
	param.maxCount = 1;
	param.option = sdkFsCloseSemaName;
	param.initCount = 0;
	sema = CreateSema(&param);
	request->sema = sema;
	request->result = &result;
	request->size = 4;
	if (sceFsSifCallRpc(sdkFsClient, 1, 0, request, 0x14, sdkFsReceive, 4, 0, 0, 0) < 0) {
		DeleteSema(sema);
		_sceFsSigSema();
		return -11;
	}
	iob->mode = 0;
	ok = *(int *)((unsigned int)sdkFsReceive | 0x20000000);
	_sceFsSigSema();
	if (!ok) {
		DeleteSema(sema);
		return -11;
	}
	WaitSema(sema);
	DeleteSema(sema);
	ret = result;
	if (ret < 0) return ret;
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceLseek);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceRead);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceWrite);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012BEB0);

int KERNEL_SECTION(sceDevctl) sceDevctl(const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
	fsDevctlRequest_t *request;
	kernelSemaParam_t param;
	int result;
	unsigned int i;
	int n, sema, ok, rpc;
	_sceFsWaitS(0x17);
	request = &sdkFsRequest.devctl;
	if (!sdkFsInitialized) sceFsInit();
	for (n = 0; n < 0x400; n++) {
		if (!(request->name[n] = name[n])) break;
	}
	if (n == 0x400) request->name[0x3ff] = 0;
	if (arglen > 0x400 || buflen > 0x400) {
		_sceFsSigSema();
		return -22;
	}
	if (cmd == 0x4601) {
		if (!((fsDevctlDma_t *)arg)->size) {
			_sceFsSigSema();
			return 0;
		}
		if (!((fsDevctlDma_t *)arg)->count) {
			_sceFsSigSema();
			return -22;
		}
	}
	for (i = 0; i < arglen; i++) request->arg[i] = ((char *)arg)[i];
	request->arglen = arglen;
	param.maxCount = 1;
	param.option = sdkFsDevctlSemaName;
	request->cmd = cmd;
	param.initCount = 0;
	sema = CreateSema(&param);
	request->buflen = buflen;
	request->result = &result;
	request->size = 4;
	request->buf = buf;
	request->sema = sema;
	if (cmd == 0x4601) {
		rpc = 0x1c;
		sceSifWriteBackDCache(((fsDevctlDma_t *)arg)->addr, ((fsDevctlDma_t *)arg)->size * ((fsDevctlDma_t *)arg)->count);
	} else {
		rpc = 0x17;
	}
	sceSifWriteBackDCache(&sdkFsRequest.devctl, 0x81c);
	if (sceFsSifCallRpc(sdkFsClient, rpc, 0, &sdkFsRequest.devctl, 0x81c, sdkFsReceive, 4, 0, 0, 0) < 0) {
		DeleteSema(sema);
		_sceFsSigSema();
		return -11;
	}
	ok = *(int *)((unsigned int)sdkFsReceive | 0x20000000);
	_sceFsSigSema();
	if (!ok) {
		DeleteSema(sema);
		return -11;
	}
	WaitSema(sema);
	DeleteSema(sema);
	return result;
}

int KERNEL_SECTION(sceSifInitIopHeap) sceSifInitIopHeap(void)
{
	int i;
	while (1) {
		if (sceSifBindRpc(&sdkIopHeapClient, 0x80000003, 0) < 0) return -1;
		if (sdkIopHeapClient.server) {
			sdkIopHeapState = 0;
			break;
		}
		i = 0x100000;
		while (i--) {}
	}
	return 0;
}

void *KERNEL_SECTION(sceSifAllocIopHeap) sceSifAllocIopHeap(int size)
{
	if (sdkIopHeapState < 0) return 0;
	sdkIopHeapSend[0] = size;
	if (sceSifCallRpc(&sdkIopHeapClient, 1, 0, sdkIopHeapSend, 4, sdkIopHeapReceive, 4, 0, 0) < 0) return 0;
	return (void *)sdkIopHeapReceive[0];
}

void *KERNEL_SECTION(sceSifAllocSysMemory) sceSifAllocSysMemory(int type, int size, void *addr)
{
	if (sdkIopHeapState < 0) return 0;
	sdkIopHeapSend[0] = size;
	sdkIopHeapSend[1] = type;
	sdkIopHeapSend[2] = (int)addr;
	if (sceSifCallRpc(&sdkIopHeapClient, 4, 0, sdkIopHeapSend, 0xc, sdkIopHeapReceive, 4, 0, 0) < 0) return 0;
	return (void *)sdkIopHeapReceive[0];
}

int KERNEL_SECTION(sceSifFreeSysMemory) sceSifFreeSysMemory(void *addr)
{
	if (sdkIopHeapState < 0) return 0;
	sdkIopHeapSend[0] = (int)addr;
	if (sceSifCallRpc(&sdkIopHeapClient, 2, 0, sdkIopHeapSend, 4, sdkIopHeapReceive, 4, 0, 0) < 0) return -1;
	return sdkIopHeapReceive[0];
}

int KERNEL_SECTION(sceSifFreeIopHeap) sceSifFreeIopHeap(void *addr)
{
	return sceSifFreeSysMemory(addr);
}

unsigned int KERNEL_SECTION(sceSifQueryMaxFreeMemSize) sceSifQueryMaxFreeMemSize(void)
{
	if (sdkIopHeapState < 0) return 0;
	if (sceSifCallRpc(&sdkIopHeapClient, 6, 0, 0, 0, sdkIopHeapReceive, 4, 0, 0) < 0) return 0xffffffff;
	return sdkIopHeapReceive[0];
}

unsigned int KERNEL_SECTION(sceSifQueryTotalFreeMemSize) sceSifQueryTotalFreeMemSize(void)
{
	if (sdkIopHeapState < 0) return 0;
	if (sceSifCallRpc(&sdkIopHeapClient, 7, 0, 0, 0, sdkIopHeapReceive, 4, 0, 0) < 0) return 0xffffffff;
	return sdkIopHeapReceive[0];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012C4A8);

int KERNEL_SECTION(_lf_bind) _lf_bind(void)
{
	int i;
	if (sdkLoadFileState < 0) {
		while (1) {
			if (sceSifBindRpc((sifRpcClient_t *)sdkLoadFileClient, 0x80000006, 0) < 0) return -1;
			if (sdkLoadFileClient[9]) {
				sdkLoadFileState = 0;
				if (sceSifCallRpc(sdkLoadFileClient, 0xff, 0, 0, 0, &sdkLoadFileBuffer, 4, 0, 0) < 0) return 0xfffeffff;
				*(kernelVersion_t *)sdkLoadFileFlags = *(kernelVersion_t *)&sdkLoadFileBuffer;
				return 0;
			}
			i = 0x100000;
			while (i--) {}
		}
	}
	return 0;
}

int KERNEL_SECTION(_lf_version) _lf_version(void)
{
	kernelVersion_t *kernel = &sdkKernelVersion;
	void *local = sdkLoadFileFlags;
	int result = 0;
	if (memcmp(local, kernel, 4) && memcmp(local, sdkLoadFileVersion, 4))
		result = memcmp(kernel, sdkLoadFileVersion, 4) != 0;
	return result;
}

int KERNEL_SECTION(sceSifLoadFileReset) sceSifLoadFileReset(void)
{
	sdkLoadFileState = -1;
	memset(sdkLoadFileFlags, 0, 4);
	return 0;
}

int KERNEL_SECTION(_sceSifLoadModuleBuffer) _sceSifLoadModuleBuffer(void *addr, int argLength, const char *args, int *result)
{
	if (_lf_bind() < 0) return 0xffff0000;
	if (_lf_version()) return 0xfffefffc;
	LOAD_BUFFER->value = (int)addr;
	if (args) {
		if (argLength > 0xfc) {
			LOAD_BUFFER->args = *(sifLoadArgs_t *)args;
			LOAD_BUFFER->argLength = 0xfc;
		} else {
			memcpy(&LOAD_BUFFER->args, args, argLength);
			LOAD_BUFFER->argLength = argLength;
		}
	} else {
		LOAD_BUFFER->argLength = 0;
	}
	if (sceSifCallRpc(sdkLoadFileClient, 6, 0, LOAD_BUFFER, 0x200, LOAD_BUFFER, 8, 0, 0) < 0) return 0xfffeffff;
	{
		int value = LOAD_BUFFER->value;
		*result = LOAD_BUFFER->argLength;
		return value;
	}
}

int KERNEL_SECTION(sceSifStopModule) sceSifStopModule(int id, int argLength, const char *args, int *result)
{
	if (_lf_bind() < 0) return 0xffff0000;
	if (_lf_version()) return 0xfffefffc;
	LOAD_BUFFER->value = id;
	if (args) {
		if (argLength > 0xfc) {
			LOAD_BUFFER->args = *(sifLoadArgs_t *)args;
			LOAD_BUFFER->argLength = 0xfc;
		} else {
			memcpy(&LOAD_BUFFER->args, args, argLength);
			LOAD_BUFFER->argLength = argLength;
		}
	} else {
		LOAD_BUFFER->argLength = 0;
	}
	if (sceSifCallRpc(sdkLoadFileClient, 7, 0, LOAD_BUFFER, 0x200, LOAD_BUFFER, 8, 0, 0) < 0) return 0xfffeffff;
	{
		int value = LOAD_BUFFER->value;
		*result = LOAD_BUFFER->argLength;
		return value;
	}
}

int KERNEL_SECTION(sceSifUnloadModule) sceSifUnloadModule(int id)
{
	if (_lf_bind() < 0) return 0xffff0000;
	if (_lf_version()) return 0xfffefffc;
	sdkLoadFileBuffer.result = id;
	if (sceSifCallRpc(sdkLoadFileClient, 8, 0, &sdkLoadFileBuffer, 4, &sdkLoadFileBuffer, 4, 0, 0) < 0) return 0xfffeffff;
	return sdkLoadFileBuffer.result;
}

int KERNEL_SECTION(sceSifSearchModuleByName) sceSifSearchModuleByName(const char *name)
{
	if (_lf_bind() < 0) return 0xffff0000;
	if (_lf_version()) return 0xfffefffc;
	strncpy(sdkLoadFileBuffer.name, name, 0xfc);
	sdkLoadFileBuffer.name[0xfb] = 0;
	if (sceSifCallRpc(sdkLoadFileClient, 9, 0, &sdkLoadFileBuffer, 0x200, &sdkLoadFileBuffer, 4, 0, 0) < 0) return 0xfffeffff;
	return sdkLoadFileBuffer.result;
}

int KERNEL_SECTION(sceSifLoadModuleBuffer) sceSifLoadModuleBuffer(void *addr, int args, const char *argp)
{
	int result[4];
	return _sceSifLoadModuleBuffer(addr, args, argp, result);
}

int KERNEL_SECTION(sceSifLoadStartModuleBuffer) sceSifLoadStartModuleBuffer(void *addr, int args, const char *argp, int *result)
{
	return _sceSifLoadModuleBuffer(addr, args, argp, result);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012CC00);

int KERNEL_SECTION(sceSifResetIop) sceSifResetIop(const char *arg, int mode)
{
	sifDmaTransfer_t dma;
	void *dest;
	int i;
	sceSifExecNotifyHandler(0, 0);
	sceSifExecNotifyHandler(1, 0);
	sceSifStopDma();
	dest = (void *)sceSifGetReg(0x80000000);
	sdkSifResetPacket.mode = mode;
	i = 0;
	while (arg[i]) {
		sdkSifResetPacket.arg[i] = arg[i];
		i++;
	}
	sdkSifResetPacket.header.dest = 0;
	sdkSifResetPacket.argLength = i;
	sdkSifResetPacket.header.cid = 0x80000003;
	sdkSifResetPacket.header.dsize = 0;
	sdkSifResetPacket.header.psize = 0x68;
	dma.src = &sdkSifResetPacket;
	dma.dest = dest;
	dma.size = 0x68;
	dma.attr = 0x44;
	sceSifWriteBackDCache(&sdkSifResetPacket, 0x68);
	sceSifSetReg(4, 0x40000);
	if (sceSifSetDma(&dma, 1)) {
		sceSifSetReg(4, 0x10000);
		sceSifSetReg(4, 0x20000);
		sceSifSetReg(0x80000002, 0);
		sceSifSetReg(0x80000000, 0);
		return 1;
	}
	return 0;
}

int KERNEL_SECTION(sceSifIsAliveIop) sceSifIsAliveIop(void)
{
	unsigned int stat = sceSifGetReg(4) & 0x10000;
	return stat != 0;
}

int KERNEL_SECTION(sceSifSyncIop) sceSifSyncIop(void)
{
	if (!(sceSifGetReg(4) & 0x40000)) return 0;
	sceResetttyinit();
	sceSifExecNotifyHandler(1, 1);
	sceSifExecNotifyHandler(0, 1);
	return 1;
}

/* Returns a pointer to the terminating NUL (inlined into sceSifRebootIop). */
static inline const char *_strEnd(const char *s)
{
	while (*s) s++;
	return s;
}

int KERNEL_SECTION(sceSifRebootIop) sceSifRebootIop(const char *path)
{
	char buffer[0x50];
	const char *prefix = sdkSifRebootPrefix;
	char *d;
	char c;
	if ((unsigned int)(_strEnd(path) + 11 - path) > 0x50) {
		scePrintf(sdkSifRebootTooLongMsg, path);
		return 0;
	}
	sceSifInitRpc(0);
	sceSifExitRpc();
	d = buffer;
	while (*prefix) *d++ = *prefix++;
	while (*path) *d++ = *path++;
	*d = 0;
	return sceSifResetIop(buffer, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012CF10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", Copy);

int KERNEL_SECTION(kCopy) kCopy(unsigned int *dst, unsigned int *src, unsigned int size)
{
	unsigned int i;
	size >>= 2;
	for (i = 0; i < size; i++) *dst++ = *src++;
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetEntryAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", setup);

void KERNEL_SECTION(InitTLBFunctions) InitTLBFunctions(void)
{
	kernelPatch_t *patch;
	unsigned int i;
	setup(sdkTlbPatchTable[0].syscall, sdkTlbPatchTable[0].func);
	Copy((void *)0x80075000, sdkTlbPatchCode, 0x330);
	FlushCache(0);
	FlushCache(2);
	setup(sdkTlbPatchTable[1].syscall, sdkTlbPatchTable[1].func);
	setup(sdkTlbPatchTable[2].syscall, sdkTlbPatchTable[2].func);
	patch = &sdkTlbPatchTable[3];
	for (i = 3; i < 8; i++) {
		setup(patch->syscall, GetEntryAddress(patch->syscall));
		patch++;
	}
	sdkExecArgv = GetEntryAddress(3);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _SetTLBEntry);

int KERNEL_SECTION(InitTLB) InitTLB(void)
{
	int ret;
	if (GetMemorySize() == 0x2000000) ret = InitTLB32MB();
	else ret = _InitTLB();
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", InitTLB32MB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D28C);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _kExitTLBHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", DIntr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", EIntr);

void KERNEL_SECTION(supplement_crt0) supplement_crt0(void)
{
	kernelSemaParam_t libc;
	kernelSemaParam_t libcEh;
	libc.option = sdkLibcSemaName;
	libc.maxCount = 1;
	libc.initCount = 1;
	libcEh.maxCount = 1;
	libcEh.initCount = 1;
	libcEh.option = sdkLibcEhSemaName;
	sdkLibcSema = CreateSema(&libc);
	sdkLibcEhSema = CreateSema(&libcEh);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D4E8);

int KERNEL_SECTION(kCopy___dupe2) kCopy___dupe2(unsigned int *dst, unsigned int *src, unsigned int size)
{
	unsigned int i;
	size >>= 2;
	for (i = 0; i < size; i++) *dst++ = *src++;
	return 0;
}

unsigned int *KERNEL_SECTION(kFindAddress) kFindAddress(unsigned int *addr, unsigned int *end, unsigned int value)
{
	while (*addr != value && addr < end) addr++;
	return addr < end ? addr : 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", FindAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D578);

void KERNEL_SECTION(InitSystemCallTableAddress) InitSystemCallTableAddress(void)
{
	unsigned int find, copy, a, b;
	setup___dupe2(sdkSyscallPatchTable[0].syscall, sdkSyscallPatchTable[0].func);
	setup___dupe2(sdkSyscallPatchTable[1].syscall, sdkSyscallPatchTable[1].func);
	find = FindAddress(0x80000000, 0x80080000, (unsigned int)kFindAddress);
	copy = FindAddress(0x80000000, 0x80080000, (unsigned int)kCopy___dupe2);
	a = find - 0x20c;
	b = copy - 0x168;
	while (a != b) {
		if (a < b) {
			find = FindAddress(find + 4, 0x80080000, (unsigned int)kFindAddress);
			a = find - 0x20c;
		} else {
			copy = FindAddress(copy + 4, 0x80080000, (unsigned int)kCopy___dupe2);
			b = copy - 0x168;
		}
	}
	sdkSyscallTable = a;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", setup___dupe2);

void KERNEL_SECTION(_InitSys) _InitSys(void)
{
	supplement_crt0();
	InitSystemCallTableAddress();
	InitAlarm();
	InitTimer(2);
	StartTimerSystemTime();
	InitThread();
	InitExecPS2();
	InitTLBFunctions();
	sceSifInitRebootNotify();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D6E4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", setup___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", Copy___dupe2);

int KERNEL_SECTION(kCopy___dupe3) kCopy___dupe3(unsigned int *dst, unsigned int *src, unsigned int size)
{
	unsigned int i;
	size >>= 2;
	for (i = 0; i < size; i++) *dst++ = *src++;
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetEntryAddress___dupe2);

int KERNEL_SECTION(PatchIsNeeded) PatchIsNeeded(void)
{
	osdConfig_t original;
	osdConfig_t test;
	GetOsdConfigParam(&original);
	test = original;
	test.version = 1;
	SetOsdConfigParam(&test);
	GetOsdConfigParam(&test);
	SetOsdConfigParam(&original);
	return test.version == 0;
}

void KERNEL_SECTION(InitExecPS2) InitExecPS2(void)
{
	kernelPatch_t *patch;
	unsigned int i;
	if (!PatchIsNeeded()) return;
	setup___dupe3(sdkExecPatchTable[0].syscall, sdkExecPatchTable[0].func);
	Copy___dupe2((void *)0x80074000, sdkExecPatchCode, 0x7a8);
	FlushCache(0);
	FlushCache(2);
	setup___dupe3(sdkExecPatchTable[1].syscall, sdkExecPatchTable[1].func);
	patch = &sdkExecPatchTable[2];
	for (i = 2; i < 3; i++) {
		setup___dupe3(patch->syscall, GetEntryAddress___dupe2(patch->syscall));
		patch++;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D864);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", Copy___dupe3);

int KERNEL_SECTION(kCopy___dupe4) kCopy___dupe4(unsigned char *dst, unsigned char *src, unsigned int size)
{
	unsigned int i;
	for (i = 0; i < size; i++) *dst++ = *src++;
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", setup___dupe4);

char *KERNEL_SECTION(SetArg) SetArg(const char *filename, int argc, char **argv)
{
	char **args = sdkExecArgv;
	char *ptr = (char *)args + 0x40;
	char *strings = ptr;
	int len, i;
	setup___dupe4(sdkArgPatch.syscall, sdkArgPatch.func);
	if (argc >= 16) argc = 15;
	Copy___dupe3(args, &ptr, 4);
	args++;
	len = strlen(filename) + 1;
	Copy___dupe3(ptr, (void *)filename, len);
	ptr += len;
	for (i = 0; i < argc; i++) {
		Copy___dupe3(args, &ptr, 4);
		args++;
		len = strlen(argv[i]) + 1;
		Copy___dupe3(ptr, argv[i], len);
		ptr += len;
	}
	return strings;
}

void KERNEL_SECTION(TerminateLibrary) TerminateLibrary(void)
{
	InitTLB();
}

void KERNEL_SECTION(LoadExecPS2) LoadExecPS2(const char *filename, int argc, char **argv)
{
	char *name = SetArg(filename, argc, argv);
	TerminateLibrary();
	_LoadExecPS2(name, argc, sdkExecArgv + 1);
}

void KERNEL_SECTION(Exit) Exit(int status)
{
	TerminateLibrary();
	_Exit(status);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012DA48);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", setup___dupe5);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", Copy___dupe4);

int KERNEL_SECTION(kCopy___dupe5) kCopy___dupe5(unsigned int *dst, unsigned int *src, unsigned int size)
{
	unsigned int i;
	size >>= 2;
	for (i = 0; i < size; i++) *dst++ = *src++;
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetEntryAddress___dupe3);

void KERNEL_SECTION(InitAlarm) InitAlarm(void)
{
	kernelPatch_t *patch;
	unsigned int i;
	if (*(volatile unsigned int *)0x10001810 & 0x100) return;
	setup___dupe5(sdkAlarmPatchTable[0].syscall, sdkAlarmPatchTable[0].func);
	Copy___dupe4((void *)0x80076000, sdkAlarmPatchCode, 0x740);
	Copy___dupe4((void *)0x82000, sdkAlarmPatchData, 0x28);
	FlushCache(0);
	FlushCache(2);
	setup___dupe5(sdkAlarmPatchTable[1].syscall, sdkAlarmPatchTable[1].func);
	patch = &sdkAlarmPatchTable[2];
	for (i = 2; i < 8; i++) {
		setup___dupe5(patch->syscall, GetEntryAddress___dupe3(patch->syscall));
		patch++;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012DB8C);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetT2);

void KERNEL_SECTION(SetT2_COUNT) SetT2_COUNT(int value)
{
	SetT2((volatile int *)0xb0001000, value);
}

void KERNEL_SECTION(SetT2_MODE) SetT2_MODE(int value)
{
	SetT2((volatile int *)0xb0001010, value);
}

void KERNEL_SECTION(SetT2_COMP) SetT2_COMP(int value)
{
	SetT2((volatile int *)0xb0001020, value);
}

int KERNEL_SECTION(InitTimer) InitTimer(int clock)
{
	timerData_t *timer = &sdkTimer;
	timerCounter_t *counter, *next;
	int i, id, intr;
	unsigned int mode;
	if (timer->intcHandlerId >= 0) return 0x80008001;
	sdkTimer.highCount = 0;
	timer->used = 0;
	memset(sdkTimerCounters, 0, sizeof(sdkTimerCounters));
	timer->freeList = sdkTimerCounters;
	for (i = 127; i >= 0; i--) sdkTimerCounters[i].next = &sdkTimerCounters[i + 1];
	sdkTimerCounters[127].next = 0;
	_InitAlarm();
	id = AddIntcHandler2(11, cbTimerHandler, 0, 0);
	if (id < 0) return 0x80009021;
	sdkTimer.intcHandlerId = id;
	intr = DIntr();
	mode = *(volatile unsigned int *)0x10001010;
	mode = (mode & ~3) | clock;
	mode |= 0x300;
	if (!(mode & 0x80)) {
		SetT2_COUNT(0);
		mode |= 0xc80;
		SetT2_COMP(0xffff);
	}
	SetT2_MODE(mode);
	EnableIntc(11);
	if (intr) EIntr();
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012DD88);

int KERNEL_SECTION(StartTimerSystemTime) StartTimerSystemTime(void)
{
	int intr = DIntr();
	unsigned int mode = *(volatile unsigned int *)0x10001010;
	if (mode & 0x80) {
		if (intr) EIntr();
		return 1;
	}
	SetT2_MODE((mode & ~0xc00) | 0x80);
	SetNextComp(iGetTimerSystemTime());
	if (intr) EIntr();
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012DE20);

void KERNEL_SECTION(SetNextComp) SetNextComp(unsigned long now)
{
	timerCounter_t *counter = sdkTimer.alarmList;
	unsigned int mode;
	unsigned long next, time;
	int shift;
	if (sdkTimer.systemId >= 0) return;
	mode = *(volatile unsigned int *)0x10001010;
	if (!counter) {
		SetT2_COMP(0);
		SetT2_MODE(mode & ~0x800);
		return;
	}
	next = counter->compare + counter->base - counter->total;
	for (counter = counter->next; counter; counter = counter->next) {
		time = counter->compare + counter->base - counter->total;
		if (time < next + 0x7333) next = time;
		else break;
	}
	shift = mode & 3;
	if ((long)(next - now) < 0x7333) {
		SetT2_COMP(*(volatile unsigned int *)0x10001000 + (int)((unsigned long)0x7333 >> (shift * 4)));
		SetT2_MODE(mode & ~0x800);
		return;
	}
	SetT2_MODE(mode & ~0x800);
	SetT2_COMP((int)(next >> (shift * 4)));
}

void KERNEL_SECTION(InsertAlarm) InsertAlarm(timerCounter_t *counter)
{
	unsigned long target = counter->compare + counter->base - counter->total;
	timerCounter_t *prev = 0;
	timerCounter_t *cur = sdkTimer.alarmList;
	while (cur) {
		if (target < cur->compare + cur->base - cur->total) break;
		prev = cur;
		cur = cur->next;
	}
	counter->prev = prev;
	counter->next = cur;
	if (cur) cur->prev = counter;
	if (prev) prev->next = counter;
	else sdkTimer.alarmList = counter;
}

timerCounter_t *KERNEL_SECTION(UnlinkAlarm) UnlinkAlarm(timerCounter_t *counter)
{
	timerCounter_t *next = counter->next;
	if (counter->prev) counter->prev->next = next;
	else sdkTimer.alarmList = next;
	if (next) next->prev = counter->prev;
	counter->prev = 0;
	return next;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", cbTimerHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", iGetTimerSystemTime);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetTimerSystemTime);

int KERNEL_SECTION(iAllocTimerCounter) iAllocTimerCounter(void)
{
	timerData_t *timer = &sdkTimer;
	timerCounter_t *counter = timer->freeList;
	if (!counter) return 0x80008005;
	timer->used++;
	counter->handler = 0;
	counter->mode = 0;
	timer->freeList = counter->next;
	timer->seq++;
	counter->total = 0;
	counter->key = ((timer->seq << 1) & 0x3fe) | 1;
	return ((unsigned int)counter << 4) | counter->key;
}

int KERNEL_SECTION(AllocTimerCounter) AllocTimerCounter(void)
{
	int interrupts = DIntr();
	int result = iAllocTimerCounter();
	if (interrupts) EIntr();
	return result;
}

int KERNEL_SECTION(iFreeTimerCounter) iFreeTimerCounter(int id)
{
	timerCounter_t *counter = (timerCounter_t *)(((unsigned int)id >> 10) << 6);
	if (id < 0 || (id & 0x3ff) != counter->key) return 0x80008002;
	if (sdkTimer.systemId == id) return 0x80000010;
	if (counter->mode & 2) UnlinkAlarm(counter);
	counter->key = 0;
	counter->mode = 0;
	counter->next = sdkTimer.freeList;
	sdkTimer.freeList = counter;
	sdkTimer.used--;
	return 0;
}

int KERNEL_SECTION(FreeTimerCounter) FreeTimerCounter(int id)
{
	int interrupts = DIntr();
	int result = iFreeTimerCounter(id);
	if (interrupts) EIntr();
	return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012E598);

int KERNEL_SECTION(iStartTimerCounter) iStartTimerCounter(int id)
{
	timerCounter_t *counter = (timerCounter_t *)(((unsigned int)id >> 10) << 6);
	timerData_t *timer;
	unsigned long now;
	unsigned int mode;
	if (id < 0 || (id & 0x3ff) != counter->key) return 0x80008002;
	timer = &sdkTimer;
	if (timer->systemId == id) return 0x80000010;
	if (counter->mode & 1) return 1;
	now = iGetTimerSystemTime();
	counter->base = now;
	mode = counter->mode | 1;
	counter->mode = mode;
	if (mode & 2) {
		InsertAlarm(counter);
		SetNextComp(now);
	}
	return 0;
}

int KERNEL_SECTION(StartTimerCounter) StartTimerCounter(int id)
{
	int interrupts = DIntr();
	int result = iStartTimerCounter(id);
	if (interrupts) EIntr();
	return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012E6A0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", iSetTimerHandler);

int KERNEL_SECTION(SetTimerHandler) SetTimerHandler(int id, unsigned long compare, void *handler, void *arg)
{
	int interrupts = DIntr();
	int result = iSetTimerHandler(id, compare, handler, arg);
	if (interrupts) EIntr();
	return result;
}

unsigned long KERNEL_SECTION(TimerUSec2BusClock) TimerUSec2BusClock(unsigned int sec, unsigned int usec)
{
	return (unsigned long)sec * 147456000 + (unsigned long)usec * 147456000 / 1000000;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012E8B8);

int KERNEL_SECTION(_InitAlarm) _InitAlarm(void)
{
	int i;
	sdkAlarmFree = sdkAlarms;
	for (i = 0; i < 64; i++) sdkAlarms[i].next = &sdkAlarms[i + 1];
	sdkAlarms[63].next = 0;
	return 0;
}

int KERNEL_SECTION(AlarmHandler) AlarmHandler(int id, int arg1, int arg2, timerAlarm_t *alarm)
{
	int ret = alarm->func(((unsigned int)alarm << 4 | (id & 0xfe)) | 1, arg1, arg2, alarm->arg);
	if (ret) return ret;
	alarm->next = sdkAlarmFree;
	sdkAlarmFree = alarm;
	alarm->counterId = 0;
	return -1;
}

/* Pops an alarm entry from the free list (inlined by both SetTimerAlarm variants). */
static inline timerAlarm_t *_allocAlarm(void)
{
	timerAlarm_t *alarm = sdkAlarmFree;
	if (alarm) sdkAlarmFree = alarm->next;
	return alarm;
}

int KERNEL_SECTION(SetTimerAlarm) SetTimerAlarm(unsigned long clock, int (*func)(int, int, int, void *), void *arg)
{
	timerAlarm_t *alarm;
	int id, intr;
	if (!func) return 0x80000016;
	intr = DIntr();
	alarm = _allocAlarm();
	if (!alarm) {
		if (intr) EIntr();
		return 0x80008005;
	}
	id = AllocTimerCounter();
	if (id < 0) {
		alarm->next = sdkAlarmFree;
		sdkAlarmFree = alarm;
		alarm->counterId = 0;
		if (intr) EIntr();
		return id;
	}
	alarm->func = func;
	alarm->arg = arg;
	alarm->counterId = id;
	SetTimerHandler(id, clock, AlarmHandler, alarm);
	StartTimerCounter(id);
	if (intr) EIntr();
	return ((unsigned int)alarm << 4 | (id & 0xfe)) | 1;
}

int KERNEL_SECTION(iSetTimerAlarm) iSetTimerAlarm(unsigned long clock, int (*func)(int, int, int, void *), void *arg)
{
	timerAlarm_t *alarm;
	int id;
	if (!func) return 0x80000016;
	alarm = _allocAlarm();
	if (!alarm) return 0x80008005;
	id = iAllocTimerCounter();
	if (id < 0) {
		alarm->next = sdkAlarmFree;
		sdkAlarmFree = alarm;
		alarm->counterId = 0;
		return id;
	}
	alarm->func = func;
	alarm->arg = arg;
	alarm->counterId = id;
	iSetTimerHandler(id, clock, AlarmHandler, alarm);
	iStartTimerCounter(id);
	return ((unsigned int)alarm << 4 | (id & 0xfe)) | 1;
}

int KERNEL_SECTION(ReleaseTimerAlarm) ReleaseTimerAlarm(int id)
{
	timerAlarm_t *alarm = (timerAlarm_t *)(((unsigned int)id >> 8) << 4);
	int intr = DIntr();
	if (id < 0 || ((id ^ alarm->counterId) & 0xff)) {
		if (intr) EIntr();
		return 0x80008002;
	}
	FreeTimerCounter(alarm->counterId);
	alarm->next = sdkAlarmFree;
	sdkAlarmFree = alarm;
	alarm->counterId = 0;
	if (intr) EIntr();
	return 0;
}

void KERNEL_SECTION(sceSifInitRebootNotify) sceSifInitRebootNotify(void)
{
	sdkRebootNotifyHandlers = 0;
	sdkRebootNotifyCount = 0;
	memset(sdkRebootNotifySystem, 0, 0x200);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012EC68);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifAddRebootNotifyHandler);

int KERNEL_SECTION(sceSifRemoveRebootNotifyHandler) sceSifRemoveRebootNotifyHandler(unsigned int id)
{
	sifNotifyHandler_t *table;
	unsigned int count;
	if ((int)id < 0) {
		table = sdkRebootNotifySystem;
		id &= 0x7fffffff;
		count = 32;
	} else {
		table = sdkRebootNotifyHandlers;
		count = sdkRebootNotifyCount;
	}
	if (id >= count) return -0x69;
	table[id].func = 0;
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifExecNotifyHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012EE28);
