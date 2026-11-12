#include "common.h"
#include "game_section.h"


typedef unsigned int s128 __attribute__((mode(TI)));
struct MobyClass;
struct MobyInstance {
	/* 0x00 */ float bSphere[4];
	/* 0x10 */ float pos[4];
	/* 0x20 */ char state;
	/* 0x21 */ unsigned char group;
	/* 0x22 */ char mClass;
	/* 0x23 */ char alpha;
	/* 0x24 */ MobyClass *pClass;
	/* 0x28 */ MobyInstance *pChain;
	/* 0x2c */ unsigned char collDamage;
	/* 0x2d */ signed char deathCnt;
	/* 0x2e */ unsigned short occlIndex;
	/* 0x30 */ char updateDist;
	/* 0x31 */ char drawn;
	/* 0x32 */ short drawDist;
	/* 0x34 */ unsigned short modeBits;
	/* 0x36 */ unsigned short modeBits2;
	/* 0x38 */ unsigned long lights;
	/* 0x40 */ void *animSeq;
	/* 0x44 */ float animSeqT;
	/* 0x48 */ float animSpeed;
	/* 0x4c */ short animIScale;
	/* 0x4e */ short poseCacheEntryIndex;
	/* 0x50 */ void *animLayers;
	/* 0x54 */ char animSeqId;
	/* 0x55 */ char animFlags;
	/* 0x56 */ char lSeq;
	/* 0x57 */ char jointCnt;
	/* 0x58 */ void *jointCache;
	/* 0x5c */ void *pManipulator;
	/* 0x60 */ int glow_rgba;
	/* 0x64 */ char lod_trans;
	/* 0x65 */ char lod_trans2;
	/* 0x66 */ char metal;
	/* 0x67 */ char subState;
	/* 0x68 */ char prevState;
	/* 0x69 */ char stateType;
	/* 0x6a */ unsigned short stateTimer;
	/* 0x6c */ char soundTrigger;
	/* 0x6d */ char soundDesired;
	/* 0x6e */ short soundChannel;
	/* 0x70 */ float scale;
	/* 0x74 */ unsigned short bangles;
	/* 0x76 */ char shadow;
	/* 0x77 */ char shadow_index;
	/* 0x78 */ float shadow_plane;
	/* 0x7c */ float shadow_range;
	/* 0x80 */ float lSphere[4];
	/* 0x90 */ void *netObject;
	/* 0x94 */ short updateID;
	/* 0x96 */ short spad0;
	/* 0x98 */ int *collData;
	/* 0x9c */ int collActive;
	/* 0xa0 */ unsigned int collCnt;
	/* 0xa4 */ char grid_min_x;
	/* 0xa5 */ char grid_min_y;
	/* 0xa6 */ char grid_max_x;
	/* 0xa7 */ char grid_max_y;
	/* 0xa8 */ void *pUpdate;
	/* 0xac */ void *pVar;
	/* 0xb0 */ char mission;
	/* 0xb1 */ char pad;
	/* 0xb2 */ short UID;
	/* 0xb4 */ short bolts;
	/* 0xb6 */ unsigned short xp;
	/* 0xb8 */ MobyInstance *pParent;
	/* 0xbc */ short oClass;
	/* 0xbe */ unsigned char triggers;
	/* 0xbf */ char standarddeathcalled;
	/* 0xc0 */ float rMtx[12];
	/* 0xf0 */ float rot[4];
};
struct SubVars {
	/* 0x00 */ int unk00[2];
	/* 0x08 */ void *trackVars;
	/* 0x0c */ void *bogeyVars;
	/* 0x10 */ void *reactVars;
	/* 0x14 */ int unk14[2];
	/* 0x1c */ void *moveVars;
	/* 0x20 */ int unk20[3];
	/* 0x2c */ void *commandVars;
	/* 0x30 */ int unk30;
	/* 0x34 */ void *flashVars;
	/* 0x38 */ void *suckVars;
	/* 0x3c */ void *navigationVars;
};
struct TargetVars {
	/* 0x00 */ char unk00[0x2c];
	/* 0x2c */ short bogeyType;
	/* 0x2e */ short team;
	/* 0x30 */ char unk30[0x48 - 0x30];
	/* 0x48 */ int maxDifficultySlotted;
	/* 0x4c */ int curDifficultySlotted;
	/* 0x50 */ MobyInstance *pTargettedByBogeys[8];
	/* 0x70 */ char unk70[0x90 - 0x70];
};
struct BotSaveDef {
	/* 0x00 */ unsigned char botUpgrades[0x11];
	/* 0x11 */ unsigned char botPaintjobs[0xb];
	/* 0x1c */ unsigned char botHeads[8];
	/* 0x24 */ unsigned char curBotPaintJob[2];
	/* 0x26 */ unsigned char curBotHead[2];
	/* 0x28 */ char unk28[0x40];
};
struct BotAbility {
	/* 0x00 */ int unk00[4];
};
struct Bot_Communication {
	/* 0x000 */ unsigned char initialized;
	/* 0x001 */ char unk001[0x1f3];
	/* 0x1f4 */ unsigned char botAbilities[0x11];
};
struct MotionBlur {
	/* 0x000 */ char unk000[0x120];
	/* 0x120 */ MobyInstance *blurMobys[4];
	/* 0x130 */ float gapReduction[4];
	/* 0x140 */ short ringIndex;
	/* 0x142 */ short ringValidSize;
	/* 0x144 */ MobyInstance *pTrackedMoby;
	/* 0x148 */ int blurCnt;
	/* 0x14c */ int active;
};
struct FlashVars {
	/* 0x0 */ short timer;
	/* 0x2 */ short type;
	/* 0x4 */ int destColor;
	/* 0x8 */ int srcColor;
	/* 0xc */ int flags;
};
extern BotSaveDef BotSave __asm__("BotSave");
extern BotAbility Bot_AbilityDefinitions[] __asm__("D_3D8B60");
extern Bot_Communication Bot_Comm_Instance __asm__("Bot_Comm_Instance");
extern unsigned char CheatsActivated[] __asm__("CheatsActivated");
TargetVars *MB_getTargetVars(MobyInstance *) __asm__("MB_getTargetVars");
void MB_StartColorFlash(MobyInstance *, int, int, FlashVars *) __asm__("MB_StartColorFlash");
void SetMobyAmbientLights(MobyInstance *, int, int, int) __asm__("SetMobyAmbientLights");
float GetGroundZ(s128, int, float, MobyInstance *, float) __asm__("GetGroundZ");
void Bot_ResetGlobalComm() __asm__("Bot_ResetGlobalComm");
BotAbility *Bot_GetAbilityDef(unsigned int) __asm__("Bot_GetAbilityDef");
int Bot_GetCurrentPaintjob(unsigned int) __asm__("Bot_GetCurrentPaintjob");
bool Bot_HasHead(unsigned int) __asm__("Bot_HasHead");
bool Bot_HasPaintjob(unsigned int) __asm__("Bot_HasPaintjob");
void CreateMotionBlur(MobyInstance *, MotionBlur &) __asm__("CreateMotionBlur");
int Lerp(int, int, float) __asm__("Lerp");
int MB_GetBogeyType(MobyInstance *) __asm__("MB_GetBogeyType");
void MB_initMobyColorFlash(MobyInstance *, FlashVars &) __asm__("MB_initMobyColorFlash");
unsigned char Bot_HasAbility(int) __asm__("Bot_HasAbility");
float GetGroundZNoWater(s128) __asm__("GetGroundZNoWater");
void MB_SetAmbientLights(MobyInstance *, int) __asm__("MB_SetAmbientLights");
void MB_SetBogeyType(MobyInstance *, int) __asm__("MB_SetBogeyType");
void *MB_getReactVars(MobyInstance *) __asm__("MB_getReactVars");
float SubLerp(float, float, float) __asm__("SubLerp");
int Bot_GetCurrentHead(unsigned int) __asm__("Bot_GetCurrentHead");
Bot_Communication *Bot_GetGlobalComm() __asm__("Bot_GetGlobalComm");
float Delt(float &, float, float) __asm__("Delt");
void *MB_GetBogeyVars(MobyInstance *) __asm__("MB_GetBogeyVars");
void *MB_GetCommandVars(MobyInstance *) __asm__("MB_GetCommandVars");
void *MB_GetFlashVars(MobyInstance *) __asm__("MB_GetFlashVars");
void *MB_GetMoveVars_2(MobyInstance *) __asm__("MB_GetMoveVars_2");
void *MB_GetNavigationVars(MobyInstance *) __asm__("MB_GetNavigationVars");
void *MB_GetSuckVars(MobyInstance *) __asm__("MB_GetSuckVars");
void *MB_getTrackVars(MobyInstance *) __asm__("MB_getTrackVars");
void Bot_GrantAbility(int) __asm__("Bot_GrantAbility");
void Bot_GrantHead(unsigned int, int) __asm__("Bot_GrantHead");
float MB_WrapRot(float) __asm__("MB_WrapRot");


struct MobySeq {
	/* 0x00 */ float bSphere[4];
	/* 0x10 */ unsigned char frameCnt;
	/* 0x11 */ signed char sound;
	/* 0x12 */ unsigned char trigsCnt;
	/* 0x13 */ char pad;
	/* 0x14 */ short *trigs;
	/* 0x18 */ void *animInfo;
	/* 0x1c */ void *frameData;
};
struct MobyClass {
	/* 0x00 */ char unk00[0xb];
	/* 0x0b */ unsigned char team_texs;
	/* 0x0c */ unsigned char seq_cnt;
	/* 0x0d */ char unk0d[0x46 - 0xd];
	/* 0x46 */ unsigned char type;
	/* 0x47 */ char mode_bits2;
	/* 0x48 */ MobySeq *seqs[0];
};
/* ===== AG additions ===== */
struct CollDamOut {
	/* 0x00 */ char unk00[0x24];
	/* 0x24 */ int damageFlags;
	/* 0x28 */ char unk28[0x18];
};
struct CommandData {
	/* 0x00 */ char unk00[0x14];
	/* 0x14 */ int msgTag;
	/* 0x18 */ char unk18[8];
};
struct LocalHero {
	/* 0x0000 */ char unk0000[0x1f9c];
	/* 0x1f9c */ char target[0x25cc - 0x1f9c];
	/* 0x25cc */ int state;
	/* 0x25d0 */ char unk25d0[0x26e4 - 0x25d0];
	/* 0x26e4 */ void *pGadgetBox;
	/* 0x26e8 */ char unk26e8[0x2ef0 - 0x26e8];
	/* 0x2ef0 */ MobyInstance *pMoby;
	/* 0x2ef4 */ char unk2ef4[0x2f14 - 0x2ef4];
	/* 0x2f14 */ int mpTeam;
	/* 0x2f18 */ char unk2f18[0x31e0 - 0x2f18];
	/* 0x31e0 */ MobyInstance *pRespawnDest;
};
extern short MB_UpgradeSceneQueue[8] __asm__("MB_UpgradeSceneQueue");
extern CollDamOut CollDamage[] __asm__("CollDamage");
extern CommandData CMD_CommandData[] __asm__("CMD_CommandData");
int FastTweenColor(int, int, float) __asm__("FastTweenColor");
float FastCos(float) __asm__("FastCos");
char *msg_string(int) __asm__("msg_string");
LocalHero *GB_GetLocalHeroFromSlot(int) __asm__("GB_GetLocalHeroFromSlot");
void SetMobyLights(MobyInstance *, int, int, int, int) __asm__("SetMobyLights");
void MB_BobMotion___dupe2(float *, float &, float &, float, float, float) __asm__("MB_BobMotion___dupe2");
float Bias0(float) __asm__("Bias0");
float Bias1(float) __asm__("Bias1");
int TweenColor(int, int, float) __asm__("TweenColor");
float Lerp___dupe2(float, float, float) __asm__("Lerp___dupe2");
int MB_isCrateOClass(int) __asm__("MB_isCrateOClass");
int MB_MP_GadgetDamageIndex(MobyInstance *) __asm__("MB_MP_GadgetDamageIndex");
void MB_BobMotion(MobyInstance *, float &, float &, float, float, float) __asm__("MB_BobMotion");
void FUN_0047eb50() __asm__("FUN_0047eb50");
void FUN_0047eb58() __asm__("FUN_0047eb58");
float MB_CubicInterpolate(float, float, float, float, float) __asm__("MB_CubicInterpolate");
float MB_CosineInterpolateUnit(float) __asm__("MB_CosineInterpolateUnit");
void MB_setState(MobyInstance *, int, int) __asm__("MB_setState");
bool MB_QueueUpgradeScene(int) __asm__("MB_QueueUpgradeScene");
bool MB_CheckQueuedUpgradeScene(int) __asm__("MB_CheckQueuedUpgradeScene");
CollDamOut *_MB_damage(MobyInstance *, int, int) __asm__("_MB_damage");
void MB_SetDefaultLights(MobyInstance *) __asm__("MB_SetDefaultLights");
int MB_isMorph(MobyInstance *) __asm__("MB_isMorph");
char *MB_GetCommandName(unsigned int) __asm__("MB_GetCommandName");
void MB_SetMobyTeamTex(MobyInstance *, int) __asm__("MB_SetMobyTeamTex");
void MB_SelectRespawnNode(int, MobyInstance *, void *) __asm__("MB_SelectRespawnNode");
void MB_GhostMe(MobyInstance *) __asm__("MB_GhostMe");


struct HeroSaveDef {
	/* 0x00 */ char unk00[0x1e];
	/* 0x1e */ unsigned char boltMultLevel;
	/* 0x1f */ unsigned char boltMultSubLevel;
	/* 0x20 */ char unk20[0x1c];
};
struct GameControllerData {
	/* 0x000 */ char unk000[0x5f0];
	/* 0x5f0 */ unsigned char numNodesOwned[10];
};
extern HeroSaveDef HeroSave __asm__("HeroSave");
extern LocalHero *g_Hero[10] __asm__("g_Hero");
extern GameControllerData g_GameControllerData __asm__("g_GameControllerData");
bool IsGameInChallengeMode() __asm__("IsGameInChallengeMode");
void LoadBotTextures(int) __asm__("LoadBotTextures");
void MB_HandleBoltMultiplier() __asm__("MB_HandleBoltMultiplier");
float MB_CosineInterpolate(float, float, float) __asm__("MB_CosineInterpolate");
void GainDampLimit(float &, float, float, float, float) __asm__("GainDampLimit");
unsigned int Float_To_RGBA(float, float, float, float) __asm__("Float_To_RGBA");
void ReorderRGB(int &, int &, int &, int) __asm__("ReorderRGB");
void Bot_GrantPaintjob(unsigned int, int) __asm__("Bot_GrantPaintjob");
bool MB_ValidateRespawnNode(int, MobyInstance *, void *) __asm__("MB_ValidateRespawnNode");
int MB_NumValidRespawnNodes(int) __asm__("MB_NumValidRespawnNodes");

static inline void agClamp(float &f, float lim) { float n = -lim; f = f <? lim; f = f >? n; }

struct BogeyVars {
	/* 0x00 */ float targetPos[4];
	/* 0x10 */ MobyInstance *pTarget;
	/* 0x14 */ short targetType;
	/* 0x16 */ short targetStatus;
	/* 0x18 */ char unk18[0x40 - 0x18];
	/* 0x40 */ int difficultyRating;
	/* 0x44 */ char unk44[0x90 - 0x44];
};
extern MobyInstance *MobyInstances __asm__("MobyInstances");
void MobyTransitionSequence(MobyInstance *, MobySeq *, int, float, int) __asm__("MobyTransitionSequence");
float SubRots(float, float, int) __asm__("SubRots");
float FastAddRots(float, float) __asm__("FastAddRots");
void DeleteMoby(MobyInstance *) __asm__("DeleteMoby");
void MB_snapAnim(MobyInstance *, int, float) __asm__("MB_snapAnim");
float SlideDelt(float &, float, float, float) __asm__("SlideDelt");
float DeltAng(float &, float, float, int) __asm__("DeltAng");
int ReorderRGB___dupe2(int, int) __asm__("ReorderRGB___dupe2");
void MB_EndColorFlash(MobyInstance *, FlashVars *) __asm__("MB_EndColorFlash");
void MB_AddMobyToDynamicGroup(MobyInstance *, short *, short) __asm__("MB_AddMobyToDynamicGroup");
void MB_DeleteMobyFromDynamicGroup(MobyInstance *, short *) __asm__("MB_DeleteMobyFromDynamicGroup");
void DeleteMotionBlur(MotionBlur &) __asm__("DeleteMotionBlur");
struct XPBundle {
	/* 0x00 */ MobyInstance *pMoby;
	/* 0x04 */ float gadgetXp[20];
};
extern XPBundle MB_xpBundle[3] __asm__("MB_xpBundle");
extern MobyInstance *MobyInstanceEnd __asm__("MobyInstanceEnd");
extern int g_gameType __asm__("g_gameType");
extern LocalHero *MyHero __asm__("MyHero");
extern MobyInstance *_CMD_CommandCache[0x100] __asm__("_CMD_CommandCache");
unsigned char _CMD_CommandCacheInited __asm__("_CMD_CommandCacheInited") GAME_GP_DATA = 0;
int _CMD_CommandCacheSize __asm__("_CMD_CommandCacheSize") GAME_GP_DATA = 0;
void FastMemSet(void *, int, int) __asm__("FastMemSet");
int NumModActive(void *, int, int) __asm__("NumModActive");
bool AddGadgetXP(void *, int, int) __asm__("AddGadgetXP");
float MB_randRange(float, float) __asm__("MB_randRange");
static inline int agIAbs(int x) { return x < 0 ? -x : x; }
int SlideDelt___dupe2(int &, int, float, int) __asm__("SlideDelt___dupe2");
bool MB_AddHoloshieldGadgetXP() __asm__("MB_AddHoloshieldGadgetXP");
int MB_isCrate(MobyInstance *) __asm__("MB_isCrate");
void MB_UnlockBogey(MobyInstance *) __asm__("MB_UnlockBogey");
void MB_InitializeCommandCache() __asm__("MB_InitializeCommandCache");
int MB_GetXPBundle(MobyInstance *) __asm__("MB_GetXPBundle");
float AccelDelt(float &, float, float &, float, float, float) __asm__("AccelDelt");
float FastSubRots(float, float) __asm__("FastSubRots");
float FastSin(float) __asm__("FastSin");
float MobyMayaFrame(MobyInstance *) __asm__("MobyMayaFrame");
int MB_MayaFrameTrigger(MobyInstance *, float) __asm__("MB_MayaFrameTrigger");
void MB_SwingMotion(MobyInstance *, float &, float &, float, float, float) __asm__("MB_SwingMotion");
unsigned char Bot_HasCommandAbility(unsigned int) __asm__("Bot_HasCommandAbility");
struct SoundTrigger {
	/* 0x0 */ unsigned short sound;
	/* 0x2 */ unsigned short frame;
};
struct vec4f {
	/* 0x0 */ float x;
	/* 0x4 */ float y;
	/* 0x8 */ float z;
	/* 0xc */ float w;
};
extern int worldUpdateTime __asm__("worldUpdateTime");
bool IsWeaponTemp(LocalHero *, int) __asm__("IsWeaponTemp");
int sound_MobyPlay(int, int, MobyInstance *) __asm__("sound_MobyPlay");
void MB_AllocateXPBundle(XPBundle *, int) __asm__("MB_AllocateXPBundle");
void MB_PlaySoundsInSeq(MobyInstance *, int, unsigned short) __asm__("MB_PlaySoundsInSeq");
void MB_transAnim___dupe2(MobyInstance *, int, float, int, int) __asm__("MB_transAnim___dupe2");
int PointInsideComplexPoly(vec4f &, vec4f *, int) __asm__("PointInsideComplexPoly");
int MB_Level99ColorTimeBased(int) __asm__("MB_Level99ColorTimeBased");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_QueueUpgradeScene);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_CheckQueuedUpgradeScene);

GAME_SECTION(MB_AddHoloshieldGadgetXP) bool MB_AddHoloshieldGadgetXP()
{
	float xp = 1.0f;
	LocalHero *pHero = GB_GetLocalHeroFromSlot(0);
	if (pHero) xp = NumModActive(pHero->pGadgetBox, 8, 6) * 0.5f + xp;
	xp = xp + MB_randRange(0.0f, 1.0f);
	return AddGadgetXP(MyHero->pGadgetBox, 8, (int)xp);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_standardDeath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_BundleDamage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AllocateXPBundle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SpawnBolts);

GAME_SECTION(MB_HandleBoltMultiplier) void MB_HandleBoltMultiplier()
{
	if (IsGameInChallengeMode() && HeroSave.boltMultLevel + 1 < 20) {
		HeroSave.boltMultSubLevel++;
		if (HeroSave.boltMultSubLevel >= (HeroSave.boltMultLevel + 1) >> 1) {
			HeroSave.boltMultLevel++;
			HeroSave.boltMultSubLevel = 0;
		}
	}
}

GAME_SECTION(MB_snapAnim) void MB_snapAnim(MobyInstance *pMoby, int seq, float frm)
{
	MobySeq *pSeq = pMoby->pClass->seqs[seq];
	if (frm >= (float)pSeq->frameCnt) frm = pSeq->frameCnt - 1;
	MobyTransitionSequence(pMoby, pSeq, seq, frm, 0);
	pMoby->animFlags &= ~2;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_transAnim);

GAME_SECTION(MB_transAnim___dupe2) void MB_transAnim___dupe2(MobyInstance *pMoby, int seq, float frm, int steps, int flags)
{
	if (frm > 0.0f && frm <= 10.0f && !(flags & 8)) MB_PlaySoundsInSeq(pMoby, seq, (int)frm - 1);
	if (steps <= 0) {
		MB_snapAnim(pMoby, seq, frm);
		return;
	}
	MobyTransitionSequence(pMoby, pMoby->pClass->seqs[seq], seq, frm, steps);
	pMoby->animFlags &= ~2;
	if (flags & 0x10) pMoby->modeBits2 |= 4;
	else pMoby->modeBits2 &= ~4;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00473A80);

GAME_SECTION(MB_setState) void MB_setState(MobyInstance *pMoby, int state, int stateType)
{
	pMoby->prevState = pMoby->state;
	pMoby->state = state;
	pMoby->stateTimer = 0;
	pMoby->triggers &= ~1;
	if (stateType != -1) {
		pMoby->stateType = stateType;
		pMoby->triggers &= ~2;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00473AD0);

GAME_SECTION(Bias0) float Bias0(float in)
{
	return in * in;
}

GAME_SECTION(Bias1) float Bias1(float in)
{
	return 1.0f - (1.0f - in) * (1.0f - in);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00473B08);

GAME_SECTION(MB_CubicInterpolate) float MB_CubicInterpolate(float v0, float v1, float v2, float v3, float x)
{
	float P = (v3 - v2) - (v0 - v1);
	float Q = (v0 - v1) - P;
	float R = v2 - v0;
	return P * (x * x * x) + Q * (x * x) + R * x + v1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_CubicInterpVec);

GAME_SECTION(MB_CosineInterpolate) float MB_CosineInterpolate(float a, float b, float x)
{
	if (x == 0.0f) return a;
	if (x == 1.0f) return b;
	return a + (b - a) * MB_CosineInterpolateUnit(x);
}

GAME_SECTION(MB_CosineInterpolateUnit) float MB_CosineInterpolateUnit(float x)
{
	return (1.0f - FastCos(x * 3.1415927f)) * 0.5f;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00473CB8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_getJumpPeak);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SetOClass);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00473F20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SolveQuad);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", GetGroundZ);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00474088);

GAME_SECTION(GetGroundZNoWater) float GetGroundZNoWater(s128 pos)
{
	return GetGroundZ(pos, 0x20, 0.5f, 0, 32.0f);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004740C0);

GAME_SECTION(PointInsideComplexPoly) int PointInsideComplexPoly(vec4f &point, vec4f *poly, int n)
{
	int cur;
	int nxt = 0;
	int oddNodes = 0;
	for (cur = 0; cur < n; cur++) {
		nxt++;
		if (nxt == n) nxt = 0;
		if (((poly[cur].y < point.y && point.y <= poly[nxt].y) || (poly[nxt].y < point.y && point.y <= poly[cur].y)) &&
			poly[cur].x + (point.y - poly[cur].y) / (poly[nxt].y - poly[cur].y) * (poly[nxt].x - poly[cur].x) < point.x)
			oddNodes = !oddNodes;
	}
	return oddNodes;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SegmentIntersect2D);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00474290);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SetCollDamIn);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004742D0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", DamageSphereAtPos);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00474478);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CollDamageMobyDirect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CollDamageMobyDirect___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004746C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CollWaterHeight);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CollMovingSphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_RegisterLameShadow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00474DA0);

GAME_SECTION(TweenColor) int TweenColor(int col0, int col1, float step)
{
	return FastTweenColor(col0, col1, step);
}

GAME_SECTION(_MB_damage) CollDamOut *_MB_damage(MobyInstance *pMoby, int damageMask, int noClearDamage)
{
	CollDamOut *d = &CollDamage[pMoby->collDamage];
	if (d->damageFlags & damageMask) return d;
	if (noClearDamage == 0) pMoby->collDamage = 0xff;
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00474E18);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_computeLobVelocity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_randPrimPoints);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00475680);

GAME_SECTION(Lerp) int Lerp(int val0, int val1, float alpha)
{
	return val0 + (int)((float)(val1 - val0) * alpha);
}

GAME_SECTION(Lerp___dupe2) float Lerp___dupe2(float val0, float val1, float alpha)
{
	return val0 + (val1 - val0) * alpha;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Lerp___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00475708);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SubLerp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", GainDampLimit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00475798);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Delt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004757D8);

GAME_SECTION(SlideDelt) float SlideDelt(float &fVal, float fTarget, float fRate, float fMinDelt)
{
	float fDelt = fTarget - fVal;
	if (fRate >= 1.0f || __builtin_fabsf(fDelt) < fMinDelt) {
		fVal = fTarget;
	} else {
		fDelt = fDelt * fRate;
		if (__builtin_fabsf(fDelt) < fMinDelt) fDelt = fTarget > fVal ? fMinDelt : -fMinDelt;
		fVal += fDelt;
	}
	return fDelt;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SlideDelt___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", AccelDelt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", AccelDelt___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", OrganicDelt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SubRots);

GAME_SECTION(DeltAng) float DeltAng(float &val, float target, float speed, int turnDir)
{
	float delt = SubRots(target, val, turnDir);
	delt = (delt <? speed) >? -speed;
	val = FastAddRots(val, delt);
	return SubRots(target, val, turnDir);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", AccelDeltAng);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00475EF8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", OrganicDeltAng);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", OrganicDeltSpeed);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MatAdjoint);

GAME_SECTION(Float_To_RGBA) unsigned int Float_To_RGBA(float r, float g, float b, float alpha)
{
	unsigned int ir = (int)(r * 255.0f);
	unsigned int ig = (int)(g * 255.0f);
	unsigned int ib = (int)(b * 255.0f);
	unsigned int ia = (int)(alpha * 255.0f);
	ir &= 0xff;
	ig &= 0xff;
	ib &= 0xff;
	return ir | (ig << 8) | (ib << 16) | (ia << 24);
}

GAME_SECTION(ReorderRGB) void ReorderRGB(int &r, int &g, int &b, int order)
{
	int temp;
	if (order & 1) {
		temp = r;
		r = g;
		g = temp;
	}
	if (order & 2) {
		temp = g;
		g = b;
		b = temp;
	}
	if (order & 4) {
		temp = b;
		b = r;
		r = temp;
	}
}

GAME_SECTION(ReorderRGB___dupe2) int ReorderRGB___dupe2(int rgba, int order)
{
	if (order == 0) return rgba;
	int r = rgba & 0xff;
	int g = (rgba & 0xff00) >> 8;
	int b = ((unsigned int)rgba >> 16) & 0xff;
	unsigned int a = (unsigned int)rgba >> 24;
	ReorderRGB(r, g, b, order);
	return (a << 24) | (b << 16) | (g << 8) | r;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004765A0);

GAME_SECTION(MB_GetSuckVars) void *MB_GetSuckVars(MobyInstance *pMoby)
{
	void *r;
	if (!pMoby || !pMoby->pVar || !(pMoby->modeBits & 0x20)) r = 0;
	else r = ((SubVars *)pMoby->pVar)->suckVars;
	return r;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004765E8);

GAME_SECTION(MB_GetMoveVars_2) void *MB_GetMoveVars_2(MobyInstance *pMoby)
{
	void *r;
	if (!pMoby || !pMoby->pVar || !(pMoby->modeBits & 0x20)) r = 0;
	else r = ((SubVars *)pMoby->pVar)->moveVars;
	return r;
}

GAME_SECTION(MB_GetNavigationVars) void *MB_GetNavigationVars(MobyInstance *pMoby)
{
	void *r;
	if (!pMoby || !pMoby->pVar || !(pMoby->modeBits & 0x20)) r = 0;
	else r = ((SubVars *)pMoby->pVar)->navigationVars;
	return r;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_getReactVars);

GAME_SECTION(MB_getTargetVars) TargetVars *MB_getTargetVars(MobyInstance *pMoby)
{
	if (pMoby) {
		int i = 0;
		LocalHero **pp = g_Hero;
		LocalHero *pHero = g_Hero[0];
		do {
			pp++;
			if (pHero && pMoby == pHero->pMoby) return (TargetVars *)pHero->target;
			i++;
			pHero = *pp;
		} while (i < 10);
		if (pMoby->pVar != 0 && (pMoby->modeBits & 0x20)) goto out;
	}
	return 0;
out:
	return *(TargetVars **)pMoby->pVar;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00476700);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_MistDeathEffect);

GAME_SECTION(MB_SetDefaultLights) void MB_SetDefaultLights(MobyInstance *pMoby)
{
	LocalHero *pHero = GB_GetLocalHeroFromSlot(0);
	if (pHero && pHero->pMoby) pMoby->lights = pHero->pMoby->lights;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CollLineValidate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", DecomposeMtx4ToAng);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetFlashVars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_StartColorFlash);

GAME_SECTION(MB_EndColorFlash) void MB_EndColorFlash(MobyInstance *pMoby, FlashVars *fVars)
{
	if (fVars || (fVars = (FlashVars *)MB_GetFlashVars(pMoby))) {
		if (fVars->type) {
			int c = fVars->srcColor;
			int a = (unsigned int)c >> 24;
			fVars->type = 0;
			int b = c >> 16;
			int g = c >> 8;
			SetMobyAmbientLights(pMoby, c & 0xff, g & 0xff, b & 0xff);
			if (fVars->flags & 1) pMoby->alpha = a;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_UpdateColorFlash);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477648);

GAME_SECTION(MB_initMobyColorFlash) void MB_initMobyColorFlash(MobyInstance *pMoby, FlashVars &fv)
{
	MB_StartColorFlash(pMoby, 1, 0, &fv);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477678);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_WrapRot);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004776C0);

GAME_SECTION(MB_isCrateOClass) int MB_isCrateOClass(int oClass)
{
	return (unsigned int)(oClass - 500) < 0x29;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_isCrate);

GAME_SECTION(MB_isMorph) int MB_isMorph(MobyInstance *pMoby)
{
	if (pMoby) {
		short o = pMoby->oClass;
		if (o == 0x10e || o == 0xe7d || o == 0x1bc3 || o == 0x2569 || o == 0x2692) return 1;
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004777C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_genericExplosion);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477A90);

GAME_SECTION(MB_AddMobyToDynamicGroup) void MB_AddMobyToDynamicGroup(MobyInstance *pMoby, short *pGroup, short limit)
{
	short index = pMoby - MobyInstances;
	int i;
	for (i = 1; i <= pGroup[0]; i++) {
		if (pGroup[i] == index) return;
	}
	if (pGroup[0] < limit) {
		pGroup[0]++;
		pGroup[pGroup[0]] = index;
	}
}

GAME_SECTION(MB_DeleteMobyFromDynamicGroup) void MB_DeleteMobyFromDynamicGroup(MobyInstance *pMoby, short *pGroup)
{
	int i;
	for (i = 1; i <= pGroup[0]; i++) {
		if (&MobyInstances[pGroup[i]] == pMoby) {
			pGroup[i] = pGroup[pGroup[0]];
			pGroup[0]--;
			return;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477B88);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_RandomizeVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_RandomizeVector___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_RandomizeVectorRange);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IsPntInCylinder);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IsPntInSphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IsPntInPath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477F30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SlerpVectors);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00477FB8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_getTrackVars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_TrackMoby_OneFrame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_TrackMoby_OneFrame_Vel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004788E8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GadgetDamageIndex);

GAME_SECTION(MB_MP_GadgetDamageIndex) int MB_MP_GadgetDamageIndex(MobyInstance *pMoby)
{
	return 0xff;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", SetNtscPalTiming);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00478E20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_compressVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_decompressVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00478FD8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_MayaFrameTrigger);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004790B0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", CreateMotionBlur);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", AddMotionBlurElem);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", UpdateMotionBlur);

GAME_SECTION(DeleteMotionBlur) void DeleteMotionBlur(MotionBlur &blur)
{
	if (blur.active) {
		int i;
		for (i = 0; i < blur.blurCnt; i++) {
			if (blur.blurMobys[i]) {
				DeleteMoby(blur.blurMobys[i]);
				blur.blurMobys[i] = 0;
			}
		}
		blur.active = 0;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00479570);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SetAmbientLights);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004795B0);

GAME_SECTION(MB_BobMotion) void MB_BobMotion(MobyInstance *pMoby, float &bobt, float &bobz, float bobAmp, float bobSpeed, float centerZ)
{
	MB_BobMotion___dupe2(pMoby->pos, bobt, bobz, bobAmp, bobSpeed, centerZ);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_BobMotion___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_004796C0);

GAME_SECTION(MB_SwingMotion) void MB_SwingMotion(MobyInstance *pMoby, float &swingAng1, float &swingAng2, float swingAmp, float swingRate1, float swingRate2)
{
	pMoby->rot[0] = swingAmp * FastSin(swingAng1) * FastSin(swingAng2);
	pMoby->rot[1] = swingAmp * FastSin(swingAng1) * FastCos(swingAng2);
	swingAng1 = FastAddRots(swingAng1, swingRate1);
	swingAng2 = FastAddRots(swingAng2, swingRate2);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00479790);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AddVectorSphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_00479818);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AttachMobyToJoint);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_ComputeTargetScore);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_getTarget);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", FUN_00479d28);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047AA28);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetLocalSpaceVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetWorldSpaceVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047AB20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_scaleRelativeXY);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_relativeXYComponent);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047AC20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_FindGravity_CageMatch);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_FindGravity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047ADE0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AddGravity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047AEA8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SphericalHeight);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AlignWithGravity);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_AlignWithNormal);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047B0F0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_DrawGlowFX);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047B2D0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_BlowCorn);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_BlowFlamingCorn);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047B7E8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", FUN_0047b7f8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047B978);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_SpawnInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047BA28);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IsPntInArea);

GAME_SECTION(MB_GetBogeyVars) void *MB_GetBogeyVars(MobyInstance *pMoby)
{
	void *r;
	if (!pMoby || !pMoby->pVar || !(pMoby->modeBits & 0x20)) r = 0;
	else r = ((SubVars *)pMoby->pVar)->bogeyVars;
	return r;
}

GAME_SECTION(MB_GetBogeyType) int MB_GetBogeyType(MobyInstance *pMoby)
{
	TargetVars *tVars = MB_getTargetVars(pMoby);
	if (tVars == 0) return 0;
	return tVars->bogeyType;
}

GAME_SECTION(MB_SetBogeyType) void MB_SetBogeyType(MobyInstance *pMoby, int type)
{
	TargetVars *tVars = MB_getTargetVars(pMoby);
	if (tVars) tVars->bogeyType = type;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047BC68);

GAME_SECTION(MB_UnlockBogey) void MB_UnlockBogey(MobyInstance *pMoby)
{
	BogeyVars *bVars = (BogeyVars *)MB_GetBogeyVars(pMoby);
	if (bVars && bVars->pTarget && bVars->targetStatus == 2) {
		TargetVars *tVars;
		bVars->targetStatus = 1;
		tVars = MB_getTargetVars(bVars->pTarget);
		if (tVars) {
			int i;
			for (i = 0; i < 8; i++) {
				if (tVars->pTargettedByBogeys[i] == pMoby) tVars->pTargettedByBogeys[i] = 0;
			}
			tVars->curDifficultySlotted -= bVars->difficultyRating;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047BD18);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_FastBsphereCheck);

GAME_SECTION(MB_PlaySoundsInSeq) void MB_PlaySoundsInSeq(MobyInstance *pMoby, int seq, unsigned short end_frame)
{
	MobyClass *pClass = pMoby->pClass;
	if (pClass && seq < pClass->seq_cnt) {
		MobySeq *pSeq = pClass->seqs[seq];
		if (pSeq->trigsCnt) {
			int i;
			SoundTrigger *pTrigger = (SoundTrigger *)pSeq->trigs;
			for (i = 0; i < pSeq->trigsCnt; i++) {
				if ((end_frame << 4) < pTrigger[i].frame) break;
				sound_MobyPlay(pTrigger[i].sound, 0, pMoby);
			}
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetCommandVars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047C050);

GAME_SECTION(MB_InitializeCommandCache) void MB_InitializeCommandCache()
{
	if (!_CMD_CommandCacheInited) {
		MobyInstance **pp = _CMD_CommandCache;
		int index = 0;
		MobyInstance *pMoby;
		for (pMoby = MobyInstances; pMoby < MobyInstanceEnd; pMoby++) {
			if (MB_GetCommandVars(pMoby)) {
				*pp++ = pMoby;
				index++;
				if (index >= 0x100) break;
			}
		}
		_CMD_CommandCacheInited = 1;
		_CMD_CommandCacheSize = index;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_DrawDestroyIcon);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_FindVisibleContextCommand);

GAME_SECTION(MB_GetCommandName) char *MB_GetCommandName(unsigned int type)
{
	char *r;
	if (type >= 13) r = 0;
	else r = msg_string(CMD_CommandData[type].msgTag);
	return r;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047CE60);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IssueCommand);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_IssueCommand___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047D240);

GAME_SECTION(Bot_GetAbilityDef) BotAbility *Bot_GetAbilityDef(unsigned int a)
{
	BotAbility *r;
	if (a > 0x10) r = 0;
	else r = &Bot_AbilityDefinitions[a];
	return r;
}

GAME_SECTION(Bot_HasAbility) unsigned char Bot_HasAbility(int a)
{
	return Bot_GetGlobalComm()->botAbilities[a];
}

GAME_SECTION(Bot_HasCommandAbility) unsigned char Bot_HasCommandAbility(unsigned int cmd)
{
	switch (cmd) {
	case 1:
	case 2:
	case 3:
	case 7:
	case 8:
	case 9:
	case 10:
		return 1;
	case 4:
		return Bot_HasAbility(6);
	case 5:
		return Bot_HasAbility(7);
	case 6:
		return Bot_HasAbility(9);
	case 11:
		return Bot_HasAbility(8);
	case 12: {
		unsigned char r = 0;
		if (Bot_HasAbility(4) || Bot_HasAbility(5)) r = 1;
		return r;
	}
	case 0:
	case 13:
	default:
		return 0;
	}
}

GAME_SECTION(Bot_GrantAbility) void Bot_GrantAbility(int a)
{
	Bot_GetGlobalComm()->botAbilities[a] = 1;
	BotSave.botUpgrades[a] = 1;
}

GAME_SECTION(Bot_GrantPaintjob) void Bot_GrantPaintjob(unsigned int paintjob, int setAsCurrent)
{
	if (paintjob < 11) {
		BotSave.botPaintjobs[paintjob] = 1;
		if (setAsCurrent && paintjob != BotSave.curBotPaintJob[0]) {
			BotSave.curBotPaintJob[0] = paintjob;
			BotSave.curBotPaintJob[1] = paintjob;
			LoadBotTextures(paintjob);
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_HasPaintjob);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_GetCurrentPaintjob);

GAME_SECTION(Bot_GrantHead) void Bot_GrantHead(unsigned int headNum, int setAsCurrent)
{
	if (headNum < 8) {
		BotSave.botHeads[headNum] = 1;
		if (setAsCurrent & 1) BotSave.curBotHead[0] = headNum;
		if (setAsCurrent & 2) BotSave.curBotHead[1] = headNum;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_HasHead);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_GetCurrentHead);

GAME_SECTION(Bot_GetGlobalComm) Bot_Communication *Bot_GetGlobalComm()
{
	if (!Bot_Comm_Instance.initialized) Bot_ResetGlobalComm();
	return &Bot_Comm_Instance;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", Bot_ResetGlobalComm);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047D6A8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetShadowSurface);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetRandomShadowPoints);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetRandomShadowSurfacePoint);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", MB_GetRandomShadowSurfacePoints);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047EB40);

GAME_SECTION(FUN_0047eb50) void FUN_0047eb50()
{
}

GAME_SECTION(FUN_0047eb58) void FUN_0047eb58()
{
}

GAME_SECTION(MB_SetMobyTeamTex) void MB_SetMobyTeamTex(MobyInstance *pMoby, int iTeam)
{
	if (pMoby->pClass && pMoby->pClass->team_texs) {
		unsigned short b = (pMoby->modeBits2 | 0x8000) & 0x87ff;
		pMoby->modeBits2 = b;
		if (iTeam == 10) {
			pMoby->modeBits2 = b | 0x5000;
			return;
		}
		pMoby->modeBits2 = b | (iTeam << 11);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047EBB0);

GAME_SECTION(MB_SelectRespawnNode) void MB_SelectRespawnNode(int iPlayer, MobyInstance *pMobyDest, void *pUserData)
{
	LocalHero *pHero = GB_GetLocalHeroFromSlot(iPlayer);
	if (pHero && pMobyDest && pHero->state != 0x66) pHero->pRespawnDest = pMobyDest;
}

GAME_SECTION(MB_ValidateRespawnNode) bool MB_ValidateRespawnNode(int iPlayer, MobyInstance *pMobyDest, void *pUserData)
{
	bool ret = false;
	int playerTeam;
	LocalHero *pLocalHero;
	if (!pMobyDest || !(pLocalHero = GB_GetLocalHeroFromSlot(iPlayer))) return false;
	playerTeam = pLocalHero->mpTeam;
	if (pMobyDest->oClass == 0x2075) {
		int team = *((unsigned char *)pMobyDest->pVar + 0x2e4);
		ret = team == playerTeam;
	}
	return ret;
}

GAME_SECTION(MB_NumValidRespawnNodes) int MB_NumValidRespawnNodes(int iPlayer)
{
	int n = 0;
	LocalHero *pLocalHero = GB_GetLocalHeroFromSlot(iPlayer);
	if (!pLocalHero) return 0;
	if ((unsigned int)pLocalHero->mpTeam < 10) n = g_GameControllerData.numNodesOwned[pLocalHero->mpTeam];
	return n;
}

GAME_SECTION(MB_GhostMe) void MB_GhostMe(MobyInstance *pMoby)
{
	pMoby->alpha = 0x40;
	pMoby->modeBits2 |= 8;
	SetMobyLights(pMoby, 0xff707070, 0xf, 0xf, 0);
}

GAME_SECTION(MB_Level99ColorTimeBased) int MB_Level99ColorTimeBased(int alpha)
{
	int color;
	float t = (float)(worldUpdateTime % 150) / 150.0f;
	if (t < 0.333f) color = FastTweenColor(0x804020, 0x208040, t * 3.0f);
	else if (t < 0.667f) color = FastTweenColor(0x208040, 0x402080, (t - 0.333f) * 3.0f);
	else color = FastTweenColor(0x402080, 0x804020, (t - 0.667f) * 3.0f);
	color &= 0xffffff;
	return color | (alpha << 24);
}

GAME_SECTION(MB_GetXPBundle) int MB_GetXPBundle(MobyInstance *pMoby)
{
	int empty = -1;
	int i;
	for (i = 0; i < 3; i++) {
		if (MB_xpBundle[i].pMoby == 0) empty = i;
		if (MB_xpBundle[i].pMoby == pMoby) return i;
	}
	if (empty >= 0) {
		FastMemSet(&MB_xpBundle[empty], 0, 0x54);
		MB_xpBundle[empty].pMoby = pMoby;
		return empty;
	}
	return -1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyutil", func_0047EEA8);
