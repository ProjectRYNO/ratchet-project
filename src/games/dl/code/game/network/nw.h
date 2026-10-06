#ifndef NETWORK_NW_H
#define NETWORK_NW_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:10346; prototype-layout.
typedef struct { // 0x8c
    /* 0x00 */ short int ranksToLevels[10];
    /* 0x14 */ short int m_dropPenaltyStart;
    /* 0x16 */ short int m_linkDirtyMax;
    /* 0x18 */ short int m_linkDirtyShortTermMax;
    /* 0x1a */ short int m_dropTo30;
    /* 0x1c */ short int m_perPlayer;
    /* 0x1e */ short int m_perPlayerSiege;
    /* 0x20 */ short int m_hasHeadset;
    /* 0x22 */ short int m_perWeapon[9];
    /* 0x34 */ short int m_perVehicle[4];
    /* 0x3c */ short int m_perLevel[12];
    /* 0x54 */ short int m_perMajorMode[5];
    /* 0x60 */ float m_RANK_SPREAD;
    /* 0x64 */ float m_RANK_DIFF_LOW_CLAMP;
    /* 0x68 */ float m_RANK_DIFF_HIGH_CLAMP;
    /* 0x6c */ float m_RANK_VALUE;
    /* 0x70 */ float m_MIN_LOSE;
    /* 0x74 */ float m_MIN_LOSE_SPREAD;
    /* 0x78 */ float m_MAX_WIN_SPREAD;
    /* 0x7c */ float m_MAX_SCORE;
    /* 0x80 */ float m_DAMP_WINNING_LOW_CLAMP;
    /* 0x84 */ float m_MIN_ALWAYS_POSITIVE_RANK_DELTA;
    /* 0x88 */ float m_MAX_ADD_TO_RANK;
} tNW_DownloadedTweaks;

// dltypes.txt:17968; ghidra-layout.
typedef struct { // 0x34
    /* 0x00 */ unsigned int crc;
    /* 0x04 */ int rank[6];
    /* 0x1c */ int padding[1];
    /* 0x20 */ char headsetAttached;
    /* 0x21 */ char isClanLeader;
    /* 0x22 */ char hasLocalPlayer;
    /* 0x23 */ char pad;
    /* 0x24 */ int clanID;
    /* 0x28 */ int totalGamesWithCheaters;
    /* 0x2c */ int consecutiveGamesWithCheaters;
    /* 0x30 */ char lastGameHadCheater;
} tNW_PlayerInfoStats;

// dltypes.txt:18013; prototype-layout.
typedef struct { // 0x8
    /* 0x0 */ int m_id;
    /* 0x4 */ int m_timeout;
} tReservations;

#endif
