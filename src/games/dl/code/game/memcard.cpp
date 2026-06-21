#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_GetName);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", func_004660E0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_RestoreGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_ResetGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_Update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_MakeWholeSave);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_Init);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_GetDataSize);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", _memcard_Checksum);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_Checksum);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_TestChecksum);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_PrepData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_RestoreInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_RestoreData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_LoadNet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_SaveNet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_LoadPatch);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_PatchLoaded);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", func_004692B8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_Save);

void memcard_cleanupbeforesession(void) {
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", DNAS_ExtractPatch);
