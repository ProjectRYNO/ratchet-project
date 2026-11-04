#ifndef MEDIUS_REQUESTS_H
#define MEDIUS_REQUESTS_H

// Medius request wrappers: the error codes, globals and request layouts they use.
// Type, member and parameter names from the retail ELF debug information; callback
// signatures are not recovered yet, so the callback types are generic.
typedef enum {
    MediusErrorNone = 0,
    MediusErrorSendingMessage = -5,
    MediusErrorNotInitialized = -15,
    MediusErrorNotConnected = -16,
    MediusErrorFeatureNotEnabled = -20,
    MediusErrorInvalidParameter = -21,
} MediusErrorCode;

// gUserArguments and gMediusFunctionPointers are indexed by the request type.
extern int GlobalInitFlag;
extern int ghMyConnection;
extern void *gUserArguments[];
extern void *gMediusFunctionPointers[];
extern int MediusSendMessage(int, int, int, void *);

typedef struct { // 0x15
    /* 0x00 */ char MessageID[21];
} MediusGetServerTimeRequest;

typedef void (*MediusTypeGetServerTimeCallback)(void);

typedef struct { // 0x50
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int DnasSignatureType;
    /* 0x2C */ char DnasSignatureLength;
    /* 0x2D */ char DnasSignature[32];
} MediusDnasSignaturePost;

typedef struct { // 0x6C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int AccountType;
    /* 0x2C */ char AccountName[32];
    /* 0x4C */ char Password[32];
} MediusAccountRegistrationRequest;

typedef void (*MediusTypeAccountRegistrationCallback)(void);

typedef struct { // 0x126
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x26 */ char Stats[256];
} MediusAccountUpdateStatsRequest;

typedef void (*MediusTypeAccountUpdateStatsCallback)(void);

typedef struct { // 0x146
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x26 */ char SessionDisplayName[32];
    /* 0x46 */ char SessionDisplayStats[256];
} MediusAnonymousLoginRequest;

typedef void (*MediusTypeAnonymousLoginCallback)(void);

typedef struct { // 0xE8
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ApplicationID;
    /* 0x2C */ int MinPlayers;
    /* 0x30 */ int MaxPlayers;
    /* 0x34 */ int GameLevel;
    /* 0x38 */ char GameName[64];
    /* 0x78 */ char GamePassword[32];
    /* 0x98 */ char SpectatorPassword[32];
    /* 0xB8 */ int PlayerSkillLevel;
    /* 0xBC */ int RulesSet;
    /* 0xC0 */ int GenericField1;
    /* 0xC4 */ int GenericField2;
    /* 0xC8 */ int GenericField3;
    /* 0xCC */ int GenericField4;
    /* 0xD0 */ int GenericField5;
    /* 0xD4 */ int GenericField6;
    /* 0xD8 */ int GenericField7;
    /* 0xDC */ int GenericField8;
    /* 0xE0 */ int GameHostType;
    /* 0xE4 */ int Attributes;
} MediusCreateGameRequest;

typedef void (*MediusTypeCreateGameCallback)(void);

typedef struct { // 0x6C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int TextFilterType;
    /* 0x2C */ char Text[64];
} MediusTextFilterRequest;

typedef void (*MediusTypeTextFilterCallback)(void);

typedef struct { // 0xA4
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ApplicationID;
    /* 0x2C */ int MaxPlayers;
    /* 0x30 */ char LobbyName[64];
    /* 0x70 */ char LobbyPassword[32];
    /* 0x90 */ unsigned char GenericField1[4];
    /* 0x94 */ unsigned char GenericField2[4];
    /* 0x98 */ unsigned char GenericField3[4];
    /* 0x9C */ unsigned char GenericField4[4];
    /* 0xA0 */ int GenericFieldLevel;
} MediusCreateChannelRequest;

typedef void (*MediusTypeCreateChannelCallback)(void);

typedef struct { // 0x4C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int MediusWorldID;
    /* 0x2C */ char LobbyChannelPassword[32];
} MediusJoinChannelRequest;

typedef void (*MediusTypeJoinChannelCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int MediusWorldID;
} MediusGameWorldPlayerListRequest;

typedef void (*MediusTypeGameWorldPlayerListCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int AccountID;
} MediusPlayerInfoRequest;

typedef void (*MediusTypePlayerInfoCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int MediusWorldID;
} MediusGameInfoRequest;

typedef void (*MediusTypeGameInfoCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int MediusWorldID;
} MediusChannelInfoRequest;

typedef void (*MediusTypeChannelInfoCallback)(void);

typedef struct { // 0x50
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int SearchType;
    /* 0x2C */ int ID;
    /* 0x30 */ char Name[32];
} MediusFindPlayerRequest;

typedef void (*MediusTypeFindPlayerCallback)(void);

typedef struct { // 0x70
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int MessageType;
    /* 0x2C */ int TargetID;
    /* 0x30 */ char Message[64];
} MediusGenericChatMessage;

typedef struct { // 0x1C0
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int MessageType;
    /* 0x2C */ int TargetAccountID;
    /* 0x30 */ char Message[400];
} MediusBinaryMessage;

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int AccountID;
} MediusAddToBuddyListRequest;

typedef void (*MediusTypeAddToBuddyListCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int AccountID;
} MediusRemoveFromBuddyListRequest;

typedef void (*MediusTypeRemoveFromBuddyListCallback)(void);

typedef struct { // 0x26
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
} MediusGetIgnoreListRequest;

typedef void (*MediusTypeGetIgnoreListCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int IgnoreAccountID;
} MediusAddToIgnoreListRequest;

typedef void (*MediusTypeAddToIgnoreListCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int IgnoreAccountID;
} MediusRemoveFromIgnoreListRequest;

typedef void (*MediusTypeRemoveFromIgnoreListCallback)(void);

typedef struct { // 0x118
    /* 0x00 */ char SessionKey[17];
    /* 0x14 */ int MediusWorldID;
    /* 0x18 */ char Stats[256];
} MediusPlayerReport;

typedef struct { // 0x180
    /* 0x00 */ int MediusWorldID;
    /* 0x04 */ int PlayerCount;
    /* 0x08 */ char GameName[64];
    /* 0x48 */ char GameStats[256];
    /* 0x148 */ int MinPlayers;
    /* 0x14C */ int MaxPlayers;
    /* 0x150 */ int GameLevel;
    /* 0x154 */ int PlayerSkillLevel;
    /* 0x158 */ int RulesSet;
    /* 0x15C */ int GenericField1;
    /* 0x160 */ int GenericField2;
    /* 0x164 */ int GenericField3;
    /* 0x168 */ int GenericField4;
    /* 0x16C */ int GenericField5;
    /* 0x170 */ int GenericField6;
    /* 0x174 */ int GenericField7;
    /* 0x178 */ int GenericField8;
    /* 0x17C */ int WorldStatus;
} MediusWorldReport;

typedef struct { // 0x7C
    /* 0x00 */ char SessionKey[17];
    /* 0x14 */ int MediusWorldID;
    /* 0x18 */ char WinningTeam[64];
    /* 0x58 */ char WinningPlayer[32];
    /* 0x78 */ int FinalScore;
} MediusEndGameReport;

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ApplicationID;
} MediusGetAnnouncementsRequest;

typedef void (*MediusTypeGetAnnouncementsCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ApplicationID;
} MediusGetAllAnnouncementsRequest;

typedef struct { // 0x28
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int FilterField;
    /* 0x1C */ int Mask;
    /* 0x20 */ int ComparisonOperator;
    /* 0x24 */ int BaselineValue;
} MediusSetGameListFilterRequest;

typedef void (*MediusTypeSetGameListFilterCallback)(void);

typedef struct { // 0x1C
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ unsigned int FilterID;
} MediusClearGameListFilterRequest;

typedef void (*MediusTypeClearGameListFilterCallback)(void);

typedef struct { // 0x26
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
} MediusGetGameListFilterRequest;

typedef void (*MediusTypeGetGameListFilterCallback)(void);

typedef struct { // 0x26
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
} MediusGetMyIPRequest;

typedef void (*MediusTypeGetMyIPCallback)(void);

typedef struct { // 0x46
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x26 */ char AccountName[32];
} MediusAccountGetIDRequest;

typedef void (*MediusTypeAccountGetIDCallback)(void);

typedef struct { // 0x26
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
} MediusGetLocationsRequest;

typedef void (*MediusTypeGetLocationsCallback)(void);

typedef struct { // 0x36
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x26 */ unsigned char GenericChatFilter[16];
} MediusGenericChatSetFilterRequest;

typedef void (*MediusTypeGenericChatSetFilterCallback)(void);

typedef struct { // 0x30
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int CharacterEncoding;
    /* 0x2C */ int Language;
} MediusSetLocalizationParamsRequest;

typedef void (*MediusTypeSetLocalizationParamsCallback)(void);

typedef struct { // 0x15
    /* 0x00 */ char MessageID[21];
} MediusGetBuddyList_ExtraInfoRequest;

typedef void (*MediusTypeGetBuddyList_ExtraInfoCallback)(void);

typedef struct { // 0x1C
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int LadderType;
} MediusGetTotalRankingsRequest;

typedef void (*MediusTypeGetTotalRankingsCallback)(void);

typedef struct { // 0x1C
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int MediusWorldID;
} MediusGetLobbyPlayerNames_ExtraInfoRequest;

typedef void (*MediusTypeGetLobbyPlayerNames_ExtraInfoCallback)(void);

typedef struct { // 0x1A
    /* 0x00 */ char MessageID[21];
    /* 0x16 */ unsigned short PageID;
    /* 0x18 */ unsigned short PageSize;
} MediusGameList_ExtraInfoRequest;

typedef void (*MediusTypeGameList_ExtraInfoCallback)(void);

typedef struct { // 0x1A
    /* 0x00 */ char MessageID[21];
    /* 0x16 */ unsigned short PageID;
    /* 0x18 */ unsigned short PageSize;
} MediusChannelList_ExtraInfoRequest;

typedef void (*MediusTypeChannelList_ExtraInfoCallback)(void);

typedef struct { // 0x1AC
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int LadderType;
    /* 0x1C */ unsigned char Stats[400];
} MediusUpdateLadderStatsWideRequest;

typedef void (*MediusTypeUpdateLadderStatsCallback)(void);

typedef struct { // 0x20
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int AccountID_or_ClanID;
    /* 0x1C */ int LadderType;
} MediusGetLadderStatsWideRequest;

typedef void (*MediusTypeGetLadderStatsWideCallback)(void);

typedef struct { // 0x34
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int TokenAction;
    /* 0x1C */ int TokenCategory;
    /* 0x20 */ unsigned int EntityID;
    /* 0x24 */ unsigned char TokenToReplace[8];
    /* 0x2C */ unsigned char Token[8];
} MediusTokenRequest;

typedef void (*MediusTypeTokenCallback)(void);

typedef struct { // 0x1C
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int AutoChatHistoryNumMessages;
} MediusSetAutoChatHistoryRequest;

typedef void (*MediusTypeSetAutoChatHistoryCallback)(void);

typedef struct { // 0x12C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanID;
    /* 0x2C */ char Stats[256];
} MediusUpdateClanStatsRequest;

typedef void (*MediusTypeUpdateClanStatsCallback)(void);

typedef struct { // 0xAC
    /* 0x00 */ unsigned char Filename[128];
    /* 0x80 */ unsigned char ServerChecksum[16];
    /* 0x90 */ unsigned int FileID;
    /* 0x94 */ unsigned int FileSize;
    /* 0x98 */ unsigned int CreationTimeStamp;
    /* 0x9C */ unsigned int OwnerID;
    /* 0xA0 */ unsigned int GroupID;
    /* 0xA4 */ unsigned short OwnerPermissionRWX;
    /* 0xA6 */ unsigned short GroupPermissionRWX;
    /* 0xA8 */ unsigned short GlobalPermissionRWX;
    /* 0xAA */ unsigned short ServerOperationID;
} MediusFile;

typedef struct { // 0x114
    /* 0x00 */ unsigned char Description[256];
    /* 0x100 */ unsigned int LastChangedTimeStamp;
    /* 0x104 */ unsigned int LastChangedByUserID;
    /* 0x108 */ unsigned int NumberAccesses;
    /* 0x10C */ unsigned int StreamableFlag;
    /* 0x110 */ unsigned int StreamingDataRate;
} MediusFileAttributes;

typedef struct { // 0x1D8
    /* 0x00 */ MediusFile MediusFileToCreate;
    /* 0xAC */ MediusFileAttributes MediusFileCreateAttributes;
    /* 0x1C0 */ char MessageID[21];
} MediusFileCreateRequest;

typedef void (*MediusFileTypeCreateCallback)(void);

typedef struct { // 0xC4
    /* 0x00 */ MediusFile MediusFileInfo;
    /* 0xAC */ char MessageID[21];
} MediusFileCloseRequest;

typedef void (*MediusFileTypeCloseCallback)(void);

typedef struct { // 0xC4
    /* 0x00 */ MediusFile MediusFileInfo;
    /* 0xAC */ char MessageID[21];
} MediusFileDownloadRequest;

typedef void (*MediusFileTypeDownloadCallback)(void);

typedef struct { // 0xC4
    /* 0x00 */ MediusFile MediusFileInfo;
    /* 0xAC */ char MessageID[21];
} MediusFileDeleteRequest;

typedef void (*MediusFileTypeDeleteCallback)(void);

typedef enum {
    ClanChallengeRequest = 0,
    ClanChallengeAccepted = 1,
    ClanChallengeRevoked = 2,
    ClanChallengeRefused = 3,
    ClanChallengeConfirmed = 4,
    ExtraMediusClanChallengeStatus = 0xFFFFFF,
} MediusClanChallengeStatus;

typedef enum {
    ClanInvitationUndecided = 0,
    ClanInvitationAccept = 1,
    ClanInvitationDecline = 2,
    ClanInvitationRevoked = 3,
    ExtraMediusClanInvitationsResponseStatus = 0xFFFFFF,
} MediusClanInvitationsResponseStatus;

typedef struct { // 0x4C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ApplicationID;
    /* 0x2C */ char ClanName[32];
} MediusCreateClanRequest;

typedef void (*MediusTypeCreateClanCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanID;
} MediusDisbandClanRequest;

typedef void (*MediusTypeDisbandClanCallback)(void);

typedef struct { // 0x30
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int AccountID;
    /* 0x2C */ int ClanID;
} MediusGetClanByIDRequest;

typedef void (*MediusTypeGetClanByIDCallback)(void);

typedef struct { // 0x4C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ApplicationID;
    /* 0x2C */ char ClanName[32];
} MediusGetClanByNameRequest;

typedef void (*MediusTypeGetClanByNameCallback)(void);

typedef struct { // 0x4C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int NewLeaderAccountID;
    /* 0x2C */ char NewLeaderAccountName[32];
} MediusTransferClanLeadershipRequest;

typedef void (*MediusTypeTransferClanLeadershipCallback)(void);

typedef struct { // 0x30
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int PlayerAccountID;
    /* 0x2C */ int ClanID;
} MediusRemovePlayerFromClanRequest;

typedef void (*MediusTypeRemovePlayerFromClanCallback)(void);

typedef struct { // 0xF4
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int PlayerAccountID;
    /* 0x2C */ char InviteMessage[200];
} MediusInvitePlayerToClanRequest;

typedef void (*MediusTypeInvitePlayerToClanCallback)(void);

typedef struct { // 0x30
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int Start;
    /* 0x2C */ int PageSize;
} MediusCheckMyClanInvitationsRequest;

typedef void (*MediusTypeCheckMyClanInvitationsCallback)(void);

typedef struct { // 0x30
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int Start;
    /* 0x2C */ int PageSize;
} MediusGetClanInvitationsSentRequest;

typedef void (*MediusTypeGetClanInvitationsSentCallback)(void);

typedef struct { // 0xF8
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanInvitationID;
    /* 0x2C */ MediusClanInvitationsResponseStatus Response;
    /* 0x30 */ char Message[200];
} MediusRespondToClanInvitationRequest;

typedef void (*MediusTypeRespondToClanInvitationCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int PlayerAccountID;
} MediusRevokeClanInvitationRequest;

typedef void (*MediusTypeRevokeClanInvitationCallback)(void);

typedef struct { // 0x34
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanID;
    /* 0x2C */ int Start;
    /* 0x30 */ int PageSize;
} MediusGetMyClanMessagesRequest;

typedef void (*MediusTypeGetMyClanMessagesCallback)(void);

typedef struct { // 0xEE
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x26 */ char Message[200];
} MediusSendClanMessageRequest;

typedef void (*MediusTypeSendClanMessageCallback)(void);

typedef struct { // 0xF4
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanMessageID;
    /* 0x2C */ char NewMessage[200];
} MediusModifyClanMessageRequest;

typedef void (*MediusTypeModifyClanMessageCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanMessageID;
} MediusDeleteClanMessageRequest;

typedef void (*MediusTypeDeleteClanMessageCallback)(void);

typedef struct { // 0xF4
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanID;
    /* 0x2C */ char Message[200];
} MediusRequestClanTeamChallengeRequest;

typedef void (*MediusTypeRequestClanTeamChallengeCallback)(void);

typedef struct { // 0xF8
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanChallengeID;
    /* 0x2C */ MediusClanChallengeStatus ChallengeStatus;
    /* 0x30 */ char Message[200];
} MediusRespondToClanTeamChallengeRequest;

typedef void (*MediusTypeRespondToClanTeamChallengeCallback)(void);

typedef struct { // 0x2C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanChallengeID;
} MediusRevokeClanTeamChallengeRequest;

typedef void (*MediusTypeRevokeClanTeamChallengeCallback)(void);

typedef struct { // 0x3C
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanID;
    /* 0x2C */ int Start;
    /* 0x30 */ int PageSize;
    /* 0x34 */ MediusClanChallengeStatus Status;
    /* 0x38 */ int ChallengedOnly;
} MediusGetClanTeamChallengesRequest;

typedef void (*MediusTypeGetClanTeamChallengesCallback)(void);

typedef struct { // 0x30
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int Start;
    /* 0x2C */ int PageSize;
} MediusGetMyClansRequest;

typedef void (*MediusTypeGetMyClansCallback)(void);

typedef struct { // 0x30
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int Start;
    /* 0x2C */ int PageSize;
} MediusGetAllClanMessagesRequest;

typedef void (*MediusTypeGetAllClanMessagesCallback)(void);

typedef struct { // 0x38
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x28 */ int ClanID;
    /* 0x2C */ int ThisClanIsChallenger;
    /* 0x30 */ int Start;
    /* 0x34 */ int PageSize;
} MediusGetClanTeamChallengeHistoryRequest;

typedef void (*MediusTypeGetClanTeamChallengeHistoryCallback)(void);

typedef enum {
    MEDIUS_ASCENDING = 0,
    MEDIUS_DESCENDING = 1,
    ExtraMediusSortOrder = 0xFFFFFF,
} MediusSortOrder;

typedef struct { // 0x28
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int ClanLadderStatIndex;
    /* 0x1C */ MediusSortOrder SortOrder;
    /* 0x20 */ unsigned int StartPosition;
    /* 0x24 */ unsigned int PageSize;
} MediusClanLadderListRequest;

typedef void (*MediusTypeClanLadderListCallback)(void);

typedef struct { // 0x24
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int ClanID;
    /* 0x1C */ int ClanLadderStatIndex;
    /* 0x20 */ MediusSortOrder SortOrder;
} MediusClanLadderPositionRequest;

typedef void (*MediusTypeClanLadderPositionCallback)(void);

typedef struct { // 0x24
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int ClanID;
    /* 0x1C */ int LadderStatIndex;
    /* 0x20 */ MediusSortOrder SortOrder;
} MediusGetClanMemberList_ExtraInfoRequest;

typedef void (*MediusTypeGetClanMemberList_ExtraInfoCallback)(void);

typedef struct { // 0x28
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int LadderStatIndex;
    /* 0x1C */ int SortOrder;
    /* 0x20 */ unsigned int StartPosition;
    /* 0x24 */ unsigned int PageSize;
} MediusLadderList_ExtraInfoRequest;

typedef void (*MediusTypeLadderList_ExtraInfoCallback)(void);

typedef struct { // 0x24
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ int AccountID;
    /* 0x1C */ int LadderStatIndex;
    /* 0x20 */ int SortOrder;
} MediusLadderPosition_ExtraInfoRequest;

typedef void (*MediusTypeLadderPosition_ExtraInfoCallback)(void);

typedef struct { // 0x26
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
} MediusSessionEndRequest;

typedef void (*MediusTypeSessionEndCallback)(void);

typedef struct { // 0x18
    /* 0x00 */ char SessionKey[17];
    /* 0x14 */ int UserAction;
} MediusUpdateUserState;

typedef struct { // 0x30
    /* 0x00 */ char MessageID[21];
    /* 0x18 */ unsigned int FilterMask1;
    /* 0x1C */ unsigned int FilterMask2;
    /* 0x20 */ unsigned int FilterMask3;
    /* 0x24 */ unsigned int FilterMask4;
    /* 0x28 */ int LobbyFilterType;
    /* 0x2C */ int FilterMaskLevel;
} MediusSetLobbyWorldFilterRequest;

typedef void (*MediusTypeSetLobbyWorldFilterCallback)(void);

typedef struct { // 0x18
    /* 0x00 */ unsigned int FilterMask1;
    /* 0x04 */ unsigned int FilterMask2;
    /* 0x08 */ unsigned int FilterMask3;
    /* 0x0C */ unsigned int FilterMask4;
    /* 0x10 */ int FilterMaskLevel;
    /* 0x14 */ int LobbyFilterType;
} MediusFilterMaskInfo;

typedef struct { // 0x46
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
    /* 0x26 */ char MasterPassword[32];
} MediusAccountDeleteRequest;

typedef void (*MediusTypeAccountDeleteCallback)(void);

typedef struct { // 0x26
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char SessionKey[17];
} MediusAccountLogoutRequest;


typedef struct { // 0xB0
    /* 0x00 */ unsigned char FilenameBeginsWith[128];
    /* 0x80 */ unsigned int FilesizeGreaterThan;
    /* 0x84 */ unsigned int FilesizeLessThan;
    /* 0x88 */ unsigned int OwnedByID;
    /* 0x8C */ unsigned int NewerThanTimestamp;
    /* 0x90 */ unsigned int StartingEntryNumber;
    /* 0x94 */ unsigned int PageSize;
    /* 0x98 */ char MessageID[21];
} MediusFileListRequest;

typedef void (*MediusFileTypeListCallback)(void);

#endif
