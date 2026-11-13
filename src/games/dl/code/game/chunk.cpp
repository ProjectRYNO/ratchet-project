#include "common.h"
#include "game_section.h"
struct MobyInstance;

int CS_RodType_Move(MobyInstance *pMoby) __asm__("CS_RodType_Move");
int CS_BallsType_Move(MobyInstance *pMoby) __asm__("CS_BallsType_Move");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_SpawnChunk);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_InitChunk);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_UpdateChunk);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_BlockType_Move);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_SphereType_Move);

GAME_SECTION(CS_RodType_Move) int CS_RodType_Move(MobyInstance *pMoby) { return 1; }

GAME_SECTION(CS_BallsType_Move) int CS_BallsType_Move(MobyInstance *pMoby) { return 1; }

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_MoveFree);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_MoveFree_Sphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_MovePivot);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_DoCollision);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_DoCollision_Sphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_AttachPivot);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_RemoveUnusedPivots);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_AddRotationVel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_RemoveRotationAroundAxis);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_ReflectVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_UnPackCollData);
