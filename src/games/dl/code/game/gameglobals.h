#ifndef GAMEGLOBALS_H
#define GAMEGLOBALS_H

#include "../include/types.h"

#ifndef __cplusplus
#include <stdbool.h>
#endif

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

typedef struct { // 0x4
	/* 0x0 */ short int second;
	/* 0x2 */ signed char kern;
	/* 0x3 */ char end;
} FontKerning;

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

typedef struct { // 0x14
	/* 0x00 */ int noofGamesPlayed;
	/* 0x04 */ int noofGamesWon;
	/* 0x08 */ int noofGamesLost;
	/* 0x0c */ int noofKills;
	/* 0x10 */ int noofDeaths;
} generalStatStruct;

typedef struct { // 0x44
	/* 0x00 */ int noofWins;
	/* 0x04 */ int noofLosses;
	/* 0x08 */ int winsPerLevel[6];
	/* 0x20 */ int lossesPerLevel[6];
	/* 0x38 */ int noofBaseCaptures;
	/* 0x3c */ int noofKills;
	/* 0x40 */ int noofDeaths;
} siegeMatchStatStruct;

typedef struct { // 0x40
	/* 0x00 */ int noofWins;
	/* 0x04 */ int noofLosses;
	/* 0x08 */ int winsPerLevel[6];
	/* 0x20 */ int lossesPerLevel[6];
	/* 0x38 */ int noofkills;
	/* 0x3c */ int noofDeaths;
} deadMatchStatStruct;

typedef struct { // 0x8
	/* 0x0 */ bool normalLeftRightMode;
	/* 0x1 */ bool normalUpDownMode;
	/* 0x4 */ int cameraSpeed;
} cameraMode;

typedef struct { // 0x64
	/* 0x00 */ int index[10];
	/* 0x28 */ float points[10];
	/* 0x50 */ int numPlayers;
	/* 0x54 */ int totalKills;
	/* 0x58 */ int totalDeaths;
	/* 0x5c */ int totalSuicides;
	/* 0x60 */ int conquestTicketScore;
} tTeamStats;

typedef struct { // 0x140
	/* 0x000 */ int CameraElevationDir[3][8];
	/* 0x060 */ int CameraAzimuthDir[3][8];
	/* 0x0c0 */ int CameraRotateSpeed[3][8];
	/* 0x120 */ unsigned char FirstPersonModeOn[8];
	/* 0x128 */ char ControllerVibrationOn[8];
	/* 0x130 */ int nControllerPadIndices[4];
} LobbyControllerSetup;

struct fsAABuff { // 0x180
	/* 0x000 */ char disp[0x30];
	/* 0x030 */ u128 giftagDrawLarge;
	/* 0x040 */ char drawLarge[0x80];
	/* 0x0c0 */ u128 giftagDrawSmall;
	/* 0x0d0 */ char drawSmall[0x80];
	/* 0x150 */ short drawW;
	/* 0x152 */ short drawH;
	/* 0x154 */ short drawPSM;
	/* 0x156 */ short drawFBP;
	/* 0x158 */ short dispW;
	/* 0x15a */ short dispH;
	/* 0x15c */ short dispPSM;
	/* 0x15e */ short dispFBP;
	/* 0x160 */ short auxW;
	/* 0x162 */ short auxH;
	/* 0x164 */ short auxPSM;
	/* 0x166 */ short auxFBP;
	/* 0x168 */ short dispOfsX;
	/* 0x16a */ short dispOfsY;
	/* 0x16c */ short zPSM;
	/* 0x16e */ short zFBP;
	/* 0x170 */ int update_context;
};

struct GSMEM { // 0x58
	/* 0x00 */ int display;
	/* 0x04 */ int draw;
	/* 0x08 */ int zbuf;
	/* 0x0c */ int base;
	/* 0x10 */ int perm_grey_tex;
	/* 0x14 */ int perm_debug_font;
	/* 0x18 */ int perm_armor;
	/* 0x1c */ int perm_armor2;
	/* 0x20 */ int perm_bots;
	/* 0x24 */ int perm_landstalker;
	/* 0x28 */ int perm_dropship;
	/* 0x2c */ int perm_bank;
	/* 0x30 */ int stash_armor;
	/* 0x34 */ int stash_armor2;
	/* 0x38 */ int stash_bots;
	/* 0x3c */ int stash_landstalker;
	/* 0x40 */ int stash_dropship;
	/* 0x44 */ int stash_mobys;
	/* 0x48 */ int stash_hud;
	/* 0x4c */ int stash_font;
	/* 0x50 */ int stash_end;
	/* 0x54 */ int pad;
};

struct SpaceDef { // 0x20
	/* 0x00 */ short state;
	/* 0x02 */ short timer;
	/* 0x04 */ short ship_type;
	/* 0x06 */ short quick_entry;
	/* 0x08 */ short first_entry;
	/* 0x0a */ short level_entry;
	/* 0x0c */ short ship_trans;
	/* 0x0e */ short wad_index;
	/* 0x10 */ int speech_played;
	/* 0x14 */ int movie_index;
	/* 0x18 */ int movie_cnt;
	/* 0x1c */ int movie_abort;
};

struct sceCdCLOCK { // 0x8
	/* 0x00 */ unsigned char stat;
	/* 0x01 */ unsigned char second;
	/* 0x02 */ unsigned char minute;
	/* 0x03 */ unsigned char hour;
	/* 0x04 */ unsigned char pad;
	/* 0x05 */ unsigned char day;
	/* 0x06 */ unsigned char month;
	/* 0x07 */ unsigned char year;
};

struct HelpDatum { // 0xc
	/* 0x00 */ unsigned short timesUsed;
	/* 0x02 */ unsigned short counter;
	/* 0x04 */ unsigned int lastTime;
	/* 0x08 */ unsigned int level_die;
};

struct MISSIONLOAD { // 0x28
	/* 0x00 */ int ActiveMission;
	/* 0x04 */ int LoadingMission;
	/* 0x08 */ int ErrorCode;
	/* 0x0c */ int QueuedMission;
	/* 0x10 */ unsigned char Success;
	/* 0x11 */ unsigned char ResetLevel;
	/* 0x12 */ unsigned char Loading;
	/* 0x13 */ unsigned char Parse;
	/* 0x14 */ unsigned char Switch;
	/* 0x15 */ unsigned char DoubleBuffer;
	/* 0x16 */ unsigned char QueuedLoad;
	/* 0x17 */ unsigned char InstancesActive;
	/* 0x18 */ unsigned char ClassesActive;
	/* 0x19 */ unsigned char InstancesLoaded;
	/* 0x1a */ unsigned char ClassesLoaded;
	/* 0x1b */ unsigned char SoundLoaded;
	/* 0x1c */ void *ActiveMissionClasses;
	/* 0x20 */ void *LoadingMissionClasses;
	/* 0x24 */ int State;
};

struct GadgetCache { // 0x1
	static void Initialize() __asm__("Initialize___dupe2");
	static void UnInitialize() __asm__("UnInitialize");
	static void Reset() __asm__("Reset___dupe2");
};

struct StashInfo { // 0x3c
	/* 0x00 */ char *base;
	/* 0x04 */ int size;
	/* 0x08 */ int cd[10];
	/* 0x30 */ char *free;
	/* 0x34 */ int block;
	/* 0x38 */ char *gadgetram;
};

#ifdef __cplusplus
extern "C" {
#endif

extern GameSettings bootSettings;
extern unsigned int progressiveScan;
extern unsigned int displayX;
extern unsigned int displayY;

#ifdef __cplusplus
}
#endif

struct tNW_Info { // 0x1684
	/* 0x0000 */ char unk0000[0x258];
	/* 0x0258 */ int onlyLocalPlayers;
	/* 0x025c */ char unk025c[0x1684 - 0x25c];
};

#endif
