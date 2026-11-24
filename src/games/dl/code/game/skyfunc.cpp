#include "common.h"
#include "game_section.h"


typedef struct skyShell {
	/* 0x00 */ short unk00;
	/* 0x02 */ unsigned short flags;
} skyShell_t;
typedef struct skyData {
	/* 0x00 */ char unk00[6];
	/* 0x06 */ short numShells;
	/* 0x08 */ short sprite_cnt;
	/* 0x0a */ short sprite_max;
	/* 0x0c */ short texCnt;
	/* 0x0e */ short fx_cnt;
	/* 0x10 */ long *tex;
	/* 0x14 */ char unk14[8];
	/* 0x1c */ struct skySprite *sprites;
	/* 0x20 */ skyShell_t *shells[1];
} skyData_t;
extern skyData_t *Sky __asm__("Sky");
void SkyDrawShellGouraud(skyShell_t *) __asm__("SkyDrawShellGouraud");
void SkyDrawShellTextured(skyShell_t *) __asm__("SkyDrawShellTextured");
typedef struct skySprite {
	/* 0x00 */ unsigned char type;
	/* 0x01 */ char unk01[3];
	/* 0x04 */ unsigned int rgba;
	/* 0x08 */ char unk08[4];
	/* 0x0c */ unsigned int user;
	/* 0x10 */ char unk10[0x10];
} skySprite_t;
void SkyDrawShell(int index) __asm__("SkyDrawShell");

extern int *vu1_bufPtr __asm__("vu1_bufPtr");
extern int GSbase __asm__("GSbase");
extern int *sky_gif_page_markerA __asm__("sky_gif_page_markerA");
extern int *sky_gif_page_markerB __asm__("sky_gif_page_markerB");
void BuildGifTextureDma() __asm__("BuildGifTextureDma");
void VU1_texFlush() __asm__("VU1_texFlush");
void DoSkyGifPaging() __asm__("DoSkyGifPaging");
extern int GSloc __asm__("GSloc");
extern int GifLoadCnt __asm__("GifLoadCnt");
extern "C" int rand();
extern int gameMode __asm__("gameMode");
extern int worldUpdateTime __asm__("worldUpdateTime");
extern int skyWorldUpdateTime __asm__("skyWorldUpdateTime");
void SkyInitNightSprites(int, int) __asm__("SkyInitNightSprites");
void UpdateSkyShellMatrix(int, int) __asm__("UpdateSkyShellMatrix");
void SkySpriteProc() __asm__("SkySpriteProc");
void SkyLevelGeneric() __asm__("SkyLevelGeneric");
void SetupSkyGifPaging() __asm__("SetupSkyGifPaging");
void SkyUpdateNightSprites() __asm__("SkyUpdateNightSprites");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", SkyInitNightSprites);

GAME_SECTION(SkyUpdateNightSprites) void SkyUpdateNightSprites()
{
	int is;
	for (is = 0; is < Sky->sprite_cnt; is++) {
		skySprite_t *pspr = &Sky->sprites[is];
		if (pspr->type) {
			int v = rand() >> 16;
			int r = (v & 0x1f00) * 0x400 - 0x202020;
			pspr->rgba = pspr->user + r + (v & 0x1f0) * 0x40 + (v & 0x1f) * 4;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", UpdateSkyShellMatrix);

GAME_SECTION(SkyLevelGeneric) void SkyLevelGeneric()
{
	int do_stars = 0;
	int star_shell;
	int update_cnt;
	int ishell;
	if (Sky->sprite_max != 0) do_stars = Sky->fx_cnt >= 2;
	star_shell = 0;
	if (do_stars) {
		if (Sky->sprite_cnt == 0) SkyInitNightSprites(Sky->sprite_max, 0);
		else SkyUpdateNightSprites();
		star_shell = gameMode == 6;
	}
	update_cnt = worldUpdateTime - skyWorldUpdateTime;
	if (update_cnt > 2) update_cnt = 2;
	for (ishell = 0; ishell < Sky->numShells; ishell++) {
		UpdateSkyShellMatrix(ishell, update_cnt);
		SkyDrawShell(ishell);
		if (do_stars && ishell == star_shell) SkySpriteProc();
	}
	skyWorldUpdateTime = worldUpdateTime;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", SetupSkyGifPaging);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", DoSkyGifPaging);

JUNK_ASM(func_004DF090,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

GAME_SECTION(SkyDrawShell) void SkyDrawShell(int index)
{
	if (index < Sky->numShells) {
		skyShell_t *shell = Sky->shells[index];
		if (shell->flags & 1) SkyDrawShellGouraud(shell);
		else SkyDrawShellTextured(shell);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", SkyDrawShellTextured);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyfunc", SkyDrawShellGouraud);

GAME_SECTION(SkySpriteProc) void SkySpriteProc(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlw $10, -0x3c8f($28)\n" /* Sky */
		"\tlui $1, %%hi(VC)\n"
		"\taddiu $1, $1, %%lo(VC)\n"
		"\tlui $2, %%hi(D_0022597F + 0x4101)\n"
		"\taddiu $2, $2, %%lo(D_0022597F + 0x4101)\n"
		"\tnop\n"
		"\tlw $24, 0x1c($10)\n"
		"\tlhu $25, 0x8($10)\n"
		"\tlw $13, 0x14($10)\n"
		"\tlw $14, 0x10($10)\n"
		"\tbeqz $25, .L004DF768\n"
		"\tnop\n"
		"\tlw $15, -0x3b5f($28)\n" /* vu1_bufPtr */
		"\tpcpyld $31, $31, $0\n"
		"\tlqc2 $vf25, 0x210($1)\n"
		"\tlqc2 $vf26, 0xb0($1)\n"
		"\tlqc2 $vf27, 0x1f0($1)\n"
		"\taddi $24, $24, -0x20\n"
		"\tvdiv Q, $vf25x, $vf26x\n"
		"\tlqc2 $vf29, 0x0($2)\n"
		"\tlqc2 $vf30, 0x10($2)\n"
		"\tlqc2 $vf31, 0x20($2)\n"
		"\tlqc2 $vf20, -0x5bff($28)\n" /* part_dma_template */
		"\tlqc2 $vf21, -0x5bef($28)\n" /* part_draw_template */
		"\tlqc2 $vf22, -0x5bdf($28)\n" /* part_flush_template */
		"\tlqc2 $vf23, -0x5ccf($28)\n" /* sky_sprite_tex_template */
		"\tvwaitq\n"
		"\tvaddq.x $vf25, $vf0, Q\n"
		"\tsq $0, 0x0($15)\n"
		"\tlui $2, %%hi(D_101140)\n"
		"\taddiu $2, $2, %%lo(D_101140)\n"
		"\tlui $1, %%hi(D_101150)\n"
		"\taddiu $1, $1, %%lo(D_101150)\n"
		"\tlw $2, 0x0($2)\n"
		"\tsw $1, 0x4($15)\n"
		"\tlui $1, (0x30000000 >> 16)\n"
		"\tsw $1, 0x0($15)\n"
		"\tnop\n"
		"\tsh $2, 0x0($15)\n"
		"\taddi $15, $15, 0x10\n"
		"\tlq $1, -0x5c1f($28)\n" /* part_dma_setup_a */
		"\tlq $2, -0x5c0f($28)\n" /* D_21FD70 */
		"\tsq $1, 0x0($15)\n"
		"\tsq $2, 0x70($15)\n"
		"\tlui $1, %%hi(VC)\n"
		"\taddiu $1, $1, %%lo(VC)\n"
		"\tlq $2, 0x220($1)\n"
		"\tlq $3, 0x1a0($1)\n"
		"\tsq $2, 0x50($15)\n"
		"\tsq $3, 0x60($15)\n"
		"\tlui $2, (0x44800000 >> 16)\n"
		"\tlui $1, %%hi(D_0022597F + 0x4101)\n"
		"\taddiu $1, $1, %%lo(D_0022597F + 0x4101)\n"
		"\tqmtc2.ni $2, $vf5\n"
		"\tlqc2 $vf1, 0x40($1)\n"
		"\tlqc2 $vf2, 0x50($1)\n"
		"\tlqc2 $vf3, 0x60($1)\n"
		"\tlqc2 $vf4, 0x70($1)\n"
		"\tvmulx.xyzw $vf1, $vf1, $vf5x\n"
		"\tvmulx.xyzw $vf2, $vf2, $vf5x\n"
		"\tvmulx.xyzw $vf3, $vf3, $vf5x\n"
		"\tnop\n"
		"\tsqc2 $vf1, 0x10($15)\n"
		"\tsqc2 $vf2, 0x20($15)\n"
		"\tsqc2 $vf3, 0x30($15)\n"
		"\tsqc2 $vf4, 0x40($15)\n"
		"\taddi $15, $15, 0x80\n"
		"\tnop\n"
		"\taddi $12, $0, 0x0\n"
		"\tnop\n"
		"\taddi $11, $15, 0x0\n"
		"\taddi $15, $15, 0x10\n"
		".globl func_004DF588\nfunc_004DF588:\n"
		"\tblez $25, .L004DF720\n"
		"\tlw $1, 0x3c($24)\n"
		"\tlqc2 $vf1, 0x30($24)\n"
		"\taddi $24, $24, 0x20\n"
		"\tqmtc2.ni $1, $vf10\n"
		"\taddi $25, $25, -0x1\n"
		"\tvmulax.xyz ACC, $vf29, $vf1x\n"
		"\tlbu $10, 0x1($24)\n"
		"\tvmadday.xyz ACC, $vf30, $vf1y\n"
		"\tlb $9, 0x2($24)\n"
		"\tvmaddz.xyz $vf2, $vf31, $vf1z\n"
		"\tlw $7, 0x4($24)\n"
		"\tbltz $9, .L004DF710\n"
		"\tlbu $6, 0x3($24)\n"
		"\tvmulx.xy $vf4, $vf27, $vf10x\n"
		"\tlw $5, 0x8($24)\n"
		"\tvmulw.x $vf10, $vf10, $vf25w\n"
		"\tpref 0x00, 0x40($24)\n"
		"\tvabs.xy $vf3, $vf2\n"
		"\tnop\n"
		"\tvmulz.xy $vf5, $vf26, $vf2z\n"
		"\tnop\n"
		"\tpextlb $7, $0, $7\n"
		"\tqmtc2.ni $0, $vf0\n"
		"\tpextlh $7, $0, $7\n"
		"\tqmtc2.ni $0, $vf0\n"
		"\tvsub.xy $vf3, $vf3, $vf4\n"
		"\tnop\n"
		"\tvdiv Q, $vf10x, $vf2z\n"
		"\tnop\n"
		"\tsll $9, $9, 4\n"
		"\tnop\n"
		"\tadd $9, $9, $14\n"
		"\tnop\n"
		"\tvsub.xy $vf3, $vf5, $vf3\n"
		"\tnop\n"
		"\tld $8, 0x0($9)\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tqmfc2.ni $3, $vf3\n"
		"\tnop\n"
		"\tvaddq.xyzw $vf11, $vf0, Q\n"
		"\tnop\n"
		"\tbltz $3, .L004DF710\n"
		"\tdsll32 $3, $3, 0\n"
		"\tbltz $3, .L004DF710\n"
		"\tnop\n"
		"\tsqc2 $vf1, 0x0($15)\n"
		"\tnop\n"
		"\tqmtc2.ni $5, $vf15\n"
		"\tnop\n"
		"\tvcallms 0xc78\n"
		"\tnop\n"
		"\tbnez $10, .L004DF680\n"
		"\taddi $1, $0, 0x1\n"
		"\tsb $1, 0x1($24)\n"
		"\tnop\n"
		".L004DF680:\n"
		"\tqmfc2.i $1, $vf15\n"
		"\tnop\n"
		"\tvmul.xy $vf11, $vf11, $vf15\n"
		"\tnop\n"
		"\tsw $0, 0xc($15)\n"
		"\tnop\n"
		"\tsq $7, 0x10($15)\n"
		"\tnop\n"
		"\tsqc2 $vf11, 0x20($15)\n"
		"\tnop\n"
		"\tbgezal $8, . + (200)\n"
		"\tsd $6, 0x28($15)\n"
		"\tsd $8, 0x30($15)\n"
		"\tnop\n"
		"\taddi $12, $12, 0x4\n"
		"\tsd $0, 0x38($15)\n"
		"\taddi $1, $12, -0x78\n"
		"\tnop\n"
		"\tbltz $1, func_004DF588\n"
		"\taddi $15, $15, 0x40\n"
		"\tsqc2 $vf21, 0x0($15)\n"
		"\tsub $1, $15, $11\n"
		"\tsrl $2, $1, 4\n"
		"\taddi $15, $15, 0x10\n"
		"\tsqc2 $vf20, 0x0($11)\n"
		"\tnop\n"
		"\tsh $2, 0x0($11)\n"
		"\taddi $2, $2, -0x1\n"
		"\tsb $2, 0xe($11)\n"
		"\tnop\n"
		"\tsw $12, 0x3c($11)\n"
		"\taddi $12, $0, 0x0\n"
		"\taddi $11, $15, 0x0\n"
		"\taddi $15, $15, 0x10\n"
		"\tj func_004DF588\n"
		"\tnop\n"
		".L004DF710:\n"
		"\tbeqz $10, func_004DF588\n"
		"\tnop\n"
		"\tj func_004DF588\n"
		"\tsb $0, 0x1($24)\n"
		".L004DF720:\n"
		"\tbeqz $12, .L004DF758\n"
		"\taddi $15, $15, -0x10\n"
		"\taddi $15, $15, 0x10\n"
		"\tnop\n"
		"\tsqc2 $vf21, 0x0($15)\n"
		"\tsub $1, $15, $11\n"
		"\tsrl $2, $1, 4\n"
		"\taddi $15, $15, 0x10\n"
		"\tsqc2 $vf20, 0x0($11)\n"
		"\tnop\n"
		"\tsh $2, 0x0($11)\n"
		"\taddi $2, $2, -0x1\n"
		"\tsb $2, 0xe($11)\n"
		"\tsw $12, 0x3c($11)\n"
		".L004DF758:\n"
		"\tsqc2 $vf22, 0x0($15)\n"
		"\taddi $15, $15, 0x10\n"
		"\tsw $15, -0x3b5f($28)\n" /* vu1_bufPtr */
		"\tpcpyud $31, $31, $0\n"
		".L004DF768:\n"
		".set at\n.set reorder" : : : "memory");
}
