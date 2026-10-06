#ifndef GUBER_GAMECONTROLLER_H
#define GUBER_GAMECONTROLLER_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:20938; prototype-layout.
typedef struct { // 0x140
    /* 0x000 */ int resurrectionPts[64];
    /* 0x100 */ int pad1;
    /* 0x104 */ int randomSpawn;
    /* 0x108 */ int smartSpawnPts;
    /* 0x10c */ int pad[13];
} DeathMatchGameData;

// dltypes.txt:21310; prototype-layout.
typedef struct { // 0x4e8
    /* 0x000 */ char gameType;
    /* 0x004 */ int timeEnd;
    /* 0x008 */ int timeStart;
    /* 0x00c */ char gameState;
    /* 0x00d */ char numTeams;
    /* 0x00e */ short int teamTicketScore[10];
    /* 0x022 */ char baseTeam[10];
    /* 0x02c */ int winningTeam;
    /* 0x030 */ int winningPlayer;
    /* 0x034 */ int gameIsOver;
    /* 0x038 */ short int weaponKills[10][9];
    /* 0x0ec */ short int weaponDeaths[10][9];
    /* 0x1a0 */ short int weaponShotsFired[10][9];
    /* 0x254 */ short int weaponShotsHit[10][9];
    /* 0x308 */ float vehicleTime[10];
    /* 0x330 */ short int vehicleWeaponKills[10];
    /* 0x344 */ short int vehicleWeaponDeaths[10];
    /* 0x358 */ short int vehicleRoadKills[10];
    /* 0x36c */ short int vehicleRoadDeaths[10];
    /* 0x380 */ short int vehicleShotsFired[10];
    /* 0x394 */ short int vehicleShotsHit[10];
    /* 0x3a8 */ short int playerKills[10];
    /* 0x3bc */ short int playerDeaths[10];
    /* 0x3d0 */ short int suicides[10];
    /* 0x3e4 */ short int multiKills[10];
    /* 0x3f8 */ short int sniperKills[10];
    /* 0x40c */ short int wrenchKills[10];
    /* 0x420 */ char conquestNodesCaptured[10];
    /* 0x42a */ char conquestNodeSaves[10];
    /* 0x434 */ char conquestDefensiveKills[10];
    /* 0x43e */ char conquestPoints[10];
    /* 0x448 */ char ctfFlagCaptures[10];
    /* 0x452 */ char ctfFlagSaves[10];
    /* 0x45c */ float kingHillHoldTime[10];
    /* 0x484 */ float juggernautTime[10];
    /* 0x4ac */ short int squats[10];
    /* 0x4c0 */ short int vehicleSquats[10];
    /* 0x4d4 */ short int ticketScore[10];
} tNW_GameStateMessage;

#endif
