#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", unpackbuff);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", ParsePatch);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", ParseBin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", GetBootOptionsFromSettings);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", ApplyBootOptionsToSettings);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", main);
