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
    if (flags & 1) __builtin_delete(context);
}

SVO_INPUT_SECTION(CInputContextBase) void *CInputContextBase(CInputContextBaseState *context)
{
    context->vtable = &svoInputContextVtable;
    for (unsigned int i = 0; i < 26; ++i) {
        context->m_actionButtons[i] = 0;
        context->m_defaultButtons[i] = 0;
    }
    // Preserve the incidental v0 value left by the original constructor loop.
    return (char *)context + 25 * 4;
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
    for (unsigned int i = 0; i < 26; ++i) {
        context->m_actionButtons[i] = context->m_defaultButtons[i];
    }
}

int SVO_INPUT_SECTION(HasActionOccurred) HasActionOccurred(
    CInputContextBaseState *context, unsigned int padmask, PadAction action)
{
    unsigned int button = context->m_actionButtons[action];
    const CInputContextVtablePrefix *table = context->vtable;
    if ((unsigned int)action - 4 >= 12) {
        return table->IsButtonDown(context, padmask, (unsigned short)button) != 0;
    }
    int negative = (action & 1) == 0;
    if (button != 0x10000 && button != 0x20000) {
        if (!table->IsButtonDown(context, padmask, (unsigned short)button)) return 0;
        return negative ? -127 : 127;
    }
    int value;
    if (action == SV_ACTION_SCROLL_UP || action == SV_ACTION_SCROLL_DOWN ||
        action == SV_ACTION_SELECT_UP || action == SV_ACTION_SELECT_DOWN) {
        value = button == 0x10000 ? table->RightVertical(context, padmask) :
                                  table->LeftVertical(context, padmask);
    } else {
        value = button == 0x10000 ? table->RightHorizontal(context, padmask) :
                                  table->LeftHorizontal(context, padmask);
    }
    if (negative) return value > 0 ? 0 : value;
    return value < 0 ? 0 : value;
}

int SVO_INPUT_SECTION(SetButtonMapForPage) SetButtonMapForPage(
    CInputContextBaseState *context, char *pageName)
{
    return 0;
}
