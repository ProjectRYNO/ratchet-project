#include "common.h"

void LevelTScene_VoxShuttle_UpdateMonitors(void) {
}

void LevelTScene_VoxShuttle_UpdateFX(void) {
}

void UpdateSceneMonitors(void) {
}

void InitForCheats(void) {
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", Level_PostTransitionFX);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", Level_TransitionFX);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", SetLanguage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", GetCurrentFrameRate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", mode_creditsInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", mode_creditsUnInit);

void mode_lobbyUnInit(void) {
}

void mode_lobbyInit(void) {
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", func_00437E20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", GetBootMemoryMap);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", GetBootPlate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", func_00437EA8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", startlevel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", UpdateBoot);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", func_00438C80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/bmain", Boot_ResetTimeOutCounter);
