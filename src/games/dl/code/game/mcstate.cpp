#include "common.h"

void csf_prompt_create_save_overwrite(void) {
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_TransToState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", UpdateMCState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_init);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_good_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_good_load);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_warning);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_autosave_warning);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_nocard);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_changed);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_wait_for_card);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_unformatted);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_format);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_format_pending);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_formatting);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_formatted);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_check_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_checking_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_nosave);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_create_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_create_save_pending);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_creating_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_init_save);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_init_load);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_newcard);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_format_failed);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", csf_prompt_create_failed);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_GetState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_SetCommand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_ClearCommand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_CommandIsSet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_SetResponse);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", MCSTATE_ClearResponse);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mcstate", func_00465F20);
