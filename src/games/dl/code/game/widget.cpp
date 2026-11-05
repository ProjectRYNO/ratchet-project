#include "common.h"
#include "game_section.h"


struct Widget2D {
	/* 0x00 */ short *positions;
	/* 0x04 */ short *uvs;
	/* 0x08 */ int *rgbas;
	/* 0x0c */ char *polys;
	/* 0x10 */ short vert_cnt;
	/* 0x12 */ short prim_cnt;
	/* 0x14 */ unsigned char prim_type;
	/* 0x15 */ char flags;
	/* 0x16 */ short frame_cnt;
	/* 0x18 */ int ipad[2];
};
void GetWidget2DScreenSize(Widget2D *, float, float, float, float &, float &, float) __asm__("GetWidget2DScreenSize");
struct SCRN {
	/* 0x00 */ int size_x;
	/* 0x04 */ int size_y;
	/* 0x08 */ int center_x;
	/* 0x0c */ int center_y;
	/* 0x10 */ int ofs_x;
	/* 0x14 */ int ofs_y;
};
extern SCRN Scrn __asm__("Scrn");
void DrawWidget2D(Widget2D *, int, int, float, float, float, unsigned int, float) __asm__("DrawWidget2D");
void ProcessWidgetVerts2D_asm(short *, int, int, int) __asm__("ProcessWidgetVerts2D_asm");
void ProcessWidgetVerts2D_asm(short *, int, int, int, float, float) __asm__("ProcessWidgetVerts2D_asm___dupe2");
void ProcessWidgetVerts2D_asm(short *, int, int, int, float, float, float) __asm__("ProcessWidgetVerts2D_asm___dupe3");
void DrawWidget2DFlatPrim_asm(Widget2D *, unsigned int, int) __asm__("DrawWidget2DFlatPrim_asm");


GAME_SECTION(DrawWidget2D) void DrawWidget2D(Widget2D *pwidget, int scr_x, int scr_y, float scale_x, float scale_y, float theta_radians, unsigned int rgba, float t_frame)
{
	int frame_id;
	float frame_intp;
	short *verts;
	int cnt;
	if (rgba >> 24) {
		frame_id = (int)t_frame;
		scr_x = scr_x * 16 + Scrn.ofs_x;
		frame_intp = t_frame - frame_id;
		scr_y = scr_y * 16 + Scrn.ofs_y;
		verts = (short *)((char *)pwidget->positions + frame_id * (pwidget->vert_cnt * 4));
		if (frame_intp < 0.001f) {
			if (scale_x == 1.0f && scale_y == 1.0f) {
				ProcessWidgetVerts2D_asm(verts, pwidget->vert_cnt, scr_x, scr_y);
			} else {
				ProcessWidgetVerts2D_asm(verts, pwidget->vert_cnt, scr_x, scr_y, scale_x, scale_y);
			}
		} else {
			ProcessWidgetVerts2D_asm(verts, pwidget->vert_cnt, scr_x, scr_y, scale_x, scale_y, frame_intp);
		}
		DrawWidget2DFlatPrim_asm(pwidget, rgba, pwidget->prim_type);
	}
}

GAME_SECTION(GetWidget2DScreenSize) void GetWidget2DScreenSize(Widget2D *pwidget, float scale_x, float scale_y, float theta_radians, float &size_x, float &size_y, float t_frame)
{
}
