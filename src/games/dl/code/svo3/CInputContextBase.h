#ifndef CINPUTCONTEXTBASE_H
#define CINPUTCONTEXTBASE_H

enum PadAction {
	SV_ACTION_NAV_UP = 0,
	SV_ACTION_NAV_DOWN = 1,
	SV_ACTION_NAV_LEFT = 2,
	SV_ACTION_NAV_RIGHT = 3,
	SV_ACTION_SCROLL_UP = 4,
	SV_ACTION_SCROLL_DOWN = 5,
	SV_ACTION_SCROLL_LEFT = 6,
	SV_ACTION_SCROLL_RIGHT = 7,
	SV_ACTION_SELECT_UP = 8,
	SV_ACTION_SELECT_DOWN = 9,
	SV_ACTION_SELECT_LEFT = 10,
	SV_ACTION_SELECT_RIGHT = 11,
	SV_ACTION_SELECT_PREV_ITEM = 12,
	SV_ACTION_SELECT_NEXT_ITEM = 13,
	SV_ACTION_SELECT_PREV_GROUP = 14,
	SV_ACTION_SELECT_NEXT_GROUP = 15,
	SV_ACTION_ACTIVATE = 16,
	SV_ACTION_BACK = 17,
	SV_ACTION_VKB_ACTIVATE = 18,
	SV_ACTION_VKB_BACKSPACE = 19,
	SV_ACTION_VKB_CANCEL = 20,
	SV_ACTION_VKB_HIDE = 21,
	SV_ACTION_VKB_SHIFT = 22,
	SV_ACTION_VKB_MOVE_CURSOR_LEFT = 23,
	SV_ACTION_VKB_MOVE_CURSOR_RIGHT = 24,
	SV_ACTION_LEAVE_FOCUS_GROUP = 25,
	SV_ACTION_MAX = 26,
	SV_ACTION_PAD = -1
};

struct CInputContextBaseState;
typedef struct { // 0x24 (verified vtable prefix)
    /* 0x00 */ void *unknown00;
    /* 0x04 */ void *unknown04;
    /* 0x08 */ void *unknown08;
    /* 0x0C */ int (*IsButtonDown)(CInputContextBaseState *, unsigned int, unsigned short);
    /* 0x10 */ void *unknown10;
    /* 0x14 */ int (*LeftHorizontal)(CInputContextBaseState *, unsigned int);
    /* 0x18 */ int (*RightHorizontal)(CInputContextBaseState *, unsigned int);
    /* 0x1C */ int (*LeftVertical)(CInputContextBaseState *, unsigned int);
    /* 0x20 */ int (*RightVertical)(CInputContextBaseState *, unsigned int);
} CInputContextVtablePrefix;

struct CInputContextBaseState { // 0xDC
    /* 0x00 */ unsigned char specialKeyCode;
    /* 0x01 */ unsigned char padding01[3];
    /* 0x04 */ int m_bEnterHit;
    /* 0x08 */ unsigned int m_defaultButtons[26];
    /* 0x70 */ unsigned int m_actionButtons[26];
    /* 0xD8 */ const CInputContextVtablePrefix *vtable;
};

typedef struct { // 0x68
    /* 0x00 */ unsigned int navUpButton;
    /* 0x04 */ unsigned int navDownButton;
    /* 0x08 */ unsigned int navLeftButton;
    /* 0x0C */ unsigned int navRightButton;
    /* 0x10 */ unsigned int scrollUpButton;
    /* 0x14 */ unsigned int scrollDownButton;
    /* 0x18 */ unsigned int scrollLeftButton;
    /* 0x1C */ unsigned int scrollRightButton;
    /* 0x20 */ unsigned int selectUpButton;
    /* 0x24 */ unsigned int selectDownButton;
    /* 0x28 */ unsigned int selectLeftButton;
    /* 0x2C */ unsigned int selectRightButton;
    /* 0x30 */ unsigned int selectPrevItemButton;
    /* 0x34 */ unsigned int selectNextItemButton;
    /* 0x38 */ unsigned int selectPrevGroupButton;
    /* 0x3C */ unsigned int selectNextGroupButton;
    /* 0x40 */ unsigned int activateButton;
    /* 0x44 */ unsigned int backButton;
    /* 0x48 */ unsigned int vkbActivateButton;
    /* 0x4C */ unsigned int vkbBackspaceButton;
    /* 0x50 */ unsigned int vkbCancelButton;
    /* 0x54 */ unsigned int vkbHideButton;
    /* 0x58 */ unsigned int vkbShiftButton;
    /* 0x5C */ unsigned int vkbScrollLeftButton;
    /* 0x60 */ unsigned int vkbScrollRightButton;
    /* 0x64 */ unsigned int leaveFocusGroupButton;
} SVButtonMap;

extern "C" {
void *CInputContextBase(CInputContextBaseState *context);
void DefineDefaultButtonMap(CInputContextBaseState *context, const SVButtonMap *map);
void SetDefaultButtonMap(CInputContextBaseState *context);
int HasActionOccurred(CInputContextBaseState *context, unsigned int padmask, PadAction action);
int SetButtonMapForPage(CInputContextBaseState *context, char *pageName);
}

#endif
