#include "common.h"
#include "game_section.h"


struct PAD {
	/* 0x000 */ char unk000[0x54c];
	/* 0x54c */ unsigned char port;
	/* 0x54d */ char unk54d[0x558 - 0x54d];
	/* 0x558 */ unsigned char slot;
};
struct actuatorWave {
	/* 0x00 */ unsigned char type;
	/* 0x01 */ unsigned char loop;
	/* 0x02 */ unsigned char side;
	/* 0x03 */ unsigned char scale;
	/* 0x04 */ short delay;
	/* 0x06 */ short lifeSpan;
	/* 0x08 */ short timer;
	/* 0x0a */ short on;
	/* 0x0c */ short off;
	/* 0x0e */ unsigned char power;
	/* 0x0f */ unsigned char minpower;
};
extern actuatorWave *actuatorWaves[] __asm__("D_3D6398");
int actuator_SetWave(actuatorWave *, PAD *) __asm__("actuator_SetWave");
int actuator_dbgplaywave(unsigned int, PAD *) __asm__("actuator_dbgplaywave");
extern actuatorWave actuators[][8] __asm__("D_3D6458");
void actuator_dbgstopwave(PAD *) __asm__("actuator_dbgstopwave");
void actuator_killWave(int, PAD *) __asm__("actuator_killWave");
int actuator_CalcPower(int *, PAD *) __asm__("actuator_CalcPower");
float FastCos(float) __asm__("FastCos");



GAME_SECTION(actuator_dbgplaywave) int actuator_dbgplaywave(unsigned int index, PAD *pPad)
{
	int ret;
	if (index >= 0x62) ret = -1;
	else ret = actuator_SetWave(actuatorWaves[index], pPad);
	return ret;
}

GAME_SECTION(actuator_dbgstopwave) void actuator_dbgstopwave(PAD *pPad)
{
	int padSlot;
	int i;
	padSlot = 0;
	if (pPad) {
		if (pPad->slot == 0xff) return;
		padSlot = pPad->port * 4 + pPad->slot;
	}
	for (i = 7; i >= 0; i--) actuators[padSlot][i].type = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/actuator", func_00438D30);

/* NOT EXACT */
GAME_SECTION(actuator_SetWave) int actuator_SetWave(actuatorWave *pAW, PAD *pPad)
{
	int i;
	int j;
	int numWaves;
	int padSlot;
	padSlot = 0;
	if (pPad) {
		if (pPad->slot == 0xff) return 0;
		padSlot = pPad->port * 4 + pPad->slot;
	}
	for (numWaves = 0; numWaves < 8 && pAW[numWaves].type != 0xff; numWaves++);
	j = 0;
	for (i = 0; i < 8 && j < numWaves; i++) {
		if (!actuators[padSlot][i].type) j++;
	}
	if (j != numWaves) return -1;
	for (j = 0; j < numWaves; j++) {
		for (i = 0; i < 8 && actuators[padSlot][i].type; i++);
		if (i < 8) {
			actuators[padSlot][i].type = pAW[j].type;
			actuators[padSlot][i].loop = pAW[j].loop;
			actuators[padSlot][i].side = pAW[j].side;
			actuators[padSlot][i].scale = pAW[j].scale;
			actuators[padSlot][i].delay = pAW[j].delay;
			actuators[padSlot][i].lifeSpan = pAW[j].lifeSpan;
			actuators[padSlot][i].timer = pAW[j].timer;
			actuators[padSlot][i].on = pAW[j].on;
			actuators[padSlot][i].off = pAW[j].off;
			actuators[padSlot][i].power = pAW[j].power - pAW[j].minpower;
			actuators[padSlot][i].minpower = pAW[j].minpower;
			if (actuators[padSlot][i].on + actuators[padSlot][i].off == 0) actuators[padSlot][i].on++;
		}
	}
	return i;
}

GAME_SECTION(actuator_killWave) void actuator_killWave(int awIdx, PAD *pPad)
{
	int padSlot;
	int i;
	padSlot = 0;
	if (pPad) {
		if (pPad->slot == 0xff) return;
		padSlot = pPad->port * 4 + pPad->slot;
	}
	for (i = 0; i < 8; i++) {
		actuatorWave *s = &actuators[padSlot][i];
		if (s->loop) {
			s->loop = 0;
			s->lifeSpan = 0;
		}
	}
}

GAME_SECTION(actuator_CalcPower) int actuator_CalcPower(int *power, PAD *pPad)
{
	int ret = 0;
	int scale[2];
	int numscale[2];
	int numpower[2];
	int i;
	actuatorWave *pAW;
	int padSlot;
	int pow;
	int timer;
	float f;
	padSlot = 0;
	if (pPad) {
		if (pPad->slot == 0xff) return 0;
		padSlot = pPad->port * 4 + pPad->slot;
	}
	for (i = 0; i < 2; i++) {
		power[i] = 0;
		scale[i] = 0;
		numscale[i] = 0;
		numpower[i] = 0;
	}
	for (i = 0; i < 8; i++) {
		pAW = &actuators[padSlot][i];
		if (!pAW->type) continue;
		ret++;
		if (!pAW->loop) {
			if (pAW->lifeSpan-- <= 0) pAW->type = 0;
		}
		if (pAW->delay) {
			pAW->delay--;
			continue;
		}
		pAW->timer++;
		timer = pAW->timer % (pAW->on + pAW->off);
		pow = 0;
		switch (pAW->type) {
		case 0:
			break;
		case 1:
			if (timer < pAW->on) pow = pAW->power + pAW->minpower;
			else pow = pAW->minpower;
			break;
		case 2:
			if (timer < pAW->on) pow = pAW->power * timer / pAW->on;
			else pow = pAW->power * (pAW->off + pAW->on - timer) / pAW->off;
			pow += pAW->minpower;
			break;
		case 3:
			if (timer < pAW->on) pow = pAW->power * timer / pAW->on + pAW->minpower;
			break;
		case 4:
			if (timer >= pAW->on) pow = pAW->power * (pAW->off + pAW->on - timer) / pAW->off + pAW->minpower;
			break;
		case 5:
			if (timer < pAW->off) f = (float)timer * 3.1415927f / (float)pAW->off;
			else f = 3.1415927f - (float)(timer - pAW->off) * 3.1415927f / (float)pAW->on;
			pow = (int)((FastCos(f) * (float)pAW->power + (float)pAW->power) * 0.5f) + pAW->minpower;
			if (pow >= 0x100) pow = 0xff;
			break;
		}
		if (pAW->scale) {
			scale[pAW->side] += pow;
			numscale[pAW->side]++;
		} else {
			power[pAW->side] += pow;
			numpower[pAW->side]++;
		}
	}
	for (i = 0; i < 2; i++) {
		if (numpower[i]) power[i] /= numpower[i];
		if (numscale[i]) {
			scale[i] /= numscale[i];
			power[i] = power[i] * scale[i] / 0xff;
		}
	}
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/actuator", func_004393C0);
