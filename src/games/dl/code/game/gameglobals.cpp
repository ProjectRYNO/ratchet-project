#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", SetFrontEndState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwKbdTimerFunc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", InitMultiplayerProfiles);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", ShutdownPS2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", PowerOffThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", PreparePowerOff);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", UndoPowerOff);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSetGuiSetBusyCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015A010);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015A028);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwGuiRefreshCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", _load_microprogram);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwConnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwConnectDebug);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwDisconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwJoinDebug);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwJoin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSyncTime);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwFastUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwUpdate);

void nwLocalConnectCallback(void) {
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwLocalDisconnectCallback);

void nwRemoteConnectCallback(void) {
}

void nwRemoteDisconnectConnectCallback(void) {
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwLocalJoinCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwLeaveGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwPostJoin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSetMediusErrorCode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwGetLastMediusError);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwForcePlayerReportNextUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSendPlayerReport);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwInitializeWorldReportFromGameInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSetWorldReportGamestatsFromGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwUpdateWorldReportFromGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwInitializeWorldReportForNewGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwForceWorldReportNextUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSendWorldReport);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwUpdateLadderStats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwVoiceOnlyUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015BC58);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwAccountUpdateStats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015BED0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwGetLadderStats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015C018);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwUpdateClanStats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015C2C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015c2d8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015C6B0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwGetUniqueId);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015C718);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015c730);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015c748);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwEnableGleamingTheCube);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwDisableGleamingTheCube);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015c770);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSystemMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015C818);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSMQueuePush);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSMQueuePop);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015CAF8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015CB10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwIsIgnored);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cb88);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cbb0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cbd8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cc00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cc28);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cc50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cc78);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cca0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015ccc8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015ccf0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cd18);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cd40);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cd68);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cd90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cdb8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cde0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015ce08);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015ce30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015ce58);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015ce80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cea8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015ced0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cef8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cf20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cf48);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cf70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cf98);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cfc0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015cfe8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d010);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d038);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d060);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d088);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d0b0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d0d8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d100);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d128);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d150);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d178);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d1a0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d1c8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d1f0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d218);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d240);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d268);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d290);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d2b8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d2e0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d308);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d330);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d358);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d380);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d3a8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d3d0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d3f8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d420);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d448);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d470);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d498);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d4c0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d4e8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d510);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d538);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d560);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d588);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d5b0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d5d8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d600);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d628);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d650);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d678);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d6a0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwReassignWorldIDCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d700);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d728);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d750);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d778);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d7a0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d7c8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d7f0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015d818);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015da10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015da28);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwMalloc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwRealloc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwFree);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015DB78);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015db80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", __builtin_delete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015DBA8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwInitializeSCERT);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwRegisterAll);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwInitAudioInfoData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015DDE8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwRegisterMessages);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015dfd8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e038);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e098);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e0f8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e158);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e1b8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e218);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e278);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e2d8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e338);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e3b8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e418);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e478);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e4d8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e538);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e598);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e5f8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e658);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015e6b8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwGameOverObjectCleanUp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwInitGameObjsArray);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwRegisterObjects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015EEF0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015EEF8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwRemoteNetPlayerCreationComplete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwPlayerInfoCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwRemoteNetPlayerDeletionComplete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwRemoteNetGameSettingsCreationCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015F068);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_0015f098);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwReleaseGameSettingsObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwRemoteNetPlayerDataCreationCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwRemoteNetPlayerDataUpdateCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwRemoteNetPlayerDataDeletionCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwCleanUp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwGetTeam);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwIsPlayerBlocked);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015F3B8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwClearBlockedPlayers);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015F430);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwCreateLocalGame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwCreateLocalNetPlayer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_0015FE10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwPlayerSetupMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwClientJoinMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwClientJoinResponseCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSetDefaultGameSetupFlags);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSetGameSetupFlagsForGameType);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwSendGameOptionsCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwGameOptionsMessageCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00160AF8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00160FD8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00161118);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00161128);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00161138);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00161158);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwMGCL_Initialize_Module);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwMGCL_Initialize_API);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00161270);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwMGCL_Update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_001612F8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00161310);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00161320);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00161330);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00161340);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", AppInitAudio);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", AppAudioEnumerate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", AppAudioOnFrame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", AppAudioIsHeadsetAttached);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", AppStartRecording);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", AppStopRecording);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", StartPlayback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", AppShutdownAudio);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00161628);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", AudioInput);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", AudioOutput);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", _audioAsyncRequestOp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", _voiceGetNextOp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_001617B0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", voiceThread);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", VoiceGetNextOutputBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", VoiceGetNextInputBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", VoiceReset);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", VoiceStart);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", VoiceStop);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", VoiceInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", VoiceShutdown);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", VoiceProcess);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00161e60);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwAudioPlayCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwAudioRecordCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwVoiceSetStreamMediaParams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00162720);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00162740);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwVoiceEnableGlobalChat);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00162840);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwVoiceIsTalking);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nwVoiceClientLookup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00162968);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", FUN_00162978);

void FUN_00162998(void) {
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nmsCreate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nmsDestroy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00162C98);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nmsEncode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nmsReadyForMultiDecode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nmsMultiDecode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", setVad);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nmsAddBlockToBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nmsMultiDecodeFlush);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nmsFindFreeBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nmsBufferIsFree);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", nmsMultiDecodeUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00163370);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", srand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", rand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", rand16);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00163440);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", cb_cdComplete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", Sync);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", Update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", Initialize);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", fs__Reset);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", Load);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", LoadAsync);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", Abort);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", IsLoading);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", GetBuffer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", cb_missionBankLoadComplete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", load_file);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", is_complete_file);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", abort_file);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", func_00163A18);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", load_mission_bank);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", is_complete_mission_bank);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", abort_mission_bank);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gameglobals", load_complete_mission_bank);
