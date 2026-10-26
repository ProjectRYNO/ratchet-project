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
extern int sdkIopHeapClient[10];
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
extern int sceSifBindRpc(void *, unsigned int, int);
extern void sceSifExitCmd(void);
extern unsigned int sceSifGetReg(unsigned int);
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
extern int sceTtyWrite(const void *, int);
extern int sceTtyRead(void *, int);
extern int *__errno(void);
extern int iSetTimerHandler(int, int, void *, void *);
extern unsigned long iGetTimerSystemTime(void);
extern void SetNextComp(unsigned long);
timerCounter_t *UnlinkAlarm(timerCounter_t *counter);
extern int DelayThread(int);
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceResetttyinit);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", topThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", InitThread);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceTtyHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceTtyWrite);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceTtyRead);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceTtyInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012830C);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", kputchar);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", deci2Putchar);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", serialPutchar);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", ftoi);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", printfloat);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceSnprintf);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", snprintf_char);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", printf_char);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", kprintf_char);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceSnprintf_pf);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSnprintf);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", scePrintf);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", kprintf);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _set_sreg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _change_addr);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifExitCmd);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceRpcGetPacket);

void KERNEL_SECTION(_sceRpcFreePacket) _sceRpcFreePacket(sifRpcPacket_t *packet)
{
	packet->id = 0;
	packet->mode &= ~1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceRpcGetFPacket);

char *KERNEL_SECTION(_sceRpcGetFPacket2) _sceRpcGetFPacket2(sifRpcData_t *rpc, int index)
{
	if (index < 0 || index >= rpc->fixedCount) return _sceRpcGetFPacket(rpc);
	return rpc->fixed + index * 64;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _request_end);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _alarm_rdata);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _request_rdata);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifGetOtherData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _search_svdata);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _alarm_bind);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _request_bind);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifBindRpc);

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

int KERNEL_SECTION(_sceFsWaitS) _sceFsWaitS(void)
{
	_sceFsSemInit();
	WaitSema(sdkFsSema);
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceFsSigSema);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceFs_Poff_Intr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceFsInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _fs_version);

int KERNEL_SECTION(sceFsReset) sceFsReset(void)
{
	sdkFsInitialized = 0;
	memset(sdkFsResetFlags, 0, 4);
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceOpen);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceClose);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceLseek);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceRead);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceWrite);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012BEB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceDevctl);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifInitIopHeap);

void *KERNEL_SECTION(sceSifAllocIopHeap) sceSifAllocIopHeap(int size)
{
	if (sdkIopHeapState < 0) return 0;
	sdkIopHeapSend[0] = size;
	if (sceSifCallRpc(sdkIopHeapClient, 1, 0, sdkIopHeapSend, 4, sdkIopHeapReceive, 4, 0, 0) < 0) return 0;
	return (void *)sdkIopHeapReceive[0];
}

void *KERNEL_SECTION(sceSifAllocSysMemory) sceSifAllocSysMemory(int type, int size, void *addr)
{
	if (sdkIopHeapState < 0) return 0;
	sdkIopHeapSend[0] = size;
	sdkIopHeapSend[1] = type;
	sdkIopHeapSend[2] = (int)addr;
	if (sceSifCallRpc(sdkIopHeapClient, 4, 0, sdkIopHeapSend, 0xc, sdkIopHeapReceive, 4, 0, 0) < 0) return 0;
	return (void *)sdkIopHeapReceive[0];
}

int KERNEL_SECTION(sceSifFreeSysMemory) sceSifFreeSysMemory(void *addr)
{
	if (sdkIopHeapState < 0) return 0;
	sdkIopHeapSend[0] = (int)addr;
	if (sceSifCallRpc(sdkIopHeapClient, 2, 0, sdkIopHeapSend, 4, sdkIopHeapReceive, 4, 0, 0) < 0) return -1;
	return sdkIopHeapReceive[0];
}

int KERNEL_SECTION(sceSifFreeIopHeap) sceSifFreeIopHeap(void *addr)
{
	return sceSifFreeSysMemory(addr);
}

unsigned int KERNEL_SECTION(sceSifQueryMaxFreeMemSize) sceSifQueryMaxFreeMemSize(void)
{
	if (sdkIopHeapState < 0) return 0;
	if (sceSifCallRpc(sdkIopHeapClient, 6, 0, 0, 0, sdkIopHeapReceive, 4, 0, 0) < 0) return 0xffffffff;
	return sdkIopHeapReceive[0];
}

unsigned int KERNEL_SECTION(sceSifQueryTotalFreeMemSize) sceSifQueryTotalFreeMemSize(void)
{
	if (sdkIopHeapState < 0) return 0;
	if (sceSifCallRpc(sdkIopHeapClient, 7, 0, 0, 0, sdkIopHeapReceive, 4, 0, 0) < 0) return 0xffffffff;
	return sdkIopHeapReceive[0];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012C4A8);

int KERNEL_SECTION(_lf_bind) _lf_bind(void)
{
	int i;
	if (sdkLoadFileState < 0) {
		while (1) {
			if (sceSifBindRpc(sdkLoadFileClient, 0x80000006, 0) < 0) return -1;
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _lf_version);

int KERNEL_SECTION(sceSifLoadFileReset) sceSifLoadFileReset(void)
{
	sdkLoadFileState = -1;
	memset(sdkLoadFileFlags, 0, 4);
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _sceSifLoadModuleBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifStopModule);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifResetIop);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifIsAliveIop);

int KERNEL_SECTION(sceSifSyncIop) sceSifSyncIop(void)
{
	if (!(sceSifGetReg(4) & 0x40000)) return 0;
	sceResetttyinit();
	sceSifExecNotifyHandler(1, 1);
	sceSifExecNotifyHandler(0, 1);
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", sceSifRebootIop);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012CF10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", Copy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", kCopy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetEntryAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", setup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", InitTLBFunctions);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _SetTLBEntry);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", InitTLB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", InitTLB32MB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D28C);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _kExitTLBHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", DIntr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", EIntr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", supplement_crt0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D4E8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", kCopy___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", kFindAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", FindAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D578);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", InitSystemCallTableAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", setup___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", _InitSys);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D6E4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", setup___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", Copy___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", kCopy___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetEntryAddress___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", PatchIsNeeded);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", InitExecPS2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012D864);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", Copy___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", kCopy___dupe4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", setup___dupe4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetArg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", TerminateLibrary);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", LoadExecPS2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", Exit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012DA48);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", setup___dupe5);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", Copy___dupe4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", kCopy___dupe5);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", GetEntryAddress___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", InitAlarm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012DB8C);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetT2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetT2_COUNT);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetT2_MODE);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetT2_COMP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", InitTimer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012DD88);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", StartTimerSystemTime);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012DE20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetNextComp);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", iAllocTimerCounter);

int KERNEL_SECTION(AllocTimerCounter) AllocTimerCounter(void)
{
	int interrupts = DIntr();
	int result = iAllocTimerCounter();
	if (interrupts) EIntr();
	return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", iFreeTimerCounter);

int KERNEL_SECTION(FreeTimerCounter) FreeTimerCounter(int id)
{
	int interrupts = DIntr();
	int result = iFreeTimerCounter(id);
	if (interrupts) EIntr();
	return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012E598);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", iStartTimerCounter);

int KERNEL_SECTION(StartTimerCounter) StartTimerCounter(int id)
{
	int interrupts = DIntr();
	int result = iStartTimerCounter(id);
	if (interrupts) EIntr();
	return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", func_0012E6A0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", iSetTimerHandler);

int KERNEL_SECTION(SetTimerHandler) SetTimerHandler(int id, int mode, void *handler, void *arg)
{
	int interrupts = DIntr();
	int result = iSetTimerHandler(id, mode, handler, arg);
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", AlarmHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", SetTimerAlarm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", iSetTimerAlarm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/kernel/libkernel", ReleaseTimerAlarm);

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
