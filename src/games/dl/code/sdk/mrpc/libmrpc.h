#ifndef SDK_MRPC_LIBMRPC_H
#define SDK_MRPC_LIBMRPC_H

/* EE kernel semaphore parameters. */
typedef struct mrpcSemaParam {
	/* 0x00 */ int count;
	/* 0x04 */ int maxCount;
	/* 0x08 */ int initCount;
	/* 0x0c */ int waitThreads;
	/* 0x10 */ unsigned int attr;
	/* 0x14 */ const char *option;
} mrpcSemaParam_t;

/* 64-byte multi-thread RPC packet. */
typedef struct mrpcEndPkt {
	/* 0x00 */ int unk00[7];
	/* 0x1c */ void *client;
	/* 0x20 */ unsigned int cid;
	/* 0x24 */ int arg24;
	/* 0x28 */ int arg28;
} mrpcEndPkt_t;

typedef struct mrpcEndClient {
	/* 0x00 */ void *packet;
	/* 0x04 */ int rpcId;
	/* 0x08 */ int sema;
	/* 0x0c */ int mode;
	/* 0x10 */ int command;
	/* 0x14 */ int buffer;
	/* 0x18 */ int gp;
	/* 0x1c */ void (*endFunc)(void *);
	/* 0x20 */ void *endParam;
	/* 0x24 */ int server;
	/* 0x28 */ int bindSema;
	/* 0x2c */ int result;
} mrpcEndClient_t;

typedef struct mrpcPkt {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ unsigned int mode;
	/* 0x14 */ void *paddr;
	/* 0x18 */ int pid;
	/* 0x1c */ void *client;
	/* 0x20 */ int cid;
	/* 0x24 */ int arg24;
	/* 0x28 */ int arg28;
	/* 0x2c */ int arg2C;
	/* 0x30 */ int unk30[4];
} mrpcPkt_t;

/* Packet pool at sdkMRpcPool. */
typedef struct mrpcPool {
	/* 0x00 */ int pid;
	/* 0x04 */ mrpcPkt_t *packets;
	/* 0x08 */ int count;
	/* 0x0c */ int unk0C;
	/* 0x10 */ int unk10;
} mrpcPool_t;

/* Multi-thread RPC client; the semaphore fields are re-read after every wait. */
typedef struct mrpcClient {
	/* 0x00 */ void *packet;
	/* 0x04 */ int rpcId;
	/* 0x08 */ volatile int sema;
	/* 0x0c */ int mode;
	/* 0x10 */ int command;
	/* 0x14 */ int unk14[4];
	/* 0x24 */ int server;
	/* 0x28 */ volatile int bindSema;
	/* 0x2c */ int result;
	/* 0x30 */ int param0;
	/* 0x34 */ int param1;
	/* 0x38 */ int param2;
} mrpcClient_t;

/* Packet layout used by sceSifMCallRpc; words it only copies are int. */
typedef struct mrpcCallPkt {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ unsigned int mode;
	/* 0x14 */ int paddr;
	/* 0x18 */ int pid;
	/* 0x1c */ int client;
	/* 0x20 */ int cid;
	/* 0x24 */ int arg24;
	/* 0x28 */ int arg28;
	/* 0x2c */ int arg2C;
	/* 0x30 */ int rmode;
	/* 0x34 */ int server;
	/* 0x38 */ int unk38[2];
} mrpcCallPkt_t;

/* Client layout used by sceSifMCallRpc. */
typedef struct mrpcCallClient {
	/* 0x00 */ void *packet;
	/* 0x04 */ int rpcId;
	/* 0x08 */ volatile int sema;
	/* 0x0c */ int mode;
	/* 0x10 */ int command;
	/* 0x14 */ int buffer;
	/* 0x18 */ int gp;
	/* 0x1c */ void *endFunc;
	/* 0x20 */ void *endParam;
	/* 0x24 */ int server;
	/* 0x28 */ volatile int bindSema;
	/* 0x2c */ int result;
	/* 0x30 */ int param0;
	/* 0x34 */ int param1;
	/* 0x38 */ int param2;
} mrpcCallClient_t;

#endif
