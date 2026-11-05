#include "common.h"
#include "game_section.h"


extern short CutSceneOffsets[] __asm__("D_3DB0A0");
int GetMovieOffset(int id) __asm__("GetMovieOffset");


GAME_SECTION(GetMovieOffset) int GetMovieOffset(int id)
{
	int i;
	if (id >= 100) {
		for (i = 0x4f; i >= 0; i--) {
			if (CutSceneOffsets[i] <= id && CutSceneOffsets[i] != 0) {
				id -= CutSceneOffsets[i];
				break;
			}
		}
	}
	return id;
}
