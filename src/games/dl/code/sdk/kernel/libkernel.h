#ifndef SDK_KERNEL_LIBKERNEL_H
#define SDK_KERNEL_LIBKERNEL_H

/* SIF command handler entry (system and user tables). */
typedef struct sifCmdHandler {
	/* 0x00 */ void *func;
	/* 0x04 */ void *data;
	/* 0x08 */ int gp;
} sifCmdHandler_t;

/* SIF command state at sdkSifCmd; only the handler table fields are recovered. */
typedef struct sifCmdData {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ sifCmdHandler_t *sysHandlers;
	/* 0x10 */ int sysCount;
	/* 0x14 */ sifCmdHandler_t *usrHandlers;
} sifCmdData_t;

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
	/* 0x08 */ int key;
	/* 0x0c */ unsigned int mode;
	/* 0x10 */ unsigned long base;
	/* 0x18 */ unsigned long total;
	/* 0x20 */ unsigned long compare;
	/* 0x28 */ void *handler;
	/* 0x2c */ void *arg;
	/* 0x30 */ int unk30[4];
} timerCounter_t;

/* Timer state at sdkTimer. */
typedef struct timerData {
	/* 0x00 */ long highCount;
	/* 0x08 */ int unk08;
	/* 0x0c */ int seq;
	/* 0x10 */ int used;
	/* 0x14 */ timerCounter_t *freeList;
	/* 0x18 */ timerCounter_t *alarmList;
	/* 0x1c */ int systemId;
} timerData_t;

/* Alarm entry (64 at sdkAlarms, free list at sdkAlarmFree). */
typedef struct timerAlarm {
	/* 0x00 */ struct timerAlarm *next;
	/* 0x04 */ int unk04;
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
