#include "common.h"
#include "MediusRequests.h"

#define MEDIUS_BILLING_SECTION(name) __attribute__((section(".medius_billing_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_billing_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", MediusBillingClientVersion);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", MediusBillingServerVersion);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", func_01ED4430);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", MediusBillingUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", func_01ED4450);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", MediusBillingIsLoaded);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", func_01ED4478);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", MediusBillingAccountLogin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", MediusBillingLogInCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", MediusBillingAccountLogout);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", func_01ED4788);

MediusErrorCode MEDIUS_BILLING_SECTION(MediusCreateClan) MediusCreateClan(MediusCreateClanRequest *MyCreateClanRequest, MediusTypeCreateClanCallback MyCreateClanCallback, void *pUserData)
{
    MyCreateClanRequest->MessageID[20] = 0;
    MyCreateClanRequest->SessionKey[16] = 0;
    MyCreateClanRequest->ClanName[31] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[72] = MyCreateClanCallback;
    gUserArguments[72] = pUserData;
    if (MediusSendMessage(1, 0x54, sizeof(MediusCreateClanRequest), MyCreateClanRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusDisbandClan) MediusDisbandClan(MediusDisbandClanRequest *MyDisbandClanRequest, MediusTypeDisbandClanCallback MyDisbandClanCallback, void *pUserData)
{
    MyDisbandClanRequest->MessageID[20] = 0;
    MyDisbandClanRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[73] = MyDisbandClanCallback;
    gUserArguments[73] = pUserData;
    if (MediusSendMessage(1, 0x56, sizeof(MediusDisbandClanRequest), MyDisbandClanRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusGetClanByName) MediusGetClanByName(MediusGetClanByNameRequest *MyGetClanByNameRequest, MediusTypeGetClanByNameCallback MyGetClanByNameCallback, void *pUserData)
{
    MyGetClanByNameRequest->MessageID[20] = 0;
    MyGetClanByNameRequest->SessionKey[16] = 0;
    MyGetClanByNameRequest->ClanName[31] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[75] = MyGetClanByNameCallback;
    gUserArguments[75] = pUserData;
    if (MediusSendMessage(1, 0x5A, sizeof(MediusGetClanByNameRequest), MyGetClanByNameRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusGetClanByID) MediusGetClanByID(MediusGetClanByIDRequest *MyGetClanByIDRequest, MediusTypeGetClanByIDCallback MyGetClanByIDCallback, void *pUserData)
{
    MyGetClanByIDRequest->MessageID[20] = 0;
    MyGetClanByIDRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[74] = MyGetClanByIDCallback;
    gUserArguments[74] = pUserData;
    if (MediusSendMessage(1, 0x58, sizeof(MediusGetClanByIDRequest), MyGetClanByIDRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusTransferClanLeadership) MediusTransferClanLeadership(MediusTransferClanLeadershipRequest *MyTransferClanLeadershipRequest, MediusTypeTransferClanLeadershipCallback MyTransferClanLeadershipCallback, void *pUserData)
{
    MyTransferClanLeadershipRequest->MessageID[20] = 0;
    MyTransferClanLeadershipRequest->SessionKey[16] = 0;
    MyTransferClanLeadershipRequest->NewLeaderAccountName[31] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[76] = MyTransferClanLeadershipCallback;
    gUserArguments[76] = pUserData;
    if (MediusSendMessage(1, 0x5C, sizeof(MediusTransferClanLeadershipRequest), MyTransferClanLeadershipRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusRemovePlayerFromClan) MediusRemovePlayerFromClan(MediusRemovePlayerFromClanRequest *MyRemovePlayerFromClanRequest, MediusTypeRemovePlayerFromClanCallback MyRemovePlayerFromClanCallback, void *pUserData)
{
    MyRemovePlayerFromClanRequest->MessageID[20] = 0;
    MyRemovePlayerFromClanRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[78] = MyRemovePlayerFromClanCallback;
    gUserArguments[78] = pUserData;
    if (MediusSendMessage(1, 0x60, sizeof(MediusRemovePlayerFromClanRequest), MyRemovePlayerFromClanRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusInvitePlayerToClan) MediusInvitePlayerToClan(MediusInvitePlayerToClanRequest *MyInvitePlayerToClanRequest, MediusTypeInvitePlayerToClanCallback MyInvitePlayerToClanCallback, void *pUserData)
{
    MyInvitePlayerToClanRequest->MessageID[20] = 0;
    MyInvitePlayerToClanRequest->SessionKey[16] = 0;
    MyInvitePlayerToClanRequest->InviteMessage[199] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[79] = MyInvitePlayerToClanCallback;
    gUserArguments[79] = pUserData;
    if (MediusSendMessage(1, 0x62, sizeof(MediusInvitePlayerToClanRequest), MyInvitePlayerToClanRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusCheckMyClanInvitations) MediusCheckMyClanInvitations(MediusCheckMyClanInvitationsRequest *MyCheckMyClanInvitationsRequest, MediusTypeCheckMyClanInvitationsCallback MyCheckMyClanInvitationsCallback, void *pUserData)
{
    MyCheckMyClanInvitationsRequest->MessageID[20] = 0;
    MyCheckMyClanInvitationsRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[80] = MyCheckMyClanInvitationsCallback;
    gUserArguments[80] = pUserData;
    if (MediusSendMessage(1, 0x64, sizeof(MediusCheckMyClanInvitationsRequest), MyCheckMyClanInvitationsRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusGetClanInvitationsSent) MediusGetClanInvitationsSent(MediusGetClanInvitationsSentRequest *MyGetClanInvitationsSentRequest, MediusTypeGetClanInvitationsSentCallback MyGetClanInvitationsSentCallback, void *pUserData)
{
    MyGetClanInvitationsSentRequest->MessageID[20] = 0;
    MyGetClanInvitationsSentRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[81] = MyGetClanInvitationsSentCallback;
    gUserArguments[81] = pUserData;
    if (MediusSendMessage(1, 0x7A, sizeof(MediusGetClanInvitationsSentRequest), MyGetClanInvitationsSentRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusRespondToClanInvitation) MediusRespondToClanInvitation(MediusRespondToClanInvitationRequest *MyRespondToClanInvitationRequest, MediusTypeRespondToClanInvitationCallback MyRespondToClanInvitationCallback, void *pUserData)
{
    MyRespondToClanInvitationRequest->MessageID[20] = 0;
    MyRespondToClanInvitationRequest->SessionKey[16] = 0;
    MyRespondToClanInvitationRequest->Message[199] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[82] = MyRespondToClanInvitationCallback;
    gUserArguments[82] = pUserData;
    if (MediusSendMessage(1, 0x66, sizeof(MediusRespondToClanInvitationRequest), MyRespondToClanInvitationRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusRevokeClanInvitation) MediusRevokeClanInvitation(MediusRevokeClanInvitationRequest *MyRevokeClanInvitationRequest, MediusTypeRevokeClanInvitationCallback MyRevokeClanInvitationCallback, void *pUserData)
{
    MyRevokeClanInvitationRequest->MessageID[20] = 0;
    MyRevokeClanInvitationRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[83] = MyRevokeClanInvitationCallback;
    gUserArguments[83] = pUserData;
    if (MediusSendMessage(1, 0x68, sizeof(MediusRevokeClanInvitationRequest), MyRevokeClanInvitationRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusGetMyClanMessages) MediusGetMyClanMessages(MediusGetMyClanMessagesRequest *MyGetMyClanMessagesRequest, MediusTypeGetMyClanMessagesCallback MyGetMyClanMessagesCallback, void *pUserData)
{
    MyGetMyClanMessagesRequest->MessageID[20] = 0;
    MyGetMyClanMessagesRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[85] = MyGetMyClanMessagesCallback;
    gUserArguments[85] = pUserData;
    if (MediusSendMessage(1, 0x6C, sizeof(MediusGetMyClanMessagesRequest), MyGetMyClanMessagesRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusSendClanMessage) MediusSendClanMessage(MediusSendClanMessageRequest *MySendClanMessageRequest, MediusTypeSendClanMessageCallback MySendClanMessageCallback, void *pUserData)
{
    MySendClanMessageRequest->MessageID[20] = 0;
    MySendClanMessageRequest->SessionKey[16] = 0;
    MySendClanMessageRequest->Message[199] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[86] = MySendClanMessageCallback;
    gUserArguments[86] = pUserData;
    if (MediusSendMessage(1, 0x6E, sizeof(MediusSendClanMessageRequest), MySendClanMessageRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusModifyClanMessage) MediusModifyClanMessage(MediusModifyClanMessageRequest *MyModifyClanMessageRequest, MediusTypeModifyClanMessageCallback MyModifyClanMessageCallback, void *pUserData)
{
    MyModifyClanMessageRequest->MessageID[20] = 0;
    MyModifyClanMessageRequest->SessionKey[16] = 0;
    MyModifyClanMessageRequest->NewMessage[199] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[87] = MyModifyClanMessageCallback;
    gUserArguments[87] = pUserData;
    if (MediusSendMessage(1, 0x70, sizeof(MediusModifyClanMessageRequest), MyModifyClanMessageRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusDeleteClanMessage) MediusDeleteClanMessage(MediusDeleteClanMessageRequest *MyDeleteClanMessageRequest, MediusTypeDeleteClanMessageCallback MyDeleteClanMessageCallback, void *pUserData)
{
    MyDeleteClanMessageRequest->MessageID[20] = 0;
    MyDeleteClanMessageRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[88] = MyDeleteClanMessageCallback;
    gUserArguments[88] = pUserData;
    if (MediusSendMessage(1, 0x72, sizeof(MediusDeleteClanMessageRequest), MyDeleteClanMessageRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusRequestClanTeamChallenge) MediusRequestClanTeamChallenge(MediusRequestClanTeamChallengeRequest *MyRequestClanTeamChallengeRequest, MediusTypeRequestClanTeamChallengeCallback MyRequestClanTeamChallengeCallback, void *pUserData)
{
    MyRequestClanTeamChallengeRequest->MessageID[20] = 0;
    MyRequestClanTeamChallengeRequest->SessionKey[16] = 0;
    MyRequestClanTeamChallengeRequest->Message[199] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[84] = MyRequestClanTeamChallengeCallback;
    gUserArguments[84] = pUserData;
    if (MediusSendMessage(1, 0x6A, sizeof(MediusRequestClanTeamChallengeRequest), MyRequestClanTeamChallengeRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusRespondToClanTeamChallenge) MediusRespondToClanTeamChallenge(MediusRespondToClanTeamChallengeRequest *MyRespondToClanTeamChallengeRequest, MediusTypeRespondToClanTeamChallengeCallback MyRespondToClanTeamChallengeCallback, void *pUserData)
{
    MyRespondToClanTeamChallengeRequest->MessageID[20] = 0;
    MyRespondToClanTeamChallengeRequest->SessionKey[16] = 0;
    MyRespondToClanTeamChallengeRequest->Message[199] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[89] = MyRespondToClanTeamChallengeCallback;
    gUserArguments[89] = pUserData;
    if (MediusSendMessage(1, 0x74, sizeof(MediusRespondToClanTeamChallengeRequest), MyRespondToClanTeamChallengeRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusRevokeClanTeamChallenge) MediusRevokeClanTeamChallenge(MediusRevokeClanTeamChallengeRequest *MyRevokeClanTeamChallengeRequest, MediusTypeRevokeClanTeamChallengeCallback MyRevokeClanTeamChallengeCallback, void *pUserData)
{
    MyRevokeClanTeamChallengeRequest->MessageID[20] = 0;
    MyRevokeClanTeamChallengeRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[90] = MyRevokeClanTeamChallengeCallback;
    gUserArguments[90] = pUserData;
    if (MediusSendMessage(1, 0x76, sizeof(MediusRevokeClanTeamChallengeRequest), MyRevokeClanTeamChallengeRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusGetClanTeamChallenges) MediusGetClanTeamChallenges(MediusGetClanTeamChallengesRequest *MyGetClanTeamChallengesRequest, MediusTypeGetClanTeamChallengesCallback MyGetClanTeamChallengesCallback, void *pUserData)
{
    MyGetClanTeamChallengesRequest->MessageID[20] = 0;
    MyGetClanTeamChallengesRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[95] = MyGetClanTeamChallengesCallback;
    gUserArguments[95] = pUserData;
    if (MediusSendMessage(1, 0x82, sizeof(MediusGetClanTeamChallengesRequest), MyGetClanTeamChallengesRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusGetMyClans) MediusGetMyClans(MediusGetMyClansRequest *MyGetMyClansRequest, MediusTypeGetMyClansCallback MyGetMyClansCallback, void *pUserData)
{
    MyGetMyClansRequest->MessageID[20] = 0;
    MyGetMyClansRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[94] = MyGetMyClansCallback;
    gUserArguments[94] = pUserData;
    if (MediusSendMessage(1, 0x7C, sizeof(MediusGetMyClansRequest), MyGetMyClansRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusBilling", func_01ED5218);

MediusErrorCode MEDIUS_BILLING_SECTION(MediusGetAllClanMessages) MediusGetAllClanMessages(MediusGetAllClanMessagesRequest *MyGetAllClanMessagesRequest, MediusTypeGetAllClanMessagesCallback MyGetAllClanMessagesCallback, void *pUserData)
{
    MyGetAllClanMessagesRequest->MessageID[20] = 0;
    MyGetAllClanMessagesRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[92] = MyGetAllClanMessagesCallback;
    gUserArguments[92] = pUserData;
    if (MediusSendMessage(1, 0x7E, sizeof(MediusGetAllClanMessagesRequest), MyGetAllClanMessagesRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_BILLING_SECTION(MediusGetClanTeamChallengeHistory) MediusGetClanTeamChallengeHistory(MediusGetClanTeamChallengeHistoryRequest *MyGetClanTeamChallengeHistoryRequest, MediusTypeGetClanTeamChallengeHistoryCallback MyGetClanTeamChallengeHistoryCallback, void *pUserData)
{
    MyGetClanTeamChallengeHistoryRequest->MessageID[20] = 0;
    MyGetClanTeamChallengeHistoryRequest->SessionKey[16] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[93] = MyGetClanTeamChallengeHistoryCallback;
    gUserArguments[93] = pUserData;
    if (MediusSendMessage(1, 0x78, sizeof(MediusGetClanTeamChallengeHistoryRequest), MyGetClanTeamChallengeHistoryRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}
