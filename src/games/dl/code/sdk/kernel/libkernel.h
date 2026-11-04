#ifndef SDK_KERNEL_LIBKERNEL_H
#define SDK_KERNEL_LIBKERNEL_H

/* EE (EABI, single-float) varargs from GCC's va-mips.h; this compiler has no stdarg.h. */
typedef char *va_list;
#define va_start(ap, last) (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8))
#define va_arg(ap, type) (*(type *)((ap += 8) - 8))
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
	/* 0x0c */ int unk0C;
	/* 0x10 */ int unk10;
	/* 0x14 */ char *recvBuffers;
	/* 0x18 */ int recvCount;
	/* 0x1c */ char *fixed;
	/* 0x20 */ int fixedCount;
	/* 0x24 */ int index;
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

/* RPC request/reply packet as seen by the EE-side request handlers (untyped argument words). */
typedef struct sifRpcReqPkt {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ unsigned int mode;
	/* 0x14 */ void *paddr;
	/* 0x18 */ int pid;
	/* 0x1c */ void *client;
	/* 0x20 */ void *cid;
	/* 0x24 */ void *arg24;
	/* 0x28 */ void *arg28;
	/* 0x2c */ void *arg2C;
	/* 0x30 */ int unk30[4];
} sifRpcReqPkt_t;

/* Leading fields of an RPC server registration returned by _search_svdata. */
typedef struct sifRpcServerHead {
	/* 0x00 */ int sid;
	/* 0x04 */ int unk04;
	/* 0x08 */ void *buffer;
} sifRpcServerHead_t;

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

/* SIF command packet header. */
typedef struct sifCmdHeader {
	/* 0x00 */ unsigned int psize : 8;
	unsigned int dsize : 24;
	/* 0x04 */ void *dest;
	/* 0x08 */ int cid;
	/* 0x0c */ unsigned int opt;
} sifCmdHeader_t;

/* SIF DMA transfer descriptor (sceSifSetDma). */
typedef struct sifDmaTransfer {
	/* 0x00 */ void *src;
	/* 0x04 */ void *dest;
	/* 0x08 */ int size;
	/* 0x0c */ int attr;
} sifDmaTransfer_t;

/* IOP reset command packet; 16-byte aligned because retail clears the header with 64-bit accesses. */
typedef struct sifResetPacket {
	/* 0x00 */ sifCmdHeader_t header;
	/* 0x10 */ int argLength;
	/* 0x14 */ int mode;
	/* 0x18 */ char arg[0x50];
} __attribute__((aligned(16))) sifResetPacket_t;

/* Module argument block copied into the load-file buffer. */
typedef struct sifLoadArgs {
	/* 0x00 */ char data[0xfc];
} sifLoadArgs_t;

/* Load-file RPC buffer layout used by the module load/stop requests (overlays sdkLoadFileBuffer). */
typedef struct sifLoadModuleBuffer {
	/* 0x000 */ int value;
	/* 0x004 */ int argLength;
	/* 0x008 */ char path[0xfc];
	/* 0x104 */ sifLoadArgs_t args;
} sifLoadModuleBuffer_t;

/* All-int view of a server registration: _request_call copies its words in source order. */
typedef struct sifRpcCallServer {
	/* 0x00 */ int sid;
	/* 0x04 */ int unk04[2];
	/* 0x0c */ int size;
	/* 0x10 */ int unk10[3];
	/* 0x1c */ int client;
	/* 0x20 */ int pktAddr;
	/* 0x24 */ int rpcNumber;
	/* 0x28 */ int recvBuf;
	/* 0x2c */ int rsize;
	/* 0x30 */ int rmode;
	/* 0x34 */ int rid;
	/* 0x38 */ int next;
	/* 0x3c */ int link;
	/* 0x40 */ struct sifRpcCallQueue *base;
} sifRpcCallServer_t;

/* All-int view of a receive queue, for _request_call. */
typedef struct sifRpcCallQueue {
	/* 0x00 */ int threadId;
	/* 0x04 */ int active;
	/* 0x08 */ int link;
	/* 0x0c */ int start;
	/* 0x10 */ int end;
	/* 0x14 */ int next;
} sifRpcCallQueue_t;

/* RPC call request as received by _request_call. */
typedef struct sifRpcCallReq {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ int mode;
	/* 0x14 */ int paddr;
	/* 0x18 */ int pid;
	/* 0x1c */ int client;
	/* 0x20 */ int rpcNumber;
	/* 0x24 */ int sendSize;
	/* 0x28 */ int recv;
	/* 0x2c */ int recvSize;
	/* 0x30 */ int rmode;
	/* 0x34 */ sifRpcCallServer_t *server;
} sifRpcCallReq_t;

/* Packet sent by sceSifInitRpc to request the IOP RPC init. */
typedef struct sifRpcInitPkt {
	/* 0x00 */ int header[3];
	/* 0x0c */ int opt;
	/* 0x10 */ int unk10[12];
} sifRpcInitPkt_t;

/* Client layout used by sceSifCallRpc; words it only copies are int. */
typedef struct sifRpcCallClient {
	/* 0x00 */ void *packet;
	/* 0x04 */ int rpcId;
	/* 0x08 */ int sema;
	/* 0x0c */ unsigned int mode;
	/* 0x10 */ unsigned int command;
	/* 0x14 */ int buffer;
	/* 0x18 */ int gp;
	/* 0x1c */ void *endFunc;
	/* 0x20 */ void *endParam;
	/* 0x24 */ int server;
} sifRpcCallClient_t;

/* RPC call packet built by sceSifCallRpc. */
typedef struct sifRpcCallPkt {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ unsigned int mode;
	/* 0x14 */ int paddr;
	/* 0x18 */ int pid;
	/* 0x1c */ int client;
	/* 0x20 */ int rpcNumber;
	/* 0x24 */ int sendSize;
	/* 0x28 */ int recv;
	/* 0x2c */ int recvSize;
	/* 0x30 */ int rmode;
	/* 0x34 */ int server;
	/* 0x38 */ int unk38[2];
} sifRpcCallPkt_t;

/* Int view of a DMA descriptor, as _sceSifSendCmd fills it. */
typedef struct sifCmdDma {
	/* 0x00 */ int src;
	/* 0x04 */ int dest;
	/* 0x08 */ int size;
	/* 0x0c */ int attr;
} sifCmdDma_t;

/* RPC completion packet handled by _request_end. */
typedef struct sifRpcEndPkt {
	/* 0x00 */ int unk00[7];
	/* 0x1c */ void *client;
	/* 0x20 */ unsigned int cid;
	/* 0x24 */ int server;
	/* 0x28 */ int buffer;
} sifRpcEndPkt_t;

/* Client view used by _request_end. */
typedef struct sifRpcEndClient {
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
} sifRpcEndClient_t;

/* Power-off callback registration passed to _sceFs_Poff_Intr. */
typedef struct fsPoffData {
	/* 0x00 */ void (*cb)(int);
	/* 0x04 */ int arg;
} fsPoffData_t;

/* TLB layout read by InitTLB32MB; names are inferred from its boot message. */
typedef struct tlbEntry {
	/* 0x00 */ unsigned int pageMask;
	/* 0x04 */ unsigned int entryHi;
	/* 0x08 */ unsigned int entryLo0;
	/* 0x0c */ unsigned int entryLo1;
} tlbEntry_t;
typedef struct tlbInfo {
	/* 0x00 */ int kernelCount;
	/* 0x04 */ int defaultCount;
	/* 0x08 */ int extendedCount;
	/* 0x0c */ int wired;
	/* 0x10 */ tlbEntry_t *kernel;
	/* 0x14 */ tlbEntry_t *def;
	/* 0x18 */ tlbEntry_t *extended;
} tlbInfo_t;

/* Request sent by sceFsInit: the shared receive buffer range. */
typedef struct fsInitRequest {
	/* 0x00 */ void *buffer;
	/* 0x04 */ void *end;
} fsInitRequest_t;

/* Four-byte version word copied without an alignment assumption. */
typedef struct fsVersion {
	/* 0x00 */ char data[4];
} fsVersion_t;

typedef unsigned int sifQword __attribute__((mode(TI)));

/* Head of a received SIF command packet; the size field is written back to mark it consumed. */
typedef struct sifCmdIntrPkt {
	/* 0x00 */ unsigned int size:8;
	unsigned int dsize:24;
	/* 0x04 */ int unk04;
	/* 0x08 */ int cid;
} sifCmdIntrPkt_t;

/* Thread status from ReferThreadStatus; only the fields StartThread reads are named. */
typedef struct threadStat {
	/* 0x00 */ int status;
	/* 0x04 */ void *func;
	/* 0x08 */ char *stack;
	/* 0x0c */ int stackSize;
	/* 0x10 */ int unk10[8];
} threadStat_t;

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

/* File-system close request (shares sdkFsRequest with the other requests). */
typedef struct fsCloseRequest {
	/* 0x00 */ int sema;
	/* 0x04 */ int *result;
	/* 0x08 */ int size;
	/* 0x0c */ int fd;
	/* 0x10 */ int index;
} fsCloseRequest_t;

/* File-system open request. */
typedef struct fsOpenRequest {
	/* 0x000 */ int sema;
	/* 0x004 */ int *result;
	/* 0x008 */ int size;
	/* 0x00c */ int flags;
	/* 0x010 */ int mode;
	/* 0x014 */ char name[0x400];
	/* 0x414 */ int index;
} fsOpenRequest_t;

/* File-system devctl request. */
typedef struct fsDevctlRequest {
	/* 0x000 */ int sema;
	/* 0x004 */ int *result;
	/* 0x008 */ int size;
	/* 0x00c */ char name[0x400];
	/* 0x40c */ char arg[0x400];
	/* 0x80c */ int cmd;
	/* 0x810 */ unsigned int arglen;
	/* 0x814 */ void *buf;
	/* 0x818 */ unsigned int buflen;
} fsDevctlRequest_t;

/* DMA descriptor passed as a devctl argument. */
typedef struct fsDevctlDma {
	/* 0x00 */ int unk00;
	/* 0x04 */ int size;
	/* 0x08 */ void *addr;
	/* 0x0c */ int count;
} fsDevctlDma_t;

/* File-system seek, read and write request (shares sdkFsRequest with the other requests). */
typedef struct fsRwRequest {
	/* 0x00 */ int sema;
	/* 0x04 */ int *result;
	/* 0x08 */ int resultSize;
	/* 0x0c */ int fd;
	/* 0x10 */ int arg[4];
} fsRwRequest_t;

/* RPC argument buffer at sdkFsRequest. */
typedef union fsRequest {
	fsCloseRequest_t close;
	fsOpenRequest_t open;
	fsDevctlRequest_t devctl;
	fsRwRequest_t rw;
} fsRequest_t;

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
	/* 0x08 */ int intcHandlerId;
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
	int timezoneOffset : 11;
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
