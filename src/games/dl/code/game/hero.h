#ifndef HERO_H
#define HERO_H

#include "mobyutil.h"
#include "pad.h"

struct GAMECAMERA;
struct HeroPlayerConstants;
struct VehicleBase;

struct Hero { // 0x2fe0
	/* 0x0000 */ char unk0000[0x2e20];
	/* 0x2e20 */ float hitPoints;
	/* 0x2e24 */ float boltPickupRadiusXY;
	/* 0x2e28 */ float boltPickupZthresh;
	/* 0x2e2c */ short noClank;
	/* 0x2e30 */ float skidDecel;
	/* 0x2e34 */ short mtxFxActive;
	/* 0x2e38 */ float analogStickStrength;
	/* 0x2e3c */ short deathFallChannel;
	/* 0x2e3e */ short wallJumpAngLimiter;
	/* 0x2e40 */ unsigned char wallJumpHeightFactor;
	/* 0x2e41 */ unsigned char wallJumpChainCnt;
	/* 0x2e44 */ float wallJumpDist;
	/* 0x2e48 */ float moonJumpIdealHeight;
	/* 0x2e4c */ float moonJumpGravity;
	/* 0x2e50 */ short chargeDoubleTapTimer;
	/* 0x2e52 */ short chargeDownTimer;
	/* 0x2e54 */ short chargeDelayTimer;
	/* 0x2e56 */ short tweakersReset;
	/* 0x2e58 */ int gadgetFilter;
	/* 0x2e5c */ int gadgetFilterSize;
	/* 0x2e60 */ int targetGadgetFilterSize;
	/* 0x2e64 */ float FPS_InterpSpeed;
	/* 0x2e68 */ float FPS_InterpAccel;
	/* 0x2e6c */ int FPS_StartTime;
	/* 0x2e70 */ unsigned char FPSTapTimer;
	/* 0x2e71 */ unsigned char FPSTapCount;
	/* 0x2e72 */ unsigned char strafeTapTimer;
	/* 0x2e73 */ unsigned char strafeTapCount;
	/* 0x2e74 */ unsigned char lockedStrafeModeOn;
	/* 0x2e78 */ unsigned int lastDamagedMeOwnerUID;
	/* 0x2e7c */ int lastDamagedMeGadgetId;
	/* 0x2e80 */ float lastDamagedMeHp;
	/* 0x2e84 */ signed char restoreCamAzDir;
	/* 0x2e85 */ signed char restoreCamRotSpd;
	/* 0x2e88 */ int rAmb;
	/* 0x2e8c */ int gAmb;
	/* 0x2e90 */ int bAmb;
	/* 0x2e94 */ MobyInstance *lastWeaponTarget;
	/* 0x2e98 */ MobyInstance *recentTargets[4];
	/* 0x2ea8 */ int lastWeaponTargetTime;
	/* 0x2eac */ char getHitMessage[0x10];
	/* 0x2ebc */ FlashVars flashVars;
	/* 0x2ecc */ unsigned char isGetHitMsgPending;
	/* 0x2ecd */ unsigned char lookAndCrouch;
	/* 0x2ece */ unsigned char lookAndThrowWrench;
	/* 0x2ecf */ unsigned char earlyThrowAbort;
	/* 0x2ed0 */ unsigned char lookAndGetHit;
	/* 0x2ed1 */ unsigned char lastDeathWasSuicide;
	/* 0x2ed2 */ unsigned char noWeaponSwitching;
	/* 0x2ed3 */ unsigned char noWrenchEquip;
	/* 0x2ed4 */ unsigned char jackpotMult;
	/* 0x2ed5 */ signed char rocketHitMe;
	/* 0x2ed6 */ unsigned char explode;
	/* 0x2ed7 */ unsigned char deathWasCalled;
	/* 0x2ed8 */ int hudHealthTimer;
	/* 0x2edc */ unsigned char pauseOn;
	/* 0x2edd */ unsigned char pauseTimer;
	/* 0x2ee0 */ int tauntOverrideTimer;
	/* 0x2ee4 */ unsigned char playerType;
	/* 0x2ee8 */ MobyInstance *flagMoby;
	/* 0x2eec */ HeroPlayerConstants *playerConst;
	/* 0x2ef0 */ MobyInstance *pMoby;
	/* 0x2ef4 */ VehicleBase *pVehicle;
	/* 0x2ef8 */ VehicleBase *pVehiclePending;
	/* 0x2efc */ GAMECAMERA *camera;
	/* 0x2f00 */ PAD *pPad;
	/* 0x2f04 */ float cheatX;
	/* 0x2f08 */ float cheatY;
	/* 0x2f0c */ float cheatZ;
	/* 0x2f10 */ int mpIndex;
	/* 0x2f14 */ int mpTeam;
	/* 0x2f18 */ int vehicleState;
	/* 0x2f1c */ int vehicleStateTimer;
	/* 0x2f20 */ int pointsLastKill;
	/* 0x2f24 */ float maxHP;
	/* 0x2f28 */ char unk2f28[0x2fe0 - 0x2f28];
};

#endif
