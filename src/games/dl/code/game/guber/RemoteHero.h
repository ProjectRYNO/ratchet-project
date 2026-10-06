#ifndef GUBER_REMOTEHERO_H
#define GUBER_REMOTEHERO_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:4024; ghidra-layout.
typedef struct { // 0x30
    /* 0x00 */ float speed;
    /* 0x04 */ float ideal;
    /* 0x08 */ float actual;
    /* 0x0c */ float gain;
    /* 0x10 */ float damp;
    /* 0x14 */ float limit;
    /* 0x18 */ char changeType;
    /* 0x19 */ char state;
    /* 0x1a */ short int timer;
    /* 0x1c */ float timerInv;
    /* 0x20 */ float init;
    /* 0x24 */ float pad[3];
} CameraFov;

// dltypes.txt:4460; ghidra-layout.
typedef struct { // 0xb4
    /* 0x00 */ int state;
    /* 0x04 */ int stateType;
    /* 0x08 */ int subState;
    /* 0x0c */ int animState;
    /* 0x10 */ int stickOn;
    /* 0x14 */ int stickOff;
    /* 0x18 */ short int noLedge;
    /* 0x1a */ short int allowQuickSelect;
    /* 0x1c */ int firing;
    /* 0x20 */ int moveModifierTimer;
    /* 0x24 */ int boltMultTimer;
    /* 0x28 */ int wallJumpOk;
    /* 0x2c */ short int postHitInvinc;
    /* 0x2e */ short int ignoreHeroColl;
    /* 0x30 */ short int collOff;
    /* 0x32 */ short int invisible;
    /* 0x34 */ short int slide;
    /* 0x36 */ short int bezerker;
    /* 0x38 */ short int noWallJump;
    /* 0x3a */ short int noJumps;
    /* 0x3c */ short int boxBreaking;
    /* 0x3e */ short int noMag;
    /* 0x40 */ short int noChargeJump;
    /* 0x42 */ short int resurrectWait;
    /* 0x44 */ int timeSinceStrafe;
    /* 0x48 */ short int noHackerSwitch;
    /* 0x4a */ short int noInput;
    /* 0x4c */ short int noJumpLookBack;
    /* 0x4e */ short int noShockAbort;
    /* 0x50 */ short int stuck;
    /* 0x52 */ short int noSwing;
    /* 0x54 */ short int noWaterJump;
    /* 0x56 */ short int noWaterDive;
    /* 0x58 */ short int facialExpression;
    /* 0x5a */ short int idle;
    /* 0x5c */ short int bumpPushing;
    /* 0x5e */ short int lookButton;
    /* 0x60 */ short int edgeStop;
    /* 0x62 */ short int clankRedEye;
    /* 0x64 */ short int edgePath;
    /* 0x66 */ short int magSlope;
    /* 0x68 */ short int ledgeCamAdj;
    /* 0x6a */ short int screenFlashRed;
    /* 0x6c */ short int holdDeathPose;
    /* 0x6e */ short int strafeMove;
    /* 0x70 */ short int noRaisedGunArm;
    /* 0x72 */ short int noExternalRot;
    /* 0x74 */ short int screenFlashOn;
    /* 0x76 */ short int screenFadeOn;
    /* 0x78 */ int lastVehicleTimer;
    /* 0x7c */ float gadgetRefire;
    /* 0x80 */ int timeAlive;
    /* 0x84 */ int noFpsCamTimer;
    /* 0x88 */ int endDeathEarly;
    /* 0x8c */ short int forceGlide;
    /* 0x8e */ short int noGrind;
    /* 0x90 */ short int instaGrind;
    /* 0x92 */ short int noCamInputTimer;
    /* 0x94 */ short int postTeleportTimer;
    /* 0x96 */ short int multiKillTimer;
    /* 0x98 */ short int armorLevelTimer;
    /* 0x9a */ short int damageMuliplierTimer;
    /* 0x9c */ int powerupEffectTimer;
    /* 0xa0 */ short int juggernautFadeTimer;
    /* 0xa2 */ short int onFireTimer;
    /* 0xa4 */ short int acidTimer;
    /* 0xa6 */ short int freezeTimer;
    /* 0xa8 */ short int noHelmTimer;
    /* 0xaa */ short int elecTimer;
    /* 0xac */ short int boltDistMulTimer;
    /* 0xae */ short int explodeTimer;
    /* 0xb0 */ short int noDeathTimer;
    /* 0xb2 */ short int invincibilityTimer;
} HeroTimers;

// dltypes.txt:4607; ghidra-layout.
typedef struct { // 0x20
    /* 0x00 */ float speed;
    /* 0x04 */ int iscale;
    /* 0x08 */ int flags;
    /* 0x0c */ int interping;
    /* 0x10 */ int env_index;
    /* 0x14 */ int env_time;
    /* 0x18 */ float mayaFrm;
    /* 0x1c */ float mayaFrmDelt;
} HeroAnim;

// dltypes.txt:4688; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ int anim;
    /* 0x4 */ float frequency;
    /* 0x8 */ float minRepeatTime;
    /* 0xc */ int repeatTimer;
} HeroSpecialIdleDef;

// dltypes.txt:4785; ghidra-layout.
typedef struct { // 0x28
    /* 0x00 */ float slope;
    /* 0x04 */ float plane;
    /* 0x08 */ float range;
    /* 0x0c */ int sample_id;
    /* 0x10 */ int pad[2];
    /* 0x18 */ float sample_pos[4];
} HeroShadow;

// dltypes.txt:4921; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ float ideal;
    /* 0x4 */ float actual;
    /* 0x8 */ int pad[2];
} HeroThrust;

// dltypes.txt:4999; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ short int index;
    /* 0x2 */ char ice;
    /* 0x3 */ char magictele;
    /* 0x4 */ char water;
    /* 0x5 */ char lava;
    /* 0x6 */ char quicksand;
    /* 0x7 */ char magnetic;
    /* 0x8 */ char noStand;
    /* 0x9 */ char deathsand;
    /* 0xa */ char icewater;
    /* 0xb */ char groundType;
    /* 0xc */ int pad;
} HeroHotspots;

// dltypes.txt:5022; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ float vel;
    /* 0x4 */ float velvar;
    /* 0x8 */ int timer;
    /* 0xc */ short int rate;
    /* 0xe */ short int flags;
} HeroDust;

// dltypes.txt:5030; ghidra-layout.
typedef struct { // 0x20
    /* 0x00 */ float gravity;
    /* 0x04 */ float xyDecel;
    /* 0x08 */ float xRotSpeed;
    /* 0x0c */ float yRotSpeed;
    /* 0x10 */ float xRotSpeedIdeal;
    /* 0x14 */ float yRotSpeedIdeal;
    /* 0x18 */ float glideTaperSpeed;
    /* 0x1c */ int pad[1];
} HeroFall;

// dltypes.txt:5115; ghidra-layout.
typedef struct { // 0x10
    /* 0x0 */ int timesFallen;
    /* 0x4 */ int pad[3];
} HeroQuickSand;

// dltypes.txt:5133; ghidra-layout.
typedef struct { // 0x8
    /* 0x0 */ short int active;
    /* 0x2 */ short int sound;
    /* 0x4 */ short int timer;
    /* 0x6 */ short int flags;
} HeroQueuedSound;

#endif
