#include "common.h"
#include "libmrpc.h"

/* Recovered directly from the retail boot instructions; no vendor source. */
#define MRPC_SECTION(name) __attribute__((section(".mrpc_" #name)))

/* Functions not yet recovered, and original padding words, stay in their own slots. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
	__asm__(".section .mrpc_" #NAME ",\"ax\",@progbits\n" \
		".set noat\n.set noreorder\n" \
		".include \"" FOLDER "/" #NAME ".s\"\n" \
		".set reorder\n.set at\n.text\n")
#endif

extern int sdkMRpcInit;
extern mrpcPool_t sdkMRpcPool;
extern mrpcPkt_t sdkMRpcPackets[0x20];
extern const char sdkMRpcNoWaitMsg[];
extern const char sdkMRpcBindSemaName[];
extern const char sdkMRpcCallSemaName[];
extern const char sdkMRpcUnbindSemaName[];
extern int DIntr(void);
extern int EIntr(void);
extern int CreateSema(mrpcSemaParam_t *);
extern int DeleteSema(int);
extern int WaitSema(int);
extern void scePrintf(const char *, ...);
extern int sceSifSendCmd(int, void *, int, void *, void *, int);
extern int sceSifAddCmdHandler(int, void *, void *);
extern void sceSifRemoveCmdHandler(int);
extern int sceSifGetSreg(int);
extern int sceSifSetSreg(int, int);
extern int sceSifAddRebootNotifyHandler(int, void *, void *);
extern int sceSifRemoveRebootNotifyHandler(int);
extern void _request_end___dupe2(mrpcEndPkt_t *, void *);
extern int iSignalSema(int);
/* D15: retail reads $gp through a volatile move that also orders the surrounding stores. */
#define GET_GP(x) __asm__ volatile("move %0, $28" : "=r"(x))
/* D16: retail swaps $gp as one move pair around the callback. */
static inline int changeGp(int gp)
{
	int old;
	__asm__ volatile("move %0, $28\n\tmove $28, %1" : "=&r"(old) : "r"(gp) : "memory");
	return old;
}
extern const char sdkMRpcSendAlignMsg[];
extern const char sdkMRpcFuncName[];
extern const char sdkMRpcRecvAlignMsg[];
extern const char sdkMRpcCallSemaName2[];
extern void sceSifWriteBackDCache(void *, int);
void _iopnotify(int mode);
mrpcPkt_t *_sceRpcGetPacket___dupe2(mrpcPool_t *rpc);
void _sceRpcFreePacket___dupe2(mrpcPkt_t *packet);

void MRPC_SECTION(sceSifMInitRpc) sceSifMInitRpc(int mode)
{
	mrpcPkt_t *packet;
	if (sdkMRpcInit) return;
	sdkMRpcInit = 1;
	DIntr();
	sdkMRpcPool.count = 0x20;
	sdkMRpcPool.packets = (mrpcPkt_t *)((unsigned int)sdkMRpcPackets | 0x20000000);
	sdkMRpcPool.pid = 1;
	sdkMRpcPool.unk0C = 0;
	sdkMRpcPool.unk10 = 0;
	sceSifAddCmdHandler(0x80000018, _request_end___dupe2, &sdkMRpcPool);
	EIntr();
	packet = &sdkMRpcPackets[1];
	packet->mode = 1;
	packet->paddr = (void *)1;
	sceSifSendCmd(0x80000001, packet, 0x18, 0, 0, 0);
	while (!sceSifGetSreg(1)) {}
	sceSifAddRebootNotifyHandler(0x80000014, _iopnotify, 0);
}

void MRPC_SECTION(_iopnotify) _iopnotify(int mode)
{
	if (mode == 1) {
		sdkMRpcInit = 0;
		sceSifSetSreg(1, 0);
	}
}

void MRPC_SECTION(sceSifMExitRpc) sceSifMExitRpc(void)
{
	sdkMRpcInit = 0;
	sceSifRemoveCmdHandler(0x80000018);
	sceSifRemoveRebootNotifyHandler(0x80000014);
}

mrpcPkt_t *MRPC_SECTION(_sceRpcGetPacket___dupe2) _sceRpcGetPacket___dupe2(mrpcPool_t *rpc)
{
	mrpcPkt_t *packet;
	int i, count, id;
	DIntr();
	count = rpc->count;
	packet = rpc->packets;
	for (i = 0; i < count; i++, packet++) {
		if (!(packet->mode & 1)) {
			packet->mode = (i << 16) | 5;
			if (++rpc->pid == 1) {
				rpc->pid++;
				id = 1;
			} else id = rpc->pid;
			packet->paddr = packet;
			packet->pid = id;
			EIntr();
			return packet;
		}
	}
	EIntr();
	return 0;
}

void MRPC_SECTION(_sceRpcFreePacket___dupe2) _sceRpcFreePacket___dupe2(mrpcPkt_t *packet)
{
	packet->pid = 0;
	packet->mode &= ~1;
}

void MRPC_SECTION(_request_end___dupe2) _request_end___dupe2(mrpcEndPkt_t *pkt, void *data)
{
	mrpcEndClient_t *c, *d;
	switch (pkt->cid) {
	case 0x8000001a:
		c = pkt->client;
		if (c->endFunc) {
			int old = changeGp(c->gp);
			c->endFunc(c->endParam);
			changeGp(old);
		}
		iSignalSema(c->bindSema);
		break;
	case 0x80000019:
		c = pkt->client;
		c->server = pkt->arg24;
		c->buffer = pkt->arg28;
		iSignalSema(c->bindSema);
		break;
	case 0x8000001c:
		break;
	case 0x8000001d:
		c = pkt->client;
		c->result = pkt->arg24;
		iSignalSema(c->bindSema);
		break;
	}
	d = pkt->client;
	if (d->sema >= 0) iSignalSema(d->sema);
	_sceRpcFreePacket___dupe2(d->packet);
	d->packet = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mrpc/libmrpc", func_00155E08);

int MRPC_SECTION(sceSifMBindRpcParam) sceSifMBindRpcParam(mrpcClient_t *client, int rpc, int mode, int param0, int param1, int param2)
{
	mrpcSemaParam_t param;
	mrpcPkt_t *packet;
	int sema;
	if (mode) {
		scePrintf(sdkMRpcNoWaitMsg);
		return -1;
	}
	param.initCount = 1;
	param.option = sdkMRpcBindSemaName;
	param.maxCount = 1;
	client->bindSema = CreateSema(&param);
	if (client->bindSema < 0) return -3;
	WaitSema(client->bindSema);
	client->command = rpc;
	client->server = 0;
	client->param0 = param0;
	client->param1 = param1;
	client->param2 = param2;
	packet = _sceRpcGetPacket___dupe2(&sdkMRpcPool);
	if (!packet) {
		DeleteSema(client->bindSema);
		return -1;
	}
	client->packet = packet;
	client->rpcId = packet->pid;
	packet->cid = rpc;
	packet->arg24 = param0;
	packet->arg28 = param1;
	packet->arg2C = param2;
	packet->paddr = packet;
	packet->client = client;
	param.maxCount = 1;
	param.option = sdkMRpcCallSemaName;
	param.initCount = 0;
	client->sema = CreateSema(&param);
	sema = client->sema;
	if (sema < 0) {
		_sceRpcFreePacket___dupe2(packet);
		DeleteSema(client->bindSema);
		return -3;
	}
	if (!sceSifSendCmd(0x80000019, packet, 0x40, 0, 0, 0)) {
		_sceRpcFreePacket___dupe2(packet);
		DeleteSema(sema);
		DeleteSema(client->bindSema);
		return -2;
	}
	WaitSema(sema);
	DeleteSema(sema);
	if (!client->server) DeleteSema(client->bindSema);
	return 0;
}

int MRPC_SECTION(sceSifMUnBindRpc) sceSifMUnBindRpc(mrpcClient_t *client, int mode)
{
	mrpcSemaParam_t param;
	mrpcPkt_t *packet;
	int sema;
	if (mode) {
		scePrintf(sdkMRpcNoWaitMsg);
		return -1;
	}
	WaitSema(client->bindSema);
	packet = _sceRpcGetPacket___dupe2(&sdkMRpcPool);
	if (!packet) return -1;
	client->packet = packet;
	client->rpcId = packet->pid;
	/* Int views keep retail's store order: the alias class decides what GCC may reorder. */
	*(int *)&packet->paddr = (int)packet;
	packet->cid = client->command;
	*(int *)&packet->client = (int)client;
	packet->arg24 = client->server;
	*(int *)&param.option = (int)sdkMRpcUnbindSemaName;
	param.initCount = 0;
	param.maxCount = 1;
	client->sema = CreateSema(&param);
	sema = client->sema;
	if (sema < 0) {
		_sceRpcFreePacket___dupe2(packet);
		return -3;
	}
	if (!sceSifSendCmd(0x8000001d, packet, 0x40, 0, 0, 0)) {
		_sceRpcFreePacket___dupe2(packet);
		DeleteSema(sema);
		return -2;
	}
	WaitSema(sema);
	DeleteSema(sema);
	if (*(volatile int *)&client->result == 1) DeleteSema(client->bindSema);
	return *(volatile int *)&client->result;
}

int MRPC_SECTION(sceSifMCallRpc) sceSifMCallRpc(mrpcCallClient_t *client, int rpc, int mode, void *send, int ssize, void *recv, int rsize, void *endFunc, void *endParam)
{
	mrpcSemaParam_t param;
	mrpcCallPkt_t *packet;
	int gp, sema;
	if (mode) {
		scePrintf(sdkMRpcNoWaitMsg);
		return -1;
	}
	WaitSema(*(int *)&client->bindSema);
	if ((unsigned int)send & 0x3f) {
		scePrintf(sdkMRpcSendAlignMsg, sdkMRpcFuncName, send);
		return -1;
	}
	if ((unsigned int)recv & 0x3f) {
		scePrintf(sdkMRpcRecvAlignMsg, sdkMRpcFuncName, recv);
		return -1;
	}
	packet = (mrpcCallPkt_t *)_sceRpcGetPacket___dupe2(&sdkMRpcPool);
	if (!packet) return -1;
	client->endParam = endParam;
	client->rpcId = packet->pid;
	client->packet = packet;
	client->endFunc = endFunc;
	GET_GP(gp);
	client->gp = gp;
	packet->cid = rpc;
	packet->paddr = (int)packet;
	packet->arg24 = ssize;
	packet->arg28 = (int)recv;
	packet->arg2C = rsize;
	packet->client = (int)client;
	packet->server = client->server;
	if (send == recv) {
		sceSifWriteBackDCache(send, ssize < rsize ? rsize : ssize);
	} else {
		if (ssize > 0) sceSifWriteBackDCache(send, ssize);
		if (rsize > 0) sceSifWriteBackDCache(recv, rsize);
	}
	if (mode & 1) {
		if (!endFunc) packet->rmode = 0;
		else packet->rmode = 1;
		client->sema = -1;
		if (sceSifSendCmd(0x8000001a, packet, 0x40, send, (void *)client->buffer, ssize)) return 0;
		_sceRpcFreePacket___dupe2((mrpcPkt_t *)packet);
		return -2;
	}
	param.initCount = 0;
	param.option = sdkMRpcCallSemaName2;
	param.maxCount = 1;
	sema = CreateSema(&param);
	*(int *)&client->sema = sema;
	if (sema < 0) {
		_sceRpcFreePacket___dupe2((mrpcPkt_t *)packet);
		return -3;
	}
	packet->rmode = 1;
	if (!sceSifSendCmd(0x8000001a, packet, 0x40, send, (void *)client->buffer, ssize)) {
		_sceRpcFreePacket___dupe2((mrpcPkt_t *)packet);
		DeleteSema(sema);
		return -2;
	}
	WaitSema(sema);
	DeleteSema(sema);
	return 0;
}
