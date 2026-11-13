#include "common.h"
#include "game_section.h"






struct memcard_saveinfo {
	/* 0x00 */ int level;
	/* 0x04 */ int unk04[7];
};
struct memcard_data {
	/* 0x00 */ int port;
	/* 0x04 */ int slot;
	/* 0x08 */ int type;
	/* 0x0c */ int free;
	/* 0x10 */ int changed;
	/* 0x14 */ int format;
	/* 0x18 */ short saveslot;
	/* 0x1a */ short curslot;
	/* 0x1c */ int RC1and2_weapons_checked;
	/* 0x20 */ int corrupt_size;
	/* 0x24 */ unsigned int patch_size;
	/* 0x28 */ int oldsave;
	/* 0x2c */ int gamesize;
	/* 0x30 */ int levelsize;
	/* 0x34 */ memcard_saveinfo info[5];
};
struct McState {
	/* 0x000 */ memcard_data memcards[2];
	/* 0x1a8 */ int cmd;
	/* 0x1ac */ int res;
	/* 0x1b0 */ int useslot;
	/* 0x1b4 */ int slot;
	/* 0x1b8 */ int level;
	/* 0x1bc */ int sync;
	/* 0x1c0 */ int file;
	/* 0x1c4 */ int stage;
	/* 0x1c8 */ int substage;
	/* 0x1cc */ int nextstage;
	/* 0x1d0 */ int nextslot;
	/* 0x1d4 */ int err;
	/* 0x1d8 */ int errslot;
	/* 0x1dc */ char *addr;
	/* 0x1e0 */ int size;
	/* 0x1e4 */ int autosave;
	/* 0x1e8 */ int checkslot;
	/* 0x1ec */ int timer;
	/* 0x1f0 */ int savesize;
};
int SaveSlotUponCreation __asm__("D_21F150") GAME_GP_DATA = 0;
extern int mcstate_response __asm__("mcstate_response");
extern int mc_state __asm__("mc_state");
extern int mcstate_flags __asm__("mcstate_flags");
extern McState mcState __asm__("D_171948");
void MCSTATE_TransToState(int) __asm__("MCSTATE_TransToState");
void MCSTATE_ClearCommand(int) __asm__("MCSTATE_ClearCommand");
void MCSTATE_ClearResponse() __asm__("MCSTATE_ClearResponse");
int MCSTATE_GetState() __asm__("MCSTATE_GetState");
void MCSTATE_SetResponse(int) __asm__("MCSTATE_SetResponse");
void csf_prompt_create_save_overwrite() __asm__("csf_prompt_create_save_overwrite");
int MCSTATE_SetSaveSlotUponSaveCreationTo(int) __asm__("MCSTATE_SetSaveSlotUponSaveCreationTo");
void csf_changed() __asm__("csf_changed");
void csf_prompt_format_failed() __asm__("csf_prompt_format_failed");
void csf_prompt_autosave_warning() __asm__("csf_prompt_autosave_warning");
void csf_format_pending() __asm__("csf_format_pending");



void (*LoadDoneCallback)() __asm__("D_21F164") GAME_GP_DATA = 0;
void (*CreateFailedCallback)() __asm__("D_21F168") GAME_GP_DATA = 0;
int McRetries __asm__("D_21F154") GAME_GP_DATA = 0;
extern int g_gameType __asm__("g_gameType");
extern int g_gameRules __asm__("g_gameRules");
void csf_good_load() __asm__("csf_good_load");
void csf_nocard() __asm__("csf_nocard");
void csf_prompt_create_failed() __asm__("csf_prompt_create_failed");
void csf_formatted() __asm__("csf_formatted");
void csf_init() __asm__("csf_init");
void MCSTATE_LoadGame(short) __asm__("MCSTATE_LoadGame");
void csf_prompt_warning() __asm__("csf_prompt_warning");


void (*save_done_cb)() __asm__("D_21F15C") GAME_GP_DATA = 0;
void (*init_load_cb)() __asm__("D_21F160") GAME_GP_DATA = 0;
int MCSTATE_which_slot __asm__("D_21F16C") GAME_GP_DATA = 0;
extern unsigned char InEndgame __asm__("InEndgame");
extern unsigned char InFrontEnd __asm__("InFrontEnd");
extern unsigned char mcstate_error __asm__("mcstate_error");
extern unsigned char Update_ShowFreezePulled __asm__("Update_ShowFreezePulled");
void csf_prompt_save_failed() __asm__("csf_prompt_save_failed");
void csf_prompt_load_failed() __asm__("csf_prompt_load_failed");
void csf_no_room() __asm__("csf_no_room");
void csf_prompt_begin_nosave() __asm__("csf_prompt_begin_nosave");
void csf_prompt_begin_unformatted() __asm__("csf_prompt_begin_unformatted");
void csf_formatting() __asm__("csf_formatting");
void csf_check_save() __asm__("csf_check_save");
void csf_create_save_pending() __asm__("csf_create_save_pending");
void csf_unformatted() __asm__("csf_unformatted");
void csf_loading() __asm__("csf_loading");
void csf_nosave() __asm__("csf_nosave");
void csf_prompt_save_overwrite() __asm__("csf_prompt_save_overwrite");
void csf_prompt_create_save() __asm__("csf_prompt_create_save");
void csf_prompt_format() __asm__("csf_prompt_format");
void csf_auto_saving() __asm__("csf_auto_saving");
void csf_creating_save() __asm__("csf_creating_save");
void csf_saving() __asm__("csf_saving");
void csf_init_load() __asm__("csf_init_load");
void csf_checking_save() __asm__("csf_checking_save");
void csf_wait_for_card() __asm__("csf_wait_for_card");
int MCSTATE_CommandIsSet(int) __asm__("MCSTATE_CommandIsSet");
extern void (*state_functions[])() __asm__("D_3D8038");
extern int MCSTATE_idle_time __asm__("MCSTATE_idle_time");
void UpdateMCState() __asm__("UpdateMCState");

/* ===== AG additions ===== */

void csf_newcard() __asm__("csf_newcard");

/* ===== AM additions ===== */
struct McClock {
	/* 0x0 */ unsigned char b[8];
};
extern "C" int sceCdReadClock(McClock *);
extern "C" int sceScfGetLocalTimefromRTC(McClock *);
extern McClock LastSaveTime __asm__("LastSaveTime");
extern int Level __asm__("Level");
void memcard_MakeWholeSave(char *) __asm__("memcard_MakeWholeSave");
void MCSTATE_SaveGame(char *, int) __asm__("MCSTATE_SaveGame");
void (*do_save_cb)() __asm__("D_21F158") GAME_GP_DATA = 0;
void csf_init_save() __asm__("csf_init_save");
void csf_good_save() __asm__("csf_good_save");

GAME_SECTION(csf_prompt_create_save_overwrite) void csf_prompt_create_save_overwrite()
{
}

GAME_SECTION(MCSTATE_TransToState) void MCSTATE_TransToState(int new_state)
{
	mc_state = new_state;
	if (new_state == 3) Update_ShowFreezePulled = 1;
	switch (new_state) {
	case 3:
	case 0x13:
	case 0x14:
	case 0x16:
	case 0x18:
	case 0x21:
		mcstate_error = 1;
	case 8:
	case 0xf:
	case 0x1a:
	case 0x1b:
	case 0x1f:
	case 0x20:
		MCSTATE_ClearResponse();
		break;
	}
}

GAME_SECTION(UpdateMCState) void UpdateMCState()
{
	int old_state;
	int ticks = McRetries - 1;
	if (ticks < 0) ticks = 0;
	McRetries = ticks;
	if (mcState.err || (mcState.memcards[0].type == 2 && mcState.memcards[0].changed) || mcState.memcards[0].oldsave > 0) {
		mcstate_error = 1;
	}
	old_state = mc_state;
	state_functions[mc_state]();
	MCSTATE_idle_time++;
	if (mc_state != old_state) MCSTATE_idle_time = 0;
}

GAME_SECTION(csf_init) void csf_init()
{
	if (!g_gameType && !g_gameRules) mcState.autosave = 0;
	mcState.memcards[0].changed = 0;
	MCSTATE_TransToState(4);
	McRetries = 5;
}

GAME_SECTION(csf_good_save) void csf_good_save()
{
	if (mcState.memcards[0].type != 2) {
		if (g_gameType == 1 || !mcState.autosave) {
			MCSTATE_TransToState(4);
		} else {
			mcState.autosave = 0;
			MCSTATE_TransToState(3);
		}
	} else if (mcstate_flags & 4) {
		MCSTATE_TransToState(0x1e);
	} else if (mcstate_flags & 2) {
		MCSTATE_TransToState(0x1d);
	} else if (g_gameType == 0) {
		if (!mcState.autosave || mcState.memcards[0].changed) {
			MCSTATE_TransToState(5);
		} else if (mcstate_flags & 0x200) {
			MCSTATE_TransToState(0x1c);
		}
	}
}

GAME_SECTION(csf_good_load) void csf_good_load()
{
	if (LoadDoneCallback) {
		LoadDoneCallback();
		LoadDoneCallback = 0;
	}
	if (!mcState.err) mcState.autosave = 1;
	MCSTATE_TransToState(1);
}

GAME_SECTION(csf_prompt_warning) void csf_prompt_warning()
{
	if (mcstate_response != 3) {
		MCSTATE_ClearCommand(0);
		MCSTATE_TransToState(4);
	}
}

GAME_SECTION(csf_prompt_autosave_warning) void csf_prompt_autosave_warning()
{
	if (mcstate_response != 3) {
		MCSTATE_ClearCommand(0);
		MCSTATE_TransToState(4);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_nocard);

GAME_SECTION(csf_changed) void csf_changed()
{
	mcState.nextstage = -1;
	mcState.nextslot = -1;
	MCSTATE_TransToState(6);
}

GAME_SECTION(csf_wait_for_card) void csf_wait_for_card()
{
	MCSTATE_ClearResponse();
	if (mcState.memcards[0].type != 2) return;
	if (mcState.memcards[0].changed != 0) {
		if (mcState.memcards[0].format != 0) goto formatted;
		mcState.memcards[0].changed = 0;
		MCSTATE_TransToState(7);
	}
	if (mcState.memcards[0].format == 0) {
		MCSTATE_TransToState(7);
		return;
	}
formatted:
	if (mcState.memcards[0].type == 2 && mcState.memcards[0].changed != 0) mcState.memcards[0].changed = 0;
	MCSTATE_TransToState(0xb);
}

GAME_SECTION(csf_unformatted) void csf_unformatted()
{
	if (mcState.memcards[0].type != 2) {
		MCSTATE_TransToState(4);
	} else if (mcState.memcards[0].changed != 0) {
		MCSTATE_TransToState(5);
	} else {
		if (InEndgame || (mcstate_flags & 0x1a)) MCSTATE_TransToState(8);
	}
}

GAME_SECTION(csf_prompt_format) void csf_prompt_format()
{
	if (mcState.memcards[0].type != 2) {
		MCSTATE_TransToState(4);
	} else if (mcState.memcards[0].changed != 0) {
		MCSTATE_TransToState(5);
	} else if (mcstate_response == 2) {
		MCSTATE_TransToState(7);
	} else if (mcstate_response == 1) {
		mcstate_flags |= 8;
		MCSTATE_TransToState(9);
	}
}

GAME_SECTION(csf_format_pending) void csf_format_pending()
{
	mcState.memcards[0].changed = 0;
	if (mcState.nextstage < 0) {
		mcState.nextslot = 0;
		mcState.nextstage = 3;
	}
	MCSTATE_TransToState(0xa);
}

GAME_SECTION(csf_formatting) void csf_formatting()
{
	if (mcState.stage == 2 && mcState.nextstage < 0) {
		if (mcState.err != 0) {
			MCSTATE_TransToState(0x13);
		} else {
			MCSTATE_TransToState(0xb);
		}
	}
}

GAME_SECTION(csf_formatted) void csf_formatted()
{
	if (mcState.memcards[0].type != 2) MCSTATE_TransToState(4);
	else if (mcstate_flags & 0x806) MCSTATE_TransToState(0xc);
}

GAME_SECTION(csf_check_save) void csf_check_save()
{
	if (mcState.stage == 2 && mcState.nextstage < 0) {
		mcState.nextstage = 7;
		mcstate_flags &= ~0x800;
		mcState.memcards[0].changed = 0;
		mcState.nextslot = 0;
		MCSTATE_TransToState(0xd);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_checking_save);

GAME_SECTION(csf_nosave) void csf_nosave()
{
	if (mcState.stage == 2 && mcState.nextstage < 0) {
		if (mcState.memcards[0].type != 2) {
			MCSTATE_TransToState(4);
		} else if (mcState.memcards[0].changed != 0) {
			MCSTATE_TransToState(5);
		} else {
			if (mcstate_flags & 0x12) MCSTATE_TransToState(0xf);
		}
	}
}

GAME_SECTION(csf_prompt_create_save) void csf_prompt_create_save()
{
	if (mcState.memcards[0].type != 2) {
		MCSTATE_TransToState(4);
	} else if (mcstate_response == 2) {
		if (InFrontEnd) {
			MCSTATE_TransToState(0x1b);
		} else {
			MCSTATE_TransToState(0xe);
		}
	} else if (mcstate_response == 1) {
		MCSTATE_TransToState(0x10);
	}
}

GAME_SECTION(csf_create_save_pending) void csf_create_save_pending()
{
	if (mcState.stage == 2 && mcState.nextstage < 0) {
		mcState.nextstage = 9;
		mcstate_flags &= ~2;
		mcstate_flags &= ~0x10;
		mcState.nextslot = 0;
		MCSTATE_TransToState(0x11);
	}
}

GAME_SECTION(csf_creating_save) void csf_creating_save()
{
	if (mcState.stage == 2 && mcState.nextstage < 0) {
		if (mcState.err != 0) {
			MCSTATE_TransToState(0x14);
		} else {
			mcState.useslot = 0;
			mcState.memcards[0].saveslot = 0;
			if (mcstate_flags & 0x1000) {
				mcstate_flags &= ~0x1000;
				mcState.memcards[0].saveslot = SaveSlotUponCreation;
				SaveSlotUponCreation = -1;
			}
			MCSTATE_TransToState(0x12);
		}
		if (CreateFailedCallback) {
			CreateFailedCallback();
			CreateFailedCallback = 0;
		}
	}
}

GAME_SECTION(csf_init_save) void csf_init_save()
{
	bool bOkToSave;
	if (mcState.stage == 2 && mcState.nextstage < 0) {
		bOkToSave = false;
		if ((g_gameType == 0 && mcState.memcards[0].info[MCSTATE_which_slot].level == -1) || mcstate_response || (mcstate_flags & 0x4000)) {
			bOkToSave = true;
		}
		if (bOkToSave) {
			mcstate_flags &= ~0x4000;
			if (do_save_cb) {
				do_save_cb();
				do_save_cb = 0;
			}
			mcState.memcards[0].saveslot = MCSTATE_which_slot;
			MCSTATE_TransToState(0x19);
		} else {
			MCSTATE_TransToState(0x1f);
		}
	}
}

GAME_SECTION(csf_init_load) void csf_init_load()
{
	if (mcState.stage == 2 && mcState.nextstage < 0) {
		if (init_load_cb) {
			init_load_cb();
			init_load_cb = 0;
		}
		mcState.useslot = 0;
		mcState.memcards[0].saveslot = MCSTATE_which_slot;
		MCSTATE_TransToState(0x17);
	}
}

GAME_SECTION(csf_newcard) void csf_newcard()
{
	if (mcState.memcards[0].type != 2) {
		MCSTATE_TransToState(4);
	} else if (g_gameType == 0 && mcState.autosave) {
		MCSTATE_TransToState(1);
	} else if (mcstate_flags & 4) {
		MCSTATE_TransToState(0x1e);
	} else if (mcstate_flags & 2) {
		MCSTATE_TransToState(0x1d);
	} else if (mcstate_flags & 0x800) {
		MCSTATE_TransToState(0xc);
	} else if (mcState.memcards[0].type == 2 && mcState.memcards[0].changed) {
		MCSTATE_TransToState(5);
	}
}

GAME_SECTION(csf_prompt_format_failed) void csf_prompt_format_failed()
{
	if (mcstate_response == 3) MCSTATE_TransToState(7);
}

GAME_SECTION(csf_prompt_create_failed) void csf_prompt_create_failed()
{
	if (CreateFailedCallback) {
		CreateFailedCallback();
		CreateFailedCallback = 0;
	}
	if (mcstate_response == 3) MCSTATE_TransToState(0xb);
}

GAME_SECTION(csf_no_room) void csf_no_room()
{
	if (mcState.memcards[0].type != 2) {
		MCSTATE_TransToState(4);
	} else {
		if (mcState.memcards[0].changed) MCSTATE_TransToState(5);
	}
}

GAME_SECTION(csf_prompt_load_failed) void csf_prompt_load_failed()
{
	if (LoadDoneCallback) {
		LoadDoneCallback();
		LoadDoneCallback = 0;
	}
	if (mcstate_response == 3) MCSTATE_TransToState(6);
}

GAME_SECTION(csf_loading) void csf_loading()
{
	mcstate_flags &= ~4;
	if (mcState.stage == 2 && mcState.nextstage < 0) {
		if (mcState.err != 0) {
			MCSTATE_ClearResponse();
			MCSTATE_TransToState(0x16);
		} else {
			MCSTATE_TransToState(2);
		}
	}
}

GAME_SECTION(csf_prompt_save_failed) void csf_prompt_save_failed()
{
	if (mcstate_response == 3) MCSTATE_TransToState(0xb);
}

GAME_SECTION(csf_saving) void csf_saving()
{
	if (mcState.stage == 2 && mcState.nextstage < 0) {
		mcstate_flags &= ~2;
		if (mcState.err != 0 || mcState.memcards[0].oldsave != 0) {
			if (g_gameType == 0 && mcState.autosave != 0) mcState.autosave = 0;
			MCSTATE_TransToState(0x18);
		} else {
			if (g_gameType == 0) mcState.autosave = 1;
			MCSTATE_TransToState(1);
		}
		if (save_done_cb) {
			save_done_cb();
			save_done_cb = 0;
		}
	}
}

GAME_SECTION(csf_auto_saving) void csf_auto_saving()
{
	mcstate_flags &= ~0x200;
	if (g_gameType == 0 && mcState.stage == 2 && mcState.nextstage < 0) {
		if (mcState.err != 0 || (mcState.memcards[0].type == 2 && mcState.memcards[0].changed != 0)) {
			mcState.autosave = 0;
			MCSTATE_TransToState(3);
		} else {
			mcState.autosave = 1;
			MCSTATE_TransToState(1);
		}
	}
}

GAME_SECTION(csf_prompt_begin_unformatted) void csf_prompt_begin_unformatted()
{
	if (mcState.memcards[0].type != 2) {
		MCSTATE_TransToState(4);
	} else {
		if (mcstate_response == 2) MCSTATE_TransToState(7);
	}
}

GAME_SECTION(csf_prompt_begin_nosave) void csf_prompt_begin_nosave()
{
	if (mcState.memcards[0].type != 2) {
		MCSTATE_TransToState(4);
	} else {
		if (mcstate_response) MCSTATE_TransToState(0xe);
	}
}

GAME_SECTION(csf_prompt_save_overwrite) void csf_prompt_save_overwrite()
{
	if (mcState.memcards[0].type != 2) {
		if (mcState.autosave != 0) {
			MCSTATE_TransToState(3);
		} else {
			MCSTATE_TransToState(4);
		}
	} else if (mcstate_response == 2) {
		MCSTATE_TransToState(0x12);
	} else if (mcstate_response == 1) {
		MCSTATE_TransToState(0x1d);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", func_00465AA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_SetSaveSlotUponSaveCreationTo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", func_00465AD8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_LoadGame);

GAME_SECTION(MCSTATE_SaveGame) void MCSTATE_SaveGame(char *addr, int which_level)
{
	McState *mc = &mcState;
	sceCdReadClock(&LastSaveTime);
	sceScfGetLocalTimefromRTC(&LastSaveTime);
	memcard_MakeWholeSave(addr);
	mc->memcards[0].saveslot = MCSTATE_which_slot;
	mc->useslot = 0;
	mc->addr = addr;
	if (which_level == -1) {
		mc->memcards[0].info[MCSTATE_which_slot].level = Level;
	} else {
		mc->memcards[0].info[MCSTATE_which_slot].level = which_level;
	}
	if (mcState.nextstage < 0) {
		mcState.nextslot = 0;
		mcState.nextstage = 0x13;
	}
}

GAME_SECTION(MCSTATE_GetState) int MCSTATE_GetState()
{
	return mc_state;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_SetCommand);

GAME_SECTION(MCSTATE_ClearCommand) void MCSTATE_ClearCommand(int cmd)
{
	switch (cmd) {
	case 5:
		mcstate_flags &= ~8;
		break;
	case 7:
		mcstate_flags &= ~0x200;
		break;
	case 0:
		mcstate_flags &= ~2;
		mcstate_flags &= ~4;
		mcstate_flags &= ~0x1000;
		mcstate_flags &= ~8;
		mcstate_flags &= ~0x10;
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 6:
		break;
	}
}

GAME_SECTION(MCSTATE_CommandIsSet) int MCSTATE_CommandIsSet(int cmd)
{
	int ret = 0;
	switch (cmd) {
	case 1:
		ret = mcstate_flags & 2;
		break;
	case 3:
		ret = mcstate_flags & 4;
		break;
	case 4:
		ret = mcstate_flags & 0x10;
		break;
	case 6:
		ret = mcstate_flags & 0x800;
		break;
	case 5:
		ret = mcstate_flags & 8;
		break;
	case 7:
		ret = mcstate_flags & 0x200;
		break;
	}
	return ret;
}

GAME_SECTION(MCSTATE_SetResponse) void MCSTATE_SetResponse(int response)
{
	mcstate_response = response;
}

GAME_SECTION(MCSTATE_ClearResponse) void MCSTATE_ClearResponse()
{
	mcstate_response = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", func_00465F20);
