#ifndef WAD_H
#define WAD_H

#include "update_core.h"

struct fileblock { // 0x8
	/* 0x00 */ int offset;
	/* 0x04 */ int length;
};

struct mpegwad { // 0x648
	/* 0x000 */ int hsize;
	/* 0x004 */ int sector;
	/* 0x008 */ binblock story[200];
};

struct miscwad { // 0x50
	/* 0x00 */ int hsize;
	/* 0x04 */ int sector;
	/* 0x08 */ fileblock debugfont;
	/* 0x10 */ fileblock irx;
	/* 0x18 */ fileblock savegame;
	/* 0x20 */ fileblock frontbin;
	/* 0x28 */ fileblock frontbin_net;
	/* 0x30 */ fileblock frontend;
	/* 0x38 */ fileblock exit;
	/* 0x40 */ fileblock bootwad;
	/* 0x48 */ fileblock gadget;
};

struct bonuswad { // 0x2a8
	/* 0x000 */ int hsize;
	/* 0x004 */ int sector;
	/* 0x008 */ fileblock credits_text[6];
	/* 0x038 */ fileblock credits_images[13];
	/* 0x0a0 */ fileblock demomenu[6];
	/* 0x0d0 */ fileblock demoexit[6];
	/* 0x100 */ fileblock cheat_images[20];
	/* 0x1a0 */ fileblock skill_images[31];
	/* 0x298 */ fileblock trophy_image;
	/* 0x2a0 */ fileblock dige;
};

struct spacewad { // 0x68
	/* 0x00 */ int hsize;
	/* 0x04 */ int sector;
	/* 0x08 */ fileblock transition_wads[12];
};

struct armordata { // 0x10
	/* 0x0 */ fileblock main;
	/* 0x8 */ fileblock vram;
};

struct armorwad { // 0x228
	/* 0x000 */ int hsize;
	/* 0x004 */ int sector;
	/* 0x008 */ armordata index[20];
	/* 0x148 */ fileblock bot_texs[12];
	/* 0x1a8 */ fileblock landstalker_texs[8];
	/* 0x1e8 */ fileblock dropship_texs[8];
};

struct chunkblock { // 0x4
	/* 0x0 */ int offset;
};

struct audiowad { // 0xa870
	/* 0x0000 */ int hsize;
	/* 0x0004 */ int sector;
	/* 0x0008 */ chunkblock vendor[254];
	/* 0x0400 */ binblock global_sfx[12];
	/* 0x0460 */ chunkblock help[2100];
	/* 0x2530 */ chunkblock help_f[2100];
	/* 0x4600 */ chunkblock help_g[2100];
	/* 0x66d0 */ chunkblock help_s[2100];
	/* 0x87a0 */ chunkblock help_i[2100];
};

struct hudwad { // 0xf88
	/* 0x000 */ int hsize;
	/* 0x004 */ int sector;
	/* 0x008 */ fileblock online_images[74];
	/* 0x258 */ fileblock ratchet_seqs[28];
	/* 0x338 */ fileblock hud_seqs[20];
	/* 0x3d8 */ fileblock vendor;
	/* 0x3e0 */ fileblock all_text[8];
	/* 0x420 */ fileblock hudw3d;
	/* 0x428 */ fileblock e3_level_ss[10];
	/* 0x478 */ fileblock nw_dnas_image;
	/* 0x480 */ fileblock splitScreenTex;
	/* 0x488 */ fileblock radar_maps[15];
	/* 0x500 */ fileblock weapon_plates_large[20];
	/* 0x5a0 */ fileblock mission_plates_large[15];
	/* 0x618 */ fileblock gui_plates[23];
	/* 0x6d0 */ fileblock vendor_plates[46];
	/* 0x840 */ fileblock loading_screen;
	/* 0x848 */ fileblock planets[16];
	/* 0x8c8 */ fileblock cinematics[21];
	/* 0x970 */ fileblock equip_large[24];
	/* 0xa30 */ fileblock equip_small[5];
	/* 0xa58 */ fileblock moves[15];
	/* 0xad0 */ fileblock save_level[16];
	/* 0xb50 */ fileblock save_empty[4];
	/* 0xb70 */ fileblock skills[26];
	/* 0xc40 */ fileblock reward_back;
	/* 0xc48 */ fileblock complete_back;
	/* 0xc50 */ fileblock complete_back_coop;
	/* 0xc58 */ fileblock rewards[26];
	/* 0xd28 */ fileblock leaderboard;
	/* 0xd30 */ fileblock cutaways[7];
	/* 0xd68 */ fileblock sketchbook[34];
	/* 0xe78 */ fileblock character_epilogues[6];
	/* 0xea8 */ fileblock character_cards[7];
	/* 0xee0 */ fileblock equip_plate;
	/* 0xee8 */ fileblock hud_flythru;
	/* 0xef0 */ fileblock mp_maps[15];
	/* 0xf68 */ fileblock tourney_plates_large[4];
};

struct onlinewad { // 0x68
	/* 0x00 */ int hsize;
	/* 0x04 */ int sector;
	/* 0x08 */ fileblock data;
	/* 0x10 */ fileblock transition_bgs[11];
};

struct levelinfo { // 0x18
	/* 0x00 */ fileblock levelaudiowad;
	/* 0x08 */ fileblock levelwad;
	/* 0x10 */ fileblock levelscenewad;
};

struct _reverb { // 0x4
	/* 0x0 */ int type;
};

struct _mms { // 0x4
	/* 0x0 */ int size;
};

struct levelwad { // 0xc68
	/* 0x000 */ int hsize;
	/* 0x004 */ int sector;
	/* 0x008 */ int level;
	/* 0x00c */ _reverb reverb;
	/* 0x010 */ _mms max_mission_sizes[2];
	/* 0x018 */ fileblock data;
	/* 0x020 */ fileblock core_bank;
	/* 0x028 */ fileblock chunk[3];
	/* 0x040 */ fileblock chunkbank[3];
	/* 0x058 */ fileblock _gameplay_core;
	/* 0x060 */ fileblock gameplay_mission_instances[128];
	/* 0x460 */ fileblock gameplay_mission_data[128];
	/* 0x860 */ fileblock mission_banks[128];
	/* 0xc60 */ fileblock art_instances;
};

struct levelaudiowad { // 0x2a0
	/* 0x000 */ int hsize;
	/* 0x004 */ int sector;
	/* 0x008 */ binblock bindata[80];
	/* 0x288 */ binblock upgradesample;
	/* 0x290 */ binblock platinumbolt;
	/* 0x298 */ binblock spare;
};

struct sceneblock { // 0x14c
	/* 0x000 */ int speech;
	/* 0x004 */ int speech_r;
	/* 0x008 */ fileblock subtitles;
	/* 0x010 */ int speech_f;
	/* 0x014 */ int speech_f_r;
	/* 0x018 */ int speech_g;
	/* 0x01c */ int speech_g_r;
	/* 0x020 */ int speech_s;
	/* 0x024 */ int speech_s_r;
	/* 0x028 */ int speech_i;
	/* 0x02c */ int speech_i_r;
	/* 0x030 */ fileblock mobyload;
	/* 0x038 */ chunkblock chunks[69];
};

struct levelscenewad { // 0x26f0
	/* 0x0000 */ int hsize;
	/* 0x0004 */ int sector;
	/* 0x0008 */ sceneblock scenes[30];
};

struct wadinfo { // 0x101a8
	/* 0x00000 */ mpegwad mpeg;
	/* 0x00648 */ miscwad misc;
	/* 0x00698 */ bonuswad bonus;
	/* 0x00940 */ spacewad space;
	/* 0x009a8 */ armorwad armor;
	/* 0x00bd0 */ audiowad audio;
	/* 0x0b440 */ hudwad hud;
	/* 0x0c3c8 */ onlinewad online;
	/* 0x0c430 */ levelinfo levels[80];
	/* 0x0cbb0 */ levelwad level;
	/* 0x0d818 */ levelaudiowad levelaudio;
	/* 0x0dab8 */ levelscenewad levelscene;
};

#endif
