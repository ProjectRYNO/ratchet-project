#include "common.h"
#include "game_section.h"


typedef int s128 __attribute__((mode(TI)));
struct vec4 {
	/* 0x00 */ s128 q;
};
struct moby {
	/* 0x00 */ char unk00[0x10];
	/* 0x10 */ vec4 pos;
	/* 0x20 */ unsigned char bits;
	/* 0x21 */ char unk21[3];
	/* 0x24 */ void *pClass;
	/* 0x28 */ char unk28[0x34 - 0x28];
	/* 0x34 */ unsigned short state;
	/* 0x36 */ char unk36[0x58 - 0x36];
	/* 0x58 */ char *pJoints;
	/* 0x5c */ char unk5c[0xbc - 0x5c];
	/* 0xbc */ short oClass;
	/* 0xbe */ char unkbe[0x100 - 0xbe];
};
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
	/* 0x03 */ char unk03[0x4d];
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
	/* 0x19a */ char unk19a[0x1b0 - 0x19a];
	/* 0x1b0 */ int underwater;
	/* 0x1b4 */ char unk1b4[0x470 - 0x2b0 - 0x1b4];
};
struct GameCameraData {
	/* 0x000 */ char unk000[0x50];
	/* 0x050 */ UpdateCam *pCurrent;
	/* 0x054 */ char unk054[0x124 - 0x54];
	/* 0x124 */ moby *pCamColl;
	/* 0x128 */ char unk128[0x2b0 - 0x128];
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


/* ===== AG3 additions ===== */
struct RETICULE {
	/* 0x000 */ char unk000[0x380];
	/* 0x380 */ int numActive;
	/* 0x384 */ int unk384[3];
};
extern RETICULE Reticule __asm__("Reticule");
struct ViewContext {
	/* 0x00 */ char unk00[0xb0];
	/* 0xb0 */ float xratio;
};
extern ViewContext VC __asm__("VC");
float FastSin(float) __asm__("FastSin");
float FastCos(float) __asm__("FastCos");
float FastSubRots(float, float) __asm__("FastSubRots");
float FastAddRots(float, float) __asm__("FastAddRots");
void UpdateViewContext() __asm__("UpdateViewContext");
moby *Spawn_Moby1007(vec4 &, int) __asm__("Spawn_Moby1007");
void DeleteMoby(moby *) __asm__("DeleteMoby");
struct NetInfo {
	/* 0x00 */ int NumLocalPlayers;
};
extern NetInfo g_nwInfo __asm__("D_172174");
extern int gFrameHz __asm__("gFrameHz");
void Camera_InitFovSystem(int) __asm__("Camera_InitFovSystem");
void Camera_handleCollWithHero(int, UpdateCam *) __asm__("Camera_handleCollWithHero");
float Cam_InterpAngles(float, float, float *, float, float, float) __asm__("Cam_InterpAngles");
float Cam_InterpValues(float, float, float *, float, float, float) __asm__("Cam_InterpValues");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_InitFovSystem);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_SetFov);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_UpdateFov);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", func_0043A3C8);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Cam_InterpValues);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", func_0043A818);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_CopyLastQuatToPolar);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", func_0043D8E8);

GAME_SECTION(Camera_DestroyReticule) void Camera_DestroyReticule(moby *pMoby)
{
	Reticule.numActive = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", func_0043D930);

GAME_SECTION(Camera_UpdateFog) void Camera_UpdateFog(vec4 &pos)
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", Camera_StartShake);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/camera", func_0043DA90);
