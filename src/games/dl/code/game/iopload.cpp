#include "common.h"
#include "game_section.h"
#include "fs.h"
#include "gameglobals.h"


extern int iopInitialized __asm__("D_21DD38");
void pad_Init() __asm__("pad_Init");
void sound_Init() __asm__("sound_Init");
extern "C" void sceSifMInitRpc(int);
extern "C" void sceSifMExitRpc();
extern "C" void snd_CloseVAGStreaming();
int DefaultIOPModuleUnloadCallback(int *) __asm__("DefaultIOPModuleUnloadCallback");
void DisplayIOPInfo() __asm__("DisplayIOPInfo");
int InitializeAstrm() __asm__("InitializeAstrm");
int StreamerLoadCallback() __asm__("StreamerLoadCallback");
int PadCallback() __asm__("PadCallback");
int SoundCallback() __asm__("SoundCallback");
int LibNetBCallback() __asm__("LibNetBCallback");
void InitializeIOP() __asm__("InitializeIOP");
int LibNetBUnloadCallback(int *module) __asm__("LibNetBUnloadCallback");
int AstrmDestroyStreams() __asm__("AstrmDestroyStreams");



typedef struct iopLoadEntry {
	/* 0x00 */ int module;
	/* 0x04 */ void *condition;
	/* 0x08 */ void *load;
	/* 0x0c */ void *unload;
} iopLoadEntry_t;
typedef struct nwInfoFlags {
	/* 0x000 */ int state;
	/* 0x004 */ char unk04[0x260];
	/* 0x264 */ unsigned char useNet;
	/* 0x265 */ char unk265[0x100];
} nwInfoFlags_t;
typedef struct nwInfoCnf {
	/* 0x00 */ unsigned char useCnf;
	/* 0x01 */ char unk01[0x100];
} nwInfoCnf_t;
extern iopLoadEntry_t g_iopload_function_table[] __asm__("g_iopload_function_table");
int g_iopload_function_table_size __asm__("g_iopload_function_table_size") GAME_GP_DATA = 0;
extern unsigned char g_iopload_core_modules_initialized __asm__("g_iopload_core_modules_initialized");
extern unsigned char g_iopload_singleplayer_modules_loaded __asm__("g_iopload_singleplayer_modules_loaded");
extern unsigned char g_iopload_multiplayer_modules_loaded __asm__("g_iopload_multiplayer_modules_loaded");
extern nwInfoFlags_t g_nwInfo __asm__("g_nwInfo");
extern nwInfoCnf_t g_nwInfoCnf __asm__("D_1723C4");
int UnloadIOPModule(int) __asm__("UnloadIOPModule");
extern "C" void ezNetCnfInit();
extern "C" void ezNetCtlInit();
extern "C" void lgKbMInit(int, int, int, unsigned long (*)());
extern "C" void lgKbMSuspendThread();
unsigned long nwKbdTimerFunc() __asm__("nwKbdTimerFunc");
int AstrmCreateStreams(int, int) __asm__("AstrmCreateStreams");
void *GetModuleLoadCondition(int module) __asm__("GetModuleLoadCondition");
void *GetModuleLoadCallback(int module) __asm__("GetModuleLoadCallback");
void *GetModuleUnloadCallback(int module) __asm__("GetModuleUnloadCallback");
int EZNetCnfCallback() __asm__("EZNetCnfCallback");
int EZNetCtlCallback() __asm__("EZNetCtlCallback");
int LgKbmCallback() __asm__("LgKbmCallback");
void UninitializeCoreIOPModules() __asm__("UninitializeCoreIOPModules");
void InitializeCoreIOPModules() __asm__("InitializeCoreIOPModules");

struct IopDataBlock {
	/* 0x0 */ int offset;
	/* 0x4 */ int length;
};
struct IOPMODULELOAD {
	/* 0x000 */ int module_id;
	/* 0x004 */ int unk004;
	/* 0x008 */ int load_size;
	/* 0x00c */ int unload_size;
	/* 0x010 */ int size_diff;
	/* 0x014 */ int argument_size;
	/* 0x018 */ char arguments[256];
	/* 0x118 */ char name[64];
	/* 0x158 */ unsigned char loaded;
	/* 0x159 */ char unk159[3];
	/* 0x15c */ void *irx_data;
	/* 0x160 */ IopDataBlock *irx_module;
	/* 0x164 */ int function_set;
};
struct IOPMODULELOADQUEUE {
	/* 0x0000 */ int num_iop_modules;
	/* 0x0004 */ int max_size;
	/* 0x0008 */ int actual_load_size;
	/* 0x000c */ int expected_load_size;
	/* 0x0010 */ IOPMODULELOAD iop_modules[25];
};
extern int g_iopload_single_gadgetcache_size __asm__("D_21DD4C");
extern int g_iopload_single_astrm_size __asm__("D_21DD48");
extern int g_iopload_multi_size __asm__("D_21DD44");
extern IOPMODULELOADQUEUE g_iopload_multiplayer_queues[1] __asm__("g_iopload_multiplayer_queues");
extern char g_iopload_multiplayer_unload_message[] __asm__("D_3D08A8");
extern "C" {
	int sceSifStopModule(int, int, const char *, int *);
	int sceSifUnloadModule(int);
	int snd_InitVAGStreamingEx(int, int, int, int);
	int ezNetCnfExit(void *);
	int lgKbMResumeThread(void *);
	int lgKbMUnloadIopModule();
}
bool EZNetCnfUnloadCallback(void *) __asm__("EZNetCnfUnloadCallback");
bool LgKbmUnloadCallback(void *) __asm__("LgKbmUnloadCallback");
void ClearIOPModuleQueue(IOPMODULELOADQUEUE *) __asm__("ClearIOPModuleQueue");
void ClearIOPModuleQueueSet(IOPMODULELOADQUEUE *, int) __asm__("ClearIOPModuleQueueSet");
void UnloadIOPModuleQueue(IOPMODULELOADQUEUE *) __asm__("UnloadIOPModuleQueue");
void UnloadIOPModuleQueueSet(IOPMODULELOADQUEUE *, int, char *) __asm__("UnloadIOPModuleQueueSet");
void LoadSinglePlayerIOPModules(void *) __asm__("LoadSinglePlayerIOPModules");
void UnloadSinglePlayerIOPModules() __asm__("UnloadSinglePlayerIOPModules");
void UnloadMultiPlayerIOPModules() __asm__("UnloadMultiPlayerIOPModules");

struct ezNetCtlStatus {
	/* 0x00 */ int unk00[12];
	/* 0x30 */ int state;
	/* 0x34 */ int unk34[3];
};
typedef int (*IOPLOAD_UNLOAD_CALLBACK)(IOPMODULELOAD *);
extern "C" {
	int sceSifSearchModuleByName(const char *);
	int sceSifQueryTotalFreeMemSize();
	int ezNetCtlGetStatus(ezNetCtlStatus *, char *, int);
	int ezNetCtlDownInterface();
	int ezNetCtlExit(int);
	int DelayThread(int);
}
extern char g_dev9ModuleName[] __asm__("D_21EF20");
void PreparePowerOff() __asm__("PreparePowerOff");
void nwGuiRefreshCallback() __asm__("nwGuiRefreshCallback");
unsigned char Dev9Callback() __asm__("Dev9Callback");
bool EZNetCtlUnloadCallback(void *) __asm__("EZNetCtlUnloadCallback");

extern "C" char *strncpy(char *, const char *, unsigned int);
void FastMemSet(void *, int, int) __asm__("FastMemSet");
void FastMemCopy(void *, const void *, int) __asm__("FastMemCopy");
void QueueIOPModuleLoad(IOPMODULELOADQUEUE *, char *, void *, void *, int, int, char *, int) __asm__("QueueIOPModuleLoad");
struct sceSifDmaData {
	/* 0x0 */ unsigned int data;
	/* 0x4 */ unsigned int addr;
	/* 0x8 */ unsigned int size;
	/* 0xc */ unsigned int mode;
};
extern "C" unsigned int sceSifSetDma(sceSifDmaData *, int);
static void DmaToIop(void *, void *, int) __asm__("DmaToIop");

void LoadIOPModuleQueueSet(IOPMODULELOADQUEUE *, int, char *) __asm__("LoadIOPModuleQueueSet");
extern IOPMODULELOADQUEUE g_core_iop_module_queue[1] __asm__("g_core_iop_module_queue");
extern char g_irxname_sio2man[] __asm__("D_21EF38");
extern char g_irxname_mtapman[] __asm__("D_3D0738");
extern char g_irxname_mcman[] __asm__("D_21EF40");
extern char g_irxname_mcserv[] __asm__("D_21EF48");
extern char g_irxname_padman[] __asm__("D_21EF50");
extern char g_irxname_libsd[] __asm__("D_3D0750");
extern char g_irxname_989snd[] __asm__("D_21EF58");
extern char g_irxname_astrm[] __asm__("D_21EF68");
extern char g_core_iop_message[] __asm__("D_3D0768");
struct irxwad {
	/* 0x00 */ IopDataBlock unk00;
	/* 0x08 */ IopDataBlock sio2man;
	/* 0x10 */ IopDataBlock mcman;
	/* 0x18 */ IopDataBlock mcserv;
	/* 0x20 */ IopDataBlock padman;
	/* 0x28 */ IopDataBlock mtapman;
	/* 0x30 */ IopDataBlock libsd;
	/* 0x38 */ IopDataBlock _989snd;
	/* 0x40 */ IopDataBlock unk40;
	/* 0x48 */ IopDataBlock inet;
	/* 0x50 */ IopDataBlock netcnf;
	/* 0x58 */ IopDataBlock inetctl;
	/* 0x60 */ IopDataBlock msifrpc;
	/* 0x68 */ IopDataBlock dev9;
	/* 0x70 */ IopDataBlock smap;
	/* 0x78 */ IopDataBlock libnetb;
	/* 0x80 */ IopDataBlock ppp;
	/* 0x88 */ IopDataBlock pppoe;
	/* 0x90 */ IopDataBlock usbd;
	/* 0x98 */ IopDataBlock lgaud;
	/* 0xa0 */ IopDataBlock eznetcnf;
	/* 0xa8 */ IopDataBlock eznetctl;
	/* 0xb0 */ IopDataBlock lgkbm;
	/* 0xb8 */ IopDataBlock unkb8;
	/* 0xc0 */ IopDataBlock astrm;
};
void LoadCoreIOPModules(irxwad *irx_data) __asm__("LoadCoreIOPModules");

extern char g_irxname_inet[] __asm__("D_21EF70");
extern char g_irxname_netcnf[] __asm__("D_3D0780");
extern char g_irxargs_netcnf[] __asm__("D_3D0798");
extern char g_irxname_inetctl[] __asm__("D_21EF80");
extern char g_irxargs_inetctl[] __asm__("D_3D07D8");
extern char g_irxname_smap[] __asm__("D_3D07F0");
extern char g_irxname_ppp[] __asm__("D_21EF90");
extern char g_irxname_pppoe[] __asm__("D_3D0808");
extern char g_irxname_msifrpc[] __asm__("D_3D0820");
extern char g_irxname_libnetb[] __asm__("D_21EFA0");
extern char g_irxargs_libnetb[] __asm__("D_21EFA8");
extern char g_irxname_usbd[] __asm__("D_21EFB8");
extern char g_irxargs_usbd[] __asm__("D_3D0838");
extern char g_irxname_eznetcnf[] __asm__("D_21EFC8");
extern char g_irxname_lgkbm[] __asm__("D_21EFD8");
extern char g_irxargs_lgkbm[] __asm__("D_3D0868");
extern char g_irxname_lgaud[] __asm__("D_21EFE0");
extern char g_irxargs_lgaud[] __asm__("D_21EFE8");
extern char g_irxname_eznetctl[] __asm__("D_21EFF8");
extern char g_multiplayer_iop_message[] __asm__("D_3D0888");
void LoadMultiPlayerIOPModules(irxwad *irx_data) __asm__("LoadMultiPlayerIOPModules");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", DmaToIop);

GAME_SECTION(DisplayIOPInfo) void DisplayIOPInfo()
{
}

GAME_SECTION(UnloadIOPModule) int UnloadIOPModule(int id)
{
	int result = 0;
	bool ret = true;
	if (id >= 0) {
		if (sceSifStopModule(id, 0, 0, &result) < 0) {
			ret = false;
		} else if (sceSifUnloadModule(id) < 0) {
			ret = false;
		}
	}
	return ret;
}

JUNK_ASM(func_00460090,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

GAME_SECTION(DefaultIOPModuleUnloadCallback) int DefaultIOPModuleUnloadCallback(int *module)
{
	int result = 1;
	if (module) result = UnloadIOPModule(*module);
	return result;
}

GAME_SECTION(AstrmCreateStreams) int AstrmCreateStreams(int segments_per_buffer_half, int num_streams)
{
	bool b_ret = false;
	if (snd_InitVAGStreamingEx(num_streams, segments_per_buffer_half, 0, 1)) {
		Fs::Initialize();
		b_ret = true;
	}
	return b_ret;
}

GAME_SECTION(AstrmDestroyStreams) int AstrmDestroyStreams()
{
	snd_CloseVAGStreaming();
	return 1;
}

GAME_SECTION(InitializeAstrm) int InitializeAstrm()
{
	return 1;
}

GAME_SECTION(PadCallback) int PadCallback()
{
	pad_Init();
	return 1;
}

GAME_SECTION(SoundCallback) int SoundCallback()
{
	sound_Init();
	return 1;
}

GAME_SECTION(StreamerLoadCallback) int StreamerLoadCallback()
{
	return 1;
}

GAME_SECTION(Dev9Callback) unsigned char Dev9Callback()
{
	if (sceSifSearchModuleByName(g_dev9ModuleName) >= 0) {
		g_nwInfo.useNet = 1;
		PreparePowerOff();
	} else {
		g_nwInfo.useNet = 0;
	}
	return g_nwInfo.useNet;
}

GAME_SECTION(EZNetCnfCallback) int EZNetCnfCallback()
{
	if (g_nwInfoCnf.useCnf) ezNetCnfInit();
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", EZNetCnfUnloadCallback);

GAME_SECTION(LibNetBCallback) int LibNetBCallback()
{
	sceSifMInitRpc(0);
	return 1;
}

GAME_SECTION(LibNetBUnloadCallback) int LibNetBUnloadCallback(int *module)
{
	DefaultIOPModuleUnloadCallback(module);
	sceSifMExitRpc();
	return 1;
}

GAME_SECTION(LgKbmCallback) int LgKbmCallback()
{
	lgKbMInit(1, 0, 0x3b, nwKbdTimerFunc);
	lgKbMSuspendThread();
	return 1;
}

GAME_SECTION(LgKbmUnloadCallback) bool LgKbmUnloadCallback(void *module_info)
{
	lgKbMResumeThread(module_info);
	return lgKbMUnloadIopModule() == 0;
}

GAME_SECTION(EZNetCtlCallback) int EZNetCtlCallback()
{
	g_nwInfo.state = 2;
	if (g_nwInfo.useNet) ezNetCtlInit();
	return 1;
}

GAME_SECTION(EZNetCtlUnloadCallback) bool EZNetCtlUnloadCallback(void *module_info)
{
	int iterations = 5000;
	char status_message[64];
	ezNetCtlStatus status;
	if (g_nwInfo.useNet) {
		ezNetCtlGetStatus(&status, status_message, 0x40);
		if (status.state != 5 && status.state != 0) ezNetCtlDownInterface();
		do {
			nwGuiRefreshCallback();
			ezNetCtlGetStatus(&status, status_message, 0x40);
			DelayThread(500);
			if (status.state == 5 || status.state == 0) break;
		} while (--iterations != -1);
		ezNetCtlExit(0);
	}
	return true;
}

JUNK_ASM(func_004603F0,
	"\tlbu $2, 0x264($3)\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", GetModuleLoadCondition);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", GetModuleLoadCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", GetModuleUnloadCallback);

JUNK_ASM(func_004604E8,
	"\tori $2, $2, 0x9fcc\n"
	"\tnop\n");

GAME_SECTION(ClearIOPModuleQueue) void ClearIOPModuleQueue(IOPMODULELOADQUEUE *queue)
{
	int i;
	queue->num_iop_modules = 0;
	queue->max_size = 0;
	queue->actual_load_size = 0;
	queue->expected_load_size = 0;
	FastMemSet(queue->iop_modules, 0, sizeof(queue->iop_modules));
	for (i = 24; i >= 0; i--) {
		queue->iop_modules[i].module_id = -1;
	}
}

GAME_SECTION(ClearIOPModuleQueueSet) void ClearIOPModuleQueueSet(IOPMODULELOADQUEUE *queues, int num_queues)
{
	int i;
	for (i = 0; i < num_queues; i++) {
		ClearIOPModuleQueue(&queues[i]);
	}
}

GAME_SECTION(QueueIOPModuleLoad) void QueueIOPModuleLoad(IOPMODULELOADQUEUE *queue, char *module_name, void *irx_data, void *irx_module, int expected_size, int argc, char *argp, int function_set)
{
	int n;
	int max;
	int len;
	queue->iop_modules[queue->num_iop_modules].irx_data = irx_data;
	queue->iop_modules[queue->num_iop_modules].irx_module = (IopDataBlock *)irx_module;
	queue->iop_modules[queue->num_iop_modules].unk004 = expected_size;
	queue->iop_modules[queue->num_iop_modules].argument_size = argc;
	queue->iop_modules[queue->num_iop_modules].function_set = function_set;
	if (module_name) {
		strncpy(queue->iop_modules[queue->num_iop_modules].name, module_name, 0x40);
	} else {
		FastMemSet(queue->iop_modules[queue->num_iop_modules].arguments, 0, 0x40);
	}
	if (argp) {
		FastMemCopy(queue->iop_modules[queue->num_iop_modules].arguments, argp, argc);
	} else {
		FastMemSet(queue->iop_modules[queue->num_iop_modules].arguments, 0, 0x100);
	}
	n = queue->num_iop_modules;
	max = queue->max_size;
	if (max < queue->iop_modules[n].irx_module->length) {
		max = queue->iop_modules[n].irx_module->length;
	}
	queue->max_size = max;
	len = queue->iop_modules[n].unk004;
	queue->num_iop_modules = n + 1;
	queue->expected_load_size = queue->expected_load_size + len;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LoadIOPModuleQueue);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LoadIOPModuleQueueSet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", UnloadIOPModuleQueue);

GAME_SECTION(UnloadIOPModuleQueueSet) void UnloadIOPModuleQueueSet(IOPMODULELOADQUEUE *queues, int num_queues, char *message)
{
	int i;
	for (i = num_queues - 1; i >= 0; i--) {
		UnloadIOPModuleQueue(&queues[i]);
		ClearIOPModuleQueue(&queues[i]);
	}
}

GAME_SECTION(LoadCoreIOPModules) void LoadCoreIOPModules(irxwad *irx_data)
{
	ClearIOPModuleQueueSet(g_core_iop_module_queue, 1);
	QueueIOPModuleLoad(g_core_iop_module_queue, g_irxname_sio2man, irx_data, &irx_data->sio2man, 0x1a00, 0, 0, 1);
	QueueIOPModuleLoad(g_core_iop_module_queue, g_irxname_mtapman, irx_data, &irx_data->mtapman, 0x3100, 0, 0, 2);
	QueueIOPModuleLoad(g_core_iop_module_queue, g_irxname_mcman, irx_data, &irx_data->mcman, 0x27500, 0, 0, 3);
	QueueIOPModuleLoad(g_core_iop_module_queue, g_irxname_mcserv, irx_data, &irx_data->mcserv, 0x4800, 0, 0, 4);
	QueueIOPModuleLoad(g_core_iop_module_queue, g_irxname_padman, irx_data, &irx_data->padman, 0x1c200, 0, 0, 5);
	QueueIOPModuleLoad(g_core_iop_module_queue, g_irxname_libsd, irx_data, &irx_data->libsd, 0x5e00, 0, 0, 6);
	QueueIOPModuleLoad(g_core_iop_module_queue, g_irxname_989snd, irx_data, &irx_data->_989snd, 0x2b200, 0, 0, 7);
	QueueIOPModuleLoad(g_core_iop_module_queue, g_irxname_astrm, irx_data, &irx_data->astrm, 0x1400, 0, 0, 9);
	LoadIOPModuleQueueSet(g_core_iop_module_queue, 1, g_core_iop_message);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LoadSinglePlayerIOPModules);

GAME_SECTION(UnloadSinglePlayerIOPModules) void UnloadSinglePlayerIOPModules()
{
	if (g_iopload_singleplayer_modules_loaded) {
		GadgetCache::UnInitialize();
		AstrmDestroyStreams();
		g_iopload_single_gadgetcache_size = 0;
		g_iopload_single_astrm_size = 0;
		g_iopload_singleplayer_modules_loaded = false;
	}
}

GAME_SECTION(LoadMultiPlayerIOPModules) void LoadMultiPlayerIOPModules(irxwad *irx_data)
{
	if (!g_iopload_core_modules_initialized && !g_iopload_multiplayer_modules_loaded && !g_iopload_singleplayer_modules_loaded) {
		ClearIOPModuleQueueSet(g_iopload_multiplayer_queues, 1);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_inet, irx_data, &irx_data->inet, 0x40e00, 0, 0, 0xe);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_netcnf, irx_data, &irx_data->netcnf, 0xcd00, 0x3e, g_irxargs_netcnf, 0xc);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_inetctl, irx_data, &irx_data->inetctl, 0x9100, 0x12, g_irxargs_inetctl, 0xf);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_dev9ModuleName, irx_data, &irx_data->dev9, 0x2900, 0, 0, 0xa);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_smap, irx_data, &irx_data->smap, 0x8600, 0, 0, 0x13);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_ppp, irx_data, &irx_data->ppp, 0x18b00, 0, 0, 0x10);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_pppoe, irx_data, &irx_data->pppoe, 0x7500, 0, 0, 0x11);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_msifrpc, irx_data, &irx_data->msifrpc, 0x2600, 0, 0, 0xb);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_libnetb, irx_data, &irx_data->libnetb, 0x6100, 0xe, g_irxargs_libnetb, 0x12);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_usbd, irx_data, &irx_data->usbd, 0x15f00, 0x2b, g_irxargs_usbd, 0x14);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_eznetcnf, irx_data, &irx_data->eznetcnf, 0x3000, 0, 0, 0xd);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_lgkbm, irx_data, &irx_data->lgkbm, 0x2a00, 0x1c, g_irxargs_lgkbm, 0x15);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_lgaud, irx_data, &irx_data->lgaud, 0xcc00, 0xf, g_irxargs_lgaud, 0x16);
		QueueIOPModuleLoad(g_iopload_multiplayer_queues, g_irxname_eznetctl, irx_data, &irx_data->eznetctl, 0x3500, 0, 0, 0x17);
		LoadIOPModuleQueueSet(g_iopload_multiplayer_queues, 1, g_multiplayer_iop_message);
		AstrmCreateStreams(0x8000, 3);
		g_iopload_multiplayer_modules_loaded = true;
	}
}

GAME_SECTION(UnloadMultiPlayerIOPModules) void UnloadMultiPlayerIOPModules()
{
	if (g_iopload_multiplayer_modules_loaded) {
		AstrmDestroyStreams();
		UnloadIOPModuleQueueSet(g_iopload_multiplayer_queues, 1, g_iopload_multiplayer_unload_message);
		g_iopload_multi_size = 0;
		g_iopload_multiplayer_modules_loaded = false;
	}
}

GAME_SECTION(InitializeIOP) void InitializeIOP()
{
	DisplayIOPInfo();
	iopInitialized = 0;
}

GAME_SECTION(InitializeCoreIOPModules) void InitializeCoreIOPModules()
{
	if (!g_iopload_core_modules_initialized && !g_iopload_singleplayer_modules_loaded && !g_iopload_multiplayer_modules_loaded) {
		AstrmCreateStreams(0x8000, 7);
		g_iopload_core_modules_initialized = 1;
	}
}

GAME_SECTION(UninitializeCoreIOPModules) void UninitializeCoreIOPModules()
{
	if (g_iopload_core_modules_initialized) {
		AstrmDestroyStreams();
		g_iopload_core_modules_initialized = 0;
	}
}
