#ifndef SDK_CDVD_LIBCDVD_H
#define SDK_CDVD_LIBCDVD_H

/* EE kernel semaphore parameters. */
typedef struct cdvdSemaParam {
	/* 0x00 */ int count;
	/* 0x04 */ int maxCount;
	/* 0x08 */ int initCount;
	/* 0x0c */ int waitThreads;
	/* 0x10 */ unsigned int attr;
	/* 0x14 */ const char *option;
} cdvdSemaParam_t;

/* SIF RPC client data used for the N-command and S-command servers. */
typedef struct cdvdRpcClient {
	/* 0x00 */ void *packet;
	/* 0x04 */ int rpcId;
	/* 0x08 */ int sema;
	/* 0x0c */ unsigned int mode;
	/* 0x10 */ unsigned int command;
	/* 0x14 */ void *buffer;
	/* 0x18 */ void *cbuffer;
	/* 0x1c */ void *endFunc;
	/* 0x20 */ void *endParam;
	/* 0x24 */ void *server;
} cdvdRpcClient_t;

/* sceCdCLOCK as copied out of the RPC result (BCD fields). */
typedef struct cdvdClock {
	/* 0x00 */ unsigned char data[8];
} cdvdClock_t;

/* sceCdRMode: read mode bytes. */
typedef struct cdvdRMode {
	/* 0x00 */ unsigned char trycount;
	/* 0x01 */ unsigned char spindlctrl;
	/* 0x02 */ unsigned char datapattern;
	/* 0x03 */ unsigned char pad;
} cdvdRMode_t;

/* N-command read request at sdkCdReadArg. */
typedef struct cdvdReadArg {
	/* 0x00 */ unsigned int lsn;
	/* 0x04 */ unsigned int sectors;
	/* 0x08 */ void *buffer;
	/* 0x0c */ cdvdRMode_t mode;
	/* 0x10 */ void *eeBuffer;
	/* 0x14 */ int *eeStatus;
} cdvdReadArg_t;

#endif
