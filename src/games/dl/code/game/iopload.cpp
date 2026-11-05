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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", DmaToIop);

GAME_SECTION(DisplayIOPInfo) void DisplayIOPInfo()
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", UnloadIOPModule);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", func_00460090);

GAME_SECTION(DefaultIOPModuleUnloadCallback) int DefaultIOPModuleUnloadCallback(int *module)
{
	int result = 1;
	if (module) result = UnloadIOPModule(*module);
	return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", AstrmCreateStreams);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", Dev9Callback);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LgKbmUnloadCallback);

GAME_SECTION(EZNetCtlCallback) int EZNetCtlCallback()
{
	g_nwInfo.state = 2;
	if (g_nwInfo.useNet) ezNetCtlInit();
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", EZNetCtlUnloadCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", func_004603F0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", GetModuleLoadCondition);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", GetModuleLoadCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", GetModuleUnloadCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", func_004604E8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", ClearIOPModuleQueue);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", ClearIOPModuleQueueSet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", QueueIOPModuleLoad);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LoadIOPModuleQueue);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LoadIOPModuleQueueSet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", UnloadIOPModuleQueue);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", UnloadIOPModuleQueueSet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LoadCoreIOPModules);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LoadSinglePlayerIOPModules);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", UnloadSinglePlayerIOPModules);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", LoadMultiPlayerIOPModules);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/iopload", UnloadMultiPlayerIOPModules);

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
