#include "CInputContextBase.h"
#include "CAudioContextBase.h"

extern "C" {
extern const char svoAudioContextVtable[];
extern const CInputContextVtablePrefix svoInputContextVtable;
void __builtin_delete(void *object);
void _CAudioContextBase(CAudioContextBaseState *context, unsigned int flags);
}
#define SVO_INPUT_SECTION(name) __attribute__((section(".svo_input_" #name)))

// This destructor belongs to the original CInputContextBase translation unit.
void SVO_INPUT_SECTION(_CAudioContextBase) _CAudioContextBase(
    CAudioContextBaseState *context, unsigned int flags)
{
    context->vtable = svoAudioContextVtable;
    if (flags & 1) { __builtin_delete(context); return; }
}

SVO_INPUT_SECTION(CInputContextBase) void *CInputContextBase(CInputContextBaseState *context)
{
    context->vtable = &svoInputContextVtable;
    for (unsigned int i = 0; i < 26; ++i) {
        context->m_actionButtons[i] = 0;
        context->m_defaultButtons[i] = 0;
    }
    // Retail falls off the end, leaving the constructor loop's last address in v0.
}

void SVO_INPUT_SECTION(DefineDefaultButtonMap) DefineDefaultButtonMap(
    CInputContextBaseState *context, const SVButtonMap *map)
{
    if (map) {
        context->m_defaultButtons[0] = map->navUpButton;
        context->m_defaultButtons[1] = map->navDownButton;
        context->m_defaultButtons[2] = map->navLeftButton;
        context->m_defaultButtons[3] = map->navRightButton;
        context->m_defaultButtons[4] = map->scrollUpButton;
        context->m_defaultButtons[5] = map->scrollDownButton;
        context->m_defaultButtons[6] = map->scrollLeftButton;
        context->m_defaultButtons[7] = map->scrollRightButton;
        context->m_defaultButtons[8] = map->selectUpButton;
        context->m_defaultButtons[9] = map->selectDownButton;
        context->m_defaultButtons[10] = map->selectLeftButton;
        context->m_defaultButtons[11] = map->selectRightButton;
        context->m_defaultButtons[12] = map->selectPrevItemButton;
        context->m_defaultButtons[13] = map->selectNextItemButton;
        context->m_defaultButtons[14] = map->selectPrevGroupButton;
        context->m_defaultButtons[15] = map->selectNextGroupButton;
        context->m_defaultButtons[16] = map->activateButton;
        context->m_defaultButtons[17] = map->backButton;
        context->m_defaultButtons[18] = map->vkbActivateButton;
        context->m_defaultButtons[19] = map->vkbBackspaceButton;
        context->m_defaultButtons[20] = map->vkbCancelButton;
        context->m_defaultButtons[21] = map->vkbHideButton;
        context->m_defaultButtons[22] = map->vkbShiftButton;
        context->m_defaultButtons[23] = map->vkbScrollLeftButton;
        context->m_defaultButtons[24] = map->vkbScrollRightButton;
        context->m_defaultButtons[25] = map->leaveFocusGroupButton;
    } else {
        context->m_defaultButtons[0] = 0x1000;
        context->m_defaultButtons[1] = 0x4000;
        context->m_defaultButtons[2] = 0x8000;
        context->m_defaultButtons[3] = 0x2000;
        context->m_defaultButtons[4] = 0x20000;
        context->m_defaultButtons[5] = 0x20000;
        context->m_defaultButtons[6] = 0x20000;
        context->m_defaultButtons[7] = 0x20000;
        context->m_defaultButtons[8] = 0x10000;
        context->m_defaultButtons[9] = 0x10000;
        context->m_defaultButtons[10] = 0x10000;
        context->m_defaultButtons[11] = 0x10000;
        context->m_defaultButtons[12] = 0x4;
        context->m_defaultButtons[13] = 0x8;
        context->m_defaultButtons[14] = 0x1;
        context->m_defaultButtons[15] = 0x2;
        context->m_defaultButtons[16] = 0x40;
        context->m_defaultButtons[17] = 0x10;
        context->m_defaultButtons[18] = 0x40;
        context->m_defaultButtons[19] = 0x20;
        context->m_defaultButtons[20] = 0x10;
        context->m_defaultButtons[21] = 0x80;
        context->m_defaultButtons[22] = 0x4;
        context->m_defaultButtons[23] = 0x1;
        context->m_defaultButtons[24] = 0x2;
        context->m_defaultButtons[25] = 0x10;
    }
}

void SVO_INPUT_SECTION(SetDefaultButtonMap) SetDefaultButtonMap(CInputContextBaseState *context)
{
    context->m_actionButtons[0] = context->m_defaultButtons[0];
    context->m_actionButtons[1] = context->m_defaultButtons[1];
    context->m_actionButtons[2] = context->m_defaultButtons[2];
    context->m_actionButtons[3] = context->m_defaultButtons[3];
    context->m_actionButtons[4] = context->m_defaultButtons[4];
    context->m_actionButtons[5] = context->m_defaultButtons[5];
    context->m_actionButtons[6] = context->m_defaultButtons[6];
    context->m_actionButtons[7] = context->m_defaultButtons[7];
    context->m_actionButtons[8] = context->m_defaultButtons[8];
    context->m_actionButtons[9] = context->m_defaultButtons[9];
    context->m_actionButtons[10] = context->m_defaultButtons[10];
    context->m_actionButtons[11] = context->m_defaultButtons[11];
    context->m_actionButtons[12] = context->m_defaultButtons[12];
    context->m_actionButtons[13] = context->m_defaultButtons[13];
    context->m_actionButtons[14] = context->m_defaultButtons[14];
    context->m_actionButtons[15] = context->m_defaultButtons[15];
    context->m_actionButtons[16] = context->m_defaultButtons[16];
    context->m_actionButtons[17] = context->m_defaultButtons[17];
    context->m_actionButtons[18] = context->m_defaultButtons[18];
    context->m_actionButtons[19] = context->m_defaultButtons[19];
    context->m_actionButtons[20] = context->m_defaultButtons[20];
    context->m_actionButtons[21] = context->m_defaultButtons[21];
    context->m_actionButtons[22] = context->m_defaultButtons[22];
    context->m_actionButtons[23] = context->m_defaultButtons[23];
    context->m_actionButtons[24] = context->m_defaultButtons[24];
    context->m_actionButtons[25] = context->m_defaultButtons[25];
}

int SVO_INPUT_SECTION(HasActionOccurred) HasActionOccurred(
    CInputContextBaseState *context, unsigned int padmask, PadAction action)
{
    int result = 0;
    switch (action) {
    case SV_ACTION_SCROLL_UP:
    case SV_ACTION_SELECT_UP:
        if (context->m_actionButtons[action] == 0x10000) result = context->vtable->RightVertical(context, padmask);
        else if (context->m_actionButtons[action] == 0x20000) result = context->vtable->LeftVertical(context, padmask);
        else goto button1;
        if (result > 0) result = 0;
        break;
    button1:
        if (context->vtable->IsButtonDown(context, padmask, context->m_actionButtons[action])) result = -127;
        break;
    case SV_ACTION_SCROLL_DOWN:
    case SV_ACTION_SELECT_DOWN:
        if (context->m_actionButtons[action] == 0x10000) result = context->vtable->RightVertical(context, padmask);
        else if (context->m_actionButtons[action] == 0x20000) result = context->vtable->LeftVertical(context, padmask);
        else goto button2;
        if (result < 0) result = 0;
        break;
    button2:
        if (context->vtable->IsButtonDown(context, padmask, context->m_actionButtons[action])) result = 127;
        break;
    case SV_ACTION_SCROLL_LEFT:
    case SV_ACTION_SELECT_LEFT:
    case SV_ACTION_SELECT_PREV_ITEM:
    case SV_ACTION_SELECT_PREV_GROUP:
        if (context->m_actionButtons[action] == 0x10000) result = context->vtable->RightHorizontal(context, padmask);
        else if (context->m_actionButtons[action] == 0x20000) result = context->vtable->LeftHorizontal(context, padmask);
        else goto button3;
        if (result > 0) result = 0;
        break;
    button3:
        if (context->vtable->IsButtonDown(context, padmask, context->m_actionButtons[action])) result = -127;
        break;
    case SV_ACTION_SCROLL_RIGHT:
    case SV_ACTION_SELECT_RIGHT:
    case SV_ACTION_SELECT_NEXT_ITEM:
    case SV_ACTION_SELECT_NEXT_GROUP:
        if (context->m_actionButtons[action] == 0x10000) result = context->vtable->RightHorizontal(context, padmask);
        else if (context->m_actionButtons[action] == 0x20000) result = context->vtable->LeftHorizontal(context, padmask);
        else goto button4;
        if (result < 0) result = 0;
        break;
    button4:
        if (context->vtable->IsButtonDown(context, padmask, context->m_actionButtons[action])) result = 127;
        break;
    default:
        result = context->vtable->IsButtonDown(context, padmask, context->m_actionButtons[action]) != 0;
        break;
    }
    return result;
}

int SVO_INPUT_SECTION(SetButtonMapForPage) SetButtonMapForPage(
    CInputContextBaseState *context, char *pageName)
{
    return 0;
}
