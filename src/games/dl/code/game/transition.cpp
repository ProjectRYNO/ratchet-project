#include "common.h"
#include "game_section.h"
struct FXRegistrySystemInternal;


struct SpaceDef {
	/* 0x00 */ short unk00;
	/* 0x02 */ short timer;
	/* 0x04 */ short unk04[3];
	/* 0x0a */ short draw_monitors;
	/* 0x0c */ short ship_trans;
	/* 0x0e */ short unk0e[3];
	/* 0x14 */ int movie_index;
	/* 0x18 */ int movie_cnt;
	/* 0x1c */ int unk1c;
};
extern SpaceDef Space __asm__("Space");
extern unsigned char g_TransitionMoviePlayed[0x10] __asm__("g_TransitionMoviePlayed");
struct PifHeader;
unsigned long QueuePifLoad(PifHeader *) __asm__("QueuePifLoad");
void Transition_ParseMovie(int) __asm__("Transition_ParseMovie");
void ParseSpaceSceneChunk(int) __asm__("ParseSpaceSceneChunk");
void Transition_UpdateMovieMobys() __asm__("Transition_UpdateMovieMobys");
void Transition_InitPlanetTex(void *, unsigned long &) __asm__("Transition_InitPlanetTex");
void Transition_ResetPlayedMovies() __asm__("Transition_ResetPlayedMovies");
void Transition_SetupFirstMovie(int) __asm__("Transition_SetupFirstMovie");
void Transition_SetupNextMovie(int) __asm__("Transition_SetupNextMovie");


/* Data transition.cpp defines (reached through $gp outside delay slots, or delay-slot only and named
 * g_Transition* in the prototype). */
typedef bool (*fnTransition_Update)();
typedef void (*fnTransition_PostUpdate)(bool);
typedef void (*fnTransition_Draw)(int);
int g_LevelTransitions_LevelTo __asm__("g_LevelTransitions_LevelTo") GAME_GP_DATA = 0;
int g_LevelTransitions_LevelFrom __asm__("g_LevelTransitions_LevelFrom") GAME_GP_DATA = 0;
fnTransition_Update g_fnTransitionUpdate __asm__("D_220938") GAME_GP_DATA = 0;
fnTransition_PostUpdate g_fnTransitionPostUpdate __asm__("D_22093C") GAME_GP_DATA = 0;
fnTransition_Draw g_fnTransitionDraw __asm__("D_220940") GAME_GP_DATA = 0;
unsigned int g_TransitionFlags __asm__("D_220954") GAME_GP_DATA = 0;
int g_TransitionNumMoviesPlayed __asm__("D_22095C") GAME_GP_DATA = 0;
unsigned int g_TransitionNumSounds __asm__("D_220960") GAME_GP_DATA = 0;
float g_TransitionFade __asm__("D_220970") GAME_GP_DATA = 0;
unsigned char g_bTransitionKeepLastFrame __asm__("D_220975") GAME_GP_DATA = 0;
int g_TransitionNumMovieIds __asm__("D_220978") GAME_GP_DATA = 0;
int g_TransitionFinalMovieId __asm__("D_22097C") GAME_GP_DATA = 0;
int g_SpaceScene __asm__("g_SpaceScene") GAME_GP_DATA = 0;
extern int g_gameType __asm__("g_gameType");
extern int g_gameRules __asm__("g_gameRules");
extern int gameMode __asm__("gameMode");
extern int worldUpdateTime __asm__("worldUpdateTime");
extern int active_vu1_mpg __asm__("active_vu1_mpg");
extern int PartIndexNext __asm__("PartIndexNext");
extern int PartIndexTop __asm__("PartIndexTop");
extern int PartActiveCnt __asm__("PartActiveCnt");
extern int JointCacheNumEntries __asm__("JointCacheNumEntries");
extern int g_TransitionSoundIds[16] __asm__("g_TransitionSoundIds");
extern void *g_TransitionSoundBanks[16] __asm__("g_TransitionSoundBanks");
extern int g_TransitionSoundHandles[16] __asm__("g_TransitionSoundHandles");
extern int g_TransitionMovieIds[16] __asm__("g_TransitionMovieIds");
struct MusicGlobals {
	/* 0x00 */ void *trackPos;
	/* 0x04 */ short loading;
	/* 0x06 */ char stop;
	/* 0x07 */ char off;
	/* 0x08 */ char unk08[0xdc];
};
extern MusicGlobals Music __asm__("Music");
struct MobyInstance {
	/* 0x00 */ char unk00[0xac];
	/* 0xac */ void *pVar;
};
struct SceneDef {
	/* 0x000 */ char unk000[0x74];
	/* 0x074 */ int iframe;
	/* 0x078 */ int cframe;
	/* 0x07c */ int ichunk;
	/* 0x080 */ short frame_cnt;
	/* 0x082 */ short unk082;
	/* 0x084 */ short actor_cnt;
	/* 0x086 */ char unk086[0xa8 - 0x86];
	/* 0x0a8 */ char *mem_chunk_comp;
	/* 0x0ac */ char *mem_chunk_uncomp;
	/* 0x0b0 */ char unk0b0[0xe0 - 0xb0];
	/* 0x0e0 */ char *chunks[0x44];
	/* 0x1f0 */ MobyInstance *actors[16];
};
extern SceneDef Scene __asm__("Scene");
struct MemSlotsDef {
	/* 0x00 */ char unk00[0x10];
	/* 0x10 */ char *level_base;
	/* 0x14 */ char unk14[0x9c - 0x14];
	/* 0x9c */ char *perm_base;
};
extern MemSlotsDef MemSlots __asm__("D_0023AB10");
struct GsMemDef {
	/* 0x00 */ int unk00[2];
	/* 0x08 */ int zbuf;
};
extern GsMemDef GSmem __asm__("GSmem");
extern "C" {
	int snd_FlushSoundCommands();
	void snd_StartCaching();
	void snd_SendCache();
	void snd_UnloadBank(void *);
	void snd_ResolveBankXREFS();
	void snd_PlaySoundVolPanPMPB_CB(void *, int, int, int, int, int, void (*)(unsigned int, unsigned long), unsigned long);
	void BankLoadFromEE_SpuLoc_CB(unsigned int, unsigned int, unsigned int, void (*)(unsigned int, unsigned long), unsigned long);
	int sceGsSyncV(int);
}
void sound_BasicCB(unsigned int, unsigned long) __asm__("sound_BasicCB");
void VoiceProcess() __asm__("VoiceProcess");
void nwUpdate() __asm__("nwUpdate");
void UpdateParts() __asm__("UpdateParts");
void ComposeCameraMatrix() __asm__("ComposeCameraMatrix");
void ResetGsRegisters() __asm__("ResetGsRegisters");
void AA_BlurPass() __asm__("AA_BlurPass");
void DeleteMoby(MobyInstance *) __asm__("DeleteMoby");
void SetupSkyGifPaging() __asm__("SetupSkyGifPaging");
void SkyLevelGeneric() __asm__("SkyLevelGeneric");
void DoSkyGifPaging() __asm__("DoSkyGifPaging");
void VU1_addGSregister(unsigned int, unsigned long, int) __asm__("VU1_addGSregister");
void mode_movieInit(int) __asm__("mode_movieInit");
void mode_movieUnInit() __asm__("mode_movieUnInit");
void UpdateModeMovie(void *, unsigned int, void *, unsigned int, void *, unsigned int) __asm__("UpdateModeMovie");
int Transition_GetDropshipTexture(int) __asm__("Transition_GetDropshipTexture");
int Transition_GetLandStalkerTexture(int) __asm__("Transition_GetLandStalkerTexture");
int Transition_GetLevelTo() __asm__("Transition_GetLevelTo");
int Transition_GetLevelFrom() __asm__("Transition_GetLevelFrom");
void Transition_LoadSoundBank(void *, int *, int, int) __asm__("Transition_LoadSoundBank");
void Transition_PlaySound_cb(unsigned int, unsigned long) __asm__("Transition_PlaySound_cb");
void Transition_PlaySound(int) __asm__("Transition_PlaySound");
void Transition_UnloadSounds() __asm__("Transition_UnloadSounds");
void Transition_CleanupMovie() __asm__("Transition_CleanupMovie");
void Transition_Draw(int) __asm__("Transition_Draw");
void Transition_PostDraw() __asm__("Transition_PostDraw");
bool Transition_Update(bool) __asm__("Transition_Update");
void Transition_DrawSky() __asm__("Transition_DrawSky");
void Transition_SetupMovieIds(int, int *, int) __asm__("Transition_SetupMovieIds");
int Transition_GetNumMoviesPlayed() __asm__("Transition_GetNumMoviesPlayed");
void Transition_ResetParticles() __asm__("Transition_ResetParticles");
void Transition_SetScreenFade(float) __asm__("Transition_SetScreenFade");
void Transition_UpdateMidSceneOrMovie() __asm__("Transition_UpdateMidSceneOrMovie");
void Transition_DoMovieMpeg() __asm__("Transition_DoMovieMpeg");
void Transition_DoMovieNpc() __asm__("Transition_DoMovieNpc");
void Transition_SetKeepLastFrame(int) __asm__("Transition_SetKeepLastFrame");

/* ===== AG additions ===== */
extern int PlanetTexLookup[36] __asm__("D_3DBF10");
int FastDecompress(void *, void *) __asm__("FastDecompress");
void Transition_UpdateScreenFade(int, int, int, int) __asm__("Transition_UpdateScreenFade");
void Transition_LoadPlanetTex(int, int &, void *) __asm__("Transition_LoadPlanetTex");
struct MemSlotsFullDef {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ char *vu1_chain[2];
	/* 0x14 */ int unk14[3];
	/* 0x20 */ char *level_base;
};
extern MemSlotsFullDef MemSlotsFull __asm__("D_0023AB00");
extern int vu1_bufSize __asm__("vu1_bufSize");
void FastMemSet(void *, int, int) __asm__("FastMemSet");

/* ===== AM additions ===== */
extern unsigned int MoviesPlayedRecord[] __asm__("MoviesPlayedRecord");
bool Transition_QueueMidSceneOrMovie(int, int, int) __asm__("Transition_QueueMidSceneOrMovie");
extern long _dma_1[] __asm__("D_1170D0");
void VU0_loadMicroProgram(long *) __asm__("VU0_loadMicroProgram");
void Transition_UpdateMovieCamera() __asm__("Transition_UpdateMovieCamera");
bool Transition_UpdateMovie() __asm__("Transition_UpdateMovie");
int MB_rand(int) __asm__("MB_rand");
int Transition_GetMovieId() __asm__("Transition_GetMovieId");

/* ===== AM additions (pass 3) ===== */
struct TrMemcardDef {
	/* 0x000 */ char unk000[0x18];
	/* 0x018 */ short saveslot;
	/* 0x01a */ char unk01a[0x1c4 - 0x1a];
	/* 0x1c4 */ int stage;
	/* 0x1c8 */ int substage;
	/* 0x1cc */ int nextstage;
	/* 0x1d0 */ int unk1d0[5];
	/* 0x1e4 */ int autosave;
	/* 0x1e8 */ int unk1e8[3];
};
extern TrMemcardDef g_memcard __asm__("D_171948");
unsigned char g_bLevelLoadAlmostDone __asm__("D_220950") GAME_GP_DATA = 0;
unsigned char g_bLevelLoadComplete __asm__("D_220951") GAME_GP_DATA = 0;
typedef void (*fnTransition_Post)();
fnTransition_Post g_fnTransitionPost __asm__("D_220944") GAME_GP_DATA = 0;
extern float NtscPalFrameTimeInSecondsFloat __asm__("NtscPalFrameTimeInSecondsFloat");
void memcard_Update() __asm__("memcard_Update");
void UpdateMCState() __asm__("UpdateMCState");
int LoadLevelData() __asm__("LoadLevelData");
void DMAC_VIF1_Disable() __asm__("DMAC_VIF1_Disable");
void ResetDrawGlobals() __asm__("ResetDrawGlobals");
struct FsAM {
	static unsigned int IsLoading() __asm__("IsLoading");
	static void Update(float) __asm__("Update___dupe53");
};
void Transition_Post() __asm__("Transition_Post");
struct TrSoundGlobals {
	/* 0x000 */ char unk000[0x29c];
	/* 0x29c */ unsigned int transBankHandle;
	/* 0x2a0 */ char unk2a0[0x20];
};
extern TrSoundGlobals TrSound __asm__("Sound");
struct TrSFXHeader {
	/* 0x00 */ char unk00[0x2c];
	/* 0x2c */ int sram_size;
};
struct TrSFXBlock {
	/* 0x00 */ char unk00[0x18];
	/* 0x18 */ TrSFXHeader hdr;
};
struct TrHdr {
	/* 0x00 */ int unk00[2];
	/* 0x08 */ int main_offset;
	/* 0x0c */ int unk0c[0x2a];
	/* 0xb4 */ int sound_offsets[16];
};
struct TrHeroSave {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ int points;
	/* 0x10 */ char unk10[0x11];
	/* 0x21 */ unsigned char blueBadges;
	/* 0x22 */ unsigned char unk22;
	/* 0x23 */ unsigned char greenBadges;
	/* 0x24 */ unsigned char goldBadges;
	/* 0x25 */ unsigned char blackBadges;
	/* 0x26 */ char unk26[0x10];
	/* 0x36 */ short progressionArmorLevel;
};
extern TrHeroSave HeroSave __asm__("HeroSave");
static inline int GetPoints() { return HeroSave.points; }
static inline int GetGreenBadges() { return HeroSave.greenBadges; }
static inline int GetBlueBadges() { return HeroSave.blueBadges; }
static inline int GetGoldBadges() { return HeroSave.goldBadges; }
static inline int GetBlackBadges() { return HeroSave.blackBadges; }
void Transition_SetupMidSceneOrMovie() __asm__("Transition_SetupMidSceneOrMovie");
unsigned char g_bTransitionBlur __asm__("D_220974") GAME_GP_DATA = 0;
extern int g_newlevelnum __asm__("g_newlevelnum");
extern unsigned char InFrontEnd __asm__("InFrontEnd");
extern int OcclUpdate __asm__("OcclUpdate");
extern int gsFrame __asm__("gsFrame");
extern int LevelLoadState __asm__("LevelLoadState");
int memcard_Save(int, int) __asm__("memcard_Save");
void Transition_SetupForFrontend() __asm__("Transition_SetupForFrontend");
bool Transition_Pre() __asm__("Transition_Pre");
void Transition_DisplayPassBlur() __asm__("Transition_DisplayPassBlur");
void VU1_sendChain() __asm__("VU1_sendChain");
void VU1_swapChain() __asm__("VU1_swapChain");
void VU1_syncChain(int) __asm__("VU1_syncChain");
void PutDrawBufferSmall() __asm__("PutDrawBufferSmall");
void PutDrawBufferLarge() __asm__("PutDrawBufferLarge");
void ClearDrawBufferLarge(int) __asm__("ClearDrawBufferLarge");
void AA_DisplayPass(int) __asm__("AA_DisplayPass");
void UpdatePad() __asm__("UpdatePad___dupe2");
void UpdateOcclusion() __asm__("UpdateOcclusion");
void FadeToBlackAM(int, unsigned int) __asm__("FadeToBlack");
bool Transition_UpdateAM(unsigned char) __asm__("Transition_Update");
static inline void AM_NetUpdate()
{
	if (g_gameType == 1) {
		VoiceProcess();
		nwUpdate();
	}
}
bool Transition_DoTransition() __asm__("Transition_DoTransition");
typedef unsigned int qword_t[4];
extern qword_t *vu1_bufPtr __asm__("vu1_bufPtr");
extern qword_t gs_regs_blur_copy[] __asm__("D_3DBFA0");
extern qword_t aaDisplayRegs[] __asm__("aaDisplayRegs");
extern qword_t gs_regs_normal[] __asm__("gs_regs_normal");
struct TrCollOutput {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ unsigned int call_cnt;
	/* 0x14 */ int unk14[3];
};
extern TrCollOutput CollOutput __asm__("CollOutput");
extern char OcclVisibility[] __asm__("OcclVisibility");
extern void *LevelSounds __asm__("LevelSounds");
extern int Level __asm__("Level");
struct TrSoundHandles {
	/* 0x00 */ char unk00[0x90];
	/* 0x90 */ void *handles[0x84];
};
extern TrSoundHandles TrSoundH __asm__("Sound");
void mode_requestChange(int, int, int, int, char *) __asm__("mode_requestChange");
void mode_doChange() __asm__("mode_doChange");
void MobyResetAnimLayerCache() __asm__("MobyResetAnimLayerCache");
extern "C" void snd_SetReverbEx(int, int, int, int, int);
void sound_StopAllSounds() __asm__("sound_StopAllSounds");
void music_Stop() __asm__("music_Stop");
void MCSTATE_ClearCommand(int) __asm__("MCSTATE_ClearCommand");
int music_Sync(int) __asm__("music_Sync");
void LoadFrontData() __asm__("LoadFrontData");
struct FsAM2 {
	static void Sync(unsigned int) __asm__("Sync");
};
extern int memcard_icon_delay __asm__("memcard_icon_delay");
extern int g_lastlevelnum __asm__("D_21DA78");
void SetupGifPagingAM(int) __asm__("SetupGifPaging");
void DoGifPagingAM() __asm__("DoGifPaging");
unsigned long GetEffectTex(int, int) __asm__("GetEffectTex");
void DrawSprite(int, int, int, int, int, int, int, int, unsigned long, unsigned long) __asm__("DrawSprite");
void Hud_DrawRotatedSprite16(float, float, float, float, float, int, int, unsigned long) __asm__("Hud_DrawRotatedSprite16");
void DrawScreenOverlay(int, int, int, int) __asm__("DrawScreenOverlay");
extern int g_ActiveDrawPane __asm__("g_ActiveDrawPane");
extern int g_ActiveDrawFrustum __asm__("g_ActiveDrawFrustum");
extern int g_BloomFlag __asm__("g_BloomFlag");
extern int g_DofFlag __asm__("g_DofFlag");
extern void *pRegistered_PreDraws __asm__("pRegistered_PreDraws");
extern void *pRegistered_MobyDraws __asm__("pRegistered_MobyDraws");
extern void *pRegistered_PostDraws __asm__("pRegistered_PostDraws");
extern long _dma_vu0[] __asm__("D_100AE0");
extern char LightTfragsData[] __asm__("LightTfragsData");
extern FXRegistrySystemInternal IntFXReg __asm__("IntFXReg");
int GetScreenFrustumIndex(int) __asm__("GetScreenFrustumIndex");
void UpdateViewContext() __asm__("UpdateViewContext");
void DrawTfrag() __asm__("DrawTfrag");
void Vif1ChainCmd(int) __asm__("Vif1ChainCmd");
void VU1_gsRegsEffects() __asm__("VU1_gsRegsEffects");
void VU1_gsRegsNormal() __asm__("VU1_gsRegsNormal");
void ExecuteDrawFunctions(void *&) __asm__("ExecuteDrawFunctions");
void DrawMobys() __asm__("DrawMobys");
extern "C" void PartProc();
void VU0_loadMicroProgramAM(long *) __asm__("VU0_loadMicroProgram");
struct Math {
	static void PreserveRegs() __asm__("PreserveRegs");
	static void RestoreRegs() __asm__("RestoreRegs");
};
extern "C" void LightTfrags(void *);
void PatchTfragGifs() __asm__("PatchTfragGifs");
void PatchMobyGifs() __asm__("PatchMobyGifs");
void PrepForEffectsRendering(FXRegistrySystemInternal *) __asm__("PrepForEffectsRendering");
void CleanUpAfterEffectsRendering(FXRegistrySystemInternal *) __asm__("CleanUpAfterEffectsRendering");
void UpdateFog(int) __asm__("UpdateFog");
void PostEffects_FrameInit_new() __asm__("PostEffects_FrameInit_new");
void PostEffects_RegisterEngineInit() __asm__("PostEffects_RegisterEngineInit");
void PostEffects_BloomCreate_new() __asm__("PostEffects_BloomCreate_new");
void PostEffects_BloomApply_new() __asm__("PostEffects_BloomApply_new");
void PostEffects_DofCreate_new() __asm__("PostEffects_DofCreate_new");
void PostEffects_RegisterEngineCleanup() __asm__("PostEffects_RegisterEngineCleanup");
void Transition_DefaultDrawAM(bool) __asm__("Transition_DefaultDraw");

GAME_SECTION(Transition_GetDropshipTexture) int Transition_GetDropshipTexture(int level)
{
	int tex = 0;
	int index = level - 1;
	if (g_gameType == 0 && g_gameRules == 1) {
		index = level - 0x15;
	}
	switch (index) {
	case 0:
	case 1:
	case 3:
	case 4:
		tex = 0;
		break;
	case 5:
	case 7:
		tex = 1;
		break;
	case 6:
	case 9:
		tex = 2;
		break;
	case 10:
	case 12:
		tex = 3;
		break;
	case 13:
	case 14:
		tex = 4;
		break;
	}
	return tex;
}

GAME_SECTION(Transition_GetLandStalkerTexture) int Transition_GetLandStalkerTexture(int level)
{
	int index = level - 1;
	if (g_gameType == 0 && g_gameRules == 1) {
		index = level - 0x15;
	}
	switch (index) {
	case 0:
	case 1:
	case 3:
	case 4:
		return 0;
	case 5:
	case 7:
		return 1;
	case 6:
	case 9:
		return 2;
	case 10:
	case 12:
		return 3;
	case 13:
	case 14:
		return 4;
	}
	return 0;
}

GAME_SECTION(Transition_GetLevelTo) int Transition_GetLevelTo()
{
	return g_LevelTransitions_LevelTo;
}

GAME_SECTION(Transition_GetLevelFrom) int Transition_GetLevelFrom()
{
	return g_LevelTransitions_LevelFrom;
}

GAME_SECTION(Transition_LoadSoundBank) void Transition_LoadSoundBank(void *addr, int *handle, int sram_addr, int sram_size)
{
	*handle = -1;
	BankLoadFromEE_SpuLoc_CB((unsigned int)addr, sram_addr, sram_size, sound_BasicCB, (long)handle);
	do {
		FlushCache(0);
		sceGsSyncV(0);
		snd_FlushSoundCommands();
		if (g_gameType == 1) {
			VoiceProcess();
			nwUpdate();
		}
	} while (*handle == -1);
}

GAME_SECTION(Transition_PlaySound_cb) void Transition_PlaySound_cb(unsigned int ret_val_, unsigned long data_)
{
	*(int *)(int)data_ = ret_val_;
}

GAME_SECTION(Transition_PlaySound) void Transition_PlaySound(int SoundId_)
{
	if (SoundId_ >= 0 && SoundId_ < (int)g_TransitionNumSounds) {
		int RemappedId = g_TransitionSoundIds[SoundId_];
		g_TransitionSoundHandles[RemappedId] = -1;
		snd_StartCaching();
		snd_PlaySoundVolPanPMPB_CB(g_TransitionSoundBanks[RemappedId], 0, 0x400, 0, 0, 0, Transition_PlaySound_cb,
			(long)&g_TransitionSoundHandles[RemappedId]);
		snd_SendCache();
		snd_FlushSoundCommands();
	}
}

GAME_SECTION(Transition_UnloadSounds) void Transition_UnloadSounds()
{
	unsigned int i;
	snd_StartCaching();
	for (i = 0; i < g_TransitionNumSounds; i++) {
		snd_UnloadBank(g_TransitionSoundBanks[i]);
	}
	snd_SendCache();
	while (snd_FlushSoundCommands()) {
		if (g_gameType == 1) {
			VoiceProcess();
			nwUpdate();
		}
	}
	snd_ResolveBankXREFS();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_LoadWad);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_LoadSounds);

GAME_SECTION(Transition_LoadPlanetTex) void Transition_LoadPlanetTex(int PlanetId_, int &Size_, void *pPlanetTex_)
{
	char *pBase = MemSlots.level_base + ((int *)MemSlots.level_base)[3];
	int nPlanetTextures = ((int *)pBase)[0];
	unsigned int *PlanetTex_offs = (unsigned int *)(pBase + 0x10);
	if (PlanetId_ >= 36 || PlanetTexLookup[PlanetId_] == -1 || PlanetTexLookup[PlanetId_] >= nPlanetTextures || PlanetTex_offs[PlanetTexLookup[PlanetId_]] == 0) PlanetId_ = 0;
	Size_ = FastDecompress(pBase + PlanetTex_offs[PlanetTexLookup[PlanetId_]], pPlanetTex_);
}

GAME_SECTION(Transition_InitPlanetTex) void Transition_InitPlanetTex(void *pPlanetTex_, unsigned long &Tex0_)
{
	Tex0_ = QueuePifLoad((PifHeader *)pPlanetTex_);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_ParseMovie);

GAME_SECTION(Transition_CleanupMovie) void Transition_CleanupMovie()
{
	int cActor;
	for (cActor = 0; cActor < Scene.actor_cnt; cActor++) {
		MobyInstance *pMoby = Scene.actors[cActor];
		if (pMoby) {
			pMoby->pVar = 0;
			DeleteMoby(pMoby);
			Scene.actors[cActor] = 0;
		}
	}
}

GAME_SECTION(Transition_Draw) void Transition_Draw(int bLevelLoadAlmostDone_)
{
	ComposeCameraMatrix();
	ResetGsRegisters();
	active_vu1_mpg = -1;
	if (g_fnTransitionDraw) {
		g_fnTransitionDraw(bLevelLoadAlmostDone_);
	}
	Transition_PostDraw();
	AA_BlurPass();
}

GAME_SECTION(Transition_PostDraw) void Transition_PostDraw()
{
	int ROT_ARROW_SPEED;
	float width;
	if ((unsigned int)(g_memcard.stage - 0xf) < 2 || g_memcard.nextstage == 0xf || (memcard_icon_delay && g_lastlevelnum >= 0)) {
		SetupGifPagingAM(1);
		ROT_ARROW_SPEED = 55;
		width = 272.0f;
		VU1_addGSregister(0x42, 0x8000000044, 0);
		VU1_addGSregister(0x47, 0x3004b, 0);
		DrawSprite(0x1a9, 0xfa, 0x40, 0x40, 0, 0, 0x40, 0x40, 0x80808080, GetEffectTex(3, 1));
		Hud_DrawRotatedSprite16(7312.0f, 4512.0f, width, width, (float)(gsFrame % ROT_ARROW_SPEED) * -6.2831855f / (float)ROT_ARROW_SPEED, 0x40, 0x40, GetEffectTex(4, 1));
		DoGifPagingAM();
		if ((unsigned int)(g_memcard.stage - 0xf) < 2 || g_memcard.nextstage == 0xf) {
			memcard_icon_delay = 30;
		} else {
			memcard_icon_delay--;
		}
	}
	VU1_addGSregister(0x42, 0x8000000044, 0);
	DrawScreenOverlay(0, 0, 0, (int)(g_TransitionFade * 128.0f));
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_Update);

GAME_SECTION(Transition_DefaultDraw) void Transition_DefaultDrawAM(bool bLevelLoadAlmostDone_)
{
	g_ActiveDrawPane = 0;
	g_ActiveDrawFrustum = GetScreenFrustumIndex(0);
	g_BloomFlag = 0;
	UpdateViewContext();
	ComposeCameraMatrix();
	if (g_TransitionFlags & 1) {
		Transition_DrawSky();
	}
	if (g_TransitionFlags & 2) {
		DrawTfrag();
		Vif1ChainCmd(0x2010000);
	}
	if (pRegistered_PreDraws) {
		VU1_gsRegsEffects();
		SetupGifPagingAM(1);
		ExecuteDrawFunctions(pRegistered_PreDraws);
		DoGifPagingAM();
		VU1_gsRegsNormal();
	}
	if (g_TransitionFlags & 0xc) {
		DrawMobys();
		Vif1ChainCmd(0x2080000);
	}
	SetupGifPagingAM(1);
	if (pRegistered_MobyDraws) {
		ExecuteDrawFunctions(pRegistered_MobyDraws);
	}
	VU1_gsRegsEffects();
	VU1_addGSregister(8, 5, 0);
	VU1_addGSregister(0x47, 0x53001, 0);
	FlushCache(0);
	PartProc();
	active_vu1_mpg = 9;
	VU1_addGSregister(0x47, 0x5360b, 0);
	VU0_loadMicroProgramAM(_dma_vu0);
	FlushCache(0);
	if (g_TransitionFlags & 2) {
		VU1_syncChain(2);
		Math::PreserveRegs();
		LightTfrags(LightTfragsData);
		Math::RestoreRegs();
		PatchTfragGifs();
	}
	if (g_TransitionFlags & 0xc) {
		VU1_syncChain(0x10);
		PatchMobyGifs();
	}
	DoGifPagingAM();
	if (pRegistered_PostDraws) {
		PrepForEffectsRendering(&IntFXReg);
		SetupGifPagingAM(1);
		ExecuteDrawFunctions(pRegistered_PostDraws);
		DoGifPagingAM();
		CleanUpAfterEffectsRendering(&IntFXReg);
	}
	UpdateFog(0);
	PostEffects_FrameInit_new();
	PostEffects_RegisterEngineInit();
	if (g_BloomFlag) {
		PostEffects_BloomCreate_new();
		PostEffects_BloomApply_new();
	}
	if (g_DofFlag) {
		PostEffects_DofCreate_new();
		g_DofFlag = 0;
	}
	PostEffects_RegisterEngineCleanup();
}

GAME_SECTION(Transition_DrawSky) void Transition_DrawSky()
{
	SetupSkyGifPaging();
	SkyLevelGeneric();
	DoSkyGifPaging();
	VU1_addGSregister(0x47, 0x5360b, 0);
	VU1_addGSregister(0x4e, (GSmem.zbuf >> 0xd) | 0x1000000, 0);
}

GAME_SECTION(Transition_SetupForFrontend) void Transition_SetupForFrontend()
{
	int i;
	FastMemSet(OcclVisibility, -1, 0x80);
	if (g_gameType == 1) {
		mode_requestChange(6, 2, 0, 0, 0);
		mode_doChange();
	} else {
		gameMode = 6;
	}
	CollOutput.call_cnt |= 0x80000000;
	if (g_gameType == 0) {
		MobyResetAnimLayerCache();
	}
	FlushCache(0);
	snd_SetReverbEx(2, 0, 0, 0, 0);
	snd_SendCache();
	snd_FlushSoundCommands();
	sound_StopAllSounds();
	music_Stop();
	Music.off = 1;
	for (i = 0; i < 0x84; i++) {
		if (TrSoundH.handles[i]) {
			snd_UnloadBank(TrSoundH.handles[i]);
			snd_ResolveBankXREFS();
			LevelSounds = 0;
			TrSoundH.handles[i] = 0;
		}
	}
	while (g_memcard.stage > 2 || g_memcard.nextstage >= 0) {
		memcard_Update();
		UpdateMCState();
	}
	if (g_memcard.autosave) {
		g_memcard.autosave = 0;
	}
	if (g_memcard.saveslot >= 0) {
		g_memcard.saveslot = -1;
	}
	MCSTATE_ClearCommand(0);
	Music.off = 0;
	music_Sync(1);
	while (snd_FlushSoundCommands()) {
		if (g_gameType == 1) {
			VoiceProcess();
			nwUpdate();
		}
	}
	Music.off = 1;
	FadeToBlackAM(6, 0);
	Level = g_newlevelnum;
	LoadFrontData();
	FsAM2::Sync(1);
	Music.off = 0;
	DMAC_VIF1_Disable();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_Pre);

GAME_SECTION(Transition_Post) void Transition_Post()
{
	if (!g_bLevelLoadComplete) {
		do {
			FlushCache(0);
			sceGsSyncV(0);
			if (g_gameType == 1) {
				VoiceProcess();
				nwUpdate();
			}
			memcard_Update();
			UpdateMCState();
			g_bLevelLoadComplete = LoadLevelData() != 0;
		} while (!g_bLevelLoadComplete);
	}
	while (g_memcard.stage != 2 || g_memcard.nextstage >= 0) {
		FlushCache(0);
		sceGsSyncV(0);
		memcard_Update();
		UpdateMCState();
		if (g_gameType == 1) {
			VoiceProcess();
			nwUpdate();
		}
	}
	Transition_UnloadSounds();
	while (FsAM::IsLoading()) {
		sceGsSyncV(0);
		FsAM::Update(NtscPalFrameTimeInSecondsFloat);
		if (g_gameType == 1) {
			VoiceProcess();
			nwUpdate();
		}
	}
	Music.off = 0;
	DMAC_VIF1_Disable();
	if (g_fnTransitionPost) {
		g_fnTransitionPost();
	}
	ResetDrawGlobals();
	if (g_gameType == 1) {
		VoiceProcess();
		nwUpdate();
	}
}

GAME_SECTION(Transition_DoTransition) bool Transition_DoTransition()
{
	bool bTransitionDone;
	if (g_gameType != 1 && !InFrontEnd) {
		memcard_Save(0, g_newlevelnum);
	}
	AM_NetUpdate();
	if (g_newlevelnum < 0) {
		Transition_SetupForFrontend();
		return true;
	}
	AM_NetUpdate();
	Transition_Pre();
	AM_NetUpdate();
	g_bLevelLoadAlmostDone = false;
	g_bLevelLoadComplete = false;
	bTransitionDone = false;
	while (!bTransitionDone) {
		VU1_sendChain();
		VU1_swapChain();
		PutDrawBufferSmall();
		if (g_bTransitionBlur) {
			Transition_DisplayPassBlur();
		} else {
			AA_DisplayPass(1);
		}
		PutDrawBufferLarge();
		ClearDrawBufferLarge(0);
		ResetDrawGlobals();
		UpdatePad();
		AM_NetUpdate();
		bTransitionDone = Transition_UpdateAM(g_bLevelLoadAlmostDone);
		OcclUpdate = 0;
		UpdateOcclusion();
		Transition_Draw(g_bLevelLoadAlmostDone);
		memcard_Update();
		UpdateMCState();
		VU1_syncChain(1);
		sceGsSyncV(0);
		gsFrame++;
		if (g_SpaceScene == 0) {
			g_bLevelLoadComplete = LoadLevelData() != 0;
		}
		g_bLevelLoadAlmostDone = LevelLoadState > 9;
	}
	AM_NetUpdate();
	if (!g_bTransitionKeepLastFrame) {
		FadeToBlackAM(6, 0);
	}
	AM_NetUpdate();
	Transition_Post();
	return true;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UpdateMovieCamera);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_DrawClankEffects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_MovieRobotEyeGlow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UpdateClankEffects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UpdateMovieMobys);

GAME_SECTION(Transition_UpdateMovie) bool Transition_UpdateMovie()
{
	bool done;
	VU0_loadMicroProgram(_dma_1);
	if (g_gameType == 1) {
		return false;
	}
	done = false;
	Scene.cframe++;
	Scene.iframe++;
	if (Scene.iframe == 1) {
		Transition_PlaySound(Space.movie_index);
	}
	if (Scene.iframe <= Scene.frame_cnt) {
		if (Scene.cframe >= 0x60) {
			Scene.ichunk++;
			ParseSpaceSceneChunk(Scene.ichunk);
		}
		Transition_UpdateMovieCamera();
		Transition_UpdateMovieMobys();
	} else {
		g_TransitionNumMoviesPlayed++;
		done = true;
	}
	return done;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_SetupMovieIds);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_ResetPlayedMovies);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_GetMovieId);

GAME_SECTION(Transition_SetupFirstMovie) void Transition_SetupFirstMovie(int MovieId_)
{
	Transition_ParseMovie(MovieId_);
	Space.movie_index = MovieId_;
	Space.movie_cnt = 0;
	ParseSpaceSceneChunk(0);
}

GAME_SECTION(Transition_SetupNextMovie) void Transition_SetupNextMovie(int MovieId_)
{
	Transition_ParseMovie(MovieId_);
	Space.movie_index = MovieId_;
	ParseSpaceSceneChunk(0);
	Transition_UpdateMovieMobys();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", func_004F4FF0);

GAME_SECTION(Transition_GetNumMoviesPlayed) int Transition_GetNumMoviesPlayed()
{
	return g_TransitionNumMoviesPlayed;
}

GAME_SECTION(Transition_ResetParticles) void Transition_ResetParticles()
{
	PartIndexNext = 0;
	PartIndexTop = -1;
	PartActiveCnt = 0;
}

GAME_SECTION(Transition_UpdateScreenFade) void Transition_UpdateScreenFade(int CurrentTime_, int EndTime_, int FadeUpTime_, int FadeDownTime_)
{
	EndTime_ = EndTime_ - 1;
	if (CurrentTime_ <= 0 || CurrentTime_ >= EndTime_) {
		g_TransitionFade = 0.0f;
	} else if (CurrentTime_ <= FadeUpTime_) {
		g_TransitionFade = (float)CurrentTime_ / (float)FadeUpTime_;
	} else if (CurrentTime_ > EndTime_ - FadeDownTime_) {
		g_TransitionFade = (float)(EndTime_ - CurrentTime_) / (float)FadeDownTime_;
	} else {
		g_TransitionFade = 1.0f;
	}
	g_TransitionFade = 1.0f - g_TransitionFade;
}

GAME_SECTION(Transition_SetScreenFade) void Transition_SetScreenFade(float Fade_)
{
	g_TransitionFade = Fade_;
}

GAME_SECTION(Transition_QueueMidSceneOrMovie) bool Transition_QueueMidSceneOrMovie(int levelFrom, int levelTo, int id)
{
	int any = -1;
	unsigned int mask;
	int cell;
	if (levelFrom != any && Transition_GetLevelFrom() != levelFrom) {
		return false;
	}
	if (levelTo != any && Transition_GetLevelTo() != levelTo) {
		return false;
	}
	cell = (unsigned int)id >> 5;
	mask = 1 << (id & 0x1f);
	if (MoviesPlayedRecord[cell] & mask) {
		return false;
	}
	g_SpaceScene = id;
	return true;
}

GAME_SECTION(Transition_SetupMidSceneOrMovie) void Transition_SetupMidSceneOrMovie()
{
	if (GetPoints() >= 5000 && GetGreenBadges() >= 2) {
		Transition_QueueMidSceneOrMovie(-1, -1, 7);
	}
	if (GetPoints() >= 10000 && GetGreenBadges() >= 3) {
		Transition_QueueMidSceneOrMovie(-1, -1, 9);
	}
	if (GetBlueBadges() > 0) {
		Transition_QueueMidSceneOrMovie(-1, -1, 0xd);
	}
	if (GetPoints() >= 50000 && GetBlueBadges() >= 2) {
		Transition_QueueMidSceneOrMovie(-1, -1, 0xc);
	}
	if (GetGoldBadges() > 0) {
		Transition_QueueMidSceneOrMovie(-1, -1, 0xe);
	}
	if (GetPoints() >= 100000 && GetGoldBadges() >= 2) {
		Transition_QueueMidSceneOrMovie(-1, -1, 0xf);
	}
	if (Transition_GetLevelTo() == 0xb || Transition_GetLevelTo() == 0x1f) {
		Transition_QueueMidSceneOrMovie(-1, -1, 10);
	}
	if (GetPoints() >= 150000 && GetBlackBadges() >= 2) {
		Transition_QueueMidSceneOrMovie(-1, -1, 0x12);
	}
	if (HeroSave.progressionArmorLevel >= 4) {
		Transition_QueueMidSceneOrMovie(-1, -1, 0x14);
	}
}

GAME_SECTION(Transition_UpdateMidSceneOrMovie) void Transition_UpdateMidSceneOrMovie()
{
	if (g_SpaceScene) {
		Music.off = 0;
		if (g_SpaceScene < 0x19) {
			Transition_DoMovieMpeg();
		} else {
			Transition_DoMovieNpc();
		}
		Music.off = 1;
		gameMode = 6;
		g_SpaceScene = 0;
	}
}

GAME_SECTION(Transition_DoMovieMpeg) void Transition_DoMovieMpeg()
{
	mode_movieInit(g_SpaceScene);
	JointCacheNumEntries = 0;
	UpdateModeMovie(0, 0, 0, 0, MemSlots.perm_base - 0x2c0000, 0x2c0000);
	mode_movieUnInit();
}

GAME_SECTION(Transition_DoMovieNpc) void Transition_DoMovieNpc()
{
}

GAME_SECTION(Transition_SetKeepLastFrame) void Transition_SetKeepLastFrame(int bKeep_)
{
	g_bTransitionKeepLastFrame = bKeep_;
}

GAME_SECTION(Transition_DisplayPassBlur) void Transition_DisplayPassBlur()
{
	(*vu1_bufPtr)[0] = 0x30000002;
	(*vu1_bufPtr)[1] = (unsigned int)gs_regs_blur_copy;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000002;
	vu1_bufPtr++;
	(*vu1_bufPtr)[0] = 0x30000029;
	(*vu1_bufPtr)[1] = (unsigned int)aaDisplayRegs;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000029;
	vu1_bufPtr++;
	(*vu1_bufPtr)[0] = 0x30000003;
	(*vu1_bufPtr)[1] = (unsigned int)gs_regs_normal;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000003;
	vu1_bufPtr++;
}
