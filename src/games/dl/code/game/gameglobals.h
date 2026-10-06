#ifndef GAMEGLOBALS_H
#define GAMEGLOBALS_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

#ifndef __cplusplus
#include <stdbool.h>
#endif

// dltypes.txt:942; prototype-layout.
typedef struct { // 0x3c
    /* 0x00 */ int bolts;
    /* 0x04 */ int boltDeficit;
    /* 0x08 */ int xp;
    /* 0x0c */ int points;
    /* 0x10 */ short int HeroMaxHp;
    /* 0x12 */ short int ArmorLevel;
    /* 0x14 */ float limitBreak;
    /* 0x18 */ int purchasedSkins;
    /* 0x1c */ short int spentDiffStars;
    /* 0x1e */ char boltMultLevel;
    /* 0x1f */ char boltMultSubLevel;
    /* 0x20 */ char OldGameSaveData;
    /* 0x21 */ char blueBadges;
    /* 0x22 */ char redBadges;
    /* 0x23 */ char greenBadges;
    /* 0x24 */ char goldBadges;
    /* 0x25 */ char blackBadges;
    /* 0x26 */ char Completes;
    /* 0x27 */ char lastEquippedGadget[2];
    /* 0x29 */ char tempWeapons[4];
    /* 0x30 */ int currentMaxLimitBreak;
    /* 0x34 */ short int ArmorLevel2;
    /* 0x36 */ short int progressionArmorLevel;
    /* 0x38 */ int startLimitBreakDiff;
} _HeroSave;

// dltypes.txt:1997; prototype-layout.
typedef struct { // 0x4
    /* 0x0 */ short int second;
    /* 0x2 */ signed char kern;
    /* 0x3 */ char end;
} FontKerning;

// dltypes.txt:2003; prototype-layout.
typedef struct { // 0x110
    /* 0x000 */ char num_palettes;
    /* 0x001 */ char num_pages;
    /* 0x002 */ char padding[14];
    /* 0x010 */ char page_palette_map[16][2];
    /* 0x030 */ char palette_types[16];
    /* 0x040 */ char page_types[16];
    /* 0x050 */ short int page_sizes[16][2];
    /* 0x090 */ int palette_offsets[16];
    /* 0x0d0 */ int page_offsets[16];
} FontFileHeader;

// dltypes.txt:2034; prototype-layout.
typedef struct { // 0xc4
    /* 0x00 */ int PalMode;
    /* 0x04 */ char HelpVoiceOn;
    /* 0x05 */ char HelpTextOn;
    /* 0x06 */ char SubtitlesActive;
    /* 0x08 */ int Stereo;
    /* 0x0c */ int MusicVolume;
    /* 0x10 */ int EffectsVolume;
    /* 0x14 */ int VoVolume;
    /* 0x18 */ int CameraElevationDir[3][4];
    /* 0x48 */ int CameraAzimuthDir[3][4];
    /* 0x78 */ int CameraRotateSpeed[3][4];
    /* 0xa8 */ unsigned char FirstPersonModeOn[10];
    /* 0xb2 */ char _was_NTSCProgessive;
    /* 0xb3 */ char Wide;
    /* 0xb4 */ char ControllerVibrationOn[8];
    /* 0xbc */ char QuickSelectPauseOn;
    /* 0xbd */ char Language;
    /* 0xbe */ char AuxSetting2;
    /* 0xbf */ char AuxSetting3;
    /* 0xc0 */ char AuxSetting4;
    /* 0xc1 */ char AutoSaveOn;
} GameSettings;

// dltypes.txt:2096; prototype-layout.
typedef struct { // 0x14
    /* 0x00 */ int noofGamesPlayed;
    /* 0x04 */ int noofGamesWon;
    /* 0x08 */ int noofGamesLost;
    /* 0x0c */ int noofKills;
    /* 0x10 */ int noofDeaths;
} generalStatStruct;

// dltypes.txt:2104; prototype-layout.
typedef struct { // 0x44
    /* 0x00 */ int noofWins;
    /* 0x04 */ int noofLosses;
    /* 0x08 */ int winsPerLevel[6];
    /* 0x20 */ int lossesPerLevel[6];
    /* 0x38 */ int noofBaseCaptures;
    /* 0x3c */ int noofKills;
    /* 0x40 */ int noofDeaths;
} siegeMatchStatStruct;

// dltypes.txt:2114; prototype-layout.
typedef struct { // 0x40
    /* 0x00 */ int noofWins;
    /* 0x04 */ int noofLosses;
    /* 0x08 */ int winsPerLevel[6];
    /* 0x20 */ int lossesPerLevel[6];
    /* 0x38 */ int noofkills;
    /* 0x3c */ int noofDeaths;
} deadMatchStatStruct;

// dltypes.txt:2123; prototype-layout.
typedef struct { // 0x8
    /* 0x0 */ bool normalLeftRightMode;
    /* 0x1 */ bool normalUpDownMode;
    /* 0x4 */ int cameraSpeed;
} cameraMode;

// dltypes.txt:2170; prototype-layout.
typedef struct { // 0x64
    /* 0x00 */ int index[10];
    /* 0x28 */ float points[10];
    /* 0x50 */ int numPlayers;
    /* 0x54 */ int totalKills;
    /* 0x58 */ int totalDeaths;
    /* 0x5c */ int totalSuicides;
    /* 0x60 */ int conquestTicketScore;
} tTeamStats;

// dltypes.txt:2058; prototype-layout.
typedef struct { // 0x140
    /* 0x000 */ int CameraElevationDir[3][8];
    /* 0x060 */ int CameraAzimuthDir[3][8];
    /* 0x0c0 */ int CameraRotateSpeed[3][8];
    /* 0x120 */ unsigned char FirstPersonModeOn[8];
    /* 0x128 */ char ControllerVibrationOn[8];
    /* 0x130 */ int nControllerPadIndices[4];
} LobbyControllerSetup;

#ifdef __cplusplus
extern "C" {
#endif

// Existing retail storage, named by symbols_core.text.txt.
extern GameSettings bootSettings;
extern unsigned int progressiveScan;
extern unsigned int displayX;
extern unsigned int displayY;

#ifdef __cplusplus
}
#endif

#endif
