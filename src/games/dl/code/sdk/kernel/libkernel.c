#include "common.h"
#include "libkernel.h"

/* Recovered directly from the retail boot instructions (libkernl 3000); no vendor source. */
#define KERNEL_SECTION(name) __attribute__((section(".kernel_" #name)))

/*
 * D19: EE kernel syscall stubs. Retail is `addiu $3, $0, n; syscall; jr $31; nop` for each, with
 * no recovered logic. The stub_ name and asm label keep the real symbol while leaving each
 * function's own prototype untouched.
 */
#define SYSCALL_STUB(name, number) \
	void stub_##name(void) __asm__(#name); \
	void KERNEL_SECTION(name) stub_##name(void) \
	{ \
		__asm__ volatile("addiu $3, $0, " #number "\n\tsyscall" : : : "$3"); \
	}

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
/* D18: walks both ways of each data-cache index; `op` is the cache operation for lines in range. */
#define DCACHE_RANGE_LOOP(op) \
	".set noreorder\n" \
	"\tlui $7, 0xffff\n" \
	"\tdaddu $6, $0, $0\n" \
	"\tori $7, $7, 0xf000\n" \
	"\tnop\n" \
	"1:\n" \
	"\tsync\n" \
	"\tcache 0x10, 0x0($6)\n" \
	"\tsync\n" \
	"\tmfc0 $2, $28\n" \
	"\tand $2, $2, $7\n" \
	"\taddu $2, $2, $6\n" \
	"\tsltu $3, $5, $2\n" \
	"\tsltu $2, $2, $4\n" \
	"\tbnez $2, 2f\n" \
	"\tnop\n" \
	"\tbnez $3, 2f\n" \
	"\tnop\n" \
	"\tsync\n" \
	"\tcache " op ", 0x0($6)\n" \
	"\tsync\n" \
	"2:\n" \
	"\tsync\n" \
	"\tcache 0x10, 0x1($6)\n" \
	"\tsync\n" \
	"\tmfc0 $2, $28\n" \
	"\tand $2, $2, $7\n" \
	"\taddu $2, $2, $6\n" \
	"\tsltu $3, $5, $2\n" \
	"\tsltu $2, $2, $4\n" \
	"\tbnez $2, 3f\n" \
	"\tnop\n" \
	"\tbnez $3, 3f\n" \
	"\tnop\n" \
	"\tsync\n" \
	"\tcache " op ", 0x1($6)\n" \
	"\tsync\n" \
	"3:\n" \
	"\tsync\n" \
	"\taddiu $6, $6, 0x40\n" \
	"\tslti $2, $6, 0x1000\n" \
	"\tbnez $2, 1b\n" \
	"\tnop\n" \
	".set reorder"
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
extern int sceSifCallRpc(sifRpcCallClient_t *, int, int, void *, int, void *, int, void *, void *);
/* D15: retail reads $gp through a volatile move that also orders the surrounding stores. */
#define GET_GP(x) __asm__ volatile("move %0, $28" : "=r"(x))
#define GET_GP_MEM(x) __asm__ volatile("move %0, $28" : "=r"(x) : : "memory")
/* D16: retail saves and loads $gp as one pair around the callback. */
#define LOAD_GP(o, m) __asm__ volatile("move %0, $28\n\tlw $28, %1" : "=r"(o) : "m"(m))
#define SET_GP(x) __asm__ volatile("move $28, %0" : : "r"(x))
/* D16: retail swaps $gp as one move pair around the callback. */
static inline int changeGp(int gp)
{
	int old;
	__asm__ volatile("move %0, $28\n\tmove $28, %1" : "=&r"(old) : "r"(gp) : "memory");
	return old;
}
extern void sceSifExitCmd(void);
extern unsigned int sceSifGetReg(unsigned int);
extern void sceResetttyinit(void);
extern void sceSifExecNotifyHandler(int, int);
extern unsigned int _sceSifSendCmd(int, int, sifCmdHeader_t *, int, void *, void *, int);
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
extern int cbTimerHandler(int, void *, void *);
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
extern unsigned int isceSifSetDma(sifDmaTransfer_t *, int);
extern void sceSifWriteBackDCache(void *, int);
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
extern sifRpcInitPkt_t sdkRpcPackets[32];
extern char sdkRpcRecvBuffers[];
extern char sdkRpcFixedPackets[];
extern void sceSifInitCmd(void);
extern void sceSifAddCmdHandler(int, void *, void *);
extern void _request_end(sifRpcEndPkt_t *, void *);
extern int sdkFsPoffGp;
void _request_rdata(sifRpcReqPkt_t *request, void *rpc);
void _request_bind(sifRpcReqPkt_t *request, void *rpc);
void _request_call(sifRpcCallReq_t *request, void *data);
extern int iWakeupThread(int);
extern const char sdkRpcCallSemaName[];
/* D16: single-instruction status/sync/interrupt fragments inside otherwise-C functions. */
#define GET_STATUS(x) __asm__ volatile("mfc0 %0, $12" : "=r"(x))
#define SYNC() __asm__ volatile("sync")
#define SYNC_P() __asm__ volatile("sync.p")
#define EI() __asm__ volatile("ei")
#define DI() __asm__ volatile("di")
#define INTC_STAT (*(volatile int *)0x1000f000)
extern int _DisableIntc(int);
extern int _EnableIntc(int);
extern int _DisableDmac(int);
extern int _EnableDmac(int);
extern void _sceSDC(unsigned int, unsigned int);
extern void _sceIDC(unsigned int, unsigned int);
extern int SetVSyncFlag(volatile int *, volatile unsigned long *);
extern void *EndOfHeap(void);
extern int iSignalSema(int);
extern const char sdkDelayThreadSemaName[];
extern char *sdkHeapEnd;
int _DelayThreadHandler(int id, int scheduled, int actual, void *arg);
extern int _iWakeupThread(int);
extern tlbInfo_t sdkTlbInfo;
extern const char sdkTlbInfoMsg[];
extern const char sdkTlbOverflow1Msg[];
extern const char sdkTlbOverflow2Msg[];
extern const char sdkTlbOverflow3Msg[];
extern void Exit(int);
extern int _SetTLBEntry(int, unsigned int, unsigned int, unsigned int, unsigned int);
extern char sdkSifCmdPacketBuffer[];
extern char sdkSifCmdDataBuffer[];
extern sifCmdChangeAddrPkt_t sdkSifCmdInitPacket;
extern sifCmdHandler_t sdkSifCmdSysHandlers[32];
extern void sceSifSetDChain(void);
extern int AddDmacHandler(int, void *, int);
extern int _sceSifCmdIntrHdlr(void);
extern int isceSifSetDChain(void);
extern fsInitRequest_t sdkFsInitRequest;
extern char sdkFsBuffer[];
extern int sdkFsRcvData[16];
extern fsPoffData_t sdkFsPoffData;
extern int sdkFsIsNew;
extern void _sceFs_Rcv_Intr(void *, void *);
extern void _sceFs_Poff_Intr(void *, fsPoffData_t *);
extern int ReferThreadStatus(int, threadStat_t *);
extern int _StartThread(int, void *);
extern int QueryIntrContext(void);
extern int sdkFsAsyncSema[32];
extern const char sdkFsLseekSemaName[];
char *_sceRpcGetFPacket(sifRpcData_t *rpc);
void _sceFsSemInit(void);
void _sceFsIobSemaMK(void);

SYSCALL_STUB(SetGsCrt, 0x2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001267B0);

SYSCALL_STUB(_Exit, 0x4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001267D0);

SYSCALL_STUB(_LoadExecPS2, 0x6);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001267F0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126800);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126810);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126820);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126830);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126840);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126850);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126860);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126870);

SYSCALL_STUB(AddIntcHandler, 0x10);

SYSCALL_STUB(AddIntcHandler2, 0x10);

SYSCALL_STUB(RemoveIntcHandler, 0x11);

SYSCALL_STUB(AddDmacHandler, 0x12);

SYSCALL_STUB(AddDmacHandler2, 0x12);

SYSCALL_STUB(RemoveDmacHandler, 0x13);

SYSCALL_STUB(_EnableIntc, 0x14);

SYSCALL_STUB(_DisableIntc, 0x15);

SYSCALL_STUB(_EnableDmac, 0x16);

SYSCALL_STUB(_DisableDmac, 0x17);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126920);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126930);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126940);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126950);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126960);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126970);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126980);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126990);

SYSCALL_STUB(CreateThread, 0x20);

SYSCALL_STUB(DeleteThread, 0x21);

SYSCALL_STUB(_StartThread, 0x22);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001269D0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001269E0);

SYSCALL_STUB(TerminateThread, 0x25);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A20);

SYSCALL_STUB(ChangeThreadPriority, 0x29);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A40);

SYSCALL_STUB(RotateThreadReadyQueue, 0x2b);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A60);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126A80);

SYSCALL_STUB(GetThreadId, 0x2f);

SYSCALL_STUB(ReferThreadStatus, 0x30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126AB0);

SYSCALL_STUB(SleepThread, 0x32);

SYSCALL_STUB(WakeupThread, 0x33);

SYSCALL_STUB(_iWakeupThread, -0x34);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126AF0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B00);

SYSCALL_STUB(SuspendThread, 0x37);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B20);

SYSCALL_STUB(ResumeThread, 0x39);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B40);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B60);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B70);

SYSCALL_STUB(EndOfHeap, 0x3e);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126B90);

SYSCALL_STUB(CreateSema, 0x40);

SYSCALL_STUB(DeleteSema, 0x41);

SYSCALL_STUB(SignalSema, 0x42);

SYSCALL_STUB(iSignalSema, -0x43);

SYSCALL_STUB(WaitSema, 0x44);

SYSCALL_STUB(PollSema, 0x45);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126C00);

SYSCALL_STUB(ReferSemaStatus, 0x47);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126C20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126C30);

SYSCALL_STUB(SetOsdConfigParam, 0x4a);

SYSCALL_STUB(GetOsdConfigParam, 0x4b);

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

SYSCALL_STUB(FlushCache, 0x64);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E40);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E60);

SYSCALL_STUB(sceSifStopDma, 0x6b);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126E90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126EA0);

SYSCALL_STUB(GetOsdConfigParam2, 0x6f);

SYSCALL_STUB(GsGetIMR, 0x70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126ED0);

SYSCALL_STUB(GsPutIMR, 0x71);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126EF0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126F00);

SYSCALL_STUB(SetVSyncFlag, 0x73);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126F20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126F30);

SYSCALL_STUB(sceSifDmaStat, 0x76);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126F50);

SYSCALL_STUB(sceSifSetDma, 0x77);

SYSCALL_STUB(isceSifSetDma, -0x77);

SYSCALL_STUB(sceSifSetDChain, 0x78);

SYSCALL_STUB(isceSifSetDChain, -0x78);

SYSCALL_STUB(sceSifSetReg, 0x79);

SYSCALL_STUB(sceSifGetReg, 0x7a);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126FC0);

SYSCALL_STUB(Deci2Call, 0x7c);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126FE0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00126FF0);

SYSCALL_STUB(GetMemorySize, 0x7f);

SYSCALL_STUB(_InitTLB, 0x82);

void KERNEL_SECTION(sceResetttyinit) sceResetttyinit(void)
{
	sdkTtyInitialized = 0;
}

void KERNEL_SECTION(VSync) VSync(void)
{
	int intr;
	intr = DIntr();
	INTC_STAT = 4;
	SYNC();
	if (intr) EIntr();
	while (!(INTC_STAT & 4)) {}
	intr = DIntr();
	INTC_STAT = 4;
	SYNC();
	if (intr) EIntr();
}

unsigned long KERNEL_SECTION(VSync2) VSync2(void)
{
	volatile int flag;
	volatile unsigned long value;
	int intr;
	flag = 0;
	SetVSyncFlag(&flag, &value);
	intr = DIntr();
	INTC_STAT = 4;
	SYNC();
	if (intr) EIntr();
	while (!(INTC_STAT & 4) && !flag) {}
	intr = DIntr();
	INTC_STAT = 4;
	SYNC();
	if (intr) EIntr();
	return value;
}

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

int KERNEL_SECTION(close) close(int fd)
{
	return -1;
}

int KERNEL_SECTION(lseek) lseek(int fd, int offset, int whence)
{
	return -1;
}

void *KERNEL_SECTION(sbrk) sbrk(int incr)
{
	int status;
	int current;
	char *next;
	void *old;
	GET_STATUS(status);
	status &= 0x10000;
	if (status) {
		do {
			DI();
			SYNC_P();
			GET_STATUS(current);
		} while (current & 0x10000);
	}
	next = sdkHeapEnd + incr;
	if ((char *)EndOfHeap() < next) {
		*__errno() = 12;
		if (status) EI();
		return (void *)0xffffffff;
	}
	old = sdkHeapEnd;
	sdkHeapEnd = next;
	if (status) EI();
	return old;
}

int KERNEL_SECTION(fstat) fstat(int fd, kernelStat_t *st)
{
	st->mode = 0x2000;
	st->blocks = 0;
	return 0;
}

int KERNEL_SECTION(getpid) getpid(void)
{
	return 1;
}

int KERNEL_SECTION(stat) stat(const char *name, kernelStat_t *st)
{
	*__errno() = 5;
	return -1;
}

void KERNEL_SECTION(_sceSDC) _sceSDC(unsigned int start, unsigned int end)
{
	__asm__ volatile(DCACHE_RANGE_LOOP("0x14"));
}

void KERNEL_SECTION(SyncDCache) SyncDCache(void *start, void *end)
{
	int status;
	GET_STATUS(status);
	status &= 0x10000;
	if (status) DIntr();
	_sceSDC((unsigned int)start & 0xffffffc0, (unsigned int)end & 0xffffffc0);
	if (status) EIntr();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001274B8);

void KERNEL_SECTION(_sceIDC) _sceIDC(unsigned int start, unsigned int end)
{
	__asm__ volatile(DCACHE_RANGE_LOOP("0x16"));
}

void KERNEL_SECTION(InvalidDCache) InvalidDCache(void *start, void *end)
{
	int status;
	GET_STATUS(status);
	status &= 0x10000;
	if (status) DIntr();
	_sceIDC((unsigned int)start & 0xffffffc0, (unsigned int)end & 0xffffffc0);
	if (status) EIntr();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_001275E8);

int KERNEL_SECTION(QueryIntrContext) QueryIntrContext(void)
{
	int status;
	GET_STATUS(status);
	return (status ^ 1) & 1;
}

int KERNEL_SECTION(DisableIntc) DisableIntc(int channel)
{
	int status;
	int result;
	GET_STATUS(status);
	status &= 0x10000;
	if (status) DIntr();
	result = _DisableIntc(channel);
	SYNC();
	if (status) EIntr();
	return result;
}

int KERNEL_SECTION(EnableIntc) EnableIntc(int channel)
{
	int status;
	int result;
	GET_STATUS(status);
	status &= 0x10000;
	if (status) DIntr();
	result = _EnableIntc(channel);
	SYNC();
	if (status) EIntr();
	return result;
}

int KERNEL_SECTION(DisableDmac) DisableDmac(int channel)
{
	int status;
	int result;
	GET_STATUS(status);
	status &= 0x10000;
	if (status) DIntr();
	result = _DisableDmac(channel);
	SYNC();
	if (status) EIntr();
	return result;
}

int KERNEL_SECTION(EnableDmac) EnableDmac(int channel)
{
	int status;
	int result;
	GET_STATUS(status);
	status &= 0x10000;
	if (status) DIntr();
	result = _EnableDmac(channel);
	SYNC();
	if (status) EIntr();
	return result;
}

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

int KERNEL_SECTION(iWakeupThread) iWakeupThread(int threadId)
{
	register int current __asm__("$2");
	int self;
	threadQueue_t *queue;
	int index;
	__asm__ volatile("addiu $3, $0, -47\n\tsyscall" : "=r"(current) : : "$3");
	self = current;
	if (self != threadId) return _iWakeupThread(threadId);
	if ((unsigned int)self >= 0x100 || !sdkThreadId) return -1;
	queue = &sdkThreadQueue;
	index = queue->unk04 & 0x1ff;
	queue->unk04 = index + 1;
	queue->requests[index].command = 0;
	queue->requests[index].threadId = self;
	iSignalSema(sdkThreadSema);
	return self;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00127A00);

int KERNEL_SECTION(DelayThread) DelayThread(int usec)
{
	kernelSemaParam_t sema;
	int id;
	int status;
	int result;
	GET_STATUS(status);
	if (!(status & 0x10000)) return 0x80008008;
	sema.maxCount = 1;
	sema.option = sdkDelayThreadSemaName;
	sema.initCount = 0;
	id = CreateSema(&sema);
	if (id < 0) return 0x80008003;
	result = SetTimerAlarm(TimerUSec2BusClock(0, usec), _DelayThreadHandler, (void *)id);
	if (result < 0) {
		DeleteSema(id);
		return result;
	}
	WaitSema(id);
	DeleteSema(id);
	return 0;
}

int KERNEL_SECTION(StartThread) StartThread(int id, void *arg)
{
	threadStat_t st;
	char *ctx;
	int ret;
	if (QueryIntrContext()) return -1;
	if (!DIntr()) return -1;
	ret = ReferThreadStatus(id, &st);
	if (ret < 0) {
		EIntr();
		return ret;
	}
	if (st.status != 0x10) {
		EIntr();
		return -1;
	}
	ctx = st.stack + st.stackSize - 0x2a0;
	/* Clear the saved thread context, then seed $a0 and the low words of the saved $gp..$ra. */
	__asm__ volatile(
		".irp off,0x0,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90,0xa0,0xb0,0xc0,0xd0,0xe0,0xf0,0x100,0x110,0x120,0x130,0x140,0x150,0x160,0x170,0x180,0x190,0x1a0,0x1b0,0x200,0x210,0x220,0x230,0x240,0x250,0x260,0x270\n"
		"\tsq $0, \\off(%0)\n"
		".endr\n"
		"\tsll $8, %1, 0\n"
		"\tsd $8, 0x40(%0)\n"
		"\tlw $8, 0x1c0(%0)\n"
		"\tsd $8, 0x1c0(%0)\n"
		"\tsd $0, 0x1c8(%0)\n"
		"\tlw $8, 0x1d0(%0)\n"
		"\tsd $8, 0x1d0(%0)\n"
		"\tsd $0, 0x1d8(%0)\n"
		"\tlw $8, 0x1e0(%0)\n"
		"\tsd $8, 0x1e0(%0)\n"
		"\tsd $0, 0x1e8(%0)\n"
		"\tlw $8, 0x1f0(%0)\n"
		"\tsd $8, 0x1f0(%0)\n"
		"\tsd $0, 0x1f8(%0)\n"
		".set noreorder\n.set reorder"
		: : "r"(ctx), "r"(arg) : "$8", "memory");
	EIntr();
	ret = _StartThread(id, arg);
	return ret;
}

int KERNEL_SECTION(_DelayThreadHandler) _DelayThreadHandler(int id, int scheduled, int actual, void *arg)
{
	iSignalSema((int)arg);
	SYNC();
	EI();
	return 0;
}

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

void KERNEL_SECTION(sceSifInitCmd) sceSifInitCmd(void)
{
	int i;
	DIntr();
	if (sdkSifCmdInitialized) {
		EIntr();
		return;
	}
	sdkSifCmdInitialized = 1;
	sdkSifCmd.packetBuffer = (void *)((unsigned int)sdkSifCmdPacketBuffer | 0x20000000);
	sdkSifCmd.unk04 = (void *)((unsigned int)sdkSifCmdDataBuffer | 0x20000000);
	sdkSifCmd.sysCount = 32;
	sdkSifCmd.iopBuffer = 0;
	sdkSifCmd.sysHandlers = sdkSifCmdSysHandlers;
	sdkSifCmd.usrHandlers = 0;
	sdkSifCmd.usrCount = 0;
	sdkSifCmd.sregs = sdkSifSreg;
	for (i = 0; i < 32; i++) {
		sdkSifCmdSysHandlers[i].func = 0;
		/* Int views keep retail's store order: the alias class decides what GCC may reorder. */
		*(int *)&sdkSifCmdSysHandlers[i].data = 0;
	}
	for (i = 31; i >= 0; i--) sdkSifSreg[i] = 0;
	i = 0x20;
	sdkSifCmdSysHandlers[0].func = _change_addr;
	*(int *)&sdkSifCmdSysHandlers[1].data = (int)&sdkSifCmd;
	*(int *)&sdkSifCmdSysHandlers[0].data = (int)&sdkSifCmd;
	sdkSifCmdSysHandlers[1].func = _set_sreg;
	EIntr();
	FlushCache(0);
	if (*(volatile unsigned int *)0x1000e010 & i) *(volatile unsigned int *)0x1000e010 = i;
	if (!(*(volatile unsigned int *)0x1000c000 & 0x100)) sceSifSetDChain();
	sdkSifCmdHandlerId = AddDmacHandler(5, _sceSifCmdIntrHdlr, 0);
	EnableDmac(5);
	sdkSifCmd.iopBuffer = (void *)sceSifGetReg(0x80000000);
	if (sdkSifCmd.iopBuffer) {
		sdkSifCmdInitPacket.addr = sdkSifCmdPacketBuffer;
		sceSifSendCmd(0x80000000, &sdkSifCmdInitPacket, 0x14, 0, 0, 0);
		return;
	}
	while (!(sceSifGetReg(4) & 0x20000)) {}
	sdkSifCmd.iopBuffer = (void *)sceSifGetReg(2);
	sceSifSetReg(0x80000000, (unsigned int)sdkSifCmd.iopBuffer);
	sceSifSetReg(0x80000001, (unsigned int)&sdkSifCmd);
	sdkSifCmdInitPacket.addr = sdkSifCmdPacketBuffer;
	sdkSifCmdInitPacket.header[3] = 0;
	sceSifSendCmd(0x80000002, &sdkSifCmdInitPacket, 0x14, 0, 0, 0);
}

void KERNEL_SECTION(sceSifExitCmd) sceSifExitCmd(void)
{
	DisableDmac(5);
	RemoveDmacHandler(5, sdkSifCmdHandlerId);
	sdkSifCmdInitialized = 0;
}

void KERNEL_SECTION(sceSifAddCmdHandler) sceSifAddCmdHandler(int cid, void *func, void *data)
{
	int gp, i;
	if (cid < 0) {
		i = cid & 0x7fffffff;
		sdkSifCmd.sysHandlers[i].func = func;
		sdkSifCmd.sysHandlers[i].data = data;
		GET_GP_MEM(gp);
		sdkSifCmd.sysHandlers[i].gp = gp;
	} else {
		sdkSifCmd.usrHandlers[cid].func = func;
		sdkSifCmd.usrHandlers[cid].data = data;
		GET_GP_MEM(gp);
		sdkSifCmd.usrHandlers[cid].gp = gp;
	}
}

void KERNEL_SECTION(sceSifRemoveCmdHandler) sceSifRemoveCmdHandler(int cid)
{
	if (cid < 0) sdkSifCmd.sysHandlers[cid & 0x7fffffff].func = 0;
	else sdkSifCmd.usrHandlers[cid].func = 0;
}

unsigned int KERNEL_SECTION(_sceSifSendCmd) _sceSifSendCmd(int cid, int mode, sifCmdHeader_t *packet, int packetSize, void *src, void *dest, int size)
{
	sifCmdDma_t dma[2];
	int count;
	if ((unsigned int)(packetSize - 0x10) > 0x60) return 0;
	count = 0;
	if (size > 0) {
		count = 1;
		packet->dsize = size;
		dma[0].src = (int)src;
		dma[0].dest = (int)dest;
		packet->dest = dest;
		dma[0].size = size;
		dma[0].attr = 0;
		if (mode & 4) sceSifWriteBackDCache(src, size);
	} else {
		packet->dsize = 0;
		packet->dest = 0;
	}
	dma[count].src = (int)packet;
	dma[count].dest = (int)sdkSifCmd.iopBuffer;
	dma[count].size = packetSize;
	packet->cid = cid;
	packet->psize = packetSize;
	dma[count].attr = 0x44;
	sceSifWriteBackDCache(packet, packetSize);
	count++;
	if (mode & 1) return isceSifSetDma((sifDmaTransfer_t *)dma, count);
	return sceSifSetDma((sifDmaTransfer_t *)dma, count);
}

int KERNEL_SECTION(sceSifSendCmd) sceSifSendCmd(int cid, void *packet, int size, void *src, void *dest, int length)
{
	return _sceSifSendCmd(cid, 0, packet, size, src, dest, length);
}

int KERNEL_SECTION(isceSifSendCmd) isceSifSendCmd(int cid, void *packet, int size, void *src, void *dest, int length)
{
	return _sceSifSendCmd(cid, 1, packet, size, src, dest, length);
}

/* $2 is not written; the clobber only keeps the new $gp out of it, as retail allocates it (fake match). */
static inline int changeGpLoad(int gp)
{
	int old;
	__asm__ volatile("move %0, $28\n\tmove $28, %1" : "=&r"(old) : "r"(gp) : "memory", "$2");
	return old;
}
static inline void cmdQcopy(sifQword *to, sifQword *from, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		to[i] = *from++;
	}
}
int KERNEL_SECTION(_sceSifCmdIntrHdlr) _sceSifCmdIntrHdlr(void)
{
	sifQword buf[7];
	sifCmdData_t *cmd = &sdkSifCmd;
	volatile sifCmdIntrPkt_t *src = cmd->packetBuffer;
	int size = src->size;
	sifQword *from, *to;
	int old;
	void (*func)(void *, void *);
	sifCmdHandler_t *h;
	int gp;
	void *data;
	if (!size) return 0;
	size = (size + 15) / 16;
	src->size = 0;
	cmdQcopy(buf, (sifQword *)src, size);
	isceSifSetDChain();
	if (((volatile sifCmdIntrPkt_t *)buf)->cid < 0) {
		size = ((volatile sifCmdIntrPkt_t *)buf)->cid & 0x7fffffff;
		if (size < cmd->sysCount) {
			func = cmd->sysHandlers[size].func;
			if (func) {
				gp = cmd->sysHandlers[size].gp; old = changeGpLoad(gp);
				h = cmd->sysHandlers; data = h[size].data; func(buf, data);
				changeGp(old);
			}
		}
	} else {
		size = ((volatile sifCmdIntrPkt_t *)buf)->cid;
		if (size < cmd->usrCount) {
			func = cmd->usrHandlers[size].func;
			if (func) {
				gp = cmd->usrHandlers[size].gp; old = changeGpLoad(gp);
				h = cmd->usrHandlers; data = h[size].data; func(buf, data);
				changeGp(old);
			}
		}
	}
	SYNC();
	EI();
	return 0;
}

void KERNEL_SECTION(sceSifWriteBackDCache) sceSifWriteBackDCache(void *addr, int size)
{
	__asm__ volatile(
		".set noreorder\n"
		"\tlui $25, 0xffff\n"
		"\tori $25, $25, 0xffc0\n"
		"\tblez $5, 9f\n"
		"\taddu $10, $4, $5\n"
		"\tand $8, $4, $25\n"
		"\taddiu $10, $10, -1\n"
		"\tand $9, $10, $25\n"
		"\tsubu $10, $9, $8\n"
		"\tsrl $11, $10, 6\n"
		"\taddiu $11, $11, 1\n"
		"\tandi $9, $11, 7\n"
		"\tbeqz $9, 2f\n"
		"\tsrl $10, $11, 3\n"
		"1:\n"
		"\tsync\n"
		"\tcache 0x18, 0x0($8)\n"
		"\tsync\n"
		"\tnop\n"
		"\taddiu $9, $9, -1\n"
		"\tbgtz $9, 1b\n"
		"\taddiu $8, $8, 0x40\n"
		"2:\n"
		"\tbeqz $10, 9f\n"
		"3:\n"
		"\taddiu $10, $10, -1\n"
		"\tsync\n"
		"\tcache 0x18, 0x0($8)\n"
		"\tsync\n"
		"\tcache 0x18, 0x40($8)\n"
		"\tsync\n"
		"\tcache 0x18, 0x80($8)\n"
		"\tsync\n"
		"\tcache 0x18, 0xc0($8)\n"
		"\tsync\n"
		"\tcache 0x18, 0x100($8)\n"
		"\tsync\n"
		"\tcache 0x18, 0x140($8)\n"
		"\tsync\n"
		"\tcache 0x18, 0x180($8)\n"
		"\tsync\n"
		"\tcache 0x18, 0x1c0($8)\n"
		"\tsync\n"
		"\tbgtz $10, 3b\n"
		"\taddiu $8, $8, 0x200\n"
		"9:\n"
		".set reorder");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_00129D8C);

void KERNEL_SECTION(sceSifInitRpc) sceSifInitRpc(int mode)
{
	sifRpcInitPkt_t *packet;
	DIntr();
	if (sdkSifRpcInitialized) {
		EIntr();
		return;
	}
	sdkSifRpcInitialized = 1;
	EIntr();
	sceSifInitCmd();
	DIntr();
	sdkRpcPool.packets = (sifRpcPkt_t *)((unsigned int)sdkRpcPackets | 0x20000000);
	sdkRpcPool.count = 32;
	sdkRpcPool.unk0C = 0;
	sdkRpcPool.unk10 = 0;
	sdkRpcPool.recvBuffers = (char *)((unsigned int)sdkRpcRecvBuffers | 0x20000000);
	sdkRpcPool.recvCount = 32;
	sdkRpcPool.fixed = (char *)((unsigned int)sdkRpcFixedPackets | 0x20000000);
	sdkRpcPool.fixedCount = 32;
	sdkRpcPool.index = 0;
	sdkRpcPool.pid = 1;
	sceSifAddCmdHandler(0x80000008, _request_end, &sdkRpcPool);
	sceSifAddCmdHandler(0x80000009, _request_bind, &sdkRpcPool);
	sceSifAddCmdHandler(0x8000000a, _request_call, &sdkRpcPool);
	sceSifAddCmdHandler(0x8000000c, _request_rdata, &sdkRpcPool);
	EIntr();
	if (sceSifGetReg(0x80000002)) return;
	packet = &sdkRpcPackets[1];
	packet->opt = 1;
	sceSifSendCmd(0x80000002, packet, 0x10, 0, 0, 0);
	while (!sceSifGetSreg(0)) {}
	sceSifSetReg(0x80000002, 1);
}

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

void KERNEL_SECTION(_request_end) _request_end(sifRpcEndPkt_t *pkt, void *data)
{
	sifRpcEndClient_t *c;
	int old;
	switch (pkt->cid) {
	case 0x8000000a:
		c = pkt->client;
		if (c->endFunc) {
			old = changeGp(c->gp);
			c->endFunc(c->endParam);
			changeGp(old);
		}
		break;
	case 0x80000009:
		c = pkt->client;
		c->server = pkt->server;
		c->buffer = pkt->buffer;
		break;
	case 0x8000000c:
		break;
	}
	c = pkt->client;
	if (c->sema >= 0) iSignalSema(c->sema);
	_sceRpcFreePacket(c->packet);
	c->packet = 0;
}

int KERNEL_SECTION(_alarm_rdata) _alarm_rdata(int id, int a1, int a2, sifRpcAlarm_t *data)
{
	return isceSifSendCmd(0x80000008, data, 0x40, data->src, data->dest, data->size) ? 0 : 0x800;
}

void KERNEL_SECTION(_request_rdata) _request_rdata(sifRpcReqPkt_t *request, void *rpc)
{
	sifRpcReqPkt_t *packet;
	void *paddr, *client;
	if (request->mode & 4) packet = _sceRpcGetFPacket2(rpc, request->mode >> 16);
	else packet = _sceRpcGetFPacket(rpc);
	paddr = request->paddr;
	client = request->client;
	packet->paddr = paddr;
	packet->client = client;
	packet->cid = (void *)0x8000000c;
	packet->arg24 = request->cid;
	packet->arg28 = request->arg24;
	packet->arg2C = request->arg28;
	if (!isceSifSendCmd(0x80000008, packet, 0x40, request->cid, request->arg24, (int)request->arg28))
		iSetTimerAlarm(0x800, _alarm_rdata, packet);
}

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

void KERNEL_SECTION(_request_bind) _request_bind(sifRpcReqPkt_t *request, void *rpc)
{
	sifRpcServerHead_t *server;
	sifRpcReqPkt_t *packet = _sceRpcGetFPacket(rpc);
	void *client, *paddr;
	paddr = request->paddr;
	client = request->client;
	packet->client = client;
	packet->paddr = paddr;
	packet->cid = (void *)0x80000009;
	server = _search_svdata((int)request->cid, rpc);
	if (!server) {
		packet->arg24 = 0;
		packet->arg28 = 0;
	} else {
		packet->arg24 = server;
		packet->arg28 = server->buffer;
	}
	if (!isceSifSendCmd(0x80000008, packet, 0x40, 0, 0, 0))
		iSetTimerAlarm(0x800, _alarm_bind, packet);
}

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

void KERNEL_SECTION(_request_call) _request_call(sifRpcCallReq_t *request, void *data)
{
	sifRpcCallServer_t *server = request->server;
	sifRpcCallQueue_t *queue = server->base;
	int paddr, client;
	if (!queue->start) queue->start = (int)server;
	else ((sifRpcCallServer_t *)queue->end)->link = (int)server;
	queue->end = (int)server;
	paddr = request->paddr;
	client = request->client;
	server->pktAddr = paddr;
	server->client = client;
	server->rpcNumber = request->rpcNumber;
	server->size = request->sendSize;
	server->recvBuf = request->recv;
	server->rsize = request->recvSize;
	server->rmode = request->rmode;
	server->rid = request->mode;
	if (queue->threadId >= 0 && !queue->active) iWakeupThread(queue->threadId);
}

int KERNEL_SECTION(sceSifCallRpc) sceSifCallRpc(sifRpcCallClient_t *client, int rpc, int mode, void *send, int ssize, void *recv, int rsize, void *endFunc, void *endParam)
{
	int gp;
	kernelSemaParam_t param;
	sifRpcCallPkt_t *packet = (sifRpcCallPkt_t *)_sceRpcGetPacket(&sdkRpcPool);
	if (!packet) return -1;
	client->endParam = endParam;
	client->rpcId = packet->pid;
	client->packet = packet;
	client->endFunc = endFunc;
	GET_GP(gp);
	client->gp = gp;
	packet->rpcNumber = rpc;
	packet->sendSize = ssize;
	packet->recv = (int)recv;
	packet->recvSize = rsize;
	packet->paddr = (int)packet;
	packet->server = client->server;
	packet->client = (int)client;
	if (!(mode & 2)) {
		if (send == recv) sceSifWriteBackDCache(send, ssize < rsize ? rsize : ssize);
		else {
			if (ssize > 0) sceSifWriteBackDCache(send, ssize);
			if (rsize > 0) sceSifWriteBackDCache(recv, rsize);
		}
	}
	if (mode & 1) {
		if (!endFunc) packet->rmode = 0;
		else packet->rmode = 1;
		client->sema = -1;
		if (sceSifSendCmd(0x8000000a, packet, 0x40, send, (void *)client->buffer, ssize)) return 0;
		_sceRpcFreePacket((sifRpcPacket_t *)packet);
		return -2;
	}
	param.initCount = 0;
	param.option = sdkRpcCallSemaName;
	param.maxCount = 1;
	client->sema = CreateSema(&param);
	if (client->sema < 0) {
		_sceRpcFreePacket((sifRpcPacket_t *)packet);
		return -3;
	}
	packet->rmode = 1;
	if (!sceSifSendCmd(0x8000000a, packet, 0x40, send, (void *)client->buffer, ssize)) {
		DeleteSema(client->sema);
		_sceRpcFreePacket((sifRpcPacket_t *)packet);
		return -2;
	}
	WaitSema(client->sema);
	DeleteSema(client->sema);
	return 0;
}

int KERNEL_SECTION(sceSifCheckStatRpc) sceSifCheckStatRpc(volatile sifRpcClient_t *client)
{
	volatile sifRpcMsg_t *packet = client->packet;
	if (!packet) goto no;
	if (client->rpcId != packet->pid) goto no;
	if (packet->mode & 1) goto yes;
no:
	return 0;
yes:
	return 1;
}

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

void KERNEL_SECTION(_sceFs_Poff_Intr) _sceFs_Poff_Intr(void *pkt, fsPoffData_t *d)
{
	if (d->cb) {
		void *old;
		LOAD_GP(old, sdkFsPoffGp);
		d->cb(d->arg);
		SET_GP(old);
	}
	SYNC();
	EI();
}

int KERNEL_SECTION(sceFsInit) sceFsInit(void)
{
	fsIob_t *iob;
	fsVersion_t version;
	fsPoffData_t *poff;
	int intr, i;
	poff = &sdkFsPoffData;
	sceSifInitRpc(0);
	poff->cb = 0;
	poff->arg = 0;
	intr = DIntr();
	sceSifAddCmdHandler(0x80000011, _sceFs_Rcv_Intr, sdkFsRcvData);
	sceSifAddCmdHandler(0x80000013, _sceFs_Poff_Intr, poff);
	if (intr) EIntr();
	while (1) {
		if (sceSifBindRpc((sifRpcClient_t *)sdkFsClient, 0x80000001, 0) < 0) return -22;
		if (sdkFsClient[9]) break;
		i = 0x100000;
		while (--i != -1) {}
	}
	_sceFsIobSemaMK();
	WaitSema(sdkFsIobSema);
	for (iob = sdkFsIob; iob < &sdkFsIob[32]; iob++) iob->mode = 0;
	SignalSema(sdkFsIobSema);
	sdkFsInitRequest.buffer = sdkFsBuffer;
	sdkFsInitRequest.end = sdkFsBuffer + 0x440;
	if (sceFsSifCallRpc(sdkFsClient, 0xff, 0, &sdkFsInitRequest, 8, sdkFsReceive, 8, 0, 0, 0) < 0) return 0xfffeffff;
	*(fsVersion_t *)sdkFsResetFlags = *(fsVersion_t *)((unsigned int)sdkFsReceive | 0x20000000);
	version = *(fsVersion_t *)((unsigned int)(sdkFsReceive + 1) | 0x20000000);
	sdkFsIsNew = *(int *)&version == 2;
	sdkFsInitialized = 1;
	return 0;
}

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

int KERNEL_SECTION(sceLseek) sceLseek(int fd, int offset, int whence)
{
	fsRwRequest_t *arg = &sdkFsRequest.rw;
	kernelSemaParam_t param;
	int result;
	fsIob_t *iob = get_iob(fd);
	int mode, async, sema, ret;
	_sceFsWaitS(4);
	if (!sdkFsInitialized || !iob || !(mode = iob->mode)) {
		_sceFsSigSema();
		return -9;
	}
	arg->fd = iob->unk00;
	arg->arg[0] = offset;
	arg->arg[1] = whence;
	arg->arg[2] = iob - sdkFsIob;
	param.maxCount = 1;
	param.option = sdkFsLseekSemaName;
	param.initCount = 0;
	async = mode & 0x8000;
	sema = CreateSema(&param);
	arg->result = &result;
	arg->resultSize = 4;
	sdkFsRequest.rw.sema = sema;
	if (async) {
		int i;
		WaitSema(sdkFsIobSema2);
		i = 0;
		/* Always false: combine folds the tests, which orders the mode writes and register choice as in retail; the stores never run or appear in the output (fake match). */
		if ((mode & 0x4000) > 0x4000) {
			arg->sema = 0;
			arg->result = 0;
			arg->resultSize = 0;
			arg->fd = 0;
			sdkFsIobSema2 = 0;
		}
		mode = async;
		for (; i < 32; i++) {
			if (sdkFsAsyncSema[i] == -1) {
				sdkFsAsyncSema[i] = arg->sema;
				arg->sema = -arg->sema;
				break;
			}
		}
		SignalSema(sdkFsIobSema2);
	} else {
		if ((mode & 0x4000) > 0x4000) {
			arg->sema = 0;
			arg->result = 0;
			arg->resultSize = 0;
		}
		mode = 0;
	}
	if (sceFsSifCallRpc(sdkFsClient, 4, 0, &sdkFsRequest, 0x1c, sdkFsReceive, 4, 0, 0, mode) < 0) {
		DeleteSema(sema);
		_sceFsSigSema();
		return -11;
	}
	ret = *(int *)((unsigned int)sdkFsReceive | 0x20000000);
	_sceFsSigSema();
	if (!ret) {
		DeleteSema(sema);
		return -11;
	}
	if (mode) {
		DeleteSema(sema);
		return 0;
	}
	WaitSema(sema);
	DeleteSema(sema);
	return result;
}

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

SYSCALL_STUB(Copy, 0x5a);

int KERNEL_SECTION(kCopy) kCopy(unsigned int *dst, unsigned int *src, unsigned int size)
{
	unsigned int i;
	size >>= 2;
	for (i = 0; i < size; i++) *dst++ = *src++;
	return 0;
}

SYSCALL_STUB(GetEntryAddress, 0x5b);

SYSCALL_STUB(setup, 0x74);

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

SYSCALL_STUB(_SetTLBEntry, 0x56);

int KERNEL_SECTION(InitTLB) InitTLB(void)
{
	int ret;
	if (GetMemorySize() == 0x2000000) ret = InitTLB32MB();
	else ret = _InitTLB();
	return ret;
}

int KERNEL_SECTION(InitTLB32MB) InitTLB32MB(void)
{
	register int i __asm__("$25");
	int n;
	tlbEntry_t *e;

	kprintf(sdkTlbInfoMsg, sdkTlbInfo.kernelCount - 1, sdkTlbInfo.kernelCount,
		sdkTlbInfo.kernelCount + sdkTlbInfo.defaultCount - 1,
		sdkTlbInfo.kernelCount + sdkTlbInfo.defaultCount,
		sdkTlbInfo.kernelCount + sdkTlbInfo.defaultCount + sdkTlbInfo.extendedCount - 1);
	__asm__ volatile("mtc0 $0, $6");
	__asm__ volatile("sync.p");
	n = sdkTlbInfo.kernelCount;
	i = 0;
	if (n > 48) {
		kprintf(sdkTlbOverflow1Msg);
		Exit(1);
	}
	e = sdkTlbInfo.kernel;
	for (; i < n; i++, e++) {
		_SetTLBEntry(i, e->pageMask, e->entryHi, e->entryLo0, e->entryLo1);
	}
	n = i + sdkTlbInfo.defaultCount;
	if (n > 48) {
		kprintf(sdkTlbOverflow2Msg);
		Exit(1);
	}
	e = sdkTlbInfo.def;
	for (; i < n; i++, e++) {
		_SetTLBEntry(i, e->pageMask, e->entryHi, e->entryLo0, e->entryLo1);
	}
	sdkTlbInfo.wired = i;
	__asm__ volatile("mtc0 %0, $6" : : "r"(i));
	__asm__ volatile("sync.p");
	if (sdkTlbInfo.extendedCount > 0) {
		n = i + sdkTlbInfo.extendedCount;
		if (n > 48) {
			kprintf(sdkTlbOverflow3Msg);
			Exit(1);
		}
		e = sdkTlbInfo.extended;
		for (; i < n; i++, e++) {
			_SetTLBEntry(i, e->pageMask, e->entryHi, e->entryLo0, e->entryLo1);
		}
	}
	{
		int j = i;
		unsigned int addr;
		i <<= 13;
		if (j < 48) {
			addr = i + 0xe0000000;
			do {
				_SetTLBEntry(j, 0, addr, 0, 0);
				j++;
				addr += 0x2000;
			} while (j < 48);
		}
	}
	return i;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D28C);

void KERNEL_SECTION(_kExitTLBHandler) _kExitTLBHandler(void)
{
	/*
	 * D18: hand-written exception return; it never reaches a function epilogue. The final section
	 * switch sends the j $31 and nop GCC always appends to a discarded section, because retail has
	 * neither, and the last word is 0xcd padding.
	 */
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tmfc0 $1, $12\n"
		"\taddiu $26, $0, -0x1c\n"
		"\tand $1, $1, $26\n"
		"\tmtc0 $1, $12\n"
		"\tsync.p\n"
		"\tlui $2, %hi(sdkTlbExitEpc)\n"
		"\tlw $2, %lo(sdkTlbExitEpc)($2)\n"
		"\tmtc0 $2, $14\n"
		"\tsync.p\n"
		"\tlui $2, %hi(sdkTlbExitHi)\n"
		"\tld $2, %lo(sdkTlbExitHi)($2)\n"
		"\tmthi $2\n"
		"\tlui $2, %hi(sdkTlbExitHi1)\n"
		"\tld $2, %lo(sdkTlbExitHi1)($2)\n"
		"\tmthi1 $2\n"
		"\tlui $2, %hi(sdkTlbExitLo)\n"
		"\tld $2, %lo(sdkTlbExitLo)($2)\n"
		"\tmtlo $2\n"
		"\tlui $2, %hi(sdkTlbExitLo1)\n"
		"\tld $2, %lo(sdkTlbExitLo1)($2)\n"
		"\tmtlo1 $2\n"
		"\tlui $2, %hi(sdkTlbExitSa)\n"
		"\tld $2, %lo(sdkTlbExitSa)($2)\n"
		"\tmtsa $2\n"
		"\tsync.p\n"
		"\tlui $26, %hi(sdkTlbExitRegs)\n"
		"\taddiu $26, $26, %lo(sdkTlbExitRegs)\n"
		"\tlq $1, 0x10($26)\n"
		"\tlq $2, 0x20($26)\n"
		"\tlq $3, 0x30($26)\n"
		"\tlq $4, 0x40($26)\n"
		"\tlq $5, 0x50($26)\n"
		"\tlq $6, 0x60($26)\n"
		"\tlq $7, 0x70($26)\n"
		"\tlq $8, 0x80($26)\n"
		"\tlq $9, 0x90($26)\n"
		"\tlq $10, 0xa0($26)\n"
		"\tlq $11, 0xb0($26)\n"
		"\tlq $12, 0xc0($26)\n"
		"\tlq $13, 0xd0($26)\n"
		"\tlq $14, 0xe0($26)\n"
		"\tlq $15, 0xf0($26)\n"
		"\tlq $16, 0x100($26)\n"
		"\tlq $17, 0x110($26)\n"
		"\tlq $18, 0x120($26)\n"
		"\tlq $19, 0x130($26)\n"
		"\tlq $20, 0x140($26)\n"
		"\tlq $21, 0x150($26)\n"
		"\tlq $22, 0x160($26)\n"
		"\tlq $23, 0x170($26)\n"
		"\tlq $24, 0x180($26)\n"
		"\tlq $25, 0x190($26)\n"
		"\tlq $28, 0x1c0($26)\n"
		"\tlq $29, 0x1d0($26)\n"
		"\tlq $30, 0x1e0($26)\n"
		"\tlq $31, 0x1f0($26)\n"
		"\tmfc0 $26, $12\n"
		"\tori $26, $26, 0x13\n"
		"\tmtc0 $26, $12\n"
		"\tsync.p\n"
		"\teret\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tlui $1, 0\n"
		"\taddu $1, $1, $2\n"
		"\tlw $1, 0($1)\n"
		"\tlui $29, 0\n"
		"\tjalr $1\n"
		"\taddiu $29, $29, 0x1000\n"
		"\tbreak 1023, 1023\n"
		"\t.p2align 3, 0xcd\n"
		".set at\n.set reorder\n"
		"\t.section .kernel_kExitTail,\"ax\",@progbits");
}

int KERNEL_SECTION(DIntr) DIntr(void)
{
	int status, result;
	__asm__ volatile("mfc0 %0, $12\n\tlui $2, 1\n\tand %0, %0, $2" : "=r"(status) : : "$2");
	result = status != 0;
	if (status) {
		__asm__ volatile(
			".set noreorder\n"
			".p2align 3\n"
			"1:\n"
			"\tdi\n"
			"\tsync.p\n"
			"\tmfc0 $2, $12\n"
			"\tlui $3, 1\n"
			"\tand $2, $2, $3\n"
			"\tnop\n"
			"\tnop\n"
			"\tbnez $2, 1b\n"
			"\tnop\n"
			".set reorder"
			: : : "$2", "$3");
	} else result = 0;
	return result;
}

int KERNEL_SECTION(EIntr) EIntr(void)
{
	int status;
	GET_STATUS(status);
	status &= 0x10000;
	EI();
	return status != 0;
}

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

SYSCALL_STUB(FindAddress, 0x83);

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

SYSCALL_STUB(setup___dupe2, 0x74);

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

SYSCALL_STUB(setup___dupe3, 0x74);

SYSCALL_STUB(Copy___dupe2, 0x5a);

int KERNEL_SECTION(kCopy___dupe3) kCopy___dupe3(unsigned int *dst, unsigned int *src, unsigned int size)
{
	unsigned int i;
	size >>= 2;
	for (i = 0; i < size; i++) *dst++ = *src++;
	return 0;
}

SYSCALL_STUB(GetEntryAddress___dupe2, 0x5b);

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

SYSCALL_STUB(Copy___dupe3, 0x5a);

int KERNEL_SECTION(kCopy___dupe4) kCopy___dupe4(unsigned char *dst, unsigned char *src, unsigned int size)
{
	unsigned int i;
	for (i = 0; i < size; i++) *dst++ = *src++;
	return 0;
}

SYSCALL_STUB(setup___dupe4, 0x74);

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

SYSCALL_STUB(setup___dupe5, 0x74);

SYSCALL_STUB(Copy___dupe4, 0x5a);

int KERNEL_SECTION(kCopy___dupe5) kCopy___dupe5(unsigned int *dst, unsigned int *src, unsigned int size)
{
	unsigned int i;
	size >>= 2;
	for (i = 0; i < size; i++) *dst++ = *src++;
	return 0;
}

SYSCALL_STUB(GetEntryAddress___dupe3, 0x5b);

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

void KERNEL_SECTION(SetT2) SetT2(volatile int *address, int value)
{
	int status;
	int current;
	GET_STATUS(status);
	status &= 0x10000;
	if (status) {
		do {
			__asm__ volatile("di\n\tsync.p\n\tmfc0 %0, $12" : "=r"(current));
		} while (current & 0x10000);
	}
	__asm__ volatile("mfc0 %0, $12\n\tsync.p" : "=r"(current));
	current = ((current | 6) ^ 2) | status;
	__asm__ volatile("mtc0 %0, $12\n\tsync.p" : : "r"(current));
	*address = value;
	__asm__ volatile(".set noreorder\n\tmtc0 $31, $30\n\tsync.p\n\teret\n\t.set reorder");
}

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

static inline unsigned long timerNow(void)
{
	unsigned int count = *(volatile unsigned int *)0x10001000;
	unsigned int mode = *(volatile unsigned int *)0x10001010;
	if (mode & 0x800) {
		*(volatile long *)&sdkTimer.highCount = *(volatile long *)&sdkTimer.highCount + 1;
		SetT2_MODE(mode & ~0x400);
		count = *(volatile unsigned int *)0x10001000;
	}
	return (((unsigned long)*(volatile long *)&sdkTimer.highCount << 16) | count) << ((mode & 3) * 4);
}

int KERNEL_SECTION(cbTimerHandler) cbTimerHandler(int cause, void *arg, void *common)
{
	timerCounter_t *counter, *next;
	unsigned long now, time, ret, late;
	if (*(volatile unsigned int *)0x10001010 & 0x400) {
		counter = sdkTimer.alarmList;
		if (counter) {
			do {
				time = counter->compare + counter->base - counter->total;
				now = timerNow();
				if (now < time) break;
				next = UnlinkAlarm(counter);
				late = now + counter->total - counter->base;
				sdkTimer.systemId = ((int)counter << 4) | counter->key;
				__asm__ volatile("lw $28, %0" : : "m"(counter->gp));
				ret = ((unsigned long (*)(int, unsigned long, unsigned long, void *, void *))counter->handler)(((int)counter << 4) | counter->key, counter->compare, late, counter->arg, common);
				if (ret == 0) {
					counter->mode &= ~2;
				} else if (ret == (unsigned long)-1) {
					counter->key = 0;
					counter->mode = 0;
					counter->next = sdkTimer.freeList;
					sdkTimer.freeList = counter;
					sdkTimer.used--;
				} else {
					if (ret < 0x3999) ret = 0x3999;
					counter->compare += ret;
					InsertAlarm(counter);
				}
				counter = next;
			} while (counter);
		}
	}
	sdkTimer.systemId = -1;
	SetNextComp(timerNow());
	timerNow();
	SYNC();
	EI();
	return 0;
}

/* D18: retail reads the timer through hand-written asm with fixed scratch registers. */
#define READ_TIME(t) __asm__ volatile( \
	".set noreorder\n" \
	"lui $3, 0x1000\n" \
	"lui $4, %%hi(sdkTimer)\n" \
	"ori $3, $3, 0x1000\n" \
	"lwu %0, 0($3)\n" \
	"lw $8, 0x10($3)\n" \
	"ld $10, %%lo(sdkTimer)($4)\n" \
	"andi $9, $8, 0x800\n" \
	"beqz $9, 1f\n" \
	"addiu $9, $0, 2\n" \
	"lwu %0, 0($3)\n" \
	"daddiu $10, $10, 1\n" \
	"1:\n" \
	"andi $8, $8, 3\n" \
	"dsll $10, $10, 16\n" \
	"movz $9, $0, $8\n" \
	"or %0, %0, $10\n" \
	"dsllv $9, $9, $8\n" \
	"dsllv %0, %0, $9\n" \
	".set reorder\n" \
	: "=r"(t) : : "$3", "$4", "$8", "$9", "$10")

unsigned long KERNEL_SECTION(iGetTimerSystemTime) iGetTimerSystemTime(void)
{
	unsigned long t;
	READ_TIME(t);
	return t;
}

unsigned long KERNEL_SECTION(GetTimerSystemTime) GetTimerSystemTime(void)
{
	int intr = DIntr();
	unsigned long t;
	READ_TIME(t);
	if (intr) EIntr();
	return t;
}

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

int KERNEL_SECTION(iSetTimerHandler) iSetTimerHandler(int id, unsigned long compare, void *handler, void *arg)
{
	register int gp __asm__("$28");
	timerCounter_t *counter = (timerCounter_t *)(((unsigned int)id >> 10) << 6);
	if (id < 0 || (id & 0x3ff) != counter->key) return 0x80008002;
	if (sdkTimer.systemId == id) return 0x80000010;
	if (counter->mode & 2) UnlinkAlarm(counter);
	counter->handler = handler;
	if (!handler) {
		counter->mode &= ~2;
	} else {
		counter->mode |= 2;
		counter->compare = compare;
		counter->gp = gp;
		counter->arg = arg;
		if (*(volatile unsigned int *)&counter->mode & 1) InsertAlarm(counter);
	}
	SetNextComp(iGetTimerSystemTime());
	return 0;
}

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

int KERNEL_SECTION(sceSifAddRebootNotifyHandler) sceSifAddRebootNotifyHandler(unsigned int index, void *func, void *data)
{
	sifNotifyHandler_t *table;
	unsigned int count;
	int intr, gp;
	if ((int)index < 0) {
		index &= 0x7fffffff;
		table = sdkRebootNotifySystem;
		count = 32;
	} else {
		table = sdkRebootNotifyHandlers;
		count = sdkRebootNotifyCount;
	}
	if (index >= count) return 0x80000069;
	intr = DIntr();
	table[index].func = func;
	table[index].data = data;
	GET_GP(gp);
	table[index].gp = gp;
	if (intr) EIntr();
	return 0;
}

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

void KERNEL_SECTION(sceSifExecNotifyHandler) sceSifExecNotifyHandler(int system, int arg)
{
	sifNotifyHandler_t *h;
	int n, i, old;
	if (system) {
		h = sdkRebootNotifySystem;
		n = 32;
	} else {
		h = sdkRebootNotifyHandlers;
		n = sdkRebootNotifyCount;
	}
	GET_GP(old);
	for (i = 0; i < n; i++) {
		if (h[i].func) {
			changeGp(h[i].gp);
			((void (*)(int, void *))h[i].func)(arg, h[i].data);
		}
	}
	changeGp(old);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012EE28);
