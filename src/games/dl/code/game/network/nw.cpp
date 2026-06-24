#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSetGuiSetBusyCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSetGuiRefreshCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwGuiSetBusyCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwGuiRefreshCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", _load_microprogram);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwConnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwConnectDebug);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwDisconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwJoinDebug);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwJoin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSyncTime);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwFastUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwUpdate);

void nwLocalConnectCallback(void) {
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwLocalDisconnectCallback);

void nwRemoteConnectCallback(void) {
}

void nwRemoteDisconnectConnectCallback(void) {
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwLocalJoinCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwLeaveGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwPostJoin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSetMediusErrorCode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwGetLastMediusError);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwForcePlayerReportNextUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSendPlayerReport);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwInitializeWorldReportFromGameInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSetWorldReportGamestatsFromGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwUpdateWorldReportFromGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwInitializeWorldReportForNewGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwForceWorldReportNextUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSendWorldReport);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwUpdateLadderStats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwVoiceOnlyUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwUpdateLadderStatsCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwAccountUpdateStats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwAccountUpdateStatsCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwGetLadderStats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwGetLadderStatsCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwUpdateClanStats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", func_0015C2C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", FUN_0015c2d8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSMChangeCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwGetUniqueId);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", func_0015C718);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSetGetPlayerTypeCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwResetMyReportIntervalTimers);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwGetGleamingTheCubeClientIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwEnableGleamingTheCube);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwDisableGleamingTheCube);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwIsGleamingTheCubeEnabled);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSystemMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwGotSystemMessage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSMQueuePush);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSMQueuePop);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwGetMyIpCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwSetIgnoreListData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/network/nw", nwIsIgnored);
