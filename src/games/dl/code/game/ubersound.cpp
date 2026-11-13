#include "common.h"
#include "game_section.h"


struct StreamInterface { // 0x1 (empty class, per dltypes)
	void StopAll(unsigned int, int, void (*)(void *), void *) __asm__("StopAll___dupe2");
};
extern StreamInterface StreamSys __asm__("StreamSys");
void StopAll(int) __asm__("StopAll");
void sound_StopAllSounds() __asm__("sound_StopAllSounds");
void music_Stop() __asm__("music_Stop");
void sound_Update() __asm__("FUN_004e0858");
int snd_FlushSoundCommands() __asm__("snd_FlushSoundCommands");
extern "C" int sceGsSyncV(int);
void UberSound_Stop(unsigned int) __asm__("Stop___dupe2");

GAME_SECTION(Stop___dupe2) void UberSound_Stop(unsigned int b_wait)
{
	StreamSys.StopAll(1, 300, 0, 0);
	StopAll(1);
	sound_StopAllSounds();
	music_Stop();
	sound_Update();
	if (b_wait) {
		while (snd_FlushSoundCommands()) {
			sceGsSyncV(0);
		}
	}
}
