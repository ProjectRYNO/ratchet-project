#ifndef HELP_H
#define HELP_H

struct HelpMsg { // 0x10
	/* 0x00 */ char *text;
	/* 0x04 */ short id;
	/* 0x06 */ short shortid;
	/* 0x08 */ short thirdpersonid;
	/* 0x0a */ short coopid;
	/* 0x0c */ short vag;
	/* 0x0e */ short character;
};

struct HelpDef { // 0x28
	/* 0x00 */ int state;
	/* 0x04 */ int counter;
	/* 0x08 */ int message_id;
	/* 0x0c */ int message_index;
	/* 0x10 */ int display_index;
	/* 0x14 */ int message_flg;
	/* 0x18 */ int num_message;
	/* 0x1c */ unsigned int streamHandle;
	/* 0x20 */ short ready_timer;
	/* 0x22 */ short text_time;
	/* 0x24 */ short suspend_timer;
	/* 0x26 */ unsigned char ready;
	/* 0x27 */ unsigned char suspend;
};

#endif
