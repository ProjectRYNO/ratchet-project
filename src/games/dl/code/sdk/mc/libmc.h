#ifndef SDK_MC_LIBMC_H
#define SDK_MC_LIBMC_H

/* Read alignment fix-up block shared with the IOP (sdkMcReadFix, accessed uncached). */
typedef struct mcReadFix {
	/* 0x00 */ int headLen;
	/* 0x04 */ int tailLen;
	/* 0x08 */ char *headDst;
	/* 0x0c */ char *tailDst;
	/* 0x10 */ char head[0x40];
	/* 0x50 */ char tail[0x40];
	/* 0x90 */ int unk90[12];
} mcReadFix_t;

/* 0x30-byte request at sdkMcRequest; fields 0x0c..0x14 are command-specific parameters. */
typedef struct mcRequest {
	/* 0x00 */ int fd;
	/* 0x04 */ int port;
	/* 0x08 */ int slot;
	/* 0x0c */ int size;
	/* 0x10 */ int offset;
	/* 0x14 */ int origin;
	/* 0x18 */ void *buffer;
	/* 0x1c */ mcReadFix_t *fix;
	/* 0x20 */ unsigned char data[16];
} mcRequest_t;

/* 0x414-byte path request at sdkMcNameRequest (open, delete, directory listing). */
typedef struct mcNameRequest {
	/* 0x000 */ int port;
	/* 0x004 */ int slot;
	/* 0x008 */ int flags;
	/* 0x00c */ int maxent;
	/* 0x010 */ void *table;
	/* 0x014 */ char name[0x400];
} mcNameRequest_t;

/* EE kernel semaphore parameters. */
typedef struct mcSemaParam {
	/* 0x00 */ int count;
	/* 0x04 */ int maxCount;
	/* 0x08 */ int initCount;
	/* 0x0c */ int waitThreads;
	/* 0x10 */ unsigned int attr;
	/* 0x14 */ const char *option;
} mcSemaParam_t;

int sceMcInit(void);
int sceMcEnd(void);
int sceMcOpen(int port, int slot, const char *name, int mode);
int sceMcMkdir(int port, int slot, const char *name);
int sceMcClose(int fd);
int sceMcSeek(int fd, int offset, int origin);
int sceMcRead(int fd, void *buffer, int size);
int sceMcWrite(int fd, const void *buffer, int size);
int sceMcSync(int mode, int *cmd, int *result);
int sceMcGetInfo(int port, int slot, int *type, int *free, int *format);
int sceMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, void *table);
int sceMcFormat(int port, int slot);
int sceMcDelete(int port, int slot, const char *name);
int sceMcUnformat(int port, int slot);
void mceSifRpcEndFunc(void *arg);
void mceIntrReadFixAlign(mcReadFix_t *arg);
void mceGetInfoApdx(void *arg);

#endif
