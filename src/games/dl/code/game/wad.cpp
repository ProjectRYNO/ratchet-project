#include "common.h"
#include "game_section.h"


struct sceCdRMode {
	/* 0x00 */ unsigned char trycount;
	/* 0x01 */ unsigned char spindlctrl;
	/* 0x02 */ unsigned char datapattern;
	/* 0x03 */ unsigned char pad;
};
extern unsigned char g_spinSpeed __asm__("g_spinSpeed");
int snd_StreamSafeCdRead(unsigned int, unsigned int, void *, sceCdRMode *) __asm__("snd_StreamSafeCdRead");
void snd_SendCache() __asm__("snd_SendCache");
int snd_FlushSoundCommands() __asm__("snd_FlushSoundCommands");
int snd_StreamSafeCdSync(int) __asm__("snd_StreamSafeCdSync");
void wad_GetSectors(int, int, void *) __asm__("wad_GetSectors");
extern char WadBuffer[] __asm__("D_001C2040");
void wad_GetHeaders(char *) __asm__("wad_GetHeaders");

struct wadEntry {
	/* 0x00 */ int lsn;
	/* 0x04 */ int unk04[5];
};
void wad_GetLevelHeaders(int, char *) __asm__("wad_GetLevelHeaders");
extern unsigned int LevelHeaderA[] __asm__("D_001CEBF0");
extern unsigned int LevelHeaderB[] __asm__("D_001CF858");
extern unsigned int LevelHeaderC[] __asm__("D_001CFAF8");
extern unsigned int LevelHeaderEnd[] __asm__("D_001D21E8");

struct wadSectors {
	/* 0x00 */ int offset;
	/* 0x04 */ int size;
};
struct wadLevelEntry {
	/* 0x00 */ wadSectors levelaudiowad;
	/* 0x08 */ wadSectors levelwad;
	/* 0x10 */ wadSectors levelscenewad;
};
struct wadDef {
	/* 0x0000 */ char unk0000[0xc430];
	/* 0xc430 */ wadLevelEntry levels[0x50];
	/* 0xc8b0 */ char unkc8b0[0x101a8 - 0xc8b0];
};
extern wadDef g_wad __asm__("D_001C2040");

GAME_SECTION(wad_GetSectors) void wad_GetSectors(int lsn, int size, void *buff)
{
	sceCdRMode CdRMode;
	CdRMode.spindlctrl = g_spinSpeed;
	CdRMode.trycount = 0x20;
	CdRMode.datapattern = 0;
	CdRMode.pad = 0;
	snd_StreamSafeCdRead(lsn, size, buff, &CdRMode);
	snd_SendCache();
	snd_FlushSoundCommands();
	snd_StreamSafeCdSync(0);
}

GAME_SECTION(wad_GetHeaders) void wad_GetHeaders(char *buff)
{
	int i; wad_GetSectors(0x3e9, 0x1a, buff = WadBuffer); char *ptr = buff;
	ptr += 0xc620;
	for (i = 0x14; i >= 0; i--) {
		*(unsigned int *)ptr = *(unsigned int *)(ptr - 0x1e0);
		ptr += 0x18;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/wad", func_00159AA8);

GAME_SECTION(wad_GetLevelHeaders) void wad_GetLevelHeaders(int level, char *buff)
{
	int audio_scene_level;
	audio_scene_level = level;
	if (level >= 0x28) audio_scene_level = 0;
	else if (level >= 0x14) audio_scene_level = level - 0x14;
	wad_GetSectors(g_wad.levels[level].levelwad.offset, 2, buff);
	{
		unsigned int *s = (unsigned int *)buff;
		unsigned int *d = LevelHeaderA;
		unsigned int *e = LevelHeaderB;
		while (d != e) *d++ = *s++;
	}
	wad_GetSectors(g_wad.levels[audio_scene_level].levelaudiowad.offset, 1, buff);
	{
		unsigned int *s = (unsigned int *)buff;
		unsigned int *d = LevelHeaderB;
		unsigned int *e = LevelHeaderC;
		while (d != e) *d++ = *s++;
	}
	wad_GetSectors(g_wad.levels[audio_scene_level].levelscenewad.offset, 5, buff);
	{
		unsigned int *s = (unsigned int *)buff;
		unsigned int *d = LevelHeaderC;
		unsigned int *e = LevelHeaderEnd;
		while (d != e) *d++ = *s++;
	}
}
