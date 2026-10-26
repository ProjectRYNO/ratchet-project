#ifndef SDK_KERNEL_LIBKERNEL_H
#define SDK_KERNEL_LIBKERNEL_H

/* EE (EABI, single-float) varargs from GCC's va-mips.h; this compiler has no stdarg.h. */
typedef char *va_list;
#define va_start(ap, last) (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8))
#define va_end(ap)

/* Character sink used by _sceSnprintf. */
typedef int (*kernelPrintfChar)(void *context, int *size, int c);

/* SIF command handler entry (system and user tables). */
typedef struct sifCmdHandler {
	/* 0x00 */ void *func;
	/* 0x04 */ void *data;
	/* 0x08 */ int gp;
} sifCmdHandler_t;

/* SIF command state at sdkSifCmd. */
typedef struct sifCmdData {
	/* 0x00 */ void *packetBuffer;
	/* 0x04 */ void *unk04;
	/* 0x08 */ void *iopBuffer;
	/* 0x0c */ sifCmdHandler_t *sysHandlers;
	/* 0x10 */ int sysCount;
	/* 0x14 */ sifCmdHandler_t *usrHandlers;
	/* 0x18 */ int usrCount;
	/* 0x1c */ int *sregs;
} sifCmdData_t;

/* SIF set-SREG command packet. */
typedef struct sifCmdSregPkt {
	/* 0x00 */ int header[4];
	/* 0x10 */ int index;
	/* 0x14 */ int value;
} sifCmdSregPkt_t;

/* SIF change-address command packet. */
typedef struct sifCmdChangeAddrPkt {
	/* 0x00 */ int header[4];
	/* 0x10 */ void *addr;
} sifCmdChangeAddrPkt_t;

/* SIF RPC packet header fields used by the packet helpers. */
typedef struct sifRpcPacket {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ unsigned int mode;
	/* 0x14 */ int unk14;
	/* 0x18 */ int id;
} sifRpcPacket_t;

/* SIF RPC packet pool fields used by the packet helpers. */
typedef struct sifRpcData {
	/* 0x00 */ int unk00[5];
	/* 0x14 */ char *packets;
	/* 0x18 */ int count;
	/* 0x1c */ char *fixed;
	/* 0x20 */ int fixedCount;
	/* 0x24 */ int index;
} sifRpcData_t;

/* SIF RPC server registration. */
typedef struct sifRpcServer {
	/* 0x00 */ int sid;
	/* 0x04 */ int unk04[2];
	/* 0x0c */ int size;
	/* 0x10 */ int unk10[3];
	/* 0x1c */ void *client;
	/* 0x20 */ void *pktAddr;
	/* 0x24 */ int rpcNumber;
	/* 0x28 */ void *recvBuf;
	/* 0x2c */ int rsize;
	/* 0x30 */ int rmode;
	/* 0x34 */ int rid;
	/* 0x38 */ struct sifRpcServer *next;
	/* 0x3c */ struct sifRpcServer *link;
	/* 0x40 */ struct sifRpcQueue *base;
} sifRpcServer_t;

/* SIF RPC receive queue. */
typedef struct sifRpcQueue {
	/* 0x00 */ int threadId;
	/* 0x04 */ int active;
	/* 0x08 */ sifRpcServer_t *link;
	/* 0x0c */ sifRpcServer_t *start;
	/* 0x10 */ sifRpcServer_t *end;
	/* 0x14 */ struct sifRpcQueue *next;
} sifRpcQueue_t;

/* 64-byte RPC packet as allocated by _sceRpcGetPacket. */
typedef struct sifRpcPkt {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ unsigned int mode;
	/* 0x14 */ void *paddr;
	/* 0x18 */ int pid;
	/* 0x1c */ int unk1C[9];
} sifRpcPkt_t;

/* Packet pool header passed to _sceRpcGetPacket. */
typedef struct sifRpcPool {
	/* 0x00 */ int pid;
	/* 0x04 */ sifRpcPkt_t *packets;
	/* 0x08 */ int count;
} sifRpcPool_t;

/* Alarm callback data for the RPC rdata/bind retries. */
typedef struct sifRpcAlarm {
	/* 0x00 */ int unk00[9];
	/* 0x24 */ void *src;
	/* 0x28 */ void *dest;
	/* 0x2c */ int size;
} sifRpcAlarm_t;

/* RPC state fields used by _search_svdata. */
typedef struct sifRpcInfo {
	/* 0x00 */ int unk00[10];
	/* 0x28 */ sifRpcQueue_t *active;
} sifRpcInfo_t;

/* 64-byte SIF RPC message (bind/call/rdata requests and replies). */
typedef struct sifRpcMsg {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ unsigned int mode;
	/* 0x14 */ void *paddr;
	/* 0x18 */ int pid;
	/* 0x1c */ void *client;
	/* 0x20 */ int cid;
	/* 0x24 */ void *arg24;
	/* 0x28 */ void *arg28;
	/* 0x2c */ int arg2C;
	/* 0x30 */ int unk30[4];
} sifRpcMsg_t;

/* SIF RPC client data (sceSifClientData). */
typedef struct sifRpcClient {
	/* 0x00 */ sifRpcMsg_t *packet;
	/* 0x04 */ int rpcId;
	/* 0x08 */ int sema;
	/* 0x0c */ int unk0C;
	/* 0x10 */ int command;
	/* 0x14 */ int unk14[4];
	/* 0x24 */ void *server;
} sifRpcClient_t;

/* SIF RPC receive data (sceSifGetOtherData); the header pointer is untyped. */
typedef struct sifRpcReceiveData {
	/* 0x00 */ void *packet;
	/* 0x04 */ int rpcId;
	/* 0x08 */ int sema;
	/* 0x0c */ unsigned int mode;
	/* 0x10 */ void *src;
	/* 0x14 */ void *dest;
	/* 0x18 */ int size;
} sifRpcReceiveData_t;

/* 64-byte SIF RPC other-data request packet. */
typedef struct sifRpcOtherPkt {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ unsigned int mode;
	/* 0x14 */ void *paddr;
	/* 0x18 */ int pid;
	/* 0x1c */ void *client;
	/* 0x20 */ void *src;
	/* 0x24 */ void *dest;
	/* 0x28 */ int size;
	/* 0x2c */ int unk2C[5];
} sifRpcOtherPkt_t;

/* Reboot notification handler entry. */
typedef struct sifNotifyHandler {
	/* 0x00 */ void *func;
	/* 0x04 */ void *data;
	/* 0x08 */ int gp;
	/* 0x0c */ int unk0C;
} sifNotifyHandler_t;

/* Load-file RPC buffer at sdkLoadFileBuffer. */
typedef struct sifSearchBuffer {
	/* 0x000 */ int result;
	/* 0x004 */ int unk04;
	/* 0x008 */ char name[0x100];
} sifSearchBuffer_t;

/* TTY ring queue header; the data follows at +0x10. */
typedef struct ttyQueue {
	/* 0x00 */ int size;
	/* 0x04 */ int count;
	/* 0x08 */ char *read;
	/* 0x0c */ char *write;
} ttyQueue_t;

/* DECI2 TTY protocol state at sdkTty; the DECI2 handler updates the volatile fields. */
typedef struct ttyData {
	/* 0x00 */ volatile int socket;
	/* 0x04 */ volatile int wlen;
	/* 0x08 */ volatile int rlen;
	/* 0x0c */ volatile int busy;
	/* 0x10 */ char *sendHeader;
	/* 0x14 */ char *recvBuffer;
	/* 0x18 */ ttyQueue_t *queue;
} ttyData_t;

/* File-system I/O block (32 entries at sdkFsIob). */
typedef struct fsIob {
	/* 0x00 */ int unk00;
	/* 0x04 */ int mode;
	/* 0x08 */ int unk08;
	/* 0x0c */ int unk0C;
} fsIob_t;

/* Software timer counter (64-byte aligned; its address is encoded in the counter ID). */
typedef struct timerCounter {
	/* 0x00 */ struct timerCounter *next;
	/* 0x04 */ struct timerCounter *prev;
	/* 0x08 */ volatile int key;
	/* 0x0c */ unsigned int mode;
	/* 0x10 */ unsigned long base;
	/* 0x18 */ unsigned long total;
	/* 0x20 */ unsigned long compare;
	/* 0x28 */ void *handler;
	/* 0x2c */ int gp;
	/* 0x30 */ void *arg;
	/* 0x34 */ int unk34[3];
} timerCounter_t;

/* Timer state at sdkTimer. */
typedef struct timerData {
	/* 0x00 */ long highCount;
	/* 0x08 */ int unk08;
	/* 0x0c */ volatile int seq;
	/* 0x10 */ volatile int used;
	/* 0x14 */ timerCounter_t *freeList;
	/* 0x18 */ timerCounter_t *alarmList;
	/* 0x1c */ volatile int systemId;
} timerData_t;

/* Alarm entry (64 at sdkAlarms, free list at sdkAlarmFree). */
typedef struct timerAlarm {
	/* 0x00 */ struct timerAlarm *next;
	/* 0x04 */ volatile int counterId;
	/* 0x08 */ int (*func)(int, int, int, void *);
	/* 0x0c */ void *arg;
} timerAlarm_t;

/* newlib stat fields written by fstat. */
typedef struct kernelStat {
	/* 0x00 */ int unk00;
	/* 0x04 */ unsigned int mode;
	/* 0x08 */ char unk08[0x40];
	/* 0x48 */ long blocks;
} kernelStat_t;

/* OSD configuration word (Get/SetOsdConfigParam). */
typedef struct osdConfig {
	/* 0x00 */ unsigned int spdifMode : 1;
	unsigned int screenType : 2;
	unsigned int videoOutput : 1;
	unsigned int japLanguage : 1;
	unsigned int ps1drvConfig : 8;
	unsigned int version : 3;
	unsigned int language : 5;
	unsigned int timezoneOffset : 11;
} osdConfig_t;

/* Kernel patch entry: syscall number and handler (sdk*PatchTable). */
typedef struct kernelPatch {
	/* 0x00 */ int syscall;
	/* 0x04 */ void *func;
} kernelPatch_t;

/* EE kernel thread parameters (CreateThread). */
typedef struct kernelThreadParam {
	/* 0x00 */ int status;
	/* 0x04 */ void *func;
	/* 0x08 */ void *stack;
	/* 0x0c */ int stackSize;
	/* 0x10 */ void *gpReg;
	/* 0x14 */ int initPriority;
	/* 0x18 */ int currentPriority;
	/* 0x1c */ unsigned int attr;
	/* 0x20 */ const char *option;
} kernelThreadParam_t;

/* Thread request queued for topThread. */
typedef struct threadRequest {
	/* 0x00 */ unsigned char command;
	/* 0x01 */ unsigned char threadId;
} threadRequest_t;

/* topThread request ring at sdkThreadQueue. */
typedef struct threadQueue {
	/* 0x000 */ int index;
	/* 0x004 */ int unk04;
	/* 0x008 */ threadRequest_t requests[0x200];
} threadQueue_t;

/* Four-byte module version stamp. */
typedef struct kernelVersion {
	/* 0x00 */ char data[4];
} kernelVersion_t;

/* EE kernel semaphore parameters. */
typedef struct kernelSemaParam {
	/* 0x00 */ int count;
	/* 0x04 */ int maxCount;
	/* 0x08 */ int initCount;
	/* 0x0c */ int waitThreads;
	/* 0x10 */ unsigned int attr;
	/* 0x14 */ const char *option;
} kernelSemaParam_t;

#endif
