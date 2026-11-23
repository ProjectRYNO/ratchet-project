#include "common.h"
#include "game_section.h"

int vsync_callback(int) __asm__("vsync_callback");
GAME_SECTION(vsync_callback) int vsync_callback(int)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $3, %%hi(frm_vsync_cnt)\n"
		"\tld $3, %%lo(frm_vsync_cnt)($3)\n"
		"\tlui $4, (0x10000800 >> 16)\n"
		"\tori $4, $4, (0x10000800 & 0xffff)\n"
		"\tlui $5, %%hi(frm_clock_time)\n"
		"\tld $5, %%lo(frm_clock_time)($5)\n"
		"\tdaddiu $3, $3, 0x1\n"
		"\tlui $1, %%hi(frm_vsync_cnt)\n"
		"\tsd $3, %%lo(frm_vsync_cnt)($1)\n"
		"\tlw $2, 0x0($4)\n"
		"\tdsll32 $2, $2, 0\n"
		"\tdsrl32 $2, $2, 0\n"
		"\tdaddu $5, $5, $2\n"
		"\tlui $1, %%hi(frm_vsync_time)\n"
		"\tsd $5, %%lo(frm_vsync_time)($1)\n"
		"\tsync\n"
		"\tei\n"
		"\tjr $31\n"
		"\tdaddu $2, $0, $0\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(vsync_callback) : : : "memory");
}
