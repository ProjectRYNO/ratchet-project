#include "common.h"
#include "game_section.h"



struct LoadArgs {
	/* 0x00 */ unsigned int arg0;
	/* 0x04 */ unsigned int arg1;
	/* 0x08 */ unsigned int arg2;
	/* 0x0c */ unsigned int arg3;
};
struct FsDesc {
	/* 0x00 */ float time_elapsed;
	/* 0x04 */ unsigned int state;
	/* 0x08 */ unsigned int command;
	/* 0x0c */ void (*p_fn_load_complete)(void *, int);
	/* 0x10 */ void *p_load_complete_args;
	/* 0x14 */ unsigned int load_type;
	/* 0x18 */ unsigned int pad32_0[2];
	/* 0x20 */ LoadArgs load_args;
	/* 0x30 */ int device_args[4];
};
typedef int (*FsDeviceFn)(LoadArgs *, void *);
extern FsDesc g_fs_desc __asm__("D_0021D940");
extern "C" {
	int snd_FlushSoundCommands();
	int snd_StreamSafeCdGetError();
	void snd_StreamSafeCdCallback(void (*)(int));
}
void cb_cdComplete(int op) __asm__("cb_cdComplete");
struct Fs {
	static void *GetBuffer() __asm__("GetBuffer");
	static void Reset() __asm__("Reset");
	static void Initialize() __asm__("Initialize");
	static unsigned int IsLoading() __asm__("IsLoading");
	static unsigned int Load(int type, unsigned int, unsigned int, unsigned int, unsigned int, void (*)(void *, int), void *) __asm__("Load");
	static unsigned int LoadAsync(int type, unsigned int, unsigned int, unsigned int, unsigned int, void (*)(void *, int), void *) __asm__("LoadAsync");
	static void Abort() __asm__("Abort");
	static void Sync(unsigned int) __asm__("Sync");
	static void Update(float) __asm__("Update___dupe53");
};
extern FsDeviceFn g_pp_fn_load[] __asm__("D_0021DF40");
extern FsDeviceFn g_pp_fn_is_complete[] __asm__("D_0021DF48");
extern FsDeviceFn g_pp_fn_abort[] __asm__("D_0021DF50");
extern FsDeviceFn g_pp_fn_load_complete[] __asm__("D_0021DF58");


GAME_SECTION(cb_cdComplete) void cb_cdComplete(int op)
{
	if (op == 1 && g_fs_desc.state != 0) {
		if (snd_StreamSafeCdGetError() != 0) {
			g_fs_desc.command |= 8;
		} else {
			g_fs_desc.device_args[0] = 1;
		}
	}
}

GAME_SECTION(Sync) void Fs::Sync(unsigned int b_blocking)
{
	do {
		Update(0.0f);
		if (b_blocking == 0) return;
	} while (IsLoading());
}

GAME_SECTION(Update___dupe53) void Fs::Update(float dt)
{
	snd_FlushSoundCommands();
	if (g_fs_desc.state == 0) {
		if (g_fs_desc.command & 1) {
			if (g_pp_fn_load[g_fs_desc.load_type](&g_fs_desc.load_args, g_fs_desc.device_args)) {
				g_fs_desc.command &= 0xfffffffe;
				g_fs_desc.state = 1;
				g_fs_desc.time_elapsed = 0.0f;
			} else {
				g_fs_desc.state = 3;
			}
		} else if (g_fs_desc.command & 4) {
			g_fs_desc.command &= 0xfffffffb;
		}
	}
	if (g_fs_desc.state == 1) {
		g_fs_desc.time_elapsed += dt;
		if (g_fs_desc.command & 4) {
			if (g_pp_fn_abort[g_fs_desc.load_type](&g_fs_desc.load_args, g_fs_desc.device_args)) {
				g_fs_desc.state = 4;
			}
			g_fs_desc.command &= 0xfffffffb;
		} else if (g_fs_desc.command & 8) {
			g_fs_desc.state = 3;
			g_fs_desc.command &= 0xfffffff7;
		} else if (g_pp_fn_is_complete[g_fs_desc.load_type](&g_fs_desc.load_args, g_fs_desc.device_args)) {
			g_fs_desc.state = 2;
		}
	}
	if (g_fs_desc.state == 2) {
		if (g_pp_fn_load_complete[g_fs_desc.load_type](&g_fs_desc.load_args, g_fs_desc.device_args)) {
			FlushCache(0);
			if (g_fs_desc.p_fn_load_complete) {
				g_fs_desc.p_fn_load_complete(g_fs_desc.p_load_complete_args, 0);
			}
			g_fs_desc.state = 0;
		} else {
			g_fs_desc.state = 0;
			g_fs_desc.command |= 1;
		}
	}
	if (g_fs_desc.state == 4) {
		if (g_pp_fn_is_complete[g_fs_desc.load_type](&g_fs_desc.load_args, g_fs_desc.device_args)) {
			if (g_pp_fn_load_complete[g_fs_desc.load_type](&g_fs_desc.load_args, g_fs_desc.device_args)) {
				FlushCache(0);
				if (g_fs_desc.p_fn_load_complete) {
					g_fs_desc.p_fn_load_complete(g_fs_desc.p_load_complete_args, 2);
				}
				g_fs_desc.state = 0;
			} else {
				g_fs_desc.state = 3;
			}
		}
	}
	if (g_fs_desc.state == 3) {
		if (g_fs_desc.p_fn_load_complete) {
			g_fs_desc.p_fn_load_complete(g_fs_desc.p_load_complete_args, 1);
		}
		g_fs_desc.state = 0;
	}
}

GAME_SECTION(Initialize) void Fs::Initialize()
{
	snd_StreamSafeCdCallback(cb_cdComplete);
}

GAME_SECTION(Reset) void Fs::Reset()
{
	g_fs_desc.state = 0;
	g_fs_desc.command = 0;
}

GAME_SECTION(Load) unsigned int Fs::Load(int type, unsigned int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3, void (*p_fn_load_complete)(void *, int), void *p_load_complete_args)
{
	unsigned int b_ret = LoadAsync(type, arg0, arg1, arg2, arg3, p_fn_load_complete, p_load_complete_args);
	Sync(1);
	return b_ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fs", LoadAsync);

GAME_SECTION(Abort) void Fs::Abort()
{
	if (IsLoading()) {
		g_fs_desc.command |= 4;
		Update(0.0f);
	}
}

GAME_SECTION(IsLoading) unsigned int Fs::IsLoading()
{
	return g_fs_desc.state != 0 || (g_fs_desc.command & 1);
}

GAME_SECTION(GetBuffer) void *Fs::GetBuffer()
{
	return 0;
}
