#include "common.h"
#include "libmc.h"

/* Recovered directly from the retail boot instructions (libmc 3020); no vendor source. */
#define MC_SECTION(name) __attribute__((section(".mc_" #name)))

/* Original padding words stay in their own slots. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
	__asm__(".section .mc_" #NAME ",\"ax\",@progbits\n" \
			".set noat\n.set noreorder\n" \
			".include \"" FOLDER "/" #NAME ".s\"\n" \
			".set reorder\n.set at\n.text\n")
#endif

extern int sdkMcCommand;
extern int sdkMcSema;
extern int sdkMcRpcSema;
extern int sdkMcClient[10];
extern int *sdkMcInfoType;
extern int *sdkMcInfoFree;
extern int *sdkMcInfoFormat;
extern mcRequest_t sdkMcRequest;
extern mcNameRequest_t sdkMcNameRequest;
extern mcReadFix_t sdkMcReadFix;
extern int sdkMcResult[4];
extern const char sdkMcSemaName[];
extern const char sdkMcRpcSemaName[];
extern const char sdkMcBindError[];
extern const char sdkMcServerError[];
extern const char sdkMcManagerError[];
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern int sceSifBindRpc(void *, unsigned int, int);
extern void sceSifInitRpc(int);
extern void sceSifWriteBackDCache(void *, int);
extern int CreateSema(mcSemaParam_t *);
extern int DeleteSema(int);
extern int PollSema(int);
extern int WaitSema(int);
extern int SignalSema(int);
extern int iSignalSema(int);
extern void FlushCache(int);
extern void scePrintf(const char *, ...);
extern char *strncpy(char *, const char *, unsigned int);

int MC_SECTION(sceMcInit) sceMcInit(void)
{
	mcSemaParam_t param;
	int retry = 0;
	int result, wait;
	if (sdkMcSema < 0) {
		param.initCount = 1;
		param.option = sdkMcSemaName;
		param.maxCount = 1;
		sdkMcSema = CreateSema(&param);
		if (sdkMcSema == -1) return -101;
		param.maxCount = 1;
		param.initCount = 0;
		param.option = sdkMcRpcSemaName;
		result = CreateSema(&param);
		sdkMcRpcSema = result;
		if (result == -1) {
			DeleteSema(sdkMcSema);
			sdkMcSema = result;
			return -101;
		}
	}
	sceMcSync(0, 0, 0);
	WaitSema(sdkMcSema);
	sceSifInitRpc(0);
	while (1) {
		if (sceSifBindRpc(sdkMcClient, 0x80000400, 0) < 0) {
			scePrintf(sdkMcBindError);
			while (1) {}
		}
		if (sdkMcClient[9]) break;
		wait = 0x100000;
		while (--wait) {}
		if (++retry >= 0x200) {
			scePrintf(sdkMcBindError);
			return -91;
		}
	}
	result = sceSifCallRpc(sdkMcClient, 0xfe, 0, &sdkMcRequest, 0x30, sdkMcResult, 0xc, 0, 0);
	SignalSema(sdkMcSema);
	if (result < 0) {
		sdkMcClient[9] = 0;
		return -91;
	}
	if (sdkMcResult[1] < 0x20a) {
		scePrintf(sdkMcServerError);
		sdkMcClient[9] = 0;
		return -120;
	}
	if (sdkMcResult[2] < 0x20e) {
		scePrintf(sdkMcManagerError);
		sdkMcClient[9] = 0;
		return -121;
	}
	return sdkMcResult[0];
}

int MC_SECTION(sceMcEnd) sceMcEnd(void)
{
	if (sdkMcSema >= 0) {
		sceMcSync(0, 0, 0);
		DeleteSema(sdkMcSema);
		sdkMcSema = -1;
		DeleteSema(sdkMcRpcSema);
	}
	return 1;
}

void MC_SECTION(mceSifRpcEndFunc) mceSifRpcEndFunc(void *arg)
{
	iSignalSema(sdkMcRpcSema);
}

/* Original padding word; not an independent function. */
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mc/libmc", func_0013A158);

int MC_SECTION(sceMcOpen) sceMcOpen(int port, int slot, const char *name, int mode)
{
	if (!sdkMcClient[9]) return -100;
	if (PollSema(sdkMcSema) < 0) return -200;
	if (!name || !*name) {
		SignalSema(sdkMcSema);
		return -210;
	}
	strncpy(sdkMcNameRequest.name, name, 0x3ff);
	sdkMcNameRequest.port = port;
	sdkMcNameRequest.flags = mode;
	sdkMcNameRequest.slot = slot;
	sdkMcNameRequest.name[0x3ff] = 0;
	if (sceSifCallRpc(sdkMcClient, 2, 1, &sdkMcNameRequest, 0x414, sdkMcResult, 4, mceSifRpcEndFunc, 0)) {
		SignalSema(sdkMcSema);
		return -91;
	}
	sdkMcCommand = 2;
	return 0;
}

int MC_SECTION(sceMcMkdir) sceMcMkdir(int port, int slot, const char *name)
{
	int result = sceMcOpen(port, slot, name, 0x40);
	if (!result) sdkMcCommand = 0xb;
	return result;
}

int MC_SECTION(sceMcClose) sceMcClose(int fd)
{
	if (!sdkMcClient[9]) return -100;
	if (PollSema(sdkMcSema) < 0) return -200;
	sdkMcRequest.fd = fd;
	if (sceSifCallRpc(sdkMcClient, 3, 1, &sdkMcRequest, 0x30, sdkMcResult, 4, mceSifRpcEndFunc, 0)) {
		SignalSema(sdkMcSema);
		return -91;
	}
	sdkMcCommand = 3;
	return 0;
}

int MC_SECTION(sceMcSeek) sceMcSeek(int fd, int offset, int origin)
{
	if (!sdkMcClient[9]) return -100;
	if (PollSema(sdkMcSema) < 0) return -200;
	sdkMcRequest.fd = fd;
	sdkMcRequest.offset = offset;
	sdkMcRequest.origin = origin;
	if (sceSifCallRpc(sdkMcClient, 4, 1, &sdkMcRequest, 0x30, sdkMcResult, 4, mceSifRpcEndFunc, 0)) {
		SignalSema(sdkMcSema);
		return -91;
	}
	sdkMcCommand = 4;
	return 0;
}

void MC_SECTION(mceIntrReadFixAlign) mceIntrReadFixAlign(mcReadFix_t *arg)
{
	mcReadFix_t *fix = (mcReadFix_t *)((unsigned int)arg | 0x20000000);
	int i;
	char *dst, *uncached;
	if (fix->headLen) {
		dst = fix->headDst;
		uncached = (char *)((unsigned int)dst | 0x20000000);
		for (i = 0; i < fix->headLen; i++) {
			unsigned char c = fix->head[i];
			*dst++ = c;
			*uncached++ = c;
		}
	}
	if (fix->tailLen) {
		dst = fix->tailDst;
		uncached = (char *)((unsigned int)dst | 0x20000000);
		for (i = 0; i < fix->tailLen; i++) {
			unsigned char c = fix->tail[i];
			*dst++ = c;
			*uncached++ = c;
		}
	}
	iSignalSema(sdkMcRpcSema);
}

int MC_SECTION(sceMcRead) sceMcRead(int fd, void *buffer, int size)
{
	if (!sdkMcClient[9]) return -100;
	if (PollSema(sdkMcSema) < 0) return -200;
	sdkMcRequest.fd = fd;
	sdkMcRequest.buffer = buffer;
	sdkMcRequest.size = size;
	sdkMcRequest.fix = &sdkMcReadFix;
	sceSifWriteBackDCache(buffer, size);
	sceSifWriteBackDCache(&sdkMcReadFix, 0xc0);
	if (sceSifCallRpc(sdkMcClient, 5, 1, &sdkMcRequest, 0x30, sdkMcResult, 4, mceIntrReadFixAlign, &sdkMcReadFix)) {
		SignalSema(sdkMcSema);
		return -91;
	}
	sdkMcCommand = 5;
	return 0;
}

int MC_SECTION(sceMcWrite) sceMcWrite(int fd, const void *buffer, int size)
{
	unsigned int i;
	int head;
	if (!sdkMcClient[9]) return -100;
	if (PollSema(sdkMcSema) < 0) return -200;
	sdkMcRequest.fd = fd;
	if (size < 17) {
		sdkMcRequest.origin = size;
		sdkMcRequest.size = 0;
		sdkMcRequest.buffer = 0;
	} else {
		{
			unsigned int start = (unsigned int)buffer - 0x10;
			head = ((start + 15) & ~0xf) - start;
		}
		sdkMcRequest.origin = head;
		sdkMcRequest.size = size - head;
		sdkMcRequest.buffer = (char *)buffer + head;
	}
	for (i = 0; i < sdkMcRequest.origin; i++) sdkMcRequest.data[i] = ((const unsigned char *)buffer)[i];
	FlushCache(0);
	if (sceSifCallRpc(sdkMcClient, 6, 1, &sdkMcRequest, 0x30, sdkMcResult, 4, mceSifRpcEndFunc, 0)) {
		SignalSema(sdkMcSema);
		return -91;
	}
	sdkMcCommand = 6;
	return 0;
}

int MC_SECTION(sceMcSync) sceMcSync(int mode, int *cmd, int *result)
{
	int done;
	if (!sdkMcCommand) return -1;
	if (PollSema(sdkMcRpcSema) < 0) done = 1;
	else done = 0;
	if (!mode && done) {
		WaitSema(sdkMcRpcSema);
		done = 0;
	}
	done = !done;
	if (cmd) *cmd = sdkMcCommand;
	if (done) {
		sdkMcCommand = 0;
		if (result) *result = sdkMcResult[0];
		SignalSema(sdkMcSema);
	}
	return done;
}

void MC_SECTION(mceGetInfoApdx) mceGetInfoApdx(void *arg)
{
	int *info = (int *)((unsigned int)arg | 0x20000000);
	if (sdkMcInfoType) *sdkMcInfoType = info[0];
	if (sdkMcInfoFree) *sdkMcInfoFree = info[1];
	if (sdkMcInfoFormat) *sdkMcInfoFormat = info[0x24];
	iSignalSema(sdkMcRpcSema);
}

int MC_SECTION(sceMcGetInfo) sceMcGetInfo(int port, int slot, int *type, int *free, int *format)
{
	if (!sdkMcClient[9]) return -100;
	if (PollSema(sdkMcSema) < 0) return -200;
	sdkMcRequest.port = port;
	sdkMcRequest.slot = slot;
	sdkMcRequest.fix = &sdkMcReadFix;
	if (type) sdkMcRequest.origin = 1;
	else sdkMcRequest.origin = 0;
	if (free) sdkMcRequest.offset = 1;
	else sdkMcRequest.offset = 0;
	if (format) sdkMcRequest.size = 1;
	else sdkMcRequest.size = 0;
	sdkMcInfoType = type;
	sdkMcInfoFree = free;
	sdkMcInfoFormat = format;
	sceSifWriteBackDCache(&sdkMcReadFix, 0xc0);
	if (sceSifCallRpc(sdkMcClient, 1, 1, &sdkMcRequest, 0x30, sdkMcResult, 4, mceGetInfoApdx, &sdkMcReadFix)) {
		SignalSema(sdkMcSema);
		return -91;
	}
	sdkMcCommand = 1;
	return 0;
}

int MC_SECTION(sceMcGetDir) sceMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, void *table)
{
	if (!sdkMcClient[9]) return -100;
	if (PollSema(sdkMcSema) < 0) return -200;
	if (!name || !*name) {
		SignalSema(sdkMcSema);
		return -210;
	}
	sdkMcNameRequest.port = port;
	sdkMcNameRequest.slot = slot;
	sdkMcNameRequest.flags = mode;
	sdkMcNameRequest.maxent = maxent;
	sdkMcNameRequest.table = table;
	strncpy(sdkMcNameRequest.name, name, 0x3ff);
	sdkMcNameRequest.name[0x3ff] = 0;
	if (maxent >= 0) sceSifWriteBackDCache(table, maxent * 64);
	if (sceSifCallRpc(sdkMcClient, 0xd, 1, &sdkMcNameRequest, 0x414, sdkMcResult, 4, mceSifRpcEndFunc, 0)) {
		SignalSema(sdkMcSema);
		return -91;
	}
	sdkMcCommand = 0xd;
	return 0;
}

/* Original padding word; not an independent function. */
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mc/libmc", func_0013AB90);

int MC_SECTION(sceMcFormat) sceMcFormat(int port, int slot)
{
	if (!sdkMcClient[9]) return -100;
	if (PollSema(sdkMcSema) < 0) return -200;
	sdkMcRequest.port = port;
	sdkMcRequest.slot = slot;
	if (sceSifCallRpc(sdkMcClient, 0x10, 1, &sdkMcRequest, 0x30, sdkMcResult, 4, mceSifRpcEndFunc, 0)) {
		SignalSema(sdkMcSema);
		return -91;
	}
	sdkMcCommand = 0x10;
	return 0;
}

int MC_SECTION(sceMcDelete) sceMcDelete(int port, int slot, const char *name)
{
	if (!sdkMcClient[9]) return -100;
	if (PollSema(sdkMcSema) < 0) return -200;
	if (!name || !*name) {
		SignalSema(sdkMcSema);
		return -210;
	}
	strncpy(sdkMcNameRequest.name, name, 0x3ff);
	sdkMcNameRequest.port = port;
	sdkMcNameRequest.slot = slot;
	sdkMcNameRequest.name[0x3ff] = 0;
	sdkMcNameRequest.flags = 0;
	if (sceSifCallRpc(sdkMcClient, 0xf, 1, &sdkMcNameRequest, 0x414, sdkMcResult, 4, mceSifRpcEndFunc, 0)) {
		SignalSema(sdkMcSema);
		return -91;
	}
	sdkMcCommand = 0xf;
	return 0;
}

/* Original padding words; not an independent function. */
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mc/libmc", func_0013AD88);

int MC_SECTION(sceMcUnformat) sceMcUnformat(int port, int slot)
{
	if (!sdkMcClient[9]) return -100;
	if (PollSema(sdkMcSema) < 0) return -200;
	sdkMcRequest.port = port;
	sdkMcRequest.slot = slot;
	if (sceSifCallRpc(sdkMcClient, 0x11, 1, &sdkMcRequest, 0x30, sdkMcResult, 4, mceSifRpcEndFunc, 0)) {
		SignalSema(sdkMcSema);
		return -91;
	}
	sdkMcCommand = 0x11;
	return 0;
}

/* Original padding words before the multitap library; not an independent function. */
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mc/libmc", func_0013AE68);
