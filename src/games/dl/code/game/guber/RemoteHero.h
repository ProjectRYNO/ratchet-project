#ifndef GUBER_REMOTEHERO_H
#define GUBER_REMOTEHERO_H

#include "../mobyutil.h"
#include "../mobyfunc.h"
#include "../pad.h"
#include "../camera.h"
#include "../path.h"
#include "GuberMoby.h"
#include "Hero.h"

struct COLL_DAM_OUT;
struct GAMECAMERA;
struct GadgetBox;
struct HeroNPJumpThrustStage;
struct UpdateCam;
struct VehicleBase;
struct tNW_Player;

struct Gadget { // 0x50
	/* 0x00 */ vec4 jointPos;
	/* 0x10 */ vec4f jointRot;
	/* 0x20 */ moby *pMoby;
	/* 0x24 */ moby *pMoby2;
	/* 0x28 */ unsigned char padButtonDown;
	/* 0x2c */ int alignPad;
	/* 0x30 */ int padButton;
	/* 0x34 */ int gsSpawnFrame;
	/* 0x38 */ unsigned char noAmmoTime;
	/* 0x39 */ unsigned char unEquipTimer;
	/* 0x3a */ unsigned char detached;
	/* 0x3b */ unsigned char unequipTime;
	/* 0x3c */ unsigned char unEquipStatus;
	/* 0x3d */ unsigned char unEquipDelay;
	/* 0x40 */ int equippedTime;
	/* 0x44 */ int state;
	/* 0x48 */ int id;
	/* 0x4c */ float lightAng;
};

struct HeroAnim { // 0x20
	/* 0x00 */ float speed;
	/* 0x04 */ int iscale;
	/* 0x08 */ int flags;
	/* 0x0c */ int interping;
	/* 0x10 */ int env_index;
	/* 0x14 */ int env_time;
	/* 0x18 */ float mayaFrm;
	/* 0x1c */ float mayaFrmDelt;
};

struct HeroAnimLayers { // 0x34
	/* 0x00 */ MobyAnimLayer *pArmBlenders[2];
	/* 0x08 */ MobyAnimLayer *pFiringBlenders[2];
	/* 0x10 */ MobyAnimLayer *pHeadBlender;
	/* 0x14 */ int detachingFiring;
	/* 0x18 */ int armBlenderSharesIdle;
	/* 0x1c */ int gadgetAttachedId;
	/* 0x20 */ int usingRunAnim[4];
	/* 0x30 */ int headAnim;
};

struct HeroAttack { // 0xb0
	/* 0x00 */ vec4 near;
	/* 0x10 */ vec4 far;
	/* 0x20 */ vec4 oldNear;
	/* 0x30 */ vec4 oldFar;
	/* 0x40 */ vec4 wrenchHandle;
	/* 0x50 */ vec4 wrenchTip;
	/* 0x60 */ vec4 idealVec;
	/* 0x70 */ vec4 bounceVec;
	/* 0x80 */ MobyInstance *pTarget;
	/* 0x84 */ MobyInstance *pMoby;
	/* 0x88 */ int rotSet;
	/* 0x8c */ float rot;
	/* 0x90 */ float bounceAng;
	/* 0x94 */ float speedFactor;
	/* 0x98 */ MobyInstance *pGunPointMoby;
	/* 0x9c */ short id;
	/* 0x9e */ short soundPlayed;
	/* 0xa0 */ float descend;
	/* 0xa4 */ float aimAngz;
	/* 0xa8 */ float aimAngy;
	/* 0xac */ int throwAttackDamageID;
};

struct HeroCharge { // 0x20
	/* 0x00 */ vec4 padWindUp;
	/* 0x10 */ float groundSpeed;
	/* 0x14 */ int hitEdge;
	/* 0x18 */ int pad[2];
};

struct HeroColl { // 0x80
	/* 0x00 */ vec4 normal;
	/* 0x10 */ vec4 ip;
	/* 0x20 */ float top;
	/* 0x24 */ float bot;
	/* 0x28 */ float ideal_top;
	/* 0x2c */ float ideal_bot;
	/* 0x30 */ float idealRadius;
	/* 0x34 */ float radius;
	/* 0x38 */ float radiusSpeed;
	/* 0x3c */ MobyInstance *pContactMoby;
	/* 0x40 */ MobyInstance *pBumpMoby;
	/* 0x44 */ float bumpPushSpeed;
	/* 0x48 */ float distToWall;
	/* 0x4c */ float wallAng;
	/* 0x50 */ float wallSlope;
	/* 0x54 */ unsigned char wallIsCrate;
	/* 0x55 */ unsigned char wallIsMoby;
	/* 0x56 */ unsigned char contact;
	/* 0x57 */ unsigned char cpad;
	/* 0x58 */ float ledgeHeight;
	/* 0x5c */ float ledgeDist;
	/* 0x60 */ int atLedge;
	/* 0x64 */ MobyInstance *pWallJumpMoby;
	/* 0x68 */ int pad[2];
	/* 0x70 */ float radiusSqd;
};

struct HeroCommand { // 0xc
	/* 0x0 */ int state;
	/* 0x4 */ MobyInstance *pCurTarget;
	/* 0x8 */ int timer;
};

struct HeroDust { // 0x10
	/* 0x0 */ float vel;
	/* 0x4 */ float velvar;
	/* 0x8 */ int timer;
	/* 0xc */ short rate;
	/* 0xe */ short flags;
};

struct HeroDynamo { // 0x30
	/* 0x00 */ MobyInstance *pTarget;
	/* 0x04 */ int valid;
	/* 0x08 */ float targetScore;
	/* 0x0c */ int trigger;
	/* 0x10 */ MobyInstance *last_pTarget;
	/* 0x14 */ int pad[7];
};

struct HeroEyes { // 0x2d0
	/* 0x000 */ Manipulator manips[7];
	/* 0x1c0 */ Manipulator clankpackManips[4];
	/* 0x2c0 */ int blink_timer;
	/* 0x2c4 */ int blink_next;
	/* 0x2c8 */ int blink_frequency;
	/* 0x2cc */ short clankBlinkCountdown;
	/* 0x2ce */ short clankBlinkTime;
};

struct HeroFall { // 0x20
	/* 0x00 */ float gravity;
	/* 0x04 */ float xyDecel;
	/* 0x08 */ float xRotSpeed;
	/* 0x0c */ float yRotSpeed;
	/* 0x10 */ float xRotSpeedIdeal;
	/* 0x14 */ float yRotSpeedIdeal;
	/* 0x18 */ float glideTaperSpeed;
	/* 0x1c */ int pad[1];
};

struct HeroFireDir { // 0x50
	/* 0x00 */ mtx3 m;
	/* 0x30 */ vec4 v;
	/* 0x40 */ vec4f rot;
};

struct FpsCamVars { // 0x160
	/* 0x000 */ mtx3 mtx;
	/* 0x030 */ vec4 pos;
	/* 0x040 */ float z_rot;
	/* 0x044 */ float z_speed_current;
	/* 0x048 */ float z_speed_max_quick;
	/* 0x04c */ float z_speed_max_aim;
	/* 0x050 */ float z_accel_quick;
	/* 0x054 */ float z_accel_aim;
	/* 0x058 */ float z_target_slowness_factor_quick;
	/* 0x05c */ float z_target_slowness_factor_aim;
	/* 0x060 */ float y_rot;
	/* 0x064 */ float y_speed_current;
	/* 0x068 */ float y_speed_max;
	/* 0x06c */ float y_accel;
	/* 0x070 */ float y_target_slowness_factor;
	/* 0x074 */ float strafe_turn_factor;
	/* 0x078 */ float strafe_tilt_factor;
	/* 0x07c */ float max_target_angle;
	/* 0x080 */ int state;
	/* 0x084 */ short quick_turn_input_time;
	/* 0x086 */ short snap_hold_time;
	/* 0x088 */ float snap_input;
	/* 0x08c */ moby *pTarget;
	/* 0x090 */ vec4 target_last_pos;
	/* 0x0a0 */ vec4 target_vel;
	/* 0x0b0 */ float target_blend_fac;
	/* 0x0b4 */ float max_y_rot;
	/* 0x0b8 */ float min_y_rot;
	/* 0x0bc */ moby *pExcludeMoby;
	/* 0x0c0 */ vec4 ext_pos_ofs;
	/* 0x0d0 */ vec4f ext_rot_ofs;
	/* 0x0e0 */ short flags;
	/* 0x0e2 */ short allegiance;
	/* 0x0e4 */ void *special_target_func;
	/* 0x0e8 */ mtx3 *pWorldMtx;
	/* 0x0ec */ mtx3 *pWorldInvMtx;
	/* 0x0f0 */ vec4 facing_dir;
	/* 0x100 */ vec4 internal_facing_dir;
	/* 0x110 */ vec4 aim_pos;
	/* 0x120 */ float range;
	/* 0x124 */ float ext_extension;
	/* 0x128 */ float ext_entension_speed;
	/* 0x12c */ int cam_slot;
	/* 0x130 */ void *pHero;
	/* 0x134 */ float camRadius;
	/* 0x138 */ int camSettingsIndex;
	/* 0x13c */ int karma_pad;
	/* 0x140 */ vec4 prevCamPos;
	/* 0x150 */ int karma_pad2[4];
};

struct HeroFps { // 0x240
	/* 0x000 */ mtx3 worldMtx;
	/* 0x030 */ mtx3 worldInvMtx;
	/* 0x060 */ quat gunFPSQuat;
	/* 0x070 */ vec4 camEffVel;
	/* 0x080 */ vec4 camPos;
	/* 0x090 */ vec4 camDir;
	/* 0x0a0 */ FpsCamVars fVars;
	/* 0x200 */ float camYSpeed;
	/* 0x204 */ float camZSpeed;
	/* 0x208 */ float gunInterp;
	/* 0x20c */ float gunInterpSpeed;
	/* 0x210 */ int active;
	/* 0x214 */ float gunWithdrawSpeed;
	/* 0x218 */ float gunWithdrawDist;
	/* 0x21c */ float gunWithdrawIdeal;
	/* 0x220 */ float bobRot;
	/* 0x224 */ float bobRotSpeed;
	/* 0x228 */ float bobAmp;
	/* 0x22c */ float camHeroOfs;
	/* 0x230 */ float camHeroOfsSpeed;
	/* 0x234 */ int ignoreGroundHeight;
	/* 0x238 */ float reticulePulseAng;
	/* 0x23c */ int reticuleFadeInTimer;
};

struct HeroGrapple { // 0x30
	/* 0x00 */ float speed;
	/* 0x04 */ MobyInstance *pTarget;
	/* 0x08 */ int valid;
	/* 0x0c */ float timeToTarget;
	/* 0x10 */ float distToTarget;
	/* 0x14 */ int straightenOut;
	/* 0x18 */ int vehicle;
	/* 0x1c */ float cableLen;
	/* 0x20 */ float idealCableLen;
	/* 0x24 */ float targetScore;
	/* 0x28 */ int earlyAbort;
	/* 0x2c */ int pad[1];
};

struct HeroGrind { // 0x100
	/* 0x00 */ vec4 closestPoint;
	/* 0x10 */ vec4 rootPos;
	/* 0x20 */ vec4 lHandPos;
	/* 0x30 */ vec4 rHandPos;
	/* 0x40 */ vec4 closestPointSwitch;
	/* 0x50 */ vec4 rampTarget;
	/* 0x60 */ Path *pPath;
	/* 0x64 */ int curNode;
	/* 0x68 */ float curSegLen;
	/* 0x6c */ int valid;
	/* 0x70 */ int EOPtime;
	/* 0x74 */ float speed;
	/* 0x78 */ int pathDir;
	/* 0x7c */ float ang;
	/* 0x80 */ float slope;
	/* 0x84 */ int wrap;
	/* 0x88 */ float heroAngOfs;
	/* 0x8c */ int animDir;
	/* 0x90 */ int switching;
	/* 0x94 */ Path *pSwitchPath;
	/* 0x98 */ int switchCurNode;
	/* 0x9c */ float switchCurSegLen;
	/* 0xa0 */ int switchWrap;
	/* 0xa4 */ float slopeSpeed;
	/* 0xa8 */ int switchTime;
	/* 0xac */ int leanDir;
	/* 0xb0 */ float userSpeed;
	/* 0xb4 */ int grappleTrigger;
	/* 0xb8 */ int onRamp;
	/* 0xbc */ short rampTrigger;
	/* 0xbe */ short damage;
	/* 0xc0 */ int rampJumpQueued;
	/* 0xc4 */ int useRampJumpTarget;
	/* 0xc8 */ float rampJumpGravity;
	/* 0xcc */ float getHitSpeed;
	/* 0xd0 */ float aimDirOfs;
	/* 0xd4 */ float aimDirSpeed;
	/* 0xd8 */ MobyInstance *pTarget;
	/* 0xdc */ float centeringSpeed;
	/* 0xe0 */ float twirlRot;
	/* 0xe4 */ float twirlRotSpeed;
	/* 0xe8 */ float twirlCamRotz;
	/* 0xec */ short twirlTimer;
	/* 0xee */ short twirlCamOn;
	/* 0xf0 */ float twirlCamRotZspeed;
	/* 0xf4 */ COLL_DAM_OUT *cdo;
	/* 0xf8 */ int noGroundTime;
	/* 0xfc */ short turnDir;
	/* 0xfe */ short pad;
};

struct HeroGround { // 0xc0
	/* 0x00 */ vec4 normal;
	/* 0x10 */ vec4 waterNormal;
	/* 0x20 */ vec4 gravity;
	/* 0x30 */ vec4 point;
	/* 0x40 */ vec4 lastGoodPos;
	/* 0x50 */ vec4 externalBootGrav;
	/* 0x60 */ float feetHeights[2];
	/* 0x68 */ float pitchSlopes[2];
	/* 0x70 */ float rollSlopes[2];
	/* 0x78 */ float height;
	/* 0x7c */ float dist;
	/* 0x80 */ float slope;
	/* 0x84 */ float pitchSlope;
	/* 0x88 */ float rollSlope;
	/* 0x8c */ float angz;
	/* 0x90 */ float waterHeight;
	/* 0x94 */ float quicksandHeight;
	/* 0x98 */ int underWater;
	/* 0x9c */ MobyInstance *pMoby;
	/* 0xa0 */ int onGood;
	/* 0xa4 */ float speed;
	/* 0xa8 */ short magnetic;
	/* 0xaa */ short stickLanding;
	/* 0xac */ short offAny;
	/* 0xae */ short offGood;
	/* 0xb0 */ int oscillating;
	/* 0xb4 */ float oscPos1;
	/* 0xb8 */ float oscPos2;
	/* 0xbc */ int pad[1];
};

struct HeroHeadIdle { // 0x20
	/* 0x00 */ vec4f rotOffset;
	/* 0x10 */ int timer;
	/* 0x14 */ float gain;
	/* 0x18 */ float damp;
	/* 0x1c */ int pad[1];
};

struct HeroHotspots { // 0x10
	/* 0x0 */ short index;
	/* 0x2 */ unsigned char ice;
	/* 0x3 */ unsigned char magictele;
	/* 0x4 */ unsigned char water;
	/* 0x5 */ unsigned char lava;
	/* 0x6 */ unsigned char quicksand;
	/* 0x7 */ unsigned char magnetic;
	/* 0x8 */ unsigned char noStand;
	/* 0x9 */ unsigned char deathsand;
	/* 0xa */ unsigned char icewater;
	/* 0xb */ unsigned char groundType;
	/* 0xc */ int pad;
} __attribute__((aligned(16)));

struct HeroJoints { // 0x180
	/* 0x000 */ mtx4 gadgetMtxs[6];
};

struct HeroJumpNonParab { // 0x30
	/* 0x00 */ int startThrustTime;
	/* 0x04 */ int endThrustTime;
	/* 0x08 */ float thrustStartFrm;
	/* 0x0c */ float peakFrm;
	/* 0x10 */ int timeToPeakFrm;
	/* 0x14 */ HeroNPJumpThrustStage *thrustTable;
	/* 0x18 */ int thrustStageIndex;
	/* 0x1c */ int thrustStageTimer;
	/* 0x20 */ float thrust;
	/* 0x24 */ float chargeJumpThrust;
	/* 0x28 */ float descendGravity;
	/* 0x2c */ int pad;
};

struct HeroJump { // 0x100
	/* 0x00 */ HeroJumpNonParab nonParab;
	/* 0x30 */ vec4 takeoffPos;
	/* 0x40 */ vec4 snapJumpThrustVec;
	/* 0x50 */ vec4 snapJumpForwardVec;
	/* 0x60 */ float camHeight;
	/* 0x64 */ float turnSpeed;
	/* 0x68 */ float wallJumpXySpeed;
	/* 0x6c */ unsigned char land_timer;
	/* 0x6d */ unsigned char useNonParabAscent;
	/* 0x6e */ unsigned char descend;
	/* 0x6f */ unsigned char noGlide;
	/* 0x70 */ float maxFallSpeed;
	/* 0x74 */ float maxXySpeed;
	/* 0x78 */ float ideal_height;
	/* 0x7c */ short pushOffTime;
	/* 0x7e */ short framesToLand;
	/* 0x80 */ float up_thrust;
	/* 0x84 */ float up_thrust_total;
	/* 0x88 */ float coll_bot;
	/* 0x8c */ float ledgeJumpSpeed;
	/* 0x90 */ float snapJumpThrustAng;
	/* 0x94 */ float snapJumpForwardAng;
	/* 0x98 */ float peakFrm;
	/* 0x9c */ float landFrm;
	/* 0xa0 */ float gameLandFrm;
	/* 0xa4 */ int snapJumpDir;
	/* 0xa8 */ float snapJumpRunThrust;
	/* 0xac */ float snapJumpSpeed;
	/* 0xb0 */ vec4 wallJumpDir;
	/* 0xc0 */ vec4 wallJumpDirCur;
	/* 0xd0 */ float accel;
	/* 0xd4 */ float decel;
	/* 0xd8 */ float minHeight;
	/* 0xdc */ float maxHeight;
	/* 0xe0 */ float fallThresh;
	/* 0xe4 */ float animMayaScale;
	/* 0xe8 */ short maxUpTime;
	/* 0xea */ short bailoutSafetyTime;
	/* 0xec */ short particleTimer;
	/* 0xee */ short particleTimer2;
	/* 0xf0 */ float gravity;
	/* 0xf4 */ short minForwardThrust;
	/* 0xf6 */ short minTimeToGlide;
	/* 0xf8 */ short onIce;
	/* 0xfa */ short minTimeToFall;
	/* 0xfc */ unsigned char gloveAttackOk;
	/* 0xfd */ unsigned char strafingFlip;
	/* 0xfe */ unsigned char flipJumpOk;
	/* 0xff */ unsigned char doubleJumpOk;
};

struct HeroLedge { // 0x40
	/* 0x00 */ vec4 idealWallPos;
	/* 0x10 */ vec4 idealGrabPos;
	/* 0x20 */ float groundHeight;
	/* 0x24 */ float wallAngZ;
	/* 0x28 */ int valid;
	/* 0x2c */ float gravity;
	/* 0x30 */ float camHeight;
	/* 0x34 */ int flags;
	/* 0x38 */ MobyInstance *pMoby;
	/* 0x3c */ int pad;
};

struct HeroLockOn { // 0x50
	/* 0x00 */ vec4 strafeIdealVec;
	/* 0x10 */ MobyInstance *pMoby;
	/* 0x14 */ short strafing;
	/* 0x16 */ unsigned char strafingBack;
	/* 0x17 */ unsigned char strafingDir;
	/* 0x18 */ float strafeRot;
	/* 0x1c */ float strafeRotSpeed;
	/* 0x20 */ float backSpeed;
	/* 0x24 */ int strafeRotTimer;
	/* 0x28 */ short strafeLeftDampTimer;
	/* 0x2a */ short strafeRightDampTimer;
	/* 0x2c */ int strafeTurnDiffZero;
	/* 0x30 */ vec4 curRetPos;
	/* 0x40 */ MobyInstance *curRetMoby;
	/* 0x44 */ float fadeInterp;
	/* 0x48 */ float retRot;
	/* 0x4c */ float strafeTurnDiff;
};

struct HeroMobys { // 0x10
	/* 0x0 */ MobyInstance *ground;
	/* 0x4 */ MobyInstance *hero;
	/* 0x8 */ int pad[2];
};

struct HeroMove { // 0xa0
	/* 0x00 */ vec4 behavior;
	/* 0x10 */ vec4 external;
	/* 0x20 */ vec4 actual;
	/* 0x30 */ vec4 actualFromBehavior;
	/* 0x40 */ vec4 actualFromBehaviorGrav;
	/* 0x50 */ vec4 actualFromBehavior2D;
	/* 0x60 */ vec4 actualFromExternal;
	/* 0x70 */ vec4 taper;
	/* 0x80 */ float speed;
	/* 0x84 */ float speed2D;
	/* 0x88 */ float forwardSpeed;
	/* 0x8c */ float ascent;
	/* 0x90 */ float zSpeed;
	/* 0x94 */ float externalSpeed;
	/* 0x98 */ int pad[2];
};

struct HeroPullShot { // 0x30
	/* 0x00 */ MobyInstance *pTarget;
	/* 0x04 */ int valid;
	/* 0x08 */ float targetScore;
	/* 0x0c */ int connected;
	/* 0x10 */ int pad[8];
};

struct HeroQueuedSound { // 0x8
	/* 0x0 */ short active;
	/* 0x2 */ short sound;
	/* 0x4 */ short timer;
	/* 0x6 */ short flags;
};

struct HeroQuickSand { // 0x10
	/* 0x0 */ int timesFallen;
	/* 0x4 */ int pad[3];
};

struct HeroShadow { // 0x28
	/* 0x00 */ float slope;
	/* 0x04 */ float plane;
	/* 0x08 */ float range;
	/* 0x0c */ int sample_id;
	/* 0x10 */ int pad[2];
	/* 0x18 */ float sample_pos[4];
};

struct HeroSpecialIdleDef { // 0x10
	/* 0x0 */ int anim;
	/* 0x4 */ float frequency;
	/* 0x8 */ float minRepeatTime;
	/* 0xc */ int repeatTimer;
};

struct HeroSurf { // 0x30
	/* 0x00 */ float sinkDepth;
	/* 0x04 */ float sinkRate;
	/* 0x08 */ int minSwimTimer;
	/* 0x0c */ float surfHeight;
	/* 0x10 */ float surfHeightSpeed;
	/* 0x14 */ MobyInstance *pIceCube;
	/* 0x18 */ float bobt;
	/* 0x1c */ float bobz;
	/* 0x20 */ float swingAng1;
	/* 0x24 */ float swingAng2;
	/* 0x28 */ int pad[2];
};

struct HeroSwim { // 0x50
	/* 0x00 */ vec4 padWindUp;
	/* 0x10 */ int diveTime;
	/* 0x14 */ float bankSpeed;
	/* 0x18 */ float pitchSpeed;
	/* 0x1c */ float yawSpeed;
	/* 0x20 */ int bubbleTimer;
	/* 0x24 */ int minSwimTimer;
	/* 0x28 */ short chargeBubbleTimer;
	/* 0x2a */ short soundTimer;
	/* 0x2c */ float buoyancySpeed;
	/* 0x30 */ short padUpTime;
	/* 0x32 */ short padDownTime;
	/* 0x34 */ short ring_timer;
	/* 0x36 */ short drop_timer;
	/* 0x38 */ short wake_timer;
	/* 0x3a */ short plunge_bubbles;
	/* 0x3c */ short solidRiseTimer;
	/* 0x3e */ short riseTimer;
	/* 0x40 */ int riseTapCnt;
	/* 0x44 */ int timeRiseLastPressed;
	/* 0x48 */ int pad[2];
};

struct HeroSwing { // 0x40
	/* 0x00 */ MobyInstance *pNextTarget;
	/* 0x04 */ MobyInstance *pTarget;
	/* 0x08 */ float targetScore;
	/* 0x0c */ short connected;
	/* 0x0e */ unsigned char valid;
	/* 0x0f */ unsigned char qSwitchMe;
	/* 0x10 */ float idealRadius;
	/* 0x14 */ float curCableLen;
	/* 0x18 */ float radialSpeed;
	/* 0x1c */ float forwardAng;
	/* 0x20 */ float gravity;
	/* 0x24 */ float firstSwingSpeed;
	/* 0x28 */ float alignRotSpeed;
	/* 0x2c */ short animScaleQueued;
	/* 0x2e */ short firstSwing;
	/* 0x30 */ float swingElv;
	/* 0x34 */ float radialGain;
	/* 0x38 */ float radialDamp;
	/* 0x3c */ float radialLimit;
};

struct HeroTailIdle { // 0x50
	/* 0x00 */ vec4f rotOffsets[4];
	/* 0x40 */ int timers[4];
};

struct HeroThrust { // 0x10
	/* 0x0 */ float ideal;
	/* 0x4 */ float actual;
	/* 0x8 */ int pad[2];
};

struct HeroTimers { // 0xb4
	/* 0x00 */ int state;
	/* 0x04 */ int stateType;
	/* 0x08 */ int subState;
	/* 0x0c */ int animState;
	/* 0x10 */ int stickOn;
	/* 0x14 */ int stickOff;
	/* 0x18 */ short noLedge;
	/* 0x1a */ short allowQuickSelect;
	/* 0x1c */ int firing;
	/* 0x20 */ int moveModifierTimer;
	/* 0x24 */ int boltMultTimer;
	/* 0x28 */ int wallJumpOk;
	/* 0x2c */ short postHitInvinc;
	/* 0x2e */ short ignoreHeroColl;
	/* 0x30 */ short collOff;
	/* 0x32 */ short invisible;
	/* 0x34 */ short slide;
	/* 0x36 */ short bezerker;
	/* 0x38 */ short noWallJump;
	/* 0x3a */ short noJumps;
	/* 0x3c */ short boxBreaking;
	/* 0x3e */ short noMag;
	/* 0x40 */ short noChargeJump;
	/* 0x42 */ short resurrectWait;
	/* 0x44 */ int timeSinceStrafe;
	/* 0x48 */ short noHackerSwitch;
	/* 0x4a */ short noInput;
	/* 0x4c */ short noJumpLookBack;
	/* 0x4e */ short noShockAbort;
	/* 0x50 */ short stuck;
	/* 0x52 */ short noSwing;
	/* 0x54 */ short noWaterJump;
	/* 0x56 */ short noWaterDive;
	/* 0x58 */ short facialExpression;
	/* 0x5a */ short idle;
	/* 0x5c */ short bumpPushing;
	/* 0x5e */ short lookButton;
	/* 0x60 */ short edgeStop;
	/* 0x62 */ short clankRedEye;
	/* 0x64 */ short edgePath;
	/* 0x66 */ short magSlope;
	/* 0x68 */ short ledgeCamAdj;
	/* 0x6a */ short screenFlashRed;
	/* 0x6c */ short holdDeathPose;
	/* 0x6e */ short strafeMove;
	/* 0x70 */ short noRaisedGunArm;
	/* 0x72 */ short noExternalRot;
	/* 0x74 */ short screenFlashOn;
	/* 0x76 */ short screenFadeOn;
	/* 0x78 */ int lastVehicleTimer;
	/* 0x7c */ float gadgetRefire;
	/* 0x80 */ int timeAlive;
	/* 0x84 */ int noFpsCamTimer;
	/* 0x88 */ int endDeathEarly;
	/* 0x8c */ short forceGlide;
	/* 0x8e */ short noGrind;
	/* 0x90 */ short instaGrind;
	/* 0x92 */ short noCamInputTimer;
	/* 0x94 */ short postTeleportTimer;
	/* 0x96 */ short multiKillTimer;
	/* 0x98 */ short armorLevelTimer;
	/* 0x9a */ short damageMuliplierTimer;
	/* 0x9c */ int powerupEffectTimer;
	/* 0xa0 */ short juggernautFadeTimer;
	/* 0xa2 */ short onFireTimer;
	/* 0xa4 */ short acidTimer;
	/* 0xa6 */ short freezeTimer;
	/* 0xa8 */ short noHelmTimer;
	/* 0xaa */ short elecTimer;
	/* 0xac */ short boltDistMulTimer;
	/* 0xae */ short explodeTimer;
	/* 0xb0 */ short noDeathTimer;
	/* 0xb2 */ short invincibilityTimer;
};

struct HeroTrack { // 0x60
	/* 0x00 */ vec4 idealPos;
	/* 0x10 */ vec4f idealRot;
	/* 0x20 */ vec4 idealWallPos;
	/* 0x30 */ vec4f idealWallRot;
	/* 0x40 */ vec4 prevVel;
	/* 0x50 */ MobyInstance *pMoby;
	/* 0x54 */ int flags;
	/* 0x58 */ int pad[2];
};

struct HeroTractorBeam { // 0x10
	/* 0x0 */ MobyInstance *pTarget;
	/* 0x4 */ float zRotOfs;
	/* 0x8 */ float zRotSpeed;
	/* 0xc */ float xySpeed;
};

struct HeroTurn { // 0x20
	/* 0x00 */ vec4 idealVec;
	/* 0x10 */ float ideal;
	/* 0x14 */ float speed;
	/* 0x18 */ float diff;
	/* 0x1c */ int pad;
};

struct HeroTweaker { // 0xb0
	/* 0x00 */ Manipulator manip;
	/* 0x40 */ vec4f rot;
	/* 0x50 */ vec4f speed;
	/* 0x60 */ vec4f target;
	/* 0x70 */ vec4 trans;
	/* 0x80 */ vec4 transSpeed;
	/* 0x90 */ vec4 transTarget;
	/* 0xa0 */ short joint;
	/* 0xa2 */ short whichMoby;
	/* 0xa4 */ float gain;
	/* 0xa8 */ float damp;
	/* 0xac */ float scale;
};

struct HeroWalk { // 0x30
	/* 0x00 */ vec4 idealTurnVec;
	/* 0x10 */ float iceMotionDotProduct;
	/* 0x14 */ float lastGroundSlope;
	/* 0x18 */ float idealTurnAng;
	/* 0x1c */ unsigned char ideal_motion;
	/* 0x1d */ unsigned char skateThrust;
	/* 0x1e */ unsigned char long_trans;
	/* 0x1f */ unsigned char qturning;
	/* 0x20 */ int idealAngSet;
	/* 0x24 */ int pad[3];
};

struct HeroWalkToPos { // 0x30
	/* 0x00 */ vec4 idealPos;
	/* 0x10 */ vec4f idealRot;
	/* 0x20 */ int abortOnArrival;
	/* 0x24 */ int walkToTeleport;
	/* 0x28 */ int teleportWaitTime;
	/* 0x2c */ MobyInstance *pTeleTarget;
};

struct HeroWeaponPosRec { // 0x100
	/* 0x00 */ mtx4 fpGunMtx[2];
	/* 0x80 */ mtx4 tpGunMtx[2];
};

struct HeroWind { // 0x20
	/* 0x00 */ vec4 vel;
	/* 0x10 */ float speed;
	/* 0x14 */ float angy;
	/* 0x18 */ float angz;
	/* 0x1c */ int pad[1];
};

struct HeroZip { // 0x50
	/* 0x00 */ vec4 closestPoint;
	/* 0x10 */ vec4 idealVec;
	/* 0x20 */ Path *pPath;
	/* 0x24 */ int curNode;
	/* 0x28 */ float curSegLen;
	/* 0x2c */ int valid;
	/* 0x30 */ int EOPtime;
	/* 0x34 */ float speed;
	/* 0x38 */ int pathDir;
	/* 0x3c */ int wrap;
	/* 0x40 */ float ang;
	/* 0x44 */ float slope;
	/* 0x48 */ float centeringSpeed;
	/* 0x4c */ int pad[1];
};

struct tNW_PlayerStateMessage { // 0x1c
	/* 0x00 */ unsigned char netPlayerIndex;
	/* 0x01 */ unsigned char newState;
	/* 0x02 */ unsigned char seqNum;
	/* 0x03 */ unsigned char frame;
	/* 0x04 */ vec3 pos;
	/* 0x10 */ vec3 rot;
};

struct Hero : Guber { // 0x2fe0
	/* 0x0020 */ mtx4 mtx;
	/* 0x0060 */ mtx4 invMtx;
	/* 0x00a0 */ vec4 pos;
	/* 0x00b0 */ vec4f rot;
	/* 0x00c0 */ vec4f rotSpeed;
	/* 0x00d0 */ vec4 sphereCenter;
	/* 0x00e0 */ vec4 missileTarget;
	/* 0x00f0 */ vec4 cg;
	/* 0x0100 */ vec4f mtxFxScale;
	/* 0x0110 */ vec4 lastPos;
	/* 0x0120 */ vec4f stickInput;
	/* 0x0130 */ HeroMove move;
	/* 0x01d0 */ HeroColl coll;
	/* 0x0250 */ HeroGround ground;
	/* 0x0310 */ HeroTrack track;
	/* 0x0370 */ HeroTimers timers;
	/* 0x0430 */ HeroHotspots hotspots;
	/* 0x0440 */ HeroGrind grind;
	/* 0x0540 */ HeroZip zip;
	/* 0x0590 */ HeroFireDir fireDir;
	/* 0x05e0 */ HeroLockOn lockOn;
	/* 0x0630 */ HeroMobys mobys;
	/* 0x0640 */ HeroAnim anim;
	/* 0x0660 */ HeroJoints joints;
	/* 0x07e0 */ HeroAnimLayers animLayers;
	/* 0x0820 */ HeroTweaker tweaker[18];
	/* 0x1480 */ HeroShadow shadow;
	/* 0x14b0 */ HeroEyes eyes;
	/* 0x1780 */ HeroThrust thrust;
	/* 0x1790 */ HeroTurn turn;
	/* 0x17b0 */ HeroAttack attack;
	/* 0x1860 */ HeroHeadIdle headIdle;
	/* 0x1880 */ HeroTailIdle tailIdle;
	/* 0x18d0 */ HeroFps fps;
	/* 0x1b10 */ HeroWeaponPosRec weaponPosRec;
	/* 0x1c10 */ HeroWalkToPos walkToPos;
	/* 0x1c40 */ HeroSurf surf;
	/* 0x1c70 */ HeroWalk walk;
	/* 0x1ca0 */ HeroJump jump;
	/* 0x1da0 */ HeroLedge ledge;
	/* 0x1de0 */ HeroTractorBeam tractorBeam;
	/* 0x1df0 */ HeroCharge charge;
	/* 0x1e10 */ HeroSwim swim;
	/* 0x1e60 */ HeroWind wind;
	/* 0x1e80 */ HeroFall fall;
	/* 0x1ea0 */ HeroGrapple grapple;
	/* 0x1ed0 */ HeroSwing swing;
	/* 0x1f10 */ HeroPullShot pullShot;
	/* 0x1f40 */ HeroDynamo dynamo;
	/* 0x1f70 */ HeroQuickSand quicksand;
	/* 0x1f80 */ HeroDust dust;
	/* 0x1f90 */ HeroCommand command;
	/* 0x1f9c */ TargetVars target;
	/* 0x2030 */ MotionBlur motionBlur;
	/* 0x2180 */ MotionBlur wrenchMotionBlur;
	/* 0x22d0 */ Gadget gadgets[6];
	/* 0x24b0 */ int assGadgets[6];
	/* 0x24d0 */ vec4 prevHandPos;
	/* 0x24e0 */ vec4 gadgetGlowPos[8];
	/* 0x2560 */ int gadgetGlowRGBA[8];
	/* 0x2580 */ float gadgetGlowSize[8];
	/* 0x25a0 */ float gadgetGlowOfs[8];
	/* 0x25c0 */ short gadgetGlowCnt;
	/* 0x25c4 */ float heroSpeedAdjuster;
	/* 0x25c8 */ unsigned char playerPostDrawFxRegistered;
	/* 0x25c9 */ unsigned char playerPostPreDrawFxRegistered;
	/* 0x25ca */ unsigned char playerFontDrawRegistered;
	/* 0x25cc */ int state;
	/* 0x25d0 */ int subState;
	/* 0x25d4 */ int stateType;
	/* 0x25d8 */ int previousState;
	/* 0x25dc */ int previousType;
	/* 0x25e0 */ int previousStateTimer;
	/* 0x25e4 */ int prePreviousState;
	/* 0x25e8 */ int prePreviousType;
	/* 0x25ec */ int stateHistory[8];
	/* 0x260c */ int stateTypeHistory[8];
	/* 0x262c */ int stateTimerHistory[8];
	/* 0x264c */ int stateHistoryLen;
	/* 0x2650 */ int effectsLevel;
	/* 0x2654 */ float minDistToLocalCamera;
	/* 0x2658 */ unsigned char cycleFiring;
	/* 0x2659 */ unsigned char gravityType;
	/* 0x265a */ unsigned char firing;
	/* 0x265c */ int clankIdleTimer;
	/* 0x2660 */ unsigned char raisedGunArm;
	/* 0x2661 */ unsigned char inShallowWater;
	/* 0x2662 */ unsigned char invisible;
	/* 0x2663 */ unsigned char hideWeapon;
	/* 0x2664 */ unsigned char gadgetsOff;
	/* 0x2665 */ unsigned char gadgetNotReady;
	/* 0x2666 */ unsigned char wrenchOnly;
	/* 0x2667 */ unsigned char holdingDeathAnim;
	/* 0x2668 */ unsigned char hideWrench;
	/* 0x2669 */ unsigned char spawnBoltsToMe;
	/* 0x266a */ unsigned char aiFollowingMe;
	/* 0x266b */ unsigned char forceWrenchSwitch;
	/* 0x266c */ unsigned char forceSwingSwitch;
	/* 0x266d */ unsigned char isLocal;
	/* 0x266e */ unsigned char inBaseHack;
	/* 0x266f */ unsigned char shieldTrigger;
	/* 0x2670 */ unsigned char curSeg;
	/* 0x2671 */ unsigned char handGadgetType;
	/* 0x2672 */ unsigned char externalUpdate;
	/* 0x2674 */ int hudGadgets[6];
	/* 0x268c */ int desiredGadgets[6];
	/* 0x26a4 */ int preemptedGadgets[6];
	/* 0x26bc */ int restoreGadgetFlags[6];
	/* 0x26d4 */ int loadingGadget;
	/* 0x26d8 */ int hackerRemovedGadget;
	/* 0x26dc */ unsigned char currIdleAnim;
	/* 0x26dd */ unsigned char machineGunFire;
	/* 0x26e0 */ int lastHackTime;
	/* 0x26e4 */ GadgetBox *pGadgetBox;
	/* 0x26e8 */ short minesPendingExplode[2];
	/* 0x26f0 */ vec4 failsafePosRing[32];
	/* 0x28f0 */ float rotZRing[32];
	/* 0x2970 */ mtx3 gadgetRotRing[16];
	/* 0x2c70 */ int rotZringIndex;
	/* 0x2c74 */ int rotZringValidSize;
	/* 0x2c78 */ int failsafeRingIndex;
	/* 0x2c7c */ int failsafeRingValidSize;
	/* 0x2c80 */ int gadgetRotRingIndex;
	/* 0x2c84 */ int gadgetRotRingValidSize;
	/* 0x2c88 */ int cameraPosRing[8];
	/* 0x2ca8 */ int cameraRotRing[8];
	/* 0x2cc8 */ int camRingIndex;
	/* 0x2ccc */ int camRingValidSize;
	/* 0x2cd0 */ vec4 camPos;
	/* 0x2ce0 */ vec4f camRot;
	/* 0x2cf0 */ mtx3 camUMtx;
	/* 0x2d20 */ HeroQueuedSound queuedSounds[2];
	/* 0x2d30 */ int loopingSounds[9];
	/* 0x2d54 */ moby *loopingSoundMobys[9];
	/* 0x2d78 */ HeroSpecialIdleDef SpecialIdles[4];
	/* 0x2db8 */ int specialIdleHistory[4];
	/* 0x2dc8 */ int specialIdleHistoryIndex;
	/* 0x2dcc */ int specialIdleHistorySize;
	/* 0x2dd0 */ int specialIdleID;
	/* 0x2dd4 */ int firingAnim;
	/* 0x2dd8 */ int firingGadget;
	/* 0x2ddc */ int desiredCam;
	/* 0x2de0 */ unsigned long savedLights;
	/* 0x2de8 */ int lightFxOn;
	/* 0x2dec */ MobyInstance *pHeadTargetMoby;
	/* 0x2df0 */ MobyInstance *pSheepMoby;
	/* 0x2df4 */ moby *pWhoHitMe;
	/* 0x2df8 */ Hero *pWhoSheepedMe;
	/* 0x2dfc */ moby *pAcidDamager;
	/* 0x2e00 */ int acidDamagerGadgetId;
	/* 0x2e04 */ unsigned char useAcidDamagerGadgetId;
	/* 0x2e05 */ unsigned char sheepMeLongTime;
	/* 0x2e08 */ float stickStrength;
	/* 0x2e0c */ float stickRawAngle;
	/* 0x2e10 */ int targetModeDelay;
	/* 0x2e14 */ float waterDepth;
	/* 0x2e18 */ short edgePath;
	/* 0x2e1c */ float glideDescentRate;
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
	/* 0x2e98 */ moby *recentTargets[4];
	/* 0x2ea8 */ int lastWeaponTargetTime;
	/* 0x2eac */ tNW_GetHitMessage getHitMessage;
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
	/* 0x2f28 */ tNW_Player *pNetPlayer;
	/* 0x2f2c */ tNW_PlayerStateMessage newStateMessage;
	/* 0x2f48 */ int timeOfReceivedStateMsg;
	/* 0x2f4c */ moby *lastVehicleMoby;
	/* 0x2f50 */ int iLastVehicleOffTime;
	/* 0x2f54 */ moby *pLastGrindRail;
	/* 0x2f58 */ float closestCamDistSqr;
	/* 0x2f5c */ int bSphereVis;
	/* 0x2f60 */ float m_shortTermLinkDirtyTime;
	/* 0x2f64 */ float m_accumLinkDirtyTime;
	/* 0x2f70 */ vec4 initialPos;
	/* 0x2f80 */ vec4f initialRot;
	/* 0x2f90 */ float stashedWallCheckHeight;
	/* 0x2f94 */ float stashedWallCheckDist;
	/* 0x2f98 */ float stashedWallDist;
	/* 0x2f9c */ int lookModeTimeout;
	/* 0x2fa0 */ int lookModeDelay;
	/* 0x2fa4 */ int baseExperience;
	/* 0x2fa8 */ int Experience;
	/* 0x2fac */ int currentAcumXp;
	/* 0x2fb0 */ float damageMultipler;
	/* 0x2fb4 */ int armorLevel;
	/* 0x2fb8 */ unsigned char limitBreakFull;
	/* 0x2fbc */ float limitBreakPercentage;
	/* 0x2fc0 */ float movementSpeedModifier;
	/* 0x2fc4 */ unsigned char grindRailWeaponLock;
	/* 0x2fc5 */ unsigned char currArmAnim;
	/* 0x2fc6 */ short activePadFrame;
	/* 0x2fc8 */ unsigned char alreadyPlayedNoAmmoClick;
	/* 0x2fc9 */ unsigned char sceneInvis;
	/* 0x2fca */ unsigned char ninjaCheatActive;
	/* 0x2fcb */ unsigned char hadWind;
	/* 0x2fcc */ moby *pWrenchReplacement;
	/* 0x2fd0 */ int startLimitBreakDiff;
};

struct CamBlenderPolarQuat { // 0x70
	/* 0x00 */ PolarSm orgPol;
	/* 0x0c */ int interpFrames;
	/* 0x10 */ float interpMaxInv;
	/* 0x14 */ int reqInterpFrames;
	/* 0x20 */ vec4 fwd;
	/* 0x30 */ vec4 up;
	/* 0x40 */ quat orgQuat;
	/* 0x50 */ vec4 pos;
	/* 0x60 */ quat q;
};

struct CamBlenderPosQuat { // 0x60
	/* 0x00 */ float quatInterpFac;
	/* 0x04 */ float quatInterpAdd;
	/* 0x08 */ float reqQuatInterpAdd;
	/* 0x0c */ float reqQuatInterpInit;
	/* 0x10 */ float posInterpFac;
	/* 0x14 */ float posInterpAdd;
	/* 0x18 */ float reqPosInterpAdd;
	/* 0x1c */ float reqPosInterpInit;
	/* 0x20 */ quat orgQuat;
	/* 0x30 */ vec4 orgPos;
	/* 0x40 */ vec4 pos;
	/* 0x50 */ quat q;
};

struct CamBlenderData { // 0xd0
	/* 0x00 */ CamBlenderPosQuat posData;
	/* 0x60 */ CamBlenderPolarQuat polarData;
};

struct CamBlender { // 0xe0
	/* 0x00 */ short state;
	/* 0x02 */ unsigned char type;
	/* 0x03 */ unsigned char reqType;
	/* 0x10 */ CamBlenderData blendData;
};

struct CameraExternal { // 0x10
	/* 0x0 */ vec4 move;
};

struct CameraFov { // 0x30
	/* 0x00 */ float speed;
	/* 0x04 */ float ideal;
	/* 0x08 */ float actual;
	/* 0x0c */ float gain;
	/* 0x10 */ float damp;
	/* 0x14 */ float limit;
	/* 0x18 */ unsigned char changeType;
	/* 0x19 */ unsigned char state;
	/* 0x1a */ short timer;
	/* 0x1c */ float timerInv;
	/* 0x20 */ float init;
	/* 0x24 */ float pad[3];
};

struct CameraHeroData { // 0x160
	/* 0x000 */ mtx4 mtx;
	/* 0x040 */ vec4 pos;
	/* 0x050 */ vec4f rot;
	/* 0x060 */ vec4 cg;
	/* 0x070 */ vec4 moveActualFromExternal;
	/* 0x080 */ vec4 groundGravity;
	/* 0x090 */ vec4 jumpGravity;
	/* 0x0a0 */ vec4 sphereCenter;
	/* 0x0b0 */ mtx3 fpsCamMtx;
	/* 0x0e0 */ vec4 fpsCamPos;
	/* 0x0f0 */ MobyInstance *pMoby;
	/* 0x0f4 */ MobyInstance *vehicleMoby;
	/* 0x0f8 */ MobyInstance *groundMoby;
	/* 0x0fc */ int desiredCam;
	/* 0x100 */ int state;
	/* 0x104 */ int stateType;
	/* 0x108 */ int previousState;
	/* 0x10c */ float moveSpeed;
	/* 0x110 */ float moveSpeed2D;
	/* 0x114 */ float groundDist;
	/* 0x118 */ float groundWaterHeight;
	/* 0x11c */ int groundOnGood;
	/* 0x120 */ short groundOffAny;
	/* 0x122 */ short groundOffGood;
	/* 0x124 */ short groundMagnetic;
	/* 0x126 */ short lockOnStrafing;
	/* 0x128 */ short jumpFramesToLand;
	/* 0x12a */ unsigned char jumpDescend;
	/* 0x12b */ unsigned char critterMode;
	/* 0x12c */ unsigned char multiplayer;
	/* 0x12d */ unsigned char fpsActive;
	/* 0x12e */ unsigned char hotSpotLava;
	/* 0x12f */ unsigned char hotSpotDeathSand;
	/* 0x130 */ unsigned char hotSpotQuickSand;
	/* 0x131 */ unsigned char hotSpotIceWater;
	/* 0x132 */ unsigned char hotSpotWater;
	/* 0x133 */ unsigned char aiFollowingMe;
	/* 0x134 */ PAD *pPad;
	/* 0x138 */ MobyInstance *pSwingTargetMoby;
	/* 0x13c */ float swingForwardAng;
	/* 0x140 */ float swingIdealRadius;
	/* 0x144 */ int timersLedgeCamAdj;
	/* 0x148 */ float ledgeWallAngZ;
	/* 0x14c */ int EOPtime;
	/* 0x150 */ Path *pPath;
	/* 0x154 */ int pad[3];
};

struct CameraStatics { // 0xf0
	/* 0x00 */ vec3 heroNoJump;
	/* 0x0c */ float heroLastZ;
	/* 0x10 */ float heroLastZSpeed;
	/* 0x20 */ vec4 heroUp;
	/* 0x30 */ vec4 heroUpActual;
	/* 0x40 */ vec4 heroUpLast;
	/* 0x50 */ vec4 heroUpSpeed;
	/* 0x60 */ vec4 heroLastPos;
	/* 0x70 */ vec4 heroMoveVec;
	/* 0x80 */ vec4 heroMoveVec2D;
	/* 0x90 */ vec4 heroMoveVecUp;
	/* 0xa0 */ float heroSpeed;
	/* 0xa4 */ float heroSpeed2D;
	/* 0xa8 */ float heroSpeedUp;
	/* 0xac */ float heroLastRotZ[5];
	/* 0xc0 */ int hotspot;
	/* 0xc4 */ moby *pCamColl;
	/* 0xc8 */ float fadeSpeed;
	/* 0xcc */ float fadeIdeal;
	/* 0xd0 */ int fadeTimer;
	/* 0xd4 */ float flashInSpeed;
	/* 0xd8 */ float flashOutSpeed;
	/* 0xdc */ float flashIdeal;
	/* 0xe0 */ int flashTimer;
	/* 0xe4 */ moby *boss;
	/* 0xe8 */ int bossTimer;
};

struct CameraWidget { // 0x14
	/* 0x00 */ UpdateCam *pCam;
	/* 0x04 */ moby *semaphore;
	/* 0x08 */ float closest;
	/* 0x0c */ float interp;
	/* 0x10 */ void *preFunc;
};

struct GAMECAMERA { // 0x470
	/* 0x000 */ vec4 pos;
	/* 0x010 */ vec4f rot;
	/* 0x020 */ CameraShake shake;
	/* 0x030 */ CameraShake shakeFwd;
	/* 0x040 */ CameraShake shakeTilt;
	/* 0x050 */ UpdateCam *pCurrentUpdCam;
	/* 0x054 */ UpdateCam *pLastUpdCam;
	/* 0x060 */ CameraStatics camStatics;
	/* 0x150 */ CameraHeroData camHeroData;
	/* 0x2b0 */ CamBlender blender;
	/* 0x390 */ mtx3 uMtx;
	/* 0x3c0 */ mtx4 bsMtx;
	/* 0x400 */ CameraWidget widget;
	/* 0x420 */ CameraExternal external;
	/* 0x430 */ CameraFov fov;
	/* 0x460 */ int CamUnderWater;
	/* 0x464 */ int camTimer;
	/* 0x468 */ int disableBlendTimer;
};

struct RemoteHero : Hero { // 0x3ab0
	/* 0x2fe0 */ GAMECAMERA DummyCamera;
	/* 0x3450 */ PAD RemotePad;
	/* 0x3a10 */ unsigned char completedEnoughUpdates;
	/* 0x3a11 */ unsigned char rotOutOfSyncLastUpdate;
	/* 0x3a12 */ unsigned char padFrameChunksReceived;
	/* 0x3a13 */ unsigned char posOutOfSyncLastUpdate;
	/* 0x3a14 */ unsigned char stateAtSyncFrame;
	/* 0x3a20 */ vec4 receivedSyncPos;
	/* 0x3a30 */ vec4 posAtSyncFrame;
	/* 0x3a40 */ vec4 syncPosDifference;
	/* 0x3a50 */ vec4f receivedSyncRot;
	/* 0x3a60 */ vec4f rotAtSyncFrame;
	/* 0x3a70 */ float interpVel;
	/* 0x3a74 */ float syncRotDifference;
	/* 0x3a78 */ int flags;
	/* 0x3a7c */ int sequenceIdOfSyncData;
	/* 0x3a80 */ int receivedState;
	/* 0x3a90 */ vec4 remoteCorrectionVel;
	/* 0x3aa0 */ float remoteCorrectionRotVel;
	/* 0x3aa4 */ unsigned char syncFrameOffset;
};

#endif
