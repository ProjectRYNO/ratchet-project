#include "common.h"
#include "MediusRequests.h"

#define MEDIUS_CLIENT_SECTION(name) __attribute__((section(".medius_client_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_client_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern short GlobalLobbyFilterFlag;
extern MediusFilterMaskInfo MyFilterMaskInfo;
// 1 when accounts are handled through MediusBilling; MediusAccountDelete is then not available.
extern int mediusBillingEnabled;
// Copy of the last logout request, resent by MediusAccountLogoutInternal.
extern MediusAccountLogoutRequest mediusBillingLogoutRequest;
extern int printf(const char *, ...);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", FUN_01ed5528);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", FUN_01ed5538);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusSetNatServiceAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusGetNatServiceAddress);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusSetProcessingState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusGetProcessingState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusSetClientAddrList);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusGetClientAddrList);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusResolveAddrCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusSetQueuedRequest);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusGetQueuedRequestType);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusGetQueuedRequest);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusCheckRequestQueue);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", BillingLoginCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", BillingLogoutCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusLocalConnectCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusSetClientConnectCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusGetClientConnectCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusGetClientConnectCallbackArg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusClearClientConnectCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED5B70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusInitializeBare);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED5CA8);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetServerTime) MediusGetServerTime(MediusGetServerTimeRequest *MyGetServerTimeRequest, MediusTypeGetServerTimeCallback MyGetServerTimeCallback,void *pUserData)
{
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[122] = MyGetServerTimeCallback;
    gUserArguments[122] = pUserData;
    if (MediusSendMessage(4, 0x2a, 0x15, MyGetServerTimeRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusGetMySessionKey);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusCloseBare);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusSendMessage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusConnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusSetDefaultDisconnectParams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusDisconnectCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MUISDisconnectCB);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusDisconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusUpdateUniverseInformation);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusUpdateBare);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusUpdateClientState) MediusUpdateClientState(MediusUpdateUserState *req)
{
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    req->SessionKey[0x10] = 0;
    if (MediusSendMessage(1, 0x49, 0x18, req) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusSessionBegin);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusSessionEnd) MediusSessionEnd(MediusSessionEndRequest *req, MediusTypeSessionEndCallback callback, void *pUserData)
{
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    if (req == 0 || req->SessionKey[0] == 0) return MediusErrorInvalidParameter;
        req->SessionKey[0x10] = 0;
        req->MessageID[0x14] = 0;
        gMediusFunctionPointers[2] = callback;
        gUserArguments[2] = pUserData;
    if (MediusSendMessage(1, 5, 0x26, req) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusDnasSignature) MediusDnasSignature(MediusDnasSignaturePost *MyDnasSignaturePost)
{
    MyDnasSignaturePost->MessageID[0x14] = 0;
    MyDnasSignaturePost->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    if (MediusSendMessage(4, 10, 0x50, MyDnasSignaturePost) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusAccountLogin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusAccountLoginInternal);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusAccountLogout);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusAccountLogoutInternal) MediusAccountLogoutInternal(MediusAccountLogoutRequest *req)
{
    printf("IDF... MediusAccountLogoutInternal\n");
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    if (MediusSendMessage(1, 0x15, 0x26, &mediusBillingLogoutRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED6908);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusAccountRegistration) MediusAccountRegistration(MediusAccountRegistrationRequest *MyAccountRegistrationRequest, MediusTypeAccountRegistrationCallback MyAccountRegistrationCallback,void *pUserData)
{
    MyAccountRegistrationRequest->MessageID[0x14] = 0;
    MyAccountRegistrationRequest->SessionKey[0x10] = 0;
    MyAccountRegistrationRequest->AccountName[0x1f] = 0;
    MyAccountRegistrationRequest->Password[0x1f] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[6] = MyAccountRegistrationCallback;
    gUserArguments[6] = pUserData;
    if (MediusSendMessage(1, 9, 0x6c, MyAccountRegistrationRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusAccountUpdateStats) MediusAccountUpdateStats(MediusAccountUpdateStatsRequest *MyAccountUpdateStatsRequest, MediusTypeAccountUpdateStatsCallback MyAccountUpdateStatsCallback,void *pUserData)
{
    MyAccountUpdateStatsRequest->MessageID[0x14] = 0;
    MyAccountUpdateStatsRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[9] = MyAccountUpdateStatsCallback;
    gUserArguments[9] = pUserData;
    if (MediusSendMessage(1, 0x11, 0x126, MyAccountUpdateStatsRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED6A18);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusAccountDelete) MediusAccountDelete(MediusAccountDeleteRequest *req, MediusTypeAccountDeleteCallback callback, void *pUserData)
{
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    if (mediusBillingEnabled == 1) return MediusErrorFeatureNotEnabled;
    gMediusFunctionPointers[11] = callback;
    gUserArguments[11] = pUserData;
    if (MediusSendMessage(1, 0x13, 0x46, req) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusAnonymousLogin) MediusAnonymousLogin(MediusAnonymousLoginRequest *MyAnonymousLoginRequest, MediusTypeAnonymousLoginCallback MyAnonymousLoginCallback,void *pUserData)
{
    MyAnonymousLoginRequest->MessageID[0x14] = 0;
    MyAnonymousLoginRequest->SessionKey[0x10] = 0;
    MyAnonymousLoginRequest->SessionDisplayName[0x1f] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[12] = MyAnonymousLoginCallback;
    gUserArguments[12] = pUserData;
    if (MediusSendMessage(1, 0x19, 0x146, MyAnonymousLoginRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusCreateGame) MediusCreateGame(MediusCreateGameRequest *MyCreateGameRequest, MediusTypeCreateGameCallback MyCreateGameCallback,void *pUserData)
{
    MyCreateGameRequest->MessageID[0x14] = 0;
    MyCreateGameRequest->SessionKey[0x10] = 0;
    MyCreateGameRequest->GameName[0x3f] = 0;
    MyCreateGameRequest->GamePassword[0x1f] = 0;
    MyCreateGameRequest->SpectatorPassword[0x1f] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[15] = MyCreateGameCallback;
    gUserArguments[15] = pUserData;
    if (MediusSendMessage(4, 0x2f, 0xe8, MyCreateGameRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusTextFilter) MediusTextFilter(MediusTextFilterRequest *MyTextFilterRequest, MediusTypeTextFilterCallback MyTextFilterCallback,void *pUserData)
{
    MyTextFilterRequest->MessageID[0x14] = 0;
    MyTextFilterRequest->SessionKey[0x10] = 0;
    MyTextFilterRequest->Text[0x3f] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[48] = MyTextFilterCallback;
    gUserArguments[48] = pUserData;
    if (MediusSendMessage(1, 0x98, 0x6c, MyTextFilterRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusCreateChannel) MediusCreateChannel(MediusCreateChannelRequest *MyCreateChannelRequest, MediusTypeCreateChannelCallback MyCreateChannelCallback,void *pUserData)
{
    MyCreateChannelRequest->MessageID[0x14] = 0;
    MyCreateChannelRequest->SessionKey[0x10] = 0;
    MyCreateChannelRequest->LobbyName[0x3f] = 0;
    MyCreateChannelRequest->LobbyPassword[0x1f] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[16] = MyCreateChannelCallback;
    gUserArguments[16] = pUserData;
    if (MediusSendMessage(4, 0x14, 0xa4, MyCreateChannelRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusJoinGame);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusJoinChannel) MediusJoinChannel(MediusJoinChannelRequest *MyJoinChannelRequest, MediusTypeJoinChannelCallback MyJoinChannelCallback,void *pUserData)
{
    MyJoinChannelRequest->MessageID[0x14] = 0;
    MyJoinChannelRequest->SessionKey[0x10] = 0;
    MyJoinChannelRequest->LobbyChannelPassword[0x1f] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[18] = MyJoinChannelCallback;
    gUserArguments[18] = pUserData;
    if (MediusSendMessage(1, 0x25, 0x4c, MyJoinChannelRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED6E30);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetGamePlayers) MediusGetGamePlayers(MediusGameWorldPlayerListRequest *MyGameWorldPlayerListRequest, MediusTypeGameWorldPlayerListCallback MyGameWorldPlayerListCallback,void *pUserData)
{
    MyGameWorldPlayerListRequest->MessageID[0x14] = 0;
    MyGameWorldPlayerListRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[14] = MyGameWorldPlayerListCallback;
    gUserArguments[14] = pUserData;
    if (MediusSendMessage(1, 0x2f, 0x2c, MyGameWorldPlayerListRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetPlayerInfo) MediusGetPlayerInfo(MediusPlayerInfoRequest *MyPlayerInfoRequest, MediusTypePlayerInfoCallback MyPlayerInfoCallback,void *pUserData)
{
    MyPlayerInfoRequest->MessageID[0x14] = 0;
    MyPlayerInfoRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[21] = MyPlayerInfoCallback;
    gUserArguments[21] = pUserData;
    if (MediusSendMessage(1, 0x31, 0x2c, MyPlayerInfoRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetGameInfo) MediusGetGameInfo(MediusGameInfoRequest *MyGameInfoRequest, MediusTypeGameInfoCallback MyGameInfoCallback,void *pUserData)
{
    MyGameInfoRequest->MessageID[0x14] = 0;
    MyGameInfoRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[22] = MyGameInfoCallback;
    gUserArguments[22] = pUserData;
    if (MediusSendMessage(4, 0x35, 0x2c, MyGameInfoRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetChannelInfo) MediusGetChannelInfo(MediusChannelInfoRequest *MyChannelInfoRequest, MediusTypeChannelInfoCallback MyChannelInfoCallback,void *pUserData)
{
    MyChannelInfoRequest->MessageID[0x14] = 0;
    MyChannelInfoRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[23] = MyChannelInfoCallback;
    gUserArguments[23] = pUserData;
    if (MediusSendMessage(1, 0x35, 0x2c, MyChannelInfoRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusFindPlayer) MediusFindPlayer(MediusFindPlayerRequest *MyFindPlayerRequest, MediusTypeFindPlayerCallback MyFindPlayerCallback,void *pUserData)
{
    MyFindPlayerRequest->MessageID[0x14] = 0;
    MyFindPlayerRequest->SessionKey[0x10] = 0;
    MyFindPlayerRequest->Name[0x1f] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[25] = MyFindPlayerCallback;
    gUserArguments[25] = pUserData;
    if (MediusSendMessage(1, 0x39, 0x50, MyFindPlayerRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusSendGenericChatMessage) MediusSendGenericChatMessage(MediusGenericChatMessage *MySendGenericChatMessage)
{
    MySendGenericChatMessage->MessageID[0x14] = 0;
    MySendGenericChatMessage->SessionKey[0x10] = 0;
    MySendGenericChatMessage->Message[0x3f] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    if (MediusSendMessage(4, 0x23, 0x70, MySendGenericChatMessage) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusSendBinaryMessage) MediusSendBinaryMessage(MediusBinaryMessage *MySendBinaryMessage)
{
    MySendBinaryMessage->MessageID[0x14] = 0;
    MySendBinaryMessage->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    if (MediusSendMessage(4, 0x16, 0x1c0, MySendBinaryMessage) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED7190);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusAddToBuddyList) MediusAddToBuddyList(MediusAddToBuddyListRequest *MyAddToBuddyListRequest, MediusTypeAddToBuddyListCallback MyAddToBuddyListCallback,void *pUserData)
{
    MyAddToBuddyListRequest->MessageID[0x14] = 0;
    MyAddToBuddyListRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[28] = MyAddToBuddyListCallback;
    gUserArguments[28] = pUserData;
    if (MediusSendMessage(1, 0x3f, 0x2c, MyAddToBuddyListRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusRemoveFromBuddyList) MediusRemoveFromBuddyList(MediusRemoveFromBuddyListRequest *MyRemoveFromBuddyListRequest, MediusTypeRemoveFromBuddyListCallback MyRemoveFromBuddyListCallback,void *pUserData)
{
    MyRemoveFromBuddyListRequest->MessageID[0x14] = 0;
    MyRemoveFromBuddyListRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[29] = MyRemoveFromBuddyListCallback;
    gUserArguments[29] = pUserData;
    if (MediusSendMessage(1, 0x41, 0x2c, MyRemoveFromBuddyListRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED7298);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetIgnoreList) MediusGetIgnoreList(MediusGetIgnoreListRequest *MyGetIgnoreListRequest, MediusTypeGetIgnoreListCallback MyGetIgnoreListCallback,void *pUserData)
{
    MyGetIgnoreListRequest->MessageID[0x14] = 0;
    MyGetIgnoreListRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[32] = MyGetIgnoreListCallback;
    gUserArguments[32] = pUserData;
    if (MediusSendMessage(1, 0xc0, 0x26, MyGetIgnoreListRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusAddToIgnoreList) MediusAddToIgnoreList(MediusAddToIgnoreListRequest *MyAddToIgnoreListRequest, MediusTypeAddToIgnoreListCallback MyAddToIgnoreListCallback,void *pUserData)
{
    MyAddToIgnoreListRequest->MessageID[0x14] = 0;
    MyAddToIgnoreListRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[33] = MyAddToIgnoreListCallback;
    gUserArguments[33] = pUserData;
    if (MediusSendMessage(1, 0xc2, 0x2c, MyAddToIgnoreListRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusRemoveFromIgnoreList) MediusRemoveFromIgnoreList(MediusRemoveFromIgnoreListRequest *MyRemoveFromIgnoreListRequest, MediusTypeRemoveFromIgnoreListCallback MyRemoveFromIgnoreListCallback,void *pUserData)
{
    MyRemoveFromIgnoreListRequest->MessageID[0x14] = 0;
    MyRemoveFromIgnoreListRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[34] = MyRemoveFromIgnoreListCallback;
    gUserArguments[34] = pUserData;
    if (MediusSendMessage(1, 0xc4, 0x2c, MyRemoveFromIgnoreListRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusGetPolicy);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusSendPlayerReport) MediusSendPlayerReport(MediusPlayerReport *PlayerReport)
{
    PlayerReport->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    if (MediusSendMessage(1, 1, 0x118, PlayerReport->SessionKey) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusSendWorldReport) MediusSendWorldReport(MediusWorldReport *WorldReport)
{
    WorldReport->GameName[0x3f] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    if (MediusSendMessage(4, 0x30, 0x180, WorldReport) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusSendEndGameReport) MediusSendEndGameReport(MediusEndGameReport *EndGameReport)
{
    EndGameReport->SessionKey[0x10] = 0;
    EndGameReport->WinningTeam[0x3f] = 0;
    EndGameReport->WinningPlayer[0x1f] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    if (MediusSendMessage(1, 2, 0x7c, EndGameReport->SessionKey) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetAnnouncements) MediusGetAnnouncements(MediusGetAnnouncementsRequest *MyGetAnnouncementsRequest, MediusTypeGetAnnouncementsCallback MyGetAnnouncementsCallback,void *pUserData)
{
    MyGetAnnouncementsRequest->MessageID[0x14] = 0;
    MyGetAnnouncementsRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[37] = MyGetAnnouncementsCallback;
    gUserArguments[37] = pUserData;
    if (MediusSendMessage(1, 0x4b, 0x2c, MyGetAnnouncementsRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetAllAnnouncements) MediusGetAllAnnouncements(MediusGetAllAnnouncementsRequest *MyGetAllAnnouncementsRequest, MediusTypeGetAnnouncementsCallback MyGetAnnouncementsCallback,void *pUserData)
{
    MyGetAllAnnouncementsRequest->MessageID[0x14] = 0;
    MyGetAllAnnouncementsRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[37] = MyGetAnnouncementsCallback;
    gUserArguments[37] = pUserData;
    if (MediusSendMessage(1, 0x4c, 0x2c, MyGetAllAnnouncementsRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusSetGameListFilter) MediusSetGameListFilter(MediusSetGameListFilterRequest *MySetGameListFilterRequest, MediusTypeSetGameListFilterCallback MySetGameListFilterCallback,void *pUserData)
{
    MySetGameListFilterRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[38] = MySetGameListFilterCallback;
    gUserArguments[38] = pUserData;
    if (MediusSendMessage(4, 0x33, 0x28, MySetGameListFilterRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusClearGameListFilter) MediusClearGameListFilter(MediusClearGameListFilterRequest *MyClearGameListFilterRequest, MediusTypeClearGameListFilterCallback MyClearGameListFilterCallback,void *pUserData)
{
    MyClearGameListFilterRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[39] = MyClearGameListFilterCallback;
    gUserArguments[39] = pUserData;
    if (MediusSendMessage(4, 0x31, 0x1c, MyClearGameListFilterRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetGameListFilter) MediusGetGameListFilter(MediusGetGameListFilterRequest *MyGetGameListFilterRequest, MediusTypeGetGameListFilterCallback MyGetGameListFilterCallback,void *pUserData)
{
    MyGetGameListFilterRequest->MessageID[0x14] = 0;
    MyGetGameListFilterRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[40] = MyGetGameListFilterCallback;
    gUserArguments[40] = pUserData;
    if (MediusSendMessage(1, 0x52, 0x26, MyGetGameListFilterRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusCreateMessageID);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetMyIP) MediusGetMyIP(MediusGetMyIPRequest *MyGetMyIPRequest,MediusTypeGetMyIPCallback MyGetMyIPCallback, void *pUserData)
{
    MyGetMyIPRequest->MessageID[0x14] = 0;
    MyGetMyIPRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[42] = MyGetMyIPCallback;
    gUserArguments[42] = pUserData;
    if (MediusSendMessage(1, 0x1b, 0x26, MyGetMyIPRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED79C8);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusAccountGetID) MediusAccountGetID(MediusAccountGetIDRequest *MyAccountGetIDRequest, MediusTypeAccountGetIDCallback MyAccountGetIDCallback,void *pUserData)
{
    MyAccountGetIDRequest->MessageID[0x14] = 0;
    MyAccountGetIDRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[3] = MyAccountGetIDCallback;
    gUserArguments[3] = pUserData;
    if (MediusSendMessage(1, 0x17, 0x46, MyAccountGetIDRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetLocations) MediusGetLocations(MediusGetLocationsRequest *MyGetLocationsRequest, MediusTypeGetLocationsCallback MyGetLocationsCallback,void *pUserData)
{
    MyGetLocationsRequest->MessageID[0x14] = 0;
    MyGetLocationsRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[45] = MyGetLocationsCallback;
    gUserArguments[45] = pUserData;
    if (MediusSendMessage(1, 0x8c, 0x26, MyGetLocationsRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED7AD8);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGenericChatSetFilter) MediusGenericChatSetFilter(MediusGenericChatSetFilterRequest *MyGenericChatSetFilterRequest, MediusTypeGenericChatSetFilterCallback MyGenericChatSetFilterCallback,void *pUserData)
{
    MyGenericChatSetFilterRequest->MessageID[0x14] = 0;
    MyGenericChatSetFilterRequest->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[71] = MyGenericChatSetFilterCallback;
    gUserArguments[71] = pUserData;
    if (MediusSendMessage(4, 0x25, 0x36, MyGenericChatSetFilterRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED7B70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusSetDefaultConnectInParams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED7C88);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusSetLocalizationParams) MediusSetLocalizationParams(MediusSetLocalizationParamsRequest *MySetLocalizationParams, MediusTypeSetLocalizationParamsCallback MySetLocalizationParamsCallback,void *pUserData)
{
    MySetLocalizationParams->MessageID[0x14] = 0;
    MySetLocalizationParams->SessionKey[0x10] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[54] = MySetLocalizationParamsCallback;
    gUserArguments[54] = pUserData;
    if (MediusSendMessage(1, 0xa3, 0x30, MySetLocalizationParams) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED7D28);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", MediusGetUniverseInformation);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetBuddyList_ExtraInfo) MediusGetBuddyList_ExtraInfo(MediusGetBuddyList_ExtraInfoRequest *MyGetBuddyListRequest, MediusTypeGetBuddyList_ExtraInfoCallback MyGetBuddyListCallback,void *pUserData)
{
    MyGetBuddyListRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[58] = MyGetBuddyListCallback;
    gUserArguments[58] = pUserData;
    if (MediusSendMessage(1, 0xd6, 0x15, MyGetBuddyListRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetTotalRankings) MediusGetTotalRankings(MediusGetTotalRankingsRequest *MyGetTotalRankingsRequest, MediusTypeGetTotalRankingsCallback MyGetTotalRankingsCallback,void *pUserData)
{
    MyGetTotalRankingsRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[59] = MyGetTotalRankingsCallback;
    gUserArguments[59] = pUserData;
    if (MediusSendMessage(1, 0xd8, 0x1c, MyGetTotalRankingsRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetLobbyPlayerNames_ExtraInfo) MediusGetLobbyPlayerNames_ExtraInfo(MediusGetLobbyPlayerNames_ExtraInfoRequest *MyGetLobbyPlayerNamesRequest, MediusTypeGetLobbyPlayerNames_ExtraInfoCallback MyGetLobbyPlayerNames_ExtraInfoCallback, void *pUserData)
{
    MyGetLobbyPlayerNamesRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[60] = MyGetLobbyPlayerNames_ExtraInfoCallback;
    gUserArguments[60] = pUserData;
    if (MediusSendMessage(1, 0xdc, 0x1c, MyGetLobbyPlayerNamesRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetGames_ExtraInfo) MediusGetGames_ExtraInfo(MediusGameList_ExtraInfoRequest *GameList_ExtraInfoRequest, MediusTypeGameList_ExtraInfoCallback GameList_ExtraInfoCallback,void *pUserData)
{
    GameList_ExtraInfoRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[61] = GameList_ExtraInfoCallback;
    gUserArguments[61] = pUserData;
    if (MediusSendMessage(4, 0x37, 0x1a, GameList_ExtraInfoRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetChannels_ExtraInfo) MediusGetChannels_ExtraInfo(MediusChannelList_ExtraInfoRequest *MyChannelList_ExtraInfoRequest, MediusTypeChannelList_ExtraInfoCallback MyChannelList_ExtraInfoCallback,void *pUserData)
{
    MyChannelList_ExtraInfoRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[62] = MyChannelList_ExtraInfoCallback;
    gUserArguments[62] = pUserData;
    if (MediusSendMessage(4, 0x1f, 0x1a, MyChannelList_ExtraInfoRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusLadderList_ExtraInfo) MediusLadderList_ExtraInfo(MediusLadderList_ExtraInfoRequest *req, MediusTypeLadderList_ExtraInfoCallback callback, void *pUserData)
{
    req->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[63] = callback;
    gUserArguments[63] = pUserData;
    if ((unsigned int)req->LadderStatIndex > 99) {
        req->LadderStatIndex = 0;
    }
    if (MediusSendMessage(4, 15, 0x28, req) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusLadderPosition_ExtraInfo) MediusLadderPosition_ExtraInfo(MediusLadderPosition_ExtraInfoRequest *req, MediusTypeLadderPosition_ExtraInfoCallback callback, void *pUserData)
{
    req->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[64] = callback;
    gUserArguments[64] = pUserData;
    if ((unsigned int)req->LadderStatIndex > 99) {
        req->LadderStatIndex = 0;
    }
    if (MediusSendMessage(1, 0xF1, 0x24, req) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusUpdateLadderStatsWide) MediusUpdateLadderStatsWide(MediusUpdateLadderStatsWideRequest *MyUpdateLadderStatsRequest, MediusTypeUpdateLadderStatsCallback MyUpdateLadderStatsCallback,void *pUserData)
{
    MyUpdateLadderStatsRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[65] = MyUpdateLadderStatsCallback;
    gUserArguments[65] = pUserData;
    if (MediusSendMessage(4, 0xb, 0x1ac, MyUpdateLadderStatsRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED81F0);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusGetLadderStatsWide) MediusGetLadderStatsWide(MediusGetLadderStatsWideRequest *MyGetLadderStatsRequest, MediusTypeGetLadderStatsWideCallback MyGetLadderStatsCallback,void *pUserData)
{
    MyGetLadderStatsRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[66] = MyGetLadderStatsCallback;
    gUserArguments[66] = pUserData;
    if (MediusSendMessage(4, 0xd, 0x20, MyGetLadderStatsRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED8270);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusSetLobbyWorldFilter) MediusSetLobbyWorldFilter(MediusSetLobbyWorldFilterRequest *req, MediusTypeSetLobbyWorldFilterCallback callback, void *pUserData)
{
    int level;
    int type;

    req->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    GlobalLobbyFilterFlag = 0;
    gMediusFunctionPointers[68] = callback;
    level = req->FilterMaskLevel;
    type = req->LobbyFilterType;
    MyFilterMaskInfo.FilterMaskLevel = level;
    MyFilterMaskInfo.LobbyFilterType = type;
    gUserArguments[68] = pUserData;
    MyFilterMaskInfo.FilterMask1 = req->FilterMask1;
    MyFilterMaskInfo.FilterMask2 = req->FilterMask2;
    MyFilterMaskInfo.FilterMask3 = req->FilterMask3;
    MyFilterMaskInfo.FilterMask4 = req->FilterMask4;
    if (MediusSendMessage(4, 0x12, 0x30, req) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", func_01ED8330);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusClient", vLocalSetLobbyWorldFilter);

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusToken) MediusToken(MediusTokenRequest *MyTokenRequest,MediusTypeTokenCallback MyTokenCallback, void *pUserData)
{
    MyTokenRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[121] = MyTokenCallback;
    gUserArguments[121] = pUserData;
    if (MediusSendMessage(4, 0x28, 0x34, MyTokenRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_CLIENT_SECTION(MediusSetAutoChatHistory) MediusSetAutoChatHistory(MediusSetAutoChatHistoryRequest *MySetAutoChatHistoryRequest, MediusTypeSetAutoChatHistoryCallback MySetAutoChatHistoryCallback,void *pUserData)
{
    MySetAutoChatHistoryRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[123] = MySetAutoChatHistoryCallback;
    gUserArguments[123] = pUserData;
    if (MediusSendMessage(4, 0x2d, 0x1c, MySetAutoChatHistoryRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}
