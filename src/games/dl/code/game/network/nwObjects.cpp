#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwGameOverObjectCleanUp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwInitGameObjsArray);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRegisterObjects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRegisterRemotePlayerCreationCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRegisterRemotePlayerDeletionCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRemoteNetPlayerCreationComplete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwPlayerInfoCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRemoteNetPlayerDeletionComplete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRemoteNetGameSettingsCreationCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRemoteNetGameSettingsUpdateCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRemoteNetGameSettingsDeletionCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwReleaseGameSettingsObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRemoteNetPlayerDataCreationCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRemoteNetPlayerDataUpdateCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwRemoteNetPlayerDataDeletionCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwCleanUp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwGetTeam);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwIsPlayerBlocked);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwBlockPlayer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwClearBlockedPlayers);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwUnblockPlayer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwCreateLocalGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwCreateLocalNetPlayer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwPlayerHasHeadSetMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwPlayerSetupMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwClientJoinMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwClientJoinResponseCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwSetDefaultGameSetupFlags);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwSetGameSetupFlagsForGameType);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwSendGameOptionsCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", nwGameOptionsMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", InsertPadMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/network/nwObjects", IncrementActivePadMsg);
