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
extern void _request_end___dupe2(void *, void *);
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mrpc/libmrpc", _request_end___dupe2);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mrpc/libmrpc", sceSifMUnBindRpc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mrpc/libmrpc", sceSifMCallRpc);
