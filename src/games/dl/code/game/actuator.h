#ifndef ACTUATOR_H
#define ACTUATOR_H

typedef struct { // 0x10
	/* 0x0 */ char type;
	/* 0x1 */ char loop;
	/* 0x2 */ char side;
	/* 0x3 */ char scale;
	/* 0x4 */ short int delay;
	/* 0x6 */ short int lifeSpan;
	/* 0x8 */ short int timer;
	/* 0xa */ short int on;
	/* 0xc */ short int off;
	/* 0xe */ char power;
	/* 0xf */ char minpower;
} actuatorWave;

#endif
