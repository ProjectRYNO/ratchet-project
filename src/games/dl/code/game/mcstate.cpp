#include "common.h"
#include "game_section.h"



struct McState {
	/* 0x000 */ char unk000[8];
	/* 0x008 */ int cardState;
	/* 0x00c */ int unk00c;
	/* 0x010 */ int unk010;
	/* 0x014 */ int unk014;
	/* 0x018 */ short command;
	/* 0x01a */ char unk01a[0x1b0 - 0x1a];
	/* 0x1b0 */ int unk1b0;
	/* 0x1b4 */ char unk1b4[0x1cc - 0x1b4];
	/* 0x1cc */ int slotA;
	/* 0x1d0 */ int slotB;
	/* 0x1d4 */ int loaded;
	/* 0x1d8 */ char unk1d8[0x1e4 - 0x1d8];
	/* 0x1e4 */ int pending;
};
int SaveSlotUponCreation __asm__("D_21F150") GAME_GP_DATA = 0;
extern int mcstate_response __asm__("mcstate_response");
extern int mc_state __asm__("mc_state");
extern unsigned int mcstate_flags __asm__("mcstate_flags");
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


GAME_SECTION(csf_prompt_create_save_overwrite) void csf_prompt_create_save_overwrite()
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_TransToState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", UpdateMCState);

GAME_SECTION(csf_init) void csf_init()
{
	if (!g_gameType && !g_gameRules) mcState.pending = 0;
	mcState.unk010 = 0;
	MCSTATE_TransToState(4);
	McRetries = 5;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_good_save);

GAME_SECTION(csf_good_load) void csf_good_load()
{
	if (LoadDoneCallback) {
		LoadDoneCallback();
		LoadDoneCallback = 0;
	}
	if (!mcState.loaded) mcState.pending = 1;
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
	mcState.slotA = -1;
	mcState.slotB = -1;
	MCSTATE_TransToState(6);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_wait_for_card);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_unformatted);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_format);

GAME_SECTION(csf_format_pending) void csf_format_pending()
{
	mcState.unk010 = 0;
	if (mcState.slotA < 0) {
		mcState.slotB = 0;
		mcState.slotA = 3;
	}
	MCSTATE_TransToState(0xa);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_formatting);

GAME_SECTION(csf_formatted) void csf_formatted()
{
	if (mcState.cardState != 2) MCSTATE_TransToState(4);
	else if (mcstate_flags & 0x806) MCSTATE_TransToState(0xc);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_check_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_checking_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_nosave);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_create_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_create_save_pending);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_creating_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_init_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_init_load);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_newcard);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_no_room);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_load_failed);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_loading);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_save_failed);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_saving);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_auto_saving);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_begin_unformatted);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_begin_nosave);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_save_overwrite);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", func_00465AA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_SetSaveSlotUponSaveCreationTo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", func_00465AD8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_LoadGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_SaveGame);

GAME_SECTION(MCSTATE_GetState) int MCSTATE_GetState()
{
	return mc_state;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_SetCommand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_ClearCommand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_CommandIsSet);

GAME_SECTION(MCSTATE_SetResponse) void MCSTATE_SetResponse(int response)
{
	mcstate_response = response;
}

GAME_SECTION(MCSTATE_ClearResponse) void MCSTATE_ClearResponse()
{
	mcstate_response = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", func_00465F20);
