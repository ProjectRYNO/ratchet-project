#ifndef SDK_PAD_LIBPAD_H
#define SDK_PAD_LIBPAD_H

/* Per port/slot client state at sdkPadSlots (2 ports x 4 slots). */
typedef struct padSlot {
	/* 0x00 */ unsigned char *dma;
	/* 0x04 */ int *send;
	/* 0x08 */ unsigned int iop;
	/* 0x0c */ int dmaId;
	/* 0x10 */ int opened;
	/* 0x14 */ int unk14;
	/* 0x18 */ int unk18;
} padSlot_t;

/* One 128-byte controller snapshot; the DMA area holds two, newest selected by frame. */
typedef struct padFrame {
	/* 0x00 */ unsigned char unk00[0x30];
	/* 0x30 */ unsigned char act[6][4];
	/* 0x48 */ unsigned char unk48[8];
	/* 0x50 */ unsigned short modeTable[8];
	/* 0x60 */ int length;
	/* 0x64 */ unsigned char exMode;
	/* 0x65 */ unsigned char id;
	/* 0x66 */ unsigned char exId;
	/* 0x67 */ unsigned char unk67;
	/* 0x68 */ unsigned char modeCount;
	/* 0x69 */ unsigned char modeCurrent;
	/* 0x6a */ unsigned char actCount;
	/* 0x6b */ unsigned char unk6B[5];
	/* 0x70 */ unsigned char state;
	/* 0x71 */ unsigned char reqState;
	/* 0x72 */ unsigned char ok;
	/* 0x73 */ unsigned char unk73[13];
} padFrame_t;

typedef struct padRaw {
	/* 0x00 */ unsigned char data[128];
} padRaw_t;

typedef struct padDmaTransfer {
	/* 0x00 */ void *src;
	/* 0x04 */ void *dest;
	/* 0x08 */ int size;
	/* 0x0c */ int attr;
} padDmaTransfer_t;

int scePadInit(int mode);
int scePadInit2(int mode);
int scePadEnd(void);
int scePadPortOpen(int port, int slot, void *addr);
int scePadPortClose(int port, int slot);
unsigned char *scePadGetDmaStr(int port, int slot, unsigned char *copy);
int scePadRead(int port, int slot, unsigned char *data);
int scePadGetState(int port, int slot);
int scePadSetReqState(int port, int slot, int state);
int scePadGetReqState(int port, int slot);
int scePadInfoAct(int port, int slot, int actno, int term);
int scePadInfoMode(int port, int slot, int term, int offs);
int scePadSetMainMode(int port, int slot, int offs, int lock);
int scePadSetActDirect(int port, int slot, const unsigned char *data);
int scePadSetActAlign(int port, int slot, const unsigned char *data);
int scePadSetButtonInfo(int port, int slot, int info);
int scePadInfoPressMode(int port, int slot);
int scePadEnterPressMode(int port, int slot);
int scePadGetModVersion(void);
void *scePadSetDmaCallback(void (*callback)(int));
int _send_to_iop(int port, int slot);

#endif
