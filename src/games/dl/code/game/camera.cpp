#include "common.h"
#include "game_section.h"
#include "game_vu0.h"
#include "mobyutil.h"
#include "draw.h"



struct UpdateCam {
	/* 0x00 */ char unk00[0x7d];
	/* 0x7d */ unsigned char active;
	/* 0x7e */ short deactivated;
	/* 0x80 */ char unk80[6];
	/* 0x86 */ short type;
	/* 0x88 */ char unk88[4];
	/* 0x8c */ short camClass;
	/* 0x8e */ char unk8e[0xb0 - 0x8e];
};
struct CameraPolar {
	/* 0x00 */ char unk00[2];
	/* 0x02 */ unsigned char valid;
	/* 0x03 */ unsigned char reqType;
	/* 0x04 */ char unk04[0x4c];
	/* 0x50 */ vec4 quat[2];
	/* 0x70 */ char unk70[0x50];
	/* 0xc0 */ vec4 lastPolar[2];
	/* 0xe0 */ char unke0[0x180 - 0xe0];
	/* 0x180 */ float fovSpeed;
	/* 0x184 */ float fovIdeal;
	/* 0x188 */ float fovActual;
	/* 0x18c */ float fovGain;
	/* 0x190 */ float fovDamp;
	/* 0x194 */ float fovLimit;
	/* 0x198 */ char fovChangeType;
	/* 0x199 */ char fovState;
	/* 0x19a */ short fovTimer;
	/* 0x19c */ float fovTimerInv;
	/* 0x1a0 */ float fovInit;
	/* 0x1a4 */ char unk1a4[0x1b0 - 0x1a4];
	/* 0x1b0 */ int underwater;
	/* 0x1b4 */ char unk1b4[0x470 - 0x2b0 - 0x1b4];
};
struct GameCameraData {
	/* 0x000 */ char unk000[0x50];
	/* 0x050 */ UpdateCam *pCurrent;
	/* 0x054 */ char unk054[0x124 - 0x54];
	/* 0x124 */ moby *pCamColl;
	/* 0x128 */ char unk128[0x1c0 - 0x128];
	/* 0x1c0 */ vec4 moveActualFromExternal;
	/* 0x1d0 */ char unk1d0[0x2b0 - 0x1d0];
	/* 0x2b0 */ CameraPolar polar;
};
struct CamClassDef {
	/* 0x00 */ void *unk00[2];
	/* 0x08 */ void (*setup)(UpdateCam *);
	/* 0x0c */ void *unk0c;
	/* 0x10 */ void (*exit)(UpdateCam *);
};
struct CameraSystem {
	/* 0x0000 */ char unk0000[0x1850];
	/* 0x1850 */ UpdateCam cams[][0x30];
};
extern GameCameraData GameCamera[] __asm__("GameCamera");
extern CamClassDef CamClassDefs[] __asm__("D_003F0F00");
void Camera_UpdateFog(vec4 &) __asm__("Camera_UpdateFog");
void Camera_DestroyReticule(moby *) __asm__("Camera_DestroyReticule");
void HandleCameraUnderWaterOverlay(int) __asm__("HandleCameraUnderWaterOverlay");
void Camera_DeactivateCurrent(int) __asm__("Camera_DeactivateCurrent");
void Camera_CopyLastPolarToQuat(int) __asm__("Camera_CopyLastPolarToQuat");
UpdateCam *Camera_FindCameraOfType(int, int) __asm__("Camera_FindCameraOfType");
void Camera_Exit(UpdateCam *) __asm__("Camera_Exit");
void Camera_runSetupToNewCam(UpdateCam *) __asm__("Camera_runSetupToNewCam");


extern CameraSystem GameCameraSystem __asm__("GameCamera");


struct RETICULE {
	/* 0x000 */ char unk000[0x380];
	/* 0x380 */ int numActive;
	/* 0x384 */ int unk384[3];
};
extern RETICULE Reticule __asm__("Reticule");
extern ViewContext VC __asm__("VC");
float FastSin(float) __asm__("FastSin");
float FastCos(float) __asm__("FastCos");
float FastSubRots(float, float) __asm__("FastSubRots");
float FastAddRots(float, float) __asm__("FastAddRots");
void UpdateViewContext() __asm__("UpdateViewContext");
moby *Spawn_Moby1007(vec4 &, int) __asm__("Spawn_Moby1007");
void DeleteMoby(moby *) __asm__("DeleteMoby");
/* g_nwInfo must be > 8 bytes so it is not treated as small data (lui $3 / lw $2 pattern) */
struct NetInfo {
	/* 0x00 */ int NumLocalPlayers;
	/* 0x04 */ int pad[3];
};
extern NetInfo g_nwInfo __asm__("D_172174");
extern int gFrameHz __asm__("gFrameHz");
void Camera_InitFovSystem(int) __asm__("Camera_InitFovSystem");
void Camera_handleCollWithHero(int, UpdateCam *) __asm__("Camera_handleCollWithHero");
float Cam_InterpAngles(float, float, float *, float, float, float) __asm__("Cam_InterpAngles");
float Cam_InterpValues(float, float, float *, float, float, float) __asm__("Cam_InterpValues");


struct NetInfoFov {
	/* 0x00 */ int unk00[5];
	/* 0x14 */ int NumLocalPlayers;
	/* 0x18 */ int unk18[0x10];
};
extern NetInfoFov g_nwInfoFov __asm__("g_nwInfo");
int FastDecTimer(short &) __asm__("FastDecTimer___dupe2");
float MB_CosineInterpolate(float, float, float) __asm__("MB_CosineInterpolate");
void Camera_UpdateFov(int) __asm__("Camera_UpdateFov");

void Camera_CopyLastQuatToPolar(int) __asm__("Camera_CopyLastQuatToPolar");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_InitFovSystem);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_SetFov);

/* fovActual store must not be moved into the bc1f delay slot: volatile store */
GAME_SECTION(Camera_UpdateFov) void Camera_UpdateFov(int cameraIndex)
{
	GameCameraData *gameCam = &GameCamera[cameraIndex];
	if ((unsigned char)gameCam->polar.fovState == 1) {
		switch ((unsigned char)gameCam->polar.fovChangeType) {
		case 0:
			if (g_nwInfoFov.NumLocalPlayers == 1) gameCam->polar.fovState = 0;
			gameCam->polar.fovActual = gameCam->polar.fovIdeal;
			break;
		case 3: {
			float res = Cam_InterpAngles(gameCam->polar.fovActual, gameCam->polar.fovIdeal, &gameCam->polar.fovSpeed, gameCam->polar.fovGain, gameCam->polar.fovDamp, gameCam->polar.fovLimit);
			float ideal = gameCam->polar.fovIdeal;
			*(volatile float *)&gameCam->polar.fovActual = res;
			if (__builtin_fabsf(res - ideal) < 0.0001f) {
				if (g_nwInfoFov.NumLocalPlayers != 1) return;
				gameCam->polar.fovState = 0;
			}
			break;
		}
		case 1: {
			float fac;
			if (FastDecTimer(gameCam->polar.fovTimer)) gameCam->polar.fovState = 0;
			fac = (float)gameCam->polar.fovTimer * gameCam->polar.fovTimerInv;
			gameCam->polar.fovActual = gameCam->polar.fovIdeal + (gameCam->polar.fovInit - gameCam->polar.fovIdeal) * fac;
			break;
		}
		case 2:
			if (FastDecTimer(gameCam->polar.fovTimer)) gameCam->polar.fovState = 0;
			gameCam->polar.fovActual = MB_CosineInterpolate(gameCam->polar.fovIdeal, gameCam->polar.fovInit, (float)gameCam->polar.fovTimer * gameCam->polar.fovTimerInv);
			break;
		}
		if (g_nwInfoFov.NumLocalPlayers == 1) {
			float hTheta = gameCam->polar.fovActual * 0.5f;
			VC.xratio = FastSin(hTheta) / FastCos(hTheta);
			UpdateViewContext();
		}
	}
}

JUNK_ASM(func_0043A3C8,
	"\tswc1 $f12, 0x0($2)\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", BackupCurrentCam);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", ExecuteCamPostUpdFuncs);

GAME_SECTION(Camera_FindCameraOfType) UpdateCam *Camera_FindCameraOfType(int cameraIndex, int type)
{
	UpdateCam *pCam = GameCameraSystem.cams[cameraIndex];
	int i;
	for (i = 0; i < 0x30; i++, pCam++) {
		if (pCam->type == type) return pCam;
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Cam_InterpVecs);

GAME_SECTION(Cam_InterpValues) float Cam_InterpValues(float current, float target, float *speed, float gain, float damp, float limit)
{
	float diff = target - current;
	if (g_nwInfo.NumLocalPlayers >= 2 && gFrameHz == 1) {
		gain = gain * 60.0f / 30.0f;
		if (limit != 0.0f) limit = limit * 60.0f / 30.0f;
	}
	{
		float f = *speed + (gain * diff - damp * *speed);
		*speed = f;
		if (limit != 0.0f) *speed = (f <? limit) >? -limit;
	}
	{
		float a = __builtin_fabsf(diff);
		*speed = (*speed <? a) >? -a;
	}
	return current + *speed;
}

JUNK_ASM(func_0043A818,
	"\tqmfc2.ni $2, $vf5\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Cam_InterpAngles);

GAME_SECTION(Camera_DeactivateCurrent) void Camera_DeactivateCurrent(int cameraIndex)
{
	GameCamera[cameraIndex].pCurrent->deactivated = 1;
	GameCamera[cameraIndex].pCurrent->active = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_handleCollWithHero);

GAME_SECTION(Camera_runSetupToNewCam) void Camera_runSetupToNewCam(UpdateCam *pCam)
{
	void (*func)(UpdateCam *) = CamClassDefs[pCam->camClass].setup;
	if (func) func(pCam);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_switchToNewCam);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_ActivationCheckPriority);

GAME_SECTION(Camera_Exit) void Camera_Exit(UpdateCam *pCam)
{
	void (*func)(UpdateCam *) = CamClassDefs[pCam->camClass].exit;
	if (func) func(pCam);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", UpdateAllCameras);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_Pos2Polar3d);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_InitBlenderPolarHero);

GAME_SECTION(Camera_CopyLastQuatToPolar) void Camera_CopyLastQuatToPolar(int cameraIndex)
{
	CameraPolar *polar = (CameraPolar *)((char *)GameCamera + 0x2b0 + cameraIndex * 0x470);
	if (polar->valid == 0) {
		s128 pos = polar->quat[0].v;
		polar->lastPolar[0].v = pos;
		if (polar->reqType == 2) {
			s128 m = GameCamera[cameraIndex].moveActualFromExternal.v;
			VU0_OP("vadd.xyz %0, %0, %1" : "+j"(m) : "j"(pos));
			polar->lastPolar[0].v = m;
		}
		polar->lastPolar[1] = polar->quat[1];
	}
}

GAME_SECTION(Camera_CopyLastPolarToQuat) void Camera_CopyLastPolarToQuat(int cameraIndex)
{
	CameraPolar *polar = (CameraPolar *)((char *)GameCamera + 0x2b0 + cameraIndex * 0x470);
	if (polar->valid) {
		polar->quat[0] = polar->lastPolar[0];
		polar->quat[1] = polar->lastPolar[1];
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_InitBlender);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_BlendCamsPosQuat);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_BlendCamsPolQuat);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_BlendCams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", HandleCameraShake);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_UpdateHeroInfo);

GAME_SECTION(HandleCameraUnderWaterOverlay) void HandleCameraUnderWaterOverlay(int cameraIndex)
{
	GameCamera[cameraIndex].polar.underwater = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Cam_HandleHotspots);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_HandleScreenFade);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_HandleScreenFlash);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_CopyGameCameraToRenderCamera);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", UpdateCamera);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_resetToFollow);

JUNK_ASM(func_0043D8E8,
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x90\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n"
	"\tsw $0, 0x4($2)\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xf0\n"
	"\tnop\n");

GAME_SECTION(Camera_DestroyReticule) void Camera_DestroyReticule(moby *pMoby)
{
	Reticule.numActive = 0;
}

JUNK_ASM(func_0043D930,
	"\taddiu $29, $29, 0x60\n"
	"\tnop\n");

GAME_SECTION(Camera_UpdateFog) void Camera_UpdateFog(vec4 &pos)
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_StartShake);

JUNK_ASM(func_0043DA90,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\tori $2, $2, 0x1\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $2, $0, 0x1\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n");
