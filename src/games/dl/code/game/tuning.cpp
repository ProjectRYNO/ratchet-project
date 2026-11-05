#include "common.h"
#include "game_section.h"


typedef struct tnDifficulty {
	/* 0x00 */ float killedHp;
	/* 0x04 */ char unk04[0x14];
	/* 0x18 */ float ammoFactor;
	/* 0x1c */ char unk1c[8];
} tnDifficulty_t;
typedef struct hero {
	/* 0x0000 */ char unk00[0x2f24];
	/* 0x2f24 */ float maxHP;
} hero_t;
extern tnDifficulty_t TN_difficultyTuning[] __asm__("TN_difficultyTuning");
extern int TN_difficultyLevel __asm__("TN_difficultyLevel");
extern hero_t *g_Hero[10] __asm__("g_Hero");
extern int Level __asm__("Level");
extern int mf_activeMissionIndex __asm__("mf_activeMissionIndex");
bool GB_VehicleHasPlayerLockedIn() __asm__("GB_VehicleHasPlayerLockedIn");
float MB_randRange(float min, float max) __asm__("MB_randRange");
int MB_rand(int max) __asm__("MB_rand");
int TN_CalculateAmmoFromEnemies(int killedHp) __asm__("TN_CalculateAmmoFromEnemies");


GAME_SECTION(TN_CalculateAmmoFromEnemies) int TN_CalculateAmmoFromEnemies(int killedHp)
{
	float heroMaxHp;
	int i;
	int ammoToSpawn;
	float spawnAmmoVariable;
	if (GB_VehicleHasPlayerLockedIn()) return 0;
	TN_difficultyTuning[0].killedHp += (float)killedHp;
	heroMaxHp = 0.0f;
	{
		hero_t *pHero = g_Hero[0];
		for (i = 0; i < 10; i++, pHero = g_Hero[i]) {
			if (pHero) {
				float hp = pHero->maxHP;
				if (0.0f < hp && heroMaxHp < hp) heroMaxHp = hp;
			}
		}
	}
	ammoToSpawn = 0;
	{
		float factor = TN_difficultyTuning[TN_difficultyLevel].ammoFactor;
		float rnd = MB_randRange(1.0f, 2.0f);
		spawnAmmoVariable = heroMaxHp * factor * rnd;
	}
	if (Level == 0xf && mf_activeMissionIndex == 3 && MB_rand(4) == 0) spawnAmmoVariable = 0.0f;
	while (spawnAmmoVariable < TN_difficultyTuning[0].killedHp) {
		TN_difficultyTuning[0].killedHp -= spawnAmmoVariable;
		ammoToSpawn++;
		if (spawnAmmoVariable <= 0.0f) break;
	}
	return ammoToSpawn;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/tuning", func_004FBF38);
