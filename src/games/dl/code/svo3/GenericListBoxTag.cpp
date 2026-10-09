#include "CDrawContextBase.h"

#include "CInputContextBase.h"
#include "CPage.h"
#include "SVBrowser.h"
#include "TagUtils.h"
#include "CAudioContextBase.h"
#include "SVOString.h"
#include "CMemoryContextBase.h"
#include "string.h"
#include "GenericListBoxTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_GenericListBoxTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {
extern char svoGenericListBoxTagSource[];

extern "C" {
extern char svoGenericListBoxTagSource[];
}
extern "C" {
extern char svoGenericListBoxTagName[];
}
extern "C" {

}
extern "C" {
extern const SVTagVtablePrefix svoGenericListBoxTagVtable;
extern char svoGenericListBoxMoveClass[];
CAudioContextBaseState *GetAudioContext();
CMemoryContextBaseState *GetMemoryContext();
}
extern "C" {
long Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
void DefaultInit___dupe23(GenericListBoxTagState *);
extern unsigned int svoNextTagId;
}
extern "C" {
extern char svoGenericListBoxFillColorAttribute[];
extern char svoGenericListBoxLineColorAttribute[];
extern char svoGenericListBoxMaxItemsAttribute[];
extern char svoGenericListBoxMaxVisibleItemsAttribute[];
extern char svoGenericListBoxClassAttribute[];
}
extern "C" {

}
#define SECTION(name) __attribute__((section(".svo_GenericListBoxTag_" #name)))

SECTION(FreeResources___dupe56) void FreeResources___dupe56(SVTag *tag)
{
    __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x70);
}

}

extern "C" SECTION(_GenericListBoxTag) void _GenericListBoxTag(GenericListBoxTagState *tag, int flags)
{
    tag->base.vtable = &svoGenericListBoxTagVtable;
    if (tag->m_pTimer) _SVChronograph(tag->m_pTimer, 3);
    if (tag->m_handles) svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_handles);
    if (tag->m_entryTagIDs) svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_entryTagIDs);
    tag->base.vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(&tag->base);
}

extern "C" SECTION(addHandle) long addHandle(GenericListBoxTagState *tag, svo_listbox_handle handle)
{
    if (tag->m_numItems >= tag->m_maxNumItems) return 0;
    if (!handle) {
        __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x1A4);
        return 0;
    }
    const GenericListBoxTagVtablePrefix *vtable = (const GenericListBoxTagVtablePrefix *)tag->base.vtable;
    if (vtable->getIndexOfHandle(tag, handle) != -1)
        __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x1AB);
    tag->m_handles[tag->m_numItems] = handle;
    ++tag->m_numItems;
    return 1;
}

extern "C" SECTION(changeSelectedItem___dupe2) void changeSelectedItem___dupe2(GenericListBoxTagState *tag, int direction)
{
    if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x141);
    if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x142);
    if (!tag->m_numItems) return;
    int old = tag->m_selectedIndex;
    int selected = tag->m_selectedIndex;
    int top = tag->m_topVisibleIndex;
    if (direction == -1) {
        if (selected == -1) tag->m_selectedIndex = tag->m_numItems - 1;
        else {
            int count = tag->m_numItems;
            int next = (selected - 1 + count) % count;
            tag->m_selectedIndex = next;
            if (next < top) tag->m_topVisibleIndex = next;
            else if (next >= top + tag->m_maxVisibleItems) tag->m_topVisibleIndex = top + count - tag->m_maxVisibleItems;
        }
    } else if (direction == 1) {
        if (selected == -1) tag->m_selectedIndex = 0;
        else {
            int count = tag->m_numItems;
            int next = (selected + 1 + count) % count;
            tag->m_selectedIndex = next;
            if (next < top) tag->m_topVisibleIndex = next;
            else if (next >= top + tag->m_maxVisibleItems) tag->m_topVisibleIndex = top + 1;
        }
    }
    if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x175);
    if (tag->m_selectedIndex >= tag->m_numItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x176);
    if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x177);
    if (old != tag->m_selectedIndex) {
        CAudioContextBaseState *audio = GetAudioContext();
        ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 5, svoGenericListBoxMoveClass);
    }
}

extern "C" SECTION(clearList) void clearList(GenericListBoxTagState *tag)
{
    if (tag->m_handles) memset(tag->m_handles, 0, tag->m_maxNumItems * 4);
    tag->m_topVisibleIndex = 0;
    tag->m_numItems = 0;
    tag->m_selectedIndex = 0;
}

extern "C" SECTION(DefaultInit___dupe23) void DefaultInit___dupe23(GenericListBoxTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoGenericListBoxTagName, 64);
    const GenericListBoxTagVtablePrefix *vtable = (const GenericListBoxTagVtablePrefix *)tag->base.vtable;
    tag->base.m_lineColor = 0xFF00FF00;
    tag->m_highlightFillColor = 0xFF808080;
    tag->m_highlightLineColor = 0xFFFFFFFF;
    tag->base.m_fillColor = 0xFFFFFFFF;
    tag->m_handles = 0;
    tag->m_turnOffDraw = 0;
    tag->m_entryTagIDs = 0;
    vtable->clearList(tag);
}

extern "C" SECTION(deleteHandle) long deleteHandle(GenericListBoxTagState *tag, svo_listbox_handle handle)
{
    const GenericListBoxTagVtablePrefix *vtable = (const GenericListBoxTagVtablePrefix *)tag->base.vtable;
    long index = vtable->getIndexOfHandle(tag, handle);
    if (index == -1) return 0;
    if (index >= tag->m_numItems) {
        __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x1D6);
        return 0;
    }
    for (int i = index; i < tag->m_numItems - 1; ++i) {
        tag->m_handles[i] = tag->m_handles[i + 1];
        if (tag->m_selectedIndex == i + 1) tag->m_selectedIndex = i;
    }
    if (index < tag->m_topVisibleIndex + tag->m_maxVisibleItems && tag->m_topVisibleIndex > 0)
        --tag->m_topVisibleIndex;
    --tag->m_numItems;
    tag->m_handles[tag->m_numItems] = 0;
    return 1;
}

extern "C" SECTION(Draw___dupe26) void Draw___dupe26(GenericListBoxTagState *tag)
{
    CDrawContextBase *draw = tag->base.m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0xB0);
    unsigned int line = tag->base.m_lineColor;
    unsigned int fill = tag->base.m_fillColor;
    if (tag->base.m_bSelected) {
        line = tag->m_highlightLineColor;
        fill = tag->m_highlightFillColor;
    }
    float fraction = 0.0f;
    if (tag->m_numItems > 0) {
        int selected = ((const GenericListBoxTagVtablePrefix *)tag->base.vtable)->getSelectedIndex(tag);
        float count = (float)tag->m_numItems;
        if ((float)tag->m_maxNumItems <= count) count = (float)tag->m_maxNumItems;
        fraction = ((float)selected + 1.0f) / count;
    }
    draw->vtable->DrawGenericListboxFrame(draw, tag->base.m_tagid, tag->base.m_x,
        tag->base.m_y, tag->base.m_width, tag->base.m_height, line, fill,
        tag->m_maxVisibleItems, fraction, tag->base.m_tagClass);
    int count = tag->m_numItems;
    if (count > 0) {
        if (tag->m_maxVisibleItems < count) count = tag->m_maxVisibleItems;
        for (int i = 0; i < count; ++i) {
            int item = i + ((const GenericListBoxTagVtablePrefix *)tag->base.vtable)->getTopVisibleIndex(tag);
            int selected = ((const GenericListBoxTagVtablePrefix *)tag->base.vtable)->getSelectedIndex(tag);
            int top = ((const GenericListBoxTagVtablePrefix *)tag->base.vtable)->getTopVisibleIndex(tag);
            unsigned int *id = tag->m_entryTagIDs + i + top;
            top = ((const GenericListBoxTagVtablePrefix *)tag->base.vtable)->getTopVisibleIndex(tag);
            draw->vtable->DrawGenericListboxEntry(draw, *id, tag->base.m_name,
                tag->m_handles[i + top], i, item == selected, tag->base.m_lineColor,
                tag->base.m_fillColor, tag->base.m_tagClass);
        }
    }
}

extern "C" SECTION(GenericListBoxTag) void GenericListBoxTag(GenericListBoxTagState *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoGenericListBoxTagVtable;
    DefaultInit___dupe23(tag);
    getColorAttrib(tag->base.m_xml, svoGenericListBoxFillColorAttribute, &tag->base.m_fillColor);
    getColorAttrib(tag->base.m_xml, svoGenericListBoxLineColorAttribute, &tag->base.m_lineColor);
    getIntAttrib(tag->base.m_xml, svoGenericListBoxMaxItemsAttribute, &tag->m_maxNumItems);
    if (tag->m_maxNumItems < 1) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x3E);
    tag->m_handles = (svo_listbox_handle *)svAllocSafe(GetMemoryContext(), tag->m_maxNumItems << 2, 0, 0x41, svoGenericListBoxTagSource);
    getIntAttrib(tag->base.m_xml, svoGenericListBoxMaxVisibleItemsAttribute, &tag->m_maxVisibleItems);
    if (tag->m_maxVisibleItems < 1) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x45);
    unsigned int *ids = (unsigned int *)svAllocSafe(GetMemoryContext(), tag->m_maxVisibleItems << 2, 0, 0x48, svoGenericListBoxTagSource);
    tag->m_entryTagIDs = ids;
    for (int i = 0; i < tag->m_maxVisibleItems; ++i) *ids++ = svoNextTagId++;
    getStringAttrib(tag->base.m_xml, svoGenericListBoxClassAttribute, &tag->base.m_tagClass);
    SVChronographState *timer = (SVChronographState *)SVChronographNew(0x10);
    SVChronograph(timer, 0);
    tag->m_pTimer = timer;
    Start___dupe3(timer);
}

extern "C" SECTION(getHandleByIndex) long getHandleByIndex(GenericListBoxTagState *tag, int index)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x219);
    if (index < 0 || index >= tag->m_numItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x21a);
    if (!tag->m_handles[index]) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x21b);
    return (int)tag->m_handles[index];
}

extern "C" SECTION(getIndexOfHandle) long getIndexOfHandle(GenericListBoxTagState *tag, svo_listbox_handle handle)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x180);
    if (tag->m_maxVisibleItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x181);
    int count = tag->m_maxNumItems;
    svo_listbox_handle *item = tag->m_handles;
    for (int i = 0; i < count; ++i) if (*item++ == handle) return i;
    return -1;
}

extern "C" SECTION(getNumVisibleRows___dupe2) long getNumVisibleRows___dupe2(GenericListBoxTagState *tag)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x211);
    if (tag->m_maxVisibleItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x212);
    return tag->m_maxVisibleItems;
}

extern "C" SECTION(getSelectedHandle) long getSelectedHandle(GenericListBoxTagState *tag)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x223);
    if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x224);
    if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x225);
    return (int)tag->m_handles[tag->m_selectedIndex];
}

extern "C" SECTION(getSelectedIndex___dupe2) long getSelectedIndex___dupe2(GenericListBoxTagState *tag)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x190);
    if (tag->m_selectedIndex >= tag->m_numItems && tag->m_numItems != 0) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x191);
    return tag->m_selectedIndex;
}

extern "C" SECTION(getTopVisibleIndex___dupe2) long getTopVisibleIndex___dupe2(GenericListBoxTagState *tag)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x202);
    if (tag->m_maxVisibleItems < tag->m_numItems) {
    if (tag->m_topVisibleIndex > tag->m_numItems - tag->m_maxVisibleItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x205);
    } else {
    if (tag->m_topVisibleIndex >= tag->m_numItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x209);
    }
    return tag->m_topVisibleIndex;
}

extern "C" SECTION(HandleInput___dupe54) int HandleInput___dupe54(GenericListBoxTagState *tag, CPage *page)
{
    CInputContextBaseState *input = tag->base.m_contexts->inputContext;
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x7B);
    if (!input) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x7C);
    if (!page) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x7D);
    if (!tag->base.vtable->IsSelected(&tag->base)) return 1;
    int analog = input->vtable->LeftVertical(input, 0x11);
    if (analog && ElapsedMS(tag->m_pTimer) > 250) {
        int magnitude = analog < 0 ? -analog : analog;
        if (magnitude > 45) {
            Reset___dupe5(tag->m_pTimer);
            ((const GenericListBoxTagVtablePrefix *)tag->base.vtable)->changeSelectedItem(tag, analog < 0 ? -1 : 1);
            return 0;
        }
    }
    if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT)) {
        CDrawContextBase *draw = tag->base.m_contexts->drawContext;
        if (!draw) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x9B);
        return !Navigate(&tag->base, input, draw, tag->base.m_xml, page);
    }
    return 1;
}

extern "C" SECTION(selectIndex___dupe2) long selectIndex___dupe2(GenericListBoxTagState *tag, int index)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x137);
    if (index < 0 || index >= tag->m_numItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x138);
    tag->m_selectedIndex = index;
    return 1;
}

extern "C" SECTION(size) long size(GenericListBoxTagState *tag)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x113);
    if (tag->m_numItems < 0) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x114);
    return tag->m_numItems;
}
