#include "common.h"
#include "MediusRequests.h"

#define MEDIUS_CLANS_SECTION(name) __attribute__((section(".medius_clans_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_clans_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

MediusErrorCode MEDIUS_CLANS_SECTION(MediusUpdateClanStats) MediusUpdateClanStats(MediusUpdateClanStatsRequest *MyUpdateClanStatsRequest,
                                      MediusTypeUpdateClanStatsCallback MyUpdateClanStatsCallback,
                                      void *pUserData)
{
    MyUpdateClanStatsRequest->MessageID[20] = 0;
    MyUpdateClanStatsRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!ghMyConnection) return MediusErrorNotConnected;
    gMediusFunctionPointers[96] = MyUpdateClanStatsCallback;
    gUserArguments[96] = pUserData;
    if (MediusSendMessage(1, 0x84, sizeof(MediusUpdateClanStatsRequest), MyUpdateClanStatsRequest) != 0)
        return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClans", func_01ED53A0);

MediusErrorCode MEDIUS_CLANS_SECTION(MediusClanLadderList) MediusClanLadderList(MediusClanLadderListRequest *MyClanLadderListRequest, MediusTypeClanLadderListCallback MyClanLadderListCallback, void *pUserData)
{
    MyClanLadderListRequest->MessageID[20] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[98] = MyClanLadderListCallback;
    gUserArguments[98] = pUserData;
    if ((unsigned int)MyClanLadderListRequest->ClanLadderStatIndex >= 100) MyClanLadderListRequest->ClanLadderStatIndex = 0;
    if (MediusSendMessage(1, 0xD2, sizeof(MediusClanLadderListRequest), MyClanLadderListRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLANS_SECTION(MediusClanLadderPosition) MediusClanLadderPosition(MediusClanLadderPositionRequest *MyClanLadderPositionRequest, MediusTypeClanLadderPositionCallback MyClanLadderPositionCallback, void *pUserData)
{
    MyClanLadderPositionRequest->MessageID[20] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[99] = MyClanLadderPositionCallback;
    gUserArguments[99] = pUserData;
    if ((unsigned int)MyClanLadderPositionRequest->ClanLadderStatIndex >= 100) MyClanLadderPositionRequest->ClanLadderStatIndex = 0;
    if (MediusSendMessage(1, 0xD4, sizeof(MediusClanLadderPositionRequest), MyClanLadderPositionRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLANS_SECTION(MediusGetClanMemberList_ExtraInfo) MediusGetClanMemberList_ExtraInfo(MediusGetClanMemberList_ExtraInfoRequest *MyGetClanMemberList_ExtraInfoRequest, MediusTypeGetClanMemberList_ExtraInfoCallback MyGetClanMemberList_ExtraInfoCallback, void *pUserData)
{
    MyGetClanMemberList_ExtraInfoRequest->MessageID[20] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[100] = MyGetClanMemberList_ExtraInfoCallback;
    gUserArguments[100] = pUserData;
    if ((unsigned int)MyGetClanMemberList_ExtraInfoRequest->LadderStatIndex >= 100) MyGetClanMemberList_ExtraInfoRequest->LadderStatIndex = 0;
    if (MediusSendMessage(1, 0xDA, sizeof(MediusGetClanMemberList_ExtraInfoRequest), MyGetClanMemberList_ExtraInfoRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}
