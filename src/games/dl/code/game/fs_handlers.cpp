#include "common.h"
#include "game_section.h"


int snd_StreamSafeCdBreak() __asm__("snd_StreamSafeCdBreak");
int abort_file() __asm__("abort_file");
int abort_mission_bank() __asm__("abort_mission_bank");
typedef struct fsLoadBank {
	/* 0x00 */ int mission;
	/* 0x04 */ unsigned int *m_pp_bank_handle;
} fsLoadBank_t;
void cb_missionBankLoadComplete(unsigned int handle, unsigned long user) __asm__("cb_missionBankLoadComplete");

/* Recovered from the retail boot instructions, using names from the prototype's debug data. */
typedef struct fsLoadFile {
	/* 0x00 */ void *p_buffer;
	/* 0x04 */ int lsn;
	/* 0x08 */ int length;
} fsLoadFile_t;
typedef struct fsDeviceArgs {
	/* 0x00 */ unsigned int b_cd_load_complete;
	/* 0x04 */ unsigned char trycount;
	/* 0x05 */ unsigned char spindlctrl;
	/* 0x06 */ unsigned char datapattern;
	/* 0x07 */ unsigned char pad;
} fsDeviceArgs_t;
unsigned int is_complete_file(fsLoadFile_t *p_load, fsDeviceArgs_t *p_device) __asm__("is_complete_file");
typedef struct soundData {
	/* 0x00 */ char unk00[0x90];
	/* 0x90 */ unsigned int handles[8];
} soundData_t;
extern soundData_t Sound __asm__("Sound");
unsigned int is_complete_mission_bank(fsLoadBank_t *p_args, fsDeviceArgs_t *p_device) __asm__("is_complete_mission_bank");
int load_complete_file(fsLoadFile_t *p_load) __asm__("load_complete_file");
int snd_SRAMGetFreeMem() __asm__("snd_SRAMGetFreeMem");
int load_complete_mission_bank(fsLoadBank_t *load_args) __asm__("load_complete_mission_bank");

extern unsigned int g_loadTime __asm__("D_0021DAA0");
extern unsigned int g_loadErr __asm__("g_loadErr");
extern unsigned char g_spinSpeed __asm__("g_spinSpeed");
extern void *soundBank3Addr;
int snd_StreamSafeCdRead(int lsn, int length, void *buffer, void *mode) __asm__("snd_StreamSafeCdRead");
unsigned int load_file(fsLoadFile_t *p_load, fsDeviceArgs_t *p_device) __asm__("load_file");

GAME_SECTION(cb_missionBankLoadComplete) void cb_missionBankLoadComplete(unsigned int handle, unsigned long user)
{
	fsLoadBank_t *args = (fsLoadBank_t *)(long)(int)user;
	if (handle) *args->m_pp_bank_handle = handle;
	else *args->m_pp_bank_handle = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fs_handlers", load_file);

GAME_SECTION(is_complete_file) unsigned int is_complete_file(fsLoadFile_t *p_load, fsDeviceArgs_t *p_device)
{
	return p_device->b_cd_load_complete;
}

GAME_SECTION(abort_file) int abort_file()
{
	return snd_StreamSafeCdBreak();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fs_handlers", func_00163A18);

GAME_SECTION(load_complete_file) int load_complete_file(fsLoadFile_t *p_load)
{
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fs_handlers", load_mission_bank);

GAME_SECTION(is_complete_mission_bank) unsigned int is_complete_mission_bank(fsLoadBank_t *p_args, fsDeviceArgs_t *p_device)
{
	return Sound.handles[3] != 0xffffffff;
}

GAME_SECTION(abort_mission_bank) int abort_mission_bank()
{
	return 1;
}

GAME_SECTION(load_complete_mission_bank) int load_complete_mission_bank(fsLoadBank_t *load_args)
{
	if (*load_args->m_pp_bank_handle) snd_SRAMGetFreeMem();
	return 1;
}
