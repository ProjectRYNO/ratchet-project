#include "common.h"
#include "libcdvd.h"

/* Recovered directly from the retail boot instructions; no vendor source. */
#define CD_SECTION(name) __attribute__((section(".cdvd_" #name)))

/* Functions not yet recovered, and original padding words, stay in their own slots. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
	__asm__(".section .cdvd_" #NAME ",\"ax\",@progbits\n" \
		".set noat\n.set noreorder\n" \
		".include \"" FOLDER "/" #NAME ".s\"\n" \
		".set reorder\n.set at\n.text\n")
#endif

/* Semaphore IDs are read through volatile accesses where the retail code reloads them. */
#define CD_VOLATILE(x) (*(volatile int *)&(x))

extern int sdkCdDebug;
extern int sdkCdCallbackThread;
extern int sdkCdScmdCurrent;
extern int sdkCdNcmdCurrent;
extern int sdkCdCallbackSema;
extern int sdkCdNcmdSema;
extern int sdkCdScmdSema;
extern int sdkCdReadSema;
extern volatile int sdkCdNcmdBusy;
extern int sdkCdNcmdBound;
extern int sdkCdScmdBound;
extern volatile int sdkCdBreakStat;
extern cdvdRpcClient_t sdkCdNcmdClient;
extern cdvdRpcClient_t sdkCdScmdClient;
extern int sdkCdNcmdResult[4];
extern int sdkCdScmdResult[4];
extern int sdkCdMmodeArg;
extern int sdkCdMmodeRpc;
extern int sdkCdMmodeSendSize;
extern int sdkCdMmodeRecvSize;
extern const char sdkCdNcmdSemaName[];
extern const char sdkCdScmdSemaName[];
extern const char sdkCdReadSemaName[];
extern const char sdkCdCallbackSemaName[];
extern const char sdkCdNcmdBusyMsg[];
extern const char sdkCdNcmdBindMsg[];
extern const char sdkCdSyncMsg[];
extern const char sdkCdSyncSMsg[];
extern const char sdkCdScmdBusyMsg[];
extern const char sdkCdScmdBindMsg[];
extern int CreateSema(cdvdSemaParam_t *);
extern int DeleteSema(int);
extern int SignalSema(int);
extern int PollSema(int);
extern int DIntr(void);
extern int EIntr(void);
extern void sceSifRemoveCmdHandler(int);
extern void scePrintf(const char *, ...);
extern void sceSifInitRpc(int);
extern int sceSifBindRpc(cdvdRpcClient_t *, unsigned int, int);
extern int sceSifCallRpc(cdvdRpcClient_t *, int, int, void *, int, void *, int, void *, void *);
extern int sceSifCheckStatRpc(cdvdRpcClient_t *);
extern int DelayThread(int);
extern void sceSifWriteBackDCache(void *, int);
int sceCdSync(int mode);
int sceCdSyncS(int mode);
int _sceCd_ncmd_prechk(int command);
int _sceCd_scmd_prechk(int command);
void cmd_sem_init(void);
extern void *sdkCdCallbackFunc;
extern volatile int sdkCdCallbackGp;
extern volatile int sdkCdLastStat;
extern int sdkCdPoffBusy;
extern int sdkCdPoffInit;
extern int iSignalSema(int);
extern int sceSifAddCmdHandler(int, void *, void *);
extern void _sceCd_Poff_Intr(void *, void *);

void *CD_SECTION(sceCdCallback) sceCdCallback(void *func)
{
	register int gp __asm__("$28");
	void *old;
	int intr;
	if (sceCdSync(1)) return 0;
	intr = DIntr();
	old = sdkCdCallbackFunc;
	sdkCdCallbackFunc = func;
	sdkCdCallbackGp = gp;
	if (intr) EIntr();
	return old;
}

void CD_SECTION(_sceCd_cd_callback) _sceCd_cd_callback(volatile int *status)
{
	sdkCdBreakStat = *status;
	sdkCdLastStat = sdkCdBreakStat;
	if (sdkCdBreakStat == 0xb) {
		sdkCdBreakStat = 0;
		sdkCdNcmdBusy = 0;
		return;
	}
	iSignalSema(CD_VOLATILE(sdkCdNcmdSema));
	if (sdkCdCallbackThread && sdkCdCallbackFunc) iSignalSema(CD_VOLATILE(sdkCdCallbackSema));
	else sdkCdNcmdBusy = 0;
	sdkCdBreakStat = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", func_00136EB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", _sceCd_cd_read_intr);

void CD_SECTION(cmd_sem_init) cmd_sem_init(void)
{
	cdvdSemaParam_t param;
	if (sdkCdNcmdSema == -1 || sdkCdScmdSema == -1 || sdkCdReadSema == -1) {
		param.initCount = 1;
		param.maxCount = 1;
		param.option = sdkCdNcmdSemaName;
		CD_VOLATILE(sdkCdNcmdSema) = CreateSema(&param);
		param.option = sdkCdScmdSemaName;
		CD_VOLATILE(sdkCdScmdSema) = CreateSema(&param);
		param.option = sdkCdReadSemaName;
		CD_VOLATILE(sdkCdReadSema) = CreateSema(&param);
		param.initCount = 0;
		param.option = sdkCdCallbackSemaName;
		CD_VOLATILE(sdkCdCallbackSema) = CreateSema(&param);
		sdkCdNcmdBusy = 0;
	}
}

void CD_SECTION(cdvd_exit) cdvd_exit(void)
{
	int intr;
	if (sdkCdCallbackThread) {
		sdkCdBreakStat = -1;
		SignalSema(CD_VOLATILE(sdkCdCallbackSema));
	}
	DeleteSema(CD_VOLATILE(sdkCdNcmdSema));
	DeleteSema(CD_VOLATILE(sdkCdScmdSema));
	DeleteSema(CD_VOLATILE(sdkCdReadSema));
	DeleteSema(CD_VOLATILE(sdkCdCallbackSema));
	intr = DIntr();
	sceSifRemoveCmdHandler(0x80000012);
	if (intr) EIntr();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", sceCdPOffCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", _sceCd_Poff_Intr);

int CD_SECTION(PowerOffCB) PowerOffCB(void)
{
	int intr;
	sdkCdPoffBusy = 1;
	intr = DIntr();
	sceSifAddCmdHandler(0x80000012, _sceCd_Poff_Intr, 0);
	if (intr) EIntr();
	sdkCdPoffBusy = 0;
	sdkCdPoffInit = 1;
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", func_00137248);

int CD_SECTION(_sceCd_ncmd_prechk) _sceCd_ncmd_prechk(int command)
{
	int i;
	cmd_sem_init();
	if (CD_VOLATILE(sdkCdNcmdSema) != PollSema(CD_VOLATILE(sdkCdNcmdSema))) {
		if (sdkCdDebug > 0) scePrintf(sdkCdNcmdBusyMsg, command, sdkCdNcmdCurrent);
		return 0;
	}
	sdkCdNcmdCurrent = command;
	if (sceCdSync(1)) {
		SignalSema(CD_VOLATILE(sdkCdNcmdSema));
		return 0;
	}
	sceSifInitRpc(0);
	if (sdkCdNcmdBound >= 0) return 1;
	while (1) {
		if (sceSifBindRpc(&sdkCdNcmdClient, 0x80000595, 0) < 0) {
			if (sdkCdDebug > 0) scePrintf(sdkCdNcmdBindMsg);
			i = 0x100000;
			while (i--) {}
			continue;
		}
		if (sdkCdNcmdClient.server) break;
		i = 0x100000;
		while (i--) {}
	}
	sdkCdNcmdBound = 0;
	return 1;
}

int CD_SECTION(sceCdNcmdDiskReady) sceCdNcmdDiskReady(void)
{
	int ret;
	if (!_sceCd_ncmd_prechk(2)) return 0;
	if (sceSifCallRpc(&sdkCdNcmdClient, 0xe, 0, 0, 0, sdkCdNcmdResult, 4, 0, 0) < 0) {
		SignalSema(sdkCdNcmdSema);
		return 0;
	}
	ret = *(int *)((unsigned int)sdkCdNcmdResult | 0x20000000);
	SignalSema(sdkCdNcmdSema);
	return ret;
}

int CD_SECTION(sceCdSync) sceCdSync(int mode)
{
	if (!mode) {
		if (sdkCdDebug > 0) scePrintf(sdkCdSyncMsg);
		while (sdkCdNcmdBusy || sceSifCheckStatRpc(&sdkCdNcmdClient)) DelayThread(4000);
		return 0;
	}
	if (sdkCdNcmdBusy || sceSifCheckStatRpc(&sdkCdNcmdClient)) return 1;
	return 0;
}

int CD_SECTION(sceCdSyncS) sceCdSyncS(int mode)
{
	if (!mode) {
		if (sdkCdDebug > 0) scePrintf(sdkCdSyncSMsg);
		while (sceSifCheckStatRpc(&sdkCdScmdClient)) DelayThread(4000);
		return 0;
	}
	return sceSifCheckStatRpc(&sdkCdScmdClient);
}

int CD_SECTION(_sceCd_scmd_prechk) _sceCd_scmd_prechk(int command)
{
	int i;
	cmd_sem_init();
	if (CD_VOLATILE(sdkCdScmdSema) != PollSema(CD_VOLATILE(sdkCdScmdSema))) {
		if (sdkCdDebug > 0) scePrintf(sdkCdScmdBusyMsg, command, sdkCdScmdCurrent);
		return 0;
	}
	sdkCdScmdCurrent = command;
	if (sceCdSyncS(1)) {
		SignalSema(CD_VOLATILE(sdkCdScmdSema));
		return 0;
	}
	sceSifInitRpc(0);
	if (sdkCdScmdBound >= 0) return 1;
	while (1) {
		if (sceSifBindRpc(&sdkCdScmdClient, 0x80000593, 0) < 0) {
			if (sdkCdDebug > 0) scePrintf(sdkCdScmdBindMsg);
			i = 0x100000;
			while (i--) {}
			continue;
		}
		if (sdkCdScmdClient.server) break;
		i = 0x100000;
		while (i--) {}
	}
	sdkCdScmdBound = 0;
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", sceCdInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", sceCdDiskReady_old);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", sceCdDiskReady);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", sceCdRead);

int CD_SECTION(sceCdGetError) sceCdGetError(void)
{
	int result;
	if (!_sceCd_scmd_prechk(3)) return -1;
	if (sceSifCallRpc(&sdkCdScmdClient, 4, 0, 0, 0, sdkCdScmdResult, 4, 0, 0) < 0) {
		SignalSema(sdkCdScmdSema);
		return -1;
	}
	result = *(int *)((unsigned int)sdkCdScmdResult | 0x20000000);
	SignalSema(sdkCdScmdSema);
	return result;
}

int CD_SECTION(sceCdBreak) sceCdBreak(void)
{
	int result;
	if (!_sceCd_scmd_prechk(0x1e)) return 0;
	sdkCdBreakStat = 8;
	if (sceSifCallRpc(&sdkCdScmdClient, 0x16, 0, 0, 0, sdkCdScmdResult, 4, 0, 0) < 0) {
		SignalSema(CD_VOLATILE(sdkCdScmdSema));
		sdkCdBreakStat = 0;
		return 0;
	}
	sdkCdBreakStat = 0;
	result = *(int *)((unsigned int)sdkCdScmdResult | 0x20000000);
	SignalSema(CD_VOLATILE(sdkCdScmdSema));
	return result;
}

int CD_SECTION(sceCdPowerOff) sceCdPowerOff(int *result)
{
	int ret;
	if (!_sceCd_scmd_prechk(0x21)) return 0;
	if (sceSifCallRpc(&sdkCdScmdClient, 0x21, 0, 0, 0, sdkCdScmdResult, 8, 0, 0) < 0) {
		SignalSema(sdkCdScmdSema);
		return 0;
	}
	*result = *(int *)(((unsigned int)sdkCdScmdResult + 4) | 0x20000000);
	ret = *(int *)((unsigned int)sdkCdScmdResult | 0x20000000);
	SignalSema(sdkCdScmdSema);
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", func_001381B4);

int CD_SECTION(sceCdMmode) sceCdMmode(int mode)
{
	int *arg = &sdkCdMmodeArg;
	int ret;
	if (!_sceCd_scmd_prechk(0x22)) return 0;
	sdkCdMmodeArg = mode;
	sceSifWriteBackDCache(arg, 4);
	if (sceSifCallRpc(&sdkCdScmdClient, sdkCdMmodeRpc, 0, arg, sdkCdMmodeSendSize, sdkCdScmdResult, sdkCdMmodeRecvSize, 0, 0) < 0) {
		SignalSema(sdkCdScmdSema);
		return 0;
	}
	ret = *(int *)((unsigned int)sdkCdScmdResult | 0x20000000);
	SignalSema(sdkCdScmdSema);
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", func_00138288);

int CD_SECTION(sceCdReadClock) sceCdReadClock(cdvdClock_t *clock)
{
	int ret;
	if (!_sceCd_scmd_prechk(0xf)) return 0;
	if (sceSifCallRpc(&sdkCdScmdClient, 1, 0, 0, 0, sdkCdScmdResult, 0x10, 0, 0) < 0) {
		SignalSema(sdkCdScmdSema);
		return 0;
	}
	*clock = *(cdvdClock_t *)(((unsigned int)sdkCdScmdResult + 4) | 0x20000000);
	ret = *(int *)((unsigned int)sdkCdScmdResult | 0x20000000);
	SignalSema(sdkCdScmdSema);
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/cdvd/libcdvd", func_0013834C);
