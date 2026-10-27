#include "common.h"
#include "MediusRequests.h"

#define MEDIUS_CALLBACK_SECTION(name) __attribute__((section(".medius_callback_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_callback_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef enum { MediusFail = -966, MediusSuccess = 0 } MediusCallbackStatus;

typedef void (*MediusCallback)(void *ThisPacket, void *UserArgument);

typedef struct {
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char pad15[3];
    /* 0x18 */ int StatusCode;
} MediusStatusResponse;

typedef struct {
    /* 0x00 */ char MessageID[21];
    /* 0x15 */ char pad15[3];
    /* 0x18 */ int StatusCode;
    /* 0x1C */ char SessionKey[17];
} MediusSessionBeginResponse;

typedef struct {
    /* 0x000 */ char MessageID[21];
    /* 0x015 */ char Text[262];
    /* 0x11B */ char pad11B;
    /* 0x11C */ char EndOfText;
} MediusUniverseNewsResponse;

typedef MediusUniverseNewsResponse MediusGetPolicyResponse;

typedef struct {
    /* 0x00 */ int iReqStartByteIndex;
    /* 0x04 */ int iPacketNumber;
    /* 0x08 */ int iXferStatus;
    /* 0x0C */ MediusCallbackStatus StatusCode;
    /* 0x10 */ char MessageID[21];
} MediusFileUploadServerReq;

typedef struct {
    /* 0x000 */ unsigned char Data[464];
    /* 0x1D0 */ int iStartByteIndex;
    /* 0x1D4 */ int iDataSize;
    /* 0x1D8 */ int iPacketNumber;
    /* 0x1DC */ int iXferStatus;
    /* 0x1E0 */ MediusCallbackStatus StatusCode;
    /* 0x1E4 */ char MessageID[21];
} MediusFileUploadResponse;

typedef struct {
    /* 0x00 */ char *begin;
    /* 0x04 */ char *end;
    /* 0x08 */ char *cursor;
    /* 0x0C */ int pad0C;
    /* 0x10 */ int lastError;
} RT_PACK_BUFFER;

typedef struct {
    /* 0x00 */ int pad00[4];
    /* 0x10 */ int Enabled;
    /* 0x14 */ int pad14;
    /* 0x18 */ int Suppress;
} FilterMaskInfo;

extern char CurrentSessionKey[];
extern unsigned int G_MCL_uiCurInfoType;
// Cleared when the server answers PostDebugInfo with status -950.
extern int mediusPostDebugInfoFlag;
extern short GlobalLobbyFilterFlag;
extern FilterMaskInfo MyFilterMaskInfo;
extern char G_MCL_UsagePolicyMessageID[];
extern char G_MCL_PrivacyPolicyMessageID[];
extern int GlobalInitFlag;
extern char *G_MFS_pClientUploadData;
// Size of the file being uploaded (the word after G_MFS_pClientUploadData).
extern int mediusFileUploadDataSize;
// MessageID (21 bytes) followed by the SVO URL from the last UniverseSvoURL response.
extern char mediusUniverseSvoURL[];
void MediusSetNatServiceAddress(void *addr);
int MediusSendMessage(int a, int b, int c, void *d);
char *strncpy(char *, const char *, unsigned int);
int strncmp(const char *, const char *, unsigned int);
void *memcpy(void *, const void *, unsigned int);
void *memset(void *, int, unsigned int);
void rt_init_pack_buffer(RT_PACK_BUFFER *b, void *begin, void *end);
void rt_pack_anything(int mode, RT_PACK_BUFFER *b, void *p, int n);
void rt_pack_cstring(int mode, RT_PACK_BUFFER *b, char *p);

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackErrorMessageHandler) MediusUniqueCallbackErrorMessageHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[0]) {
        ((MediusCallback)gMediusFunctionPointers[0])(ThisPacket, gUserArguments[0]);
    }
    return 0x104;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackSessionBeginResponseHandler) MediusUniqueCallbackSessionBeginResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, MediusSessionBeginResponse *ThisPacket)
{
    if (ThisPacket->StatusCode == 0) {
        strncpy(CurrentSessionKey, ThisPacket->SessionKey, 0x11);
    }
    if (gMediusFunctionPointers[1]) {
        ((MediusCallback)gMediusFunctionPointers[1])(ThisPacket, gUserArguments[1]);
    }
    return 0x30;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackSessionEndResponseHandler) MediusUniqueCallbackSessionEndResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, MediusStatusResponse *ThisPacket)
{
    if (ThisPacket->StatusCode == 0) {
        CurrentSessionKey[0] = 0;
    }
    if (gMediusFunctionPointers[2]) {
        ((MediusCallback)gMediusFunctionPointers[2])(ThisPacket, gUserArguments[2]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackDnasSignaturePostHandler) MediusUniqueCallbackDnasSignaturePostHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x50;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAccountLoginResponseHandler) MediusUniqueCallbackAccountLoginResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, MediusStatusResponse *ThisPacket)
{
    if (ThisPacket->StatusCode == 0) {
        MediusSetNatServiceAddress((char *)ThisPacket + 0x44);
    }
    if (gMediusFunctionPointers[4]) {
        ((MediusCallback)gMediusFunctionPointers[4])(ThisPacket, gUserArguments[4]);
    }
    return 0xC4;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edbc68) FUN_01edbc68(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[5]) {
        ((MediusCallback)gMediusFunctionPointers[5])(ThisPacket, gUserArguments[5]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edbca0) FUN_01edbca0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[6]) {
        ((MediusCallback)gMediusFunctionPointers[6])(ThisPacket, gUserArguments[6]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAccountGetProfileResponseHandler) MediusUniqueCallbackAccountGetProfileResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[10]) {
        ((MediusCallback)gMediusFunctionPointers[10])(ThisPacket, gUserArguments[10]);
    }
    return 0x1CC;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edbd10) FUN_01edbd10(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[7]) {
        ((MediusCallback)gMediusFunctionPointers[7])(ThisPacket, gUserArguments[7]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edbd48) FUN_01edbd48(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[8]) {
        ((MediusCallback)gMediusFunctionPointers[8])(ThisPacket, gUserArguments[8]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edbd80) FUN_01edbd80(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[9]) {
        ((MediusCallback)gMediusFunctionPointers[9])(ThisPacket, gUserArguments[9]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAnonymousLoginResponseHandler) MediusUniqueCallbackAnonymousLoginResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[12]) {
        ((MediusCallback)gMediusFunctionPointers[12])(ThisPacket, gUserArguments[12]);
    }
    return 0xC4;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edbdf0) FUN_01edbdf0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[15]) {
        ((MediusCallback)gMediusFunctionPointers[15])(ThisPacket, gUserArguments[15]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edbe28) FUN_01edbe28(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[16]) {
        ((MediusCallback)gMediusFunctionPointers[16])(ThisPacket, gUserArguments[16]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackJoinGameResponseHandler) MediusUniqueCallbackJoinGameResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[17]) {
        ((MediusCallback)gMediusFunctionPointers[17])(ThisPacket, gUserArguments[17]);
    }
    return 0xBC;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackJoinChannelResponseHandler) MediusUniqueCallbackJoinChannelResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[18]) {
        ((MediusCallback)gMediusFunctionPointers[18])(ThisPacket, gUserArguments[18]);
    }
    return 0xB8;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackJoinChannelFwdResponseHandler) MediusUniqueCallbackJoinChannelFwdResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x3C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGameListResponseHandler) MediusUniqueCallbackGameListResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[19]) {
        ((MediusCallback)gMediusFunctionPointers[19])(ThisPacket, gUserArguments[19]);
    }
    return 0x70;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackChannelListResponseHandler) MediusUniqueCallbackChannelListResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[20]) {
        ((MediusCallback)gMediusFunctionPointers[20])(ThisPacket, gUserArguments[20]);
    }
    return 0x68;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackLobbyWorldPlayerListResponseHandler) MediusUniqueCallbackLobbyWorldPlayerListResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[13]) {
        ((MediusCallback)gMediusFunctionPointers[13])(ThisPacket, gUserArguments[13]);
    }
    return 0x14C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGameWorldPlayerListResponseHandler) MediusUniqueCallbackGameWorldPlayerListResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[14]) {
        ((MediusCallback)gMediusFunctionPointers[14])(ThisPacket, gUserArguments[14]);
    }
    return 0x148;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackPlayerInfoResponseHandler) MediusUniqueCallbackPlayerInfoResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[21]) {
        ((MediusCallback)gMediusFunctionPointers[21])(ThisPacket, gUserArguments[21]);
    }
    return 0x148;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGameInfoResponseHandler) MediusUniqueCallbackGameInfoResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[22]) {
        ((MediusCallback)gMediusFunctionPointers[22])(ThisPacket, gUserArguments[22]);
    }
    return 0x1A0;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackChannelInfoResponseHandler) MediusUniqueCallbackChannelInfoResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[23]) {
        ((MediusCallback)gMediusFunctionPointers[23])(ThisPacket, gUserArguments[23]);
    }
    return 0x64;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFindWorldByNameResponseHandler) MediusUniqueCallbackFindWorldByNameResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[24]) {
        ((MediusCallback)gMediusFunctionPointers[24])(ThisPacket, gUserArguments[24]);
    }
    return 0x90;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFindPlayerResponseHandler) MediusUniqueCallbackFindPlayerResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[25]) {
        ((MediusCallback)gMediusFunctionPointers[25])(ThisPacket, gUserArguments[25]);
    }
    return 0x70;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGenericChatMessageHandler) MediusUniqueCallbackGenericChatMessageHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x70;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGenericChatFwdMessageHandler) MediusUniqueCallbackGenericChatFwdMessageHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[26]) {
        ((MediusCallback)gMediusFunctionPointers[26])(ThisPacket, gUserArguments[26]);
    }
    return 0x6C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackBinaryMessageHandler) MediusUniqueCallbackBinaryMessageHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x1C0;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackBinaryFwdMessageHandler) MediusUniqueCallbackBinaryFwdMessageHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[69]) {
        ((MediusCallback)gMediusFunctionPointers[69])(ThisPacket, gUserArguments[69]);
    }
    return 0x1B0;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetBuddyListResponseHandler) MediusUniqueCallbackGetBuddyListResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[27]) {
        ((MediusCallback)gMediusFunctionPointers[27])(ThisPacket, gUserArguments[27]);
    }
    return 0x48;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAddToBuddyListResponseHandler) MediusUniqueCallbackAddToBuddyListResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[28]) {
        ((MediusCallback)gMediusFunctionPointers[28])(ThisPacket, gUserArguments[28]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackRemoveFromBuddyListResponseHandler) MediusUniqueCallbackRemoveFromBuddyListResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[29]) {
        ((MediusCallback)gMediusFunctionPointers[29])(ThisPacket, gUserArguments[29]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAddToBuddyListConfirmationResponseHandler) MediusUniqueCallbackAddToBuddyListConfirmationResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[31]) {
        ((MediusCallback)gMediusFunctionPointers[31])(ThisPacket, gUserArguments[31]);
    }
    return 0x40;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAddToBuddyListFwdConfirmationRequestHandler) MediusUniqueCallbackAddToBuddyListFwdConfirmationRequestHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[30]) {
        ((MediusCallback)gMediusFunctionPointers[30])(ThisPacket, gUserArguments[30]);
    }
    return 0x40;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAddToBuddyListFwdConfirmationResponseHandler) MediusUniqueCallbackAddToBuddyListFwdConfirmationResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x38;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetIgnoreListResponseHandler) MediusUniqueCallbackGetIgnoreListResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[32]) {
        ((MediusCallback)gMediusFunctionPointers[32])(ThisPacket, gUserArguments[32]);
    }
    return 0x48;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAddToIgnoreListResponseHandler) MediusUniqueCallbackAddToIgnoreListResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[33]) {
        ((MediusCallback)gMediusFunctionPointers[33])(ThisPacket, gUserArguments[33]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackRemoveFromIgnoreListResponseHandler) MediusUniqueCallbackRemoveFromIgnoreListResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[34]) {
        ((MediusCallback)gMediusFunctionPointers[34])(ThisPacket, gUserArguments[34]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetPolicyResponseHandler) MediusUniqueCallbackGetPolicyResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, MediusGetPolicyResponse *ThisPacket)
{
    if (strncmp(ThisPacket->MessageID, G_MCL_UsagePolicyMessageID, 0x15) == 0) {
        if (ThisPacket->EndOfText) {
            G_MCL_UsagePolicyMessageID[0] = 0;
        }
        if (gMediusFunctionPointers[0x23]) {
            ((MediusCallback)gMediusFunctionPointers[0x23])(ThisPacket, gUserArguments[0x23]);
        }
    } else if (strncmp(ThisPacket->MessageID, G_MCL_PrivacyPolicyMessageID, 0x15) == 0) {
        if (ThisPacket->EndOfText) {
            G_MCL_PrivacyPolicyMessageID[0] = 0;
        }
        if (gMediusFunctionPointers[0x24]) {
            ((MediusCallback)gMediusFunctionPointers[0x24])(ThisPacket, gUserArguments[0x24]);
        }
    }
    return 0x120;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackUpdateUserStateHandler) MediusUniqueCallbackUpdateUserStateHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x18;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetAnnouncementsResponseHandler) MediusUniqueCallbackGetAnnouncementsResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[37]) {
        ((MediusCallback)gMediusFunctionPointers[37])(ThisPacket, gUserArguments[37]);
    }
    return 0x40C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackSetGameListFilterResponseHandler0) MediusUniqueCallbackSetGameListFilterResponseHandler0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackSetGameListFilterResponseHandler) MediusUniqueCallbackSetGameListFilterResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[38]) {
        ((MediusCallback)gMediusFunctionPointers[38])(ThisPacket, gUserArguments[38]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackClearGameListFilterResponseHandler) MediusUniqueCallbackClearGameListFilterResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[39]) {
        ((MediusCallback)gMediusFunctionPointers[39])(ThisPacket, gUserArguments[39]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetGameListFilterResponseHandler0) MediusUniqueCallbackGetGameListFilterResponseHandler0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x2C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetGameListFilterResponseHandler) MediusUniqueCallbackGetGameListFilterResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[40]) {
        ((MediusCallback)gMediusFunctionPointers[40])(ThisPacket, gUserArguments[40]);
    }
    return 0x34;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc4d8) FUN_01edc4d8(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[72]) {
        ((MediusCallback)gMediusFunctionPointers[72])(ThisPacket, gUserArguments[72]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAccountUpdateStatsResponseHandler) MediusUniqueCallbackAccountUpdateStatsResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[73]) {
        ((MediusCallback)gMediusFunctionPointers[73])(ThisPacket, gUserArguments[73]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetClanByIDResponseHandler) MediusUniqueCallbackGetClanByIDResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[74]) {
        ((MediusCallback)gMediusFunctionPointers[74])(ThisPacket, gUserArguments[74]);
    }
    return 0x168;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc580) FUN_01edc580(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[75]) {
        ((MediusCallback)gMediusFunctionPointers[75])(ThisPacket, gUserArguments[75]);
    }
    return 0x148;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc5b8) FUN_01edc5b8(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[76]) {
        ((MediusCallback)gMediusFunctionPointers[76])(ThisPacket, gUserArguments[76]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc5f0) FUN_01edc5f0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[77]) {
        ((MediusCallback)gMediusFunctionPointers[77])(ThisPacket, gUserArguments[77]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc628) FUN_01edc628(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[78]) {
        ((MediusCallback)gMediusFunctionPointers[78])(ThisPacket, gUserArguments[78]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc660) FUN_01edc660(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[79]) {
        ((MediusCallback)gMediusFunctionPointers[79])(ThisPacket, gUserArguments[79]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackCheckMyClanInvitationsResponseHandler) MediusUniqueCallbackCheckMyClanInvitationsResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[80]) {
        ((MediusCallback)gMediusFunctionPointers[80])(ThisPacket, gUserArguments[80]);
    }
    return 0x118;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetClanInvitationsSentResponseHandler) MediusUniqueCallbackGetClanInvitationsSentResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[81]) {
        ((MediusCallback)gMediusFunctionPointers[81])(ThisPacket, gUserArguments[81]);
    }
    return 0x114;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc708) FUN_01edc708(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[82]) {
        ((MediusCallback)gMediusFunctionPointers[82])(ThisPacket, gUserArguments[82]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc740) FUN_01edc740(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[83]) {
        ((MediusCallback)gMediusFunctionPointers[83])(ThisPacket, gUserArguments[83]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc778) FUN_01edc778(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[84]) {
        ((MediusCallback)gMediusFunctionPointers[84])(ThisPacket, gUserArguments[84]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetMyClanMessagesResponseHandler) MediusUniqueCallbackGetMyClanMessagesResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[85]) {
        ((MediusCallback)gMediusFunctionPointers[85])(ThisPacket, gUserArguments[85]);
    }
    return 0xEC;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc7e8) FUN_01edc7e8(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[86]) {
        ((MediusCallback)gMediusFunctionPointers[86])(ThisPacket, gUserArguments[86]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc820) FUN_01edc820(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[87]) {
        ((MediusCallback)gMediusFunctionPointers[87])(ThisPacket, gUserArguments[87]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc858) FUN_01edc858(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[88]) {
        ((MediusCallback)gMediusFunctionPointers[88])(ThisPacket, gUserArguments[88]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc890) FUN_01edc890(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[89]) {
        ((MediusCallback)gMediusFunctionPointers[89])(ThisPacket, gUserArguments[89]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc8c8) FUN_01edc8c8(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[90]) {
        ((MediusCallback)gMediusFunctionPointers[90])(ThisPacket, gUserArguments[90]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetMyClansResponseHandler) MediusUniqueCallbackGetMyClansResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[94]) {
        ((MediusCallback)gMediusFunctionPointers[94])(ThisPacket, gUserArguments[94]);
    }
    return 0x170;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetClanTeamChallengesResponseHandler) MediusUniqueCallbackGetClanTeamChallengesResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[95]) {
        ((MediusCallback)gMediusFunctionPointers[95])(ThisPacket, gUserArguments[95]);
    }
    return 0x1C4;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc970) FUN_01edc970(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[91]) {
        ((MediusCallback)gMediusFunctionPointers[91])(ThisPacket, gUserArguments[91]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetAllClanMessagesResponseHandler) MediusUniqueCallbackGetAllClanMessagesResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[92]) {
        ((MediusCallback)gMediusFunctionPointers[92])(ThisPacket, gUserArguments[92]);
    }
    return 0xF0;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edc9e0) FUN_01edc9e0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[93]) {
        ((MediusCallback)gMediusFunctionPointers[93])(ThisPacket, gUserArguments[93]);
    }
    return 0x28;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edca18) FUN_01edca18(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[96]) {
        ((MediusCallback)gMediusFunctionPointers[96])(ThisPacket, gUserArguments[96]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetMyIPResponseHandler) MediusUniqueCallbackGetMyIPResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[42]) {
        ((MediusCallback)gMediusFunctionPointers[42])(ThisPacket, gUserArguments[42]);
    }
    return 0x30;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackVersionServerResponseHandler) MediusUniqueCallbackVersionServerResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[41]) {
        ((MediusCallback)gMediusFunctionPointers[41])(ThisPacket, gUserArguments[41]);
    }
    return 0x4D;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcac0) FUN_01edcac0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[43]) {
        ((MediusCallback)gMediusFunctionPointers[43])(ThisPacket, gUserArguments[43]);
    }
    return 0x28;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcaf8) FUN_01edcaf8(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[44]) {
        ((MediusCallback)gMediusFunctionPointers[44])(ThisPacket, gUserArguments[44]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcb30) FUN_01edcb30(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[11]) {
        ((MediusCallback)gMediusFunctionPointers[11])(ThisPacket, gUserArguments[11]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcb68) FUN_01edcb68(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[3]) {
        ((MediusCallback)gMediusFunctionPointers[3])(ThisPacket, gUserArguments[3]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcba0) FUN_01edcba0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[45]) {
        ((MediusCallback)gMediusFunctionPointers[45])(ThisPacket, gUserArguments[45]);
    }
    return 0x64;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcbd8) FUN_01edcbd8(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[46]) {
        ((MediusCallback)gMediusFunctionPointers[46])(ThisPacket, gUserArguments[46]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcc10) FUN_01edcc10(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[97]) {
        ((MediusCallback)gMediusFunctionPointers[97])(ThisPacket, gUserArguments[97]);
    }
    return 0x44;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcc48) FUN_01edcc48(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[47]) {
        ((MediusCallback)gMediusFunctionPointers[47])(ThisPacket, gUserArguments[47]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGenericChatSetFilterResponseHandler) MediusUniqueCallbackGenericChatSetFilterResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[71]) {
        ((MediusCallback)gMediusFunctionPointers[71])(ThisPacket, gUserArguments[71]);
    }
    return 0x2C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackTextFilterResponseHandler) MediusUniqueCallbackTextFilterResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[48]) {
        ((MediusCallback)gMediusFunctionPointers[48])(ThisPacket, gUserArguments[48]);
    }
    return 0x5C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackReassignGameMediusWorldIDHandler) MediusUniqueCallbackReassignGameMediusWorldIDHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[49]) {
        ((MediusCallback)gMediusFunctionPointers[49])(ThisPacket, gUserArguments[49]);
    }
    return 0x8;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcd28) FUN_01edcd28(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[50]) {
        ((MediusCallback)gMediusFunctionPointers[50])(ThisPacket, gUserArguments[50]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcd60) FUN_01edcd60(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[51]) {
        ((MediusCallback)gMediusFunctionPointers[51])(ThisPacket, gUserArguments[51]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcd98) FUN_01edcd98(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[52]) {
        ((MediusCallback)gMediusFunctionPointers[52])(ThisPacket, gUserArguments[52]);
    }
    return 0x44;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcdd0) FUN_01edcdd0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[53]) {
        ((MediusCallback)gMediusFunctionPointers[53])(ThisPacket, gUserArguments[53]);
    }
    return 0x24;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edce08) FUN_01edce08(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[54]) {
        ((MediusCallback)gMediusFunctionPointers[54])(ThisPacket, gUserArguments[54]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edce40) FUN_01edce40(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[55]) {
        ((MediusCallback)gMediusFunctionPointers[55])(ThisPacket, gUserArguments[55]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edce78) FUN_01edce78(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[98]) {
        ((MediusCallback)gMediusFunctionPointers[98])(ThisPacket, gUserArguments[98]);
    }
    return 0x48;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edceb0) FUN_01edceb0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[99]) {
        ((MediusCallback)gMediusFunctionPointers[99])(ThisPacket, gUserArguments[99]);
    }
    return 0x24;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcee8) FUN_01edcee8(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[58]) {
        ((MediusCallback)gMediusFunctionPointers[58])(ThisPacket, gUserArguments[58]);
    }
    return 0xD0;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcf20) FUN_01edcf20(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[59]) {
        ((MediusCallback)gMediusFunctionPointers[59])(ThisPacket, gUserArguments[59]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcf58) FUN_01edcf58(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[60]) {
        ((MediusCallback)gMediusFunctionPointers[60])(ThisPacket, gUserArguments[60]);
    }
    return 0xD0;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edcf90) FUN_01edcf90(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[100]) {
        ((MediusCallback)gMediusFunctionPointers[100])(ThisPacket, gUserArguments[100]);
    }
    return 0x1DC;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGameList_ExtraInfoResponseHandler) MediusUniqueCallbackGameList_ExtraInfoResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[61]) {
        ((MediusCallback)gMediusFunctionPointers[61])(ThisPacket, gUserArguments[61]);
    }
    return 0x1A4;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackChannelList_ExtraInfoResponseHandler) MediusUniqueCallbackChannelList_ExtraInfoResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[62]) {
        ((MediusCallback)gMediusFunctionPointers[62])(ThisPacket, gUserArguments[62]);
    }
    return 0x84;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackLadderList_ExtraInfoResponseHandler) MediusUniqueCallbackLadderList_ExtraInfoResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[63]) {
        ((MediusCallback)gMediusFunctionPointers[63])(ThisPacket, gUserArguments[63]);
    }
    return 0x1D8;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edd070) FUN_01edd070(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[65]) {
        ((MediusCallback)gMediusFunctionPointers[65])(ThisPacket, gUserArguments[65]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edd0a8) FUN_01edd0a8(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[65]) {
        ((MediusCallback)gMediusFunctionPointers[65])(ThisPacket, gUserArguments[65]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edd0e0) FUN_01edd0e0(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[66]) {
        ((MediusCallback)gMediusFunctionPointers[66])(ThisPacket, gUserArguments[66]);
    }
    return 0x1B0;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edd118) FUN_01edd118(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[64]) {
        ((MediusCallback)gMediusFunctionPointers[64])(ThisPacket, gUserArguments[64]);
    }
    return 0x24;
}

int MEDIUS_CALLBACK_SECTION(FUN_01edd150) FUN_01edd150(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[101]) {
        ((MediusCallback)gMediusFunctionPointers[101])(ThisPacket, gUserArguments[101]);
    }
    return 0xC8;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileUploadFromClientResponseHandler) MediusUniqueCallbackFileUploadFromClientResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x1FC;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileUploadResponseHandler) MediusUniqueCallbackFileUploadResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, MediusFileUploadServerReq *ThisPacket)
{
    MediusFileUploadResponse resp;
    int n;
    resp.iStartByteIndex = ThisPacket->iReqStartByteIndex;
    resp.iPacketNumber = ThisPacket->iPacketNumber;
    resp.iXferStatus = ThisPacket->iXferStatus;
    resp.StatusCode = ThisPacket->StatusCode;
    resp.iDataSize = 0;
    memcpy(resp.MessageID, ThisPacket->MessageID, 0x15);
    if (resp.iXferStatus != 0) {
        n = mediusFileUploadDataSize - resp.iStartByteIndex;
        if (n > 0x1D0) {
            n = 0x1D0;
        }
        resp.iDataSize = n;
        memcpy(resp.Data, G_MFS_pClientUploadData + resp.iStartByteIndex, n);
    }
    if (GlobalInitFlag != 1) {
        resp.StatusCode = MediusFail;
    }
    if (gMediusFunctionPointers[0x66]) {
        ((MediusCallback)gMediusFunctionPointers[0x66])(&resp, gUserArguments[0x66]);
    }
    MediusSendMessage(1, 0xA8, 0x1FC, &resp);
    return 0x28;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileCloseResponseHandler) MediusUniqueCallbackFileCloseResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[103]) {
        ((MediusCallback)gMediusFunctionPointers[103])(ThisPacket, gUserArguments[103]);
    }
    return 0xC8;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileDownloadResponseHandler) MediusUniqueCallbackFileDownloadResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[104]) {
        ((MediusCallback)gMediusFunctionPointers[104])(ThisPacket, gUserArguments[104]);
    }
    return 0x1FC;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileDownloadStreamResponseHandler) MediusUniqueCallbackFileDownloadStreamResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[105]) {
        ((MediusCallback)gMediusFunctionPointers[105])(ThisPacket, gUserArguments[105]);
    }
    return 0x1FC;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileDeleteResponseHandler) MediusUniqueCallbackFileDeleteResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[106]) {
        ((MediusCallback)gMediusFunctionPointers[106])(ThisPacket, gUserArguments[106]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileListFilesResponseHandler) MediusUniqueCallbackFileListFilesResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[107]) {
        ((MediusCallback)gMediusFunctionPointers[107])(ThisPacket, gUserArguments[107]);
    }
    return 0xC8;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileUpdateAttributesResponseHandler) MediusUniqueCallbackFileUpdateAttributesResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[108]) {
        ((MediusCallback)gMediusFunctionPointers[108])(ThisPacket, gUserArguments[108]);
    }
    return 0xC8;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileGetAttributesResponseHandler) MediusUniqueCallbackFileGetAttributesResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[109]) {
        ((MediusCallback)gMediusFunctionPointers[109])(ThisPacket, gUserArguments[109]);
    }
    return 0x1DC;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileUpdateMetaDataResponseHandler) MediusUniqueCallbackFileUpdateMetaDataResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[110]) {
        ((MediusCallback)gMediusFunctionPointers[110])(ThisPacket, gUserArguments[110]);
    }
    return 0xC8;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileGetMetaDataResponseHandler) MediusUniqueCallbackFileGetMetaDataResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[111]) {
        ((MediusCallback)gMediusFunctionPointers[111])(ThisPacket, gUserArguments[111]);
    }
    return 0x200;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileSearchByMetaDataResponseHandler) MediusUniqueCallbackFileSearchByMetaDataResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[112]) {
        ((MediusCallback)gMediusFunctionPointers[112])(ThisPacket, gUserArguments[112]);
    }
    return 0x200;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackFileCancelOperationResponseHandler) MediusUniqueCallbackFileCancelOperationResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[113]) {
        ((MediusCallback)gMediusFunctionPointers[113])(ThisPacket, gUserArguments[113]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackUniverseNewsHandler) MediusUniqueCallbackUniverseNewsHandler(int nNotUsed, int WorldID, int SourceClientIndex, MediusUniverseNewsResponse *ThisPacket)
{
    if (ThisPacket->EndOfText == 1) {
        G_MCL_uiCurInfoType |= 2;
    }
    if (gMediusFunctionPointers[0x38]) {
        ((MediusCallback)gMediusFunctionPointers[0x38])(ThisPacket, gUserArguments[0x38]);
    }
    return 0x120;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackUniverseStatusListHandler) MediusUniqueCallbackUniverseStatusListHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x230;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackUniverseStatusList_ExtraInfoHandler) MediusUniqueCallbackUniverseStatusList_ExtraInfoHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    return 0x338;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackUniverseSvoURLHandler) MediusUniqueCallbackUniverseSvoURLHandler(int nNotUsed, int WorldID, int SourceClientIndex, char *ThisPacket)
{
    RT_PACK_BUFFER buf;
    memset(mediusUniverseSvoURL, 0, 0x95);
    rt_init_pack_buffer(&buf, ThisPacket, ThisPacket + 0x200);
    rt_pack_anything(2, &buf, mediusUniverseSvoURL, 0x15);
    rt_pack_cstring(2, &buf, mediusUniverseSvoURL + 0x15);
    if (buf.lastError != 0) {
        return -1;
    }
    return buf.cursor - buf.begin;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/callback", MediusUniqueCallbackUniverseVariableInfoHandler);

int MEDIUS_CALLBACK_SECTION(MediusUtilGetServerVersionResponseHandler) MediusUtilGetServerVersionResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[114]) {
        ((MediusCallback)gMediusFunctionPointers[114])(ThisPacket, gUserArguments[114]);
    }
    return 0x18;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetTotalChannelsResponseHandler) MediusUniqueCallbackGetTotalChannelsResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[115]) {
        ((MediusCallback)gMediusFunctionPointers[115])(ThisPacket, gUserArguments[115]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetLobbyPlayerNamesResponseHandler) MediusUniqueCallbackGetLobbyPlayerNamesResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[116]) {
        ((MediusCallback)gMediusFunctionPointers[116])(ThisPacket, gUserArguments[116]);
    }
    return 0x20;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetTotalUsersResponseHandler) MediusUniqueCallbackGetTotalUsersResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[117]) {
        ((MediusCallback)gMediusFunctionPointers[117])(ThisPacket, gUserArguments[117]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackSetLocalizationParamsResponseHandler) MediusUniqueCallbackSetLocalizationParamsResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[118]) {
        ((MediusCallback)gMediusFunctionPointers[118])(ThisPacket, gUserArguments[118]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUtilEventMsgHandler) MediusUtilEventMsgHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[119]) {
        ((MediusCallback)gMediusFunctionPointers[119])(ThisPacket, gUserArguments[119]);
    }
    return 0x10;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetBuddyInvitationsResponseHandler) MediusUniqueCallbackGetBuddyInvitationsResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[67]) {
        ((MediusCallback)gMediusFunctionPointers[67])(ThisPacket, gUserArguments[67]);
    }
    return 0x48;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackSetLobbyWorldFilterResponseHandler) MediusUniqueCallbackSetLobbyWorldFilterResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, MediusStatusResponse *ThisPacket)
{
    if (ThisPacket->StatusCode == 0 && MyFilterMaskInfo.Enabled) {
        GlobalLobbyFilterFlag = 1;
    }
    if (MyFilterMaskInfo.Suppress == 1) {
        MyFilterMaskInfo.Suppress = 0;
    } else if (gMediusFunctionPointers[0x44]) {
        ((MediusCallback)gMediusFunctionPointers[0x44])(ThisPacket, gUserArguments[0x44]);
    }
    return 0x34;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackPostDebugInfoResponseHandler) MediusUniqueCallbackPostDebugInfoResponseHandler(int ConnectionIndex, int WorldID, int SourceClientIndex, MediusStatusResponse *ThisPacket)
{
    if (ThisPacket->StatusCode == -0x3B6) {
        mediusPostDebugInfoFlag = 0;
    }
    if (gMediusFunctionPointers[0x78]) {
        ((MediusCallback)gMediusFunctionPointers[0x78])(ThisPacket, gUserArguments[0x78]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackUpdateClanLadderStatsWide_DeltaResponseHandler) MediusUniqueCallbackUpdateClanLadderStatsWide_DeltaResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[70]) {
        ((MediusCallback)gMediusFunctionPointers[70])(ThisPacket, gUserArguments[70]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackTokenResponseHandler) MediusUniqueCallbackTokenResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[121]) {
        ((MediusCallback)gMediusFunctionPointers[121])(ThisPacket, gUserArguments[121]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackGetServerTimeResponseHandler) MediusUniqueCallbackGetServerTimeResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[122]) {
        ((MediusCallback)gMediusFunctionPointers[122])(ThisPacket, gUserArguments[122]);
    }
    return 0x24;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackSetAutoChatHistoryResponseHandler) MediusUniqueCallbackSetAutoChatHistoryResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[123]) {
        ((MediusCallback)gMediusFunctionPointers[123])(ThisPacket, gUserArguments[123]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAccountUpdateStats_OpenAccessResponseHandler) MediusUniqueCallbackAccountUpdateStats_OpenAccessResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[124]) {
        ((MediusCallback)gMediusFunctionPointers[124])(ThisPacket, gUserArguments[124]);
    }
    return 0x1C;
}

int MEDIUS_CALLBACK_SECTION(MediusUniqueCallbackAddPlayerToClan_ByClanOfficerResponseHandler) MediusUniqueCallbackAddPlayerToClan_ByClanOfficerResponseHandler(int nNotUsed, int WorldID, int SourceClientIndex, void *ThisPacket)
{
    if (gMediusFunctionPointers[125]) {
        ((MediusCallback)gMediusFunctionPointers[125])(ThisPacket, gUserArguments[125]);
    }
    return 0x1C;
}
