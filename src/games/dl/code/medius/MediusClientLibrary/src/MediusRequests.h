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

#endif
