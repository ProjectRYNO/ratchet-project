#include "common.h"
#include "game_section.h"


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
struct Fs {
	static void Initialize() __asm__("Initialize");
};
struct GadgetCache {
	static void Initialize() __asm__("Initialize___dupe2");
	static void UnInitialize() __asm__("UnInitialize");
};
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

/* ===== AM additions ===== */
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", func_00460090);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", func_004603F0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", GetModuleLoadCondition);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", GetModuleLoadCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", GetModuleUnloadCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", func_004604E8);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LoadCoreIOPModules);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LoadMultiPlayerIOPModules);

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
