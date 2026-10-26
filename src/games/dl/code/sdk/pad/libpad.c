#include "common.h"
#include "libpad.h"

/* Recovered directly from the retail boot instructions (libpad 3020); no vendor source. */
#define PAD_SECTION(name) __attribute__((section(".pad_" #name)))

/* Functions still in assembly, and original padding words, stay in their own slots. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
	__asm__(".section .pad_" #NAME ",\"ax\",@progbits\n" \
			".set noat\n.set noreorder\n" \
			".include \"" FOLDER "/" #NAME ".s\"\n" \
			".set reorder\n.set at\n.text\n")
#endif

extern int sdkPadInitialized;
extern int sdkPadDebug;
extern void (*sdkPadDmaCallback)(int);
extern int sdkPadInitArg;
extern int sdkPadClient[20];
extern padSlot_t sdkPadSlots[2][4];
extern int sdkPadSend[2][4][8];
extern int sdkPadBuffer[32];
extern int sdkPadGp;
extern const char sdkPadVersionError[];
extern const char sdkPadVersionFormat[];
extern const char sdkPadSendError[];
extern const char sdkPadAlignError[];
extern const char sdkPadOpenError[];
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern int sceSifBindRpc(void *, unsigned int, int);
extern void sceSifAddCmdHandler(unsigned int, void *, void *);
extern void sceSifRemoveCmdHandler(unsigned int);
extern int sceSifDmaStat(unsigned int);
extern unsigned int sceSifSetDma(padDmaTransfer_t *, int);
extern int DIntr(void);
extern int EIntr(void);
extern void SyncDCache(void *, void *);
extern void scePrintf(const char *, ...);
extern void *memcpy(void *, const void *, unsigned int);
extern void *memset(void *, int, unsigned int);
extern int _pad_intr_hdr(void *);

int PAD_SECTION(scePadInit) scePadInit(int mode)
{
	int version, i;
	if (!sdkPadInitialized) {
		while (sceSifBindRpc(sdkPadClient, 0x80000100, 0), !sdkPadClient[9]) {
			i = 0x10000;
			while (i--) {}
		}
		while (sceSifBindRpc(&sdkPadClient[10], 0x80000101, 0), !sdkPadClient[19]) {
			i = 0x10000;
			while (i--) {}
		}
		version = scePadGetModVersion();
		if ((version >> 8) != 4) {
			if (sdkPadDebug) {
				scePrintf(sdkPadVersionError);
				scePrintf(sdkPadVersionFormat, 4, 0, version >> 8, version & 0xff);
			}
			return 0;
		}
	}
	i = scePadInit2(mode);
	sdkPadInitialized = 1;
	return i;
}

/* Interrupt handler written with inline asm in the original (gp swap, sync, ei). */
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/pad/libpad", _pad_intr_hdr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/pad/libpad", scePadInit2);

int PAD_SECTION(scePadEnd) scePadEnd(void)
{
	int result;
	if (!sdkPadInitialized) return 1;
	scePadSetDmaCallback(0);
	sdkPadBuffer[0] = 0xf;
	if (sceSifCallRpc(sdkPadClient, 1, 0, sdkPadBuffer, 128, sdkPadBuffer, 128, 0, 0) < 0) return 0;
	sceSifRemoveCmdHandler(0x80000019);
	result = sdkPadBuffer[3];
	if (result == 1) sdkPadInitialized = 0;
	sdkPadInitArg = 0;
	return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/pad/libpad", _send_to_iop);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/pad/libpad", scePadPortOpen);

int PAD_SECTION(scePadPortClose) scePadPortClose(int port, int slot)
{
	if (!sdkPadSlots[port][slot].opened) return 0;
	sdkPadBuffer[0] = 0xe;
	sdkPadBuffer[1] = port;
	sdkPadBuffer[2] = slot;
	sdkPadBuffer[4] = 1;
	if (sceSifCallRpc(sdkPadClient, 1, 0, sdkPadBuffer, 128, sdkPadBuffer, 128, 0, 0) < 0) return 0;
	sdkPadSlots[port][slot].opened = 0;
	return sdkPadBuffer[3];
}

unsigned char *PAD_SECTION(scePadGetDmaStr) scePadGetDmaStr(int port, int slot, unsigned char *copy)
{
	int interrupts = DIntr();
	unsigned char *dma = sdkPadSlots[port][slot].dma;
	int frame;
	SyncDCache(dma, dma + 0xff);
	frame = *(int *)(dma + 0x58) < *(int *)(dma + 0xd8);
	if (copy) *(padRaw_t *)copy = *(padRaw_t *)(dma + frame * 128);
	if (interrupts == 1) EIntr();
	return dma + frame * 128;
}

int PAD_SECTION(scePadRead) scePadRead(int port, int slot, unsigned char *data)
{
	unsigned char copy[128];
	if (!sdkPadSlots[port][slot].opened) return 0;
	scePadGetDmaStr(port, slot, copy);
	memcpy(data, copy, *(int *)(copy + 0x60));
	return *(int *)(copy + 0x60);
}

int PAD_SECTION(scePadGetState) scePadGetState(int port, int slot)
{
	unsigned char copy[128];
	if (!sdkPadSlots[port][slot].opened) return 99;
	scePadGetDmaStr(port, slot, copy);
	if (copy[0x70] == 6 && copy[0x71] == 2) return 5;
	return copy[0x70];
}

/* Original padding word; not an independent function. */
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/pad/libpad", func_0013BB10);

int PAD_SECTION(scePadSetReqState) scePadSetReqState(int port, int slot, int state)
{
	int interrupts;
	unsigned char *dma;
	if (!sdkPadSlots[port][slot].opened) return 0;
	interrupts = DIntr();
	dma = scePadGetDmaStr(port, slot, 0);
	dma[0x71] = state;
	SyncDCache(dma, dma + 0x7f);
	if (interrupts == 1) EIntr();
	return 1;
}

int PAD_SECTION(scePadGetReqState) scePadGetReqState(int port, int slot)
{
	if (!sdkPadSlots[port][slot].opened) return 0;
	return scePadGetDmaStr(port, slot, 0)[0x71];
}

/* Original padding word; not an independent function. */
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/pad/libpad", func_0013BC28);

int PAD_SECTION(scePadInfoAct) scePadInfoAct(int port, int slot, int actno, int term)
{
	padFrame_t copy;
	if (!sdkPadSlots[port][slot].opened) return 0;
	scePadGetDmaStr(port, slot, (unsigned char *)&copy);
	if (copy.ok != 1) return 0;
	if (copy.exMode < 2) return 0;
	if (actno >= copy.actCount) return 0;
	if (actno == -1) return copy.actCount;
	switch (term) {
	case 1: return copy.act[actno][0];
	case 2: return copy.act[actno][1];
	case 3: return copy.act[actno][2];
	case 4: return copy.act[actno][3];
	}
	return 0;
}

/* Original padding word; not an independent function. */
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/pad/libpad", func_0013BD48);

int PAD_SECTION(scePadInfoMode) scePadInfoMode(int port, int slot, int term, int offs)
{
	padFrame_t copy;
	if (!sdkPadSlots[port][slot].opened) return 0;
	scePadGetDmaStr(port, slot, (unsigned char *)&copy);
	if (copy.ok != 1) return 0;
	if (copy.reqState == 2) return 0;
	switch (term) {
	case 1:
		if (copy.id == 0xf3) return 0;
		return copy.id >> 4;
	case 2:
		if (copy.exMode == 1) return 0;
		return copy.modeTable[copy.modeCurrent];
	case 3:
		if (copy.exMode == 1) return 0;
		return copy.modeCurrent;
	case 4:
		if (copy.exMode == 1) return 0;
		if (offs == -1) return copy.modeCount;
		if (offs >= copy.modeCount) return 0;
		return copy.modeTable[offs];
	}
	return 0;
}

int PAD_SECTION(scePadSetMainMode) scePadSetMainMode(int port, int slot, int offs, int lock)
{
	sdkPadBuffer[0] = 6;
	sdkPadBuffer[1] = port;
	sdkPadBuffer[2] = slot;
	sdkPadBuffer[3] = offs;
	sdkPadBuffer[4] = lock;
	if (sceSifCallRpc(sdkPadClient, 1, 0, sdkPadBuffer, 128, sdkPadBuffer, 128, 0, 0) < 0) return 0;
	if (sdkPadBuffer[5] == 1) scePadSetReqState(port, slot, 2);
	return sdkPadBuffer[5];
}

int PAD_SECTION(scePadSetActDirect) scePadSetActDirect(int port, int slot, const unsigned char *data)
{
	padFrame_t copy;
	int *send;
	int i;
	scePadGetDmaStr(port, slot, (unsigned char *)&copy);
	if (copy.ok != 1) return 0;
	send = sdkPadSlots[port][slot].send;
	{
		unsigned char *dst = (unsigned char *)(send + 3);
		for (i = 0; i < 6; i++) dst[i] = data[i];
	}
	send[1] = 1;
	send[2] = 6;
	if (_send_to_iop(port, slot) != 1) return 0;
	return 1;
}

int PAD_SECTION(scePadSetActAlign) scePadSetActAlign(int port, int slot, const unsigned char *data)
{
	int i;
	int *buffer = sdkPadBuffer;
	buffer[0] = 8;
	buffer[1] = port;
	buffer[2] = slot;
	{
		unsigned char *dst = (unsigned char *)(buffer + 3);
		for (i = 0; i < 6; i++) dst[i] = data[i];
	}
	if (sceSifCallRpc(sdkPadClient, 1, 0, buffer, 128, buffer, 128, 0, 0) < 0) return 0;
	if (buffer[5] == 1) scePadSetReqState(port, slot, 2);
	return buffer[5];
}

int PAD_SECTION(scePadSetButtonInfo) scePadSetButtonInfo(int port, int slot, int info)
{
	sdkPadBuffer[0] = 0xa;
	sdkPadBuffer[1] = port;
	sdkPadBuffer[2] = slot;
	sdkPadBuffer[3] = info;
	if (sceSifCallRpc(sdkPadClient, 1, 0, sdkPadBuffer, 128, sdkPadBuffer, 128, 0, 0) < 0) return 0;
	if (sdkPadBuffer[4] == 1) scePadSetReqState(port, slot, 2);
	return sdkPadBuffer[4];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/pad/libpad", scePadInfoPressMode);

int PAD_SECTION(scePadEnterPressMode) scePadEnterPressMode(int port, int slot)
{
	if (!sdkPadSlots[port][slot].opened) return 0;
	return scePadSetButtonInfo(port, slot, 0xfff);
}

/* Original padding words; not an independent function. */
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/pad/libpad", func_0013C268);

int PAD_SECTION(scePadGetModVersion) scePadGetModVersion(void)
{
	sdkPadBuffer[0] = 0x12;
	if (sceSifCallRpc(sdkPadClient, 1, 0, sdkPadBuffer, 128, sdkPadBuffer, 128, 0, 0) < 0) return 0;
	return sdkPadBuffer[3];
}

void *PAD_SECTION(scePadSetDmaCallback) scePadSetDmaCallback(void (*callback)(int))
{
	register int gp __asm__("$28");
	void (*old)(int) = sdkPadDmaCallback;
	int interrupts;
	int *buffer;
	if (!callback) {
		buffer = sdkPadBuffer;
		buffer[0] = 0x18;
		sdkPadDmaCallback = 0;
		buffer[1] = 0;
		while (sceSifCallRpc(sdkPadClient, 1, 0, buffer, 128, buffer, 128, 0, 0) < 0) {}
		return (void *)old;
	}
	if (!old) {
		buffer = sdkPadBuffer;
		buffer[0] = 0x18;
		buffer[1] = 1;
		while (sceSifCallRpc(sdkPadClient, 1, 0, buffer, 128, buffer, 128, 0, 0) < 0) {}
	}
	interrupts = DIntr();
	sdkPadGp = gp;
	sdkPadDmaCallback = callback;
	if (interrupts == 1) EIntr();
	return (void *)old;
}

/* Original padding bytes (stale vector-store words) before the VU0 library; not a function. */
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/pad/libpad", func_0013C410);
