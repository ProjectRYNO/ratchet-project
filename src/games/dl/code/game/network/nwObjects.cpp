#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwGameOverObjectCleanUp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwInitGameObjsArray);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRegisterObjects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRegisterRemotePlayerCreationCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRegisterRemotePlayerDeletionCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRemoteNetPlayerCreationComplete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwPlayerInfoCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRemoteNetPlayerDeletionComplete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRemoteNetGameSettingsCreationCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRemoteNetGameSettingsUpdateCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRemoteNetGameSettingsDeletionCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwReleaseGameSettingsObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRemoteNetPlayerDataCreationCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRemoteNetPlayerDataUpdateCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwRemoteNetPlayerDataDeletionCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwCleanUp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwGetTeam);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwIsPlayerBlocked);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwBlockPlayer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwClearBlockedPlayers);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwUnblockPlayer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwCreateLocalGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwCreateLocalNetPlayer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwPlayerHasHeadSetMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwPlayerSetupMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwClientJoinMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwClientJoinResponseCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwSetDefaultGameSetupFlags);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwSetGameSetupFlagsForGameType);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwSendGameOptionsCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", nwGameOptionsMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", InsertPadMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nwObjects", IncrementActivePadMsg);
